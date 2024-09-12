using System;

namespace libdb
{
	public sealed class ListItemChangedEventArgs<T> : EventArgs
	{
		public int Index { get; internal set; }
		public T NewValue { get; internal set; }
	}
}
