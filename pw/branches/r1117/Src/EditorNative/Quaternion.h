#pragma once

#include "Vector3.h"

namespace EditorNative
{
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	public ref class Quaternion sealed
	{
	private:
		float x;
		float y;
		float z;
		float w;

	public:
		Quaternion( float _x, float _y, float _z, float _w );

	internal:
		Quaternion( const CQuat& native );

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

		property float W
		{
			float get() { return w; }
      void set( float value ) { w = value; }
		}

		property Quaternion^ Inverted
		{
			Quaternion^ get();
		}

		property float Yaw
		{
			float get();
      void set( float value );
		}

		property float Pitch
		{
			float get();
      void set( float value );
		}

		property float Roll
		{
			float get();
      void set( float value );
		}

		Vector3^ Rotate( Vector3^ vec );

		static Quaternion^ FromAngleAxis( double angle, Vector3^ axis );
		static Quaternion^ FromEulerAngles( Vector3^ eulerAngles );

    void DecompAngleAxis( [System::Runtime::InteropServices::OutAttribute] double% angle, [System::Runtime::InteropServices::OutAttribute] Vector3^% axis )
    {
      float ang;
      CVec3 ax;
      Native.DecompAngleAxis( &ang, &ax );
      angle = ang;
      axis = gcnew Vector3( ax.x, ax.y, ax.z );
    }

		static Quaternion^ operator * ( Quaternion^ left, Quaternion^ right );
		static Quaternion^ Normalize(Quaternion^ q){
			float length = sqrt(q->X*q->X+q->Y*q->Y+q->Z*q->Z+q->W*q->W);
			q->x/=length;
			q->y/=length;
			q->z/=length;
			q->w/=length;
			return q;
		}
		Vector3^ GetXAxis(){
			CVec3 res;
			Native.GetXAxis(&res);
			return gcnew Vector3( res );
		}
		Vector3^ GetYAxis(){
			CVec3 res;
			Native.GetYAxis(&res);
			return gcnew Vector3( res );
		}
		Vector3^ GetZAxis(){
			CVec3 res;
			Native.GetZAxis(&res);
			return gcnew Vector3( res );
		}
		property Vector3^ EulerAngles{
			Vector3^ get() {
				Vector3^ res = gcnew Vector3(0,0,0);
				res->X = ToDegree(Roll);
				res->Y = ToDegree(Pitch);
				res->Z = ToDegree(Yaw);
				return res;
			}	
		}
		static Quaternion^ FromToRotation(Vector3^ from, Vector3^ to){
			Quaternion^ q = gcnew Quaternion( 0, 0, 0, 1 );
			Vector3^ a = Vector3::Cross(from , to);
			q->x = a->X;
			q->y = a->Y;
			q->z = a->Z;
			q->w = sqrt((from->Length * from->Length) * (to->Length * to->Length)) + Vector3::Dot(from, to);
			q = Normalize(q);
			return q;
		}

		static property Quaternion^ Identity
		{
			Quaternion^ get() { return gcnew Quaternion( 0, 0, 0, 1 ); }
		}

		virtual System::String^ ToString() override
		{
			return x.ToString() + ", " + y.ToString() + ", " + z.ToString() + ", " + w.ToString();
		}

	internal:
		property CQuat Native
		{
			CQuat get() { return CQuat( CVec4( x, y, z, w ) ); }
		}
	};
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}	// namespace EditorNative
