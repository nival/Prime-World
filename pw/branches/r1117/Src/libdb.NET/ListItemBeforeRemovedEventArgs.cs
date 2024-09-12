using System;

namespace libdb
{
	public sealed class ListItemBeforeRemovedEventArgs<T> : EventArgs
	{
		public int Index { get; internal set; }
		public T Item { get; internal set; }
	}
}
