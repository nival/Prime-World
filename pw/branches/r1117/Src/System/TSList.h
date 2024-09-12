
#ifndef __TSLIST_H_
#define __TSLIST_H_

#include "interlocked.h"

//#define DEBUG_TSLIST_HEAVY  1
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
template<class T> 
class CTSList
{
	struct SData
	{
		T data;
		SData* pNext;
    SData(): data(), pNext(NULL) {}
	};

	SData *pFirst;
	SData *pLast;
#ifdef DEBUG_TSLIST_HEAVY
  mutable int pushThreadID;
  mutable int popThreadID;
#endif
	CTSList ( const CTSList<T> & ) {}
public:
	CTSList()
	{
		pFirst = new SData();
		pLast = pFirst;
#ifdef DEBUG_TSLIST_HEAVY
    pushThreadID = -1;
    popThreadID = -1;
#endif
  }

	virtual ~CTSList()
	{
#ifdef DEBUG_TSLIST_HEAVY
    popThreadID = -1;
#endif
		while ( !IsEmpty() )
			PopFront();
		delete pLast;
	}

	// Thread 1 only
	virtual T* GetBack()
	{
#ifdef DEBUG_TSLIST_HEAVY
    if ( pushThreadID == -1 )
      pushThreadID = ::GetCurrentThreadId();
    NI_ASSERT( (DWORD)pushThreadID == ::GetCurrentThreadId(), "TSList misuse: pushed by two threads" );
#endif
		return &pLast->data;
	}

	virtual void PushBack()
	{
#ifdef DEBUG_TSLIST_HEAVY
    if ( pushThreadID == -1 )
      pushThreadID = ::GetCurrentThreadId();
    NI_ASSERT( (DWORD)pushThreadID == ::GetCurrentThreadId(), "TSList misuse: pushed by two threads" );
#endif
    SData* p = pLast;
    pLast = new SData;
		p->pNext = pLast;
	}

	// Thread 2 only
	virtual bool IsEmpty() const
	{
#ifdef DEBUG_TSLIST_HEAVY
    if ( popThreadID == -1 )
      popThreadID = ::GetCurrentThreadId();
    NI_ASSERT( (DWORD)popThreadID == ::GetCurrentThreadId(), "TSList misuse: popped by two threads" );
#endif

		return pFirst == pLast;
	}

	virtual T* GetFront(int nI = 0)
	{
#ifdef DEBUG_TSLIST_HEAVY
    if ( popThreadID == -1 )
      popThreadID = ::GetCurrentThreadId();
    NI_ASSERT( (DWORD)popThreadID == ::GetCurrentThreadId(), "TSList misuse: popped by two threads" );
#endif

    SData *p = pFirst;
    while(nI > 0 && p->pNext != NULL)
    {
      p = p->pNext;
      nI--;
    }
    if(nI == 0 && p->pNext != NULL)
    {
		  return &p->data;
    }
    else
    {
      return NULL;
    }
	}

  virtual T const * GetFront(int nI = 0) const
  {
#ifdef DEBUG_TSLIST_HEAVY
    if ( popThreadID == -1 )
      popThreadID = ::GetCurrentThreadId();
    NI_ASSERT( (DWORD)popThreadID == ::GetCurrentThreadId(), "TSList misuse: popped by two threads" );
#endif

    SData *p = pFirst;
    while(nI > 0 && p->pNext != NULL)
    {
      p = p->pNext;
      nI--;
    }
    if(nI == 0 && p->pNext != NULL)
    {
      return &p->data;
    }
    else
    {
      return NULL;
    }
  }

	virtual void PopFront(int nI = 0)
	{
#ifdef DEBUG_TSLIST_HEAVY
    if ( popThreadID == -1 )
      popThreadID = ::GetCurrentThreadId();
    NI_ASSERT( (DWORD)popThreadID == ::GetCurrentThreadId(), "TSList misuse: popped by two threads" );
#endif

    SData *pTemp = NULL;
    SData **ppNF = &pFirst;
    pTemp = (*ppNF)->pNext;
    NI_ASSERT(pTemp != NULL, "popping from empty list");
    while(nI > 0 && (*ppNF)->pNext != NULL)
    {
      NI_ASSERT((*ppNF)->pNext != NULL, "popping unexistent item");
      ppNF = &(*ppNF)->pNext;
      pTemp = (*ppNF)->pNext;
      nI --;
    }
    NI_ASSERT((*ppNF)->pNext != NULL, "popping from empty list");
		delete (*ppNF);
		(*ppNF) = pTemp;
	}
};
*/
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
@brief Single-producer, single-consumer thread-safe queue

Uses dynamic memory allocation, but holds unused memory in second queue and re-uses it

@param T Containing data type
@param TIn Type of data to pass to Enqueue function. Useful when T is smart-pointer.
@param TOut Type of data to return from Dequeue function. Useful when T is smart-pointer.
*/
template<class T, class TIn = T, class TOut = T> 
class SPSCQueue
{
public:

  /**
  @brief Default constructor

  @param _recycleListSize Maximum number of list nodes to hold in recycle list
  */
  SPSCQueue( int _recycleListSize = 256 )
    : size(0), recycleSize(0), recycleListSize(_recycleListSize), maxSize(0)
  {
    head = new Node();
    tail = head;
    recycleHead = new Node();
    recycleTail = recycleHead;
  }

  /**
  @brief Destructor

  @param p Pointer (defaults to NULL).
  */
  ~SPSCQueue()
  {
    T dataSink;
    while ( Dequeue( dataSink ) )
      ; 

    Purge( 0 );
    NI_ASSERT( head == tail, "queue must be empty on delete" );
    NI_ASSERT( recycleHead == recycleTail, "queue must be empty on delete" );

    delete head;
    delete recycleHead;
  }

  /**
  @brief Put data into queue

  Can be accessed from producer thread only

  @param data Data 

  @return none
  */
  void Enqueue( const TIn& data )
  {
    Node* n = Allocate( data );
    nival::interlocked_exchange_pointer( head->next, n );
    head = n;
    nival::interlocked_increment( size );
    maxSize = max( size, maxSize );
  }

  /**
  @brief Retrieve data from queue

  Can be accessed from consumer thread only 

  @param data Place to hold retrieved value 

  @note when function returns false, contents of data is not changed

  @return false if queue is empty; true otherwise
  */
  bool Dequeue( TOut& data )
  {
    Node* t = tail;
    Node* n = (Node*)(t->next);
    if ( n == 0 )
      return false;
    data = n->data;
    n->Cleanup();
    Recycle( t );
    tail = n;
    nival::interlocked_decrement( size );
    return true;
  }

  /**
  @brief Retrieve data from queue, but do not dequeue

  Can be accessed from consumer thread only 

  @param data Place to hold retrieved value 

  @note when function returns false, contents of data is not changed

  @return false if queue is empty; true otherwise
  */
  bool Pick( TOut& data )
  {
    Node* t = tail;
    Node* n = (Node*)(t->next);
    if ( n == 0 )
      return false;
    data = n->data;
    return true;
  }

  /**
  @brief Get number of elements in queue

  @return number of elements in queue
  */
  int Size() const { return size; }

  /**
  @brief Get number of allocated elements (in both queue and recycle list)

  @return umber of allocated elements
  */
  int Allocated() const { return size + recycleSize; }

private:
  struct Node
  {
    T data;
    volatile Node* next;

    Node( T _data = T() )
      : next( 0 ), data( _data )
    {}
    void Cleanup()
    {
      data.~T();
      new(&data) T(); 
    }
    void Init( T _data )
    {
      new(&data) T( _data );
      next = 0;
    }
  };

  Node* head;
  Node* tail;
  volatile LONG size;
  volatile LONG maxSize;

  Node* recycleHead; 
  Node* recycleTail; 
  volatile LONG recycleSize;
  int recycleListSize;

  void Recycle( Node* n )
  {
    n->next = 0;
    nival::interlocked_exchange_pointer( recycleHead->next, n );
    recycleHead = n;
    nival::interlocked_increment( recycleSize );
  }

  Node* Allocate( const T& data = T() )
  {
    Node* t = recycleTail;
    Node* n = (Node*)(t->next);
    if ( n == 0 )
      return new Node( data );

    recycleTail = n;

    t->Init( data );

    nival::interlocked_decrement( recycleSize );

    if ( recycleSize > recycleListSize )
      Purge( recycleListSize / 2 );

    return t;
  }

  void Purge( int newSize ) 
  {
    while( recycleSize > newSize )
    {
      Node* t = recycleTail;
      Node* n = (Node*)(t->next);
      if ( n == 0 )
        break;

      delete t;
      recycleTail = n;
      nival::interlocked_decrement( recycleSize );
    }
  }
};
#endif   //__TSLIST_H_
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

