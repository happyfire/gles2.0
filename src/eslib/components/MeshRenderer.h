#ifndef ESL_COMPONENTS_MESHRENDERER_H
#define ESL_COMPONENTS_MESHRENDERER_H

#include "eslib/common.h"
#include "eslib/SharedPtr.h"
#include "eslib/components/IRenderer.h"
#include "eslib/math/Matrix4.h"
#include "eslib/scene/AABBox.h"

NS_ESLIB_BEGIN

ESL_FORWARD_PTR(Mesh)


class MeshRenderer: public IRenderer
{
public:
    MeshRenderer();
	virtual ~MeshRenderer();
    
    MeshRenderer(const MeshRenderer& rhs);
    MeshRenderer& operator=(const MeshRenderer& rhs);
    
    virtual Component* clone() const;
    
	virtual const CompIDType& getComponentID() const;
	
	virtual void update(float dt);
    
public:
	virtual void setTransform(const Matrix4 &transform);
    virtual void render();
    virtual const AABBox& getTransformedAABB();

public:
	void setMesh(MeshPtr mesh);
	MeshPtr getMesh();

private:
    void initAABBMesh();
    
private:
    MeshPtr m_mesh;
    
    AABBox m_aabb;
    
    MeshPtr m_aabbMesh;
};


NS_ESLIB_END

#endif //ESL_COMPONENTS_MESHRENDERER_H

