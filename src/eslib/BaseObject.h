#ifndef ESL_BASE_OBJECT_H
#define ESL_BASE_OBJECT_H

#include "common.h"
#include "sharedPtr.h"

NS_ESLIB_BEGIN

//! Base class of most objects of the FirstLight Engine.

ESL_FORWARD_PTR(BaseObject)

class BaseObject
{
public:
	BaseObject();
	virtual ~BaseObject();

	void grab() const;

	bool drop() const;

	s32 getRefCount() const;

	void setName(const stringc& name);
	
	const stringc& getName() const;

protected:
	virtual void onDelete();
	
	stringc m_name;	

private:
	mutable s32 m_refCount;	
};

NS_ESLIB_END

#endif //ESL_BASE_OBJECT_H