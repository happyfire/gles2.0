#include "MD2MeshLoader.h"
#include "esUtil/esUtil.h"
#include "eslib/Mesh.h"
#include "eslib/Geometry.h"
#include "eslib/Material.h"

USING_NS_ESLIB

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
	unsigned char v[3];
    unsigned char normalIndex;
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
//		if(m_pVerts)  
//			delete [] m_pVerts;  
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

struct MD2Model
{
    MD2Header m_header;
    MD2Skin *m_skins;
    MD2TexCoord *m_texCoords;
    MD2Tri *m_triangles;
    MD2Frame *m_frames;
};

bool loadMD2Model(const char* md2File, MD2Model &mdl)
{
    FILE* file = esOpenFile(md2File);
	if(file==NULL)
	{
        ESL_DBG("md2","cannot open md2 file:%s",md2File);
		return false;
	}
    
	fread(&mdl.m_header, 1, sizeof(MD2Header), file);
    
    if(mdl.m_header.m_magic!=844121161 || mdl.m_header.m_version!=8)
    {
        fclose(file);
        ESL_DBG("md2", "error:bad version or identifier");
        return false;
    }
    
    mdl.m_skins = new MD2Skin[mdl.m_header.m_numSkins];
    mdl.m_texCoords = new MD2TexCoord[mdl.m_header.m_numTexCoords];
    mdl.m_triangles = new MD2Tri[mdl.m_header.m_numTexCoords];
    mdl.m_frames = new MD2Frame[mdl.m_header.m_numFrames];
    
    fseek(file, mdl.m_header.m_offsetSkins, SEEK_SET);
    fread(mdl.m_skins, sizeof(MD2Skin), mdl.m_header.m_numSkins, file);
    
    fseek(file, mdl.m_header.m_offsetTexCoords, SEEK_SET);
    fread(mdl.m_texCoords, sizeof(MD2TexCoord), mdl.m_header.m_numTexCoords, file);
    
    fseek(file, mdl.m_header.m_offsetTriangles, SEEK_SET);
    fread(mdl.m_triangles, sizeof(MD2Tri), mdl.m_header.m_numTriangles, file);
    
    fseek(file, mdl.m_header.m_offsetFrames, SEEK_SET);
    for(int i=0; i<mdl.m_header.m_numFrames; i++)
    {
        mdl.m_frames[i].m_pVerts = new MD2Vert[mdl.m_header.m_numVertices];
        
        fread(mdl.m_frames[i].m_scale, 3*sizeof(float), 1, file);
        fread(mdl.m_frames[i].m_translate, 3*sizeof(float), 1, file);
        fread(mdl.m_frames[i].m_name, sizeof(char), 16, file);
        fread(mdl.m_frames[i].m_pVerts, sizeof(MD2Vert), mdl.m_header.m_numVertices, file);
    }
    
    fclose(file);
    
    return true;
}

void freeMD2Model(MD2Model &mdl)
{
    if(mdl.m_skins)
    {
        ESL_SAFE_DEL_ARRAY(mdl.m_skins);
    }
    
    if(mdl.m_texCoords)
    {
        ESL_SAFE_DEL_ARRAY(mdl.m_texCoords);
    }
    
    if(mdl.m_triangles)
    {
        ESL_SAFE_DEL_ARRAY(mdl.m_triangles);
    }
    
    if(mdl.m_frames)
    {
        for(int i=0; i<mdl.m_header.m_numFrames; i++)
        {
            ESL_SAFE_DEL_ARRAY(mdl.m_frames[i].m_pVerts);
        }
        
        ESL_SAFE_DEL_ARRAY(mdl.m_frames);
    }
}

MD2MeshLoader::MD2MeshLoader()
{

}

			  
MeshPtr MD2MeshLoader::load(const char* md2File, const char* textureFile)
{
    MD2Model mdl;
    if(loadMD2Model(md2File, mdl))
    {
        MeshPtr mesh = new Mesh();
    
        //create mesh (only load from the first frame,for now morph animation is not supported)
        int triNum = mdl.m_header.m_numTriangles;
    
        GeometryPtr geometry = mesh->createEmpty(MVF_POS_3F|MVF_TCOORD_2F, mdl.m_header.m_numVertices, triNum*3, true, true);
        
        int vertexNum = mdl.m_header.m_numVertices;
    
        float* vertexPos = new float[vertexNum*3];
        for (int i=0; i<vertexNum; i+=3)
        {
            MD2Frame* frame = &mdl.m_frames[0];
            vertexPos[i*3] = (frame->m_pVerts[i].v[0] * frame->m_scale[0]) + frame->m_translate[0];
            vertexPos[i*3+1] = (frame->m_pVerts[i].v[1] * frame->m_scale[1]) + frame->m_translate[1];
            vertexPos[i*3+2] = (frame->m_pVerts[i].v[2] * frame->m_scale[2]) + frame->m_translate[2];
        }
        
        geometry->appendVertexData(0, vertexPos, sizeof(vertexPos));
        
        GLfloat* uvs = new GLfloat[vertexNum*2];
        GLushort* indices = new GLushort[triNum*3];
        
        for(int i=0; i<triNum; i++)
        {
            MD2Tri* tri = &mdl.m_triangles[i];
            for(int j=0; j<3; j++)
            {
                int vertexIndex = tri->m_vertIndices[j];
                indices[i*3+j] = vertexIndex;
                uvs[vertexIndex*2] = (GLfloat)mdl.m_texCoords[tri->m_texIndices[j]].u / mdl.m_header.m_skinWidth;
                uvs[vertexIndex*2+1] = (GLfloat)mdl.m_texCoords[tri->m_texIndices[j]].v / mdl.m_header.m_skinHeight;
            }
        }
        
        geometry->appendVertexData(1, uvs, sizeof(uvs));
        
        geometry->appendIndexData(indices, sizeof(indices));
        
        //create material
        MaterialPtr material = new Material();
        material->setShaderProgramFromFile("media/texture.vs","media/texture.fs").setTextureProperty("u_map",textureFile);
        material->updateShaderProperites();
        
        mesh->setMaterial(material);


        
        freeMD2Model(mdl);
        
        return mesh;
    }
    else
    {
        MeshPtr ptr;
        return ptr;
    }
}


