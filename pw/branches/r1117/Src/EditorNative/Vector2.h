#pragma once
#include "Vector3.h"

namespace EditorNative
{
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	public ref class Vector2 sealed
	{
	private:
		float x;
		float y;

	public:
		Vector2( float _x, float _y );
		Vector2( Vector3^ v );

	internal:
		Vector2( const CVec2& native );

	public:
		property float X
		{
			float get() { return x; }
		}

		property float Y
		{
			float get() { return y; }
		}

		static property Vector2^ Zero
		{
			Vector2^ get() { return gcnew Vector2(0, 0 ); }
		}

		static Vector2^ operator + ( Vector2^ left, Vector2^ right )
		{
			return gcnew Vector2( left->Native + right->Native );
		}

		static Vector2^ operator - ( Vector2^ left, Vector2^ right )
		{
			return gcnew Vector2( left->Native - right->Native );
		}

		static Vector2^ operator * ( Vector2^ left, float right )
		{
			return gcnew Vector2( left->Native * right );
		}

		virtual System::String^ ToString() override
		{
			return x.ToString() + ", " + y.ToString();
		}

	internal:
		property CVec2 Native
		{
			CVec2 get() { return CVec2( x, y ); }
		}
	};
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}	// namespace EditorNative
