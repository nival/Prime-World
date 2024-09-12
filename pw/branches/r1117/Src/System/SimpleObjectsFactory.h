#pragma once
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
class SimpleObjectsFactory
{
public:
	typedef T* (*TNewFunction)();
private:
	typedef hash_map< int, TNewFunction > TConstructors;

	TConstructors constructors;
public:
	void RegisterType( const int typeId, TNewFunction newFunction )
	{
		typename TConstructors::const_iterator pos = constructors.find( typeId );
		NI_VERIFY( pos == constructors.end(), NStr::StrFmt( "Type for ID 0x%08X already registred", typeId ), return );

		constructors[typeId] = newFunction;
	}

	T* CreateObject( const int typeId ) const
	{
		typename TConstructors::const_iterator pos = constructors.find( typeId );
		NI_VERIFY( pos != constructors.end(), NStr::StrFmt( "Type for ID 0x%08X not registred", typeId ), return 0 );

		return (pos->second)();
	}
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
