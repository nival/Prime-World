#pragma once

#define FP16_MIN_NORMAL_VALUE (1.e-4) //2^-14 
//#define FP16_MIN_SUBNORMAL_VALUE (1.e-7) //2^-24



//class is NOT tested yet!!!



class Float16
{
#pragma warning(disable:4201) //warning C4201: nonstandard extension used : nameless struct/union
	typedef union
	{
		struct 
		{
			unsigned short Mantissa : 10;		// intel
			unsigned short Exponent : 5;		// byte		
			unsigned short Sign : 1;				// order
		};
		unsigned short Encoded;
	} __float16;

	typedef union
	{
		struct 
		{
			unsigned __int32 Mantissa : 23;		// intel
			unsigned __int32 Exponent : 8;		// byte		
			unsigned __int32 Sign : 1;				// order
		};
		float Encoded;
	} __float32;
#pragma warning(default:4201)


public:

	__float16 fp16_value;

	Float16() {}

	explicit Float16( float _float32_value )
	{
		__float32 fp32_value;
		fp32_value.Encoded = _float32_value;
		if( abs(_float32_value) < FP16_MIN_NORMAL_VALUE ) //wan't handle subnormal float
		{
			fp16_value.Mantissa = 0;
			fp16_value.Exponent = 15;
			return;
		}

		if( fp32_value.Exponent > 158 )
		{
			NI_ALWAYS_ASSERT("can't pack such big number");
		}

		fp32_value.Encoded = _float32_value;
		
		fp16_value.Sign = fp32_value.Sign;

		fp16_value.Exponent = __int32(fp32_value.Exponent) - 127 + 15;
		fp16_value.Mantissa = unsigned short(fp32_value.Mantissa >> 13);
	}

	Float16& operator=(const float _float32_value)
	{
		__float32 fp32_value;
		fp32_value.Encoded = _float32_value;
		if( abs(_float32_value) < FP16_MIN_NORMAL_VALUE ) //wan't handle subnormal float
		{
			fp16_value.Mantissa = 0;
			fp16_value.Exponent = 15;
			return *this;
		}

		if( fp32_value.Exponent > 158 )
		{
			NI_ALWAYS_ASSERT("can't pack such big number");
		}

		fp32_value.Encoded = _float32_value;

		fp16_value.Sign = fp32_value.Sign;

		fp16_value.Exponent = __int32(fp32_value.Exponent) - 127 + 15;
		fp16_value.Mantissa = unsigned short(fp32_value.Mantissa >> 13);
		
		
		return *this;
	}


	operator float() const
	{
		__float32 fp32_result;
		if( fp16_value.Exponent == 0 )
		{
			// Zero or denormal. Just clamp to zero...
			fp32_result.Exponent = 0;
			fp32_result.Mantissa = 0;
		}
		else if (fp16_value.Exponent == 31)		// 2^5 - 1
		{
			// Infinity or NaN.
			fp32_result.Exponent = 255;
			fp32_result.Mantissa = DWORD(fp16_value.Mantissa) << 13;
		}
		else
		{
			// Normal number.
			fp32_result.Exponent = __int32(fp16_value.Exponent) - 15 + 127; // Stored exponents are biased by half their range.
			fp32_result.Mantissa = DWORD(fp16_value.Mantissa) << 13;
		}

		return fp32_result.Encoded;

	}

};
