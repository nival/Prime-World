#ifndef N_ITERATOR_H
#define N_ITERATOR_H

namespace nstl
{
template <class _Container>
class back_insert_iterator
  //: public iterator<output_iterator_tag, void, void, void, void> 
{
  typedef back_insert_iterator<_Container> _Self;
protected:
  //c is a Standard name (24.4.2.1), do no make it STLport naming convention compliant.
  _Container *container;
public:
  typedef _Container          container_type;
  //typedef output_iterator_tag iterator_category;

  explicit back_insert_iterator(_Container& __x) : container(&__x) {}

  _Self& operator=(const _Self& __other) {
    container = __other.container;
    return *this;
  }
  _Self& operator=(const typename _Container::value_type& __val) {
    container->push_back(__val);
    return *this;
  }
  _Self& operator*() { return *this; }
  _Self& operator++() { return *this; }
  _Self  operator++(int) { return *this; }
};

template <class _Container>
inline back_insert_iterator<_Container> back_inserter(_Container& __x)
{ return back_insert_iterator<_Container>(__x); }

template <class _Container>
class front_insert_iterator
  //: public iterator<output_iterator_tag, void, void, void, void> 
{
  typedef front_insert_iterator<_Container> _Self;
protected:
  //c is a Standard name (24.4.2.3), do no make it STLport naming convention compliant.
  _Container *container;
public:
  typedef _Container          container_type;
  //typedef output_iterator_tag iterator_category;
  explicit front_insert_iterator(_Container& __x) : container(&__x) {}

  _Self& operator=(const _Self& __other) {
    container = __other.container;
    return *this;
  }
  _Self& operator=(const typename _Container::value_type& __val) {
    container->push_front(__val);
    return *this;
  }
  _Self& operator*() { return *this; }
  _Self& operator++() { return *this; }
  _Self  operator++(int) { return *this; }
};

template <class _Container>
inline front_insert_iterator<_Container> front_inserter(_Container& __x)
{ return front_insert_iterator<_Container>(__x); }

}



#endif