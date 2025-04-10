
#ifndef _MFnNObjectData
#define _MFnNObjectData
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
// CLASS:    MFnNObjectData
//
// *****************************************************************************
//
// CLASS DESCRIPTION (MFnNObjectData)
// 
// This class is the function set for nucleus geometry data.
//
// *****************************************************************************

#if defined __cplusplus

// *****************************************************************************

// INCLUDED HEADER FILES


#include <maya/MFnData.h>

// *****************************************************************************

// DECLARATIONS

class MPoint;
class MnCloth;


// *****************************************************************************

// CLASS DECLARATION (MFnNObjectData)

/// (OpenMayaFX) (OpenMayaFX.py)
/**
	Class for transferring N object data between connections
*/

#ifdef _WIN32
#pragma warning(disable: 4522)
#endif // _WIN32
class OPENMAYAFX_EXPORT MFnNObjectData : public MFnData 
{

    declareMFn( MFnNObjectData, MFnData );

public:


    ///
    MObject         create() const ;    
    ///
	MStatus			getObjectPtr( MnCloth *& ptr ) const;
	///
	MStatus			setObjectPtr( MnCloth * ptr );    
    ///
    MStatus			getCollide( bool & ) const;	
    ///
    MStatus         getCached( bool & cached) const;
    ///
    MStatus         setCached( bool cached);
    

BEGIN_NO_SCRIPT_SUPPORT:

 	declareMFnConstConstructor( MFnNObjectData, MFnData );
	
END_NO_SCRIPT_SUPPORT:

protected:
// No protected members

private:
// No Private members
 
};

#ifdef _WIN32
#pragma warning(default: 4522)
#endif // _WIN32

// *****************************************************************************
#endif /* __cplusplus */
#endif /* _MFnNObjectData */
