#ifndef ESL_BASE_GAMEOBJECT_H
#define ESL_BASE_GAMEOBJECT_H

#include "eslib/BaseObject.h"
#include "eslib/sharedPtr.h"
#include "eslib/base/Component.h"
#include <list>

NS_ESLIB_BEGIN

ESL_FORWARD_PTR(GameObject)

class Transform;
class IRenderer;

typedef std::list<GameObjectPtr> GameObjectList;
typedef GameObjectList::iterator GameObjectIter;

class GameObject: public BaseObject
{
public:
	GameObject();
	virtual ~GameObject();
    
    GameObject(const GameObject& rhs);
    GameObject& operator=(const GameObject& rhs);
    
    int getID() const;

    Component* getComponent(const CompIDType& familyID);
    
	///add a new component to game object,
	///if it has already haven a component has the same interface, the old componenet will be removed. 
    void addComponent(Component* newComp);
    
    void clearComponents();

	Transform* getTransform();

	void render();
    
    const GameObjectPtr& getParent() const;
    
    GameObjectList& getChildren();
    
    void addChild(GameObject* obj);
    
    void removeChild(GameObject* obj);
    
    void removeFromParent();
    
protected:
    void setParent(GameObject* obj);
    
protected:
    int m_id;
    
    typedef std::map<const CompIDType, Component*> CompTable;
    CompTable m_components;
    
    static int sAutoIDLast;

	Transform* m_transform;
	IRenderer* m_renderer;
    
    GameObjectList m_children;
    GameObjectPtr m_parent;
};



NS_ESLIB_END

#endif //ESL_BASE_GAMEOBJECT_H
