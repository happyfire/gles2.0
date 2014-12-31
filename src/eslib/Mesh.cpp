#include "eslib/Material.h"
#include "eslib/Geometry.h"
#include "eslib/ShaderProgram.h"
#include "eslib/math/Matrix4.h"
#include "Mesh.h"

NS_ESLIB_BEGIN

Mesh::Mesh()
{

}

Mesh::~Mesh()
{

}

GeometryPtr Mesh::createEmpty(int vertexFlag, int vertexCount, int indexCount, bool useVBO, bool multiStream)
{
	m_geometry = new Geometry();

	std::vector<const VertexAttribute*> meshAttributes;
    
    int streamID = 0;

	VertexAttribute attributePos;
	if(esTestFlag(vertexFlag,MVF_POS_3F))
	{
		attributePos.ElementCount = 3;
        attributePos.VertexStreamID = streamID;
		attributePos.Name = "a_position";
        attributePos.Type = Type_Position;
		meshAttributes.push_back(&attributePos);
        
        if(multiStream){
            streamID++;
        }
	}
	
	VertexAttribute attributeTexcoord;
	if(esTestFlag(vertexFlag,MVF_TCOORD_2F))
	{
		attributeTexcoord.ElementCount = 2;
        attributeTexcoord.VertexStreamID = streamID;
		attributeTexcoord.Name = "a_texCoord";
        attributeTexcoord.Type = Type_UV;
		meshAttributes.push_back(&attributeTexcoord);
        
        if(multiStream){
            streamID++;
        }
	}
	

	m_geometry->create(meshAttributes, vertexCount, indexCount, useVBO);

	return m_geometry;
}

GeometryPtr Mesh::createDebugBox()
{
    m_geometry = new Geometry(GL_LINES);
    
    std::vector<const VertexAttribute*> meshAttributes;
    
    VertexAttribute attributePos;

    attributePos.ElementCount = 3;
    attributePos.VertexStreamID = 0;
    attributePos.Name = "a_position";
    attributePos.Type = Type_Custom; //debug geomotry不需要再计算aabb
    meshAttributes.push_back(&attributePos);
    
    m_geometry->create(meshAttributes, 8, 24, false);
    
    MaterialPtr material = new Material();
    material->setShaderProgramFromFile("media/aabb.vs","media/aabb.fs");
    
    MaterialProperty colorMP;
    colorMP.mName = "u_color";
    colorMP.mType = MPT_FLOAT4;
    colorMP.fVec4[0] = 1;
    colorMP.fVec4[1] = 1;
    colorMP.fVec4[2] = 1;
    colorMP.fVec4[3] = 1;
    material->setProperty("u_color", colorMP);
    
    material->updateShaderProperites();
    
    this->setMaterial(material);
    
    return m_geometry;
}

void Mesh::setMaterial(const MaterialPtr& material)
{
	m_material = material;
}

void Mesh::setTransform(const Matrix4 &transform)
{
	ESL_ASSERT(m_material.isValid());

	m_material->getShaderProgram()->setUniformMatrix4fv("u_mvpMatrix", transform.getData());
}

void Mesh::render()
{
	m_material->apply();

	m_geometry->render(m_material->getShaderProgram());
}

NS_ESLIB_END