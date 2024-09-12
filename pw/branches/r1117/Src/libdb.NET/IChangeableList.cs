using System.Collections.Generic;
using System;

namespace libdb
{
	public interface IChangeableList<T> : IList<T>, IChangeable, IRichList, IBasicDBValue
	{
    new int Count { get; }
    
    event EventHandler<ListItemAddedEventArgs<T>> ListItemAdded;
		event EventHandler<ListItemBeforeRemovedEventArgs<T>> ListItemBeforeRemoved;
		event EventHandler<ListItemChangedEventArgs<T>> ListItemChanged;
		event EventHandler<ListItemBeforeChangedEventArgs<T>> ListItemBeforeChanged;
	}
}
