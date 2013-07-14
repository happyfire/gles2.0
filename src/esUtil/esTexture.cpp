#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GLES2/gl2.h>
#include <EGL/egl.h>
#include "esUtil.h"
#include "Image.h"


GLuint ESUTIL_API esCreateTextureFromTGA(const char* tgaFilePath)
{
	Image img;
	TexImage tex;

	img.loadTGA(&tex, tgaFilePath);

	GLsizei width, height;
	const void *data;

	width = tex.width;
	height = tex.height;
	data = tex.imageData;


	GLuint newTexture;

	// Generates a new texture name/id.
	glGenTextures(1, &newTexture);

	// Binds the new name/id to really create the texture and hold it to set its properties.
	glBindTexture(GL_TEXTURE_2D, newTexture);

	// Uploads the pixel data to the bound texture.
	glTexImage2D(GL_TEXTURE_2D, 0, tex.imageType, width, height, 0, tex.imageType, GL_UNSIGNED_BYTE, data);

	// Defines the Minification and Magnification filters to the bound texture.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Generates a full MipMap chain to the current bound texture.
	glGenerateMipmap(GL_TEXTURE_2D);

	img.release(&tex);

	return newTexture;
}