#ifndef _IMAGE_H_
#define _IMAGE_H_

#include "esUtil.h"
#include <stdio.h>

// These defines are used to tell us about the type of TARGA file it is
#define TGA_RGB		 2		// This tells us it's a normal RGB (really BGR) file
#define TGA_A		 3		// This tells us it's a ALPHA file
#define TGA_RLE		10		// This tells us that the targa is Run-Length Encoded (RLE)


#pragma pack( push, 1 )			//禁止字节自动对齐

typedef struct
{
	GLubyte		descLen;
	GLubyte		cmapType;
	GLubyte		imageType;
	GLshort		cmapStart;
	GLushort	cmapEntries;
	GLubyte		cmapBits;
	GLushort	xOffset;
	GLushort	yOffset;
}Header;

typedef struct 
{
	Header		head;
	GLushort	width;
	GLushort	height;
	GLubyte		bpp;
	GLubyte		attrib;
}TGAHeader;


typedef struct _tTexImage
{
	GLubyte*	imageData;
	GLuint		width;
	GLuint		height;
	GLuint		bpp;				//Image color depth in bits per pixel	
	GLuint		imageType;
	GLboolean	bCompressed;		//Compressed or Uncompressed

	_tTexImage():imageData(NULL){}
}TexImage;

#pragma pack( pop )

class Image
{
public:
	Image(void);
	~Image(void);

	bool	loadTGA( TexImage* texture, const char* filename );
	bool	release( TexImage* texture );
	
protected:
	bool    loadUncompressedTGA( TexImage* texture, FILE* file );
	bool	loadCompressedTGA( TexImage* texture, FILE* file );
};

#endif