#include "MD2MeshLoader.h"
#include "esUtil/esUtil.h"

using eslib::MeshPtr;
using eslib::Mesh;

struct MD2Header  
{  
	int m_magic;  
	int m_version;  
	int m_skinWidth;  
	int m_skinHeight;  
	int m_frameSize;  
	int m_numSkins;  
	int m_numVertices; //for each frame, and each frame has the same number of vertices  
	int m_numTexCoords;  
	int m_numTriangles;  
	int m_numGLCommands;  
	int m_numFrames;  
	int m_offsetSkins;  
	int m_offsetTexCoords;  
	int m_offsetTriangles;  
	int m_offsetFrames;  
	int m_offsetGlCommands;  
	int m_fileSize;  
};

struct MD2Vert  
{  
	float m_vert[3];  
}; 

struct MD2Frame  
{  
	float m_scale[3];  
	float m_translate[3];  
	char m_name[16];  
	MD2Vert * m_pVerts;
	
	MD2Frame()  
	{  
		m_pVerts = 0;  
	}  
	
	~MD2Frame()  
	{  
		if(m_pVerts)  
			delete [] m_pVerts;  
	}  
}; 

struct MD2Tri  
{  
	unsigned short m_vertIndices[3];  
	unsigned short m_texIndices[3];  
};

struct MD2Skin
{
	char m_name[64];
};

struct MD2TexCoord  
{  
	short u, v;  
};

MD2MeshLoader::MD2MeshLoader()
{

}

			  
MeshPtr MD2MeshLoader::load(const char* md2File)
{
	MeshPtr mesh = new Mesh();

	//GeometryPtr geometry = mesh->createEmpty(MVF_POS_3F|MVF_TCOORD_2F, 20, 36, true);
	//geometry->appendVertexData(0, cubeStructure, sizeof(cubeStructure));
	//geometry->appendIndexData(cubeIndices, sizeof(cubeIndices));

	FILE* file = esOpenFile(md2File);
	if(file==NULL)
	{
		return mesh;
	}

	MD2Header header;
	fread(&header, 1, sizeof(MD2Header), file);


	return mesh;
}