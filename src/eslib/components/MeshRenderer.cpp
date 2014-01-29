#include "eslib/Mesh.h"
#include "eslib/components/MeshRenderer.h"

NS_ESLIB_BEGIN

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

static CompIDType sFamilyID = "MeshRenderer";
static CompIDType sCompID = "MeshRenderer";

const CompIDType& MeshRenderer::getFamilyID() const
{
    return sFamilyID;
}

const CompIDType& MeshRenderer::getComponentID() const
{
    return sCompID;
}


void MeshRenderer::update()
{
    
}

void MeshRenderer::setMesh(MeshPtr mesh)
{
    m_mesh = mesh;
}

MeshPtr MeshRenderer::getMesh()
{
    return m_mesh;
}

void MeshRenderer::render()
{
    m_mesh->render();
}


NS_ESLIB_END