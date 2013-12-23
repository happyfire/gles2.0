#include "esUtil/esUtil.h"
#include "eslib/Material.h"
#include "eslib/Geometry.h"
#include "eslib/ShaderProgram.h"
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
		meshAttributes.push_back(&attributeTexcoord);
        
        if(multiStream){
            streamID++;
        }
	}
	

	m_geometry->create(meshAttributes, vertexCount, indexCount, useVBO);

	return m_geometry;
}

void Mesh::setMaterial(const MaterialPtr& material)
{
	m_material = material;
}

void Mesh::setTransform(const ESMatrix &transform)
{
	ESL_ASSERT(m_material.isValid());

	m_material->getShaderProgram()->setUniformMatrix4fv("u_mvpMatrix", transform);
}

void Mesh::render()
{
	m_material->apply();

	m_geometry->render(m_material->getShaderProgram());
}

NS_ESLIB_END