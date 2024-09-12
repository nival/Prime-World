
#ifndef __TSLIST_H_
#define __TSLIST_H_

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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

	CTSList ( const CTSList<T> & ) {}
public:
	CTSList()
	{
		pFirst = new SData();
		pLast = pFirst;
	}

	virtual ~CTSList()
	{
		while ( !IsEmpty() )
			PopFront();
		delete pLast;
	}

	// Thread 1 only
	virtual T* GetBack()
	{
		return &pLast->data;
	}

	virtual void PushBack()
	{
		pLast->pNext = new SData;
		pLast = pLast->pNext;
	}

	// Thread 2 only
	virtual bool IsEmpty() const
	{
		return pFirst == pLast;
	}

	virtual T* GetFront(int nI = 0)
	{
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

#endif   //__TSLIST_H_
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

