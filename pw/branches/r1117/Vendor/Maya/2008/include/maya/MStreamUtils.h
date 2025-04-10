#ifndef _MStreamUtils
#define _MStreamUtils
//
//-
// ==========================================================================
// Copyright (C) 1995 - 2005 Alias Systems Corp. and/or its licensors.  All 
// rights reserved.
// 
// The coded instructions, statements, computer programs, and/or related 
// material (collectively the "Data") in these files contain unpublished 
// information proprietary to Alias Systems Corp. ("Alias") and/or its 
// licensors, which is protected by Canadian and US federal copyright law and 
// by international treaties.
// 
// The Data may not be disclosed or distributed to third parties or be copied 
// or duplicated, in whole or in part, without the prior written consent of 
// Alias.
// 
// THE DATA IS PROVIDED "AS IS". ALIAS HEREBY DISCLAIMS ALL WARRANTIES RELATING 
// TO THE DATA, INCLUDING, WITHOUT LIMITATION, ANY AND ALL EXPRESS OR IMPLIED 
// WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY AND/OR FITNESS FOR A 
// PARTICULAR PURPOSE. IN NO EVENT SHALL ALIAS BE LIABLE FOR ANY DAMAGES 
// WHATSOEVER, WHETHER DIRECT, INDIRECT, SPECIAL, OR PUNITIVE, WHETHER IN AN 
// ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, OR IN EQUITY, 
// ARISING OUT OF ACCESS TO, USE OF, OR RELIANCE UPON THE DATA.
// ==========================================================================
//+
//
// CLASS:    MStreamUtils
//
// *****************************************************************************
// *****************************************************************************
//
// CLASS DESCRIPTION (MStreamUtils)
//
//  This class provides some standard stream functionality for developers
//	working in C++ or script.
//	
// *****************************************************************************

#if defined __cplusplus

// *****************************************************************************

// INCLUDED HEADER FILES
#include <maya/MIOStreamFwd.h>

// *****************************************************************************

// DECLARATIONS

class MStatus;

// *****************************************************************************

// CLASS DECLARATION (MStreamUtils)

/// Stream functionality. (OpenMaya) (OpenMaya.py) 
/**
 	Methods for getting streams and writing to them.
*/
#ifdef _WIN32
#pragma warning(disable: 4522)
#endif // _WIN32

class OPENMAYA_EXPORT MStreamUtils
{
public:

	///
	static std::ostream& stdErrorStream();
	///
	static std::ostream& stdOutStream(); 
	
	///
	static MStatus writeChar( std::ostream& out, const char value, bool binary = false );
	///
	static MStatus writeCharBuffer( std::ostream& out, const char* value, bool binary = false );
	///
	static MStatus writeInt( std::ostream& out, const int value, bool binary = false );
	///
	static MStatus writeFloat( std::ostream& out, const float value, bool binary = false );
	///
	static MStatus writeDouble( std::ostream& out, const double value, bool binary = false );	

	///
	static MStatus readChar( std::istream& in, char& value, bool binary = false );
	///
	static MStatus readCharBuffer( std::istream& in, char*& value, unsigned int length, bool binary = false );
	///
	static MStatus readInt( std::istream& in, int& value, bool binary = false );
	///
	static MStatus readFloat( std::istream& in, float& value, bool binary = false );
	///
	static MStatus readDouble( std::istream& in, double& value, bool binary = false );	
	
protected:
// No protected members 	
private:
// No protected members 
}; 

#endif  // __cplusplus
#endif // _MStreamUtils
