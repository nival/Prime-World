//!Component('PF_GameLogic/AnimController')

#include "stdafx.h"
#include <cxxtest/TestSuite.h>

//#include <Scene/TestHelpers.h>
#include <Scene/DiAnGr.h>
//#include <Scene/AGTrace.h>
#include <Scene/AGHelpers.h>

#include "PFAnimController.h"

namespace test
{

class TestAnimGraphBlender : public NScene::IAnimGraphBlender
{
public:
  explicit TestAnimGraphBlender( test::AnimationDataHolder& _holder ) :
    mainGraph(0)
  {
    mainGraph = DiAnimGraph::CreateByData( _holder.animations, this );    
  }

  ~TestAnimGraphBlender()
  {
    if ( mainGraph )
    {
      DiAnimGraph::Destroy( mainGraph ); 
      mainGraph = 0;
    }
  }

  virtual NScene::AnimationVector const &GetAnimationVector() const { return animVector; }
  virtual NScene::Time GetAnimDuration(const int& animName) const { return 0.f; }
  virtual void SetVirtualParameterByMix(int nMixIdx, float rT) {}
  virtual bool RegisterSequencesToMix(int nSeqsCount, int  *npSeqIndices, float *rWeights) { return true; }
  virtual DiAnimGraph       *GetMainGraph() { return mainGraph; }
  virtual DiAnimGraph const *GetMainGraph() const { return mainGraph; }
  virtual DiAnimGraph       *GetAdditionalGraph() { return 0; }
  virtual DiAnimGraph const *GetAdditionalGraph() const { return 0; }
  virtual bool Update(float dt) { return true; }
  virtual bool SetMainAGTargetNode( int nodeId ) { return true; }
  virtual bool SetAdditionalAGTargetNode( int nodeId ) { return true; }
private:

  NScene::AnimationVector animVector;
  DiAnimGraph* mainGraph;
};


}

struct Test_PFAnimController : public CxxTest::TestSuite
{
  test::AnimationDataHolder animDataHolder;
  NDb::AnimSet priestessSet;

  void setUpSuite()
  {
    animDataHolder.AddAnimation( "ability2", 0.5f );
    animDataHolder.AddAnimation( "ability2_3", 0.5f );
    animDataHolder.AddAnimation( "ability2_4", 0.5f );

    priestessSet.states.resize( NDb::KnownEnum<NDb::EAnimStates>::sizeOf );
    priestessSet.states[ NDb::ANIMSTATES_ABILITY2 ].commonNode = "ability2";
  }

  void tearDownSuite()
  {

  }

  void test_AnimSet_Register()
  {
    test::TestAnimGraphBlender blender( animDataHolder );
    NGameX::PFAnimController controller;            

    controller.Initialize( &blender, 0 , true);

    NDb::AnimSet animSet1;
    NDb::AnimSet animSet2;
    NDb::AnimSet animSet3;
    NDb::AnimSet animSet4;

    TS_ASSERT_EQUALS(0, controller.RegisterAnimSet( &animSet1 ) );
    TS_ASSERT_EQUALS(1, controller.RegisterAnimSet( &animSet2 ) );
    TS_ASSERT_EQUALS(2, controller.RegisterAnimSet( &animSet3 ) );
    TS_ASSERT_EQUALS(3, controller.RegisterAnimSet( &animSet4 ) );

    TS_ASSERT( controller.UnRegisterAnimSet( 2 ) );

    TS_ASSERT_EQUALS(2, controller.RegisterAnimSet( &animSet3 ) );

    controller.ActivateAnimSet( 1 );

    controller.Cleanup();

    TS_ASSERT_EQUALS(0, controller.RegisterAnimSet( &animSet1 ) );
  }

  void test_ReplaceAnimation()
  {
    test::TestAnimGraphBlender blender( animDataHolder );
    NGameX::PFAnimController controller;            

    controller.Initialize( &blender, 0 , true);

    int setId = controller.RegisterAnimSet( &priestessSet );
    controller.ActivateAnimSet( setId );

    unsigned original = controller.GetStateId( NDb::ANIMSTATES_ABILITY2 );
    unsigned new1 = controller.ReplaceAnimation( NDb::ANIMSTATES_ABILITY2, "ability2_3", "", false );
    TS_ASSERT_DIFFERS( -1, new1 );
    TS_ASSERT_DIFFERS( original, controller.GetStateId( NDb::ANIMSTATES_ABILITY2 ) );
    TS_ASSERT( controller.RollbackAnimation( NDb::ANIMSTATES_ABILITY2, new1, false ) );
    TS_ASSERT_EQUALS( original, controller.GetStateId( NDb::ANIMSTATES_ABILITY2 ) );
  }

  void test_DoubleReplaceAnimation()
  {
    test::TestAnimGraphBlender blender( animDataHolder );
    NGameX::PFAnimController controller;            

    controller.Initialize( &blender, 0 , true);

    int setId = controller.RegisterAnimSet( &priestessSet );
    controller.ActivateAnimSet( setId );

    unsigned original  = controller.GetStateId( NDb::ANIMSTATES_ABILITY2 );
    unsigned new1 = controller.ReplaceAnimation( NDb::ANIMSTATES_ABILITY2, "ability2_3", "", false );
    unsigned replaced1 = controller.GetStateId( NDb::ANIMSTATES_ABILITY2 );
    unsigned new2 = controller.ReplaceAnimation( NDb::ANIMSTATES_ABILITY2, "ability2_4", "", false );
    TS_ASSERT_DIFFERS( -1, new1 );
    TS_ASSERT_DIFFERS( -1, new2 );
    TS_ASSERT_DIFFERS( original, replaced1 );
    TS_ASSERT_DIFFERS( original, controller.GetStateId( NDb::ANIMSTATES_ABILITY2 ) );
    TS_ASSERT( controller.RollbackAnimation( NDb::ANIMSTATES_ABILITY2, new2, false ) );
    TS_ASSERT( controller.RollbackAnimation( NDb::ANIMSTATES_ABILITY2, new1, false ) );
    TS_ASSERT_EQUALS( original, controller.GetStateId( NDb::ANIMSTATES_ABILITY2 ) );
  }

  void test_DoubleReplaceAnimation_NotFILO()
  {
    test::TestAnimGraphBlender blender( animDataHolder );
    NGameX::PFAnimController controller;            

    controller.Initialize( &blender, 0 , true);

    int setId = controller.RegisterAnimSet( &priestessSet );
    controller.ActivateAnimSet( setId );

    unsigned original = controller.GetStateId( NDb::ANIMSTATES_ABILITY2 );
    unsigned new1 = controller.ReplaceAnimation( NDb::ANIMSTATES_ABILITY2, "ability2_3", "", false );
    unsigned replaced1 = controller.GetStateId( NDb::ANIMSTATES_ABILITY2 );
    unsigned new2 = controller.ReplaceAnimation( NDb::ANIMSTATES_ABILITY2, "ability2_4", "", false );
    TS_ASSERT_DIFFERS( -1, new1 );
    TS_ASSERT_DIFFERS( -1, new2 );
    TS_ASSERT_DIFFERS( original, replaced1 );
    TS_ASSERT_DIFFERS( original,  controller.GetStateId( NDb::ANIMSTATES_ABILITY2 ) );
    TS_ASSERT( controller.RollbackAnimation( NDb::ANIMSTATES_ABILITY2, new1, false ) );
    TS_ASSERT( controller.RollbackAnimation( NDb::ANIMSTATES_ABILITY2, new2, false ) );
    TS_ASSERT_EQUALS( original, controller.GetStateId( NDb::ANIMSTATES_ABILITY2 ) );
  }

  void test_AnimSet_Replace_Interaction()
  {
    test::TestAnimGraphBlender blender( animDataHolder );
    NGameX::PFAnimController controller;            

    controller.Initialize( &blender, 0 , true);

    int setId1 = controller.RegisterAnimSet( &priestessSet );
    int setId2 = controller.RegisterAnimSet( &priestessSet );

    TS_ASSERT( controller.ActivateAnimSet( setId1 ) );

    unsigned original = controller.GetStateId( NDb::ANIMSTATES_ABILITY2 );
    unsigned new1 = controller.ReplaceAnimation( NDb::ANIMSTATES_ABILITY2, "ability2_3", "", false, true );
    TS_ASSERT_DIFFERS( -1, new1 );
    TS_ASSERT_DIFFERS( original, controller.GetStateId( NDb::ANIMSTATES_ABILITY2 ) );

    TS_ASSERT( controller.ActivateAnimSet( setId2 ) );

    TS_ASSERT( controller.RollbackAnimation( NDb::ANIMSTATES_ABILITY2, new1, false ) );
    TS_ASSERT_EQUALS( original, controller.GetStateId( NDb::ANIMSTATES_ABILITY2 ) );
  }

  void test_AnimSet_Replace_Interaction2()
  {
    test::TestAnimGraphBlender blender( animDataHolder );
    NGameX::PFAnimController controller;            

    controller.Initialize( &blender, 0 , true);

    int setId1 = controller.RegisterAnimSet( &priestessSet );
    int setId2 = controller.RegisterAnimSet( &priestessSet );

    TS_ASSERT( controller.ActivateAnimSet( setId1 ) );
    TS_ASSERT( controller.ActivateAnimSet( setId2 ) );

    unsigned original = controller.GetStateId( NDb::ANIMSTATES_ABILITY2 );
    unsigned new1 = controller.ReplaceAnimation( NDb::ANIMSTATES_ABILITY2, "ability2_3", "", false, true );
    TS_ASSERT_DIFFERS( -1, new1 );
    TS_ASSERT_DIFFERS( original, controller.GetStateId( NDb::ANIMSTATES_ABILITY2 ) );

    TS_ASSERT( controller.UnRegisterAnimSet( setId2 ) );
    TS_ASSERT( controller.ActivateAnimSet( setId1 ) );

    TS_ASSERT( controller.RollbackAnimation( NDb::ANIMSTATES_ABILITY2, new1, false ) );
    TS_ASSERT_EQUALS( original, controller.GetStateId( NDb::ANIMSTATES_ABILITY2 ) );
  }

  void test_AnimSet_Replace_Interaction3()
  {
    test::TestAnimGraphBlender blender( animDataHolder );
    NGameX::PFAnimController controller;            

    controller.Initialize( &blender, 0 ,true);

    int setId1 = controller.RegisterAnimSet( &priestessSet );
    int setId2 = controller.RegisterAnimSet( &priestessSet );

    TS_ASSERT( controller.ActivateAnimSet( setId1 ) );
    unsigned original = controller.GetStateId( NDb::ANIMSTATES_ABILITY2 );
    unsigned new1     = controller.ReplaceAnimation( NDb::ANIMSTATES_ABILITY2, "ability2_3", "", false, false);
    unsigned replaced = controller.GetStateId( NDb::ANIMSTATES_ABILITY2 );
    TS_ASSERT_DIFFERS( -1, new1 );
    TS_ASSERT_DIFFERS( original, replaced);

    TS_ASSERT( controller.ActivateAnimSet( setId2 ) );
    TS_ASSERT_DIFFERS( replaced, controller.GetStateId( NDb::ANIMSTATES_ABILITY2 ) );

    TS_ASSERT( controller.UnRegisterAnimSet( setId2 ) );
    TS_ASSERT( controller.ActivateAnimSet( setId1 ) );

    TS_ASSERT_EQUALS( replaced, controller.GetStateId( NDb::ANIMSTATES_ABILITY2 ) );

    TS_ASSERT( controller.RollbackAnimation( NDb::ANIMSTATES_ABILITY2, new1, false ) );
    TS_ASSERT_EQUALS( original, controller.GetStateId( NDb::ANIMSTATES_ABILITY2 ) );
  }

};

