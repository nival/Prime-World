using System;
using ViewModel;

namespace Flash.Utils
{
	public static class EventHelper
	{
		public static void Invoke( Action action )
		{
			Action innerAction = action;
			if ( innerAction != null ) innerAction();
		}
		
		public static void Invoke<T>( Action<T> action, T arg )
		{
			Action<T> innerAction = action;
			if ( innerAction != null )
				innerAction(arg);
		}

		public static void Invoke<T1, T2>( Action<T1, T2> action, T1 arg1, T2 arg2 )
		{
			Action<T1, T2> innerAction = action;
			if ( innerAction != null )
				innerAction( arg1, arg2 );
		}

		public static void Invoke<T1, T2, T3>( Action<T1, T2, T3> action, T1 arg1, T2 arg2, T3 arg3 )
		{
			Action<T1, T2, T3> innerAction = action;
			if ( innerAction != null )
				innerAction( arg1, arg2, arg3 );
		}

    public static void Invoke<T1, T2, T3, T4>( Action<T1, T2, T3, T4> action, T1 arg1, T2 arg2, T3 arg3, T4 arg4 )
    {
      Action<T1, T2, T3, T4> innerAction = action;
      if( innerAction != null )
        innerAction( arg1, arg2, arg3, arg4 );
    }

    public static void Invoke<T1, T2, T3, T4, T5>(ActionCustom<T1, T2, T3, T4, T5> action, T1 arg1, T2 arg2, T3 arg3, T4 arg4, T5 arg5)
    {
      ActionCustom<T1, T2, T3, T4, T5> innerAction = action;
      if( innerAction != null )
        innerAction( arg1, arg2, arg3, arg4, arg5 );
    }

    public static void Invoke<T1, T2, T3, T4, T5, T6>(ActionCustom<T1, T2, T3, T4, T5, T6> action, T1 arg1, T2 arg2, T3 arg3, T4 arg4, T5 arg5, T6 arg6)
    {
      ActionCustom<T1, T2, T3, T4, T5, T6> innerAction = action;
      if (innerAction != null)
        innerAction(arg1, arg2, arg3, arg4, arg5, arg6);
    }

	  public static void Invoke( EventHandler<EventArgs> action, object sender )
		{
			EventHandler<EventArgs> innerAction = action;
			if ( innerAction != null )
				innerAction( sender, EventArgs.Empty );
		}

		public static void Invoke<T>( EventHandler<T> action, object sender, T args) where T : EventArgs
		{
			EventHandler<T> innerAction = action;
			if ( innerAction != null )
				innerAction( sender, args );
		}
	}
}
