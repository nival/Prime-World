#pragma once
#include "ScreenBase.h"

namespace NScreenCommands
{
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
_interface IScreenCommand : public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_1( IScreenCommand, BaseObjectST );

	virtual void Exec() = 0;
	virtual bool Prepare() = 0;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
IScreenCommand *CreatePushScreenCommand( NMainLoop::IScreenBase *pScreenToPush );
IScreenCommand *CreatePopScreenCommand( NMainLoop::IScreenBase *pScreenToPop );
IScreenCommand *CreatePopScreenCommand( const string& screenToPopName );
IScreenCommand *CreateClearStackCommand();

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef NMainLoop::IScreenBase* (*CreateFun)();
void RegisterInScreensFactory(const string& name, CreateFun);
NMainLoop::IScreenBase* CreateScreen(const string& name);
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PushCommand( IScreenCommand *pCommand );
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ProcessScreenCmds();
bool AnalizeScreenCmds();
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClearCommands();
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef list<Strong<NScreenCommands::IScreenCommand>> TScreenCommandsList;

#define REGISTER_SCREEN( command )																																											\
static struct SRegisterGlobalScreen_##command																																								\
{																																																															\
	static NMainLoop::IScreenBase * Create() { return new command(); }																																		\
	SRegisterGlobalScreen_##command##()																																												\
	{																																																														\
		NScreenCommands::RegisterInScreensFactory( #command, Create );																																								\
	}																																																														\
} registerGlobalScreen_##command##;																																													\

}

