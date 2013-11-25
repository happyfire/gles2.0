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
// 函数名    : Image::loadTGA
// 说明      : 加载TGA图片
// 返回      : BOOL 
// 参数      : TexImage* texture
// 参数      : LPCSTR filename 
// 作者      : Teng
// 创建时间  : 2010-4-14 15:35:32
// 最后修改  : 2010-4-14
//-----------------------------------------------------------------------
bool Image::loadTGA( TexImage* texture, const char* filename )
{
	if ( filename == NULL )
		return false;
		
	Header uTGAcompare = { 0,0,2,0,0,0,0,0};		//2为非压缩RGB格式		3  -  未压缩的，黑白图像
	Header cTGAcompare = { 0,0,10,0,0,0,0,0};		//10为压缩RGB格式

	TGAHeader header;
	FILE* file = fopen( filename, "rb" );
	if ( !file ){
		TRACE("Openf file %s failed!\n", filename );
		return false;
	}
	
	if ( fread( &header, 1, sizeof(TGAHeader), file ) != sizeof( TGAHeader ) ){		//读取TGA整个头结构体
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
		

	if ( memcmp( &uTGAcompare, &header.head, sizeof(header.head) )== 0 ){			//未压缩TGA
		texture->bCompressed = false;
		if ( !loadUncompressedTGA( texture, file ) ){
			TRACE("Load uncompressed TGA failed!\n");
			return false;
		}
	}else if ( memcmp( &cTGAcompare, &header.head ,sizeof(header.head) ) == 0 ){	//压缩TGA
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
// 函数名    : Image::loadUncompressedTGA
// 说明      : 加载未压缩TGA纹理
// 返回      : BOOL 
// 参数      : TexImage* texture
// 参数      : FILE* file		当前file指针，指向TGA图像第一个像素地址
// 作者      : Teng
// 创建时间  : 2010-4-14 14:39:22
// 最后修改  : 2010-4-14
//-----------------------------------------------------------------------
bool Image::loadUncompressedTGA( TexImage* texture, FILE* file )
{
	//ASSERT( file != NULL && texture!=NULL );

	GLuint bytePerPixel = texture->bpp/8;
	GLuint imgSize = texture->width*texture->height*bytePerPixel;				//图像总字节数
	texture->imageData = new GLubyte[ imgSize ];

	if ( fread( texture->imageData, 1, imgSize, file ) != imgSize  )
	{
		printf("Read texture imagedata failed!\n");
		return false;
	}

	//TGA采用了逆OpenGL的格式,要将BGR转换成为RGB
	// Go through all of the pixels and swap the B and R values since TGA
	// files are stored as BGR instead of RGB (or use GL_BGR_EXT verses GL_RGB)
	for( int i = 0; i < (int)imgSize; i+=bytePerPixel ){
		/*GLushort temp = texture->imageData[i];
		texture->imageData[i] = texture->imageData[i+2];
		texture->imageData[i+2] = temp;*/
		texture->imageData[i] ^= texture->imageData[i+2] ^= texture->imageData[i] ^= texture->imageData[ i+2 ];		//位操作提高速度,更换B,R分量
	}

	flipImage(texture->imageData, texture->width, texture->height, bytePerPixel);

	fclose( file );
	return true;
}

//-----------------------------------------------------------------------
// 函数名    : Image::loadCompressedTGA
// 说明      : 加载压缩TGA纹理
// 返回      : BOOL 
// 参数      : TexImage* texture
// 参数      : FILE* file 
// 作者      : Teng
// 创建时间  : 2010-4-14 14:38:55
// 最后修改  : 2010-4-14
//-----------------------------------------------------------------------
bool Image::loadCompressedTGA( TexImage* texture, FILE* file )
{
	//ASSERT( file != NULL && texture!=NULL );
	
	GLuint bytePerPixel = texture->bpp/8;
	GLuint imgSize = texture->width*texture->height*bytePerPixel;
	texture->imageData = new GLubyte[ imgSize ];

	GLuint pixelcount = texture->width * texture->height;
	GLuint currentPixel = 0;		//当前正在读取的像素
	GLuint currentByte = 0;			//当前正在向图像中写入的像素
	GLubyte *colorbuffer = (GLubyte *)malloc( bytePerPixel );	// 一个像素的存储空间s

	do
	{
		GLubyte chunkHeader  = 0;		//存储ID块值的变量
		if ( !fread( &chunkHeader,1, sizeof( GLubyte ), file ) ){
			return false;
		}
		if ( chunkHeader < 128 )			//RAW块
		{
			chunkHeader++;				// 变量值加1以获取RAW像素的总数

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
		 //下一段处理描述RLE段的“块”头。首先我们将chunkheader减去127来得到获取下一个颜色重复的次数。 
		else		
		{
			chunkHeader -= 127;			//减去127获得ID bit 的rid	开始循环拷贝我们多次读到内存中的像素，这由RLE头中的值规定。

			if ( fread( colorbuffer, 1, bytePerPixel, file ) !=  bytePerPixel ){
				printf("Read pixel failed!\n");
				return false;
			}
			
			for( int i = 0; i < chunkHeader; i++ ){
				texture->imageData[ currentByte ] = colorbuffer[ 2 ];				// 拷贝“R”字节
				texture->imageData[ currentByte +1 ] = colorbuffer[ 1 ];			// 拷贝“G”字节
				texture->imageData[ currentByte + 2 ] = colorbuffer[ 0 ];			// 拷贝“B”字节
				if ( bytePerPixel == 4 )
					texture->imageData[ currentByte+3 ] = colorbuffer[ 3 ];			// 拷贝“A”字节

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
// 函数名    : Image::release
// 说明      : 释放资源
// 返回      : BOOL 
// 参数      : TexImage* texture 
// 作者      : Teng
// 创建时间  : 2010-5-25 17:42:59
// 最后修改  : 2010-5-25
//-----------------------------------------------------------------------
bool Image::release( TexImage* texture )
{
	if ( !texture )
		return false;
	
	if ( texture->imageData )
		delete[] texture->imageData;
	
	return true;
}
