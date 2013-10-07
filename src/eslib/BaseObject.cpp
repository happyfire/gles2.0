#include "BaseObject.h"

NS_ESLIB_BEGIN

BaseObject::BaseObject():m_refCount(0),m_name("_unnamed_")
{
}

BaseObject::~BaseObject()
{
}

void BaseObject::grab() const
{
	++m_refCount; 
}

bool BaseObject::drop() const
{
	ESL_DEBUG_BREAK_IF(m_refCount<=0);

	--m_refCount;
	if(m_refCount==0)
	{
		const_cast<BaseObject*>(this)->onDelete();
		delete this;
		return true;
	}

	return false;
}

s32 BaseObject::getRefCount() const
{
	return m_refCount;
}

void BaseObject::onDelete() 
{
}

void BaseObject::setName(const stringc& name)
{
	m_name = name;
}

const stringc& BaseObject::getName() const
{
	return m_name;
}

NS_ESLIB_END