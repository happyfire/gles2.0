#include "eslib/base/Component.h"
#include "eslib/base/GameObject.h"
#include "eslib/components/Transform.h"
#include "eslib/components/IRenderer.h"
#include "eslib/components/Camera.h"

NS_ESLIB_BEGIN

int GameObject::sAutoIDLast = 1;

GameObject::GameObject()
    :BaseObject()
	,m_transform(NULL)
	,m_renderer(NULL)
    ,m_camera(NULL)
{
    m_id = sAutoIDLast;
    sAutoIDLast++;

	addComponent(new Transform());
}

GameObject::~GameObject()
{
    clearComponents();
}

GameObject::GameObject(const GameObject& rhs)
    :BaseObject()
{
    m_id = sAutoIDLast;
    sAutoIDLast++;
    
    CompTable components = rhs.m_components;
    
    CompTable::iterator iter;
    for(iter=components.begin(); iter!=components.end(); ++iter)
    {
        Component* comp = iter->second->clone();
        addComponent(comp);
    }
}

GameObject& GameObject::operator=(const GameObject& rhs)
{
    if(&rhs==this)
    {
        return *this;
    }
    
    CompTable components = rhs.m_components;
    
    CompTable::iterator iter;
    for(iter=components.begin(); iter!=components.end(); ++iter)
    {
        Component* comp = iter->second->clone();
        addComponent(comp);
    }
    
    return *this;
}

int GameObject::getID() const
{
    return m_id;
}

Component* GameObject::getComponent(const CompIDType& familyID)
{
    CompTable::iterator iter = m_components.find(familyID);
    if (iter!=m_components.end()) {
        return iter->second;
    }
    else{
        return NULL;
    }
}

void GameObject::addComponent(Component* newComp)
{
    if(newComp==NULL)
    {
        return ;
    }
    
    CompIDType family = newComp->getFamilyID();
    Component* oldComp = m_components[family];
    m_components[family] = newComp;
	delete oldComp;

	newComp->setOwnerObject(this);

	if(family=="Transform"){
		m_transform = static_cast<Transform*>(newComp);
	}
	else if(family=="IRenderer"){
		m_renderer = static_cast<IRenderer*>(newComp);
	}
    else if(family=="Camera"){
        m_camera = static_cast<Camera*>(newComp);
    }
}

void GameObject::clearComponents()
{
    CompTable::iterator iter;
    for(iter=m_components.begin(); iter!=m_components.end(); ++iter)
    {
        delete iter->second;
    }
    m_components.clear();

	m_transform = NULL;
	m_renderer = NULL;
    m_camera = NULL;
}

void GameObject::broadcastMessage(Component *sender, int messageId, void *payload)
{
    CompTable::iterator iter;
    for(iter=m_components.begin(); iter!=m_components.end(); ++iter)
    {
        Component* receiver = iter->second;
        if(receiver!=sender)
        {
            receiver->receiveMessage(sender, messageId, payload);
        }
    }
}

void GameObject::sendMessage(Component *sender, const CompIDType& receiverCompFamilyId, int messageId, void *payload)
{
    Component* receiver = getComponent(receiverCompFamilyId);
    if (receiver!=NULL)
    {
        receiver->receiveMessage(sender, messageId, payload);
    }
}

Transform* GameObject::getTransform()
{
	return m_transform;
}

Camera* GameObject::getCamera()
{
    return m_camera;
}

void GameObject::render()
{
	if(m_renderer!=NULL)
	{
		m_renderer->setTransform(m_transform->getMVPMatrix());
		m_renderer->render();
	}
}

const GameObjectPtr& GameObject::getParent() const
{
    return m_parent;
}

void GameObject::setParent(GameObject* obj)
{
    m_parent = obj;
}

GameObjectList& GameObject::getChildren()
{
    return m_children;
}

void GameObject::addChild(GameObject* obj)
{
    obj->removeFromParent();
    obj->setParent(this);
    m_children.push_back(obj);
}

void GameObject::removeChild(GameObject* obj)
{
    obj->setParent(NULL);
    m_children.remove(obj);
}

void GameObject::removeFromParent()
{
    if (m_parent.isValid()) {
        m_parent->removeChild(this);
        m_parent = NULL;
    }
}

GameObject* GameObject::getChildByTag(int tag)
{
    GameObjectIter iter = m_children.begin();
    
    for (GameObjectIter iterEnd=m_children.end(); iter!=iterEnd; ++iter)
    {
        GameObjectPtr& obj = *iter;
        
        if(obj->m_tag==tag)
            return obj;
    }
    
    return NULL;
}


NS_ESLIB_END
