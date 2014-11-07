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