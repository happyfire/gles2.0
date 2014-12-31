#include "eslib/Mesh.h"
#include "eslib/Geometry.h"
#include "eslib/components/MeshRenderer.h"

NS_ESLIB_BEGIN

static CompIDType sCompID = "MeshRenderer";

MeshRenderer::MeshRenderer()
{
    initAABBMesh();
}

MeshRenderer::~MeshRenderer()
{
    
}

MeshRenderer::MeshRenderer(const MeshRenderer& rhs)
	:IRenderer(rhs)
{
    m_mesh = rhs.m_mesh;
}

MeshRenderer& MeshRenderer::operator=(const MeshRenderer& rhs)
{
    if (&rhs==this) {
        return *this;
    }

	IRenderer::operator=(rhs);
    
    m_mesh = rhs.m_mesh;
    
    return *this;
}

Component* MeshRenderer::clone() const
{
    MeshRenderer* newComp = new MeshRenderer(*this);
    return newComp;
}

const CompIDType& MeshRenderer::getComponentID() const
{
    return sCompID;
}


void MeshRenderer::update(float dt)
{
    
}

void MeshRenderer::setTransform(const Matrix4 &transform)
{
	if(m_mesh.isValid())
	{
		m_mesh->setTransform(transform);
        
        //get and transform AABB
        const GeometryPtr& geometry = m_mesh->getGeometry();
        const AABBox& aabb = geometry->getAABB();
        m_aabb = aabb;
        m_aabb.transform(transform);
        
        //update AABB mesh
        const GeometryPtr& aabb_geometry = m_aabbMesh->getGeometry();
        aabb_geometry->resetAppendVertexData(0);
        
        Vector3 edges[8];
        m_aabb.getEdges(edges);
        
        for (int i=0; i<8; i++) {
            aabb_geometry->appendVertexData(0, &edges[i].x, sizeof(float));
            aabb_geometry->appendVertexData(0, &edges[i].y, sizeof(float));
            aabb_geometry->appendVertexData(0, &edges[i].z, sizeof(float));
        }
        
        m_aabbMesh->setTransform(kMatrixIdentity);
	}
}

void MeshRenderer::render()
{
    m_mesh->render();
    
    m_aabbMesh->render();
}

const AABBox& MeshRenderer::getTransformedAABB()
{
    return m_aabb;
}

void MeshRenderer::setMesh(MeshPtr mesh)
{
	m_mesh = mesh;
}

MeshPtr MeshRenderer::getMesh()
{
	return m_mesh;
}

void MeshRenderer::initAABBMesh()
{
    m_aabbMesh = new Mesh();
    GeometryPtr aabb_geometry = m_aabbMesh->createDebugBox();
    
    GLushort boxIndices[]=
    {
        1, 5, 5, 7, 7, 3, 3, 1,
        0, 4, 4, 6, 6, 2, 2, 0,
        0, 1, 2, 3, 4, 5, 6, 7
    };
    
    aabb_geometry->appendIndexData(boxIndices, sizeof(boxIndices));
}

NS_ESLIB_END
