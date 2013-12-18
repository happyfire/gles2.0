#ifndef ESL_MATERIAL_H
#define ESL_MATERIAL_H

#include "BaseObject.h"
#include "sharedPtr.h"
#include "glcommon.h"
#include <map>
#include <vector>

NS_ESLIB_BEGIN

ESL_FORWARD_PTR(Material)
ESL_FORWARD_PTR(ShaderProgram)
ESL_FORWARD_PTR(Texture)

//Material class

static const int k_maxTextureUnitNum = 8;

enum MatPropertyType
{
	MPT_FLOAT1,
	MPT_FLOAT2,
	MPT_FLOAT3,
	MPT_FLOAT4,
	MPT_INT1,
	MPT_INT2,
	MPT_INT3,
	MPT_INT4,
	MPT_MATRIX,
	MPT_TEXTURE_UNIT,
};

struct MaterialProperty
{
	std::string mName;
	MatPropertyType mType;
	union{
		float fValue;
		float fVec2[2];
		float fVec3[3];
		float fVec4[4];
		int iValue;
		int iVec2[2];
		int iVec3[3];
		int iVec4[4];
		float fMatrix[16];
	};
};

class Material: public BaseObject
{
public:
	Material();
	virtual ~Material();

	Material& setShaderProgramFromFile(const char* vsFile, const char* fsFile);
	Material& setShaderProgramFromSource(const char* vsSrc, const char* fsSrc);
	Material& setShaderProgram(const ShaderProgramPtr& program);
	Material& setProperty(const std::string& name, const MaterialProperty& property);
	Material& setTextureProperty(const std::string& propertyName, const char* textureFile);

	Material& setTexture(unsigned int textureUnit, const char* textureFile);

	void updateShaderProperites();

	const ShaderProgramPtr& getShaderProgram() const;

	void apply() const;

private:
	ShaderProgramPtr m_shaderProgram;

	typedef std::map<std::string, MaterialProperty> PropertyMap;
	typedef PropertyMap::iterator PropertyMapIter;

	PropertyMap m_properties;

	std::vector<TexturePtr> m_textures;
};



NS_ESLIB_END

#endif //ESL_MATERIAL_H