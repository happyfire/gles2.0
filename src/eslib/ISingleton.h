#ifndef ESL_I_SINGLETON_H
#define ESL_I_SINGLETON_H

#include "common.h"

NS_ESLIB_BEGIN

template <typename T> class ISingleton
{	
public:		
	virtual ~ISingleton()
	{  
		ESL_ASSERT( ms_singleton!=0 );  
		ms_singleton = 0;  
	}

	static void newInstance()
	{
		new T();
	}

	static void deleteInstance()
	{
		if(ms_singleton!=0)
		{
			delete ms_singleton;
		}
	}

	static T& getInstance()
	{ 
		if(ms_singleton==0){
			newInstance();
		}

		ESL_ASSERT( ms_singleton!=0 );  
		return ( *ms_singleton );  
	}

	static T* getInstancePtr()
	{  
		if(ms_singleton==0){
			newInstance();
		}

		ESL_ASSERT( ms_singleton!=0 );
		return ( ms_singleton );  
	}

protected:
	ISingleton()
	{
		ESL_ASSERT(ms_singleton==0);
#if defined( _MSC_VER ) && _MSC_VER < 1200	 		
		u64 offset = (u64)(T*)1 - (u64)(ISingleton <T>*)(T*)1;	//using u64 to avoid warning 4311
		ms_singleton = (T*)((u64)this + offset);
#else
		ms_singleton = static_cast< T* >( this );
#endif		
	}

private:
	static T* ms_singleton;
};

template <typename T> T* ISingleton <T>::ms_singleton = 0;

NS_ESLIB_END

#endif //ESL_I_SINGLETON_H
