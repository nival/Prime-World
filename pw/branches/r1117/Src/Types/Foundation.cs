using System.Collections.Generic;
using libdb.Animated;
using libdb.DB;

namespace Foundation.DBSystem
{
  // if you made changes in resources (theirs content, structure or everything else) and don't know
  // for what resource update DBVersion, update it here
  [DBVersion( 1 )]
  [NoCode]
  [NoCSCode]
  public class DBVersionResource
  {
  }

	[NoCode]
	[RenameType( "Animated<int, NDb::AnimatedAlgorithms::Linear>" )]
	public class AnimatedInt : AnimatedLinear<int, IntAlgorithm>
	{
		public AnimatedInt() : base() { }
		public AnimatedInt( DBResource owner, int value ) : base( owner, value ) { }
	}

	[NoCode]
	[RenameType( "Animated<float, NDb::AnimatedAlgorithms::Linear>" )]
	public class AnimatedFloat : AnimatedLinear<float, FloatAlgorithm> 
  { 
		public AnimatedFloat() : base() { }
		public AnimatedFloat( float value ) : base( null, value ) { }
		public AnimatedFloat( DBResource owner, float value ) : base( owner, value ) { }
  }

	[NoCode]
	[RenameType( "Animated<string, NDb::AnimatedAlgorithms::Discrete>" )]
	public class AnimatedString : AnimatedDiscrete<string>{}

	[NoCode]
  [Custom( "Social" )]
	[RenameType( "CVec2" )]
	public class Vec2
	{
		public float x = 0.0f;
		public float y = 0.0f;

		public Vec2() {}

		public Vec2( float _x, float _y )
		{
			x = _x;
			y = _y;
		}
	}

	[NoCode]
	[RenameType( "Animated<CVec2, NDb::AnimatedAlgorithms::Linear>" )]
	[AnimatedComplexConverter( "x", "y" ) ]
	public class AnimatedVec2 : AnimatedComplex<Vec2, float, FloatAlgorithm, DummyComplexConverter<Vec2, float>> { }

	[NoCode]
  [Custom("Social")]
	[RenameType( "CVec3" )]
	public class Vec3
	{
		public float x = 0.0f;
		public float y = 0.0f;
		public float z = 0.0f;

		public Vec3() {}

		public Vec3( float _x,  float _y,  float _z )
		{
			x = _x;
			y = _y;
			z = _z;
		}
	}

	[NoCode]
	[RenameType( "Animated<CVec3, NDb::AnimatedAlgorithms::Linear>" )]
	[AnimatedComplexConverter( "x", "y", "z" )]
	public class AnimatedVec3 : AnimatedComplex<Vec3, float, FloatAlgorithm, DummyComplexConverter<Vec3, float>>
	{
		public AnimatedVec3() : base() { }
		public AnimatedVec3( float x, float y, float z ) : base( x, y, z ) { }
	}

	[NoCode]
	[RenameType( "CVec3" )]
	public class Scale
	{
		public float x = 1.0f;
		public float y = 1.0f;
		public float z = 1.0f;
	}

	[NoCode]
	[RenameType( "Animated<CVec3, NDb::AnimatedAlgorithms::Linear>" )]
	[AnimatedComplexConverter( "x", "y", "z" )]
	public class AnimatedScale : AnimatedComplex<Scale, float, FloatAlgorithm, DummyComplexConverter<Scale, float>>
	{
		public AnimatedScale() : base() { }
		public AnimatedScale( float x, float y, float z ) : base( x, y, z ) { }
	}

	[NoCode]
	[RenameType( "CQuat" )]
	public class Quat
	{
		public float x = 0.0f;
		public float y = 0.0f;
		public float z = 0.0f;
		public float w = 1.0f;
	}

	[NoCode]
	[RenameType( "Animated<CQuat, NDb::AnimatedAlgorithms::Linear>" )]
  [AnimatedComplexConverter(false, "RotateX", "RotateY", "RotateZ")]
	public class AnimatedQuat : AnimatedComplex<Quat, float, FloatAlgorithm, DummyComplexConverter<Quat, float>>
	{
		public AnimatedQuat() : base() { }
    public AnimatedQuat(float RotateX, float RotateY, float RotateZ) : base(RotateX, RotateY, RotateZ) { }
	}

	[NoCode]
	[RenameType("Matrix43")]
	public class Matrix
	{
		public float x1 = 1.0f;
		public float y1 = 0.0f;
		public float z1 = 0.0f;
		public float w1 = 0.0f;
		public float x2 = 0.0f;
		public float y2 = 1.0f;
		public float z2 = 0.0f;
		public float w2 = 0.0f;
		public float x3 = 0.0f;
		public float y3 = 0.0f;
		public float z3 = 1.0f;
		public float w3 = 0.0f;
	}

  [NoCode]
  [RenameType( "CPlacement" )]
  public class Placement
  {
    public Vec3 location;
    public Quat rotation;
    public Scale scale;
  }

  [NoCode]
  [RenameType( "CPlacement" )]
  public class Placement2
  {
    public float translateX = 0.0f;
    public float translateY = 0.0f;
    public float translateZ = 0.0f;
    public float rotationX = 0.0f;
    public float rotationY = 0.0f;
    public float rotationZ = 0.0f;
    public float scaleX = 1.0f;
    public float scaleY = 1.0f;
    public float scaleZ = 1.0f;
  }

	[NoCode]
	[RenameType( "Render::Color" )]
  [Custom("Social")]
	public class Color
	{
		public int R = 0;
		public int G = 0;
		public int B = 0;
		public int A = 255;

    public Color() {}

    public Color(int _R, int _G, int _B, int _A)
    {
      this.A = _A;
      this.R = _R;
      this.G = _G;
      this.B = _B;
    }
	};

	[NoCode]
	[RenameType( "Render::HDRColor" )]
  [Custom("Social")]
	public class HDRColor
	{
		public float R = 0;
		public float G = 0;
		public float B = 0;
		public float A = 1.0f;

		public HDRColor() { }

		public HDRColor( float _R, float _G, float _B, float _A )
		{
			this.R = _R;
			this.G = _G;
			this.B = _B;
			this.A = _A;
		}
	}

  [NoCode]
  [RenameType("Animated<Render::HDRColor, NDb::AnimatedAlgorithms::Linear>")]
  [AnimatedComplexConverter("R", "G", "B", "A")]
  public class AnimatedHDRColor : AnimatedComplex<HDRColor, float, FloatAlgorithm, DummyComplexConverter<HDRColor, float>>
  {
    public AnimatedHDRColor() : base() { }
    public AnimatedHDRColor(float R, float G, float B, float A) : base(R, G, B, A) { }
  }

  [NoCode]
  [RenameType( "CTPoint<int>" )]
  public class IntPoint
  {
    public int x = 0;
    public int y = 0;

    public IntPoint() { }

    public IntPoint( int _x, int _y )
    {
      x = _x;
      y = _y;
    }
  }

  [NoCode]
  [RenameType( "CTRect<int>" )]
  public class IntRect
  {
    public int x1 = 0;
    public int y1 = 0;
    public int x2 = 0;
    public int y2 = 0;
  }
  
  [NoCode]
  [RenameType("CTPoint<float>")]
  public class FloatPoint
  {
    public int x = 0;
    public int y = 0;

    public FloatPoint() { }

    public FloatPoint(int _x, int _y)
    {
      x = _x;
      y = _y;
    }
  }

  [NoCode]
  [RenameType( "CTRect<float>" )]
  public class FloatRect
  {
    public float x1 = 0;
    public float y1 = 0;
    public float x2 = 0;
    public float y2 = 0;
  }
}
