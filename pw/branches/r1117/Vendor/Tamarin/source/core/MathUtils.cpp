/* ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is [Open Source Virtual Machine.].
 *
 * The Initial Developer of the Original Code is
 * Adobe System Incorporated.
 * Portions created by the Initial Developer are Copyright (C) 2004-2006
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *   Adobe AS3 Team
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either the GNU General Public License Version 2 or later (the "GPL"), or
 * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the MPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the MPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */

#include "avmplus.h"
#include "BigInteger.h"

//GCC only allows intrinsics if sse2 is enabled
#if (defined(_MSC_VER) || (defined(__GNUC__) && defined(__SSE2__))) && (defined(AVMPLUS_IA32) || defined(AVMPLUS_AMD64))
    #include <emmintrin.h>
#endif

namespace avmplus
{
	const double kLog2_10 = 0.30102999566398119521373889472449;

	// optimize pow(10,x) for commonly sized numbers;
	static const double kPowersOfTen[23] = { 1, 1e1, 1e2, 1e3, 1e4, 1e5, 1e6, 1e7, 1e8, 1e9, 1e10,
									   1e11, 1e12, 1e13, 1e14, 1e15, 1e16, 1e17, 1e18, 1e19, 1e20,
									   1e21, 1e22 };

	static inline double quickPowTen(int32_t exp)
	{
		if (exp < 23 && exp > 0) {
			return kPowersOfTen[exp];
		} else {
			return MathUtils::pow(10,exp);
		}
	}

	// skipSpaces: skip whitespace characters

	static int32_t skipSpaces(const StringIndexer& s, int32_t index)
	{
		while (index < s->length())
		{
			uint32_t ch = s[index];
			if (!(ch == ' ' || ch == '\t' || ch == '\r' || ch == '\n' || ch == '\f' || ch == '\v' || 
				 (ch >= 0x2000 && ch <=0x200b) || ch == 0x2028 || ch == 0x2029 || ch == 0x205f || ch == 0x3000 ))
				break;
			index++;
		}
		return index;
	}

	// handleSign: helper function which checks for sign indicator
	//

	int32_t handleSign(const StringIndexer& s, int32_t index, bool& negative)
	{
		negative = false;
		if (index >= s->length())
			return index;
		uint32_t ch = s[index];
		if (ch == '+') {
			index++;
		} else if (ch == '-') {
			negative = true;
			index++;
		}
		return index;
	}

	bool MathUtils::equals(double x, double y)
	{
		// Infiniti-ness must match up
		if (isInfinite(x) != isInfinite(y)) {
			return false;
		}
		// Nothing is equal to NaN, not even itself.
		if (isNaN(x) || isNaN(y)) {
			return false;
		}
		return x == y;
	}

	static double _nan()
	{
		union { float f; uint32_t d; }; d = 0x7FFFFFFF;
		return f;
	}

	static double _infinity()
	{
		union { float f; uint32_t d; }; d = 0x7F800000;
		return f;
	}

	static double _neg_infinity()
	{
		union { float f; uint32_t d; }; d = 0xFF800000;
		return f;
	}


	/*static*/ const double MathUtils::kNaN = _nan();
	/*static*/ const double MathUtils::kInfinity = _infinity();
	/*static*/ const double MathUtils::kNegInfinity = _neg_infinity();

#ifdef UNIX
	/*
	 * MathUtils::isNaN and MathUtils::isInfinite are modified versions of
	 * s_isNaN.c and s_isInfinite.c, freely usable code by Sun.  Copyright follows:
	 *======================================================
	 * Copyright (C) 1993 by Sun Microsystems, Inc.  All rights reserved.
	 *
	 * Developed at SunPro, a Sun Microsystems, Inc. business.
	 * Permission to use, copy, modify and distribute this
	 * software is freely granted, provided that this notice is preserved.
	 *======================================================
	 */

	union double_overlay {
		double value;
		#if defined AVMPLUS_BIG_ENDIAN || defined VMCFG_DOUBLE_MSW_FIRST
			struct { uint32_t msw, lsw; } parts;
		#else
			struct { uint32_t lsw, msw; } parts;
		#endif
	};
		

	int32_t MathUtils::isInfinite(double x)
	{
		double_overlay u;
		u.value = x;

		int32_t hx = u.parts.msw;
		int32_t lx = u.parts.lsw;

		lx |= (hx & 0x7FFFFFFF) ^ 0x7FF00000;
		lx |= -lx;
		return ~(lx >> 31) & (hx >> 30);
	}

	bool MathUtils::isNaN(double x)
	{
		// Infinity is NOT considered NaN in
		// JavaScript
		if (MathUtils::isInfinite(x) != 0) {
			return false;
		}

		double_overlay u;
		u.value = x;

		int32_t hx = u.parts.msw;
		int32_t lx = u.parts.lsw;

		hx &= 0x7FFFFFFF;
		hx |= (uint32_t) (lx | (-lx)) >> 31;
		hx = 0x7FF00000 - hx;
		return (bool) (((uint32_t)(hx) >> 31) != 0);
	}

	bool MathUtils::isNegZero(double x)
	{
		double_overlay u;
		u.value = x;

		int32_t hx = u.parts.msw;
		int32_t lx = u.parts.lsw;

		return (hx == (int32_t)0x80000000 && lx == (int32_t)0x0);
	}

#else
	
	/*
	 * double precision special value tests:

	     inf = 7FF0 0000 0000 0000
	           FFF0 0000 0000 0000

	     nan = 7FFx xxxx xxxx xxxx where x != 0
		       FFFx xxxx xxxx xxxx
     */

	int32_t MathUtils::isInfinite(double x)
	{
		union { double d; uint64 v; }; d = x;
		if ((v & 0x7fffffffffffffffLL) != 0x7FF0000000000000LL)
			return 0;
		if (v & 0x8000000000000000LL)
			return -1;
		else
			return 1;
	}

	bool MathUtils::isNaN(double value)
	{
		union {
			  double dvalue;
			  uint64 lvalue;
		};
		dvalue = value;
		return ( ( int64(lvalue) & ~0x8000000000000000ULL ) > 0x7ff0000000000000ULL ); 
		//return x != x;
	}

	bool MathUtils::isNegZero(double x)
	{
		union { double d; uint64 v; }; d = x;
		return (v == 0x8000000000000000LL);
	}

#endif // UNIX

	int32_t MathUtils::nextPowerOfTwo(int32_t n)
	{
		int32_t i = 2;
		while (i < n)
		{
			i <<= 1;
		}

		return (i);
	}

	static bool isHexNumber(const StringIndexer& s, int32_t index)
	{
		if (s->length() - index < 2 || s[index] != '0')
			return false;
		uint32_t ch = s[index+1];
		return (ch == 'x' || ch == 'X');
	}

	// parseIntDigit: Helper for ParseInt and ConvertStringToInteger
	//

	static int32_t parseIntDigit(wchar ch)
	{
		if (ch >= '0' && ch <= '9') {
			return (ch - '0');
		} else if (ch >= 'a' && ch <= 'z') {
			return (ch - 'a' + 10);
		} else if (ch >= 'A' && ch <= 'Z') {
			return (ch - 'A' + 10);
		} else {
			return -1;
		}
	}

	// parseInt: Implementation of ECMA-262 parseInt function
	double MathUtils::parseInt(Stringp inStr, int32_t radix /*=10*/, bool strict /*=false*/ )
	{
		bool negate;
		bool gotDigits = false;
		double result = 0;

		StringIndexer s(inStr);
		int32_t index = skipSpaces(s, 0); // leading and trailing whitespace is valid.
		index = handleSign(s, index, negate);
		if (isHexNumber(s, index) && (radix == 16 || radix == 0) ) {
			index += 2;
			if (radix == 0)
				radix = 16;
		} else if (radix == 0) {
		    // default radix is 10
			radix = 10;
		}

		// Make sure radix is valid, and we have digits
		if (radix >= 2 && radix <= 36 && index < s->length()) {
				result = 0;
				int32_t start = index; 

				// Read the digits, generate result
				while (index < s->length()) {
					int32_t v = parseIntDigit(s[index]);
					if (v == -1 || v >= radix) {
						break;
					}
					result = result * radix + v;
					gotDigits = true;
					index++;
				}
				
				index = skipSpaces(s, index); // leading and trailing whitespace is valid.
				if (strict && index < s->length()) {
					return MathUtils::kNaN;
				}

			if ( result >= 0x20000000000000LL &&  // i.e. if the result may need at least 54 bits of mantissa
					(radix == 2 || radix == 4 || radix == 8 || radix == 16 || radix == 32) )  {

				// CN:  we're here because we may have incurred roundoff error with the above.  
				//  Error will creep in once we need more than the available 53 bits
				//  of precision in the mantissa portion of a double.  No way to deduce
				//  this from the result, so we have to recalculate it more slowly.
				result = 0;

				int32_t powOf2 = 1;
				for(int32_t x = radix; (x != 1); x >>= 1)
					powOf2++;
				powOf2--; // each word contains one less than this # of bits.
				index = start;
				int32_t v=0;
				
				int32_t end,next;
				// skip leading zeros
				for(end=index; end < s->length() && s[end] == '0'; end++)
					;
				if (end >= s->length())
					return 0;

				for (next=0; next*powOf2 <= 52; next++) { // read first 52 non-zero digits.  Once charPosition*log2(radix) is > 53, we can have rounding issues
					v = parseIntDigit(s[end++]);
					if (v == -1 || v >= radix) {
						v = 0;
						break;
					}
					result = result * radix + v;
					if (end >= s->length())
						break;
				}
				if (next*powOf2 > 52) { // If number contains more than 53 bits of precision, may need to roundUp last digit processed.
					bool roundUp = false;
					int32_t bit53 = 0;
					int32_t bit54 = 0;

					double factor = 1;

					switch(radix) {
					case 32:  // last word read contained digits 51,52,53,54,55
						bit53 = v & (1 << 2);
						bit54 = v & (1 << 1);
						roundUp = (v & 1);
						break;
					case 16:  // last word read contained digits 50,51,52,53
						bit53 = v & (1 << 0);
						v = parseIntDigit(s[end]);
						if (v != -1 && v < radix) {
							factor *= radix;
							bit54 = v & (1 << 3);
							roundUp = (v & 0x3) != 0;  // check if any bit after bit54 is set
						} else {
							roundUp = bit53 != 0;
						}
						break;
					case 8: // last work read contained digits 49,50,51, next word contains 52,53,54
						v = parseIntDigit(s[end]);
						if (v == -1 || v >= radix) {
							v = 0;
						}
						factor *= radix;
						bit53 = v & (1 << 1);
						bit54 = v & (1 << 0);
						break;
					case 4: // 51,52 - 53,54
						v = parseIntDigit(s[end]);
						if (v == -1 || v >= radix) {
							v = 0;
						}
						factor *= radix;
						bit53 = v & (1 << 1);
						bit54 = v & (1 << 0);
						break;
					case 2: // 52 - 53 - 54
						/*
						v = parseIntDigit(s[end++]);
						result = result * radix;  // add factor before round-off adjustment for 52 bit
						*/
						bit53 = v & (1 << 0);
						v = parseIntDigit(s[end]);
						if (v != -1 && v < radix) {
							factor *= radix;
							bit54 = (v != -1 ? (v & (1 << 0)) : 0); // Might be there are only 53 digits.
						}

						break;
					}
					
					bit53 = !!bit53;
					bit54 = !!bit54;
					
					
					while(++end < s->length()) {
						v = parseIntDigit(s[end]);
						if (v == -1 || v >= radix) {
							break;
						}
						roundUp |= (v != 0); // any trailing positive bit causes us to round up
						factor *= radix;
					}
					roundUp = bit54 && (bit53 || roundUp);
					result += (roundUp ? 1.0 : 0.0);
					result *= factor;
				}
				
			}
			/*
			else if (radix == 10 && result >= 0x20000000000000)
			// if there are more than 15 digits, roundoff error may affect us.  Need to use exact integer rep instead of float
			//int32_t numDigits = len - (s - sStart);
			*/
			if (negate) {
				result = -result;
			}
		}
		return gotDigits ? result : MathUtils::kNaN;
	}

	// used by AvmCore::number() and numberAtom() for converting arbitrary string to a number.
	double MathUtils::convertStringToNumber(Stringp inStr)
	{
		double value;

		if (inStr->length() == 0) { // toNumber("") should be 0, not NaN
			value = 0;
		} else if (MathUtils::convertStringToDouble(inStr, &value, true)) {
			// nothing to do, value set by side effect.
		} else  {
			value = MathUtils::parseInt(inStr, 0,true); // 0 radix means figure it out from the string.
		}
		return value;
	}

	double MathUtils::round(double value)
	{
		return MathUtils::floor(value + 0.5);
	}
	
	// apparently SunPro compiler doesn't like combining REALLY_INLINE with static functions.
	/*static*/
	REALLY_INLINE int32_t real_to_int(double value)
	{
#if defined(WIN32) && defined(AVMPLUS_AMD64)
		int32_t intValue = _mm_cvttsd_si32(_mm_set_sd(value));
#elif defined(WIN32) && defined(AVMPLUS_IA32)
		int32_t intValue;
		_asm fld [value];
		_asm fistp [intValue];
#elif defined(_MAC) && (defined(AVMPLUS_IA32) || defined(AVMPLUS_AMD64))
		int32_t intValue = _mm_cvttsd_si32(_mm_set_sd(value));
#else
		int32_t intValue = MathUtils::real2int(value);
#endif
		return intValue;
	}

	// MathUtils::toInt is the ToInteger algorithm from
	// ECMA-262 section 9.4
	double MathUtils::toInt(double value)
	{
		int32_t intValue = real_to_int(value);

		if ((value == (double)(intValue)) && ((uint32_t)intValue != 0x80000000))
			return value;

		if (MathUtils::isNaN(value)) {
			return 0;
		}
		if (MathUtils::isInfinite(value) || value == 0) {
			return value;
		}
		if (value < 0) {
			return -MathUtils::floor(-value);
		} else {
			return MathUtils::floor(value);
		}
	}

	int32_t MathUtils::toIntClamp(double value, int32_t clampMagnitude)
	{
		AvmAssert(clampMagnitude >= 0);
		
		if (MathUtils::isNaN(value)) 
			return 0;
	
		int32_t const inf = MathUtils::isInfinite(value);
		if (inf > 0)
			return clampMagnitude;
		else if (inf < 0)
			return -clampMagnitude;

		//
		// clamp first, so we know the double is in an integer range.
		// 
		double const clampMag = (double)clampMagnitude;
		if (value > clampMag)
			value = clampMag;
		else if (value < -clampMag)
			value = -clampMag;

		int32_t intValue = real_to_int(value);

		if (value != (double)(intValue))
		{
			// alas, have to round, then reconvert.
			if (value < 0) 
				value = -MathUtils::floor(-value);
			else 
				value = MathUtils::floor(value);

			intValue = real_to_int(value);
		}
	
		return intValue;
	}

	//
	// powerOfTen(exponent, value) returns the value
	//    value * 10 ^ exponent
	//

	double MathUtils::powerOfTen(int32_t exponent, double value)
	{
		double base = 10.0;

		if (exponent < 0) {
			exponent = -exponent;
			while (exponent) {
				if (exponent & 1) {
					value /= base;
				}
				exponent >>= 1;
				base *= base;
			}
		} else {
			while (exponent) {
				if (exponent & 1) {
					value *= base;
				}
				exponent >>= 1;
				base *= base;
			}
		}
		return value;
	}

	//
	// powInt(base, exponent) returns the value
	//    base ^ exponent
	// where exponent is an integer.
	//
	static double powInt(double base, int32_t exponent)
	{
		double value = 1.0;
		double original_base = base;
		int32_t original_exponent = exponent;

		if (MathUtils::isInfinite(base))
		{
			if (exponent < 0) // return -0 or 0 depending on sign of base
				return (base < 0) ? 1.0/base : 0.0;

			// if base is -Infinity, return Infinity or -Infinity depending whether the exponent is even or not.
			if (base < 0) 
				return (MathUtils::mod(exponent, 2) != 0) ? base : 0-base;

			return base;
		}

		if (exponent < 0) {
			exponent = -exponent;
			while (exponent) {
				if (exponent & 1) {
					value /= base;
				    // cn: max double value is magnitude 1e308 (base 10), but min double value is magnitude 1e-324
				    // That means we can't invert the exponent when the base ten value exponent is < 307.  
				    //  We could first check if powerOfTwo(base)*exp > 1074, but that would
				    //  slow down all powInts calls.  This limits the xtra work to just very small numbers.
					if (value == 0 && base != 0) // double check by calling the real thing
						return MathUtils::powInternal(original_base,(double)original_exponent);
				}
				exponent >>= 1;
				base *= base;
			}
		} else {
			while (exponent) {
				if (exponent & 1) {
					value *= base;
				}
				exponent >>= 1;
				base *= base;
			}
		}
		return value;
	}

	// x = base, y = exponent
	double MathUtils::pow(double x, double y)
	{
		if (MathUtils::isNaN(y)) {
			// x^NaN = NaN
			return MathUtils::kNaN;
		}

		if (y == 0) {
			// x^0 is 1 for all x
			return 1;
		}

		int32_t infy = MathUtils::isInfinite(y);

		if (infy == 0 && y == (int32_t)y) {
			// If y is an integer, use multiplication
			// algorithm which yields more accurate
			// results
			return powInt(x, (int32_t)y);
		}
		
		double absx = MathUtils::abs(x);

		if (absx < 1) {
			infy = -infy;
		}
		if (absx == 1 && infy != 0) {
			// (+/-)1^(+/-)Infinity = NaN
			return MathUtils::kNaN;
		}
		if (infy == 1) {
			// x^Infinity = Infinity
			return MathUtils::kInfinity;
		} else if (infy == -1) {
			// x^-Infinity = +0
			return +0;
		}

		if (MathUtils::isInfinite(x))
		{
			if (y < 0) {
				// y<0
				// Infinity^y = 0
				// -Infinity^y = 0
				return 0;
			} else {
				if (y < 1.0) {
					return MathUtils::kInfinity;
				} else {
					// y>0
					// Infinity^y = Infinity
					// -Infinity^y = Infinity
					return x;
				}
			}
		}
 
		// R41
		// Handle negative x.
		if (x < 0.0) {
			// If y is non-integer, return NaN.
			if (y != MathUtils::floor(y)) {
				return MathUtils::kNaN;
			}
			// Switch sign of base
			x = -x;
			// If exponent is odd, negate result
			if (MathUtils::mod(y, 2) != 0) {
				return -powInternal(x, y);
			}
			// Else do the usual thing.
		}
		// end R41

		// Bug 33811 - Windows math returns NaN incorrectly when base = 0.0
		if (x == 0.0)
		{
			if (y < 0.0)
				return MathUtils::kInfinity;
			else
				return 0.0;
		}

		return powInternal(x, y);
	}

	int32_t MathUtils::nextDigit(double *value)
	{
		int32_t digit;

		#if defined(WIN32) && defined(AVMPLUS_AMD64)
		digit = _mm_cvttsd_si32(_mm_set_sd(*value));
		#elif defined(WIN32) && defined(AVMPLUS_IA32)
		// WARNING! nextDigit assumes that rounding mode is
		// set to truncate.
		_asm mov eax,[value];
		_asm fld qword ptr [eax];
		_asm fistp [digit];
		#elif defined(_MAC) && (defined(AVMPLUS_IA32) || defined(AVMPLUS_AMD64))
		digit = _mm_cvttsd_si32(_mm_set_sd(*value));
		#else
		digit = (int32_t) *value;
		#endif

		*value -= digit;
		*value *= 10;
		return digit;
	}

	int32_t MathUtils::roundInt(double x)
	{
		if (x < 0) {
			return (int32_t) (x - 0.5);
		} else {
			return (int32_t) (x + 0.5);
		}
	}

	Stringp MathUtils::convertIntegerToStringRadix(AvmCore* core,
											  intptr_t value,
											  int32_t radix,
											  UnsignedTreatment treatAs)
	{
		MMgc::GC::AllocaAutoPtr _buffer;
		char* buffer = (char*)VMPI_alloca(core, _buffer, kMinSizeForInt64_t_toString);
		int32_t len = kMinSizeForInt64_t_toString;
		char* p = convertIntegerToStringBuffer(value, buffer, len, radix, treatAs);
		return core->newStringLatin1(p, len);
	}

	Stringp MathUtils::convertIntegerToStringBase10(AvmCore* core,
											  int32_t  value,
											  UnsignedTreatment treatAs)
	{
		char buffer[kMinSizeForInt32_t_base10_toString];
		int32_t len = kMinSizeForInt32_t_base10_toString;
	#ifdef AVMPLUS_64BIT
		intptr_t wideVal = treatAs == kTreatAsUnsigned ? (intptr_t)(uint32_t)value : (intptr_t)value;
	#else
		intptr_t wideVal = (intptr_t) value;
	#endif
		char* p = convertIntegerToStringBuffer(wideVal, buffer, len, 10, treatAs);
		return core->newStringLatin1(p, len);
	}

	char* MathUtils::convertIntegerToStringBuffer(intptr_t value,
								            char *buffer,
										    int32_t& len,
								            int32_t radix,
										    UnsignedTreatment treatAs)
	{		
		#ifndef AVMPLUS_64BIT
		// This routines does not work with this integer number since negating
		// this value returns the same negative value and screws up our code 
		// in the while loop below.
		if ( (uint32_t)value == 0x80000000 && treatAs == kTreatAsSigned) 
		// MathUtils::convertIntegerToString doesn't deal with this number because you can't negate it.
		{
			AvmAssert(len >= 12);
			if (len < 12)
				return NULL;
			VMPI_memcpy (buffer, "-2147483648", 12);
			len = 11;
			return buffer;
		}
		#endif

		if (radix < 2 || radix > 36) 
		{
			AvmAssert( 0 );
			return NULL;
		}

		char *src = buffer + len - 1;
		char *srcEnd = src;

		*src-- = '\0';

		if (value == 0)
		{
			*src-- = '0';
		}
		else
		{
			uintptr uVal;
			bool negative=false;

			if (treatAs == kTreatAsUnsigned)
			{
				uVal = (uintptr)value;
			}
			else
			{
				negative = (value < 0);
				if (negative)
					value = -value;
				uVal = (uintptr)value;
			}

			while (uVal != 0)
			{
				// buffer too small?
				AvmAssert(src >= buffer);
				uintptr j = uVal;
				uVal = uVal / radix;
				j -= (uVal * radix);

				*src-- = (char)((j < 10) ? (j + '0') : (j + ('a' - 10)));
			}

			if (negative)
			{
				AvmAssert(src >= buffer);
				if (src < buffer)
					// buffer too small
					return NULL;
				*src-- = '-';
			}
		}

		src++;
		len = (int32_t)(srcEnd-src);

		return src;
	}

	Stringp MathUtils::convertDoubleToStringRadix(AvmCore *core,
												  double value,
										          int32_t radix)
	{
		if (radix < 2 || radix > 36) 
		{
			AvmAssert( 0 );
			return NULL;
		}

		MMgc::GC::AllocaAutoPtr _tmp;
		char* tmp = (char*)VMPI_alloca(core, _tmp, kMinSizeForDouble_base2_toString);
		char *src = tmp + kMinSizeForDouble_base2_toString - 1;
		char *srcEnd = src;

		bool negative=false;

		negative = (value < 0);
		if (negative)
			value = -value;

		if (value < 1)
		{
			*src-- = '0';
		}
		else
		{
			double uVal = MathUtils::floor(value);

			while (uVal != 0)
			{
				double j = uVal;
				uVal = MathUtils::floor(uVal / radix);
				j -= (uVal * radix);

				*src-- = (char)((j < 10) ? ((int32_t)j + '0') : ((int32_t)j + ('a' - 10)));

				AvmAssert(src >= tmp || 0 == uVal);
			}

			if (negative)
				*src-- = '-';
		}

		int32_t len = (int32_t)(srcEnd-src);
		return core->newStringLatin1(src+1, len);
	}
	
	Stringp MathUtils::convertDoubleToString(AvmCore* core,
											 double value,
										     int32_t mode,
										     int32_t precision)
	{
		switch (isInfinite(value)) {
		case -1:
			return core->newConstantStringLatin1("-Infinity");
		case 1:
			return core->newConstantStringLatin1("Infinity");
		}
		if (isNaN(value)) {
			return core->newConstantStringLatin1("NaN");
		}

		// If our double is really an integer, call our integer version which
		// is much, much faster then our double version.  (Skips a ton of _ftol
		// which are slow).
		if (mode == DTOSTR_NORMAL) {
#if defined(WIN32) && defined(AVMPLUS_AMD64)
			int32_t intValue = _mm_cvttsd_si32(_mm_set_sd(value));
#elif defined(WIN32) && defined(AVMPLUS_IA32)
			int32_t intValue;
			_asm fld [value];
			_asm fistp [intValue];
#elif defined(_MAC) && (defined(AVMPLUS_IA32) || defined(AVMPLUS_AMD64))
			int32_t intValue = _mm_cvttsd_si32(_mm_set_sd(value));
#else
			int32_t intValue = real2int(value);
#endif
			if ((value == (double)(intValue)) && ((uint32_t)intValue != 0x80000000))
				return convertIntegerToStringBase10(core, intValue, kTreatAsSigned);
		}
		
		int32_t i, len = 0;

		MMgc::GC::AllocaAutoPtr _buffer;
		char* buffer = (char*)VMPI_alloca(core, _buffer, kMinSizeForDouble_base10_toString);
		char *s = buffer;
		bool negative = false;

		// Deal with negative numbers
		if (value < 0) {
			value = -value;
			negative = true;
			// make room for minus sign later (after applying sentinel)
			s++;
		}

		// initialize d2a engine
		D2A *d2a = mmfx_new(D2A(value, mode, precision));
		int32_t exp10 = d2a->expBase10()-1;
		
		// Sentinel is used for rounding
		char *sentinel = s;

		enum {
			kNormal,
			kExponential,
			kFraction,
			kFixedFraction
		};
		int32_t format;
		int32_t digit;

		switch (mode) {
		case DTOSTR_FIXED:
			{
				if (exp10 < 0) {
					format = kFixedFraction;
				} else {
					format = kNormal;
					precision++;
				}
			}
			break;
		case DTOSTR_PRECISION:
			{
				if (exp10 < 0) {
					format = kFraction;
				} else if (exp10 >= precision) {
					format = kExponential;
				} else {
					format = kNormal;
				}
			}
			break;
		case DTOSTR_EXPONENTIAL:
			format = kExponential;
			precision++;
			break;
		default:
			if (exp10 < 0 && exp10 > -7) {
				// Number is of form 0.######
				if (exp10 < -precision) {
					exp10 = -precision-1;
				}
				format = kFraction;
			} else if (exp10 > 20) { // ECMA spec 9.8.1
				format = kExponential;
			} else {
				format = kNormal;
			}
		}

		#if 0 // ifdef WIN32
		// On Windows, set the FPU control word to round
		// down for the rest of this operation.
		volatile uint16 oldcw;
		volatile uint16 newcw;
		_asm fnstcw [oldcw];
		_asm mov ax,[oldcw];
		_asm or ax,0xc3f;
		_asm mov [newcw],ax;
		_asm fldcw [newcw];
		#endif
		
		bool wroteDecimal = false;
		switch (format) {
		case kNormal:
			{
				int32_t digits = 0;
				sentinel = s;
				*s++ = '0';
				digit = d2a->nextDigit(); 
				if (digit > 0) {
					*s++ = (char)(digit + '0');
				}
				while (exp10 > 0) {
					digit = (d2a->finished) ? 0 : d2a->nextDigit();
					*s++ = (char)(digit + '0');
					exp10--;
					digits++;
				}
				if (mode == DTOSTR_FIXED) {
					digits = 0;
				}
				if (mode == DTOSTR_NORMAL) {
					if (!d2a->finished) {
						*s++ = '.';
						wroteDecimal = true;
						while( !d2a->finished ) {
							*s++ = (char)(d2a->nextDigit() + '0');
						}
					}
				}
				else if (digits < precision-1)
				{
					*s++ = '.';
					wroteDecimal = true;
					for (; digits < precision-1; digits++) {
						digit = d2a->finished ? 0 : d2a->nextDigit();
						*s++ = (char)(digit + '0');
					}
				}
			}
			break;
		case kFixedFraction:
			{
				*s++ = '0'; // Sentinel
				*s++ = '0';
				*s++ = '.';
				wroteDecimal = true;
				// Write out leading zeros
				int32_t digits = 0;
				if (exp10 > 0) {
					while (++exp10 < 10 && digits < precision) {
						*s++ = '0';
						digits++;
					}
				} else if (exp10 < 0) {
					while ((++exp10 < 0) && (precision-- > 0))
						*s++ = '0';
				}

				// Write out significand
				for ( ; digits<precision; digits++) {
					if (d2a->finished)
					{
						if (mode == DTOSTR_NORMAL)
							break;
						*s++ = '0';
					} else {
						*s++ = (char)(d2a->nextDigit() + '0');
					}
				}
				exp10 = 0;
			}
			break;
		case kFraction:
			{
				*s++ = '0'; // Sentinel
				*s++ = '0';
				*s++ = '.';
				wroteDecimal = true;

				// Write out leading zeros
				if (value)
				{
					for (i=exp10; i<-1; i++) {
						*s++ = '0';
					}
				}

				// Write out significand
				i=0;
				while (!d2a->finished)
				{
					*s++ = (char)(d2a->nextDigit() + '0');
					if (mode != DTOSTR_NORMAL && ++i >= precision)
						break;
				}
				if (mode == DTOSTR_PRECISION)
				{
					while(i++ < precision)
						*s++ = (char)(d2a->finished ? '0' : d2a->nextDigit() + '0');
				}
				exp10 = 0;
			}
			break;
		case kExponential:
			{
				digit = d2a->finished ? 0 : d2a->nextDigit(); 
				*s++ = (char)(digit + '0');
				if ( ((mode == DTOSTR_NORMAL) && !d2a->finished) ||
					 ((mode != DTOSTR_NORMAL) && precision > 1) ) {
					*s++ = '.';
					wroteDecimal = true;
					for (i=0; i<precision-1; i++) {
						if (d2a->finished)
						{
							if (mode == DTOSTR_NORMAL)
								break;
							*s++ = '0';
						} else {
							*s++ = (char)(d2a->nextDigit() + '0');
						}
					}
				}
			}
			break;
		}

		// Rounding  (todo: argh, was hoping to get rid of this, but we still need it for fastEstimate mode)
		// fix bug 121952: must also do rounding for fixed mode
		if (d2a->bFastEstimateOk || mode == DTOSTR_FIXED || mode == DTOSTR_PRECISION)
		{
			i = d2a->nextDigit();
			if (i > 4) {
				char *ptr = s-1;
				while (ptr >= buffer) {
					if (*ptr < '0') {
						ptr--;
						continue;
					}
					(*ptr)++;
					if (*ptr != 0x3A) {
						break;
					}
					*ptr-- = '0';
				}
			}
			if (mode == MathUtils::DTOSTR_NORMAL && wroteDecimal) {
				// Remove trailing zeros
				while (*(s-1) == '0') {
					s--;
				}
				if (*(s-1) == '.') {
					s--;
				}
			}
		}

		if (exp10) {
			char *firstNonZero = buffer + int(negative);
			while (firstNonZero < s && *firstNonZero == '0') {
				firstNonZero++;
			}
			if (s == firstNonZero) {
				// Deal with case where all digits were
				// rounded away
				*s++ = '1';
				exp10++;
			} else {
				char *lastNonZero = s;
				while (lastNonZero > firstNonZero) {
					if (*--lastNonZero != '0') {
						break;
					}
				}
				if (value && (firstNonZero == lastNonZero) ) {
					// Watch out for extra zeros like
					// 10e+95
					exp10 += (int32_t) (s - firstNonZero - 1);
					s = lastNonZero+1;
				}
			}				
			*s++ = 'e';
			if (exp10 > 0) {
				*s++ = '+';
			}
			char expstr[kMinSizeForInt32_t_base10_toString];
			len = kMinSizeForInt32_t_base10_toString;
			char* t = convertIntegerToStringBuffer(exp10, expstr, len, 10, kTreatAsSigned);
			while (*t) { *s++ = *t++; }
		}
  
		len = (int32_t)(s-buffer);
		s = buffer;
		if (negative)
			s++;
		if (sentinel && sentinel[0] == '0' && sentinel[1] != '.') {
			s = sentinel + 1;
			len--;
		}
		if (negative)
			*--s = '-';

		#if 0 // def WIN32
		// Restore control word
		_asm fldcw [oldcw];
		#endif

		mmfx_delete(d2a);

		return core->newStringLatin1(s, len);
	}

	// convertStringToDouble: Converts an ASCII string in the form
	//     [+-]######.######e[+-]###
	// to a double-precision floating-point number
	//
	bool MathUtils::convertStringToDouble(Stringp inStr,
										  double *value,
										  bool strict /*=false*/ )
	{
		bool negate;
		int32_t numDigits = 0;
		int32_t exp10 = 0;
		double result = 0;
		uint32_t ch = 0;

		StringIndexer s(inStr);
		int32_t index = skipSpaces(s, 0);

		if (index >= s->length()) // empty string or string of spaces == 0
		{
			*value = 0;
			return (strict ? true : false); // odd use of strict, but Number('  ') is 0 and that uses strict == true.  parseFloat('  ') is NaN and that uses strict == false
		}

		index = handleSign(s, index, negate);

		// Pass 1: Validate input and determine exponents.
		int32_t start = index;
		while (index < s->length()) {
			ch = s[index];
			if (ch >= '0' && ch <= '9') {
				numDigits++;
				index++;
			}
			else
				break;
		}

		// If decimal point encountered, read past digits
		// to right of decimal point.
		if (ch == '.') {
			while (++index < s->length()) {
				ch = s[index];
				if (ch >= '0' && ch <= '9') {
					numDigits++;
				}
				else
					break;
			}
		}

		// Handle exponent
		if (index < s->length() && (s[index] == 'e' || s[index] == 'E')) {
			int32_t num = 0;
			bool negexp;
			index = handleSign(s, ++index, negexp);
			if (negexp && index >= s->length()) // fail if string ends in "e-" with no exponent value specified.
				return false;

			while (index < s->length()) {
				ch = s[index];
				if (ch >= '0' && ch <= '9') {
					num = num * 10 + (ch - '0');
					index++;
				}
				else
					break;
			}
			if (negexp) {
				num = -num;
			}
			exp10 += num;
		}
		// ecma3 compliant to allow leading and trailing whitespace
		index = skipSpaces(s, index);

		// If we got no digits, check for Infinity/-Infinity, else fail
		if (numDigits == 0) {
			// check for the strings "Infinity" and "-Infinity"
			if (s->matchesLatin1("Infinity", 8, index)) {
				index += 8;
				// there may be trailing whitespace
				if (index < s->length() && skipSpaces(s, index) == index)
					return false;
				*value = (negate ? MathUtils::kNegInfinity : MathUtils::kInfinity);
				return true;
			}
			return false;
		}

		// If we got digits, but we're in strict mode and not at end of string, fail.
		if (index < s->length() && strict) {
			return false;
		}

		// Pass 2: We've validated the input, now calculate the result.

		// Read all the digits
		// cn: multiplyinging by negative powers of ten injects roundoff errors.
		/*
		while ((*s >= '0' && *s <= '9') || *s == '.') {
			if (*s != '.') {
				result += powerOfTen(exp10--, *s - '0');
			}
			s++;
		}
		*/
		index = start;
		if (numDigits > 15) // after 15 digits, we can run into roundoff error
		{
			BigInteger exactInt;
			exactInt.setFromInteger(0);
			int32_t decimalDigits= -1;
			while (index < s->length()) {
				ch = s[index];
				if ((ch >= '0' && ch <= '9') || ch == '.') {
					if (decimalDigits != -1) {
						decimalDigits++;
					}
					if (ch != '.') {
						exactInt.multAndIncrementBy(10, ch - '0');
					} else {
						decimalDigits=0;
					}
					index++;
				}
				else
					break;
			}
			if (decimalDigits > 0) {
				exp10 -= decimalDigits;
			}
			if (exp10 > 0) {
				exactInt.multBy(quickPowTen(exp10));
				exp10 = 0;
			}
			//  This is an approximation which is at most off by 1.  To gain complete accuracy, we need to implement
			//   the algorithm commented out below 
			result = exactInt.doubleValueOf();
			if (exp10 < 0) {
				if (exp10 < -307) { // max positive value is e308. min neg value is e-324  Avoid overflow
					int32_t diff = exp10 + 307;
					result /= quickPowTen(-diff);
					exp10 -= diff;
				}
				result /= quickPowTen(-exp10); // actually more accurate than multiplying by negative power of 10
			}
		}
		else // we can use double
		{
			int32_t decimalDigits= -1;
			while (index < s->length())
			{
				ch = s[index];
				if ((ch >= '0' && ch <= '9') || ch == '.') {
					if (decimalDigits != -1) {
						decimalDigits++;
					}
					if (ch != '.') {
						result = result*10 + ch - '0';
					} else {
						decimalDigits=0;
					}
					index++;
				}
				else
					break;
			}
			if (decimalDigits > 0) {
				exp10 -= decimalDigits;
			}
			if (exp10 >= 0) {
				result *= quickPowTen(exp10);
			
			} else {			
				if (exp10 < -307) { // max positive value is e308.  min neg value is e-324. Avoid overflow
					int32_t diff = exp10 + 307;
					result /= quickPowTen(-diff);
					exp10 -= diff;
				}
				result /= quickPowTen(-exp10); // actually more accurate than multiplying by negative power of 10
			}
		}

		*value = negate ? -result : result;
		return true;
	}

		// cn: The following Alg is based on William Clinger's paper "How to Read Floating Point Numbers Accurately"
		// 
		//  Using BigIntegers gives us a result which is either the best approximation or the next best approximation.
		//   The rest of this algorithm should be completed to adjust the result in order to make sure its the best.
		//   Held off on finishing it as there are bigger fish to fry, the ecmaScript number tests pass with the above
		//   and perhaps that's good enough.  To finish
		//		1) BigInteger class needs to be extended to support negative numbers
		//		2) The section under findClosestFloat after the comment "Compare" needs to be fleshed out with the
		//         details from Clinger's paper to figure out if the result, nextFloat(), or previousFloat() should
		//         be returned.  Note that no loop needs to be completed because the BigInteger
		//		   calclulation gaurantees we are at worst one estimate off the true value and the loop will 
		//         only require a single iteration.
		//      3) Implement nextFloat() / previousFloat()
		/*
		// Check if both the mantissa and exponent are guaranteed to accurately fit into a double 
		//  (mantissa is <= 2^53, exponent is <= 10^23)   If so, we can get away with double math.
		if ( (exactInt->numWords == 1) || 
			 (exactInt->numWords == 2 && wordBuffer[1] < 0x00200000) )  { // i.e. its < 0x0020 0000 0000 0000 == 2^53
			
			if (exp10 >= 0 && exp10 < 23) { // log5-of-two^53 = ceil( log(pow(2,53)) / log(5) ) = ceil(22.82585758) = 23
				double f = exactInt->doubleValueOf();
				result = f * quickPowTen(exp10);
			}
			else if (exp10 < 0 && -exp10 < 23) {
				double f = exactInt->doubleValueOf();
				result = f / quickPowTen(exp10);
			}
			else { // exponent doesn't fit exactly into a double
				result = Bellerophon_MultiplyAndTest(exactInt, exp10, 0);
			}
		} else if (exactInt->numWords == 2) { // i.e. its < 0x0000 0001 0000 0000 0000 0000 == 2^64
			if ( (exp10 >= 0) && (exp10 < 23) {
					result = Bellerophon_MultiplyAndTest(exactInt, exp10, 0);
			} else { // exp10 < 0 || exp10 > 23)
					result = Bellerophon_MultiplyAndTest(exactInt, exp10, 3);
			}
		} else {
			if ( (exp10 >= 0) && (exp10 < 23) {
					result = Bellerophon_MultiplyAndTest(exactInt, exp10, 1);
			} else { // exp10 < 0 || exp10 > 23)
					result = Bellerophon_MultiplyAndTest(exactInt, exp10, 4);
			}
		}

		*value = negate ? -result : result;
		return true;
	}

	MathUtils::Bellerophon_MultiplyAndTest(BigInteger* f, int32_t exp10, int32_t slop)
	{
		double x = f->doubleValueOf();
		double y = quickPowTen(exp10);
		double estimate = x*y;
		uint64 mantissaEstimate = frexp(estimate,&e);
		int64 lowBits = (int64)(mantissaEstimate % 2048); // two^p-n = 2^(64-53) = 2^11 = 2048

		// check if slop is large enough to make a difference when rounding to 53 bits
		int64 diff = lowBits - 1024;
		if ( (diff >= 0 && diff <= slop) ||
			 (diff < 0 && -diff <= slop) )
		{
			findClosestFloat(f,exp10,estimate);
		}

		return estimate;
	}

	MathUtils::findClosestFloat(BigInteger* f, int32_t e, double estimate)
	{
		int32_t k;
		uint64 m = frexp(estimate,&k);
		BigInteger *m = BigInteger::newFromUint64(m);
		BigInteger* compX;
		BigInteger* compY;

		if (e >= 0) {
			if (k >= 0) {
				compX = f->multBy(quickPow2(e));
				compY = m->multBy(pow(beta,k));
			} else {
				compX = f->multBy(quickPow2(e))->multBy( pow(beta,-k) );
				compY = m;
			}
		} else { // e < 0
			if (k >= 0) {
				compX = f;
				compY = m->multBy(pow(beta,k))->multBy(quickPow2(-e));
			} else {
				compX = f->multBy(pow(beta,-k));
				compY = m->multBy(quickPow2(-e)) );
			}
		}
		// compare
		BigInteger* diff = compX->subtract(compY); // need to modify BigInteger to support negative values
		// rest of compare would go here
	}

	*/

	//
	// Random number generator
	//

	/*-------------------------------------------------------------------------*/
	/* Coefficients used in the pure random number generator. */
#define c3  15731L
#define c2  789221L
#define c1  1376312589L

	/* Read-only, XOR masks for random # generation. */
	static const uint32_t Random_Xor_Masks[31] =
		{
			/* First mask is for generating sequences of 3 (2^2 - 1) random numbers,
			   /  Second mask is for generating sequences of 7 (2^3 - 1) random numbers,
			   /  etc.  Numbers to the right are number of bits of random number sequence.
			   /  It generates 2^n - 1 numbers. */
			0x00000003L, 0x00000006L, 0x0000000CL, 0x00000014L,     /* 2,3,4,5 */
			0x00000030L, 0x00000060L, 0x000000B8L, 0x00000110L,     /* 6,7,8,9 */
			0x00000240L, 0x00000500L, 0x00000CA0L, 0x00001B00L,     /* 10,11,12,13 */
			0x00003500L, 0x00006000L, 0x0000B400L, 0x00012000L,     /* 14,15,16,17 */
			0x00020400L, 0x00072000L, 0x00090000L, 0x00140000L,     /* 18,19,20,21 */
			0x00300000L, 0x00400000L, 0x00D80000L, 0x01200000L,     /* 22,23,24,25 */
			0x03880000L, 0x07200000L, 0x09000000L, 0x14000000L,     /* 26,27,28,29 */
			0x32800000L, 0x48000000L, 0xA3000000L                   /* 30,31,32 */

		};                              /* Randomizer Xor mask values  CRK 10-29-90 */
	/*-------------------------------------------------------------------------*/

	//TRandomFast gRandomFast = { 0, 0, 0};  Initialized in global.cpp

	/*-*-------------------------------------------------------------------------
	  / Function
	  /   RandomFastInit
	  /
	  / Purpose
	  /   This initializes the fast random number generator.
	  /
	  / Notes
	  /   The fast random number generator has some unique qualities:
	  /
	  /   1) It generates an exact and repeatable sequence of pseudorandom
	  /      integers between 1 and 2^n-1, inclusive.  Zero is not generated.
	  /   2) The same sequence repeats every 2^n-1 generations.
	  /   3) Each number can be generated extremely rapidly.
	  /
	  /   This returns the first random number in the sequence.
	  /
	  / Entry
	  /   pRandomFast = Pointer to data structure for current state of a fast
	  /     pseudorandom number generator.
	  /   n = A value which sets the number of unique values to generate before
	  /     repeating.  This value can range from 2 to 32, inclusive.  If an
	  /     invalid value (such as zero) is passed in, 32 is assumed.
	  /--------------------------------------------*/
	void MathUtils::RandomFastInit(pTRandomFast pRandomFast)
	{
		sint32 n = 31; // Changed from 32 to 31 per Prince

		/* The sequence always starts with 1. */
		//    pRandomFast->uValue = 1L;
		pRandomFast->uValue = (uint32_t)(VMPI_getTime());

		/* Figure out the sequence length (2^n - 1). */
		pRandomFast->uSequenceLength = (1L << n) - 1L;

		/* Gather the XOR mask value. */
		pRandomFast->uXorMask = Random_Xor_Masks[n - 2];
	}
	/*-------------------------------------------------------------------------*/

	/*-*-------------------------------------------------------------------------
	  / Function
	  /   imRandomFastNext
	  /
	  / Purpose
	  /   This generates a new pseudorandom number using the fast random number
	  /   generator.
	  /
	  / Notes
	  /   The fast random number generator must be initialized before use.
	  /
	  /   This is implemented as a macro for the best possible performance.
	  /
	  / Entry
	  /   pRandomFast = Pointer to data structure for current state of a fast
	  /     pseudorandom number generator.
	  /
	  / Exit
	  /   Returns the next pseudorandom number in the sequence.
	  /--------------------------------------------*/
#define RandomFastNext(_pRandomFast)                                                            \
(                                                                                               \
    ((_pRandomFast)->uValue & 1L)                                                               \
        ? ((_pRandomFast)->uValue = ((_pRandomFast)->uValue >> 1) ^ (_pRandomFast)->uXorMask)   \
        : ((_pRandomFast)->uValue = ((_pRandomFast)->uValue >> 1))                              \
)
	/*-------------------------------------------------------------------------*/

	/*-*-------------------------------------------------------------------------
	  / Function
	  /   RandomPureHasher
	  /
	  / Purpose
	  /   This generates a pseudorandom number from a given seed using the high
	  /   quality random number generator.
	  /
	  / Notes
	  /   The caller must pass in a seed value.  This value is typically the
	  /   output of the fast random number generator multiplied by a prime
	  /   number, but can be any seed which was not derived from the output of
	  /   this function.
	  /
	  /   Please note that this random number generator is really as hasher.
	  /   It will not work well if you pass its own output in as the next input.
	  /
	  /   A given input seed always generates the same pseudorandom output result.
	  /
	  /   The feature of this hasher is that the value returned from one seed
	  /   to the next is highly uncorrelated to the seed value.  High quality
	  /   multidimensional random numbers can be generated by using a sum of
	  /   prime multiples of the seed values.
	  /
	  /   For example, to generate a vector given three seed values sx, sy and sz,
	  /   use something like the following:
	  /     result = imRandomPureHasher(59*sx + 67*sy + 71*sz);
	  /
	  / Entry
	  /   iSeed = Starting seed value.
	  /
	  / Exit
	  /   Returns the next pseudorandom value in the sequence.
	  /--------------------------------------------*/
	sint32 MathUtils::RandomPureHasher(sint32 iSeed)
	{
		sint32   iResult;

		/* Adapted from "A Recursive Implementation of the Perlin Noise Function,"
		   /  by Greg Ward, Graphics Gems II, p. 396. */

		/* First, hash s as a preventive measure.  This helps ensure the first
		   /  few numbers are more random when used in conjunction with the fast
		   /  random number generator, which starts off with the first 10 or so
		   /  numbers all zero in the lowe bits. */
		iSeed = ((iSeed << 13) ^ iSeed) - (iSeed >> 21);

		/* Next, use a third order odd polynomial, better than linear. */
		iResult = (iSeed*(iSeed*iSeed*c3 + c2) + c1) & kRandomPureMax;

		/* DJ14dec94 -- The above wonderful expression always returns odd
		   /  numbers, and this is easy to prove.  So we add the seed back to
		   /  the result which again randomizes bit zero. */
		iResult += iSeed;

		/* DJ17nov95 -- The above always returns values that are NEVER divisible
		   /  evenly by four, so do additional hashing. */
		iResult = ((iResult << 13) ^ iResult) - (iResult >> 21);

		return iResult;
	}
	/* ------------------------------------------------------------------------------ */
	sint32 MathUtils::GenerateRandomNumber(pTRandomFast pRandomFast)
	{
		/* Fill out gRandomFast if it is uninitialized.
		   /  This means seed hasn't been set.  Sequence of numbers will be
		   /  the same every time player is run. */
		if (pRandomFast->uValue == 0) {
			/* Initialize 32 bit pure random number generator. */
			RandomFastInit(pRandomFast);
		}

		long aNum = RandomFastNext(pRandomFast);

		/* Use the pure random number generator to hash the result. */
		aNum = RandomPureHasher(aNum * 71L);

		return aNum & kRandomPureMax;
	}

	sint32 MathUtils::Random(sint32 range, pTRandomFast pRandomFast)
	{
		if (range > 0) {
			return GenerateRandomNumber(pRandomFast) % range;
		} else {
			return 0;
		}
	}

	void MathUtils::initRandom(TRandomFast *seed)
	{
		RandomFastInit(seed);
	}
	
	double MathUtils::random(TRandomFast *seed)
	{
		return (double)GenerateRandomNumber(seed) / ((double)kRandomPureMax+1.0);
	}
	
	/*-------------------------------------------------------------------------*/
	/*  Begining D2A class implemention, used for converting double values to  */
	/*   strings accurately.												   */

	// This algorithm for printing floating point numbers is based on the paper
	//  "Printing floating-point numbers quickly and accurately" by Robert G Burger
	//  and R. Kent Dybvig  http://www.cs.indiana.edu/~burger/FP-Printing-PLDI96.pdf
	//  See that paper for details.
	//
	//  The algorithm generates the shortest, correctly rounded output string that 
	//   converts to the same number when read back in.  This implementation assumes
	//   IEEE unbiased rounding, that the input is a 64 bit (base 2) floating point 
	//   number composed of a sign bit, a hidden bit (valued 1) and 52 explict bits of
	//   mantissa data, and an 11 bit exponent (in base 2).  It also assumes the output
	//   desired is base 10.


	// ------------------------------------------------------
	//  Support functions

	// For results larger than 10^22, error creeps into the double estimate.  Use BigIntegers to avoid error
	static inline void quickBigPowTen(int32_t exp, BigInteger* result)
	{
		if (exp < 22 && exp > 0) {
			result->setFromDouble(kPowersOfTen[exp]);
		} else if (exp > 0) {// double starts to include roundoff error after 1e22, need to compute exactly
			result->setFromDouble(kPowersOfTen[21]);
			exp -= 21;
			while (exp-- > 0)
				result->multBy((int32)10);
		} else { // we won't get here because we only deal in positive exponents
			result->setFromDouble(MathUtils::pow(10,exp)); // but just in case
		}
	}

	// Use left shifts to compute powers of 2 < 63
	static inline double quickPowTwo(int32_t exp)
	{
		static uint64 one = 1; // max we can shift is 64bits
		if (exp < 64 && exp > 0)
			return (double)(one << exp);
		else
			return MathUtils::pow(2,exp);
	}

	// nextDigit() returns the next relevant digit in the number being converted, else -1 if 
	//  there are no more relevant digits.  
	int32_t D2A::nextDigit()
	{
		if (finished)
			return -1;

		bool withinLowEndRoundRange;
		bool withinHighEndRoundRange;
		int32_t quotient;

		if ( bFastEstimateOk )
		{
			quotient = (int32_t)(dr / ds);
			double mod = MathUtils::mod(dr,ds);
			dr = mod;
         
			// check if remaining ratio r/s is within the range of floats which would round to the value we have output
			//  so far when read in from a string.
			withinLowEndRoundRange  = (lowOk  ? (dr <= dMMinus)   : (dr < dMMinus));
			withinHighEndRoundRange = (highOk ? (dr+dMPlus >= ds) : (dr+dMPlus > ds));		
		}
		else
		{
			BigInteger bigQuotient;
			bigQuotient.setFromInteger(0);
			r.divBy(&s, &bigQuotient); // r = r %s,  bigQuotient = r / s.
			quotient = (int32)(bigQuotient.wordBuffer[0]); // todo: optimize away need for BigInteger result?  We know it should always be a single digit
   											  // r <= mMinus               :  r < rMinus
			withinLowEndRoundRange  = (lowOk  ? (r.compare(&mMinus) != 1)  : (r.compare(&mMinus) == -1));
                                              // r+mPlus >= s                     :  r+mPlus > s
			withinHighEndRoundRange = (highOk ? (r.compareOffset(&s,&mPlus) != -1) : (r.compareOffset(&s,&mPlus) == 1));
		}
		

		if (quotient < 0 || quotient > 9) 
		{
			AvmAssert(quotient >= 0);
			AvmAssert(quotient < 10);
			quotient = 0;
		}
		if (!withinLowEndRoundRange)
		{
			if (!withinHighEndRoundRange) // if not within either error range, set up to generate the next digit.
			{
				if ( bFastEstimateOk )
				{
					dr *= 10; 
					dMPlus *= 10;
					dMMinus *= 10;
				}
				else
				{
					r.multBy((int32)10); 
					mPlus.multBy((int32)10);
					mMinus.multBy((int32)10);
				}
			}
			else
			{
				quotient++;
				finished = true;
			}
		}
		else if (!withinHighEndRoundRange)
		{
			finished = true;
		}
		else 
		{
			if ( (bFastEstimateOk && (dr*2 < ds)) || 
				 (!bFastEstimateOk && (r.compareOffset(&s,&r) == -1)) ) // if (r*2 < s)  todo: faster to do lshift and compare?
			{
				finished = true;
			}
			else
			{
				quotient++;
				finished = true;
			}
		}
		return quotient;
	}


	int32_t D2A::fixup_ExponentEstimate(int32_t exponentEstimate)
	{
		int32_t correctedEstimate;
		if (bFastEstimateOk)
		{
			if (highOk ? (dr+dMPlus) >= ds : dr+dMPlus > ds)
			{
				correctedEstimate = exponentEstimate+1;
			}
			else
			{
				dr *= 10;
				dMPlus *= 10;
				dMMinus *= 10;
				correctedEstimate = exponentEstimate;
			}
		}
		else
		{
			if (highOk ? (r.compareOffset(&s,&mPlus) != -1) : (r.compareOffset(&s,&mPlus) == 1))
			{
				correctedEstimate = exponentEstimate+1;
			}
			else
			{
				r.multBy((int32)10);
				mPlus.multBy((int32)10);
				mMinus.multBy((int32)10);
				correctedEstimate = exponentEstimate;
			}
		}
		return correctedEstimate;
	}

	int32_t D2A::scale()
	{
		// estimate base10 exponent:
		int32_t base2Exponent = e + mantissaPrec-1;
		int32_t exponentEstimate = (int32_t)MathUtils::ceil( (base2Exponent * kLog2_10) - 0.0000000001);


		if (bFastEstimateOk)
		{
			double scale = quickPowTen( (exponentEstimate > 0) ? exponentEstimate : -exponentEstimate);
			
			if (exponentEstimate >= 0)
			{
				ds *= scale; 
				return fixup_ExponentEstimate(exponentEstimate);
			}
			else
			{
				dr *= scale;
				dMPlus *= scale;
				dMMinus *= scale;
				return fixup_ExponentEstimate(exponentEstimate);
			}
		}
		else
		{
			BigInteger scale;
			scale.setFromInteger(0);
			quickBigPowTen( (exponentEstimate > 0) ? exponentEstimate : -exponentEstimate, &scale);

			if (exponentEstimate >= 0)
			{
				s.multBy(&scale);
				return fixup_ExponentEstimate(exponentEstimate);
			}
			else
			{
				r.multBy(&scale);			
				mPlus.multBy(&scale); 
				mMinus.multBy(&scale); 

				return fixup_ExponentEstimate(exponentEstimate);
			}
		}
	}

	D2A::~D2A()
	{
	}


	D2A::D2A(double avalue, int32_t mode, int32_t minDigits)
		: value(avalue), finished(false), bFastEstimateOk(false), minPrecision(minDigits)
	{
		// break double down into integer mantissa (max size unsigned 53 bits) and integer base 2
		//  expondent (max size 11 signed bits).
		mantissa = MathUtils::frexp(value,&e); // value = mantissa*2^e, mantissa and e are integers.

		if (mode != MathUtils::DTOSTR_NORMAL)
		{
			lowOk = highOk = true;
		}
		else
		{
			bool round = !(mantissa & 0x1); // if mantissa is even, need to round.
			lowOk = highOk = round; // IEEE standard unbiased rounding.
		}

		// calculate #of bits of precision needed to encode this mantissa (max is 53 bits)
		long base2Precision = 53;
		mantissaPrec = base2Precision; // double has 53 bits of precision in the mantissa, but first bit is assumed
		while ( mantissaPrec != 0 && ((mantissa >> --mantissaPrec & 1) == 0) )
			; // skip leading zeros
		mantissaPrec++; 
	
		int32_t absE = (e > 0 ? e : -e);
		if ((absE + mantissaPrec-1) < 50) // we get error prone when there is more than 15 base 10 digits of precision.  (15 / kLog2_10) == 49.828921423310435218054791442341)
			bFastEstimateOk = true;

		// Represent this double as a ratio of two integers.  Use infinitely precise integers if bFastEstimate is false.
		//  mPlus and mMinus represent the range of doubles around this value which would
		//  round to this same value when converted from string back to number via atod().  
		if (bFastEstimateOk)
		{
			if (e >= 0)
			{
				if (mantissa != 0x10000000000000LL) // == 4503599627370496 == pow(2, base2Precision-1)) == 2^52 (i.e. just under becoming +1 to e and rolling over to 0)
				{
					double be = quickPowTwo(e); // 2^e

					dr = (double)mantissa*be*2;
					ds = 2;
					dMPlus = be;
					dMMinus = be;
				}
				else
				{
					double be = quickPowTwo(e);; // 2^e
					double be1 = be*2; // 2^(e+1)

					dr = (double)mantissa*be1*2;
					ds = 4; // 2*2;
					dMPlus  = be1;
					dMMinus = be;
				}
			}
			else if ( mantissa != MathUtils::pow(2, base2Precision-1) )
			{
				dr = (double)mantissa*2.0;
				ds = quickPowTwo(1-e); // pow(2,-e)*2; 
				dMPlus  = 1;
				dMMinus = 1;
			}
			else
			{
				dr = (double)mantissa*4.0;
				ds = quickPowTwo(2-e); // pow(2, 1-e)*2;
				dMPlus  = 2;
				dMMinus = 1;
			}
			
			// adjust stopping conditions if a particular number of digits are requested
			if (mode != MathUtils::DTOSTR_NORMAL)
			{
				double fixedPrecisionPowTen = quickPowTen( minPrecision );
				ds *= fixedPrecisionPowTen;
				dr *= fixedPrecisionPowTen;
			}
		}
		else
		{
			if (e >= 0)
			{
				if (mantissa != 0x10000000000000LL) // == 4503599627370496 == pow(2, base2Precision-1)) == 2^53 (i.e. just under becoming +1 to e and rolling over to 0)
				{
					BigInteger be;
					be.setFromInteger(1);
					be.lshiftBy(e); // == pow(2,e);
		
					r.setFromDouble(value); 
					r.lshiftBy(1); // r = mantissa*be*2
		
					s.setFromInteger(2);

					mPlus.setFromBigInteger(&be,0,be.numWords);  // == be;
					mMinus.setFromBigInteger(&be,0,be.numWords); // == be;
				}
				else
				{
					BigInteger be;
					be.setFromInteger(1);
					be.lshiftBy(e); // be = pow(2,e);

					BigInteger be1;
					be1.setFromInteger(0);
					be.lshift(1,&be1); // be1 == be*2;

					r.setFromDouble(value*4.0); // r == mantissa*be1*2;
					s.setFromInteger(4); // 2*2
					mPlus.setFromBigInteger(&be1,0,be1.numWords); // == be1;
					mMinus.setFromBigInteger(&be,0,be.numWords); // == be;
				}
			}
			else if ( mantissa != MathUtils::pow(2, base2Precision-1) )
			{
				r.setFromDouble( (double)(mantissa*2) );
				s.setFromInteger(2);
				s.lshiftBy(-e); // s = pow(2,-e)*2;
				mPlus.setFromInteger(1);
				mMinus.setFromInteger(1);
			}
			else
			{
				r.setFromDouble( (double)(mantissa*4) );
				s.setFromInteger(2);
				s.lshiftBy(1-e);  // s == pow(2, 1-e)*2;
				mPlus.setFromInteger(2); 
				mMinus.setFromInteger(1);
			}

			// adjust stopping conditions if a particular number of digits are requested
			//  Note: this is a cheap approximation of the correct adjustment.  It will likely
			//   lead to occasional off by one errors in the final digit generated for toPrecision() when
			//   a truncation might be required.  This mode is actually less accurate than normal mode anyway.  
			//   Only normal mode is gauranteed to generate a string which will result in the same value when converted back
			//   from string (base 10) to double (base 2).  Extra digits generated by toPrecision will often be junk
			//   (but will display a value more similar to what you would see in a code debugger, where 0.012 can
			//    appear as 0.012999999999999999999 or such apparent nonsense)
			if (mode != MathUtils::DTOSTR_NORMAL)
			{
				BigInteger bFixedPrecisionPowTen;
				bFixedPrecisionPowTen.setFromInteger(0);
				quickBigPowTen( minPrecision, &bFixedPrecisionPowTen );
				s.multBy(&bFixedPrecisionPowTen);
				r.multBy(&bFixedPrecisionPowTen);
			}
		}
		base10Exp = scale();
	}


	/*
	A2D::A2D(String source,int32_t radix)
	{
		bitsPerChar = 0;
		while ( (radix >>= 1) != 1 )
			bitsPerChar++;

		source = source;
		radix = radix;
		next = 0;
		end = string.length();
		finished = false;

		// skip leading 0's
		while( nextDigit() == 0);
		next--;
	}

	inline int32_t A2D::parseIntDigit(wchar ch)
	{
		if (ch >= '0' && ch <= '9') {
			return (ch - '0');
		} else if (ch >= 'a' && ch <= 'z') {
			return (ch - 'a' + 10);
		} else if (ch >= 'A' && ch <= 'Z') {
			return (ch - 'A' + 10);
		} else {
			return -1;
		}
	}
	int32_t A2D::nextDigit()
	{
		if (finished)
			return -1;

		wc = source[next++];
		int32_t result = parseIntDigit(wc);
		if (next == end || result == -1)
			finished = true;
		return result;
	}
   */
}
