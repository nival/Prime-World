using System.Collections.Generic;
using libdb;

namespace PF_Editor.Map.AdvMapObjects
{
  internal class ListObserver<T>
	{
		#region Private members.

		private readonly IChangeableList<T> list;
		private readonly List<ControllableVisualObject> visualObjects = new List<ControllableVisualObject>();

		#endregion

		#region Initialization.

    public ListObserver(IChangeableList<T> list)
		{
			this.list = list;
		}

    public void Initialize(CreateVisualObject createVisualObject)
		{
      this.createVisualObject = createVisualObject;

      visualObjects.Clear();
      visualObjects.Capacity = list.Count;
      for ( int index = 0; index < list.Count; ++index )
        Insert( index, list[index] );

      list.ListItemAdded += OnListItemAdded;
      list.ListItemBeforeRemoved += OnListItemBeforeRemoved;
      list.ListItemBeforeChanged += OnListItemBeforeChanged;
      list.ListItemChanged += OnListItemChanged;
		}

		public void Unsubscribe()
		{
		  createVisualObject = null;
			list.ListItemAdded -= OnListItemAdded;
			list.ListItemBeforeRemoved -= OnListItemBeforeRemoved;
			list.ListItemBeforeChanged -= OnListItemBeforeChanged;
			list.ListItemChanged -= OnListItemChanged;

			while ( visualObjects.Count > 0 )
			{
				RemoveAt( 0 );
			}
		}

		#endregion

		#region Public properties.

    public IEnumerable<ControllableVisualObject> VisualObjects
		{
			get { return visualObjects; }
		}

		public IChangeableList<T> Resource
		{
			get { return list; }
		}

		#endregion

		#region Event handlers.

		private void OnListItemAdded( object sender, ListItemAddedEventArgs<T> e )
		{
			Insert( e.Index, e.Item );
		}

		private void OnListItemBeforeRemoved( object sender, ListItemBeforeRemovedEventArgs<T> e )
		{
			RemoveAt( e.Index );
		}

		private void OnListItemBeforeChanged( object sender, ListItemBeforeChangedEventArgs<T> e )
		{
			RemoveAt( e.Index );
		}

		private void OnListItemChanged( object sender, ListItemChangedEventArgs<T> e )
		{
			Insert( e.Index, e.NewValue );
		}

		#endregion

		#region Delegates and Events

    public delegate ControllableVisualObject CreateVisualObject(T item);
    private CreateVisualObject createVisualObject = null;
    public delegate void OnControllerRemoved(ControllableVisualObject controller);
    public event OnControllerRemoved OnControllerRemovedEvent = null;

		#endregion

		#region Private helper methods.

		private void Insert( int index, T item )
		{
      visualObjects.Insert(index, createVisualObject(item));
		}

		private void RemoveAt( int index )
		{
		  ControllableVisualObject controller = visualObjects[index];

      if(controller != null)
      {
        if (OnControllerRemovedEvent != null)
          OnControllerRemovedEvent(controller);

        controller.Unsubscribe();        
      }

			visualObjects.RemoveAt( index );
		}

		#endregion
	}
}
