/* ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is [Open Source Virtual Machine.].
 *
 * The Initial Developer of the Original Code is
 * Adobe System Incorporated.
 * Portions created by the Initial Developer are Copyright (C) 2004-2006
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *   Adobe AS3 Team
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either the GNU General Public License Version 2 or later (the "GPL"), or
 * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the MPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the MPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */

#ifndef __TypeTraits__
#define __TypeTraits__

#include "StaticAssert.h"

/*
	This header file implements a small subset of the type traits
	functionality defined in TR1. At present, however, TR1 is not 
	available on all supported systems.
*/

namespace MMgc
{
	template <typename _Type>
	struct remove_const { typedef _Type type; };

	template <typename _Type>
	struct remove_const<_Type const> { typedef _Type type; };

	template <typename _Type>
	struct remove_volatile { typedef _Type type; };

	template <typename _Type>
	struct remove_volatile<_Type volatile> { typedef _Type type; };

	template <typename _Type>
	struct remove_cv
	{
		typedef typename remove_const<typename remove_volatile<_Type>::type>::type type;
	};

	template <typename _Type>
	struct remove_pointer
	{
		typedef _Type type;
	};

#define _RP_SPECIALIZE(_ModifiedType) \
	template <typename _Type> \
	struct remove_pointer<_ModifiedType> \
	{ \
		typedef _Type type; \
	};

	_RP_SPECIALIZE(_Type *)
	_RP_SPECIALIZE(_Type * const)
	_RP_SPECIALIZE(_Type * volatile)
	_RP_SPECIALIZE(_Type * const volatile)

#undef _RP_SPECIALIZE

	template <typename _Type, _Type _Value>
	struct integral_constant
	{
		static const _Type value = _Value;
		typedef _Type value_type;
		typedef integral_constant<_Type, _Value> type;
	};

	typedef integral_constant<bool, true> true_type;
	typedef integral_constant<bool, false> false_type;

	template <typename, typename>
	struct is_same : public false_type { };

	template <typename _Type>
	struct is_same<_Type, _Type> : public true_type { };

	template <typename _Type>
	struct _is_class_or_union_helper
	{
	private:
		typedef char _one;
		typedef struct { char _c[2]; } _two;

	public:
		template <typename _T>
			static _one _test (int _T::*);
		template <typename>
			static _two _test (...);

		static const bool _value = sizeof (_test<_Type>(0)) == sizeof (_one);
	};

	template <typename _Type>
	struct _is_class_or_union : public integral_constant<bool, _is_class_or_union_helper<_Type>::_value>
	{
	};

	template <typename _Base, typename _Derived>
	struct _is_base_of_helper
	{
	private:
		// Disallow incomplete types.
		MMGC_STATIC_ASSERT(sizeof (_Base) != 0);
		MMGC_STATIC_ASSERT(sizeof (_Derived) != 0);

		typedef typename remove_cv<_Base>::type _RCV_Base;
		typedef typename remove_cv<_Derived>::type _RCV_Derived;

		typedef char _one;
		typedef struct { char _c[2]; } _two;

	public:
		template <typename _T>
			static _one _test (_RCV_Derived &, _T);
		static _two _test (_RCV_Base &, int);

		struct _convert
		{
			operator _RCV_Base & () const;
			operator _RCV_Derived & ();
		};

		static const bool _value = (_is_class_or_union<_Base>::value &&
			_is_class_or_union<_Derived>::value &&
			(sizeof (_test(_convert(), 0)) == sizeof (_one) ||
			is_same<_Base, _Derived>::value));
	};

	template <typename _Base, typename _Derived>
	struct is_base_of :
		public integral_constant<bool, _is_base_of_helper<_Base, _Derived>::_value>
	{
	};
}

#endif /* __TypeTraits__ */
