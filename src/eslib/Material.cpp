#include "Material.h"
#include "eslib/ShaderProgram.h"
#include "eslib/Texture.h"
#include "eslib/Shader.h"
#include "esUtil/esUtil.h"

NS_ESLIB_BEGIN

Material::Material()
{
}

Material::~Material()
{
	m_properties.clear();
}

Material& Material::setShaderProgramFromFile(const char* vsFile, const char* fsFile)
{
	char* vsSrc = 0;
	esLoadFile(vsFile, &vsSrc);

	char* fsSrc = 0;
	esLoadFile(fsFile, &fsSrc);

    setShaderProgramFromSource(vsSrc, fsSrc);
    
    delete[] vsSrc;
    delete[] fsSrc;
    
    return *this;
}

Material& Material::setShaderProgramFromSource(const char* vsSrc, const char* fsSrc)
{
	ShaderPtr vs = new Shader();
	vs->create(GL_VERTEX_SHADER, vsSrc);

	ShaderPtr fs = new Shader();
	fs->create(GL_FRAGMENT_SHADER, fsSrc);

	m_shaderProgram = new ShaderProgram();
	m_shaderProgram->create(vs,fs);

	ESL_ASSERT(m_shaderProgram->isValid());

	return *this;
}

Material& Material::setShaderProgram(const ShaderProgramPtr& program)
{
	m_shaderProgram = program;
	return *this;
}

Material& Material::setProperty(const std::string& name, const MaterialProperty& property)
{
	m_properties[name] = property;
	return *this;
}

Material& Material::setTextureProperty(const std::string& propertyName, const char* textureFile)
{
	PropertyMapIter iter = m_properties.find(propertyName);
	if(iter==m_properties.end())
	{
		int unit = m_textures.size()+1;
		TexturePtr tex = new Texture();
		tex->create(textureFile);
		m_textures.push_back(tex);
		
		MaterialProperty texP;
		texP.mName = propertyName;
		texP.mType = MPT_TEXTURE_UNIT;
		texP.iValue = unit;
		setProperty(propertyName, texP);
	}
	else
	{
		MaterialProperty& texP = iter->second;
		setTexture(texP.iValue, textureFile);
	}

	return *this;
}

Material& Material::setTexture(unsigned int textureUnit, const char* textureFile)
{
	ESL_ASSERT(textureUnit>=1 && textureUnit<=k_maxTextureUnitNum);

	if(textureUnit<=m_textures.size())
	{	
		m_textures[textureUnit-1] = new Texture();
		m_textures[textureUnit-1]->create(textureFile);
	}
	else
	{
		TexturePtr tex = new Texture();
		tex->create(textureFile);
		m_textures.push_back(tex);
	}
	return *this;
}

void Material::updateShaderProperites()
{
	ESL_ASSERT(m_shaderProgram->isValid());

	PropertyMapIter iter = m_properties.begin();
	for (;iter!=m_properties.end();++iter)
	{
		MaterialProperty& matP = iter->second;
		switch(matP.mType){
			case MPT_FLOAT3:
				m_shaderProgram->setUniform(matP.mName.c_str(), matP.fVec3[0], matP.fVec3[1], matP.fVec3[2]);
				break;
			case MPT_FLOAT4:
				m_shaderProgram->setUniform(matP.mName.c_str(), matP.fVec4[0], matP.fVec4[1], matP.fVec4[2], matP.fVec4[3]);
				break;
			case MPT_INT1:
				m_shaderProgram->setUniform(matP.mName.c_str(), matP.iValue);
				break;
			case MPT_MATRIX:
				m_shaderProgram->setUniformMatrix4fv(matP.mName.c_str(), matP.fMatrix);
				break;
			case MPT_TEXTURE_UNIT:
				m_shaderProgram->setUniform(matP.mName.c_str(), matP.iValue);
				glActiveTexture(GL_TEXTURE0+matP.iValue-1);//just for illustration
				glBindTexture(GL_TEXTURE_2D, m_textures[matP.iValue-1]->getTextureObject());
				break;

		}
	}
}

const ShaderProgramPtr& Material::getShaderProgram() const
{
	return m_shaderProgram;
}

void Material::apply() const
{
	ESL_ASSERT(m_shaderProgram->isValid());

	glUseProgram(m_shaderProgram->getProgramObject());
}

NS_ESLIB_END
