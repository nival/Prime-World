#pragma once

namespace EditorNative
{
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	public ref class Vector3 sealed
	{
	private:
		float x;
		float y;
		float z;

	public:
		Vector3( float _x, float _y, float _z );

	internal:
		Vector3( const CVec3& native );

	public:
		property float X
		{
			float get() { return x; }
      void set( float value ) { x = value; }
		}

		property float Y
		{
			float get() { return y; }
      void set( float value ) { y = value; }
		}

		property float Z
		{
			float get() { return z; }
      void set( float value ) { z = value; }
		}

		property Vector3^ Normalized
		{
			Vector3^ get();
		}

		property float Abs
		{
			float get (){ return fabs( Native ); }
		}

		property float Length 
		{
			float get(){return Native.Length();}
		}

		static property Vector3^ AxisX
		{
			Vector3^ get() { return gcnew Vector3( 1, 0, 0 ); }
		}

		static property Vector3^ AxisY
		{
			Vector3^ get() { return gcnew Vector3( 0, 1, 0 ); }
		}

		static property Vector3^ AxisZ
		{
			Vector3^ get() { return gcnew Vector3( 0, 0, 1 ); }
		}

		static property Vector3^ Zero
		{
			Vector3^ get() { return gcnew Vector3( 0, 0, 0 ); }
		}

		static property Vector3^ Ones
		{
			Vector3^ get() { return gcnew Vector3( 1, 1, 1 ); }
		}

		static Vector3^ operator + ( Vector3^ left, Vector3^ right )
		{
			return gcnew Vector3( left->Native + right->Native );
		}

		static Vector3^ operator - ( Vector3^ left, Vector3^ right )
		{
			return gcnew Vector3( left->Native - right->Native );
		}

		static Vector3^ operator * ( Vector3^ left, float right )
		{
			return gcnew Vector3( left->Native * right );
		}

		static Vector3^ operator * ( Vector3^ left, Vector3^ right )
		{
			CVec3 res;
			res.Mul( left->Native, right->Native );
			return gcnew Vector3( res );
		}

		static Vector3^ Cross ( Vector3^ left, Vector3^ right ) 
		{
			Vector3^ res = gcnew Vector3(0,0,0);
			res->X = left->Y * right->Z - left->Z * right->Y;
			res->Y = left->Z * right->X - left->X * right->Z;
			res->Z = left->X * right->Y - left->Y * right->X;
			return res;
		}

		static float Dot ( Vector3^ left, Vector3^ right )
		{
			return left->X*right->X + left->Y*right->Y + left->Z*right->Z;
		}

		static float AngleInRadians ( Vector3^ left, Vector3^ right )
		{
			return acos(Dot(left,right));
		}

		static float AngleInDegrees(Vector3^ left, Vector3^ right)
		{
			return ToDegree(AngleInRadians(left,right));
		}

		virtual System::String^ ToString() override
		{
			return x.ToString() + ", " + y.ToString() + ", " + z.ToString();
		}

	internal:
		property CVec3 Native
		{
			CVec3 get() { return CVec3( x, y, z ); }
		}
	};
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}	// namespace EditorNative
