#ifndef _POOLEDCONTAINER_H_
#define _POOLEDCONTAINER_H_

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef _DEBUG
#define PooledListContainer_CHECK_FREE_LIST 
#endif
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
Class PooledListContainer
Хранит структуры, имеющие указатель на следующий элемент (int)
Память выделяется блоками по N_BLOCK_SIZE елементов 
указатель на следующий элемент используется также для списка свободных элементов
TElement должен содержать поле int nextElement, int prevElement, int thisElement и конструктор без параметров; 
может содержать оператор сериализации и деструктор 
*/

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class TElement, class TContainer>
struct PooledIterator
{
	typedef PooledIterator<TElement, TContainer> _Self;

  TContainer* container;
  TElement* element;

  PooledIterator( TContainer* _container, TElement* _element ) : container(_container), element(_element) {}
  PooledIterator() : container(0), element(0) {}

  TElement& operator*() const { return *element; }
  TElement* operator->() const { return element; }

  _Self& operator++() 
  {
    element =  &( container->GetNext( *element ) );
    return *this;
  }

  _Self operator++( int ) 
  {
    PooledIterator __tmp = *this;
    element =  &container->GetNext( *element );
    return __tmp;
  }

  bool operator==( const PooledIterator& __y ) const { return element->thisElement == __y.element->thisElement; }
  bool operator!=( const PooledIterator& __y ) const { return element->thisElement != __y.element->thisElement; }
  void operator=( const PooledIterator& __y ) { container = __y.container; element = __y.element; }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class TElement, int N_BLOCK_SIZE = 4096>
class PooledContainer
{
public:
	typedef int TPtr;

  typedef PooledIterator<TElement, PooledContainer> iterator; 
  typedef PooledIterator<const TElement, const PooledContainer> const_iterator; 

  static const TPtr Null = (TPtr)-1;
private:
	struct SBlock
	{
		vector<TElement> data;
		SBlock(): data( N_BLOCK_SIZE, TElement() ) {}
	};

public:

	void operator=( const PooledContainer &a )
	{
		Clear();
		for ( int i = 0; i < a.data.size(); ++i )
		{
			Alloc();
			for ( int j = 0; j < a.data[i].data.size(); ++j )
				data[i].data[j] = a.data[i].data[j];
			freeListHead = Null;
		}
		freeListHead = a.freeListHead;
	}

	PooledContainer( const PooledContainer &a ) 
  { 
    operator=( a ); 
  }

#ifdef PooledListContainer_CHECK_FREE_LIST
	bool IsInFreeList( TPtr n ) const
	{
		TPtr next = freeListHead != Null ? 0 : Null;
		while ( next != Null )
		{
			if ( next == n )
				return true;
			next = Get( next ).nextElement;
		}
		return false;
	}
#endif

private:
		vector<SBlock> data;
	  TPtr freeListHead;
    TPtr listHead;
    TElement backElement;
public:

	PooledContainer() : freeListHead( Null ), listHead( Null ) 
  {
    backElement.thisElement = Null;
    backElement.nextElement = Null;
    backElement.prevElement = Null;
  }

	void Clear() 
  { 
    data.clear(); 
    listHead = Null;
    freeListHead = Null; 
  }

  bool Empty() 
  {
    return (listHead == Null);
  }

  iterator Begin()
  {
    return iterator( this, &Get( listHead ) );
  }

  iterator End()
  {
    return iterator( this, &backElement );
  }

  const_iterator Begin() const
  {
    return const_iterator( this, &Get( listHead ) );
  }

  const_iterator End() const
  {
    return const_iterator( this, &backElement );
  }

  TElement& Get( TPtr n )
	{
    if ( Null == n )
      return backElement;

		const int nBlock = n / N_BLOCK_SIZE;
#ifdef PooledListContainer_CHECK_FREE_LIST
		NI_VERIFY( nBlock < data.size(), "Element index outside pool", return backElement );
#else
		NI_ASSERT( nBlock < data.size(), "Element index outside pool" );
#endif
		return data[nBlock].data[ n % N_BLOCK_SIZE ];
	}

	const TElement& Get( TPtr n ) const
	{
    if ( Null == n )
      return backElement;

    const int nBlock = n / N_BLOCK_SIZE;
#ifdef PooledListContainer_CHECK_FREE_LIST
		static TElement empty;
		NI_VERIFY( nBlock < data.size(), "Element index outside pool", return backElement );
#else
		NI_ASSERT( nBlock < data.size(), "Element index outside pool" );
#endif
		return data[nBlock].data[ n % N_BLOCK_SIZE ];
	}

	TElement& GetNext( const TElement& cur )
	{
		return Get( cur.nextElement );
	}

  const TElement& GetNext( const TElement& cur ) const
  {
    return Get( cur.nextElement );
  }

  TElement& AllocAndGet()
  {
    return Get( Alloc() );
  }

  void PreAlloc()
  {
    data.push_back();
    freeListHead = ( data.size() - 1 ) * N_BLOCK_SIZE; 
    SBlock &newBlock = data.back();

    int n = 0;

    for ( ; n < ( N_BLOCK_SIZE - 1 ); ++n )
    {
      newBlock.data[n].prevElement = Null;
      newBlock.data[n].nextElement = freeListHead + n + 1;
      newBlock.data[n].thisElement = freeListHead + n;
    }

    newBlock.data[n].prevElement = Null;
    newBlock.data[n].nextElement = Null;
    newBlock.data[n].thisElement = freeListHead + n;
  }

	TPtr Alloc()
	{
		if ( freeListHead == Null ) 
		{
      PreAlloc();
		}

		TPtr newElem = freeListHead;

    TElement& element = Get( freeListHead );
		
    freeListHead = element.nextElement;
    element.nextElement = listHead;
    element.prevElement = Null;
    element.thisElement = newElem;

    if ( Null != listHead )
    {
      Get( listHead ).prevElement = newElem;
    }

    listHead = newElem;

		return newElem;
	}

  iterator Free( iterator it )
  {
    iterator next = it;

    next++;

    Free( it->thisElement );

    return next;
  }

	void Free( TPtr n )
	{
#ifdef PooledListContainer_CHECK_FREE_LIST
//		NI_VERIFY( IsInFreeList( n ), "Freing already free element", return )
#endif

		TElement& elem = Get( n );

    if ( Null != elem.prevElement )
    {
      Get( elem.prevElement ).nextElement = elem.nextElement;
    }
    else
    {
      NI_ASSERT( elem.thisElement == listHead, "Has Null prevElement, but is not list head" );
      listHead = elem.nextElement;
    }

    if ( Null != elem.nextElement )
    {
      Get( elem.nextElement ).prevElement = elem.prevElement;
    }

		elem.TElement::~TElement();
		new(&elem) TElement();	

		elem.nextElement = freeListHead;
		freeListHead = n;
	}
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

