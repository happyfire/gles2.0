#ifndef ESL_BASE_GAMEOBJECT_H
#define ESL_BASE_GAMEOBJECT_H

#include "eslib/BaseObject.h"
#include "eslib/sharedPtr.h"
#include "eslib/base/Component.h"

NS_ESLIB_BEGIN

ESL_FORWARD_PTR(GameObject)

class GameObject: public BaseObject
{
public:
	GameObject();
	virtual ~GameObject();
    
    GameObject(const GameObject& rhs);
    GameObject& operator=(const GameObject& rhs);
    
    int getID() const;

    Component* getComponent(const CompIDType& familyID);
    
    Component* setComponent(Component* newComp);
    
    void clearComponents();
    
protected:
    int m_id;
    
    typedef std::map<const CompIDType, Component*> CompTable;
    CompTable m_components;
    
    static int sAutoIDLast;
};



NS_ESLIB_END

#endif //ESL_BASE_GAMEOBJECT_H