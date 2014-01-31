#include "eslib/base/Component.h"
#include "eslib/base/GameObject.h"
#include "eslib/components/Transform.h"
#include "eslib/components/IRenderer.h"


NS_ESLIB_BEGIN

int GameObject::sAutoIDLast = 1;

GameObject::GameObject()
    :BaseObject()
	,m_transform(NULL)
	,m_renderer(NULL)
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
    return m_components[familyID];
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
}

Transform* GameObject::getTransform()
{
	return m_transform;
}

void GameObject::render()
{
	if(m_renderer!=NULL)
	{
		m_renderer->setTransform(m_transform->getMVPMatrix());
		m_renderer->render();
	}
}


NS_ESLIB_END
