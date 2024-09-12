#include "StdAfx.h"
#include <CxxTest.h>

#include "MainLoop.h"
#include "ScreenBase.h"
#include "StubScreen.h"
#include "ScreenCommands.h"
#include "../Input/Bind.h"
namespace NMainLoop
{
TScreenList &GetScreens();
}
namespace NScreenCommands
{
TScreenCommandsList &GetScreenCmds();
}

class CScreenTests : public CxxTest::TestSuite
{

public:
	void Add4Screens();
	void RemoveScreen();
	void RemoveAllScreens();
	void DrawScreens();
	void ProcessEvent();
	void IndependCommands();
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CScreenTests::Add4Screens()
{
	TS_ASSERT( NMainLoop::GetScreens().size() == 0 );
	TS_ASSERT( NScreenCommands::GetScreenCmds().size() == 0 );

	CPtr<NMainLoop::CStubScreen> pStubScreen = new NMainLoop::CStubScreen();
	TS_ASSERT( pStubScreen );
	pStubScreen->Init( 0 );
	NMainLoop::AddScreen( pStubScreen );
	TS_ASSERT( NMainLoop::GetScreens().size() == 0 );
	TS_ASSERT( NMainLoop::Step( true ) );
	TS_ASSERT( pStubScreen == NMainLoop::GetScreens().front() );
	
	pStubScreen = new NMainLoop::CStubScreen();
	pStubScreen->Init( 0 );
	NMainLoop::AddScreen(pStubScreen);

	pStubScreen = new NMainLoop::CStubScreen();
	pStubScreen->Init( 0 );
	pStubScreen->SetTransparent(true);
	pStubScreen->SetModal(true);
	NMainLoop::AddScreen(pStubScreen);

	pStubScreen = new NMainLoop::CStubScreen();
	pStubScreen->Init( 0 );
	pStubScreen->SetTransparent(true);
	NMainLoop::AddScreen(pStubScreen);
	TS_ASSERT( NMainLoop::GetScreens().size() == 1 );
	TS_ASSERT( NMainLoop::Step( true ) );
	TS_ASSERT( NMainLoop::GetScreens().size() == 4 );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CScreenTests::DrawScreens()
{
	TS_ASSERT( NMainLoop::GetScreens().size() == 2 );
	CDynamicCast<NMainLoop::CStubScreen> pStubScreenBack = NMainLoop::GetScreens().back();
	TS_ASSERT( IsValid(pStubScreenBack) );
	if ( !IsValid(pStubScreenBack)	)
	{
		return;
	}
	TS_ASSERT( pStubScreenBack->GetDraw() == 2);
	CDynamicCast<NMainLoop::CStubScreen> pStubScreenFront = NMainLoop::GetScreens().front();
	TS_ASSERT_EQUALS(	IsValid(pStubScreenFront), true );
	if ( !IsValid(pStubScreenFront)	)
	{
		return;
	}
	TS_ASSERT_EQUALS(	pStubScreenFront->GetDraw(), 2);

	pStubScreenFront->SetTransparent(false);

	TS_ASSERT_EQUALS(	NMainLoop::Step( true ), true );

	TS_ASSERT_EQUALS(	pStubScreenBack->GetDraw(), 2);
	TS_ASSERT_EQUALS(	pStubScreenFront->GetDraw(), 3);


}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CScreenTests::IndependCommands()
{
	CObj<NMainLoop::CStubScreen> pStubScreen = new NMainLoop::CStubScreen();

	TS_ASSERT( pStubScreen );
	pStubScreen->Init( 0 );
	NMainLoop::AddScreen( pStubScreen );
	TS_ASSERT_EQUALS( NMainLoop::Step( true ), true);

	const int nTotalScreensCount = NMainLoop::GetScreens().size();
	const int nDrawCalles = pStubScreen->GetDraw();
	pStubScreen->RemoveMeOnNextStep();
	// OnBeforeClose должен возвращать false
	pStubScreen->DoNotAllowRemoveMe();
	TS_ASSERT_EQUALS( pStubScreen->OnBeforeClose(), false );
	TS_ASSERT_EQUALS( NMainLoop::Step( true ), true);
	// проверяем что команда на удаление не выполняется прямо в этом Step'е, выполниться она должна в следущем
	TS_ASSERT_EQUALS( NMainLoop::GetScreens().size(), nTotalScreensCount );
	TS_ASSERT_EQUALS( NMainLoop::Step( true ), true);
	// теперь команда должны была обламаться, т.к. OnBeforeClose нам вернул false, но мы поместили еще одну команду на удаление самих себя в стек!!!
	TS_ASSERT_EQUALS( NMainLoop::GetScreens().size(), nTotalScreensCount );
	pStubScreen->AllowRemoveMe();
	TS_ASSERT_DIFFERS( pStubScreen->OnBeforeClose(), false );
	// а вот теперь нас должны были прибить, но сначала нам должны были позвать Draw, вообще нам Draw должны были позвать 3 (по количеству Step) раз
	TS_ASSERT_EQUALS( NMainLoop::Step( true ), false);
	TS_ASSERT_EQUALS( NMainLoop::GetScreens().size(), nTotalScreensCount - 1 );
	// я могу спросить ->GetDraw, т.к. сам держу на экран CObj, поэтому его уничтожение в стеке экранов меня не волнует
	TS_ASSERT_EQUALS( pStubScreen->GetDraw(), nDrawCalles + 3 );
	// а вот тут я не должне упать, у меня есть команда, которая хочет удалить невалидный экран
	TS_ASSERT_EQUALS( NMainLoop::Step( true ), false);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CScreenTests::RemoveScreen()
{
	int nSize = NMainLoop::GetScreens().size();
	if( nSize < 1 ) return;
	NMainLoop::IScreenBase * frontScreen = NMainLoop::GetScreens().front();
	NMainLoop::IScreenBase * backScreen = NMainLoop::GetScreens().back();

	NMainLoop::RemoveScreen( frontScreen );
	TS_ASSERT( frontScreen == NMainLoop::GetScreens().front() );
	TS_ASSERT( nSize == NMainLoop::GetScreens().size() );

	TS_ASSERT( NMainLoop::Step( true ) );
	TS_ASSERT( frontScreen != NMainLoop::GetScreens().front() );
	TS_ASSERT( nSize == NMainLoop::GetScreens().size() + 1 );
	TS_ASSERT( backScreen == NMainLoop::GetScreens().back() );

	nSize = NMainLoop::GetScreens().size();
	if( nSize < 1 ) return;

	NMainLoop::RemoveScreen( backScreen );
	TS_ASSERT( backScreen == NMainLoop::GetScreens().back() );
	TS_ASSERT( nSize == NMainLoop::GetScreens().size() );

	TS_ASSERT( NMainLoop::Step( true ) );
	TS_ASSERT( backScreen != NMainLoop::GetScreens().back() );
	TS_ASSERT( nSize == NMainLoop::GetScreens().size() + 1 );

}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CScreenTests::RemoveAllScreens()
{
	int nSize = NMainLoop::GetScreens().size();
	if( nSize < 1 ) return;
	NMainLoop::RemoveAllScreens();
	TS_ASSERT( nSize == NMainLoop::GetScreens().size() );

	TS_ASSERT( !NMainLoop::Step( true ) );
	TS_ASSERT( 0 == NMainLoop::GetScreens().size() );
}
void CScreenTests::ProcessEvent()
{
	TS_ASSERT( NMainLoop::GetScreens().size() == 2 );
	CDynamicCast<NMainLoop::CStubScreen> pStubScreenBack = NMainLoop::GetScreens().back();
	TS_ASSERT( IsValid(pStubScreenBack) );
	if ( !IsValid(pStubScreenBack)	)
	{
		return;
	}
	TS_ASSERT( pStubScreenBack->GetParam1() == 0);
	TS_ASSERT( pStubScreenBack->GetParam2() == 0);

	CDynamicCast<NMainLoop::CStubScreen> pStubScreenFront = NMainLoop::GetScreens().front();
	TS_ASSERT( IsValid(pStubScreenFront) );
	if ( !IsValid(pStubScreenFront)	)
	{
		return;
	}
	TS_ASSERT( pStubScreenFront->GetParam1() == 0);
	TS_ASSERT( pStubScreenFront->GetParam2() == 0);
	NInput::PostEvent( "BU", 10, 100 );
	TS_ASSERT( pStubScreenBack->GetParam1() == 0);
	TS_ASSERT( pStubScreenBack->GetParam2() == 0);
	TS_ASSERT( pStubScreenFront->GetParam1() == 0);
	TS_ASSERT( pStubScreenFront->GetParam2() == 0);
	TS_ASSERT( NMainLoop::Step( true ) );
	TS_ASSERT( pStubScreenFront->GetParam1() == 10);
	TS_ASSERT( pStubScreenFront->GetParam2() == 100);
	TS_ASSERT( pStubScreenBack->GetParam1() == 0);
	TS_ASSERT( pStubScreenBack->GetParam2() == 0);
	pStubScreenFront->SetModal( false );
	NInput::PostEvent( "BD", 11, 101 );
	TS_ASSERT( pStubScreenFront->GetParam1() == 10);
	TS_ASSERT( pStubScreenFront->GetParam2() == 100);
	TS_ASSERT( pStubScreenBack->GetParam1() == 0);
	TS_ASSERT( pStubScreenBack->GetParam2() == 0);
	TS_ASSERT( NMainLoop::Step( true ) );
	TS_ASSERT( pStubScreenFront->GetParam1() == 11);
	TS_ASSERT( pStubScreenFront->GetParam2() == 101);
	TS_ASSERT( pStubScreenBack->GetParam1() == 11);
	TS_ASSERT( pStubScreenBack->GetParam2() == 101);
}
CXX_REGISTER_TEST_SUITE( CScreenTests )
{
	CXX_REGISTER_TEST_FUNCTION( Add4Screens );
	CXX_REGISTER_TEST_FUNCTION( RemoveScreen );
	CXX_REGISTER_TEST_FUNCTION( DrawScreens );
	CXX_REGISTER_TEST_FUNCTION( ProcessEvent );
	CXX_REGISTER_TEST_FUNCTION( RemoveAllScreens );
	CXX_REGISTER_TEST_FUNCTION( IndependCommands );
}