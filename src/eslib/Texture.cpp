#include "Texture.h"
#include "esUtil/esUtil.h"

NS_ESLIB_BEGIN

Texture::Texture()
:m_textureObject(0)
{
}

Texture::~Texture()
{
	if(m_textureObject!=0)
	{
		glDeleteTextures(1,&m_textureObject);
	}
}

bool Texture::create(const char* file)
{
	m_textureObject = esCreateTextureFromTGA(file);
	return true;
}

bool Texture::isValid() const
{
	return m_textureObject!=0;
}

GLuint Texture::getTextureObject() const
{
	return m_textureObject;
}

NS_ESLIB_END