using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;

namespace EditorLib.Utils
{
	public static class FormUtils
	{
		public delegate void Operation();
		public delegate void Operation<T1>( T1 param1 );
		public delegate void Operation<T1, T2>( T1 param1, T2 param2 );
		public delegate void Operation<T1, T2, T3>( T1 param1, T2 param2, T3 param3 );

		public static void Invoke( Control control, Operation operation )
		{
			if ( control.InvokeRequired )
				control.Invoke( operation );
			else
				operation();
		}

		public static void Invoke<T1>( Control control, Operation<T1> operation, T1 param1 )
		{
			if ( control.InvokeRequired )
				control.Invoke( operation, param1 );
			else
				operation( param1 );
		}

		public static void Invoke<T1, T2>( Control control, Operation<T1, T2> operation, T1 param1, T2 param2 )
		{
			if ( control.InvokeRequired )
				control.Invoke( operation, param1, param2 );
			else
				operation( param1, param2 );
		}

		public static void BeginInvoke( Control control, Operation operation )
		{
			if ( control.InvokeRequired )
				control.BeginInvoke( operation );
			else
				operation();
		}

		public static void BeginInvoke<T1>( Control control, Operation<T1> operation, T1 param1 )
		{
			if ( control.InvokeRequired )
				control.BeginInvoke( operation, param1 );
			else
				operation( param1 );
		}

		public static void BeginInvoke<T1, T2>( Control control, Operation<T1, T2> operation, T1 param1, T2 param2 )
		{
			if ( control.InvokeRequired )
				control.BeginInvoke( operation, param1, param2 );
			else
				operation( param1, param2 );
		}

		public static void BeginInvoke<T1, T2, T3>( Control control, Operation<T1, T2, T3> operation, T1 param1, T2 param2, T3 param3 )
		{
			if ( control.InvokeRequired )
				control.BeginInvoke( operation, param1, param2, param3 );
			else
				operation( param1, param2, param3 );
		}

    private static int Lerp( int x0, int x1, float t )
    {
      return (int)( (float)x0 * ( 1.0f - t ) + (float)x1 * t );
    }

    public static System.Drawing.Color MixColors( System.Drawing.Color a, System.Drawing.Color b, float t )
    {
      return System.Drawing.Color.FromArgb( Lerp( a.A, b.A, t ), Lerp( a.R, b.R, t ), Lerp( a.G, b.G, t ), Lerp( a.B, b.B, t ) );
    }
  }
}
