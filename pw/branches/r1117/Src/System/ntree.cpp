/*
 *
 *
 * Copyright (c) 1994
 * Hewlett-Packard Company
 *
 * Copyright (c) 1996,1997
 * Silicon Graphics Computer Systems, Inc.
 *
 * Copyright (c) 1997
 * Moscow Center for SPARC Technology
 *
 * Copyright (c) 1999 
 * Boris Fomitchev
 *
 * This material is provided "as is", with absolutely no warranty expressed
 * or implied. Any use is at your own risk.
 *
 * Permission to use or copy this software for any purpose is hereby granted 
 * without fee, provided the above notices are retained on all copies.
 * Permission to modify the code and to distribute modified code is granted,
 * provided the above notices are retained, and a notice that the code was
 * modified is included with the above copyright notice.
 *
 * Modified CRP 7/10/00 for improved conformance / efficiency on insert_unique /
 * insert_equal with valid hint -- efficiency is improved all around, and it is
 * should now be standard conforming for complexity on insert point immediately
 * after hint (amortized constant time).
 *
 */
//#ifndef _STLP_TREE_C
//#define _STLP_TREE_C

#include "stdafx.h"
#include "ntree.h"

namespace nstl
{

// fbp: these defines are for outline methods definitions.
// needed for definitions to be portable. Should not be used in method bodies.
/*
# if defined	( _STLP_NESTED_TYPE_PARAM_BUG )
#	define __iterator__				_Rb_tree_iterator<_Value, _Nonconst_traits<_Value> > #	define __size_type__			 size_t
#	define iterator __iterator__
# else
*/
#	define __iterator__	typename _Rb_tree<_Key, _Value, _KeyOfValue, _Compare/*, _Alloc*/>::iterator
#	define __size_type__	typename _Rb_tree<_Key, _Value, _KeyOfValue, _Compare/*, _Alloc*/>::size_type
//# endif
/*
#if defined ( _STLP_DEBUG)
#	define _Rb_tree __WORKAROUND_DBG_RENAME(Rb_tree)
#endif
*/
//_STLP_BEGIN_NAMESPACE

//# if defined (_STLP_EXPOSE_GLOBALS_IMPLEMENTATION)

void _Rotate_left(_Rb_tree_node_base* __x, _Rb_tree_node_base*& __root)
//template <class _Dummy> void _STLP_CALL
//_Rb_global<_Dummy>::_Rotate_left(_Rb_tree_node_base* __x, _Rb_tree_node_base*& __root)
{
	_Rb_tree_node_base* __y = __x->_M_right;
	__x->_M_right = __y->_M_left;
	if (__y->_M_left !=0)
		__y->_M_left->_M_parent = __x;
	__y->_M_parent = __x->_M_parent;

	if (__x == __root)
		__root = __y;
	else if (__x == __x->_M_parent->_M_left)
		__x->_M_parent->_M_left = __y;
	else
		__x->_M_parent->_M_right = __y;
	__y->_M_left = __x;
	__x->_M_parent = __y;
}

void _Rotate_right(_Rb_tree_node_base* __x, _Rb_tree_node_base*& __root)
//template <class _Dummy> void _STLP_CALL 
//_Rb_global<_Dummy>::_Rotate_right(_Rb_tree_node_base* __x, _Rb_tree_node_base*& __root)
{
	_Rb_tree_node_base* __y = __x->_M_left;
	__x->_M_left = __y->_M_right;
	if (__y->_M_right != 0)
		__y->_M_right->_M_parent = __x;
	__y->_M_parent = __x->_M_parent;

	if (__x == __root)
		__root = __y;
	else if (__x == __x->_M_parent->_M_right)
		__x->_M_parent->_M_right = __y;
	else
		__x->_M_parent->_M_left = __y;
	__y->_M_right = __x;
	__x->_M_parent = __y;
}

void _Rebalance(_Rb_tree_node_base* __x, _Rb_tree_node_base*& __root)
//template <class _Dummy> void _STLP_CALL
//_Rb_global<_Dummy>::_Rebalance(_Rb_tree_node_base* __x, 
//						 _Rb_tree_node_base*& __root)
{
	__x->_M_color = _S_rb_tree_red;
	while (__x != __root && __x->_M_parent->_M_color == _S_rb_tree_red) {
		if (__x->_M_parent == __x->_M_parent->_M_parent->_M_left) {
			_Rb_tree_node_base* __y = __x->_M_parent->_M_parent->_M_right;
			if (__y && __y->_M_color == _S_rb_tree_red) {
				__x->_M_parent->_M_color = _S_rb_tree_black;
				__y->_M_color = _S_rb_tree_black;
				__x->_M_parent->_M_parent->_M_color = _S_rb_tree_red;
				__x = __x->_M_parent->_M_parent;
			}
			else {
				if (__x == __x->_M_parent->_M_right) {
					__x = __x->_M_parent;
					_Rotate_left(__x, __root);
				}
				__x->_M_parent->_M_color = _S_rb_tree_black;
				__x->_M_parent->_M_parent->_M_color = _S_rb_tree_red;
				_Rotate_right(__x->_M_parent->_M_parent, __root);
			}
		}
		else {
			_Rb_tree_node_base* __y = __x->_M_parent->_M_parent->_M_left;
			if (__y && __y->_M_color == _S_rb_tree_red) {
				__x->_M_parent->_M_color = _S_rb_tree_black;
				__y->_M_color = _S_rb_tree_black;
				__x->_M_parent->_M_parent->_M_color = _S_rb_tree_red;
				__x = __x->_M_parent->_M_parent;
			}
			else {
				if (__x == __x->_M_parent->_M_left) {
					__x = __x->_M_parent;
					_Rotate_right(__x, __root);
				}
				__x->_M_parent->_M_color = _S_rb_tree_black;
				__x->_M_parent->_M_parent->_M_color = _S_rb_tree_red;
				_Rotate_left(__x->_M_parent->_M_parent, __root);
			}
		}
	}
	__root->_M_color = _S_rb_tree_black;
}

_Rb_tree_node_base* _Rebalance_for_erase(_Rb_tree_node_base* __z,
																				 _Rb_tree_node_base*& __root,
																				 _Rb_tree_node_base*& __leftmost,
																				 _Rb_tree_node_base*& __rightmost)
/*
template <class _Dummy> _Rb_tree_node_base* _STLP_CALL
_Rb_global<_Dummy>::_Rebalance_for_erase(_Rb_tree_node_base* __z,
					 _Rb_tree_node_base*& __root,
					 _Rb_tree_node_base*& __leftmost,
					 _Rb_tree_node_base*& __rightmost)
*/
{
	_Rb_tree_node_base* __y = __z;
	_Rb_tree_node_base* __x = 0;
	_Rb_tree_node_base* __x_parent = 0;
	if (__y->_M_left == 0)		 // __z has at most one non-null child. y == z.
		__x = __y->_M_right;		 // __x might be null.
	else
		if (__y->_M_right == 0)	// __z has exactly one non-null child. y == z.
			__x = __y->_M_left;		// __x is not null.
		else {									 // __z has two non-null children.	Set __y to
			__y = __y->_M_right;	 //	 __z's successor.	__x might be null.
			while (__y->_M_left != 0)
				__y = __y->_M_left;
			__x = __y->_M_right;
		}
	if (__y != __z) {					// relink y in place of z.	y is z's successor
		__z->_M_left->_M_parent = __y; 
		__y->_M_left = __z->_M_left;
		if (__y != __z->_M_right) {
			__x_parent = __y->_M_parent;
			if (__x) __x->_M_parent = __y->_M_parent;
			__y->_M_parent->_M_left = __x;			// __y must be a child of _M_left
			__y->_M_right = __z->_M_right;
			__z->_M_right->_M_parent = __y;
		}
		else
			__x_parent = __y;	
		if (__root == __z)
			__root = __y;
		else if (__z->_M_parent->_M_left == __z)
			__z->_M_parent->_M_left = __y;
		else 
			__z->_M_parent->_M_right = __y;
		__y->_M_parent = __z->_M_parent;
		swap(__y->_M_color, __z->_M_color);
		__y = __z;
		// __y now points to node to be actually deleted
	}
	else {												// __y == __z
		__x_parent = __y->_M_parent;
		if (__x) __x->_M_parent = __y->_M_parent;	 
		if (__root == __z)
			__root = __x;
		else 
			if (__z->_M_parent->_M_left == __z)
				__z->_M_parent->_M_left = __x;
			else
				__z->_M_parent->_M_right = __x;
		if (__leftmost == __z) 
			if (__z->_M_right == 0)				// __z->_M_left must be null also
				__leftmost = __z->_M_parent;
		// makes __leftmost == _M_header if __z == __root
			else
				__leftmost = _Rb_tree_node_base::_S_minimum(__x);
		if (__rightmost == __z)	
			if (__z->_M_left == 0)				 // __z->_M_right must be null also
				__rightmost = __z->_M_parent;	
		// makes __rightmost == _M_header if __z == __root
			else											// __x == __z->_M_left
				__rightmost = _Rb_tree_node_base::_S_maximum(__x);
	}
	if (__y->_M_color != _S_rb_tree_red) { 
		while (__x != __root && (__x == 0 || __x->_M_color == _S_rb_tree_black))
			if (__x == __x_parent->_M_left) {
				_Rb_tree_node_base* __w = __x_parent->_M_right;
				if (__w->_M_color == _S_rb_tree_red) {
					__w->_M_color = _S_rb_tree_black;
					__x_parent->_M_color = _S_rb_tree_red;
					_Rotate_left(__x_parent, __root);
					__w = __x_parent->_M_right;
				}
				if ((__w->_M_left == 0 || 
						 __w->_M_left->_M_color == _S_rb_tree_black) && (__w->_M_right == 0 || 
						 __w->_M_right->_M_color == _S_rb_tree_black)) {
					__w->_M_color = _S_rb_tree_red;
					__x = __x_parent;
					__x_parent = __x_parent->_M_parent;
				} else {
					if (__w->_M_right == 0 || 
							__w->_M_right->_M_color == _S_rb_tree_black) {
						if (__w->_M_left) __w->_M_left->_M_color = _S_rb_tree_black;
						__w->_M_color = _S_rb_tree_red;
						_Rotate_right(__w, __root);
						__w = __x_parent->_M_right;
					}
					__w->_M_color = __x_parent->_M_color;
					__x_parent->_M_color = _S_rb_tree_black;
					if (__w->_M_right) __w->_M_right->_M_color = _S_rb_tree_black;
					_Rotate_left(__x_parent, __root);
					break;
				}
			} else {									// same as above, with _M_right <-> _M_left.
				_Rb_tree_node_base* __w = __x_parent->_M_left;
				if (__w->_M_color == _S_rb_tree_red) {
					__w->_M_color = _S_rb_tree_black;
					__x_parent->_M_color = _S_rb_tree_red;
					_Rotate_right(__x_parent, __root);
					__w = __x_parent->_M_left;
				}
				if ((__w->_M_right == 0 || 
						 __w->_M_right->_M_color == _S_rb_tree_black) && (__w->_M_left == 0 || 
						 __w->_M_left->_M_color == _S_rb_tree_black)) {
					__w->_M_color = _S_rb_tree_red;
					__x = __x_parent;
					__x_parent = __x_parent->_M_parent;
				} else {
					if (__w->_M_left == 0 || 
							__w->_M_left->_M_color == _S_rb_tree_black) {
						if (__w->_M_right) __w->_M_right->_M_color = _S_rb_tree_black;
						__w->_M_color = _S_rb_tree_red;
						_Rotate_left(__w, __root);
						__w = __x_parent->_M_left;
					}
					__w->_M_color = __x_parent->_M_color;
					__x_parent->_M_color = _S_rb_tree_black;
					if (__w->_M_left) __w->_M_left->_M_color = _S_rb_tree_black;
					_Rotate_right(__x_parent, __root);
					break;
				}
			}
		if (__x) __x->_M_color = _S_rb_tree_black;
	}
	return __y;
}

_Rb_tree_node_base* _M_decrement(_Rb_tree_node_base* _M_node)
//template <class _Dummy> _Rb_tree_node_base* _STLP_CALL
//_Rb_global<_Dummy>::_M_decrement(_Rb_tree_node_base* _M_node)
{
	if (_M_node->_M_color == _S_rb_tree_red && _M_node->_M_parent->_M_parent == _M_node)
		_M_node = _M_node->_M_right;
	else if (_M_node->_M_left != 0) {
		_Base_ptr __y = _M_node->_M_left;
		while (__y->_M_right != 0)
			__y = __y->_M_right;
		_M_node = __y;
	}
	else {
		_Base_ptr __y = _M_node->_M_parent;
		while (_M_node == __y->_M_left) {
			_M_node = __y;
			__y = __y->_M_parent;
		}
		_M_node = __y;
	}
	return _M_node;
}

_Rb_tree_node_base* _M_increment(_Rb_tree_node_base* _M_node)
//template <class _Dummy> _Rb_tree_node_base* _STLP_CALL
//_Rb_global<_Dummy>::_M_increment(_Rb_tree_node_base* _M_node)
{
	if (_M_node->_M_right != 0) {
		_M_node = _M_node->_M_right;
		while (_M_node->_M_left != 0)
			_M_node = _M_node->_M_left;
	}
	else {
		_Base_ptr __y = _M_node->_M_parent;
		while (_M_node == __y->_M_right) {
			_M_node = __y;
			__y = __y->_M_parent;
		}
		if (_M_node->_M_right != __y)
			_M_node = __y;
	}
	return _M_node;
}

//#endif /* defined (__BUILDING_STLPORT) || ! defined (_STLP_OWN_IOSTREAMS) */


// Modifications CRP 7/10/00 as noted to improve conformance and
// efficiency.

template <class _Key, class _Value, class _KeyOfValue, 
					class _Compare/*, class _Alloc*/> __iterator__ 
_Rb_tree<_Key,_Value,_KeyOfValue,_Compare/*,_Alloc*/> ::insert_equal(iterator __position, const _Value& __v)
{
	if (__position._M_node == this->_M_header._M_data->_M_left) { // begin()

		// Check for zero members
		if (size() <= 0)
				return insert_equal(__v);

		if (!_M_key_compare(_S_key(__position._M_node), _KeyOfValue()(__v)))
			return _M_insert(__position._M_node, __position._M_node, __v);
		else		{
			// Check for only one member
			if (__position._M_node->_M_left == __position._M_node)
				// Unlike insert_unique, can't avoid doing a comparison here.
				return _M_insert(0, __position._M_node, __v);
								
			// All other cases:
			// Standard-conformance - does the insertion point fall immediately AFTER
			// the hint?
			iterator __after = __position;
			++__after;
			
			// Already know that compare(pos, v) must be true!
			// Therefore, we want to know if compare(after, v) is false.
			// (i.e., we now pos < v, now we want to know if v <= after)
			// If not, invalid hint.
			if ( __after._M_node==this->_M_header._M_data ||
		 !_M_key_compare( _S_key(__after._M_node), _KeyOfValue()(__v) ) ) {
				if (_S_right(__position._M_node) == 0)
					return _M_insert(0, __position._M_node, __v, __position._M_node);
				else
					return _M_insert(__after._M_node, __after._M_node, __v);
			} else // Invalid hint
				return insert_equal(__v);
		}
	} else if (__position._M_node == this->_M_header._M_data) {// end()
		if (!_M_key_compare(_KeyOfValue()(__v), _S_key(_M_rightmost())))
			return _M_insert(0, _M_rightmost(), __v, __position._M_node); // Last argument only needs to be non-null
		else
			return insert_equal(__v);
	} else {
		iterator __before = __position;
		--__before;
		// store the result of the comparison between pos and v so
		// that we don't have to do it again later.	Note that this reverses the shortcut
		// on the if, possibly harming efficiency in comparisons; I think the harm will
		// be negligible, and to do what I want to do (save the result of a comparison so
		// that it can be re-used) there is no alternative.	Test here is for before <= v <= pos.
		bool __comp_pos_v = _M_key_compare(_S_key(__position._M_node), _KeyOfValue()(__v));
		if (!__comp_pos_v
				&& !_M_key_compare(_KeyOfValue()(__v), _S_key(__before._M_node))) {
			if (_S_right(__before._M_node) == 0)
				return _M_insert(0, __before._M_node, __v, __before._M_node); // Last argument only needs to be non-null
			else
				return _M_insert(__position._M_node, __position._M_node, __v);
		} else	{
			// Does the insertion point fall immediately AFTER the hint?
			// Test for pos < v <= after
			iterator __after = __position;
			++__after;
			
			if (__comp_pos_v
		&& ( __after._M_node==this->_M_header._M_data 
				 || !_M_key_compare( _S_key(__after._M_node), _KeyOfValue()(__v) ) ) ) {
				if (_S_right(__position._M_node) == 0)
					return _M_insert(0, __position._M_node, __v, __position._M_node);
				else
					return _M_insert(__after._M_node, __after._M_node, __v);
			} else // Invalid hint
				return insert_equal(__v);
		}
	}
}

template <class _Key, class _Value, class _KeyOfValue, 
					class _Compare/*, class _Alloc*/> size_t
_Rb_tree<_Key,_Value,_KeyOfValue,_Compare/*,_Alloc*/> ::count(const _Key& __k) const
{
	pair<const_iterator, const_iterator> __p = equal_range(__k);
	size_t __n = distance(__p.first, __p.second);
	return __n;
}

inline int 
__black_count(_Rb_tree_node_base* __node, _Rb_tree_node_base* __root)
{
	if (__node == 0)
		return 0;
	else {
		int __bc = __node->_M_color == _S_rb_tree_black ? 1 : 0;
		if (__node == __root)
			return __bc;
		else
			return __bc + __black_count(__node->_M_parent, __root);
	}
}

template <class _Key, class _Value, class _KeyOfValue, 
					class _Compare/*, class _Alloc*/> bool _Rb_tree<_Key,_Value,_KeyOfValue,_Compare/*,_Alloc*/>::__rb_verify() const
{
	if (_M_node_count == 0 || begin() == end())
		return _M_node_count == 0 && begin() == end() && this->_M_header._M_data->_M_left == this->_M_header._M_data
			&& this->_M_header._M_data->_M_right == this->_M_header._M_data;
	
	int __len = __black_count(_M_leftmost(), _M_root());
	for (const_iterator __it = begin(); __it != end(); ++__it) {
		_Link_type __x = (_Link_type) __it._M_node;
		_Link_type __L = _S_left(__x);
		_Link_type __R = _S_right(__x);

		if (__x->_M_color == _S_rb_tree_red)
			if ((__L && __L->_M_color == _S_rb_tree_red) ||
					(__R && __R->_M_color == _S_rb_tree_red))
				return false;

		if (__L && _M_key_compare(_S_key(__x), _S_key(__L)))
			return false;
		if (__R && _M_key_compare(_S_key(__R), _S_key(__x)))
			return false;

		if (!__L && !__R && __black_count(__x, _M_root()) != __len)
			return false;
	}

	if (_M_leftmost() != _Rb_tree_node_base::_S_minimum(_M_root()))
		return false;
	if (_M_rightmost() != _Rb_tree_node_base::_S_maximum(_M_root()))
		return false;

	return true;
}
//_STLP_END_NAMESPACE

# undef __iterator__				
# undef iterator
# undef __size_type__	

}

//#endif /*	_STLP_TREE_C */

// Local Variables:
// mode:C++
// End:
