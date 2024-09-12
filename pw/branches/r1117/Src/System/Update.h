#ifndef _UPDATE_H_
#define _UPDATE_H_

#include "../MemoryLib/SymAccess.h"
#include "StackWalk.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct SUpdateBase : public CObjectBase
{
	OBJECT_BASIC_METHODS( SUpdateBase );
public:
#ifndef _SHIPPING
	SCallStackEntry callStack[5];
	int operator&( IBinSaver &f ) { f.Add(2,&callStack); return 0; }
#else
	int operator&( IBinSaver &f ) { return 0; }
#endif
protected:
	void CollectCallStack()
	{
#ifndef _SHIPPING
		//vector<SCallStackEntry> _callStack;
		//::CollectCallStack( &_callStack );
		//for ( int i = 3; i < _callStack.size() && i-3 < 5; ++i )
		//	callStack[i-3] = _callStack[i];
#endif
	}
public:
	SUpdateBase() {}
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define UPDATE_0_PARAM( N, name )																																															\
struct name : public SUpdateBase																																															\
{																																																															\
	OBJECT_METHODS( N, name );																																																	\
public:																																																												\
	int operator&( IBinSaver &f ) { f.Add(1,(SUpdateBase*)this); return 0; }																										\
	name() { CollectCallStack(); }																																															\
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define UPDATE_1_PARAM( N, name, type1, name1 )																																								\
struct name : public SUpdateBase																																															\
{																																																															\
	OBJECT_METHODS( N, name );																																																	\
public:																																																												\
	type1 name1;																																																								\
	int operator&( IBinSaver &f ) { f.Add(1,(SUpdateBase*)this); f.Add(2,&name1); return 0; }																		\
private:																																																											\
	name() {}																																																										\
public:																																																												\
	name( const type1 &_name1 ) : name1( _name1 ) { CollectCallStack(); }																												\
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define UPDATE_2_PARAM( N, name, type1, name1, type2, name2 )																																	\
struct name : public SUpdateBase																																															\
{																																																															\
	OBJECT_METHODS( N, name );																																																	\
public:																																																												\
	type1 name1;																																																								\
	type2 name2;																																																								\
	int operator&( IBinSaver &f ) { f.Add(1,(SUpdateBase*)this); f.Add(2,&name1); f.Add(3,&name2); return 0; }									\
private:																																																											\
	name() {}																																																										\
public:																																																												\
	name( const type1 &_name1, const type2 &_name2 ) : name1( _name1 ), name2( _name2 ) { CollectCallStack(); }									\
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define UPDATE_3_PARAM( N, name, type1, name1, type2, name2, type3, name3 )																										\
struct name : public SUpdateBase																																															\
{																																																															\
	OBJECT_METHODS( N, name );																																																	\
public:																																																												\
	type1 name1;																																																								\
	type2 name2;																																																								\
	type3 name3;																																																								\
	int operator&( IBinSaver &f ) { f.Add(1,(SUpdateBase*)this); f.Add(2,&name1); f.Add(3,&name2); f.Add(4,&name3); return 0; }	\
private:																																																											\
	name() {}																																																										\
public:																																																												\
	name( const type1 &_name1, const type2 &_name2, const type3 &_name3 ) : name1( _name1 ), name2( _name2 ), name3( _name3 )		\
		{ CollectCallStack(); }																																																		\
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define UPDATE_3_PARAM( N, name, type1, name1, type2, name2, type3, name3 )																										\
struct name : public SUpdateBase																																															\
{																																																															\
	OBJECT_METHODS( N, name );																																																	\
public:																																																												\
	type1 name1;																																																								\
	type2 name2;																																																								\
	type3 name3;																																																								\
	int operator&( IBinSaver &f ) { f.Add(1,(SUpdateBase*)this); f.Add(2,&name1); f.Add(3,&name2); f.Add(4,&name3); return 0; }	\
private:																																																											\
	name() {}																																																										\
public:																																																												\
	name( const type1 &_name1, const type2 &_name2, const type3 &_name3 ) : name1( _name1 ), name2( _name2 ), name3( _name3 )		\
		{ CollectCallStack(); }																																																		\
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define UPDATE_4_PARAM( N, name, type1, name1, type2, name2, type3, name3, type4, name4 )																			\
struct name : public SUpdateBase																																															\
{																																																															\
	OBJECT_METHODS( N, name );																																																	\
public:																																																												\
	type1 name1;																																																								\
	type2 name2;																																																								\
	type3 name3;																																																								\
	type4 name4;																																																								\
	int operator&( IBinSaver &f )																																																\
	{																																																														\
		f.Add(1,(SUpdateBase*)this); f.Add(2,&name1); f.Add(3,&name2); f.Add(4,&name3); f.Add(5,&name4); return 0;								\
	}																																																														\
private:																																																											\
	name() {}																																																										\
public:																																																												\
	name( const type1 &_name1, const type2 &_name2, const type3 &_name3, const type4 &_name4 ) : name1( _name1 ),								\
		name2( _name2 ), name3( _name3 ), name4( _name4 ) { CollectCallStack(); }																									\
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define UPDATE_5_PARAM( N, name, type1, name1, type2, name2, type3, name3, type4, name4, type5, name5 )												\
struct name : public SUpdateBase																																															\
{																																																															\
	OBJECT_METHODS( N, name );																																																	\
public:																																																												\
	type1 name1;																																																								\
	type2 name2;																																																								\
	type3 name3;																																																								\
	type4 name4;																																																								\
	type5 name5;																																																								\
	int operator&( IBinSaver &f )																																																\
	{																																																														\
		f.Add(1,(SUpdateBase*)this); f.Add(2,&name1); f.Add(3,&name2); f.Add(4,&name3); f.Add(5,&name4); f.Add(6,&name5);					\
		return 0;																																																									\
	}																																																														\
private:																																																											\
	name() {}																																																										\
public:																																																												\
	name( const type1 &_name1, const type2 &_name2, const type3 &_name3, const type4 &_name4, const type5 &_name5 )							\
		: name1( _name1 ), name2( _name2 ), name3( _name3 ), name4( _name4 ), name5( _name5 ) { CollectCallStack(); }							\
};

#endif	// _UPDATE_H_

