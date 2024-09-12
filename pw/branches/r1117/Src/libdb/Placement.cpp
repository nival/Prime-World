#include "stdafx.h"
#include "XmlSaver.h"
#include "Placement.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CPlacement::CPlacement()
{
	Identity( &matrix );
  rotation2 = VNULL3;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CPlacement::CPlacement( const CVec3& location, const CQuat& rotation, const CVec3& scale )
{
	place.pos = location;
	place.rot = rotation;
	place.scale = scale;
	ComposeMatrix( matrix, location, rotation, scale );
  rotation2 = VNULL3;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CPlacement::operator&( IXmlSaver &f )
{
	if ( f.IsReading() )
	{
		CVec3 location( VNULL3 );
		CQuat rotation( QNULL );
    CVec3 scale( 1, 1, 1 );
    f.Add( "translateX", &location.x );
    f.Add( "translateY", &location.y );
    f.Add( "translateZ", &location.z );
    f.Add( "location", &location );
		
    f.Add( "rotationX", &rotation2.x );
    f.Add( "rotationY", &rotation2.y );
    f.Add( "rotationZ", &rotation2.z );
    rotation.FromEulerAngles( ToRadian(rotation2.z), ToRadian(rotation2.y), ToRadian(rotation2.x) );
    f.Add( "rotation", &rotation );

    f.Add( "scaleX", &scale.x );
    f.Add( "scaleY", &scale.y );
    f.Add( "scaleZ", &scale.z );
    f.Add( "scale", &scale );

		place.pos = location;
		place.rot = rotation;
		place.scale = scale;

		ComposeMatrix( matrix, location, rotation, scale );

		return 0;
	}
	else
	{
		return -1;
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
