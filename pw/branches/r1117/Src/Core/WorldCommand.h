#pragma once
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NCore
{
_interface IWorldBase;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class WorldCommand : public CObjectBase
{
  int id;

public:
  WorldCommand() : id(-1) {}

  void SetId(int _id) { id = _id; }
  int  GetId() const { return id; }

	virtual bool CanExecute() const = 0;
	virtual void Execute(	IWorldBase *pWorld	) = 0;
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//class WorldCommandQueue : public NonCopyable
//{
//  list<CObj<WorldCommand> > commands;
//public:
//  WorldCommandQueue() {}
//  WorldCommandQueue(CObj<WorldCommand> const& pCommand) { AddCommand(pCommand); }
//
//  void AddCommand(CObj<WorldCommand> const& pCommand) {  if(NULL != pCommand ) commands.insert(commands.end(), pCommand); }
//  CObj<WorldCommand> Front() const { return  commands.empty() ? NULL : *commands.begin(); }
//  void               PopFront() { if( !commands.empty() ) commands.erase( commands.begin() ); }
//  bool               IsEmpty() const { return commands.empty(); }
//};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}; // namespace NCore
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// макросы для создания команд 
// DEFINE_N_PARAM_CMD( name, ...) - для команд, у которых CanExecute всегда true. Надо написать функцию name::Execute
// DEFINE_N_PARAM_CMD_CHECK( name, ...) - для команд, которым нужен кастомный CanExecute. Надо написать функции name::Execute и name::CanExecute
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define DEFINE_0_PARAM_CMD( N, name ) \
class name : public NCore::WorldCommand {\
	OBJECT_METHODS( N, name );\
public:\
	name() {}\
	int operator&( IBinSaver &f ) { return 0; }\
	bool CanExecute() const { return true; } \
	void Execute( NCore::IWorldBase * );\
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define DEFINE_1_PARAM_CMD( N, name, type1, name1 ) \
class name : public NCore::WorldCommand {\
	OBJECT_METHODS( N, name );\
	name() {}\
public:\
	type1 name1; int operator&( IBinSaver &f ) { f.Add(2,&name1); return 0; }\
	name( const type1 &_p ) : name1(_p) {}\
	bool CanExecute() const { return true; } \
	void Execute( NCore::IWorldBase * );\
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define DEFINE_2_PARAM_CMD( N, name, type1, name1, type2, name2 ) \
class name : public NCore::WorldCommand {\
	OBJECT_METHODS( N, name );\
	name() {}\
public:\
	type1 name1; type2 name2; int operator&( IBinSaver &f ) { f.Add(2,&name1); f.Add(3,&name2); return 0; }\
	name( const type1 &_p1, const type2 &_p2 ) : name1(_p1), name2(_p2) {}\
	bool CanExecute() const { return true; } \
	void Execute( NCore::IWorldBase * );\
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define DEFINE_3_PARAM_CMD( N, name, type1, name1, type2, name2, type3, name3 ) \
class name : public NCore::WorldCommand {\
	OBJECT_METHODS( N, name );\
	name() {}\
public:\
	type1 name1; type2 name2; type3 name3; int operator&( IBinSaver &f ) { f.Add(2,&name1); f.Add(3,&name2); f.Add(4,&name3); return 0; }\
	name( const type1 &_p1, const type2 &_p2, const type3 &_p3 ) : name1(_p1), name2(_p2), name3(_p3) {}\
	bool CanExecute() const { return true; } \
	void Execute( NCore::IWorldBase * );\
};
////////////////////////////////////////////////////////////////////////////////////////////////////
#define DEFINE_4_PARAM_CMD( N, name, type1, name1, type2, name2, type3, name3, type4, name4 ) \
class name : public NCore::WorldCommand {\
	OBJECT_METHODS( N, name );\
	name() {}\
public:\
	type1 name1; type2 name2; type3 name3; type4 name4; int operator&( IBinSaver &f ) { f.Add(2,&name1); f.Add(3,&name2); f.Add(4,&name3); f.Add(5,&name4); return 0; }\
	name( const type1 &_p1, const type2 &_p2, const type3 &_p3, const type4 &_p4 ) : name1(_p1), name2(_p2), name3(_p3), name4(_p4) {}\
	bool CanExecute() const { return true; } \
	void Execute( NCore::IWorldBase * );\
};
////////////////////////////////////////////////////////////////////////////////////////////////////
#define DEFINE_5_PARAM_CMD( N, name, type1, name1, type2, name2, type3, name3, type4, name4, type5, name5 ) \
class name : public NCore::WorldCommand {\
	OBJECT_METHODS( N, name );\
	name() {}\
public:\
	type1 name1; type2 name2; type3 name3; type4 name4; type5 name5; int operator&( IBinSaver &f ) { f.Add(2,&name1); f.Add(3,&name2); f.Add(4,&name3); f.Add(5,&name4); f.Add(6,&name5); return 0; }\
	name( const type1 &_p1, const type2 &_p2, const type3 &_p3, const type4 &_p4, const type5 &_p5 ) : name1(_p1), name2(_p2), name3(_p3), name4(_p4), name5(_p5) {}\
	bool CanExecute() const { return true; } \
	void Execute( NCore::IWorldBase * );\
};
////////////////////////////////////////////////////////////////////////////////////////////////////
#define DEFINE_6_PARAM_CMD( N, name, type1, name1, type2, name2, type3, name3, type4, name4, type5, name5, type6, name6 ) \
class name : public NCore::WorldCommand {\
	OBJECT_METHODS( N, name );\
	name() {}\
public:\
	type1 name1; type2 name2; type3 name3; type4 name4; type5 name5; type6 name6; int operator&( IBinSaver &f ) { f.Add(2,&name1); f.Add(3,&name2); f.Add(4,&name3); f.Add(5,&name4); f.Add(6,&name5); f.Add(7,&name6); return 0; }\
	name( const type1 &_p1, const type2 &_p2, const type3 &_p3, const type4 &_p4, const type5 &_p5, const type6 &_p6 ) : name1(_p1), name2(_p2), name3(_p3), name4(_p4), name5(_p5), name6(_p6) {}\
	bool CanExecute() const { return true; } \
	void Execute( NCore::IWorldBase * );\
};
////////////////////////////////////////////////////////////////////////////////////////////////////
#define DEFINE_7_PARAM_CMD( N, name, type1, name1, type2, name2, type3, name3, type4, name4, type5, name5, type6, name6, type7, name7 ) \
class name : public NCore::WorldCommand {\
	OBJECT_METHODS( N, name );\
	name() {}\
public:\
	type1 name1; type2 name2; type3 name3; type4 name4; type5 name5; type6 name6; type7 name7; int operator&( IBinSaver &f ) { f.Add(2,&name1); f.Add(3,&name2); f.Add(4,&name3); f.Add(5,&name4); f.Add(6,&name5); f.Add(7,&name6); f.Add(8,&name7); return 0; }\
	name( const type1 &_p1, const type2 &_p2, const type3 &_p3, const type4 &_p4, const type5 &_p5, const type6 &_p6, const type7 &_p7 ) : name1(_p1), name2(_p2), name3(_p3), name4(_p4), name5(_p5), name6(_p6), name7(_p7) {}\
	bool CanExecute() const { return true; } \
	void Execute( NCore::IWorldBase * );\
};
////////////////////////////////////////////////////////////////////////////////////////////////////
#define DEFINE_8_PARAM_CMD( N, name, type1, name1, type2, name2, type3, name3, type4, name4, type5, name5, type6, name6, type7, name7, type8, name8 ) \
class name : public NCore::WorldCommand {\
	OBJECT_METHODS( N, name );\
	name() {}\
public:\
	type1 name1; type2 name2; type3 name3; type4 name4; type5 name5; type6 name6; type7 name7; type8 name8; int operator&( IBinSaver &f ) { f.Add(2,&name1); f.Add(3,&name2); f.Add(4,&name3); f.Add(5,&name4); f.Add(6,&name5); f.Add(7,&name6); f.Add(8,&name7); f.Add(9,&name8); return 0; }\
	name( const type1 &_p1, const type2 &_p2, const type3 &_p3, const type4 &_p4, const type5 &_p5, const type6 &_p6, const type7 &_p7, const type8 &_p8 ) : name1(_p1), name2(_p2), name3(_p3), name4(_p4), name5(_p5), name6(_p6), name7(_p7), name8(_p8) {}\
	bool CanExecute() const { return true; } \
	void Execute( NCore::IWorldBase * );\
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define DEFINE_1_PARAM_CMD_CHECK( N, name, type1, name1 ) \
class name : public NCore::WorldCommand {\
	OBJECT_METHODS( N, name );\
	name() {}\
public:\
	type1 name1; int operator&( IBinSaver &f ) { f.Add(2,&name1); return 0; }\
	name( const type1 &_p ) : name1(_p) {}\
	bool CanExecute() const; \
	void Execute( NCore::IWorldBase * );\
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define DEFINE_2_PARAM_CMD_CHECK( N, name, type1, name1, type2, name2 ) \
class name : public NCore::WorldCommand {\
	OBJECT_METHODS( N, name );\
	name() {}\
public:\
	type1 name1; type2 name2; int operator&( IBinSaver &f ) { f.Add(2,&name1); f.Add(3,&name2); return 0; }\
	name( const type1 &_p1, const type2 &_p2 ) : name1(_p1), name2(_p2) {}\
	bool CanExecute() const; \
	void Execute( NCore::IWorldBase * );\
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define DEFINE_3_PARAM_CMD_CHECK( N, name, type1, name1, type2, name2, type3, name3 ) \
class name : public NCore::WorldCommand {\
	OBJECT_METHODS( N, name );\
	name() {}\
public:\
	type1 name1; type2 name2; type3 name3; int operator&( IBinSaver &f ) { f.Add(2,&name1); f.Add(3,&name2); f.Add(4,&name3); return 0; }\
	name( const type1 &_p1, const type2 &_p2, const type3 &_p3 ) : name1(_p1), name2(_p2), name3(_p3) {}\
	bool CanExecute() const; \
	void Execute( NCore::IWorldBase * );\
};
////////////////////////////////////////////////////////////////////////////////////////////////////
#define DEFINE_4_PARAM_CMD_CHECK( N, name, type1, name1, type2, name2, type3, name3, type4, name4 ) \
class name : public NCore::WorldCommand {\
	OBJECT_METHODS( N, name );\
	name() {}\
public:\
	type1 name1; type2 name2; type3 name3; type4 name4; int operator&( IBinSaver &f ) { f.Add(2,&name1); f.Add(3,&name2); f.Add(4,&name3); f.Add(5,&name4); return 0; }\
	name( const type1 &_p1, const type2 &_p2, const type3 &_p3, const type4 &_p4 ) : name1(_p1), name2(_p2), name3(_p3), name4(_p4) {}\
	bool CanExecute() const; \
	void Execute( NCore::IWorldBase * );\
};
////////////////////////////////////////////////////////////////////////////////////////////////////
#define DEFINE_5_PARAM_CMD_CHECK( N, name, type1, name1, type2, name2, type3, name3, type4, name4, type5, name5 ) \
class name : public NCore::WorldCommand {\
	OBJECT_METHODS( N, name );\
	name() {}\
public:\
	type1 name1; type2 name2; type3 name3; type4 name4; type5 name5; int operator&( IBinSaver &f ) { f.Add(2,&name1); f.Add(3,&name2); f.Add(4,&name3); f.Add(5,&name4); f.Add(6,&name5); return 0; }\
	name( const type1 &_p1, const type2 &_p2, const type3 &_p3, const type4 &_p4, const type5 &_p5 ) : name1(_p1), name2(_p2), name3(_p3), name4(_p4), name5(_p5) {}\
	bool CanExecute() const; \
	void Execute( NCore::IWorldBase * );\
};
////////////////////////////////////////////////////////////////////////////////////////////////////
#define DEFINE_6_PARAM_CMD_CHECK( N, name, type1, name1, type2, name2, type3, name3, type4, name4, type5, name5, type6, name6 ) \
class name : public NCore::WorldCommand {\
	OBJECT_METHODS( N, name );\
	name() {}\
public:\
	type1 name1; type2 name2; type3 name3; type4 name4; type5 name5; type6 name6; int operator&( IBinSaver &f ) { f.Add(2,&name1); f.Add(3,&name2); f.Add(4,&name3); f.Add(5,&name4); f.Add(6,&name5); f.Add(7,&name6); return 0; }\
	name( const type1 &_p1, const type2 &_p2, const type3 &_p3, const type4 &_p4, const type5 &_p5, const type6 &_p6 ) : name1(_p1), name2(_p2), name3(_p3), name4(_p4), name5(_p5), name6(_p6) {}\
	bool CanExecute() const; \
	void Execute( NCore::IWorldBase * );\
};
////////////////////////////////////////////////////////////////////////////////////////////////////
#define DEFINE_7_PARAM_CMD_CHECK( N, name, type1, name1, type2, name2, type3, name3, type4, name4, type5, name5, type6, name6, type7, name7 ) \
class name : public NCore::WorldCommand {\
	OBJECT_METHODS( N, name );\
	name() {}\
public:\
	type1 name1; type2 name2; type3 name3; type4 name4; type5 name5; type6 name6; type7 name7; int operator&( IBinSaver &f ) { f.Add(2,&name1); f.Add(3,&name2); f.Add(4,&name3); f.Add(5,&name4); f.Add(6,&name5); f.Add(7,&name6); f.Add(8,&name7); return 0; }\
	name( const type1 &_p1, const type2 &_p2, const type3 &_p3, const type4 &_p4, const type5 &_p5, const type6 &_p6, const type7 &_p7 ) : name1(_p1), name2(_p2), name3(_p3), name4(_p4), name5(_p5), name6(_p6), name7(_p7) {}\
	bool CanExecute() const; \
	void Execute( NCore::IWorldBase * );\
};
////////////////////////////////////////////////////////////////////////////////////////////////////
#define DEFINE_8_PARAM_CMD_CHECK( N, name, type1, name1, type2, name2, type3, name3, type4, name4, type5, name5, type6, name6, type7, name7, type8, name8 ) \
class name : public NCore::WorldCommand {\
	OBJECT_METHODS( N, name );\
	name() {}\
public:\
	type1 name1; type2 name2; type3 name3; type4 name4; type5 name5; type6 name6; type7 name7; type8 name8; int operator&( IBinSaver &f ) { f.Add(2,&name1); f.Add(3,&name2); f.Add(4,&name3); f.Add(5,&name4); f.Add(6,&name5); f.Add(7,&name6); f.Add(8,&name7); f.Add(9,&name8); return 0; }\
	name( const type1 &_p1, const type2 &_p2, const type3 &_p3, const type4 &_p4, const type5 &_p5, const type6 &_p6, const type7 &_p7, const type8 &_p8 ) : name1(_p1), name2(_p2), name3(_p3), name4(_p4), name5(_p5), name6(_p6), name7(_p7), name8(_p8) {}\
	bool CanExecute() const; \
	void Execute( NCore::IWorldBase * );\
};
////////////////////////////////////////////////////////////////////////////////////////////////////
//#define CREATE_WORLDCMD_QUEUE( ARG ) AutoPtr<NCore::WorldCommandQueue>( new NCore::WorldCommandQueue( (ARG) ) )
////////////////////////////////////////////////////////////////////////////////////////////////////
