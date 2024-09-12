using System;

namespace libdb
{
	public sealed class ListItemAddedEventArgs<T> : EventArgs
	{
		public int Index { get; internal set; }
		public T Item { get; internal set; }
	}
}
