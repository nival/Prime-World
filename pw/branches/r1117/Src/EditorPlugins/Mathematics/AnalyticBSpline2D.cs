using System;
using System.Collections.Generic;
using System.Text;
using System.Drawing;

namespace EditorPlugins.Mathematics
{
	public sealed class AnalyticBSpline2D
	{
		// двумерный кубический сплайн

		private AnalyticBSpline x = new AnalyticBSpline();
		private AnalyticBSpline y = new AnalyticBSpline();

		public AnalyticBSpline2D() { }
		public AnalyticBSpline2D( PointF p0, PointF p1, PointF p2, PointF p3 ) { Setup( p0, p1, p2, p3 ); }

		public void Setup( PointF p0, PointF p1, PointF p2, PointF p3 )
		{
			x.Setup( p0.X, p1.X, p2.X, p3.X );
			y.Setup( p0.Y, p1.Y, p2.Y, p3.Y );
		}

		public PointF Get( float t ) { return new PointF( x.Get( t ), y.Get( t ) ); }

		public PointF GetDiff1( float t ) { return new PointF( x.GetDiff1( t ), y.GetDiff1( t ) ); }
		public PointF GetDiff2( float t ) { return new PointF( x.GetDiff2( t ), y.GetDiff2( t ) ); }
		public PointF GetDiff3( float t ) { return new PointF( x.GetDiff3( t ), y.GetDiff3( t ) ); }

		public float GetLength( int nNumSteps )
		{
			float fStep = 1.0f / nNumSteps;
			PointF vLastPos = new PointF();
			PointF vPos = Get( 0 );
			float fLen = 0;
			for ( float fT = 0; fT <= 1; fT += fStep )
			{
				vLastPos = vPos;
				vPos = Get( fT );
				fLen += (float)Math.Sqrt( ( vLastPos.X - vPos.X ) * ( vLastPos.X - vPos.X ) + ( vLastPos.Y - vPos.Y ) * ( vLastPos.Y - vPos.Y ) );
			}
			return fLen;
		}

		public float GetLength( float t, int nNumSteps )
		{
			if ( t < 1e-4 )
			{
				PointF vPos1 = Get( t );
				PointF vPos2 = Get( 0 );
				return (float)System.Math.Sqrt( ( vPos1.X - vPos2.X ) * ( vPos1.X - vPos2.X ) + ( vPos1.Y - vPos2.Y ) * ( vPos1.Y - vPos2.Y ) );
			}

			float fStep = 1.0f / nNumSteps;
			PointF vLastPos = new PointF();
			PointF vPos = Get( 0 );
			float fLen = 0;
			for ( float fT = 0; fT <= t; fT += fStep )
			{
				vLastPos = vPos;
				vPos = Get( fT );
				fLen += (float)System.Math.Sqrt( ( vLastPos.X - vPos.X ) * ( vLastPos.X - vPos.X ) + ( vLastPos.Y - vPos.Y ) * ( vLastPos.Y - vPos.Y ) );
			}
			return fLen;
		}

		public float GetLength( float fT1, float fT2, int nNumSteps )
		{
			if ( fT2 - fT1 < 1e-4 )
			{
				PointF vPos1 = Get( fT2 );
				PointF vPos2 = Get( fT1 );
				return (float)System.Math.Sqrt( ( vPos1.X - vPos2.X ) * ( vPos1.X - vPos2.X ) + ( vPos1.Y - vPos2.Y ) * ( vPos1.Y - vPos2.Y ) );
			}
			float fStep = 1.0f / nNumSteps;
			PointF vLastPos = new PointF();
			PointF vPos = Get( fT1 );
			float fLen = 0;
			for ( float fT = fT1; fT <= fT2; fT += fStep )
			{
				vLastPos = vPos;
				vPos = Get( fT );
				fLen += (float)System.Math.Sqrt( ( vLastPos.X - vPos.X ) * ( vLastPos.X - vPos.X ) + ( vLastPos.Y - vPos.Y ) * ( vLastPos.Y - vPos.Y ) );
			}
			return fLen;
		}

		public float GetLengthAdaptive( float fTolerance, int nStepLimit )
		{
			float fLen1 = GetLength( 100 );
			float fLen2 = GetLength( 200 );
			int nStepCounter = 2;
			while ( ( System.Math.Abs( fLen1 - fLen2 ) > fTolerance ) && ( nStepCounter < nStepLimit ) )
			{
				++nStepCounter;
				fLen1 = fLen2;
				fLen2 = GetLength( 100 * nStepCounter );
			}
			return fLen2;
		}

		public float GetStep( float fStep ) { return fStep / GetLength( 100 ); }

		// радиус кривизны кривой, заданной параметрически:
		//		 ((x`)^2 + (y`)^2)^(3/2)
		// R = -----------------------
		//				 |x`y`` - y`x``|
		public float GetCurvatureRadius( float t )
		{
			float dx = x.GetDiff1( t );
			float dy = y.GetDiff1( t );
			float denominator = System.Math.Abs( dx * y.GetDiff2( t ) - dy * x.GetDiff2( t ) );
			return denominator < 1e-5f ? 0 : (float)System.Math.Pow( dx * dx + dy * dy, 3.0f / 2.0f ) / denominator;
		}

		// центр кривизны кривой, заданной параметрически:
		//					(x`)^2 + (y`)^2
		// x0 = x - --------------- * y`
		//					 x`y`` - y`x``
		//					(x`)^2 + (y`)^2
		// y0 = y + --------------- * x`
		//					 x`y`` - y`x``
		public PointF GetCurvatureCenter( float t )
		{
			float dx = x.GetDiff1( t );
			float dy = y.GetDiff1( t );
			float denominator = dx * y.GetDiff2( t ) - dy * x.GetDiff2( t );
			if ( System.Math.Abs( denominator ) < 1e-5f )
				return new PointF();
			float fCoeff = ( dx * dx + dy * dy ) / denominator;
			return new PointF( x.Get( t ) - fCoeff * dy, y.Get( t ) + fCoeff * dx );
		}

	};
}
