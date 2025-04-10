/*********************************************************************
** Copyright (C) 2003 Terabit Pty Ltd.  All rights reserved.
**
** This file is part of the POSIX-Proactor module.
**
**  
**   
**
**
**
** @author Alexander Libman <libman@terabit.com.au>
**
**********************************************************************/

#ifndef TERABIT_SINGLE_LIST_T_H
#define TERABIT_SINGLE_LIST_T_H

#include /**/ "ace/pre.h"


#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include <functional>
#include <algorithm>

#include "ace/Log_Msg.h"

ACE_BEGIN_VERSIONED_NAMESPACE_DECL


template <typename X> class LinkS_T;
template <typename X> class LinkD_T;

template <typename X, typename F> class Single_List_T;
template <typename X, typename F> class Single_Queue_T;
template <typename X, typename F> class Double_List_T;

//============================================================
//
//
//============================================================
template <typename X> 
class LinkS_T
{
private:
 
    template <typename > friend class LinkD_T;
    template <typename , typename > friend class Single_List_T;
    template <typename , typename > friend class Single_Queue_T;
    template <typename , typename > friend class Double_List_T;

public:
   
    static X * end ();
    
    ~LinkS_T () {}
    LinkS_T () : ptr_ (0) {}

    X * get() const { return ptr_;}
    X * operator-> () const { return ptr_;}

    bool is_free () const { return ptr_ == 0; }
    bool is_end () const  { return ptr_ == end (); }


private:
    void set (X * x)   
    { 
         //ACE_ASSERT (x != 0);
         ptr_ = x;
    }

    void set_free ()   { ptr_ = 0; }
    void set_end  ()   { ptr_ = end ();} 



    LinkS_T (X * x) : ptr_ (x) {}

    X * ptr_;
};

template <typename X> 
inline X * 
LinkS_T<X>::end () 
{ 
    return (X*) (-1L);
}

//------------------------------------------------------------
// class that converts X reference to LinkS_T<X> reference
//------------------------------------------------------------

template <class X> 
class LinkS_Functor_T :  public std::unary_function < X, LinkS_T <X> > 
{
public :
    LinkS_T <X> *  operator ()( const X * x )  const 
    {
        return  const_cast < X* > (x);
    }
};

//============================================================
//
//
//============================================================

template < class X, class F = LinkS_Functor_T <X> >
class Single_List_T 
{
public: 
    typedef Single_List_T<X,F> List;
    typedef LinkS_T<X>         Link;

    class iterator 
    {
        friend class  Single_List_T<X,F>;

        iterator(X * x) : x_ (x)  {;}
        iterator(const Link & link) : x_ (link.get())  {;}
 
    public:
        ~iterator () {}

        iterator () : x_ (0) {;}

        iterator(const iterator & other ) 
        : x_ (other.x_)
        {;}


        iterator & operator = (const iterator & other )
        {
            x_ = other.x_;
            return *this;
        }

        bool operator == (const iterator & other )const
        {
            return (x_ == other.x_ );
        }

        bool operator != (const iterator & other )const
        {
            return (x_ != other.x_ );
        }

        iterator & operator ++ ();
        iterator operator ++ (int);

        operator X *   () const { return x_; }
        X * operator * () const { return x_; }

   
    private:
   
        X *    x_;
    };

    Single_List_T () : head_ (Link::end())
    {}

    bool empty () const  { return head_.is_end(); }
    size_t size() const;

    void push_front (X * x);
    void push_back  (X * x);

    X * pop_front ();
    X * pop_back  ();

    X * front ();
    X * back  ();

    X * find (X *x);
    X * remove (X *x);


    iterator begin() const { return iterator (head_);}
    iterator end ()  const { return iterator (Link::end());}

    void swap   (Single_List_T<X, F>  & other);

    template < class Other_List_T >
    void splice (Other_List_T  & other);

private:
    friend class iterator;
            
    /// Protect from copy and assignment
    Single_List_T  (const Single_List_T<X, F>  & other);
    Single_List_T & operator= (const Single_List_T <X, F> & other);

    // functor that converts object pointer to link pointer
    // does it make sense to have non-static converter ??
    static Link * get_link (const X * x);

    static X *    get_next (const X * x);


    Link          head_;
};

//-----------------------------------------------------
//   Single_List_T::iterator
//-----------------------------------------------------
template <class X, class F>
inline typename Single_List_T<X,F>::iterator &
Single_List_T<X,F>::iterator::operator ++()
{
    // behavior unpredictable if iterator not valid
    this->x_ =  Single_List_T<X,F>::get_next (this->x_);
    return *this;
}
   
template <class X, class F>
inline typename Single_List_T<X,F>::iterator 
Single_List_T<X,F>::iterator::operator ++(int)
{
    // behavior unpredictable if iterator not valid
    iterator itr (*this);
    ++(*this);
    return itr;
}
 
//-----------------------------------------------------
//    Single_List_T
//-----------------------------------------------------

template <class X, class F>
inline typename Single_List_T<X,F>::Link * 
Single_List_T<X,F>::get_link (const X * x)
{
    ACE_ASSERT (x != 0 &&  x != Link::end() );
    static F funcObj2Link;
    return funcObj2Link (x);
}

template <class X, class F>
inline X * 
Single_List_T<X,F>::get_next (const X * x)
{
    return get_link (x)->get ();
}


template <class X, class F>
inline void
Single_List_T<X,F>::push_front (X * x)
{
    //ACE_ASSERT (x != 0 && x != Link::end() && head_.get() != 0);

    Link * link = get_link (x);
    ACE_ASSERT (link->is_free());

    link->set (head_.get());
    head_.set (x);
}

template <class X, class F>
inline void
Single_List_T<X,F>::push_back (X * x) 
{
    //ACE_ASSERT (x != 0 && x != Link::end() && head_.get() != 0);

    Link * link = get_link (x);
    ACE_ASSERT (link->is_free());

    Link * linkLast = &head_;

    while (!linkLast->is_end())
    {
        linkLast = get_link (linkLast->get());
    }

    linkLast->set (x);
    link->set_end ();
}

template <class X, class F>
inline X *
Single_List_T<X,F>::front ()
{
    X * x = head_.get();

    if (x != Link::end())
    {
        return x;
    }
    return  0;
}

template <class X, class F>
inline X *
Single_List_T<X,F>::back ()
{
    X * x = 0;
    
    iterator it1 = begin();
    iterator it2 = end();

    for (; it1 !=it2 ; ++it1)
    {
        x = *it1;
    }
    return x;
}

template <class X, class F>
inline size_t
Single_List_T<X,F>::size () const
{
    size_t count =0;
    iterator it1 = begin();
    iterator it2 = end();

    for (; it1 !=it2 ; ++count, ++it1)
    {
    }

    return count;
}

template <class X, class F>
inline X *
Single_List_T<X,F>::pop_front ()
{
    X * x = head_.get();

    if (x == Link::end ())
    {
        return 0;
    }

    //ACE_ASSERT (x != 0 );
    //ACE_ASSERT (this->get_next (x) != 0);

    head_.set (this->get_next(x));
    this->get_link(x)->set_free();

    ACE_ASSERT (head_.get() != 0);
    return x;
}

template <class X, class F>
inline X *
Single_List_T<X,F>::pop_back ()
{
    X * x = 0;
    Link * prevLink = &head_;
    if (prevLink->is_end ())
    {
        return x;
    }

    for (;;)
    {
        x = prevLink->get ();
        Link * nextLink = this->get_link (x);
        if (nextLink->is_end ())
        {
            break;
        }
        prevLink = nextLink;
    }
    prevLink->set_end ();
    get_link(x)->set_free();

    //ACE_ASSERT (x != 0 && x != Link::end() && head_.get() != 0);
    return x;
}

template <class X, class F>
inline void
Single_List_T<X,F>::swap (Single_List_T<X,F>  & other)
{
    if (&other == this)
        return;

    std::swap (head_, other.head_);
}

template <class X, class F>
inline X *
Single_List_T<X,F>::find (X *x)
{
  if (x == 0)
    return 0;
  
  iterator it1 = begin();
  iterator it2 = end();

  for (; it1 != it2 ; ++it1)
    {
      if (x == *it1)
        return x;
    }

    return 0;
}

template <class X, class F>
inline X *
Single_List_T<X,F>::remove (X *x)
{
  if (x == 0)
    return 0;
  
  Link * link_x = get_link (x);
  Link * link_cur = &this->head_;

  for (;;)
    {
      X *next = link_cur->get ();

      if (next == Link::end())
        break; // not found

      if (next == x)
        {
          link_cur->set (link_x->get ());
          link_x->set_free ();
          return x;
        }
      link_cur = get_link (next);
    }
  return 0;
}

template < class X, class F >
template < class Other_List_T >
inline void
Single_List_T<X,F>::splice (Other_List_T & other)
{
    X * x = other.front ();
    if (x == 0)
        return;

    Link * linkLast = &head_;

    if (linkLast->get() == x)
    {
        return; // the same
    }

    while(!linkLast->is_end())
    {
        linkLast = get_link (linkLast->get());
    }

    linkLast->set (x);

    Other_List_T tmp;
    tmp.swap (other);

    //other.head_.set_end();
}


//============================================================
//
//
//============================================================

template <class X, class F = LinkS_Functor_T <X> >
class Single_Queue_T 
{
public: 
    typedef Single_Queue_T<X,F> Queue;
    typedef LinkS_T<X>          Link;

    class iterator 
    {
        friend class Single_Queue_T<X,F>;

        iterator(X * x) : x_ (x)  {;}
        iterator(const Link & link) : x_ (link.get())  {;}
 
    public:
        ~iterator () {}

        iterator () : x_ (0) {;}

        iterator(const iterator & other ) 
        : x_ (other.x_)
        {;}


        iterator & operator = (const iterator & other )
        {
            x_ = other.x_;
            return *this;
        }

        bool operator == (const iterator & other )const
        {
            return (x_ == other.x_ );
        }

        bool operator != (const iterator & other )const
        {
            return (x_ != other.x_ );
        }

        iterator & operator ++ ();
        iterator operator ++ (int);

        operator X *   () const { return x_; }
        X * operator * () const { return x_; }

   
    private:
   
        X *    x_;
    };

    Single_Queue_T () 
        : head_ (Link::end())
        , tail_ (Link::end())
        , size_ (0)
    {}

    bool empty () const  { return (size_ == 0); }
    size_t size() const  { return size_;}

    void push_front (X * x);
    void push_back  (X * x);

    X * pop_front ();
    X * pop_back  ();

    X * front ();
    X * back  ();

    X * find (X *x);
    X * remove (X *x);

    void swap   (Single_Queue_T<X, F>  & other);

    template < class Other_List_T >
    void splice (Other_List_T  & other);

    iterator begin() const { return iterator (head_);}
    iterator end ()  const { return iterator (Link::end());}

private:
    friend class iterator;
            
    /// Protect from copy and assignment
    Single_Queue_T  (const Single_Queue_T<X, F>  & other);
    Single_Queue_T & operator= (const Single_Queue_T <X, F> & other);

    // functor that converts object pointer to link pointer
    // does it make sense to have non-static converter ??
    static Link * get_link (const X * x);

    static X *    get_next (const X * x);


    Link    head_;
    Link    tail_; 
    size_t  size_;
};

//-----------------------------------------------------
//   Single_Queue_T::iterator
//-----------------------------------------------------
template <class X, class F>
inline typename Single_Queue_T<X,F>::iterator &
Single_Queue_T<X,F>::iterator::operator ++()
{
    // behavior unpredictable if iterator not valid
    x_ =  Single_Queue_T<X,F>::get_next (x_);
    return *this;
}
   
template <class X, class F>
inline typename Single_Queue_T<X,F>::iterator 
Single_Queue_T<X,F>::iterator::operator ++(int)
{
    // behavior unpredictable if iterator not valid
    iterator itr (*this);
    ++(*this);
    return itr;
}
 
//-----------------------------------------------------
//    Single_Queue_T
//-----------------------------------------------------

template <class X, class F>
inline typename Single_Queue_T<X,F>::Link * 
Single_Queue_T<X,F>::get_link (const X * x)
{
    ACE_ASSERT (x != 0 &&  x != Link::end() );
    static F funcObj2Link;
    return funcObj2Link (x);
}

template <class X, class F>
inline X * 
Single_Queue_T<X,F>::get_next (const X * x)
{
    return get_link (x)->get ();
}


template <class X, class F>
inline void
Single_Queue_T<X,F>::push_front (X * x)
{
    //ACE_ASSERT (x != 0 && x != Link::end() && head_.get() != 0);

    Link * link = get_link (x);
    ACE_ASSERT (link->is_free());

    link->set (head_.get());
    head_.set (x);
    if (size_ == 0)
    {
        tail_ = head_;
    }
    ++size_;
}

template <class X, class F>
inline void
Single_Queue_T<X,F>::push_back (X * x) 
{
    //ACE_ASSERT (x != 0 && x != Link::end() && head_.get() != 0);

    Link * link = get_link (x);
    ACE_ASSERT (link->is_free());

    link->set (Link::end());

    if (size_ == 0)
    {
        head_.set (x);
    }
    else
    {
        get_link(tail_.get())->set (x);
    }
    tail_.set (x);
    ++size_;
}

template <class X, class F>
inline X *
Single_Queue_T<X,F>::front ()
{
    if (size_ == 0)
    {
        return 0;
    }
    return head_.get();
}

template <class X, class F>
inline X *
Single_Queue_T<X,F>::back ()
{
    if (size_ == 0)
    {
        return 0;
    }
    return tail_.get();
}

template <class X, class F>
inline X *
Single_Queue_T<X,F>::pop_front ()
{
    X * x = head_.get();

    if (x == Link::end ())
    {
        return 0;
    }

    head_.set (this->get_next(x));
    if (--size_ == 0)
    {
        tail_ = head_;
    }
        
    get_link(x)->set_free();
    return x;
}

template <class X, class F>
inline X *
Single_Queue_T<X,F>::pop_back ()
{
    if (size_ <= 1)
    {
        return pop_front ();
    }

    iterator it1 (head_);
    iterator it2 (tail_);

    X * xprev = *it1;
    X * xlast = *it2;

    for (; it1 != it2 ; ++it1)
    {
        xprev = *it1;
    }

    --size_;
    tail_.set (xprev);

    get_link(xprev)->set_end();
    get_link(xlast)->set (0);
    return xlast;
}

template <class X, class F>
inline void
Single_Queue_T<X,F>::swap (Single_Queue_T<X,F>  & other)
{
    if (&other == this)
        return;

    std::swap (head_, other.head_);
    std::swap (tail_, other.tail_);
    std::swap (size_, other.size_);
}

template <class X, class F>
inline X *
Single_Queue_T<X,F>::find (X *x)
{
  if (x == 0)
    return 0;
  
  iterator it1 = begin();
  iterator it2 = end();

  for (; it1 != it2 ; ++it1)
    {
      if (x == *it1)
        return x;
    }

    return 0;
}

template <class X, class F>
inline X *
Single_Queue_T<X,F>::remove (X *x)
{
  if (x == 0)
    return 0;

  if (head_.get () == x)
    return pop_front ();

  if (tail_.get () == x)
    return pop_back ();

  
  Link * link_x = get_link (x);
  Link * link_cur = &this->head_;

  for (;;)
    {
      X *next = link_cur->get ();

      if (next == Link::end())
        break; // not found

      if (next == x)
        {
          link_cur->set (link_x->get ());
          link_x->set_free ();

          ACE_ASSERT (this->tail_.get () != x);
          
          --this->size_;
          return x;
        }
      link_cur = get_link (next);
    }
  return 0;
}

template <class X, class F >
template < class Other_List_T >
inline void
Single_Queue_T<X,F>::splice (Other_List_T  & other)
{
    if (other.empty())
        return;

    X * x0 = this->front ();
    X * x1 = this->back ();
    X * x2 = other.front();

    if (x0 == x2) // the same
        return;

    if (x1 == 0)
    {
        head_.set (x2);
    }
    else
    {
        get_link(x1)->set (x2);
    }

    this->tail_.set (other.back());  // it is valid back()!!!
    this->size_ += other.size ();

    Other_List_T tmp;
    tmp.swap (other);

//    other.head_.set_end();
//    other.tail_.set_end();
//    other.size_ = 0;
}

ACE_END_VERSIONED_NAMESPACE_DECL

#include /**/ "ace/post.h"
#endif /* TERABIT_SINGLE_LIST_T_H */
