#ifndef __STACK_H_INCLUDED__358460__
#define __STACK_H_INCLUDED__358460__

#include "System/Node/Config.h"
#include <assert.h>

namespace nvl {

	struct CStackableEntity {

		CStackableEntity(): m_pNextEntity( NULL )
		{}

		template< typename T > void GetNextEntity( T * &pNextEntity ) const
		{
			assert( NULL == m_pNextEntity || 0 != dynamic_cast< T * >( m_pNextEntity ) );
			pNextEntity = static_cast< T * >( m_pNextEntity );
		}

		template< typename T > T * GetNextEntity() const
		{
			assert( NULL == m_pNextEntity || 0 != dynamic_cast< T * >( m_pNextEntity ) );
			return static_cast< T * >( m_pNextEntity );
		}

		void SetNextEntity( CStackableEntity * pNextEntity )
		{ m_pNextEntity = pNextEntity; }

		virtual void DestroyEntity() = 0;

	protected:

		CStackableEntity * m_pNextEntity;

	};

	inline void DestroyStack( CStackableEntity * pStack )
	{
		while ( pStack ) {

			CStackableEntity * pNode = pStack;
			pStack = pNode->GetNextEntity< CStackableEntity >();
			pNode->SetNextEntity( NULL );
			pNode->DestroyEntity();

		}
	}

	template< typename T > T * ReverseStack( T * pStack )
	{
		T * pPreviousEntity = NULL;
		while ( pStack ) {

			T * pNextEntity = pStack->template GetNextEntity< T >();
			pStack->SetNextEntity( pPreviousEntity );
			pPreviousEntity = pStack;
			pStack = pNextEntity;

		}

		return pPreviousEntity;
	}

	template< typename T > T * FindLastStackEntity( T * pStack )
	{
		if ( pStack ) {

			while ( pStack->template GetNextEntity< T >() )
				pStack = pStack->template GetNextEntity< T >();

			return pStack;

		}

		return NULL;
	}

	template< typename T > class CStack
	{
	private:

		CStack( CStack const & );
		CStack & operator = ( CStack const & );

	public:

		CStack(): m_pStackHead( NULL )
		{}

		~CStack()
		{ DestroyStack( m_pStackHead ); }

		void Push( T * pEntity )
		{
			assert( NULL != pEntity );

			pEntity->SetNextEntity( m_pStackHead );
			m_pStackHead = pEntity;
		}

		void PushStack( T * pStack )
		{
			assert( NULL != pStack );

			if ( m_pStackHead )
				FindLastStackEntity( pStack )->SetNextEntity( m_pStackHead );

			m_pStackHead = pStack;
		}

		T * Pop()
		{
			T * pEntity = m_pStackHead;

			if ( pEntity )
				m_pStackHead = pEntity->template GetNextEntity< T >();

			return pEntity;
		}

		T * PopStack()
		{
			T * pEntity = m_pStackHead;
			m_pStackHead = NULL;

			return pEntity;
		}

		T * PopReversedStack()
		{ return ReverseStack( PopStack() ); }

		bool IsEmpty() const
		{ return NULL == m_pStackHead; }

	private:

		T * m_pStackHead;

	};

}

#endif // __STACK_H_INCLUDED__358460__
