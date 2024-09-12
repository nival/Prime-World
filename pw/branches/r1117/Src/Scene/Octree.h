#pragma once 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class TFinal, int N_MIN_NODE>
class OctreeNode: public CObjectBase
{
	typedef OctreeNode<TFinal, N_MIN_NODE> TSelf;
	CVec3 ptBase;
	float fSize;
	CObj<TFinal> links[8];
	CPtr<TFinal> pUpLink;

	//! get multiplier to fSize*sqrt(3) to calc maximal element size
	float GetMaxElementSize() const { return 0.25f * fSize * sqrt(3.0f); }
protected:
	void SetUpLink( TFinal *_p ) { pUpLink = _p; }
public:
	void SetSize( const CVec3 &_ptBase, float _fSize ) { ptBase = _ptBase; fSize = _fSize; }
	float GetSize() const { return fSize; }
	bool Walk() 
	{
		bool bRes = IsEmpty();
		for ( int i = 0; i < 8; ++i )
		{
			if ( links[i] )
			{
				if ( links[i]->Walk() )
					links[i] = 0;
				else
					bRes = false;
			}
		}
		return bRes;
	}
	virtual bool IsEmpty() const { return false; }
	void GetBound( SSphere *pRes ) const
	{
		pRes->ptCenter.x = ptBase.x + fSize * 0.5f;
		pRes->ptCenter.y = ptBase.y + fSize * 0.5f;
		pRes->ptCenter.z = ptBase.z + fSize * 0.5f;
		pRes->fRadius = fSize * sqrt(3.0f) * 0.5f + GetMaxElementSize();
	}
	void GetBound( SBound *pRes ) const
	{
		float fHalfSize = fSize * 0.5;
		float fS = fHalfSize + GetMaxElementSize();
		pRes->BoxExInit( ptBase + CVec3( fHalfSize, fHalfSize, fHalfSize ), CVec3(fS,fS,fS) );
	}

	TFinal* GetUpLink() const { return pUpLink; }
	TFinal* GetNode( int nIdx ) { ASSERT( nIdx >= 0 && nIdx < 8 ); return links[nIdx]; }
	TFinal* GetNode( const CVec3 &ptCenter, float fRadius )
	{
		TFinal *pThis = static_cast<TFinal*>( this );
		float fLowerSize = 0.5f * GetMaxElementSize();
		if ( fSize <= N_MIN_NODE || fRadius >= fLowerSize )
			return pThis;
		else
		{
			int nIdx = 0;
			if ( ptCenter.x >= ptBase.x + fSize * 0.5f )
				nIdx += 1;
			if ( ptCenter.y >= ptBase.y + fSize * 0.5f )
				nIdx += 2;
			if ( ptCenter.z >= ptBase.z + fSize * 0.5f )
				nIdx += 4;
			if ( !links[nIdx] )
			{
				CVec3 ptNewBase( ptBase );
				if ( nIdx & 1 )
					ptNewBase.x += fSize * 0.5f;
				if ( nIdx & 2 )
					ptNewBase.y += fSize * 0.5f;
				if ( nIdx & 4 )
					ptNewBase.z += fSize * 0.5f;
				TFinal *pNewFinal = new TFinal;
				pNewFinal->SetSize( ptNewBase, fSize * 0.5f );
				links[nIdx] = pNewFinal;
				pNewFinal->SetUpLink( pThis );
			}
			return links[nIdx]->GetNode( ptCenter, fRadius );
		}
	}
	int operator&( IBinSaver &f )
	{
		f.Add( 1, &ptBase );
		f.Add( 2, &fSize );
		for ( int i = 0; i < 8; ++i )
			f.Add( 10 + i, &links[i] );
		f.Add( 20, &pUpLink );
		return 0;
	}
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

