#ifndef _PROGRESS_H_
#define _PROGRESS_H_

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
_interface IProgressHook : public CObjectBase
{
	// set number of steps in current subrange
	virtual void SetNumSteps( const int nNumSteps ) = 0;
	// lock subrange (from current position to nLength) for subsequent SetNumSteps() call
	// !-----------!-----------!-----------!-----------! <-- lock a subrange from the whole range
	//						 !---!---!---!---!---!---!						 <-- lock a subrange from the current subrange
	//										 !-----!-----!								 <-- steps will be in the current sub-subrange
	virtual void LockRange( const int nLength ) = 0;
	// unlock range
	virtual void UnlockRange() = 0;
	// do one step in progress
	virtual void Step() = 0;
	// direct set a step in the current subrange
	virtual void SetCurrentStep( int nCurrentStep ) = 0;
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NProgressHook
{
	inline void SetNumSteps( IProgressHook *pProgressHook, const int nNumSteps )
	{
		if ( pProgressHook ) pProgressHook->SetNumSteps( nNumSteps );
	}

	inline void LockRange( IProgressHook *pProgressHook, const int nLength )
	{
		if ( pProgressHook ) pProgressHook->LockRange( nLength );
	}

	inline void UnlockRange( IProgressHook *pProgressHook )
	{
		if ( pProgressHook ) pProgressHook->UnlockRange();
	}

	inline void Step( IProgressHook *pProgressHook )
	{
		if ( pProgressHook ) pProgressHook->Step();
	}

	void DebugLock( const string &szFileName, const int nLine );
	void DebugUnLock( const string &szFileName, const int nLine );
	void DebugStep( const string &szFileName, const int nLine );
	
	inline void LockRange( IProgressHook *pProgressHook, const int nLength, const string &szFileName, const int nLine )
	{
		if ( pProgressHook )
		{
			pProgressHook->LockRange( nLength );
			DebugLock( szFileName, nLine );
		}
	}

	inline void UnlockRange( IProgressHook *pProgressHook, const string &szFileName, const int nLine )
	{
		if ( pProgressHook )
		{
			pProgressHook->UnlockRange();
			DebugUnLock( szFileName, nLine );
		}
	}

	inline void Step( IProgressHook *pProgressHook, const string &szFileName, const int nLine )
	{
		if ( pProgressHook )
		{
			pProgressHook->Step();
			DebugStep( szFileName, nLine );
		}
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _SHIPPING
#define LOCK_RANGE( pProgressHook, nLength ) NProgressHook::LockRange( pProgressHook, nLength, __FILE__, __LINE__ );
#define UNLOCK_RANGE( pProgressHook ) NProgressHook::UnlockRange( pProgressHook, __FILE__, __LINE__ );
#define PROGRESS_HOOK_STEP( pProgressHook ) NProgressHook::Step( pProgressHook,	__FILE__, __LINE__ );
#else
#define LOCK_RANGE( pProgressHook, nLength ) NProgressHook::LockRange( pProgressHook, nLength );
#define UNLOCK_RANGE( pProgressHook ) NProgressHook::UnlockRange( pProgressHook );
#define PROGRESS_HOOK_STEP( pProgressHook ) NProgressHook::Step( pProgressHook );
#endif

#endif

