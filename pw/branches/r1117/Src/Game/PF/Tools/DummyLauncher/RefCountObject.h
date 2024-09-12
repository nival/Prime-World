#pragma once

// сервисный класс - счетчик ссылок
class RefCountObject
{
public:
	RefCountObject() : m_refs(0)
	{
	}
	virtual ~RefCountObject()
	{
	}
	long IncRef()
	{
		return InterlockedIncrement( &m_refs );
	}

	long DecRef()
	{
		long refs = InterlockedDecrement( &m_refs );
		if ( refs < 1 )
			delete this;
		return refs;
	}

	virtual RefCountObject* CastToRootType() { return static_cast<RefCountObject*>(this); }
	virtual const RefCountObject* CastToRootType() const { return static_cast<const RefCountObject*>(this); }
private:
	volatile long m_refs;
};

// сервисный класс для управления объектом со счетчиком ссылок
template<typename T>
class RefCountPtr
{
public:
	RefCountPtr() : m_ptr(NULL)
	{
	}

	RefCountPtr( T* p ) : m_ptr(p)
	{
		if( m_ptr )
			m_ptr->IncRef();
	}

	RefCountPtr( const RefCountPtr<T>& rhs ) : m_ptr(rhs.m_ptr)
	{
		if( m_ptr )
			m_ptr->IncRef();
	}

	~RefCountPtr()
	{
		if( m_ptr )
			m_ptr->DecRef();
	}

	T* operator ->()
	{
		return m_ptr;
	}

	const T* operator ->() const
	{
		return m_ptr;
	}

	operator T* ()
	{ 
		return m_ptr; 
	}

	operator const T* () const    
	{ 
		return m_ptr; 
	}

	RefCountPtr& operator =( const RefCountPtr<T>& rhs )
	{
		if( this != &rhs )
		{
			if( m_ptr )
				m_ptr->DecRef();

			if( rhs.m_ptr )
				rhs.m_ptr->IncRef();

			m_ptr = rhs.m_ptr;
		}
		return *this;
	}

	bool operator ==( const RefCountPtr<T>& rhs ) const 
	{
		return (m_ptr == rhs.m_ptr);
	}

	bool operator ==( const T* rhs ) const
	{
		return (m_ptr == rhs);
	}

	bool operator !() const
	{
		return (m_ptr == 0);
	}

	bool IsNull() const
	{
		return (m_ptr == 0);
	}

	bool HasValue() const
	{
		return (m_ptr != 0);
	}

private:
	T* m_ptr;
};
