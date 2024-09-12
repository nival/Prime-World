using System;
using System.Collections.Generic;
using System.Text;

namespace River.Core.Utils
{
	public class Pair<TKey, TValue>
	{
		private TKey key;
		private TValue value;

		public Pair( TKey key, TValue value ) { this.key = key; this.value = value; }

		public TKey Key { get { return key; } set { key = value; } }
		public TValue Value { get { return value; } set { this.value = value; } }
	}
}
