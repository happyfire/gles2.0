#ifndef ESL_COMPONENTS_MESHRENDERER_H
#define ESL_COMPONENTS_MESHRENDERER_H

#include "eslib/common.h"
#include "eslib/SharedPtr.h"
#include "eslib/base/Component.h"

NS_ESLIB_BEGIN

ESL_FORWARD_PTR(Mesh)


class MeshRenderer: public Component
{
public:
    MeshRenderer();
	virtual ~MeshRenderer();
    
    MeshRenderer(const MeshRenderer& rhs);
    MeshRenderer& operator=(const MeshRenderer& rhs);
    
    virtual Component* clone() const;
    
    virtual const CompIDType& getFamilyID() const;
    
	virtual const CompIDType& getComponentID() const;
	
	virtual void update();
    
public:
    void setMesh(MeshPtr mesh);
    MeshPtr getMesh();
    void render();
    
private:
    MeshPtr m_mesh;
};


NS_ESLIB_END

#endif //ESL_COMPONENTS_MESHRENDERER_H

