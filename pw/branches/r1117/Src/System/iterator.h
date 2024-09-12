#ifndef _ITERATOR_H_
#define _ITERATOR_H_

namespace nstl
{
	template <class _Container>
	class insert_iterator 
	{
	protected:
		_Container* container;
		typename _Container::iterator iter;
	public:
		typedef _Container					container_type;

		insert_iterator(_Container& __x, typename _Container::iterator __i) 
			: container(&__x), iter(__i) {}

		insert_iterator<_Container>& operator=(const typename _Container::value_type& __value)
		{ 
			iter = container->insert(iter, __value);
			++iter;
			return *this;
		}
				
		insert_iterator<_Container>& operator*() { return *this; }
		insert_iterator<_Container>& operator++() { return *this; }
		insert_iterator<_Container>& operator++(int) { return *this; }
	};

	template<class _Container,
		class _Iter> inline
		insert_iterator<_Container> inserter(_Container& _Cont, _Iter _Where)
		{
			return insert_iterator<_Container>(_Cont, _Where);
		}
}

#endif	// _ITERATOR_H_

