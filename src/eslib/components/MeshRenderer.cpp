#include "eslib/Mesh.h"
#include "eslib/components/MeshRenderer.h"

NS_ESLIB_BEGIN

static CompIDType sCompID = "MeshRenderer";

MeshRenderer::MeshRenderer()
{
}

MeshRenderer::~MeshRenderer()
{
    
}

MeshRenderer::MeshRenderer(const MeshRenderer& rhs)
{
    m_mesh = rhs.m_mesh;
}

MeshRenderer& MeshRenderer::operator=(const MeshRenderer& rhs)
{
    if (&rhs==this) {
        return *this;
    }
    
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


void MeshRenderer::update()
{
    
}

void MeshRenderer::setTransform(const ESMatrix &transform)
{
	if(m_mesh.isValid())
	{
		m_mesh->setTransform(transform);
	}
}

void MeshRenderer::render()
{
    m_mesh->render();
}

void MeshRenderer::setMesh(MeshPtr mesh)
{
	m_mesh = mesh;
}

MeshPtr MeshRenderer::getMesh()
{
	return m_mesh;
}

NS_ESLIB_END