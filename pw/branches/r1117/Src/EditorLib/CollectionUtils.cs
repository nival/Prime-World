using System;
using System.Collections.Generic;

namespace EditorLib
{
	public static class CollectionUtils
	{
		public static List<T> Concat<T>( IEnumerable<T> begin, IEnumerable<T> end )
		{
			var result = new List<T>( begin );
			result.AddRange( end );
			return result;
		}

		public static List<TOutput> ConvertAll<TInput, TOutput>( IEnumerable<TInput> enumerable, Converter<TInput, TOutput> convert )
		{
			var result = new List<TOutput>();
			foreach ( var item in enumerable )
			{
				result.Add( convert( item ) );
			}
			return result;
		}

		public static List<T> FindAll<T>( IEnumerable<T> enumerable, System.Predicate<T> predicate )
		{
			var result = new List<T>();
			foreach ( var item in enumerable )
			{
				if ( predicate( item ) )
				{
					result.Add( item );
				}
			}
			return result;
		}

		public static T Find<T>( IEnumerable<T> enumerable, System.Predicate<T> predicate )
		{
			foreach ( var item in enumerable )
			{
				if(predicate(item))
					return item;
			}

			return default(T);
		}

		public static List<T> Combine<T>( IEnumerable<T> enumerable, params T[] values )
		{
			var result = new List<T>( enumerable );
			result.AddRange( values );
			return result;
		}

		public static bool ArrayEquals<T>( T[] _array1, T[] _array2 )
		{
			if ( _array1.Length != _array2.Length )
			{
				return false;
			}

			for ( int i = 0; i < _array1.Length; ++i )
			{
				if ( !_array1[i].Equals( _array1[i] ) )
				{
					return false;
				}
			}

			return true;
		}

		public static List<T> Intersection<T>( IEnumerable<T> _list1, IEnumerable<T> _list2 )
    {
			return Intersection(_list1, _list2, (i1, i2) => i1.Equals(i2));
    }

		public static List<T> Intersection<T>( IEnumerable<T> _list1, IEnumerable<T> _list2, Predicate<T, T> _comparer )
		{
			List<T> result = new List<T>();

			foreach ( T item1 in _list1 )
			{
				foreach ( T item2 in _list2 )
				{
					if ( _comparer(item1, item2) )
					{
						result.Add( item1 );
						break;
					}
				}
			}

			return result;
		}
	}
}
