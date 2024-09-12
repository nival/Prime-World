using System;

namespace libdb
{
	public class ListItemBeforeChangedEventArgs<T> : EventArgs
	{
		public int Index { get; internal set; }
		public T PrevValue { get; internal set; }
	}
}
