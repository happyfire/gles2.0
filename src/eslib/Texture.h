#ifndef ESL_TEXTURE_H
#define ESL_TEXTURE_H

#include "BaseObject.h"
#include "glcommon.h"

NS_ESLIB_BEGIN

ESL_FORWARD_PTR(Texture)

//Texture class

class Texture: public BaseObject
{
public:
	Texture();
	virtual ~Texture();

	bool create(const char* file);

	bool isValid() const;

	GLuint getTextureObject() const;

private:
	GLuint m_textureObject;
};



NS_ESLIB_END

#endif //ESL_TEXTURE_H
