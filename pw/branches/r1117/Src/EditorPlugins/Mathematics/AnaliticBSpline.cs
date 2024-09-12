using System;
using System.Collections.Generic;
using System.Text;
using System.Drawing;

namespace EditorPlugins.Mathematics
{
	public sealed class AnalyticBSpline
	{
		// кубический сплайн
		private float a3, a2, a1, a0;

		public AnalyticBSpline() { }
		public AnalyticBSpline( float p0, float p1, float p2, float p3 ) { Setup( p0, p1, p2, p3 ); }
		public AnalyticBSpline( AnalyticBSpline bs ) { a3 = bs.a3; a2 = bs.a2; a1 = bs.a1; a0 = bs.a0; }
		//
		public void Setup( float p0, float p1, float p2, float p3 )
		{
			a3 = ( -p0 + 3.0f * ( p1 - p2 ) + p3 ) * ( 1.0f / 6.0f );
			a2 = ( p0 - 2.0f * p1 + p2 ) * ( 1.0f / 2.0f );
			a1 = ( -p0 + p2 ) * ( 1.0f / 2.0f );
			a0 = ( p0 + 4.0f * p1 + p2 ) * ( 1.0f / 6.0f );
		}
		public float Get( float t ) { return ( ( a3 * t + a2 ) * t + a1 ) * t + a0; }

		public float GetDiff1( float t ) { return ( a3 * 3.0f * t + a2 * 2.0f ) * t + a1; }
		public float GetDiff2( float t ) { return a3 * 6.0f * t + a2 * 2.0f; }
		public float GetDiff3( float t ) { return a3 * 6.0f; }
	};
}
