#include "Image.h"
#include <stdlib.h>

Image::Image(void)
{
}

Image::~Image(void)
{
}


#define TRACE printf
//-----------------------------------------------------------------------
// ������    : Image::loadTGA
// ˵��      : ����TGAͼƬ
// ����      : BOOL 
// ����      : TexImage* texture
// ����      : LPCSTR filename 
// ����      : Teng
// ����ʱ��  : 2010-4-14 15:35:32
// ����޸�  : 2010-4-14
//-----------------------------------------------------------------------
bool Image::loadTGA( TexImage* texture, const char* filename )
{
	if ( filename == NULL )
		return false;
		
	Header uTGAcompare = { 0,0,2,0,0,0,0,0};		//2Ϊ��ѹ��RGB��ʽ		3  -  δѹ���ģ��ڰ�ͼ��
	Header cTGAcompare = { 0,0,10,0,0,0,0,0};		//10Ϊѹ��RGB��ʽ

	TGAHeader header;
	FILE* file = fopen( filename, "rb" );
	if ( !file ){
		TRACE("Openf file %s failed!\n", filename );
		return false;
	}
	
	if ( fread( &header, 1, sizeof(TGAHeader), file ) != sizeof( TGAHeader ) ){		//��ȡTGA����ͷ�ṹ��
		if ( file )
			fclose( file );
		TRACE("Read data failed\n");
		return false;
	}
	
	texture->width = header.width;
	texture->height = header.height;
	texture->bpp = header.bpp;

	if ( header.bpp == 32 )
		texture->imageType = GL_RGBA;
	else if ( header.bpp = 24 )
		texture->imageType = GL_RGB;
	else{
		TRACE("Image type error!\n");
		return false;
	}
		

	if ( memcmp( &uTGAcompare, &header.head, sizeof(header.head) )== 0 ){			//δѹ��TGA
		texture->bCompressed = false;
		if ( !loadUncompressedTGA( texture, file ) ){
			TRACE("Load uncompressed TGA failed!\n");
			return false;
		}
	}else if ( memcmp( &cTGAcompare, &header.head ,sizeof(header.head) ) == 0 ){	//ѹ��TGA
		texture->bCompressed = 1;
		if ( !loadCompressedTGA( texture, file ) ){
			TRACE("Load compressed TGA failed!\n");
			return false;
		}
	}else{
		TRACE("Error TGA type!\n");
		return false;
	}

	return true;
}

void flipImage(GLubyte* data, int width, int height, int bytesPerPixel)
{
	const int lineWidth = width * bytesPerPixel;

	GLubyte* tempLine = new GLubyte[lineWidth];
	GLubyte* bottomLine = data + (height-1)*lineWidth;

	for(int y=0; y<height/2; ++y)
	{		
		memcpy(tempLine, bottomLine, lineWidth);
		memcpy(bottomLine, data, lineWidth);
		memcpy(data, tempLine, lineWidth);

		data += lineWidth;
		bottomLine -= lineWidth;
	}

	delete tempLine;
}

//-----------------------------------------------------------------------
// ������    : Image::loadUncompressedTGA
// ˵��      : ����δѹ��TGA����
// ����      : BOOL 
// ����      : TexImage* texture
// ����      : FILE* file		��ǰfileָ�룬ָ��TGAͼ���һ�����ص�ַ
// ����      : Teng
// ����ʱ��  : 2010-4-14 14:39:22
// ����޸�  : 2010-4-14
//-----------------------------------------------------------------------
bool Image::loadUncompressedTGA( TexImage* texture, FILE* file )
{
	//ASSERT( file != NULL && texture!=NULL );

	GLuint bytePerPixel = texture->bpp/8;
	GLuint imgSize = texture->width*texture->height*bytePerPixel;				//ͼ�����ֽ���
	texture->imageData = new GLubyte[ imgSize ];

	if ( fread( texture->imageData, 1, imgSize, file ) != imgSize  )
	{
		printf("Read texture imagedata failed!\n");
		return false;
	}

	//TGA��������OpenGL�ĸ�ʽ,Ҫ��BGRת����ΪRGB
	// Go through all of the pixels and swap the B and R values since TGA
	// files are stored as BGR instead of RGB (or use GL_BGR_EXT verses GL_RGB)
	for( int i = 0; i < (int)imgSize; i+=bytePerPixel ){
		/*GLushort temp = texture->imageData[i];
		texture->imageData[i] = texture->imageData[i+2];
		texture->imageData[i+2] = temp;*/
		texture->imageData[i] ^= texture->imageData[i+2] ^= texture->imageData[i] ^= texture->imageData[ i+2 ];		//λ��������ٶ�,����B,R����
	}

	flipImage(texture->imageData, texture->width, texture->height, bytePerPixel);

	fclose( file );
	return true;
}

//-----------------------------------------------------------------------
// ������    : Image::loadCompressedTGA
// ˵��      : ����ѹ��TGA����
// ����      : BOOL 
// ����      : TexImage* texture
// ����      : FILE* file 
// ����      : Teng
// ����ʱ��  : 2010-4-14 14:38:55
// ����޸�  : 2010-4-14
//-----------------------------------------------------------------------
bool Image::loadCompressedTGA( TexImage* texture, FILE* file )
{
	//ASSERT( file != NULL && texture!=NULL );
	
	GLuint bytePerPixel = texture->bpp/8;
	GLuint imgSize = texture->width*texture->height*bytePerPixel;
	texture->imageData = new GLubyte[ imgSize ];

	GLuint pixelcount = texture->width * texture->height;
	GLuint currentPixel = 0;		//��ǰ���ڶ�ȡ������
	GLuint currentByte = 0;			//��ǰ������ͼ����д�������
	GLubyte *colorbuffer = (GLubyte *)malloc( bytePerPixel );	// һ�����صĴ洢�ռ�s

	do
	{
		GLubyte chunkHeader  = 0;		//�洢ID��ֵ�ı���
		if ( !fread( &chunkHeader,1, sizeof( GLubyte ), file ) ){
			return false;
		}
		if ( chunkHeader < 128 )			//RAW��
		{
			chunkHeader++;				// ����ֵ��1�Ի�ȡRAW���ص�����

			for( int i = 0; i < chunkHeader; i++ ){
				if ( fread( colorbuffer, 1, bytePerPixel, file ) !=  bytePerPixel ){
					printf("Read pixel failed!\n");
					return false;
				}
				texture->imageData[currentByte] = colorbuffer[ 2 ];
				texture->imageData[currentByte+1] = colorbuffer[1];
				texture->imageData[currentByte+2] = colorbuffer[0];
				if ( bytePerPixel == 4 )
					texture->imageData[ currentByte+3] = colorbuffer[3];

				currentPixel++;
				currentByte += bytePerPixel;
			}
		}
		 //��һ�δ�������RLE�εġ��顱ͷ���������ǽ�chunkheader��ȥ127���õ���ȡ��һ����ɫ�ظ��Ĵ����� 
		else		
		{
			chunkHeader -= 127;			//��ȥ127���ID bit ��rid	��ʼѭ���������Ƕ�ζ����ڴ��е����أ�����RLEͷ�е�ֵ�涨��

			if ( fread( colorbuffer, 1, bytePerPixel, file ) !=  bytePerPixel ){
				printf("Read pixel failed!\n");
				return false;
			}
			
			for( int i = 0; i < chunkHeader; i++ ){
				texture->imageData[ currentByte ] = colorbuffer[ 2 ];				// ������R���ֽ�
				texture->imageData[ currentByte +1 ] = colorbuffer[ 1 ];			// ������G���ֽ�
				texture->imageData[ currentByte + 2 ] = colorbuffer[ 0 ];			// ������B���ֽ�
				if ( bytePerPixel == 4 )
					texture->imageData[ currentByte+3 ] = colorbuffer[ 3 ];			// ������A���ֽ�

				currentPixel++;
				currentByte += bytePerPixel;
			}
		}
	}while( currentPixel < pixelcount );

	free( colorbuffer );
	fclose( file );

	flipImage(texture->imageData, texture->width, texture->height, bytePerPixel);

	return true;
}


//-----------------------------------------------------------------------
// ������    : Image::release
// ˵��      : �ͷ���Դ
// ����      : BOOL 
// ����      : TexImage* texture 
// ����      : Teng
// ����ʱ��  : 2010-5-25 17:42:59
// ����޸�  : 2010-5-25
//-----------------------------------------------------------------------
bool Image::release( TexImage* texture )
{
	if ( !texture )
		return false;
	
	if ( texture->imageData )
		delete[] texture->imageData;
	
	return true;
}
