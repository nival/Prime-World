#include "systemStdAfx.h"
#include "System/nalgoritm.h"


#pragma warning(disable:4239)

namespace nstl
{

struct DefaultAllocator
{
  void Deallocate(void* address) {}
  template <typename T> T* Allocate() { return 0; }
};

template< class T, class AllocatorType = DefaultAllocator>
class LockFreeQueue
{
private:

	// pointer structure
	struct node_t;

	struct pointer_t 
	{
		node_t* ptr;
		LONG count;
		// default to a null pointer with a count of zero
		pointer_t(): ptr(NULL),count(0){}
		pointer_t(node_t* node, const LONG c ) : ptr(node),count(c){}
		pointer_t(const pointer_t& p)
		{
			nival::interlocked_exchange( count, p.count );
			nival::interlocked_exchange_pointer( ptr, p.ptr );
		}

		pointer_t(const pointer_t* p): ptr(NULL),count(0)
		{
			if(NULL == p)
				return;

			nival::interlocked_exchange( count, p->count );
			nival::interlocked_exchange_pointer( ptr, const_cast< node_t* >(p->ptr) );
		}

	};

	// node structure
	struct node_t 
	{
		T value;
		pointer_t next;
		// default constructor
		node_t(){}
	};

	pointer_t Head;
	pointer_t Tail;
  AllocatorType* allocator;
	bool CAS(pointer_t& dest, pointer_t compare, pointer_t value)
	{
		if(compare.ptr==nival::interlocked_compare_exchange_pointer( dest.ptr, value.ptr, compare.ptr ))
		{
			nival::interlocked_exchange( dest.count, value.count );
			return true;
		}
		return false;
	}
  node_t* Allocate()
  {
    return allocator?allocator->template Allocate<node_t>():new node_t();
  }

  void Deallocate(node_t* instance)
  {
    allocator?allocator->Deallocate(instance):delete instance;
  }
public:	
	// default constructor
  LockFreeQueue(AllocatorType* _allocator=0):
  allocator(_allocator)
	{
		node_t* pNode = Allocate();
		Head.ptr = Tail.ptr = pNode;
	}

	~LockFreeQueue()
	{
		// remove the dummy head
    node_t* head = Head.ptr;
    while (true)
    {
      pointer_t next = head->next;
      Deallocate(head);
      if (next.ptr)
      {
        head = next.ptr;
      } else
      {
        break;
      }
    }
    
	}

	// insert items of class T in the back of the queue
	// items of class T must implement a default and copy constructor
	// Enqueue method
	void enqueue(const T& t)
	{
		// Allocate a new node from the free list
		node_t* pNode = Allocate(); 

		// Copy enqueued value into node
		pNode->value = t;

		// Keep trying until Enqueue is done
		bool bEnqueueNotDone = true;

		while(bEnqueueNotDone)
		{
			// Read Tail.ptr and Tail.count together
			pointer_t tail(Tail);

			bool nNullTail = (NULL==tail.ptr); 
			// Read next ptr and count fields together
			pointer_t next( // ptr 
							(nNullTail)? NULL : tail.ptr->next.ptr,
							// count
							(nNullTail)? 0 : tail.ptr->next.count
							) ;


			// Are tail and next consistent?
			if(tail.count == Tail.count && tail.ptr == Tail.ptr)
			{
				if(NULL == next.ptr) // Was Tail pointing to the last node?
				{
					// Try to link node at the end of the linked list										
					if(CAS( tail.ptr->next, next, pointer_t(pNode,next.count+1) ) )
					{
						bEnqueueNotDone = false;
					} // endif

				} // endif

				else // Tail was not pointing to the last node
				{
					// Try to swing Tail to the next node
					CAS(Tail, tail, pointer_t(next.ptr,tail.count+1) );
				}

			} // endif

		} // endloop
	}

	// remove items of class T from the front of the queue
	// items of class T must implement a default and copy constructor
	// Dequeue method
	bool dequeue(T& t)
	{
		pointer_t head;
		// Keep trying until Dequeue is done
		bool bDequeNotDone = true;
		while(bDequeNotDone)
		{
			// Read Head
			head = Head;
			// Read Tail
			pointer_t tail(Tail);

			if(head.ptr == NULL)
			{
				// queue is empty
				return false;
			}

			// Read Head.ptr->next
			pointer_t next(head.ptr->next);

			// Are head, tail, and next consistent
			if(head.count == Head.count && head.ptr == Head.ptr)
			{
				if(head.ptr == tail.ptr) // is tail falling behind?
				{
					// Is the Queue empty
					if(NULL == next.ptr)
					{
						// queue is empty cannot deque
						return false;
					}
					CAS(Tail,tail, pointer_t(next.ptr,tail.count+1)); // Tail is falling behind. Try to advance it
				} // endif

				else // no need to deal with tail
				{
					// read value before CAS otherwise another deque might try to free the next node
					t = next.ptr->value;

					// try to swing Head to the next node
					if(CAS(Head,head, pointer_t(next.ptr,head.count+1) ) )
					{
						bDequeNotDone = false;
					}
				}

			} // endif

		} // endloop
		
		// It is now safe to free the old dummy node
		Deallocate(head.ptr);
		// queue was not empty, deque succeeded
		return true;
	}
};

}