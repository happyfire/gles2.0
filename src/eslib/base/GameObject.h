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
class Camera;

typedef std::list<GameObjectPtr> GameObjectList;
typedef GameObjectList::iterator GameObjectIter;

enum ComponentMessage
{
    Message_TransformPositionChanged,
    Message_TransformRotationChanged,
    
    Message_CustomStart //custom message should start from it
};

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
    
    //组件间通信，通过消息
    void broadcastMessage(Component *sender, int messageId, void *payload);
    
    void sendMessage(Component *sender, const CompIDType& receiverCompFamilyId, int messageId, void *payload);

	Transform* getTransform();
    
    Camera* getCamera();

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
    Camera* m_camera;
    
    GameObjectList m_children;
    GameObjectPtr m_parent;
};



NS_ESLIB_END

#endif //ESL_BASE_GAMEOBJECT_H
