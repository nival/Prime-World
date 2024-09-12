//!Component('Render/SkeletalTestHelpers')
//!Component('MemoryLib/NewDelete')
//!Component('System/FileSystem/TestFileSystem')
//!Component('System/Math')
#include "stdafx.h"
#include <cxxtest/TestSuite.h>
#include "SkeletalAnimationSampler.h"
#include "SkeletonWrapper.h"
#include "System/FileSystem/TestFileSystem.h"
#include "../MeshConverter/SkeletonHeader.h"
#include <iostream>
#include "System/Decompose.h"

template <class T>
const T* InPlaceLoad(TestFileSystem* pFileSystem,const nstl::string& fileName)
{
  //VTuneResumer vtRes( g_Profile_ResourceLoading );
  Stream* pFileStream = pFileSystem->OpenFile( fileName, FILEACCESS_READ, FILEOPEN_OPEN_EXISTING );
  NI_VERIFY( pFileStream && pFileStream->IsOk(), NStr::StrFmt( "Cannot open file for reading: %s", fileName.c_str() ), delete pFileStream; return 0; );
  const int fileSize = pFileStream->GetSize();
  T* pData = (T *)malloc( fileSize );
  pFileStream->Read( pData, fileSize );
  //NI_VERIFY(pData->size() == fileSize, "Inplace Data Was changed", return NULL;);
  return pData;
}

struct Test_Skeletal : public CxxTest::TestSuite
{
  void test_First()
  {
    CObj<TestFileSystem> pFileSystem;
    pFileSystem = new TestFileSystem( "", true );
    pFileSystem->AssignFileWithFile( "LocalAnim.anim", "LocalAnim.anim" );
    pFileSystem->AssignFileWithFile( "Absolute.anim", "Absolute.anim" );
    pFileSystem->AssignFileWithFile( "Root.skel", "Root.skel" );

    const SkeletalAnimationData* pLocalSkeletalAnimationData = InPlaceLoad<SkeletalAnimationData>( pFileSystem, "LocalAnim.anim" );
    SkeletalAnimationDataWrapper* localwrapper = new SkeletalAnimationDataWrapper( pLocalSkeletalAnimationData );
    Render::SkeletalAnimationSampler* localSampler = new Render::SkeletalAnimationSampler( 0.0f, localwrapper );

    const SkeletalAnimationData* pAbsoluteSkeletalAnimationData = InPlaceLoad<SkeletalAnimationData>( pFileSystem, "Absolute.anim" );
    SkeletalAnimationDataWrapper* absolutewrapper = new SkeletalAnimationDataWrapper( pAbsoluteSkeletalAnimationData );
    Render::SkeletalAnimationSampler* absoluteSampler = new Render::SkeletalAnimationSampler( 0.0f, absolutewrapper );

    SkeletonDataWrapper* skel = new SkeletonDataWrapper( reinterpret_cast<const SkeletonData*>( InPlaceLoad<void>( pFileSystem, "Root.skel" ) ) );
    Render::SkeletonWrapper* pSkeletonWrapper = new Render::SkeletonWrapper( skel );

    Render::SkeletonWrapper* pSkeletonWrapper2 = new Render::SkeletonWrapper( skel );

    localSampler->Update(0.0f);
    absoluteSampler->Update(0.0f);
    for ( int step = 0; step < 90; step++ )
    {
      TS_ASSERT_EQUALS( 61, localSampler->GetJointsCount() );
      TS_ASSERT_EQUALS( 61, absoluteSampler->GetJointsCount() );
      for ( unsigned int i = 0; i < 1/*localSampler->GetJointsCount()*/; i++ )
      {
        {
          for(unsigned int jointNumber = 0; jointNumber < localSampler->GetJointsCount(); jointNumber++ )
          {
            CVec3 bonepos;
            CQuat bonerot;
            CVec3 bonescale;
            localSampler->GetTranslation( jointNumber, bonepos );
            localSampler->GetRotation( jointNumber, bonerot );
            localSampler->GetScale( jointNumber, bonescale );

            Matrix43* out = pSkeletonWrapper->GetSampledMatrix()+jointNumber;
            out->Set(bonerot, bonepos, bonescale);
          }
          Matrix43 id(IDENTITY_MATRIX);
          pSkeletonWrapper->Update(id);
          const Matrix43* bmat = pSkeletonWrapper->GetBoneWorldMatrices();
          Placement jointPos;
          jointPos.FromMatrix( bmat[i] );

          for(unsigned int jointNumber = 0; jointNumber < absoluteSampler->GetJointsCount(); jointNumber++ )
          {
            CVec3 bonepos;
            CQuat bonerot;
            CVec3 bonescale;
            absoluteSampler->GetTranslation( jointNumber, bonepos );
            absoluteSampler->GetRotation( jointNumber, bonerot );
            absoluteSampler->GetScale( jointNumber, bonescale );

            Matrix43* out = pSkeletonWrapper2->GetSampledMatrix()+jointNumber;
            out->Set(bonerot, bonepos, bonescale);
          }
          pSkeletonWrapper2->Update(id);
          const Matrix43* bmat2 = pSkeletonWrapper2->GetBoneWorldMatrices();
          Placement jointPos2;
          jointPos2.FromMatrix( bmat2[i] );

          TS_ASSERT_DELTA( jointPos.pos.x, jointPos2.pos.x, 0.01f );
          TS_ASSERT_DELTA( jointPos.pos.y, jointPos2.pos.y, 0.01f );
          TS_ASSERT_DELTA( jointPos.pos.z, jointPos2.pos.z, 0.01f );

          TS_ASSERT_DELTA( jointPos.rot.x, jointPos2.rot.x, 0.01f );
          TS_ASSERT_DELTA( jointPos.rot.y, jointPos2.rot.y, 0.01f );
          TS_ASSERT_DELTA( jointPos.rot.z, jointPos2.rot.z, 0.01f );
          TS_ASSERT_DELTA( jointPos.rot.w, jointPos2.rot.w, 0.01f );

          TS_ASSERT_DELTA( jointPos.scale.x, jointPos2.scale.x, 0.01f );
          TS_ASSERT_DELTA( jointPos.scale.y, jointPos2.scale.y, 0.01f );
          TS_ASSERT_DELTA( jointPos.scale.z, jointPos2.scale.z, 0.01f );
        }
      }
      localSampler->Update(1.f/60.f);
      absoluteSampler->Update(1.f/60.f);
    }
    free((void*)pLocalSkeletalAnimationData);
    free((void*)pAbsoluteSkeletalAnimationData);
    delete pSkeletonWrapper;
    delete skel;
    delete localwrapper;
    delete localSampler;
    delete pSkeletonWrapper2;
    delete absolutewrapper;
    delete absoluteSampler;
  }
};
