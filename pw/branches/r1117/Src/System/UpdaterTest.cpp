//!Component('System/Updater')
#include "stdafx.h"
#include "Update.h"
#include "Updater.h"
#include "UpdateProcessor.h"
#include "Functor.h"
#include "Notifier.h"

#include <CxxTest.h>
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UPDATE_1_PARAM( 0x1E4A8B4D, SUpdate, int, nParam );
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace
{
	int param = 0;
	void TestFunction( const SUpdate& update )
	{
		param = update.nParam;
	}
}

class CUpdateProcessorTest : public Updater::CUpdateProcessor
{
	OBJECT_METHODS( 0x1E4A8B4C, CUpdateProcessorTest );

	ZDATA
		int nParam;
		int nLine;
		string szFile;
	ZEND int operator&( IBinSaver &f ) { f.Add(2,&nParam); f.Add(3,&nLine); f.Add(4,&szFile); return 0; }

	void OnUpdate( const SUpdate &update )
	{
		nParam = update.nParam;
#ifndef _SHIPPING
		nLine = update.callStack[0].nLine;
		szFile = update.callStack[0].szFile.szStr;
#endif
	}
protected:
	void SubscribeUpdates()
	{
		Subscribe( &CUpdateProcessorTest::OnUpdate );
	}
public:
	CUpdateProcessorTest() : nParam( 0 ) { SubscribeUpdates(); }

	const int GetParam() const { return nParam; }
	const int GetLine() const { return nLine; }
	const string &GetFile() const { return szFile; }
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CUpdaterTest : public CxxTest::TestSuite
{
	CObj<Updater::CUpdater> pUpdater;
	CObj<CUpdateProcessorTest> pProcessor;
  CObj<Updater::Functor<SUpdate> > pFunctor;
public:
	void setUpSuite()
	{
		pUpdater = new Updater::CUpdater();
		pProcessor = new CUpdateProcessorTest();
		pUpdater->Register( pProcessor );
    pFunctor = new Updater::Functor<SUpdate>( TestFunction );
    pUpdater->Register( SUpdate::typeId , pFunctor );		
	}
	void tearDownSuite()
	{
		pProcessor = 0;
		pUpdater = 0;
    pFunctor = 0;
	}

	void TestBasic()
  {
    pUpdater->Push( new SUpdate( 10 ), false );
    TS_ASSERT_EQUALS( pProcessor->GetParam(), 10 );
    TS_ASSERT_EQUALS( param, 10 );
    pUpdater->Push( new SUpdate( 11 ), true );
    TS_ASSERT_EQUALS( pProcessor->GetParam(), 10 );
    TS_ASSERT_EQUALS( param, 10 );
    pUpdater->Step();
    TS_ASSERT_EQUALS( pProcessor->GetParam(), 11 );
    TS_ASSERT_EQUALS( param, 11 );
  }

	//void TestCallStack()
 // {
 //   #ifdef _SHIPPING
 //   TS_TRACE( "Collection callstack for updates doesn't work in _SHIPPING version" );
 //   #else
 //   pUpdater->Push( new SUpdate( 10 ), false );
 //   TS_ASSERT_EQUALS( pProcessor->GetLine(), __LINE__ - 1 );
 //   #endif
 // }

  struct NotificationCallback
  {
    string res1, res2;

    void Callback1( const string& param )
    {
      res1 = param;
    }
    void Callback2( const string& param )
    {
      res2 = param;
    }
  };

  void TestNotifier()
  {
    Notifier<string> n1;
    NotificationCallback c1, c2;

    n1.Subscribe( &c1, &NotificationCallback::Callback1 );
    n1.Subscribe( &c2, &NotificationCallback::Callback2 );

    n1.Notify( "aaa" );
    TS_ASSERT( c1.res1 == "aaa" );
    TS_ASSERT( c2.res2 == "aaa" );

    n1.Unsubscribe( &c2, &NotificationCallback::Callback2 );

    n1.Notify( "bbb" );
    TS_ASSERT( c1.res1 == "bbb" );
    TS_ASSERT( c2.res2 == "aaa" );
  }
  void TestNotifiersRegistry()
  {

    NotifiersRegistry<int, string> r;
    NotificationCallback c1, c2;

    r.Subscribe( 1, &c1, &NotificationCallback::Callback1 );
    r.Subscribe( 1, &c2, &NotificationCallback::Callback1 );

    r.Subscribe( 2, &c1, &NotificationCallback::Callback2 );
    r.Subscribe( 2, &c2, &NotificationCallback::Callback2 );

    r.Subscribe( 3, &c1, &NotificationCallback::Callback1 );

    r.Notify( 1, "aaa" );
    TS_ASSERT( c1.res1 == "aaa" );
    TS_ASSERT( c2.res1 == "aaa" );

    r.Notify( 2, "bbb" );
    TS_ASSERT( c1.res2 == "bbb" );
    TS_ASSERT( c2.res2 == "bbb" );

    r.Notify( 3, "ccc" );
    TS_ASSERT( c1.res1 == "ccc" );
    TS_ASSERT( c2.res1 == "aaa" );

    r.Unsubscribe( 1, &c2, &NotificationCallback::Callback1 );
    r.Notify( 1, "d" );
    TS_ASSERT( c1.res1 == "d" );
    TS_ASSERT( c2.res1 == "aaa" );

  }

};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
REGISTER_SAVELOAD_CLASS( CUpdateProcessorTest );
REGISTER_SAVELOAD_CLASS( SUpdate );
