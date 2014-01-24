#ifndef ESL_BASE_COMPONENT_H
#define ESL_BASE_COMPONENT_H

#include "eslib/common.h"
#include "eslib/SharedPtr.h"

NS_ESLIB_BEGIN

ESL_FORWARD_PTR(GameObject)

typedef stringc CompIDType;

class Component
{
public:
    Component();
	virtual ~Component();
    
    Component(const Component& rhs);
    Component& operator=(const Component& rhs);
    
    virtual Component* clone() const = 0;
    
    virtual const CompIDType& getFamilyID() const = 0;
    
	virtual const CompIDType& getComponentID() const = 0;
	
	virtual void update();
    
    void setOwnerObject(GameObjectPtr obj);
    GameObjectPtr getOwnerObject();
    
private:
    GameObjectPtr m_ownerObj;
};


NS_ESLIB_END

#endif //ESL_BASE_COMPONENT_H

