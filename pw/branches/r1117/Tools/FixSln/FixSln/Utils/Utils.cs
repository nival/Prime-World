using System;
using System.Collections.Generic;
using System.Text;

namespace FixSln.Utils
{
	public static class Utils
	{
		public static void AddToDictionaryList<TKey, TValue>( Dictionary<TKey, List<TValue>> dictionary, TKey key, TValue value )
		{
			List<TValue> list = null;
			if ( !dictionary.TryGetValue( key, out list ) )
			{
				list = new List<TValue>();
				dictionary.Add( key, list );
			}
			list.Add( value );
		}
	}
}
