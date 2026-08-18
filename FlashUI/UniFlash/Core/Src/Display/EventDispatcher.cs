using System;
using System.Collections.Generic;

namespace Flash
{

  

  public abstract class EventDispatcher
  {
    private class TypeComparer: IComparer<Type>
    {
      public int Compare(Type x, Type y)
      {
        if (x == y)
          return 0;

        return x.FullName.CompareTo(y.FullName);
      }
    }

    private static readonly TypeComparer _typeComparer = new TypeComparer();

    private SortedList<Type, List<Delegate>> _typedEvents = new SortedList<Type, List<Delegate>>(0, _typeComparer);
    protected SortedList<Type, List<Delegate>> TypedEvents
    {
      get { return _typedEvents; }
      set { _typedEvents = value; }
    }

    /// <summary>
    /// Add event listener
    /// </summary>
    /// <typeparam name="T">Flash Event</typeparam>
    /// <param name="eventType">Unique event identifier</param>
    /// <param name="action">Action for handle event</param>
    public void AddEventListener<T>( Action<T> action ) where T : Event
    {
      Type eventType = typeof(T);

      if (!TypedEvents.ContainsKey(eventType))
        TypedEvents[eventType] = new List<Delegate>(1);

      TypedEvents[eventType].Add(action);
    }

    public void RemoveEventListener<T>( Action<T> action ) where T : Event
    {
      Type eventType = typeof( T );

      if ( !TypedEvents.ContainsKey( eventType ) )
        return;

      TypedEvents[eventType].Remove( action );
    }

    /// <summary>
    /// Raises pop event 
    /// </summary>
    /// <typeparam name="T">Flash event</typeparam>
    /// <param name="evt">Instance of event</param>
    protected void DispatchEvent<T>( T evt ) where T : Event
    {
      DispatchEventInternal( evt );

      if ( evt.PropogateAcrossHierarchy )
        PropagateToParent( evt );
    }

    private void DispatchEventInternal<T>( T evt ) where T : Event
    {
      Type eventType = typeof( T );

      do
      {
        List<Delegate> actions;

        if ( TypedEvents.TryGetValue( eventType, out actions ) )
        {
          var tempActions = new List<Delegate>(actions);//чтобы можно было отписываться в обработчике события

          foreach ( Delegate obj in tempActions )
          {
            if ( !evt.PropogateAcrossNode )
              break;

            ( (Delegate)obj ).DynamicInvoke( evt );
          }
        }

        eventType = eventType.BaseType;

      } while ( eventType != null && eventType != typeof( object ) && eventType != typeof( Event ) );
    }

    protected abstract void PropagateToParent<T>( T evt ) where T : Event;
  }
}
