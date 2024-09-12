#pragma once

namespace NWorld
{

class PFWorld;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <class T, class T_DB> 
class DBLinker : public T
{
public:
	DBLinker () {}
	DBLinker (typename T::CreateParams const &cp) : T(cp)
	{
		// Try to cast applicator
		NI_ASSERT(dynamic_cast<T_DB const*>(GetDBBase().GetPtr()) != 0, "Invalid DB applicator");
	}

	DBLinker (typename T::CreateParams const &cp, PFWorld* world) : T(cp, world)
	{
		// Try to cast applicator
		NI_ASSERT(dynamic_cast<T_DB const*>(GetDBBase().GetPtr()) != 0, "Invalid DB applicator");
	}

	T_DB const &GetDB() const { return *static_cast<T_DB const*>(GetDBBase().GetPtr()); }

	typedef DBLinker<T, T_DB> Base;
	ZDATA_(T)
public:
	ZEND int operator&( IBinSaver &f ) { f.Add(1,(T*)this); return 0; }
};

}