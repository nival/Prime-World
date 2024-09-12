#include "stdafx.h"
#include "SkeletonWrapper.h"

#include "../MeshConverter/SkeletonHeader.h"

namespace Render
{

	SkeletonWrapper::SkeletonWrapper( const SkeletonDataWrapper* _pSkeletonData ) : 
    pSkeletonData(_pSkeletonData), 
    pSampledMatrix(0), 
    pSkinWorldMatrix(0), 
    activeBonesCount(0),
    allocatedBonesCount(0)
	{
		const unsigned int bonesCount = pSkeletonData->GetData()->jointsCount;

		pSampledMatrix = static_cast<Matrix43*>(Aligned_MAlloc(sizeof(Matrix43)*bonesCount*2, 16));
		pBoneWorldMatrix = pSampledMatrix + bonesCount;
	}

  SkeletonWrapper::~SkeletonWrapper()
  {
    Aligned_Free(pSampledMatrix);
    Aligned_Free(pSkinWorldMatrix);
  }

  void SkeletonWrapper::SetActiveBones( unsigned int count )
  {
    matrixReindex.resize( count );

    for ( unsigned int i = 0; i < count; ++i )
    {
      matrixReindex[i] = i;
    }

    activeBonesCount = count;

    if ( count > allocatedBonesCount )
    {
      if ( pSkinWorldMatrix )
      {
        Aligned_Free( pSkinWorldMatrix );
      }

      allocatedBonesCount = count;

      pSkinWorldMatrix = static_cast<Matrix43*>(Aligned_MAlloc(sizeof(Matrix43)*allocatedBonesCount, 16));
    }
  }


	void SkeletonWrapper::Update( const Matrix43& _worldMatrix )
	{
		const unsigned int bonesCount = pSkeletonData->GetData()->jointsCount;
		const unsigned int* pParentIndicies = pSkeletonData->GetData()->parentsIDs.at(0);
		const Matrix43* pBindMatricies = pSkeletonData->GetData()->invertedBindPoseBones.at(0);

		__declspec(align(16)) Matrix43 worldMatrix(_worldMatrix);

		SEEMatrixMultiply( &pBoneWorldMatrix[0], &worldMatrix, &pSampledMatrix[0] );

    // Hierarchical bone placements
		for	( unsigned int i = 1; i < bonesCount; ++i )
  		SEEMatrixMultiply( &pBoneWorldMatrix[i], &pBoneWorldMatrix[ pParentIndicies[i] ], &pSampledMatrix[i] );

    // Absolute bone placements
    //for	( unsigned int i = 1; i < bonesCount; ++i )
    // SEEMatrixMultiply( &pBoneWorldMatrix[i], &worldMatrix, &pSampledMatrix[i] );
    
		for	( unsigned int i = 0; i < activeBonesCount; ++i ) 
      SEEMatrixMultiply( &pSkinWorldMatrix[i], &pBoneWorldMatrix[ matrixReindex[i] ], &pBindMatricies[ matrixReindex[i] ] );
	}

	bool SkeletonWrapper::GetJointIndexByName( const char* name, unsigned int& index ) const
	{
		//crap!!!
		//nstl::find_if( pSkeletonData->boneNames.begin(), pSkeletonData->boneNames.end(), JointPredicate );

		for ( unsigned int i = 0; i < pSkeletonData->GetData()->jointsCount; i++ )
		{
			if ( strcmp( pSkeletonData->GetData()->jointsNames[i].c_str(), name ) == 0 )
			{
				index = pSkeletonData->GetData()->namesOrder[i];
				return true;
			}
		}
		return false;
	}

  bool SkeletonWrapper::GetJointOrderByName( const char* name, unsigned int& index ) const
  {
    //crap!!!
    //nstl::find_if( pSkeletonData->boneNames.begin(), pSkeletonData->boneNames.end(), JointPredicate );

    for ( unsigned int i = 0; i < pSkeletonData->GetData()->jointsCount; i++ )
    {
      if ( strcmp( pSkeletonData->GetData()->jointsNames[i].c_str(), name ) == 0 )
      {
        index = i;
        return true;
      }
    }
    return false;
  }

  void SkeletonWrapper::GetBoneChildren(unsigned int index, vector<unsigned int> &childrenIdxes) const
  {
    for ( unsigned int i = 0; i < pSkeletonData->GetData()->jointsCount; i++ )
    {
      if(pSkeletonData->GetData()->parentsIDs[i] == index)
      {
        childrenIdxes.push_back(i);
      }
    }  
    return;
  }

  char const * SkeletonWrapper::GetJointNameByIndex(unsigned int index ) const
  {
    for(unsigned int i = 0; i < pSkeletonData->GetData()->jointsCount; i++)
    {
      if(pSkeletonData->GetData()->namesOrder[i] == index)
      {
        return pSkeletonData->GetData()->jointsNames[i].c_str();
      }
    }
    return NULL;
  }

	int SkeletonWrapper::GetBonesCount() const
	{
		return pSkeletonData->GetData()->jointsCount;
	}

  vector<string> SkeletonWrapper::GetJointsList()
  {
    vector<string> res;
    for ( unsigned int i = 0; i < pSkeletonData->GetData()->jointsCount; i++ )
    {
      res.push_back( pSkeletonData->GetData()->jointsNames[i].c_str() );
    }
    return res;
  }

  void SkeletonWrapper::SetReindex( unsigned int from, unsigned int to )
  {
    NI_ASSERT( from >= 0 && from < pSkeletonData->GetData()->jointsCount, "Wrong index" );
    NI_ASSERT( to >= 0 && to < (unsigned int)matrixReindex.size(), "Wrong index" );
    matrixReindex[to] = from;
  }

  //void SkeletonWrapper::SetSkeletonData( const SkeletonDataWrapper* pNewSkeletonData )
  //{
  //  pSkeletonData = pNewSkeletonData;
  //}

};