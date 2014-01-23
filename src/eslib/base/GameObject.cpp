#include "eslib/base/Component.h"
#include "eslib/base/GameObject.h"


NS_ESLIB_BEGIN

int GameObject::sAutoIDLast = 1;

GameObject::GameObject()
    :BaseObject()
{
    m_id = sAutoIDLast;
    sAutoIDLast++;
}

GameObject::~GameObject()
{
    
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
        Component* comp = NULL;
        //Component* comp = new Component(*(iter->second)); //TODO: use a component factory to copy concreate component
        Component* old = setComponent(comp);
        if(old!=NULL)
        {
            delete old;
        }
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
        Component* comp = NULL;
        //Component* comp = new Component(*(iter->second)); //TODO: use a component factory to copy concreate component
        Component* old = setComponent(comp);
        if(old!=NULL)
        {
            delete old;
        }
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

Component* GameObject::setComponent(Component* newComp)
{
    if(newComp==NULL)
    {
        return NULL;
    }
    
    CompIDType family = newComp->getFamilyID();
    Component* oldComp = m_components[family];
    m_components[family] = newComp;
    return oldComp;
}

void GameObject::clearComponents()
{
    CompTable::iterator iter;
    for(iter=m_components.begin(); iter!=m_components.end(); ++iter)
    {
        delete iter->second;
    }
    m_components.clear();
}


NS_ESLIB_END
