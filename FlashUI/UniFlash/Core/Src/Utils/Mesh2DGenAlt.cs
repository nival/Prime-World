using System.Collections.Generic;
using UnityEngine;

namespace Flash.Utils
{
	public class Mesh2DGenAlt
	{

		private const double EPSILON = 0.0000000001;
		public static bool Process( List<Vector3> contour, List<int> result )
		{
			return Process( Convert3To2VectorArray( contour ), result );
		}
		public static bool Process( List<Vector2> contour, List<int> result )
		{
			/* allocate and initialize list of Vertices in polygon */

			int n = contour.Count;
			if ( n < 3 )
				return false;

			int[] V = new int[n];

			/* we want a counter-clockwise polygon in V */

			if ( 0.0f < Area( contour ) )
				for ( int v = 0; v < n; v++ )
					V[v] = v;
			else
				for ( int v = 0; v < n; v++ )
					V[v] = ( n - 1 ) - v;

			int nv = n;

			/*  remove nv-2 Vertices, creating 1 triangle every time */
			int count = 2 * nv;   /* error detection */

			for ( int m = 0, v = nv - 1; nv > 2; )
			{
				/* if we loop, it is probably a non-simple polygon */
				if ( 0 >= ( count-- ) )
				{
					Debug.LogWarning( "TESSELATION ASSERT : Non simple polygon count <=0 : count = " + count );
					//** Triangulate: ERROR - probable bad polygon!
					return false;
				}

				/* three consecutive vertices in current polygon, <u,v,w> */
				int u = v;
				if ( nv <= u )
					u = 0; /* previous */
				v = u + 1;
				if ( nv <= v )
					v = 0; /* new v    */
				int w = v + 1;
				if ( nv <= w )
					w = 0; /* next     */

				if ( Snip( contour, u, v, w, nv, V ) )
				{
					int a, b, c, s, t;

					/* true names of the vertices */
					a = V[u];
					b = V[v];
					c = V[w];

					/* output Triangle */
					//result.Add( contour[a] );
					//result.Add( contour[b] );
					//result.Add( contour[c] );
					result.Add( c );
					result.Add( b );
					result.Add( a );

					m++;

					/* remove v from remaining polygon */
					for ( s = v, t = v + 1; t < nv; s++, t++ )
						V[s] = V[t];
					nv--;

					/* resest error detection counter */
					count = 2 * nv;
				}
			}

			return true;
		}
		private static List<Vector2> Convert3To2VectorArray( List<Vector3> input )
		{
			List<Vector2> result = new List<Vector2>( input.Count );

			foreach ( Vector3 v in input )
				result.Add( new Vector2( v.x, v.y ) );

			return result;
		}
		private static float Area( List<Vector2> contour )
		{
			int n = contour.Count;

			float A = 0.0F;

			for ( int p = n - 1, q = 0; q < n; p = q++ )
			{
				A += contour[p].x * contour[q].y - contour[q].x * contour[p].y;
			}

			return A * 0.5F;
		}
		private static bool InsideTriangle( float Ax, float Ay,
																				float Bx, float By,
																				float Cx, float Cy,
																				float Px, float Py )
		{
			float ax, ay, bx, by, cx, cy, apx, apy, bpx, bpy, cpx, cpy;
			float cCROSSap, bCROSScp, aCROSSbp;

			ax = Cx - Bx;
			ay = Cy - By;
			bx = Ax - Cx;
			by = Ay - Cy;
			cx = Bx - Ax;
			cy = By - Ay;
			apx = Px - Ax;
			apy = Py - Ay;
			bpx = Px - Bx;
			bpy = Py - By;
			cpx = Px - Cx;
			cpy = Py - Cy;

			aCROSSbp = ax * bpy - ay * bpx;
			cCROSSap = cx * apy - cy * apx;
			bCROSScp = bx * cpy - by * cpx;

			return ( ( aCROSSbp >= 0.0f ) && ( bCROSScp >= 0.0f ) && ( cCROSSap >= 0.0f ) );
		}
		private static bool Snip( List<Vector2> contour, int u, int v, int w, int n, int[] V )
		{
			// TODO ’рень с тессел€цией
			return true;

			/*int p;
			float Ax, Ay, Bx, By, Cx, Cy, Px, Py;

			Ax = contour[V[u]].x;
			Ay = contour[V[u]].y;

			Bx = contour[V[v]].x;
			By = contour[V[v]].y;

			Cx = contour[V[w]].x;
			Cy = contour[V[w]].y;

			if ( EPSILON > ( ( ( Bx - Ax ) * ( Cy - Ay ) ) - ( ( By - Ay ) * ( Cx - Ax ) ) ) )
			{
				return false;
			}

			for ( p = 0; p < n; p++ )
			{
				if ( ( p == u ) || ( p == v ) || ( p == w ) )
					continue;
				Px = contour[V[p]].x;
				Py = contour[V[p]].y;
				if ( InsideTriangle( Ax, Ay, Bx, By, Cx, Cy, Px, Py ) )
					return false;
			}

			return true;*/
		}
	}
}
