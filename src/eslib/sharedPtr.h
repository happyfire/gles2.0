#ifndef ESL_SHARED_PTR_H
#define ESL_SHARED_PTR_H

#include "common.h"

NS_ESLIB_BEGIN

//! Shared smart pointer for BaseObject and its sub classes.
template<typename T>
class SharedPtr
{
public:
	
	// construction and destruction
	SharedPtr();	
	SharedPtr(T* p);	
	SharedPtr(const SharedPtr<T>& ptr);	
	~SharedPtr();

	// assignment
	void operator=(T* p);
	void operator=(const SharedPtr<T>& ptr);
	
	// comparisons
	bool operator==(const T* p) const;
	bool operator!=(const T* p) const;

	bool operator==(const SharedPtr<T>& ptr) const;
	bool operator!=(const SharedPtr<T>& ptr) const;		
	
	// safe -> operator
	T* operator->() const;
	// safe dereference operator
	T& operator*() const;
	// safe pointer cast operator
	operator T*() const;
	// return raw pointer 
	T* get() const;
	// check if pointer is valid
	bool isValid() const;
	// release raw pointer
	void reset();
	// get raw pointer to sub class, so can use = to get a sub class share ptr
	template<typename SubClassType> SubClassType* toSubClass();	
	
private:
	T* m_p;
};

/////////////////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////////////////
// construction and destruction

template<typename T>
SharedPtr<T>::SharedPtr() : m_p(0)
{
}


template<typename T>
SharedPtr<T>::SharedPtr(T* p) : m_p(p)
{
	if (m_p!=0)
	{
		m_p->grab();
	}
}

template<typename T>
SharedPtr<T>::SharedPtr(const SharedPtr<T>& p) : m_p(p.m_p)
{
	if (m_p!=0)
	{
		m_p->grab();
	}
}


template<typename T>
SharedPtr<T>::~SharedPtr()
{
	if (m_p!=0)
	{
		m_p->drop();
		m_p=0;
	}
}

/////////////////////////////////////////////////////////////////////////////////
// assignment

template<typename T>
void SharedPtr<T>::operator=(T* p)
{
	if (m_p != p)
	{
		if(p!=0)
		{
			p->grab();
		}

		if(m_p!=0)
		{
			m_p->drop();
		}

		m_p = p;		
	}
}

template<typename T>
void SharedPtr<T>::operator=(const SharedPtr<T>& ptr)
{
	if (m_p != ptr.m_p)
	{
		if(ptr.m_p!=0)
		{
			ptr.m_p->grab();
		}

		if(m_p!=0)
		{
			m_p->drop();
		}

		m_p = ptr.m_p;		
	}
}


/////////////////////////////////////////////////////////////////////////////////
// comparisons

template<typename T>
bool SharedPtr<T>::operator==(const T* p) const
{
	return (m_p == p);
}

template<typename T>
bool SharedPtr<T>::operator!=(const T* p) const
{
	return (m_p != p);
}

template<typename T>
bool SharedPtr<T>::operator==(const SharedPtr<T>& ptr) const
{
	return (m_p == ptr.m_p);
}

template<typename T>
bool SharedPtr<T>::operator!=(const SharedPtr<T>& ptr) const
{
	return (m_p != ptr.m_p);
}


/////////////////////////////////////////////////////////////////////////////////

template<typename T>
T* SharedPtr<T>::operator->() const
{
	ESL_ASSERT(m_p!=0 && "NULL pointer access in SharedPtr::operator->()!");
	return m_p;
}

template<typename T>
T& SharedPtr<T>::operator*() const
{
	ESL_ASSERT(m_p!=0 && "NULL pointer access in SharedPtr::operator*()!");
	return *m_p;
}

template<typename T>
SharedPtr<T>::operator T*() const
{
	ESL_ASSERT(m_p!=0 && "NULL pointer access in SharedPtr::operator T*()!");
	return m_p;
}

template<typename T>
T* SharedPtr<T>::get() const
{
	ESL_ASSERT(m_p!=0 && "NULL pointer access in SharedPtr::get()!");
	return m_p;
}

template<typename T>
bool SharedPtr<T>::isValid() const
{
	return (m_p!=0);
}

template<typename T>
void SharedPtr<T>::reset()
{
	if(m_p!=0)
	{
		m_p->drop();
	}

	m_p = 0;
}

template<typename T>
template<typename SubClassType> 
SubClassType* SharedPtr<T>::toSubClass()
{		
	return static_cast<SubClassType*>(m_p);
};

/////////////////////////////////////////////////////////////////////////////////
	
NS_ESLIB_END

#endif //ESL_SHARED_PTR_H