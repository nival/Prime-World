#ifndef _NHASHMAP_SET_H
#define _NHASHMAP_SET_H

#include "nhash_map.h"
namespace nstl
{
/////////////////////////////////////////////////////////////////////////////
//hash_set 
/////////////////////////////////////////////////////////////////////////////
template <class TElement, class THashFunc = hash<TElement> >
class hash_set : public hash_map<TElement, bool, THashFunc>
{
public:
	typedef hash_map<TElement, bool, THashFunc> CBase;
	typedef typename CBase::iterator CBaseIterator;
	typedef typename CBase::const_iterator CBaseConstIterator;

	class iterator 
	{
		CBaseIterator it;
	public:
		const TElement& operator->() const { return it->first; }
		operator const TElement*() const { return &it->first; }

		iterator() {	}
		iterator( const CBaseIterator &_it ) : it( _it ) { }
		bool operator==( const CBaseIterator &_it ) const 
		{ 
			return it == _it; 
		}
		bool operator!=( const CBaseIterator &_it ) const 
		{ 
			return it != _it; 
		}
		void operator++() { it.operator++(); }
		void operator--() { it.operator--(); }
		iterator operator++( int a ) { return it.operator++( a); }
		iterator operator--( int a ) { return it.operator--( a); }
		operator CBaseIterator() const { return it; }
	};

	class const_iterator 
	{
		CBaseConstIterator it;

	public:
		const TElement& operator->() const { return it->first; }
		operator const TElement*() const { return &it->first; }

		const_iterator() {	}
		const_iterator( const CBaseConstIterator &_it ) : it( _it ) { }
		bool operator==( const CBaseConstIterator &_it ) const 
		{ 
			return it == _it; 
		}
		bool operator!=( const CBaseConstIterator &_it ) const 
		{ 
			return it != _it; 
		}
		void operator++() { it.operator++(); }
		void operator--() { it.operator--(); }
		const_iterator operator++( int a ) { return it.operator++( a); }
		const_iterator operator--( int a ) { return it.operator--( a); }
		operator CBaseConstIterator() const { return it; }
	};

	void insert( const TElement &el )
		{	CBase::operator[]( el ) = true; }
	void remove( const TElement &el )
		{ CBase::erase( el ); }
	void remove( iterator &it )
		{	CBase::erase( it );	}

};
}

#endif

