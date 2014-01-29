#include "eslib/base/GameObject.h"
#include "eslib/base/Component.h"


NS_ESLIB_BEGIN

Component::Component()
{
}

Component::~Component()
{
    
}

Component::Component(const Component& rhs)
{
    m_ownerObj = rhs.m_ownerObj;
}

Component& Component::operator=(const Component& rhs)
{
    if (&rhs==this) {
        return *this;
    }
    
    m_ownerObj = rhs.m_ownerObj;
    
    return *this;
}


void Component::update()
{
    
}

void Component::setOwnerObject(GameObjectPtr obj)
{
    m_ownerObj = obj;
}

GameObjectPtr Component::getOwnerObject()
{
    return m_ownerObj;
}


NS_ESLIB_END