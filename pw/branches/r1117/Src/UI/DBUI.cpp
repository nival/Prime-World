// Automatically generated file, don't change it manually!
#include "stdafx.h"
#include "../libdb/Checksum.h"
#include "../libdb/XmlSaver.h"
#include "../Scripts/lua.hpp"
#include "../Scripts/ScriptMacroses.h"
#include "System/StrUtils.h"

#include "../Render/DBRender.h"
#include "../Render/DBRenderResources.h"
#include "../UI/DBPreferences.h"
#include "../UI/DBVotingForSurrender.h"
#include "DBUI.h"
namespace
{
	char enumToStrBuffer[12];
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
REGISTER_DBRESOURCE( UICursorBase );
REGISTER_DBRESOURCE( UILayout );
REGISTER_DBRESOURCE( UIImageLabelLayout );
REGISTER_DBRESOURCE( UICommonControl );
REGISTER_DBRESOURCE( UIButtonLayout );
REGISTER_DBRESOURCE( UIContentResource );
REGISTER_DBRESOURCE( UICursor );
REGISTER_DBRESOURCE( UIAnimatedCursor );
REGISTER_DBRESOURCE( UIEditBoxLayout );
REGISTER_DBRESOURCE( UIFlashLayout );
REGISTER_DBRESOURCE( UIFlashLayout2 );
REGISTER_DBRESOURCE( UIFontStyle );
REGISTER_DBRESOURCE( UIHealthBarLayout );
REGISTER_DBRESOURCE( UICheckBoxLayout );
REGISTER_DBRESOURCE( UIBaseLayout );
REGISTER_DBRESOURCE( UIObjectOvertips );
REGISTER_DBRESOURCE( UIPageTabControlLayout );
REGISTER_DBRESOURCE( UIProgressBarLayout );
REGISTER_DBRESOURCE( UIRadioButtonLayout );
REGISTER_DBRESOURCE( UIRadioPanelLayout );
REGISTER_DBRESOURCE( UIRoot );
REGISTER_DBRESOURCE( UIScrollableWindowLayout );
REGISTER_DBRESOURCE( UIScrollAreaLayout );
REGISTER_DBRESOURCE( UIScrollBarLayout );
REGISTER_DBRESOURCE( UIScrollListLayout );
REGISTER_DBRESOURCE( UITexture );
REGISTER_DBRESOURCE( UIViewLayout );
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// includes for factories
#ifndef VISUAL_CUTTED
#include "../Render/TextureManager.h"
#endif // #ifndef VISUAL_CUTTED

namespace NDb
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EImageLabelShapeType value )
{
	switch( value )
	{
		case IMAGELABELSHAPETYPE_EMPTY:
			return "Empty";
		case IMAGELABELSHAPETYPE_SIMPLEBOX:
			return "SimpleBox";
		case IMAGELABELSHAPETYPE_FROMSHAPESTYLE:
			return "FromShapeStyle";
		case IMAGELABELSHAPETYPE_FROMBACKGROUNDSTYLE:
			return "FromBackgroundStyle";
		case IMAGELABELSHAPETYPE_FROMSHAPEORBACKGROUNDSTYLE:
			return "FromShapeOrBackgroundStyle";
		case IMAGELABELSHAPETYPE_BYTEXT:
			return "ByText";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EImageLabelShapeType", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EImageLabelShapeType StringToEnum_EImageLabelShapeType( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EImageLabelShapeType)(NStr::ToInt( value ));
	if ( strcmp( value, "Empty" ) == 0 || strcmp( value, "IMAGELABELSHAPETYPE_EMPTY" ) == 0 )
		return IMAGELABELSHAPETYPE_EMPTY;
	if ( strcmp( value, "SimpleBox" ) == 0 || strcmp( value, "IMAGELABELSHAPETYPE_SIMPLEBOX" ) == 0 )
		return IMAGELABELSHAPETYPE_SIMPLEBOX;
	if ( strcmp( value, "FromShapeStyle" ) == 0 || strcmp( value, "IMAGELABELSHAPETYPE_FROMSHAPESTYLE" ) == 0 )
		return IMAGELABELSHAPETYPE_FROMSHAPESTYLE;
	if ( strcmp( value, "FromBackgroundStyle" ) == 0 || strcmp( value, "IMAGELABELSHAPETYPE_FROMBACKGROUNDSTYLE" ) == 0 )
		return IMAGELABELSHAPETYPE_FROMBACKGROUNDSTYLE;
	if ( strcmp( value, "FromShapeOrBackgroundStyle" ) == 0 || strcmp( value, "IMAGELABELSHAPETYPE_FROMSHAPEORBACKGROUNDSTYLE" ) == 0 )
		return IMAGELABELSHAPETYPE_FROMSHAPEORBACKGROUNDSTYLE;
	if ( strcmp( value, "ByText" ) == 0 || strcmp( value, "IMAGELABELSHAPETYPE_BYTEXT" ) == 0 )
		return IMAGELABELSHAPETYPE_BYTEXT;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EImageLabelShapeType", value ) );
	return IMAGELABELSHAPETYPE_EMPTY;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EUI3DOvertipMode value )
{
	switch( value )
	{
		case UI3DOVERTIPMODE_WORLD:
			return "World";
		case UI3DOVERTIPMODE_BILLBOARD:
			return "Billboard";
		case UI3DOVERTIPMODE_AXISBILLBOARD:
			return "AxisBillboard";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EUI3DOvertipMode", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EUI3DOvertipMode StringToEnum_EUI3DOvertipMode( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EUI3DOvertipMode)(NStr::ToInt( value ));
	if ( strcmp( value, "World" ) == 0 || strcmp( value, "UI3DOVERTIPMODE_WORLD" ) == 0 )
		return UI3DOVERTIPMODE_WORLD;
	if ( strcmp( value, "Billboard" ) == 0 || strcmp( value, "UI3DOVERTIPMODE_BILLBOARD" ) == 0 )
		return UI3DOVERTIPMODE_BILLBOARD;
	if ( strcmp( value, "AxisBillboard" ) == 0 || strcmp( value, "UI3DOVERTIPMODE_AXISBILLBOARD" ) == 0 )
		return UI3DOVERTIPMODE_AXISBILLBOARD;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EUI3DOvertipMode", value ) );
	return UI3DOVERTIPMODE_WORLD;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EUIButtonViewMode value )
{
	switch( value )
	{
		case UIBUTTONVIEWMODE_BYMATERIALS:
			return "ByMaterials";
		case UIBUTTONVIEWMODE_BYPINS:
			return "ByPins";
		case UIBUTTONVIEWMODE_BYPINSWITHOUTDISABLEPIN:
			return "ByPinsWithoutDisablePin";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EUIButtonViewMode", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EUIButtonViewMode StringToEnum_EUIButtonViewMode( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EUIButtonViewMode)(NStr::ToInt( value ));
	if ( strcmp( value, "ByMaterials" ) == 0 || strcmp( value, "UIBUTTONVIEWMODE_BYMATERIALS" ) == 0 )
		return UIBUTTONVIEWMODE_BYMATERIALS;
	if ( strcmp( value, "ByPins" ) == 0 || strcmp( value, "UIBUTTONVIEWMODE_BYPINS" ) == 0 )
		return UIBUTTONVIEWMODE_BYPINS;
	if ( strcmp( value, "ByPinsWithoutDisablePin" ) == 0 || strcmp( value, "UIBUTTONVIEWMODE_BYPINSWITHOUTDISABLEPIN" ) == 0 )
		return UIBUTTONVIEWMODE_BYPINSWITHOUTDISABLEPIN;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EUIButtonViewMode", value ) );
	return UIBUTTONVIEWMODE_BYMATERIALS;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EUIControlMouseActions value )
{
	switch( value )
	{
		case UICONTROLMOUSEACTIONS_LEFT:
			return "Left";
		case UICONTROLMOUSEACTIONS_RIGHT:
			return "Right";
		case UICONTROLMOUSEACTIONS_BOTH:
			return "Both";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EUIControlMouseActions", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EUIControlMouseActions StringToEnum_EUIControlMouseActions( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EUIControlMouseActions)(NStr::ToInt( value ));
	if ( strcmp( value, "Left" ) == 0 || strcmp( value, "UICONTROLMOUSEACTIONS_LEFT" ) == 0 )
		return UICONTROLMOUSEACTIONS_LEFT;
	if ( strcmp( value, "Right" ) == 0 || strcmp( value, "UICONTROLMOUSEACTIONS_RIGHT" ) == 0 )
		return UICONTROLMOUSEACTIONS_RIGHT;
	if ( strcmp( value, "Both" ) == 0 || strcmp( value, "UICONTROLMOUSEACTIONS_BOTH" ) == 0 )
		return UICONTROLMOUSEACTIONS_BOTH;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EUIControlMouseActions", value ) );
	return UICONTROLMOUSEACTIONS_LEFT;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EUIDiscreteType value )
{
	switch( value )
	{
		case UIDISCRETETYPE_NONE:
			return "None";
		case UIDISCRETETYPE_FIXED:
			return "Fixed";
		case UIDISCRETETYPE_RELATIVETOITEMSCOUNT:
			return "RelativeToItemsCount";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EUIDiscreteType", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EUIDiscreteType StringToEnum_EUIDiscreteType( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EUIDiscreteType)(NStr::ToInt( value ));
	if ( strcmp( value, "None" ) == 0 || strcmp( value, "UIDISCRETETYPE_NONE" ) == 0 )
		return UIDISCRETETYPE_NONE;
	if ( strcmp( value, "Fixed" ) == 0 || strcmp( value, "UIDISCRETETYPE_FIXED" ) == 0 )
		return UIDISCRETETYPE_FIXED;
	if ( strcmp( value, "RelativeToItemsCount" ) == 0 || strcmp( value, "UIDISCRETETYPE_RELATIVETOITEMSCOUNT" ) == 0 )
		return UIDISCRETETYPE_RELATIVETOITEMSCOUNT;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EUIDiscreteType", value ) );
	return UIDISCRETETYPE_NONE;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EUIElementAspectRatio value )
{
	switch( value )
	{
		case UIELEMENTASPECTRATIO_DONTCARE:
			return "DontCare";
		case UIELEMENTASPECTRATIO_WIDTHBASED:
			return "WidthBased";
		case UIELEMENTASPECTRATIO_HEIGHTBASED:
			return "HeightBased";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EUIElementAspectRatio", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EUIElementAspectRatio StringToEnum_EUIElementAspectRatio( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EUIElementAspectRatio)(NStr::ToInt( value ));
	if ( strcmp( value, "DontCare" ) == 0 || strcmp( value, "UIELEMENTASPECTRATIO_DONTCARE" ) == 0 )
		return UIELEMENTASPECTRATIO_DONTCARE;
	if ( strcmp( value, "WidthBased" ) == 0 || strcmp( value, "UIELEMENTASPECTRATIO_WIDTHBASED" ) == 0 )
		return UIELEMENTASPECTRATIO_WIDTHBASED;
	if ( strcmp( value, "HeightBased" ) == 0 || strcmp( value, "UIELEMENTASPECTRATIO_HEIGHTBASED" ) == 0 )
		return UIELEMENTASPECTRATIO_HEIGHTBASED;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EUIElementAspectRatio", value ) );
	return UIELEMENTASPECTRATIO_DONTCARE;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EUIElementHAlign value )
{
	switch( value )
	{
		case UIELEMENTHALIGN_LEFT:
			return "Left";
		case UIELEMENTHALIGN_RIGHT:
			return "Right";
		case UIELEMENTHALIGN_CENTER:
			return "Center";
		case UIELEMENTHALIGN_FIXEDMARGINS:
			return "FixedMargins";
		case UIELEMENTHALIGN_PROPORTIONAL:
			return "Proportional";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EUIElementHAlign", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EUIElementHAlign StringToEnum_EUIElementHAlign( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EUIElementHAlign)(NStr::ToInt( value ));
	if ( strcmp( value, "Left" ) == 0 || strcmp( value, "UIELEMENTHALIGN_LEFT" ) == 0 )
		return UIELEMENTHALIGN_LEFT;
	if ( strcmp( value, "Right" ) == 0 || strcmp( value, "UIELEMENTHALIGN_RIGHT" ) == 0 )
		return UIELEMENTHALIGN_RIGHT;
	if ( strcmp( value, "Center" ) == 0 || strcmp( value, "UIELEMENTHALIGN_CENTER" ) == 0 )
		return UIELEMENTHALIGN_CENTER;
	if ( strcmp( value, "FixedMargins" ) == 0 || strcmp( value, "UIELEMENTHALIGN_FIXEDMARGINS" ) == 0 )
		return UIELEMENTHALIGN_FIXEDMARGINS;
	if ( strcmp( value, "Proportional" ) == 0 || strcmp( value, "UIELEMENTHALIGN_PROPORTIONAL" ) == 0 )
		return UIELEMENTHALIGN_PROPORTIONAL;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EUIElementHAlign", value ) );
	return UIELEMENTHALIGN_LEFT;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EUIElementVAlign value )
{
	switch( value )
	{
		case UIELEMENTVALIGN_TOP:
			return "Top";
		case UIELEMENTVALIGN_BOTTOM:
			return "Bottom";
		case UIELEMENTVALIGN_CENTER:
			return "Center";
		case UIELEMENTVALIGN_FIXEDMARGINS:
			return "FixedMargins";
		case UIELEMENTVALIGN_PROPORTIONAL:
			return "Proportional";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EUIElementVAlign", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EUIElementVAlign StringToEnum_EUIElementVAlign( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EUIElementVAlign)(NStr::ToInt( value ));
	if ( strcmp( value, "Top" ) == 0 || strcmp( value, "UIELEMENTVALIGN_TOP" ) == 0 )
		return UIELEMENTVALIGN_TOP;
	if ( strcmp( value, "Bottom" ) == 0 || strcmp( value, "UIELEMENTVALIGN_BOTTOM" ) == 0 )
		return UIELEMENTVALIGN_BOTTOM;
	if ( strcmp( value, "Center" ) == 0 || strcmp( value, "UIELEMENTVALIGN_CENTER" ) == 0 )
		return UIELEMENTVALIGN_CENTER;
	if ( strcmp( value, "FixedMargins" ) == 0 || strcmp( value, "UIELEMENTVALIGN_FIXEDMARGINS" ) == 0 )
		return UIELEMENTVALIGN_FIXEDMARGINS;
	if ( strcmp( value, "Proportional" ) == 0 || strcmp( value, "UIELEMENTVALIGN_PROPORTIONAL" ) == 0 )
		return UIELEMENTVALIGN_PROPORTIONAL;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EUIElementVAlign", value ) );
	return UIELEMENTVALIGN_TOP;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EUIListItemsPlacingOrder value )
{
	switch( value )
	{
		case UILISTITEMSPLACINGORDER_BYROWS:
			return "ByRows";
		case UILISTITEMSPLACINGORDER_BYCOLUMNS:
			return "ByColumns";
		case UILISTITEMSPLACINGORDER_BYROWSOFCOLUMNS:
			return "ByRowsOfColumns";
		case UILISTITEMSPLACINGORDER_BYCOLUMNSOFROWS:
			return "ByColumnsOfRows";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EUIListItemsPlacingOrder", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EUIListItemsPlacingOrder StringToEnum_EUIListItemsPlacingOrder( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EUIListItemsPlacingOrder)(NStr::ToInt( value ));
	if ( strcmp( value, "ByRows" ) == 0 || strcmp( value, "UILISTITEMSPLACINGORDER_BYROWS" ) == 0 )
		return UILISTITEMSPLACINGORDER_BYROWS;
	if ( strcmp( value, "ByColumns" ) == 0 || strcmp( value, "UILISTITEMSPLACINGORDER_BYCOLUMNS" ) == 0 )
		return UILISTITEMSPLACINGORDER_BYCOLUMNS;
	if ( strcmp( value, "ByRowsOfColumns" ) == 0 || strcmp( value, "UILISTITEMSPLACINGORDER_BYROWSOFCOLUMNS" ) == 0 )
		return UILISTITEMSPLACINGORDER_BYROWSOFCOLUMNS;
	if ( strcmp( value, "ByColumnsOfRows" ) == 0 || strcmp( value, "UILISTITEMSPLACINGORDER_BYCOLUMNSOFROWS" ) == 0 )
		return UILISTITEMSPLACINGORDER_BYCOLUMNSOFROWS;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EUIListItemsPlacingOrder", value ) );
	return UILISTITEMSPLACINGORDER_BYROWS;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EUIListItemsPlacingOrigin value )
{
	switch( value )
	{
		case UILISTITEMSPLACINGORIGIN_LEFTTOP:
			return "LeftTop";
		case UILISTITEMSPLACINGORIGIN_RIGHTTOP:
			return "RightTop";
		case UILISTITEMSPLACINGORIGIN_LEFTBOTTOM:
			return "LeftBottom";
		case UILISTITEMSPLACINGORIGIN_RIGHTBOTTOM:
			return "RightBottom";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EUIListItemsPlacingOrigin", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EUIListItemsPlacingOrigin StringToEnum_EUIListItemsPlacingOrigin( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EUIListItemsPlacingOrigin)(NStr::ToInt( value ));
	if ( strcmp( value, "LeftTop" ) == 0 || strcmp( value, "UILISTITEMSPLACINGORIGIN_LEFTTOP" ) == 0 )
		return UILISTITEMSPLACINGORIGIN_LEFTTOP;
	if ( strcmp( value, "RightTop" ) == 0 || strcmp( value, "UILISTITEMSPLACINGORIGIN_RIGHTTOP" ) == 0 )
		return UILISTITEMSPLACINGORIGIN_RIGHTTOP;
	if ( strcmp( value, "LeftBottom" ) == 0 || strcmp( value, "UILISTITEMSPLACINGORIGIN_LEFTBOTTOM" ) == 0 )
		return UILISTITEMSPLACINGORIGIN_LEFTBOTTOM;
	if ( strcmp( value, "RightBottom" ) == 0 || strcmp( value, "UILISTITEMSPLACINGORIGIN_RIGHTBOTTOM" ) == 0 )
		return UILISTITEMSPLACINGORIGIN_RIGHTBOTTOM;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EUIListItemsPlacingOrigin", value ) );
	return UILISTITEMSPLACINGORIGIN_LEFTTOP;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EUIOvertipBindPoint value )
{
	switch( value )
	{
		case UIOVERTIPBINDPOINT_NONE:
			return "None";
		case UIOVERTIPBINDPOINT_CENTER:
			return "Center";
		case UIOVERTIPBINDPOINT_LEFTTOP:
			return "LeftTop";
		case UIOVERTIPBINDPOINT_CENTERTOP:
			return "CenterTop";
		case UIOVERTIPBINDPOINT_RIGHTTOP:
			return "RightTop";
		case UIOVERTIPBINDPOINT_LEFTCENTER:
			return "LeftCenter";
		case UIOVERTIPBINDPOINT_RIGHTCENTER:
			return "RightCenter";
		case UIOVERTIPBINDPOINT_LEFTBOTTOM:
			return "LeftBottom";
		case UIOVERTIPBINDPOINT_CENTERBOTTOM:
			return "CenterBottom";
		case UIOVERTIPBINDPOINT_RIGHTBOTTOM:
			return "RightBottom";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EUIOvertipBindPoint", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EUIOvertipBindPoint StringToEnum_EUIOvertipBindPoint( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EUIOvertipBindPoint)(NStr::ToInt( value ));
	if ( strcmp( value, "None" ) == 0 || strcmp( value, "UIOVERTIPBINDPOINT_NONE" ) == 0 )
		return UIOVERTIPBINDPOINT_NONE;
	if ( strcmp( value, "Center" ) == 0 || strcmp( value, "UIOVERTIPBINDPOINT_CENTER" ) == 0 )
		return UIOVERTIPBINDPOINT_CENTER;
	if ( strcmp( value, "LeftTop" ) == 0 || strcmp( value, "UIOVERTIPBINDPOINT_LEFTTOP" ) == 0 )
		return UIOVERTIPBINDPOINT_LEFTTOP;
	if ( strcmp( value, "CenterTop" ) == 0 || strcmp( value, "UIOVERTIPBINDPOINT_CENTERTOP" ) == 0 )
		return UIOVERTIPBINDPOINT_CENTERTOP;
	if ( strcmp( value, "RightTop" ) == 0 || strcmp( value, "UIOVERTIPBINDPOINT_RIGHTTOP" ) == 0 )
		return UIOVERTIPBINDPOINT_RIGHTTOP;
	if ( strcmp( value, "LeftCenter" ) == 0 || strcmp( value, "UIOVERTIPBINDPOINT_LEFTCENTER" ) == 0 )
		return UIOVERTIPBINDPOINT_LEFTCENTER;
	if ( strcmp( value, "RightCenter" ) == 0 || strcmp( value, "UIOVERTIPBINDPOINT_RIGHTCENTER" ) == 0 )
		return UIOVERTIPBINDPOINT_RIGHTCENTER;
	if ( strcmp( value, "LeftBottom" ) == 0 || strcmp( value, "UIOVERTIPBINDPOINT_LEFTBOTTOM" ) == 0 )
		return UIOVERTIPBINDPOINT_LEFTBOTTOM;
	if ( strcmp( value, "CenterBottom" ) == 0 || strcmp( value, "UIOVERTIPBINDPOINT_CENTERBOTTOM" ) == 0 )
		return UIOVERTIPBINDPOINT_CENTERBOTTOM;
	if ( strcmp( value, "RightBottom" ) == 0 || strcmp( value, "UIOVERTIPBINDPOINT_RIGHTBOTTOM" ) == 0 )
		return UIOVERTIPBINDPOINT_RIGHTBOTTOM;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EUIOvertipBindPoint", value ) );
	return UIOVERTIPBINDPOINT_NONE;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EUIProgressBarType value )
{
	switch( value )
	{
		case UIPROGRESSBARTYPE_HORIZONTALSCALINGBAR:
			return "HorizontalScalingBar";
		case UIPROGRESSBARTYPE_TEXTUREMASKEDPROGRESS:
			return "TextureMaskedProgress";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EUIProgressBarType", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EUIProgressBarType StringToEnum_EUIProgressBarType( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EUIProgressBarType)(NStr::ToInt( value ));
	if ( strcmp( value, "HorizontalScalingBar" ) == 0 || strcmp( value, "UIPROGRESSBARTYPE_HORIZONTALSCALINGBAR" ) == 0 )
		return UIPROGRESSBARTYPE_HORIZONTALSCALINGBAR;
	if ( strcmp( value, "TextureMaskedProgress" ) == 0 || strcmp( value, "UIPROGRESSBARTYPE_TEXTUREMASKEDPROGRESS" ) == 0 )
		return UIPROGRESSBARTYPE_TEXTUREMASKEDPROGRESS;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EUIProgressBarType", value ) );
	return UIPROGRESSBARTYPE_HORIZONTALSCALINGBAR;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EUIRotationType value )
{
	switch( value )
	{
		case UIROTATIONTYPE_CW:
			return "CW";
		case UIROTATIONTYPE_CCW:
			return "CCW";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EUIRotationType", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EUIRotationType StringToEnum_EUIRotationType( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EUIRotationType)(NStr::ToInt( value ));
	if ( strcmp( value, "CW" ) == 0 || strcmp( value, "UIROTATIONTYPE_CW" ) == 0 )
		return UIROTATIONTYPE_CW;
	if ( strcmp( value, "CCW" ) == 0 || strcmp( value, "UIROTATIONTYPE_CCW" ) == 0 )
		return UIROTATIONTYPE_CCW;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EUIRotationType", value ) );
	return UIROTATIONTYPE_CW;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EUIScrollBarElementStyle value )
{
	switch( value )
	{
		case UISCROLLBARELEMENTSTYLE_NORMAL:
			return "Normal";
		case UISCROLLBARELEMENTSTYLE_HILITED:
			return "Hilited";
		case UISCROLLBARELEMENTSTYLE_PRESSED:
			return "Pressed";
		case UISCROLLBARELEMENTSTYLE_DISABLED:
			return "Disabled";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EUIScrollBarElementStyle", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EUIScrollBarElementStyle StringToEnum_EUIScrollBarElementStyle( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EUIScrollBarElementStyle)(NStr::ToInt( value ));
	if ( strcmp( value, "Normal" ) == 0 || strcmp( value, "UISCROLLBARELEMENTSTYLE_NORMAL" ) == 0 )
		return UISCROLLBARELEMENTSTYLE_NORMAL;
	if ( strcmp( value, "Hilited" ) == 0 || strcmp( value, "UISCROLLBARELEMENTSTYLE_HILITED" ) == 0 )
		return UISCROLLBARELEMENTSTYLE_HILITED;
	if ( strcmp( value, "Pressed" ) == 0 || strcmp( value, "UISCROLLBARELEMENTSTYLE_PRESSED" ) == 0 )
		return UISCROLLBARELEMENTSTYLE_PRESSED;
	if ( strcmp( value, "Disabled" ) == 0 || strcmp( value, "UISCROLLBARELEMENTSTYLE_DISABLED" ) == 0 )
		return UISCROLLBARELEMENTSTYLE_DISABLED;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EUIScrollBarElementStyle", value ) );
	return UISCROLLBARELEMENTSTYLE_NORMAL;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EUIScrollBarType value )
{
	switch( value )
	{
		case UISCROLLBARTYPE_VERTICAL:
			return "Vertical";
		case UISCROLLBARTYPE_HORIZONTAL:
			return "Horizontal";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EUIScrollBarType", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EUIScrollBarType StringToEnum_EUIScrollBarType( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EUIScrollBarType)(NStr::ToInt( value ));
	if ( strcmp( value, "Vertical" ) == 0 || strcmp( value, "UISCROLLBARTYPE_VERTICAL" ) == 0 )
		return UISCROLLBARTYPE_VERTICAL;
	if ( strcmp( value, "Horizontal" ) == 0 || strcmp( value, "UISCROLLBARTYPE_HORIZONTAL" ) == 0 )
		return UISCROLLBARTYPE_HORIZONTAL;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EUIScrollBarType", value ) );
	return UISCROLLBARTYPE_VERTICAL;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EUITextEntryType value )
{
	switch( value )
	{
		case UITEXTENTRYTYPE_FREE:
			return "Free";
		case UITEXTENTRYTYPE_CONSOLE:
			return "Console";
		case UITEXTENTRYTYPE_NUMERIC:
			return "Numeric";
		case UITEXTENTRYTYPE_IDENTIFIER:
			return "Identifier";
		case UITEXTENTRYTYPE_PLAYERNAME:
			return "PlayerName";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EUITextEntryType", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EUITextEntryType StringToEnum_EUITextEntryType( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EUITextEntryType)(NStr::ToInt( value ));
	if ( strcmp( value, "Free" ) == 0 || strcmp( value, "UITEXTENTRYTYPE_FREE" ) == 0 )
		return UITEXTENTRYTYPE_FREE;
	if ( strcmp( value, "Console" ) == 0 || strcmp( value, "UITEXTENTRYTYPE_CONSOLE" ) == 0 )
		return UITEXTENTRYTYPE_CONSOLE;
	if ( strcmp( value, "Numeric" ) == 0 || strcmp( value, "UITEXTENTRYTYPE_NUMERIC" ) == 0 )
		return UITEXTENTRYTYPE_NUMERIC;
	if ( strcmp( value, "Identifier" ) == 0 || strcmp( value, "UITEXTENTRYTYPE_IDENTIFIER" ) == 0 )
		return UITEXTENTRYTYPE_IDENTIFIER;
	if ( strcmp( value, "PlayerName" ) == 0 || strcmp( value, "UITEXTENTRYTYPE_PLAYERNAME" ) == 0 )
		return UITEXTENTRYTYPE_PLAYERNAME;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EUITextEntryType", value ) );
	return UITEXTENTRYTYPE_FREE;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EUITextHAlign value )
{
	switch( value )
	{
		case UITEXTHALIGN_RIGHT:
			return "Right";
		case UITEXTHALIGN_CENTER:
			return "Center";
		case UITEXTHALIGN_LEFT:
			return "Left";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EUITextHAlign", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EUITextHAlign StringToEnum_EUITextHAlign( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EUITextHAlign)(NStr::ToInt( value ));
	if ( strcmp( value, "Right" ) == 0 || strcmp( value, "UITEXTHALIGN_RIGHT" ) == 0 )
		return UITEXTHALIGN_RIGHT;
	if ( strcmp( value, "Center" ) == 0 || strcmp( value, "UITEXTHALIGN_CENTER" ) == 0 )
		return UITEXTHALIGN_CENTER;
	if ( strcmp( value, "Left" ) == 0 || strcmp( value, "UITEXTHALIGN_LEFT" ) == 0 )
		return UITEXTHALIGN_LEFT;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EUITextHAlign", value ) );
	return UITEXTHALIGN_RIGHT;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EUITextVAlign value )
{
	switch( value )
	{
		case UITEXTVALIGN_TOP:
			return "Top";
		case UITEXTVALIGN_CENTER:
			return "Center";
		case UITEXTVALIGN_BOTTOM:
			return "Bottom";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EUITextVAlign", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EUITextVAlign StringToEnum_EUITextVAlign( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EUITextVAlign)(NStr::ToInt( value ));
	if ( strcmp( value, "Top" ) == 0 || strcmp( value, "UITEXTVALIGN_TOP" ) == 0 )
		return UITEXTVALIGN_TOP;
	if ( strcmp( value, "Center" ) == 0 || strcmp( value, "UITEXTVALIGN_CENTER" ) == 0 )
		return UITEXTVALIGN_CENTER;
	if ( strcmp( value, "Bottom" ) == 0 || strcmp( value, "UITEXTVALIGN_BOTTOM" ) == 0 )
		return UITEXTVALIGN_BOTTOM;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EUITextVAlign", value ) );
	return UITEXTVALIGN_TOP;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UI3DOvertipDesc::UI3DOvertipDesc() :
		mode( UI3DOVERTIPMODE_WORLD )
	, depthBias( 0.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UI3DOvertipDesc::operator&( IBinSaver &saver )
{
	saver.Add( 2, &layout );
	saver.Add( 3, &mode );
	saver.Add( 4, &worldSize );
	saver.Add( 5, &align );
	saver.Add( 6, &depthBias );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UI3DOvertipDesc::operator&( IXmlSaver &saver )
{
	saver.Add( "layout", &layout );
	saver.Add( "mode", &mode );
	saver.Add( "worldSize", &worldSize );
	saver.Add( "align", &align );
	saver.Add( "depthBias", &depthBias );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UICatchEvents::UICatchEvents() :
		mouseMove( true )
	, leftMouseDown( true )
	, rightMouseDown( true )
	, leftMouseUp( true )
	, rightMouseUp( true )
	, leftDoubleClick( true )
	, rightDoubleClick( true )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UICatchEvents::operator&( IBinSaver &saver )
{
	saver.Add( 2, &mouseMove );
	saver.Add( 3, &leftMouseDown );
	saver.Add( 4, &rightMouseDown );
	saver.Add( 5, &leftMouseUp );
	saver.Add( 6, &rightMouseUp );
	saver.Add( 7, &leftDoubleClick );
	saver.Add( 8, &rightDoubleClick );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UICatchEvents::operator&( IXmlSaver &saver )
{
	saver.Add( "mouseMove", &mouseMove );
	saver.Add( "leftMouseDown", &leftMouseDown );
	saver.Add( "rightMouseDown", &rightMouseDown );
	saver.Add( "leftMouseUp", &leftMouseUp );
	saver.Add( "rightMouseUp", &rightMouseUp );
	saver.Add( "leftDoubleClick", &leftDoubleClick );
	saver.Add( "rightDoubleClick", &rightDoubleClick );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool UICatchEvents::IsEqual( const UICatchEvents& _uICatchEvents ) const
{
	return mouseMove == _uICatchEvents.mouseMove
		&& leftMouseDown == _uICatchEvents.leftMouseDown
		&& rightMouseDown == _uICatchEvents.rightMouseDown
		&& leftMouseUp == _uICatchEvents.leftMouseUp
		&& rightMouseUp == _uICatchEvents.rightMouseUp
		&& leftDoubleClick == _uICatchEvents.leftDoubleClick
		&& rightDoubleClick == _uICatchEvents.rightDoubleClick;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UICatchEvents::Assign( const UICatchEvents& _uICatchEvents )
{
	mouseMove = _uICatchEvents.mouseMove;
	leftMouseDown = _uICatchEvents.leftMouseDown;
	rightMouseDown = _uICatchEvents.rightMouseDown;
	leftMouseUp = _uICatchEvents.leftMouseUp;
	rightMouseUp = _uICatchEvents.rightMouseUp;
	leftDoubleClick = _uICatchEvents.leftDoubleClick;
	rightDoubleClick = _uICatchEvents.rightDoubleClick;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UIConstant::UIConstant()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UIConstant::operator&( IBinSaver &saver )
{
	saver.Add( 2, &name );
	saver.Add( 3, &value );
	saver.Add( 4, &comment );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UIConstant::operator&( IXmlSaver &saver )
{
	saver.Add( "name", &name );
	saver.Add( "value", &value );
	saver.Add( "comment", &comment );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UIContentGroup::UIContentGroup()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UIContentGroup::operator&( IBinSaver &saver )
{
	saver.Add( 2, &groupId );
	saver.Add( 3, &resources );
	saver.Add( 4, &comment );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UIContentGroup::operator&( IXmlSaver &saver )
{
	saver.Add( "groupId", &groupId );
	saver.Add( "resources", &resources );
	saver.Add( "comment", &comment );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UICursorDesc::UICursorDesc()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UICursorDesc::operator&( IBinSaver &saver )
{
	saver.Add( 2, &cursorId );
	saver.Add( 3, &cursor );
	saver.Add( 4, &cursorOverlay );
	saver.Add( 5, &cursorOverlayOffset );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UICursorDesc::operator&( IXmlSaver &saver )
{
	saver.Add( "cursorId", &cursorId );
	saver.Add( "cursor", &cursor );
	saver.Add( "cursorOverlay", &cursorOverlay );
	saver.Add( "cursorOverlayOffset", &cursorOverlayOffset );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UICursors::UICursors() :
		normal( "ui_normal" )
	, dragging( "ui_dragging" )
	, dragable( "ui_dragable" )
	, focused( "ui_focused" )
	, disabled( "ui_disabled" )
	, pushing( "ui_pushing" )
	, pushable( "ui_pushable" )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UICursors::operator&( IBinSaver &saver )
{
	saver.Add( 2, &normal );
	saver.Add( 3, &dragging );
	saver.Add( 4, &dragable );
	saver.Add( 5, &focused );
	saver.Add( 6, &disabled );
	saver.Add( 7, &pushing );
	saver.Add( 8, &pushable );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UICursors::operator&( IXmlSaver &saver )
{
	saver.Add( "normal", &normal );
	saver.Add( "dragging", &dragging );
	saver.Add( "dragable", &dragable );
	saver.Add( "focused", &focused );
	saver.Add( "disabled", &disabled );
	saver.Add( "pushing", &pushing );
	saver.Add( "pushable", &pushable );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool UICursors::IsEqual( const UICursors& _uICursors ) const
{
	return normal == _uICursors.normal
		&& dragging == _uICursors.dragging
		&& dragable == _uICursors.dragable
		&& focused == _uICursors.focused
		&& disabled == _uICursors.disabled
		&& pushing == _uICursors.pushing
		&& pushable == _uICursors.pushable;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UICursors::Assign( const UICursors& _uICursors )
{
	normal = _uICursors.normal;
	dragging = _uICursors.dragging;
	dragable = _uICursors.dragable;
	focused = _uICursors.focused;
	disabled = _uICursors.disabled;
	pushing = _uICursors.pushing;
	pushable = _uICursors.pushable;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UIFlashProperties::UIFlashProperties()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UIFlashProperties::operator&( IBinSaver &saver )
{
	saver.Add( 2, &propertyName );
	saver.Add( 3, &propertyValue );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UIFlashProperties::operator&( IXmlSaver &saver )
{
	saver.Add( "propertyName", &propertyName );
	saver.Add( "propertyValue", &propertyValue );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool UIFlashProperties::IsEqual( const UIFlashProperties& _uIFlashProperties ) const
{
	return propertyName == _uIFlashProperties.propertyName
		&& propertyValue == _uIFlashProperties.propertyValue;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UIHealthStripes::UIHealthStripes() :
		stripe1Step( 100.0f )
	, stripe2Step( 1000.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UIHealthStripes::operator&( IBinSaver &saver )
{
	saver.Add( 2, &stripe1Step );
	saver.Add( 3, &stripe2Step );
	saver.Add( 4, &allyColor100 );
	saver.Add( 5, &enemyColor100 );
	saver.Add( 6, &allyColor1000 );
	saver.Add( 7, &enemyColor1000 );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UIHealthStripes::operator&( IXmlSaver &saver )
{
	saver.Add( "stripe1Step", &stripe1Step );
	saver.Add( "stripe2Step", &stripe2Step );
	saver.Add( "allyColor100", &allyColor100 );
	saver.Add( "enemyColor100", &enemyColor100 );
	saver.Add( "allyColor1000", &allyColor1000 );
	saver.Add( "enemyColor1000", &enemyColor1000 );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UIPageTabElement::UIPageTabElement()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UIPageTabElement::operator&( IBinSaver &saver )
{
	saver.Add( 2, &button );
	saver.Add( 3, &page );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UIPageTabElement::operator&( IXmlSaver &saver )
{
	saver.Add( "button", &button );
	saver.Add( "page", &page );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool UIPageTabElement::IsEqual( const UIPageTabElement& _uIPageTabElement ) const
{
	return button == _uIPageTabElement.button
		&& page == _uIPageTabElement.page;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UIPlainOvertipDesc::UIPlainOvertipDesc() :
		bindPoint( UIOVERTIPBINDPOINT_CENTER )
	, useDepth( false )
	, depthBias( 0.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UIPlainOvertipDesc::operator&( IBinSaver &saver )
{
	saver.Add( 2, &bindPoint );
	saver.Add( 3, &layout );
	saver.Add( 4, &useDepth );
	saver.Add( 5, &depthBias );
	saver.Add( 6, &offset );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UIPlainOvertipDesc::operator&( IXmlSaver &saver )
{
	saver.Add( "bindPoint", &bindPoint );
	saver.Add( "layout", &layout );
	saver.Add( "useDepth", &useDepth );
	saver.Add( "depthBias", &depthBias );
	saver.Add( "offset", &offset );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UIRelatedLayout::UIRelatedLayout()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UIRelatedLayout::operator&( IBinSaver &saver )
{
	saver.Add( 2, &id );
	saver.Add( 3, &layout );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UIRelatedLayout::operator&( IXmlSaver &saver )
{
	saver.Add( "id", &id );
	saver.Add( "layout", &layout );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool UIRelatedLayout::IsEqual( const UIRelatedLayout& _uIRelatedLayout ) const
{
	return id == _uIRelatedLayout.id
		&& layout == _uIRelatedLayout.layout;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UIRelatedLayout::Assign( const UIRelatedLayout& _uIRelatedLayout )
{
	id = _uIRelatedLayout.id;
	layout = _uIRelatedLayout.layout;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UIRelatedText::UIRelatedText()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UIRelatedText::operator&( IBinSaver &saver )
{
	saver.Add( 2, &id );
	saver.Add( 3, &relatedText );
	saver.Add( 4, &comment );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UIRelatedText::operator&( IXmlSaver &saver )
{
	saver.Add( "id", &id );
	saver.Add( "relatedText", &relatedText );
	saver.Add( "comment", &comment );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool UIRelatedText::IsEqual( const UIRelatedText& _uIRelatedText ) const
{
	return id == _uIRelatedText.id
		&& relatedText == _uIRelatedText.relatedText
		&& comment == _uIRelatedText.comment;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UIRelatedText::Assign( const UIRelatedText& _uIRelatedText )
{
	id = _uIRelatedText.id;
	relatedText = _uIRelatedText.relatedText;
	comment = _uIRelatedText.comment;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UIScreenDesc::UIScreenDesc()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UIScreenDesc::operator&( IBinSaver &saver )
{
	saver.Add( 2, &screenId );
	saver.Add( 3, &baseLayout );
	saver.Add( 4, &comment );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UIScreenDesc::operator&( IXmlSaver &saver )
{
	saver.Add( "screenId", &screenId );
	saver.Add( "baseLayout", &baseLayout );
	saver.Add( "comment", &comment );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UIScriptDesc::UIScriptDesc()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UIScriptDesc::operator&( IBinSaver &saver )
{
	saver.Add( 2, &scriptFile );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UIScriptDesc::operator&( IXmlSaver &saver )
{
	saver.Add( "scriptFile", &scriptFile );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UIScrollLimits::UIScrollLimits() :
		inMin( 0.0f )
	, inMax( 1.0f )
	, outMin( 0 )
	, outMax( 0 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UIScrollLimits::operator&( IBinSaver &saver )
{
	saver.Add( 2, &inMin );
	saver.Add( 3, &inMax );
	saver.Add( 4, &outMin );
	saver.Add( 5, &outMax );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UIScrollLimits::operator&( IXmlSaver &saver )
{
	saver.Add( "inMin", &inMin );
	saver.Add( "inMax", &inMax );
	saver.Add( "outMin", &outMin );
	saver.Add( "outMax", &outMax );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool UIScrollLimits::IsEqual( const UIScrollLimits& _uIScrollLimits ) const
{
	return inMin == _uIScrollLimits.inMin
		&& inMax == _uIScrollLimits.inMax
		&& outMin == _uIScrollLimits.outMin
		&& outMax == _uIScrollLimits.outMax;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UISoundDesc::UISoundDesc()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UISoundDesc::operator&( IBinSaver &saver )
{

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UISoundDesc::operator&( IXmlSaver &saver )
{

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UIStyleAlias::UIStyleAlias()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UIStyleAlias::operator&( IBinSaver &saver )
{
	saver.Add( 2, &name );
	saver.Add( 3, &material );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UIStyleAlias::operator&( IXmlSaver &saver )
{
	saver.Add( "name", &name );
	saver.Add( "material", &material );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UITextSubstitute::UITextSubstitute()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UITextSubstitute::operator&( IBinSaver &saver )
{
	saver.Add( 2, &id );
	saver.Add( 3, &captionText );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UITextSubstitute::operator&( IXmlSaver &saver )
{
	saver.Add( "id", &id );
	saver.Add( "captionText", &captionText );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UICursorBase::UICursorBase()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UICursorBase::operator&( IBinSaver &saver )
{

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UICursorBase::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			UICursorBase* parentPtr = (UICursorBase*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UICursorBase::SerializeSelf( IXmlSaver &saver )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UICursorBase::Assign( const UICursorBase& _uICursorBase )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UILayout::UILayout() :
		visible( true )
	, enabled( true )
	, hAlign( UIELEMENTHALIGN_LEFT )
	, vAlign( UIELEMENTVALIGN_TOP )
	, keepAspectRatio( UIELEMENTASPECTRATIO_DONTCARE )
	, draggable( false )
	, transparent( false )
	, cursorTransparent( false )
	, needCrop( false )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UILayout::operator&( IBinSaver &saver )
{
	saver.Add( 2, &name );
	saver.Add( 3, &visible );
	saver.Add( 4, &enabled );
	saver.Add( 5, &location );
	saver.Add( 6, &size );
	saver.Add( 7, &hAlign );
	saver.Add( 8, &vAlign );
	saver.Add( 9, &keepAspectRatio );
	saver.Add( 10, &subclass );
	saver.Add( 11, &scriptFile );
	saver.Add( 12, &cursors );
	saver.Add( 13, &subLayouts );
	saver.Add( 14, &draggable );
	saver.Add( 15, &defaultEventsCatch );
	saver.Add( 16, &transparent );
	saver.Add( 17, &cursorTransparent );
	saver.Add( 18, &needCrop );
	saver.Add( 19, &relatedLayouts );
	saver.Add( 20, &relatedTexts );
	saver.Add( 21, &tooltipText );
	saver.Add( 22, &soundShow );
	saver.Add( 23, &soundHide );
	saver.Add( 24, &soundActivate );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UILayout::operator&( IXmlSaver &saver )
{
	bool inheritedStates = false;
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			UILayout* parentPtr = (UILayout*)__parent.GetPtr();
			Assign( *parentPtr );
			StateSerializeHelper< UILayout > parentStateCopier( this, stateManager.states, &UILayout::NewUILayout );
			parentStateCopier.InheritStates( parentPtr, parentPtr->GetStatesManager()->states, saver );
			inheritedStates = true;
		}
	}

	SerializeSelf( saver );
	if ( !inheritedStates )
	{
		StateSerializeHelper< UILayout > reader( this, stateManager.states, &UILayout::NewUILayout );
		saver.AddPolymorphicBase( "__states", &reader );
	}
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UILayout::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "name", &name );
	saver.Add( "visible", &visible );
	saver.Add( "enabled", &enabled );
	saver.Add( "location", &location );
	saver.Add( "size", &size );
	saver.Add( "hAlign", &hAlign );
	saver.Add( "vAlign", &vAlign );
	saver.Add( "keepAspectRatio", &keepAspectRatio );
	saver.Add( "subclass", &subclass );
	saver.Add( "scriptFile", &scriptFile );
	saver.Add( "cursors", &cursors );
	saver.Add( "subLayouts", &subLayouts );
	saver.Add( "draggable", &draggable );
	saver.Add( "defaultEventsCatch", &defaultEventsCatch );
	saver.Add( "transparent", &transparent );
	saver.Add( "cursorTransparent", &cursorTransparent );
	saver.Add( "needCrop", &needCrop );
	saver.Add( "relatedLayouts", &relatedLayouts );
	saver.Add( "relatedTexts", &relatedTexts );
	saver.Add( "tooltipText", &tooltipText );
	saver.Add( "soundShow", &soundShow );
	saver.Add( "soundHide", &soundHide );
	saver.Add( "soundActivate", &soundActivate );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool UILayout::IsEqual( const UILayout& _uILayout ) const
{
	return name == _uILayout.name
		&& visible == _uILayout.visible
		&& enabled == _uILayout.enabled
		&& location.x == _uILayout.location.x
		&& location.y == _uILayout.location.y
		&& size.x == _uILayout.size.x
		&& size.y == _uILayout.size.y
		&& hAlign == _uILayout.hAlign
		&& vAlign == _uILayout.vAlign
		&& keepAspectRatio == _uILayout.keepAspectRatio
		&& subclass == _uILayout.subclass
		&& scriptFile == _uILayout.scriptFile
		&& cursors.normal == _uILayout.cursors.normal
		&& cursors.dragging == _uILayout.cursors.dragging
		&& cursors.dragable == _uILayout.cursors.dragable
		&& cursors.focused == _uILayout.cursors.focused
		&& cursors.disabled == _uILayout.cursors.disabled
		&& cursors.pushing == _uILayout.cursors.pushing
		&& cursors.pushable == _uILayout.cursors.pushable
		&& subLayouts == _uILayout.subLayouts
		&& draggable == _uILayout.draggable
		&& defaultEventsCatch.mouseMove == _uILayout.defaultEventsCatch.mouseMove
		&& defaultEventsCatch.leftMouseDown == _uILayout.defaultEventsCatch.leftMouseDown
		&& defaultEventsCatch.rightMouseDown == _uILayout.defaultEventsCatch.rightMouseDown
		&& defaultEventsCatch.leftMouseUp == _uILayout.defaultEventsCatch.leftMouseUp
		&& defaultEventsCatch.rightMouseUp == _uILayout.defaultEventsCatch.rightMouseUp
		&& defaultEventsCatch.leftDoubleClick == _uILayout.defaultEventsCatch.leftDoubleClick
		&& defaultEventsCatch.rightDoubleClick == _uILayout.defaultEventsCatch.rightDoubleClick
		&& transparent == _uILayout.transparent
		&& cursorTransparent == _uILayout.cursorTransparent
		&& needCrop == _uILayout.needCrop
		&& relatedLayouts == _uILayout.relatedLayouts
		&& relatedTexts == _uILayout.relatedTexts
		&& tooltipText == _uILayout.tooltipText
		&& soundShow.projectName == _uILayout.soundShow.projectName
		&& soundShow.groupName == _uILayout.soundShow.groupName
		&& soundShow.eventName == _uILayout.soundShow.eventName
		&& soundHide.projectName == _uILayout.soundHide.projectName
		&& soundHide.groupName == _uILayout.soundHide.groupName
		&& soundHide.eventName == _uILayout.soundHide.eventName
		&& soundActivate.projectName == _uILayout.soundActivate.projectName
		&& soundActivate.groupName == _uILayout.soundActivate.groupName
		&& soundActivate.eventName == _uILayout.soundActivate.eventName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UILayout::Assign( const UILayout& _uILayout )
{
	name = _uILayout.name;
	visible = _uILayout.visible;
	enabled = _uILayout.enabled;
	location = _uILayout.location;
	size = _uILayout.size;
	hAlign = _uILayout.hAlign;
	vAlign = _uILayout.vAlign;
	keepAspectRatio = _uILayout.keepAspectRatio;
	subclass = _uILayout.subclass;
	scriptFile = _uILayout.scriptFile;
	cursors.normal = _uILayout.cursors.normal;
	cursors.dragging = _uILayout.cursors.dragging;
	cursors.dragable = _uILayout.cursors.dragable;
	cursors.focused = _uILayout.cursors.focused;
	cursors.disabled = _uILayout.cursors.disabled;
	cursors.pushing = _uILayout.cursors.pushing;
	cursors.pushable = _uILayout.cursors.pushable;
	subLayouts = _uILayout.subLayouts;
	draggable = _uILayout.draggable;
	defaultEventsCatch.mouseMove = _uILayout.defaultEventsCatch.mouseMove;
	defaultEventsCatch.leftMouseDown = _uILayout.defaultEventsCatch.leftMouseDown;
	defaultEventsCatch.rightMouseDown = _uILayout.defaultEventsCatch.rightMouseDown;
	defaultEventsCatch.leftMouseUp = _uILayout.defaultEventsCatch.leftMouseUp;
	defaultEventsCatch.rightMouseUp = _uILayout.defaultEventsCatch.rightMouseUp;
	defaultEventsCatch.leftDoubleClick = _uILayout.defaultEventsCatch.leftDoubleClick;
	defaultEventsCatch.rightDoubleClick = _uILayout.defaultEventsCatch.rightDoubleClick;
	transparent = _uILayout.transparent;
	cursorTransparent = _uILayout.cursorTransparent;
	needCrop = _uILayout.needCrop;
	relatedLayouts = _uILayout.relatedLayouts;
	relatedTexts = _uILayout.relatedTexts;
	tooltipText = _uILayout.tooltipText;
	soundShow.projectName = _uILayout.soundShow.projectName;
	soundShow.groupName = _uILayout.soundShow.groupName;
	soundShow.eventName = _uILayout.soundShow.eventName;
	soundHide.projectName = _uILayout.soundHide.projectName;
	soundHide.groupName = _uILayout.soundHide.groupName;
	soundHide.eventName = _uILayout.soundHide.eventName;
	soundActivate.projectName = _uILayout.soundActivate.projectName;
	soundActivate.groupName = _uILayout.soundActivate.groupName;
	soundActivate.eventName = _uILayout.soundActivate.eventName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UIImageLabelLayout::UIImageLabelLayout() :
		shapeType( IMAGELABELSHAPETYPE_FROMSHAPEORBACKGROUNDSTYLE )
	, wordWrap( true )
	, stretchText( false )
	, rawTextMode( false )
	, textVAlign( UITEXTVALIGN_CENTER )
	, textHAlign( UITEXTHALIGN_CENTER )
	, captionOpacity( 1.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UIImageLabelLayout::operator&( IBinSaver &saver )
{
	saver.Add( 1, (UILayout*)this );
	saver.Add( 2, &backgroundMaterial );
	saver.Add( 3, &shapeType );
	saver.Add( 4, &captionText );
	saver.Add( 5, &fontStyle );
	saver.Add( 6, &wordWrap );
	saver.Add( 7, &stretchText );
	saver.Add( 8, &rawTextMode );
	saver.Add( 9, &textVAlign );
	saver.Add( 10, &textHAlign );
	saver.Add( 11, &textMargins );
	saver.Add( 12, &captionOpacity );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UIImageLabelLayout::operator&( IXmlSaver &saver )
{
	bool inheritedStates = false;
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			UIImageLabelLayout* parentPtr = (UIImageLabelLayout*)__parent.GetPtr();
			Assign( *parentPtr );
			StateSerializeHelper< UIImageLabelLayout > parentStateCopier( this, stateManager.states, &UIImageLabelLayout::NewUIImageLabelLayout );
			parentStateCopier.InheritStates( parentPtr, parentPtr->GetStatesManager()->states, saver );
			inheritedStates = true;
		}
	}

	SerializeSelf( saver );
	if ( !inheritedStates )
	{
		StateSerializeHelper< UIImageLabelLayout > reader( this, stateManager.states, &UIImageLabelLayout::NewUIImageLabelLayout );
		saver.AddPolymorphicBase( "__states", &reader );
	}
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UIImageLabelLayout::SerializeSelf( IXmlSaver &saver )
{
	UILayout::SerializeSelf( saver );
	saver.Add( "backgroundMaterial", &backgroundMaterial );
	saver.Add( "shapeType", &shapeType );
	saver.Add( "captionText", &captionText );
	saver.Add( "fontStyle", &fontStyle );
	saver.Add( "wordWrap", &wordWrap );
	saver.Add( "stretchText", &stretchText );
	saver.Add( "rawTextMode", &rawTextMode );
	saver.Add( "textVAlign", &textVAlign );
	saver.Add( "textHAlign", &textHAlign );
	saver.Add( "textMargins", &textMargins );
	saver.Add( "captionOpacity", &captionOpacity );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool UIImageLabelLayout::IsEqual( const UIImageLabelLayout& _uIImageLabelLayout ) const
{
	return backgroundMaterial == _uIImageLabelLayout.backgroundMaterial
		&& shapeType == _uIImageLabelLayout.shapeType
		&& captionText == _uIImageLabelLayout.captionText
		&& fontStyle == _uIImageLabelLayout.fontStyle
		&& wordWrap == _uIImageLabelLayout.wordWrap
		&& stretchText == _uIImageLabelLayout.stretchText
		&& rawTextMode == _uIImageLabelLayout.rawTextMode
		&& textVAlign == _uIImageLabelLayout.textVAlign
		&& textHAlign == _uIImageLabelLayout.textHAlign
		&& textMargins.x1 == _uIImageLabelLayout.textMargins.x1
		&& textMargins.y1 == _uIImageLabelLayout.textMargins.y1
		&& textMargins.x2 == _uIImageLabelLayout.textMargins.x2
		&& textMargins.y2 == _uIImageLabelLayout.textMargins.y2
		&& captionOpacity == _uIImageLabelLayout.captionOpacity
		&& name == _uIImageLabelLayout.name
		&& visible == _uIImageLabelLayout.visible
		&& enabled == _uIImageLabelLayout.enabled
		&& location.x == _uIImageLabelLayout.location.x
		&& location.y == _uIImageLabelLayout.location.y
		&& size.x == _uIImageLabelLayout.size.x
		&& size.y == _uIImageLabelLayout.size.y
		&& hAlign == _uIImageLabelLayout.hAlign
		&& vAlign == _uIImageLabelLayout.vAlign
		&& keepAspectRatio == _uIImageLabelLayout.keepAspectRatio
		&& subclass == _uIImageLabelLayout.subclass
		&& scriptFile == _uIImageLabelLayout.scriptFile
		&& cursors.normal == _uIImageLabelLayout.cursors.normal
		&& cursors.dragging == _uIImageLabelLayout.cursors.dragging
		&& cursors.dragable == _uIImageLabelLayout.cursors.dragable
		&& cursors.focused == _uIImageLabelLayout.cursors.focused
		&& cursors.disabled == _uIImageLabelLayout.cursors.disabled
		&& cursors.pushing == _uIImageLabelLayout.cursors.pushing
		&& cursors.pushable == _uIImageLabelLayout.cursors.pushable
		&& subLayouts == _uIImageLabelLayout.subLayouts
		&& draggable == _uIImageLabelLayout.draggable
		&& defaultEventsCatch.mouseMove == _uIImageLabelLayout.defaultEventsCatch.mouseMove
		&& defaultEventsCatch.leftMouseDown == _uIImageLabelLayout.defaultEventsCatch.leftMouseDown
		&& defaultEventsCatch.rightMouseDown == _uIImageLabelLayout.defaultEventsCatch.rightMouseDown
		&& defaultEventsCatch.leftMouseUp == _uIImageLabelLayout.defaultEventsCatch.leftMouseUp
		&& defaultEventsCatch.rightMouseUp == _uIImageLabelLayout.defaultEventsCatch.rightMouseUp
		&& defaultEventsCatch.leftDoubleClick == _uIImageLabelLayout.defaultEventsCatch.leftDoubleClick
		&& defaultEventsCatch.rightDoubleClick == _uIImageLabelLayout.defaultEventsCatch.rightDoubleClick
		&& transparent == _uIImageLabelLayout.transparent
		&& cursorTransparent == _uIImageLabelLayout.cursorTransparent
		&& needCrop == _uIImageLabelLayout.needCrop
		&& relatedLayouts == _uIImageLabelLayout.relatedLayouts
		&& relatedTexts == _uIImageLabelLayout.relatedTexts
		&& tooltipText == _uIImageLabelLayout.tooltipText
		&& soundShow.projectName == _uIImageLabelLayout.soundShow.projectName
		&& soundShow.groupName == _uIImageLabelLayout.soundShow.groupName
		&& soundShow.eventName == _uIImageLabelLayout.soundShow.eventName
		&& soundHide.projectName == _uIImageLabelLayout.soundHide.projectName
		&& soundHide.groupName == _uIImageLabelLayout.soundHide.groupName
		&& soundHide.eventName == _uIImageLabelLayout.soundHide.eventName
		&& soundActivate.projectName == _uIImageLabelLayout.soundActivate.projectName
		&& soundActivate.groupName == _uIImageLabelLayout.soundActivate.groupName
		&& soundActivate.eventName == _uIImageLabelLayout.soundActivate.eventName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UIImageLabelLayout::Assign( const UIImageLabelLayout& _uIImageLabelLayout )
{
	backgroundMaterial = _uIImageLabelLayout.backgroundMaterial;
	shapeType = _uIImageLabelLayout.shapeType;
	captionText = _uIImageLabelLayout.captionText;
	fontStyle = _uIImageLabelLayout.fontStyle;
	wordWrap = _uIImageLabelLayout.wordWrap;
	stretchText = _uIImageLabelLayout.stretchText;
	rawTextMode = _uIImageLabelLayout.rawTextMode;
	textVAlign = _uIImageLabelLayout.textVAlign;
	textHAlign = _uIImageLabelLayout.textHAlign;
	textMargins = _uIImageLabelLayout.textMargins;
	captionOpacity = _uIImageLabelLayout.captionOpacity;
	name = _uIImageLabelLayout.name;
	visible = _uIImageLabelLayout.visible;
	enabled = _uIImageLabelLayout.enabled;
	location = _uIImageLabelLayout.location;
	size = _uIImageLabelLayout.size;
	hAlign = _uIImageLabelLayout.hAlign;
	vAlign = _uIImageLabelLayout.vAlign;
	keepAspectRatio = _uIImageLabelLayout.keepAspectRatio;
	subclass = _uIImageLabelLayout.subclass;
	scriptFile = _uIImageLabelLayout.scriptFile;
	cursors.normal = _uIImageLabelLayout.cursors.normal;
	cursors.dragging = _uIImageLabelLayout.cursors.dragging;
	cursors.dragable = _uIImageLabelLayout.cursors.dragable;
	cursors.focused = _uIImageLabelLayout.cursors.focused;
	cursors.disabled = _uIImageLabelLayout.cursors.disabled;
	cursors.pushing = _uIImageLabelLayout.cursors.pushing;
	cursors.pushable = _uIImageLabelLayout.cursors.pushable;
	subLayouts = _uIImageLabelLayout.subLayouts;
	draggable = _uIImageLabelLayout.draggable;
	defaultEventsCatch.mouseMove = _uIImageLabelLayout.defaultEventsCatch.mouseMove;
	defaultEventsCatch.leftMouseDown = _uIImageLabelLayout.defaultEventsCatch.leftMouseDown;
	defaultEventsCatch.rightMouseDown = _uIImageLabelLayout.defaultEventsCatch.rightMouseDown;
	defaultEventsCatch.leftMouseUp = _uIImageLabelLayout.defaultEventsCatch.leftMouseUp;
	defaultEventsCatch.rightMouseUp = _uIImageLabelLayout.defaultEventsCatch.rightMouseUp;
	defaultEventsCatch.leftDoubleClick = _uIImageLabelLayout.defaultEventsCatch.leftDoubleClick;
	defaultEventsCatch.rightDoubleClick = _uIImageLabelLayout.defaultEventsCatch.rightDoubleClick;
	transparent = _uIImageLabelLayout.transparent;
	cursorTransparent = _uIImageLabelLayout.cursorTransparent;
	needCrop = _uIImageLabelLayout.needCrop;
	relatedLayouts = _uIImageLabelLayout.relatedLayouts;
	relatedTexts = _uIImageLabelLayout.relatedTexts;
	tooltipText = _uIImageLabelLayout.tooltipText;
	soundShow.projectName = _uIImageLabelLayout.soundShow.projectName;
	soundShow.groupName = _uIImageLabelLayout.soundShow.groupName;
	soundShow.eventName = _uIImageLabelLayout.soundShow.eventName;
	soundHide.projectName = _uIImageLabelLayout.soundHide.projectName;
	soundHide.groupName = _uIImageLabelLayout.soundHide.groupName;
	soundHide.eventName = _uIImageLabelLayout.soundHide.eventName;
	soundActivate.projectName = _uIImageLabelLayout.soundActivate.projectName;
	soundActivate.groupName = _uIImageLabelLayout.soundActivate.groupName;
	soundActivate.eventName = _uIImageLabelLayout.soundActivate.eventName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UICommonControl::UICommonControl() :
		mouseActions( UICONTROLMOUSEACTIONS_LEFT )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UICommonControl::operator&( IBinSaver &saver )
{
	saver.Add( 1, (UIImageLabelLayout*)this );
	saver.Add( 2, &mouseActions );
	saver.Add( 3, &soundHilite );
	saver.Add( 4, &activationBind );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UICommonControl::operator&( IXmlSaver &saver )
{
	bool inheritedStates = false;
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			UICommonControl* parentPtr = (UICommonControl*)__parent.GetPtr();
			Assign( *parentPtr );
			StateSerializeHelper< UICommonControl > parentStateCopier( this, stateManager.states, &UICommonControl::NewUICommonControl );
			parentStateCopier.InheritStates( parentPtr, parentPtr->GetStatesManager()->states, saver );
			inheritedStates = true;
		}
	}

	SerializeSelf( saver );
	if ( !inheritedStates )
	{
		StateSerializeHelper< UICommonControl > reader( this, stateManager.states, &UICommonControl::NewUICommonControl );
		saver.AddPolymorphicBase( "__states", &reader );
	}
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UICommonControl::SerializeSelf( IXmlSaver &saver )
{
	UIImageLabelLayout::SerializeSelf( saver );
	saver.Add( "mouseActions", &mouseActions );
	saver.Add( "soundHilite", &soundHilite );
	saver.Add( "activationBind", &activationBind );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool UICommonControl::IsEqual( const UICommonControl& _uICommonControl ) const
{
	return mouseActions == _uICommonControl.mouseActions
		&& soundHilite.projectName == _uICommonControl.soundHilite.projectName
		&& soundHilite.groupName == _uICommonControl.soundHilite.groupName
		&& soundHilite.eventName == _uICommonControl.soundHilite.eventName
		&& activationBind == _uICommonControl.activationBind
		&& backgroundMaterial == _uICommonControl.backgroundMaterial
		&& shapeType == _uICommonControl.shapeType
		&& captionText == _uICommonControl.captionText
		&& fontStyle == _uICommonControl.fontStyle
		&& wordWrap == _uICommonControl.wordWrap
		&& stretchText == _uICommonControl.stretchText
		&& rawTextMode == _uICommonControl.rawTextMode
		&& textVAlign == _uICommonControl.textVAlign
		&& textHAlign == _uICommonControl.textHAlign
		&& textMargins.x1 == _uICommonControl.textMargins.x1
		&& textMargins.y1 == _uICommonControl.textMargins.y1
		&& textMargins.x2 == _uICommonControl.textMargins.x2
		&& textMargins.y2 == _uICommonControl.textMargins.y2
		&& captionOpacity == _uICommonControl.captionOpacity
		&& name == _uICommonControl.name
		&& visible == _uICommonControl.visible
		&& enabled == _uICommonControl.enabled
		&& location.x == _uICommonControl.location.x
		&& location.y == _uICommonControl.location.y
		&& size.x == _uICommonControl.size.x
		&& size.y == _uICommonControl.size.y
		&& hAlign == _uICommonControl.hAlign
		&& vAlign == _uICommonControl.vAlign
		&& keepAspectRatio == _uICommonControl.keepAspectRatio
		&& subclass == _uICommonControl.subclass
		&& scriptFile == _uICommonControl.scriptFile
		&& cursors.normal == _uICommonControl.cursors.normal
		&& cursors.dragging == _uICommonControl.cursors.dragging
		&& cursors.dragable == _uICommonControl.cursors.dragable
		&& cursors.focused == _uICommonControl.cursors.focused
		&& cursors.disabled == _uICommonControl.cursors.disabled
		&& cursors.pushing == _uICommonControl.cursors.pushing
		&& cursors.pushable == _uICommonControl.cursors.pushable
		&& subLayouts == _uICommonControl.subLayouts
		&& draggable == _uICommonControl.draggable
		&& defaultEventsCatch.mouseMove == _uICommonControl.defaultEventsCatch.mouseMove
		&& defaultEventsCatch.leftMouseDown == _uICommonControl.defaultEventsCatch.leftMouseDown
		&& defaultEventsCatch.rightMouseDown == _uICommonControl.defaultEventsCatch.rightMouseDown
		&& defaultEventsCatch.leftMouseUp == _uICommonControl.defaultEventsCatch.leftMouseUp
		&& defaultEventsCatch.rightMouseUp == _uICommonControl.defaultEventsCatch.rightMouseUp
		&& defaultEventsCatch.leftDoubleClick == _uICommonControl.defaultEventsCatch.leftDoubleClick
		&& defaultEventsCatch.rightDoubleClick == _uICommonControl.defaultEventsCatch.rightDoubleClick
		&& transparent == _uICommonControl.transparent
		&& cursorTransparent == _uICommonControl.cursorTransparent
		&& needCrop == _uICommonControl.needCrop
		&& relatedLayouts == _uICommonControl.relatedLayouts
		&& relatedTexts == _uICommonControl.relatedTexts
		&& tooltipText == _uICommonControl.tooltipText
		&& soundShow.projectName == _uICommonControl.soundShow.projectName
		&& soundShow.groupName == _uICommonControl.soundShow.groupName
		&& soundShow.eventName == _uICommonControl.soundShow.eventName
		&& soundHide.projectName == _uICommonControl.soundHide.projectName
		&& soundHide.groupName == _uICommonControl.soundHide.groupName
		&& soundHide.eventName == _uICommonControl.soundHide.eventName
		&& soundActivate.projectName == _uICommonControl.soundActivate.projectName
		&& soundActivate.groupName == _uICommonControl.soundActivate.groupName
		&& soundActivate.eventName == _uICommonControl.soundActivate.eventName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UICommonControl::Assign( const UICommonControl& _uICommonControl )
{
	mouseActions = _uICommonControl.mouseActions;
	soundHilite.projectName = _uICommonControl.soundHilite.projectName;
	soundHilite.groupName = _uICommonControl.soundHilite.groupName;
	soundHilite.eventName = _uICommonControl.soundHilite.eventName;
	activationBind = _uICommonControl.activationBind;
	backgroundMaterial = _uICommonControl.backgroundMaterial;
	shapeType = _uICommonControl.shapeType;
	captionText = _uICommonControl.captionText;
	fontStyle = _uICommonControl.fontStyle;
	wordWrap = _uICommonControl.wordWrap;
	stretchText = _uICommonControl.stretchText;
	rawTextMode = _uICommonControl.rawTextMode;
	textVAlign = _uICommonControl.textVAlign;
	textHAlign = _uICommonControl.textHAlign;
	textMargins = _uICommonControl.textMargins;
	captionOpacity = _uICommonControl.captionOpacity;
	name = _uICommonControl.name;
	visible = _uICommonControl.visible;
	enabled = _uICommonControl.enabled;
	location = _uICommonControl.location;
	size = _uICommonControl.size;
	hAlign = _uICommonControl.hAlign;
	vAlign = _uICommonControl.vAlign;
	keepAspectRatio = _uICommonControl.keepAspectRatio;
	subclass = _uICommonControl.subclass;
	scriptFile = _uICommonControl.scriptFile;
	cursors.normal = _uICommonControl.cursors.normal;
	cursors.dragging = _uICommonControl.cursors.dragging;
	cursors.dragable = _uICommonControl.cursors.dragable;
	cursors.focused = _uICommonControl.cursors.focused;
	cursors.disabled = _uICommonControl.cursors.disabled;
	cursors.pushing = _uICommonControl.cursors.pushing;
	cursors.pushable = _uICommonControl.cursors.pushable;
	subLayouts = _uICommonControl.subLayouts;
	draggable = _uICommonControl.draggable;
	defaultEventsCatch.mouseMove = _uICommonControl.defaultEventsCatch.mouseMove;
	defaultEventsCatch.leftMouseDown = _uICommonControl.defaultEventsCatch.leftMouseDown;
	defaultEventsCatch.rightMouseDown = _uICommonControl.defaultEventsCatch.rightMouseDown;
	defaultEventsCatch.leftMouseUp = _uICommonControl.defaultEventsCatch.leftMouseUp;
	defaultEventsCatch.rightMouseUp = _uICommonControl.defaultEventsCatch.rightMouseUp;
	defaultEventsCatch.leftDoubleClick = _uICommonControl.defaultEventsCatch.leftDoubleClick;
	defaultEventsCatch.rightDoubleClick = _uICommonControl.defaultEventsCatch.rightDoubleClick;
	transparent = _uICommonControl.transparent;
	cursorTransparent = _uICommonControl.cursorTransparent;
	needCrop = _uICommonControl.needCrop;
	relatedLayouts = _uICommonControl.relatedLayouts;
	relatedTexts = _uICommonControl.relatedTexts;
	tooltipText = _uICommonControl.tooltipText;
	soundShow.projectName = _uICommonControl.soundShow.projectName;
	soundShow.groupName = _uICommonControl.soundShow.groupName;
	soundShow.eventName = _uICommonControl.soundShow.eventName;
	soundHide.projectName = _uICommonControl.soundHide.projectName;
	soundHide.groupName = _uICommonControl.soundHide.groupName;
	soundHide.eventName = _uICommonControl.soundHide.eventName;
	soundActivate.projectName = _uICommonControl.soundActivate.projectName;
	soundActivate.groupName = _uICommonControl.soundActivate.groupName;
	soundActivate.eventName = _uICommonControl.soundActivate.eventName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UIButtonLayout::UIButtonLayout() :
		viewMode( UIBUTTONVIEWMODE_BYMATERIALS )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UIButtonLayout::operator&( IBinSaver &saver )
{
	saver.Add( 1, (UICommonControl*)this );
	saver.Add( 2, &highlightMaterial );
	saver.Add( 3, &pushedMaterial );
	saver.Add( 4, &disabledMaterial );
	saver.Add( 5, &flashedMaterial );
	saver.Add( 6, &viewMode );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UIButtonLayout::operator&( IXmlSaver &saver )
{
	bool inheritedStates = false;
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			UIButtonLayout* parentPtr = (UIButtonLayout*)__parent.GetPtr();
			Assign( *parentPtr );
			StateSerializeHelper< UIButtonLayout > parentStateCopier( this, stateManager.states, &UIButtonLayout::NewUIButtonLayout );
			parentStateCopier.InheritStates( parentPtr, parentPtr->GetStatesManager()->states, saver );
			inheritedStates = true;
		}
	}

	SerializeSelf( saver );
	if ( !inheritedStates )
	{
		StateSerializeHelper< UIButtonLayout > reader( this, stateManager.states, &UIButtonLayout::NewUIButtonLayout );
		saver.AddPolymorphicBase( "__states", &reader );
	}
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UIButtonLayout::SerializeSelf( IXmlSaver &saver )
{
	UICommonControl::SerializeSelf( saver );
	saver.Add( "highlightMaterial", &highlightMaterial );
	saver.Add( "pushedMaterial", &pushedMaterial );
	saver.Add( "disabledMaterial", &disabledMaterial );
	saver.Add( "flashedMaterial", &flashedMaterial );
	saver.Add( "viewMode", &viewMode );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool UIButtonLayout::IsEqual( const UIButtonLayout& _uIButtonLayout ) const
{
	return highlightMaterial == _uIButtonLayout.highlightMaterial
		&& pushedMaterial == _uIButtonLayout.pushedMaterial
		&& disabledMaterial == _uIButtonLayout.disabledMaterial
		&& flashedMaterial == _uIButtonLayout.flashedMaterial
		&& viewMode == _uIButtonLayout.viewMode
		&& mouseActions == _uIButtonLayout.mouseActions
		&& soundHilite.projectName == _uIButtonLayout.soundHilite.projectName
		&& soundHilite.groupName == _uIButtonLayout.soundHilite.groupName
		&& soundHilite.eventName == _uIButtonLayout.soundHilite.eventName
		&& activationBind == _uIButtonLayout.activationBind
		&& backgroundMaterial == _uIButtonLayout.backgroundMaterial
		&& shapeType == _uIButtonLayout.shapeType
		&& captionText == _uIButtonLayout.captionText
		&& fontStyle == _uIButtonLayout.fontStyle
		&& wordWrap == _uIButtonLayout.wordWrap
		&& stretchText == _uIButtonLayout.stretchText
		&& rawTextMode == _uIButtonLayout.rawTextMode
		&& textVAlign == _uIButtonLayout.textVAlign
		&& textHAlign == _uIButtonLayout.textHAlign
		&& textMargins.x1 == _uIButtonLayout.textMargins.x1
		&& textMargins.y1 == _uIButtonLayout.textMargins.y1
		&& textMargins.x2 == _uIButtonLayout.textMargins.x2
		&& textMargins.y2 == _uIButtonLayout.textMargins.y2
		&& captionOpacity == _uIButtonLayout.captionOpacity
		&& name == _uIButtonLayout.name
		&& visible == _uIButtonLayout.visible
		&& enabled == _uIButtonLayout.enabled
		&& location.x == _uIButtonLayout.location.x
		&& location.y == _uIButtonLayout.location.y
		&& size.x == _uIButtonLayout.size.x
		&& size.y == _uIButtonLayout.size.y
		&& hAlign == _uIButtonLayout.hAlign
		&& vAlign == _uIButtonLayout.vAlign
		&& keepAspectRatio == _uIButtonLayout.keepAspectRatio
		&& subclass == _uIButtonLayout.subclass
		&& scriptFile == _uIButtonLayout.scriptFile
		&& cursors.normal == _uIButtonLayout.cursors.normal
		&& cursors.dragging == _uIButtonLayout.cursors.dragging
		&& cursors.dragable == _uIButtonLayout.cursors.dragable
		&& cursors.focused == _uIButtonLayout.cursors.focused
		&& cursors.disabled == _uIButtonLayout.cursors.disabled
		&& cursors.pushing == _uIButtonLayout.cursors.pushing
		&& cursors.pushable == _uIButtonLayout.cursors.pushable
		&& subLayouts == _uIButtonLayout.subLayouts
		&& draggable == _uIButtonLayout.draggable
		&& defaultEventsCatch.mouseMove == _uIButtonLayout.defaultEventsCatch.mouseMove
		&& defaultEventsCatch.leftMouseDown == _uIButtonLayout.defaultEventsCatch.leftMouseDown
		&& defaultEventsCatch.rightMouseDown == _uIButtonLayout.defaultEventsCatch.rightMouseDown
		&& defaultEventsCatch.leftMouseUp == _uIButtonLayout.defaultEventsCatch.leftMouseUp
		&& defaultEventsCatch.rightMouseUp == _uIButtonLayout.defaultEventsCatch.rightMouseUp
		&& defaultEventsCatch.leftDoubleClick == _uIButtonLayout.defaultEventsCatch.leftDoubleClick
		&& defaultEventsCatch.rightDoubleClick == _uIButtonLayout.defaultEventsCatch.rightDoubleClick
		&& transparent == _uIButtonLayout.transparent
		&& cursorTransparent == _uIButtonLayout.cursorTransparent
		&& needCrop == _uIButtonLayout.needCrop
		&& relatedLayouts == _uIButtonLayout.relatedLayouts
		&& relatedTexts == _uIButtonLayout.relatedTexts
		&& tooltipText == _uIButtonLayout.tooltipText
		&& soundShow.projectName == _uIButtonLayout.soundShow.projectName
		&& soundShow.groupName == _uIButtonLayout.soundShow.groupName
		&& soundShow.eventName == _uIButtonLayout.soundShow.eventName
		&& soundHide.projectName == _uIButtonLayout.soundHide.projectName
		&& soundHide.groupName == _uIButtonLayout.soundHide.groupName
		&& soundHide.eventName == _uIButtonLayout.soundHide.eventName
		&& soundActivate.projectName == _uIButtonLayout.soundActivate.projectName
		&& soundActivate.groupName == _uIButtonLayout.soundActivate.groupName
		&& soundActivate.eventName == _uIButtonLayout.soundActivate.eventName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UIButtonLayout::Assign( const UIButtonLayout& _uIButtonLayout )
{
	highlightMaterial = _uIButtonLayout.highlightMaterial;
	pushedMaterial = _uIButtonLayout.pushedMaterial;
	disabledMaterial = _uIButtonLayout.disabledMaterial;
	flashedMaterial = _uIButtonLayout.flashedMaterial;
	viewMode = _uIButtonLayout.viewMode;
	mouseActions = _uIButtonLayout.mouseActions;
	soundHilite.projectName = _uIButtonLayout.soundHilite.projectName;
	soundHilite.groupName = _uIButtonLayout.soundHilite.groupName;
	soundHilite.eventName = _uIButtonLayout.soundHilite.eventName;
	activationBind = _uIButtonLayout.activationBind;
	backgroundMaterial = _uIButtonLayout.backgroundMaterial;
	shapeType = _uIButtonLayout.shapeType;
	captionText = _uIButtonLayout.captionText;
	fontStyle = _uIButtonLayout.fontStyle;
	wordWrap = _uIButtonLayout.wordWrap;
	stretchText = _uIButtonLayout.stretchText;
	rawTextMode = _uIButtonLayout.rawTextMode;
	textVAlign = _uIButtonLayout.textVAlign;
	textHAlign = _uIButtonLayout.textHAlign;
	textMargins = _uIButtonLayout.textMargins;
	captionOpacity = _uIButtonLayout.captionOpacity;
	name = _uIButtonLayout.name;
	visible = _uIButtonLayout.visible;
	enabled = _uIButtonLayout.enabled;
	location = _uIButtonLayout.location;
	size = _uIButtonLayout.size;
	hAlign = _uIButtonLayout.hAlign;
	vAlign = _uIButtonLayout.vAlign;
	keepAspectRatio = _uIButtonLayout.keepAspectRatio;
	subclass = _uIButtonLayout.subclass;
	scriptFile = _uIButtonLayout.scriptFile;
	cursors.normal = _uIButtonLayout.cursors.normal;
	cursors.dragging = _uIButtonLayout.cursors.dragging;
	cursors.dragable = _uIButtonLayout.cursors.dragable;
	cursors.focused = _uIButtonLayout.cursors.focused;
	cursors.disabled = _uIButtonLayout.cursors.disabled;
	cursors.pushing = _uIButtonLayout.cursors.pushing;
	cursors.pushable = _uIButtonLayout.cursors.pushable;
	subLayouts = _uIButtonLayout.subLayouts;
	draggable = _uIButtonLayout.draggable;
	defaultEventsCatch.mouseMove = _uIButtonLayout.defaultEventsCatch.mouseMove;
	defaultEventsCatch.leftMouseDown = _uIButtonLayout.defaultEventsCatch.leftMouseDown;
	defaultEventsCatch.rightMouseDown = _uIButtonLayout.defaultEventsCatch.rightMouseDown;
	defaultEventsCatch.leftMouseUp = _uIButtonLayout.defaultEventsCatch.leftMouseUp;
	defaultEventsCatch.rightMouseUp = _uIButtonLayout.defaultEventsCatch.rightMouseUp;
	defaultEventsCatch.leftDoubleClick = _uIButtonLayout.defaultEventsCatch.leftDoubleClick;
	defaultEventsCatch.rightDoubleClick = _uIButtonLayout.defaultEventsCatch.rightDoubleClick;
	transparent = _uIButtonLayout.transparent;
	cursorTransparent = _uIButtonLayout.cursorTransparent;
	needCrop = _uIButtonLayout.needCrop;
	relatedLayouts = _uIButtonLayout.relatedLayouts;
	relatedTexts = _uIButtonLayout.relatedTexts;
	tooltipText = _uIButtonLayout.tooltipText;
	soundShow.projectName = _uIButtonLayout.soundShow.projectName;
	soundShow.groupName = _uIButtonLayout.soundShow.groupName;
	soundShow.eventName = _uIButtonLayout.soundShow.eventName;
	soundHide.projectName = _uIButtonLayout.soundHide.projectName;
	soundHide.groupName = _uIButtonLayout.soundHide.groupName;
	soundHide.eventName = _uIButtonLayout.soundHide.eventName;
	soundActivate.projectName = _uIButtonLayout.soundActivate.projectName;
	soundActivate.groupName = _uIButtonLayout.soundActivate.groupName;
	soundActivate.eventName = _uIButtonLayout.soundActivate.eventName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UIContentResource::UIContentResource()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UIContentResource::operator&( IBinSaver &saver )
{
	saver.Add( 2, &contentId );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UIContentResource::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			UIContentResource* parentPtr = (UIContentResource*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UIContentResource::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "contentId", &contentId );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UIContentResource::Assign( const UIContentResource& _uIContentResource )
{
	contentId = _uIContentResource.contentId;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UICursor::UICursor() :
		hotSpotX( 0 )
	, hotSpotY( 0 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UICursor::operator&( IBinSaver &saver )
{
	saver.Add( 1, (UICursorBase*)this );
	saver.Add( 2, &texture );
	saver.Add( 3, &hotSpotX );
	saver.Add( 4, &hotSpotY );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UICursor::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			UICursor* parentPtr = (UICursor*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UICursor::SerializeSelf( IXmlSaver &saver )
{
	UICursorBase::SerializeSelf( saver );
	saver.Add( "texture", &texture );
	saver.Add( "hotSpotX", &hotSpotX );
	saver.Add( "hotSpotY", &hotSpotY );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UICursor::Assign( const UICursor& _uICursor )
{
	texture = _uICursor.texture;
	hotSpotX = _uICursor.hotSpotX;
	hotSpotY = _uICursor.hotSpotY;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UIAnimatedCursor::UIAnimatedCursor() :
		frameCount( 1 )
	, fps( 10 )
	, delay( 0.0f )
	, hotSpotX( 0 )
	, hotSpotY( 0 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UIAnimatedCursor::operator&( IBinSaver &saver )
{
	saver.Add( 1, (UICursorBase*)this );
	saver.Add( 2, &srcFileName );
	saver.Add( 3, &dstFileName );
	saver.Add( 4, &frameCount );
	saver.Add( 5, &fps );
	saver.Add( 6, &delay );
	saver.Add( 7, &hotSpotX );
	saver.Add( 8, &hotSpotY );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UIAnimatedCursor::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			UIAnimatedCursor* parentPtr = (UIAnimatedCursor*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UIAnimatedCursor::SerializeSelf( IXmlSaver &saver )
{
	UICursorBase::SerializeSelf( saver );
	saver.Add( "srcFileName", &srcFileName );
	saver.Add( "dstFileName", &dstFileName );
	saver.Add( "frameCount", &frameCount );
	saver.Add( "fps", &fps );
	saver.Add( "delay", &delay );
	saver.Add( "hotSpotX", &hotSpotX );
	saver.Add( "hotSpotY", &hotSpotY );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UIAnimatedCursor::Assign( const UIAnimatedCursor& _uIAnimatedCursor )
{
	srcFileName = _uIAnimatedCursor.srcFileName;
	dstFileName = _uIAnimatedCursor.dstFileName;
	frameCount = _uIAnimatedCursor.frameCount;
	fps = _uIAnimatedCursor.fps;
	delay = _uIAnimatedCursor.delay;
	hotSpotX = _uIAnimatedCursor.hotSpotX;
	hotSpotY = _uIAnimatedCursor.hotSpotY;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UIEditBoxLayout::UIEditBoxLayout() :
		maxLength( 65535 )
	, isPassword( false )
	, maxLines( 1 )
	, textEntryType( UITEXTENTRYTYPE_FREE )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UIEditBoxLayout::operator&( IBinSaver &saver )
{
	saver.Add( 1, (UIImageLabelLayout*)this );
	saver.Add( 2, &disabledMaterial );
	saver.Add( 3, &cursorMaterial );
	saver.Add( 4, &maxLength );
	saver.Add( 5, &isPassword );
	saver.Add( 6, &maxLines );
	saver.Add( 7, &textEntryType );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UIEditBoxLayout::operator&( IXmlSaver &saver )
{
	bool inheritedStates = false;
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			UIEditBoxLayout* parentPtr = (UIEditBoxLayout*)__parent.GetPtr();
			Assign( *parentPtr );
			StateSerializeHelper< UIEditBoxLayout > parentStateCopier( this, stateManager.states, &UIEditBoxLayout::NewUIEditBoxLayout );
			parentStateCopier.InheritStates( parentPtr, parentPtr->GetStatesManager()->states, saver );
			inheritedStates = true;
		}
	}

	SerializeSelf( saver );
	if ( !inheritedStates )
	{
		StateSerializeHelper< UIEditBoxLayout > reader( this, stateManager.states, &UIEditBoxLayout::NewUIEditBoxLayout );
		saver.AddPolymorphicBase( "__states", &reader );
	}
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UIEditBoxLayout::SerializeSelf( IXmlSaver &saver )
{
	UIImageLabelLayout::SerializeSelf( saver );
	saver.Add( "disabledMaterial", &disabledMaterial );
	saver.Add( "cursorMaterial", &cursorMaterial );
	saver.Add( "maxLength", &maxLength );
	saver.Add( "isPassword", &isPassword );
	saver.Add( "maxLines", &maxLines );
	saver.Add( "textEntryType", &textEntryType );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool UIEditBoxLayout::IsEqual( const UIEditBoxLayout& _uIEditBoxLayout ) const
{
	return disabledMaterial == _uIEditBoxLayout.disabledMaterial
		&& cursorMaterial == _uIEditBoxLayout.cursorMaterial
		&& maxLength == _uIEditBoxLayout.maxLength
		&& isPassword == _uIEditBoxLayout.isPassword
		&& maxLines == _uIEditBoxLayout.maxLines
		&& textEntryType == _uIEditBoxLayout.textEntryType
		&& backgroundMaterial == _uIEditBoxLayout.backgroundMaterial
		&& shapeType == _uIEditBoxLayout.shapeType
		&& captionText == _uIEditBoxLayout.captionText
		&& fontStyle == _uIEditBoxLayout.fontStyle
		&& wordWrap == _uIEditBoxLayout.wordWrap
		&& stretchText == _uIEditBoxLayout.stretchText
		&& rawTextMode == _uIEditBoxLayout.rawTextMode
		&& textVAlign == _uIEditBoxLayout.textVAlign
		&& textHAlign == _uIEditBoxLayout.textHAlign
		&& textMargins.x1 == _uIEditBoxLayout.textMargins.x1
		&& textMargins.y1 == _uIEditBoxLayout.textMargins.y1
		&& textMargins.x2 == _uIEditBoxLayout.textMargins.x2
		&& textMargins.y2 == _uIEditBoxLayout.textMargins.y2
		&& captionOpacity == _uIEditBoxLayout.captionOpacity
		&& name == _uIEditBoxLayout.name
		&& visible == _uIEditBoxLayout.visible
		&& enabled == _uIEditBoxLayout.enabled
		&& location.x == _uIEditBoxLayout.location.x
		&& location.y == _uIEditBoxLayout.location.y
		&& size.x == _uIEditBoxLayout.size.x
		&& size.y == _uIEditBoxLayout.size.y
		&& hAlign == _uIEditBoxLayout.hAlign
		&& vAlign == _uIEditBoxLayout.vAlign
		&& keepAspectRatio == _uIEditBoxLayout.keepAspectRatio
		&& subclass == _uIEditBoxLayout.subclass
		&& scriptFile == _uIEditBoxLayout.scriptFile
		&& cursors.normal == _uIEditBoxLayout.cursors.normal
		&& cursors.dragging == _uIEditBoxLayout.cursors.dragging
		&& cursors.dragable == _uIEditBoxLayout.cursors.dragable
		&& cursors.focused == _uIEditBoxLayout.cursors.focused
		&& cursors.disabled == _uIEditBoxLayout.cursors.disabled
		&& cursors.pushing == _uIEditBoxLayout.cursors.pushing
		&& cursors.pushable == _uIEditBoxLayout.cursors.pushable
		&& subLayouts == _uIEditBoxLayout.subLayouts
		&& draggable == _uIEditBoxLayout.draggable
		&& defaultEventsCatch.mouseMove == _uIEditBoxLayout.defaultEventsCatch.mouseMove
		&& defaultEventsCatch.leftMouseDown == _uIEditBoxLayout.defaultEventsCatch.leftMouseDown
		&& defaultEventsCatch.rightMouseDown == _uIEditBoxLayout.defaultEventsCatch.rightMouseDown
		&& defaultEventsCatch.leftMouseUp == _uIEditBoxLayout.defaultEventsCatch.leftMouseUp
		&& defaultEventsCatch.rightMouseUp == _uIEditBoxLayout.defaultEventsCatch.rightMouseUp
		&& defaultEventsCatch.leftDoubleClick == _uIEditBoxLayout.defaultEventsCatch.leftDoubleClick
		&& defaultEventsCatch.rightDoubleClick == _uIEditBoxLayout.defaultEventsCatch.rightDoubleClick
		&& transparent == _uIEditBoxLayout.transparent
		&& cursorTransparent == _uIEditBoxLayout.cursorTransparent
		&& needCrop == _uIEditBoxLayout.needCrop
		&& relatedLayouts == _uIEditBoxLayout.relatedLayouts
		&& relatedTexts == _uIEditBoxLayout.relatedTexts
		&& tooltipText == _uIEditBoxLayout.tooltipText
		&& soundShow.projectName == _uIEditBoxLayout.soundShow.projectName
		&& soundShow.groupName == _uIEditBoxLayout.soundShow.groupName
		&& soundShow.eventName == _uIEditBoxLayout.soundShow.eventName
		&& soundHide.projectName == _uIEditBoxLayout.soundHide.projectName
		&& soundHide.groupName == _uIEditBoxLayout.soundHide.groupName
		&& soundHide.eventName == _uIEditBoxLayout.soundHide.eventName
		&& soundActivate.projectName == _uIEditBoxLayout.soundActivate.projectName
		&& soundActivate.groupName == _uIEditBoxLayout.soundActivate.groupName
		&& soundActivate.eventName == _uIEditBoxLayout.soundActivate.eventName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UIEditBoxLayout::Assign( const UIEditBoxLayout& _uIEditBoxLayout )
{
	disabledMaterial = _uIEditBoxLayout.disabledMaterial;
	cursorMaterial = _uIEditBoxLayout.cursorMaterial;
	maxLength = _uIEditBoxLayout.maxLength;
	isPassword = _uIEditBoxLayout.isPassword;
	maxLines = _uIEditBoxLayout.maxLines;
	textEntryType = _uIEditBoxLayout.textEntryType;
	backgroundMaterial = _uIEditBoxLayout.backgroundMaterial;
	shapeType = _uIEditBoxLayout.shapeType;
	captionText = _uIEditBoxLayout.captionText;
	fontStyle = _uIEditBoxLayout.fontStyle;
	wordWrap = _uIEditBoxLayout.wordWrap;
	stretchText = _uIEditBoxLayout.stretchText;
	rawTextMode = _uIEditBoxLayout.rawTextMode;
	textVAlign = _uIEditBoxLayout.textVAlign;
	textHAlign = _uIEditBoxLayout.textHAlign;
	textMargins = _uIEditBoxLayout.textMargins;
	captionOpacity = _uIEditBoxLayout.captionOpacity;
	name = _uIEditBoxLayout.name;
	visible = _uIEditBoxLayout.visible;
	enabled = _uIEditBoxLayout.enabled;
	location = _uIEditBoxLayout.location;
	size = _uIEditBoxLayout.size;
	hAlign = _uIEditBoxLayout.hAlign;
	vAlign = _uIEditBoxLayout.vAlign;
	keepAspectRatio = _uIEditBoxLayout.keepAspectRatio;
	subclass = _uIEditBoxLayout.subclass;
	scriptFile = _uIEditBoxLayout.scriptFile;
	cursors.normal = _uIEditBoxLayout.cursors.normal;
	cursors.dragging = _uIEditBoxLayout.cursors.dragging;
	cursors.dragable = _uIEditBoxLayout.cursors.dragable;
	cursors.focused = _uIEditBoxLayout.cursors.focused;
	cursors.disabled = _uIEditBoxLayout.cursors.disabled;
	cursors.pushing = _uIEditBoxLayout.cursors.pushing;
	cursors.pushable = _uIEditBoxLayout.cursors.pushable;
	subLayouts = _uIEditBoxLayout.subLayouts;
	draggable = _uIEditBoxLayout.draggable;
	defaultEventsCatch.mouseMove = _uIEditBoxLayout.defaultEventsCatch.mouseMove;
	defaultEventsCatch.leftMouseDown = _uIEditBoxLayout.defaultEventsCatch.leftMouseDown;
	defaultEventsCatch.rightMouseDown = _uIEditBoxLayout.defaultEventsCatch.rightMouseDown;
	defaultEventsCatch.leftMouseUp = _uIEditBoxLayout.defaultEventsCatch.leftMouseUp;
	defaultEventsCatch.rightMouseUp = _uIEditBoxLayout.defaultEventsCatch.rightMouseUp;
	defaultEventsCatch.leftDoubleClick = _uIEditBoxLayout.defaultEventsCatch.leftDoubleClick;
	defaultEventsCatch.rightDoubleClick = _uIEditBoxLayout.defaultEventsCatch.rightDoubleClick;
	transparent = _uIEditBoxLayout.transparent;
	cursorTransparent = _uIEditBoxLayout.cursorTransparent;
	needCrop = _uIEditBoxLayout.needCrop;
	relatedLayouts = _uIEditBoxLayout.relatedLayouts;
	relatedTexts = _uIEditBoxLayout.relatedTexts;
	tooltipText = _uIEditBoxLayout.tooltipText;
	soundShow.projectName = _uIEditBoxLayout.soundShow.projectName;
	soundShow.groupName = _uIEditBoxLayout.soundShow.groupName;
	soundShow.eventName = _uIEditBoxLayout.soundShow.eventName;
	soundHide.projectName = _uIEditBoxLayout.soundHide.projectName;
	soundHide.groupName = _uIEditBoxLayout.soundHide.groupName;
	soundHide.eventName = _uIEditBoxLayout.soundHide.eventName;
	soundActivate.projectName = _uIEditBoxLayout.soundActivate.projectName;
	soundActivate.groupName = _uIEditBoxLayout.soundActivate.groupName;
	soundActivate.eventName = _uIEditBoxLayout.soundActivate.eventName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UIFlashLayout::UIFlashLayout() :
		useScissorTest( false )
	, useOwnSize( false )
	, triangulationError( 1.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UIFlashLayout::operator&( IBinSaver &saver )
{
	saver.Add( 1, (UILayout*)this );
	saver.Add( 2, &srcFileName );
	saver.Add( 3, &useScissorTest );
	saver.Add( 4, &useOwnSize );
	saver.Add( 5, &triangulationError );
	saver.Add( 6, &properties );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UIFlashLayout::operator&( IXmlSaver &saver )
{
	bool inheritedStates = false;
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			UIFlashLayout* parentPtr = (UIFlashLayout*)__parent.GetPtr();
			Assign( *parentPtr );
			StateSerializeHelper< UIFlashLayout > parentStateCopier( this, stateManager.states, &UIFlashLayout::NewUIFlashLayout );
			parentStateCopier.InheritStates( parentPtr, parentPtr->GetStatesManager()->states, saver );
			inheritedStates = true;
		}
	}

	SerializeSelf( saver );
	if ( !inheritedStates )
	{
		StateSerializeHelper< UIFlashLayout > reader( this, stateManager.states, &UIFlashLayout::NewUIFlashLayout );
		saver.AddPolymorphicBase( "__states", &reader );
	}
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UIFlashLayout::SerializeSelf( IXmlSaver &saver )
{
	UILayout::SerializeSelf( saver );
	saver.Add( "srcFileName", &srcFileName );
	saver.Add( "useScissorTest", &useScissorTest );
	saver.Add( "useOwnSize", &useOwnSize );
	saver.Add( "triangulationError", &triangulationError );
	saver.Add( "properties", &properties );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool UIFlashLayout::IsEqual( const UIFlashLayout& _uIFlashLayout ) const
{
	return srcFileName == _uIFlashLayout.srcFileName
		&& useScissorTest == _uIFlashLayout.useScissorTest
		&& useOwnSize == _uIFlashLayout.useOwnSize
		&& triangulationError == _uIFlashLayout.triangulationError
		&& properties == _uIFlashLayout.properties
		&& name == _uIFlashLayout.name
		&& visible == _uIFlashLayout.visible
		&& enabled == _uIFlashLayout.enabled
		&& location.x == _uIFlashLayout.location.x
		&& location.y == _uIFlashLayout.location.y
		&& size.x == _uIFlashLayout.size.x
		&& size.y == _uIFlashLayout.size.y
		&& hAlign == _uIFlashLayout.hAlign
		&& vAlign == _uIFlashLayout.vAlign
		&& keepAspectRatio == _uIFlashLayout.keepAspectRatio
		&& subclass == _uIFlashLayout.subclass
		&& scriptFile == _uIFlashLayout.scriptFile
		&& cursors.normal == _uIFlashLayout.cursors.normal
		&& cursors.dragging == _uIFlashLayout.cursors.dragging
		&& cursors.dragable == _uIFlashLayout.cursors.dragable
		&& cursors.focused == _uIFlashLayout.cursors.focused
		&& cursors.disabled == _uIFlashLayout.cursors.disabled
		&& cursors.pushing == _uIFlashLayout.cursors.pushing
		&& cursors.pushable == _uIFlashLayout.cursors.pushable
		&& subLayouts == _uIFlashLayout.subLayouts
		&& draggable == _uIFlashLayout.draggable
		&& defaultEventsCatch.mouseMove == _uIFlashLayout.defaultEventsCatch.mouseMove
		&& defaultEventsCatch.leftMouseDown == _uIFlashLayout.defaultEventsCatch.leftMouseDown
		&& defaultEventsCatch.rightMouseDown == _uIFlashLayout.defaultEventsCatch.rightMouseDown
		&& defaultEventsCatch.leftMouseUp == _uIFlashLayout.defaultEventsCatch.leftMouseUp
		&& defaultEventsCatch.rightMouseUp == _uIFlashLayout.defaultEventsCatch.rightMouseUp
		&& defaultEventsCatch.leftDoubleClick == _uIFlashLayout.defaultEventsCatch.leftDoubleClick
		&& defaultEventsCatch.rightDoubleClick == _uIFlashLayout.defaultEventsCatch.rightDoubleClick
		&& transparent == _uIFlashLayout.transparent
		&& cursorTransparent == _uIFlashLayout.cursorTransparent
		&& needCrop == _uIFlashLayout.needCrop
		&& relatedLayouts == _uIFlashLayout.relatedLayouts
		&& relatedTexts == _uIFlashLayout.relatedTexts
		&& tooltipText == _uIFlashLayout.tooltipText
		&& soundShow.projectName == _uIFlashLayout.soundShow.projectName
		&& soundShow.groupName == _uIFlashLayout.soundShow.groupName
		&& soundShow.eventName == _uIFlashLayout.soundShow.eventName
		&& soundHide.projectName == _uIFlashLayout.soundHide.projectName
		&& soundHide.groupName == _uIFlashLayout.soundHide.groupName
		&& soundHide.eventName == _uIFlashLayout.soundHide.eventName
		&& soundActivate.projectName == _uIFlashLayout.soundActivate.projectName
		&& soundActivate.groupName == _uIFlashLayout.soundActivate.groupName
		&& soundActivate.eventName == _uIFlashLayout.soundActivate.eventName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UIFlashLayout::Assign( const UIFlashLayout& _uIFlashLayout )
{
	srcFileName = _uIFlashLayout.srcFileName;
	useScissorTest = _uIFlashLayout.useScissorTest;
	useOwnSize = _uIFlashLayout.useOwnSize;
	triangulationError = _uIFlashLayout.triangulationError;
	properties = _uIFlashLayout.properties;
	name = _uIFlashLayout.name;
	visible = _uIFlashLayout.visible;
	enabled = _uIFlashLayout.enabled;
	location = _uIFlashLayout.location;
	size = _uIFlashLayout.size;
	hAlign = _uIFlashLayout.hAlign;
	vAlign = _uIFlashLayout.vAlign;
	keepAspectRatio = _uIFlashLayout.keepAspectRatio;
	subclass = _uIFlashLayout.subclass;
	scriptFile = _uIFlashLayout.scriptFile;
	cursors.normal = _uIFlashLayout.cursors.normal;
	cursors.dragging = _uIFlashLayout.cursors.dragging;
	cursors.dragable = _uIFlashLayout.cursors.dragable;
	cursors.focused = _uIFlashLayout.cursors.focused;
	cursors.disabled = _uIFlashLayout.cursors.disabled;
	cursors.pushing = _uIFlashLayout.cursors.pushing;
	cursors.pushable = _uIFlashLayout.cursors.pushable;
	subLayouts = _uIFlashLayout.subLayouts;
	draggable = _uIFlashLayout.draggable;
	defaultEventsCatch.mouseMove = _uIFlashLayout.defaultEventsCatch.mouseMove;
	defaultEventsCatch.leftMouseDown = _uIFlashLayout.defaultEventsCatch.leftMouseDown;
	defaultEventsCatch.rightMouseDown = _uIFlashLayout.defaultEventsCatch.rightMouseDown;
	defaultEventsCatch.leftMouseUp = _uIFlashLayout.defaultEventsCatch.leftMouseUp;
	defaultEventsCatch.rightMouseUp = _uIFlashLayout.defaultEventsCatch.rightMouseUp;
	defaultEventsCatch.leftDoubleClick = _uIFlashLayout.defaultEventsCatch.leftDoubleClick;
	defaultEventsCatch.rightDoubleClick = _uIFlashLayout.defaultEventsCatch.rightDoubleClick;
	transparent = _uIFlashLayout.transparent;
	cursorTransparent = _uIFlashLayout.cursorTransparent;
	needCrop = _uIFlashLayout.needCrop;
	relatedLayouts = _uIFlashLayout.relatedLayouts;
	relatedTexts = _uIFlashLayout.relatedTexts;
	tooltipText = _uIFlashLayout.tooltipText;
	soundShow.projectName = _uIFlashLayout.soundShow.projectName;
	soundShow.groupName = _uIFlashLayout.soundShow.groupName;
	soundShow.eventName = _uIFlashLayout.soundShow.eventName;
	soundHide.projectName = _uIFlashLayout.soundHide.projectName;
	soundHide.groupName = _uIFlashLayout.soundHide.groupName;
	soundHide.eventName = _uIFlashLayout.soundHide.eventName;
	soundActivate.projectName = _uIFlashLayout.soundActivate.projectName;
	soundActivate.groupName = _uIFlashLayout.soundActivate.groupName;
	soundActivate.eventName = _uIFlashLayout.soundActivate.eventName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UIFlashLayout2::UIFlashLayout2()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UIFlashLayout2::operator&( IBinSaver &saver )
{
	saver.Add( 1, (UIFlashLayout*)this );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UIFlashLayout2::operator&( IXmlSaver &saver )
{
	bool inheritedStates = false;
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			UIFlashLayout2* parentPtr = (UIFlashLayout2*)__parent.GetPtr();
			Assign( *parentPtr );
			StateSerializeHelper< UIFlashLayout2 > parentStateCopier( this, stateManager.states, &UIFlashLayout2::NewUIFlashLayout2 );
			parentStateCopier.InheritStates( parentPtr, parentPtr->GetStatesManager()->states, saver );
			inheritedStates = true;
		}
	}

	SerializeSelf( saver );
	if ( !inheritedStates )
	{
		StateSerializeHelper< UIFlashLayout2 > reader( this, stateManager.states, &UIFlashLayout2::NewUIFlashLayout2 );
		saver.AddPolymorphicBase( "__states", &reader );
	}
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UIFlashLayout2::SerializeSelf( IXmlSaver &saver )
{
	UIFlashLayout::SerializeSelf( saver );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool UIFlashLayout2::IsEqual( const UIFlashLayout2& _uIFlashLayout2 ) const
{
	return srcFileName == _uIFlashLayout2.srcFileName
		&& useScissorTest == _uIFlashLayout2.useScissorTest
		&& useOwnSize == _uIFlashLayout2.useOwnSize
		&& triangulationError == _uIFlashLayout2.triangulationError
		&& properties == _uIFlashLayout2.properties
		&& name == _uIFlashLayout2.name
		&& visible == _uIFlashLayout2.visible
		&& enabled == _uIFlashLayout2.enabled
		&& location.x == _uIFlashLayout2.location.x
		&& location.y == _uIFlashLayout2.location.y
		&& size.x == _uIFlashLayout2.size.x
		&& size.y == _uIFlashLayout2.size.y
		&& hAlign == _uIFlashLayout2.hAlign
		&& vAlign == _uIFlashLayout2.vAlign
		&& keepAspectRatio == _uIFlashLayout2.keepAspectRatio
		&& subclass == _uIFlashLayout2.subclass
		&& scriptFile == _uIFlashLayout2.scriptFile
		&& cursors.normal == _uIFlashLayout2.cursors.normal
		&& cursors.dragging == _uIFlashLayout2.cursors.dragging
		&& cursors.dragable == _uIFlashLayout2.cursors.dragable
		&& cursors.focused == _uIFlashLayout2.cursors.focused
		&& cursors.disabled == _uIFlashLayout2.cursors.disabled
		&& cursors.pushing == _uIFlashLayout2.cursors.pushing
		&& cursors.pushable == _uIFlashLayout2.cursors.pushable
		&& subLayouts == _uIFlashLayout2.subLayouts
		&& draggable == _uIFlashLayout2.draggable
		&& defaultEventsCatch.mouseMove == _uIFlashLayout2.defaultEventsCatch.mouseMove
		&& defaultEventsCatch.leftMouseDown == _uIFlashLayout2.defaultEventsCatch.leftMouseDown
		&& defaultEventsCatch.rightMouseDown == _uIFlashLayout2.defaultEventsCatch.rightMouseDown
		&& defaultEventsCatch.leftMouseUp == _uIFlashLayout2.defaultEventsCatch.leftMouseUp
		&& defaultEventsCatch.rightMouseUp == _uIFlashLayout2.defaultEventsCatch.rightMouseUp
		&& defaultEventsCatch.leftDoubleClick == _uIFlashLayout2.defaultEventsCatch.leftDoubleClick
		&& defaultEventsCatch.rightDoubleClick == _uIFlashLayout2.defaultEventsCatch.rightDoubleClick
		&& transparent == _uIFlashLayout2.transparent
		&& cursorTransparent == _uIFlashLayout2.cursorTransparent
		&& needCrop == _uIFlashLayout2.needCrop
		&& relatedLayouts == _uIFlashLayout2.relatedLayouts
		&& relatedTexts == _uIFlashLayout2.relatedTexts
		&& tooltipText == _uIFlashLayout2.tooltipText
		&& soundShow.projectName == _uIFlashLayout2.soundShow.projectName
		&& soundShow.groupName == _uIFlashLayout2.soundShow.groupName
		&& soundShow.eventName == _uIFlashLayout2.soundShow.eventName
		&& soundHide.projectName == _uIFlashLayout2.soundHide.projectName
		&& soundHide.groupName == _uIFlashLayout2.soundHide.groupName
		&& soundHide.eventName == _uIFlashLayout2.soundHide.eventName
		&& soundActivate.projectName == _uIFlashLayout2.soundActivate.projectName
		&& soundActivate.groupName == _uIFlashLayout2.soundActivate.groupName
		&& soundActivate.eventName == _uIFlashLayout2.soundActivate.eventName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UIFlashLayout2::Assign( const UIFlashLayout2& _uIFlashLayout2 )
{
	srcFileName = _uIFlashLayout2.srcFileName;
	useScissorTest = _uIFlashLayout2.useScissorTest;
	useOwnSize = _uIFlashLayout2.useOwnSize;
	triangulationError = _uIFlashLayout2.triangulationError;
	properties = _uIFlashLayout2.properties;
	name = _uIFlashLayout2.name;
	visible = _uIFlashLayout2.visible;
	enabled = _uIFlashLayout2.enabled;
	location = _uIFlashLayout2.location;
	size = _uIFlashLayout2.size;
	hAlign = _uIFlashLayout2.hAlign;
	vAlign = _uIFlashLayout2.vAlign;
	keepAspectRatio = _uIFlashLayout2.keepAspectRatio;
	subclass = _uIFlashLayout2.subclass;
	scriptFile = _uIFlashLayout2.scriptFile;
	cursors.normal = _uIFlashLayout2.cursors.normal;
	cursors.dragging = _uIFlashLayout2.cursors.dragging;
	cursors.dragable = _uIFlashLayout2.cursors.dragable;
	cursors.focused = _uIFlashLayout2.cursors.focused;
	cursors.disabled = _uIFlashLayout2.cursors.disabled;
	cursors.pushing = _uIFlashLayout2.cursors.pushing;
	cursors.pushable = _uIFlashLayout2.cursors.pushable;
	subLayouts = _uIFlashLayout2.subLayouts;
	draggable = _uIFlashLayout2.draggable;
	defaultEventsCatch.mouseMove = _uIFlashLayout2.defaultEventsCatch.mouseMove;
	defaultEventsCatch.leftMouseDown = _uIFlashLayout2.defaultEventsCatch.leftMouseDown;
	defaultEventsCatch.rightMouseDown = _uIFlashLayout2.defaultEventsCatch.rightMouseDown;
	defaultEventsCatch.leftMouseUp = _uIFlashLayout2.defaultEventsCatch.leftMouseUp;
	defaultEventsCatch.rightMouseUp = _uIFlashLayout2.defaultEventsCatch.rightMouseUp;
	defaultEventsCatch.leftDoubleClick = _uIFlashLayout2.defaultEventsCatch.leftDoubleClick;
	defaultEventsCatch.rightDoubleClick = _uIFlashLayout2.defaultEventsCatch.rightDoubleClick;
	transparent = _uIFlashLayout2.transparent;
	cursorTransparent = _uIFlashLayout2.cursorTransparent;
	needCrop = _uIFlashLayout2.needCrop;
	relatedLayouts = _uIFlashLayout2.relatedLayouts;
	relatedTexts = _uIFlashLayout2.relatedTexts;
	tooltipText = _uIFlashLayout2.tooltipText;
	soundShow.projectName = _uIFlashLayout2.soundShow.projectName;
	soundShow.groupName = _uIFlashLayout2.soundShow.groupName;
	soundShow.eventName = _uIFlashLayout2.soundShow.eventName;
	soundHide.projectName = _uIFlashLayout2.soundHide.projectName;
	soundHide.groupName = _uIFlashLayout2.soundHide.groupName;
	soundHide.eventName = _uIFlashLayout2.soundHide.eventName;
	soundActivate.projectName = _uIFlashLayout2.soundActivate.projectName;
	soundActivate.groupName = _uIFlashLayout2.soundActivate.groupName;
	soundActivate.eventName = _uIFlashLayout2.soundActivate.eventName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UIFontStyle::UIFontStyle() :
		drawContour( false )
	, fontSize( 0 )
	, lineGap( 0 )
	, additionalAdvance( 0.0f )
	, spaceScale( 1.0f )
	, bold( false )
	, italic( false )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UIFontStyle::operator&( IBinSaver &saver )
{
	saver.Add( 2, &styleName );
	saver.Add( 3, &drawContour );
	saver.Add( 4, &primaryColor );
	saver.Add( 5, &secondaryColor );
	saver.Add( 6, &renderState );
	saver.Add( 7, &ttfFileName );
	saver.Add( 8, &fontFamily );
	saver.Add( 9, &fontSize );
	saver.Add( 10, &lineGap );
	saver.Add( 11, &additionalAdvance );
	saver.Add( 12, &spaceScale );
	saver.Add( 13, &bold );
	saver.Add( 14, &italic );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UIFontStyle::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			UIFontStyle* parentPtr = (UIFontStyle*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UIFontStyle::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "styleName", &styleName );
	saver.Add( "drawContour", &drawContour );
	saver.Add( "primaryColor", &primaryColor );
	saver.Add( "secondaryColor", &secondaryColor );
	saver.Add( "renderState", &renderState );
	saver.Add( "ttfFileName", &ttfFileName );
	saver.Add( "fontFamily", &fontFamily );
	saver.Add( "fontSize", &fontSize );
	saver.Add( "lineGap", &lineGap );
	saver.Add( "additionalAdvance", &additionalAdvance );
	saver.Add( "spaceScale", &spaceScale );
	saver.Add( "bold", &bold );
	saver.Add( "italic", &italic );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UIFontStyle::Assign( const UIFontStyle& _uIFontStyle )
{
	styleName = _uIFontStyle.styleName;
	drawContour = _uIFontStyle.drawContour;
	primaryColor = _uIFontStyle.primaryColor;
	secondaryColor = _uIFontStyle.secondaryColor;
	renderState.blendMode = _uIFontStyle.renderState.blendMode;
	renderState.alphaTest = _uIFontStyle.renderState.alphaTest;
	renderState.alphaTestRef = _uIFontStyle.renderState.alphaTestRef;
	renderState.culling = _uIFontStyle.renderState.culling;
	ttfFileName = _uIFontStyle.ttfFileName;
	fontFamily = _uIFontStyle.fontFamily;
	fontSize = _uIFontStyle.fontSize;
	lineGap = _uIFontStyle.lineGap;
	additionalAdvance = _uIFontStyle.additionalAdvance;
	spaceScale = _uIFontStyle.spaceScale;
	bold = _uIFontStyle.bold;
	italic = _uIFontStyle.italic;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UIHealthBarLayout::UIHealthBarLayout() :
		showShield( false )
	, showStripes( false )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UIHealthBarLayout::operator&( IBinSaver &saver )
{
	saver.Add( 1, (UIImageLabelLayout*)this );
	saver.Add( 2, &healthMaterial );
	saver.Add( 3, &shieldMaterial );
	saver.Add( 4, &showShield );
	saver.Add( 5, &showStripes );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UIHealthBarLayout::operator&( IXmlSaver &saver )
{
	bool inheritedStates = false;
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			UIHealthBarLayout* parentPtr = (UIHealthBarLayout*)__parent.GetPtr();
			Assign( *parentPtr );
			StateSerializeHelper< UIHealthBarLayout > parentStateCopier( this, stateManager.states, &UIHealthBarLayout::NewUIHealthBarLayout );
			parentStateCopier.InheritStates( parentPtr, parentPtr->GetStatesManager()->states, saver );
			inheritedStates = true;
		}
	}

	SerializeSelf( saver );
	if ( !inheritedStates )
	{
		StateSerializeHelper< UIHealthBarLayout > reader( this, stateManager.states, &UIHealthBarLayout::NewUIHealthBarLayout );
		saver.AddPolymorphicBase( "__states", &reader );
	}
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UIHealthBarLayout::SerializeSelf( IXmlSaver &saver )
{
	UIImageLabelLayout::SerializeSelf( saver );
	saver.Add( "healthMaterial", &healthMaterial );
	saver.Add( "shieldMaterial", &shieldMaterial );
	saver.Add( "showShield", &showShield );
	saver.Add( "showStripes", &showStripes );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool UIHealthBarLayout::IsEqual( const UIHealthBarLayout& _uIHealthBarLayout ) const
{
	return healthMaterial == _uIHealthBarLayout.healthMaterial
		&& shieldMaterial == _uIHealthBarLayout.shieldMaterial
		&& showShield == _uIHealthBarLayout.showShield
		&& showStripes == _uIHealthBarLayout.showStripes
		&& backgroundMaterial == _uIHealthBarLayout.backgroundMaterial
		&& shapeType == _uIHealthBarLayout.shapeType
		&& captionText == _uIHealthBarLayout.captionText
		&& fontStyle == _uIHealthBarLayout.fontStyle
		&& wordWrap == _uIHealthBarLayout.wordWrap
		&& stretchText == _uIHealthBarLayout.stretchText
		&& rawTextMode == _uIHealthBarLayout.rawTextMode
		&& textVAlign == _uIHealthBarLayout.textVAlign
		&& textHAlign == _uIHealthBarLayout.textHAlign
		&& textMargins.x1 == _uIHealthBarLayout.textMargins.x1
		&& textMargins.y1 == _uIHealthBarLayout.textMargins.y1
		&& textMargins.x2 == _uIHealthBarLayout.textMargins.x2
		&& textMargins.y2 == _uIHealthBarLayout.textMargins.y2
		&& captionOpacity == _uIHealthBarLayout.captionOpacity
		&& name == _uIHealthBarLayout.name
		&& visible == _uIHealthBarLayout.visible
		&& enabled == _uIHealthBarLayout.enabled
		&& location.x == _uIHealthBarLayout.location.x
		&& location.y == _uIHealthBarLayout.location.y
		&& size.x == _uIHealthBarLayout.size.x
		&& size.y == _uIHealthBarLayout.size.y
		&& hAlign == _uIHealthBarLayout.hAlign
		&& vAlign == _uIHealthBarLayout.vAlign
		&& keepAspectRatio == _uIHealthBarLayout.keepAspectRatio
		&& subclass == _uIHealthBarLayout.subclass
		&& scriptFile == _uIHealthBarLayout.scriptFile
		&& cursors.normal == _uIHealthBarLayout.cursors.normal
		&& cursors.dragging == _uIHealthBarLayout.cursors.dragging
		&& cursors.dragable == _uIHealthBarLayout.cursors.dragable
		&& cursors.focused == _uIHealthBarLayout.cursors.focused
		&& cursors.disabled == _uIHealthBarLayout.cursors.disabled
		&& cursors.pushing == _uIHealthBarLayout.cursors.pushing
		&& cursors.pushable == _uIHealthBarLayout.cursors.pushable
		&& subLayouts == _uIHealthBarLayout.subLayouts
		&& draggable == _uIHealthBarLayout.draggable
		&& defaultEventsCatch.mouseMove == _uIHealthBarLayout.defaultEventsCatch.mouseMove
		&& defaultEventsCatch.leftMouseDown == _uIHealthBarLayout.defaultEventsCatch.leftMouseDown
		&& defaultEventsCatch.rightMouseDown == _uIHealthBarLayout.defaultEventsCatch.rightMouseDown
		&& defaultEventsCatch.leftMouseUp == _uIHealthBarLayout.defaultEventsCatch.leftMouseUp
		&& defaultEventsCatch.rightMouseUp == _uIHealthBarLayout.defaultEventsCatch.rightMouseUp
		&& defaultEventsCatch.leftDoubleClick == _uIHealthBarLayout.defaultEventsCatch.leftDoubleClick
		&& defaultEventsCatch.rightDoubleClick == _uIHealthBarLayout.defaultEventsCatch.rightDoubleClick
		&& transparent == _uIHealthBarLayout.transparent
		&& cursorTransparent == _uIHealthBarLayout.cursorTransparent
		&& needCrop == _uIHealthBarLayout.needCrop
		&& relatedLayouts == _uIHealthBarLayout.relatedLayouts
		&& relatedTexts == _uIHealthBarLayout.relatedTexts
		&& tooltipText == _uIHealthBarLayout.tooltipText
		&& soundShow.projectName == _uIHealthBarLayout.soundShow.projectName
		&& soundShow.groupName == _uIHealthBarLayout.soundShow.groupName
		&& soundShow.eventName == _uIHealthBarLayout.soundShow.eventName
		&& soundHide.projectName == _uIHealthBarLayout.soundHide.projectName
		&& soundHide.groupName == _uIHealthBarLayout.soundHide.groupName
		&& soundHide.eventName == _uIHealthBarLayout.soundHide.eventName
		&& soundActivate.projectName == _uIHealthBarLayout.soundActivate.projectName
		&& soundActivate.groupName == _uIHealthBarLayout.soundActivate.groupName
		&& soundActivate.eventName == _uIHealthBarLayout.soundActivate.eventName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UIHealthBarLayout::Assign( const UIHealthBarLayout& _uIHealthBarLayout )
{
	healthMaterial = _uIHealthBarLayout.healthMaterial;
	shieldMaterial = _uIHealthBarLayout.shieldMaterial;
	showShield = _uIHealthBarLayout.showShield;
	showStripes = _uIHealthBarLayout.showStripes;
	backgroundMaterial = _uIHealthBarLayout.backgroundMaterial;
	shapeType = _uIHealthBarLayout.shapeType;
	captionText = _uIHealthBarLayout.captionText;
	fontStyle = _uIHealthBarLayout.fontStyle;
	wordWrap = _uIHealthBarLayout.wordWrap;
	stretchText = _uIHealthBarLayout.stretchText;
	rawTextMode = _uIHealthBarLayout.rawTextMode;
	textVAlign = _uIHealthBarLayout.textVAlign;
	textHAlign = _uIHealthBarLayout.textHAlign;
	textMargins = _uIHealthBarLayout.textMargins;
	captionOpacity = _uIHealthBarLayout.captionOpacity;
	name = _uIHealthBarLayout.name;
	visible = _uIHealthBarLayout.visible;
	enabled = _uIHealthBarLayout.enabled;
	location = _uIHealthBarLayout.location;
	size = _uIHealthBarLayout.size;
	hAlign = _uIHealthBarLayout.hAlign;
	vAlign = _uIHealthBarLayout.vAlign;
	keepAspectRatio = _uIHealthBarLayout.keepAspectRatio;
	subclass = _uIHealthBarLayout.subclass;
	scriptFile = _uIHealthBarLayout.scriptFile;
	cursors.normal = _uIHealthBarLayout.cursors.normal;
	cursors.dragging = _uIHealthBarLayout.cursors.dragging;
	cursors.dragable = _uIHealthBarLayout.cursors.dragable;
	cursors.focused = _uIHealthBarLayout.cursors.focused;
	cursors.disabled = _uIHealthBarLayout.cursors.disabled;
	cursors.pushing = _uIHealthBarLayout.cursors.pushing;
	cursors.pushable = _uIHealthBarLayout.cursors.pushable;
	subLayouts = _uIHealthBarLayout.subLayouts;
	draggable = _uIHealthBarLayout.draggable;
	defaultEventsCatch.mouseMove = _uIHealthBarLayout.defaultEventsCatch.mouseMove;
	defaultEventsCatch.leftMouseDown = _uIHealthBarLayout.defaultEventsCatch.leftMouseDown;
	defaultEventsCatch.rightMouseDown = _uIHealthBarLayout.defaultEventsCatch.rightMouseDown;
	defaultEventsCatch.leftMouseUp = _uIHealthBarLayout.defaultEventsCatch.leftMouseUp;
	defaultEventsCatch.rightMouseUp = _uIHealthBarLayout.defaultEventsCatch.rightMouseUp;
	defaultEventsCatch.leftDoubleClick = _uIHealthBarLayout.defaultEventsCatch.leftDoubleClick;
	defaultEventsCatch.rightDoubleClick = _uIHealthBarLayout.defaultEventsCatch.rightDoubleClick;
	transparent = _uIHealthBarLayout.transparent;
	cursorTransparent = _uIHealthBarLayout.cursorTransparent;
	needCrop = _uIHealthBarLayout.needCrop;
	relatedLayouts = _uIHealthBarLayout.relatedLayouts;
	relatedTexts = _uIHealthBarLayout.relatedTexts;
	tooltipText = _uIHealthBarLayout.tooltipText;
	soundShow.projectName = _uIHealthBarLayout.soundShow.projectName;
	soundShow.groupName = _uIHealthBarLayout.soundShow.groupName;
	soundShow.eventName = _uIHealthBarLayout.soundShow.eventName;
	soundHide.projectName = _uIHealthBarLayout.soundHide.projectName;
	soundHide.groupName = _uIHealthBarLayout.soundHide.groupName;
	soundHide.eventName = _uIHealthBarLayout.soundHide.eventName;
	soundActivate.projectName = _uIHealthBarLayout.soundActivate.projectName;
	soundActivate.groupName = _uIHealthBarLayout.soundActivate.groupName;
	soundActivate.eventName = _uIHealthBarLayout.soundActivate.eventName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UICheckBoxLayout::UICheckBoxLayout()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UICheckBoxLayout::operator&( IBinSaver &saver )
{
	saver.Add( 1, (UICommonControl*)this );
	saver.Add( 2, &highlightMaterial );
	saver.Add( 3, &checkedMaterial );
	saver.Add( 4, &highlightCheckedMaterial );
	saver.Add( 5, &disabledMaterial );
	saver.Add( 6, &disabledCheckedMaterial );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UICheckBoxLayout::operator&( IXmlSaver &saver )
{
	bool inheritedStates = false;
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			UICheckBoxLayout* parentPtr = (UICheckBoxLayout*)__parent.GetPtr();
			Assign( *parentPtr );
			StateSerializeHelper< UICheckBoxLayout > parentStateCopier( this, stateManager.states, &UICheckBoxLayout::NewUICheckBoxLayout );
			parentStateCopier.InheritStates( parentPtr, parentPtr->GetStatesManager()->states, saver );
			inheritedStates = true;
		}
	}

	SerializeSelf( saver );
	if ( !inheritedStates )
	{
		StateSerializeHelper< UICheckBoxLayout > reader( this, stateManager.states, &UICheckBoxLayout::NewUICheckBoxLayout );
		saver.AddPolymorphicBase( "__states", &reader );
	}
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UICheckBoxLayout::SerializeSelf( IXmlSaver &saver )
{
	UICommonControl::SerializeSelf( saver );
	saver.Add( "highlightMaterial", &highlightMaterial );
	saver.Add( "checkedMaterial", &checkedMaterial );
	saver.Add( "highlightCheckedMaterial", &highlightCheckedMaterial );
	saver.Add( "disabledMaterial", &disabledMaterial );
	saver.Add( "disabledCheckedMaterial", &disabledCheckedMaterial );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool UICheckBoxLayout::IsEqual( const UICheckBoxLayout& _uICheckBoxLayout ) const
{
	return highlightMaterial == _uICheckBoxLayout.highlightMaterial
		&& checkedMaterial == _uICheckBoxLayout.checkedMaterial
		&& highlightCheckedMaterial == _uICheckBoxLayout.highlightCheckedMaterial
		&& disabledMaterial == _uICheckBoxLayout.disabledMaterial
		&& disabledCheckedMaterial == _uICheckBoxLayout.disabledCheckedMaterial
		&& mouseActions == _uICheckBoxLayout.mouseActions
		&& soundHilite.projectName == _uICheckBoxLayout.soundHilite.projectName
		&& soundHilite.groupName == _uICheckBoxLayout.soundHilite.groupName
		&& soundHilite.eventName == _uICheckBoxLayout.soundHilite.eventName
		&& activationBind == _uICheckBoxLayout.activationBind
		&& backgroundMaterial == _uICheckBoxLayout.backgroundMaterial
		&& shapeType == _uICheckBoxLayout.shapeType
		&& captionText == _uICheckBoxLayout.captionText
		&& fontStyle == _uICheckBoxLayout.fontStyle
		&& wordWrap == _uICheckBoxLayout.wordWrap
		&& stretchText == _uICheckBoxLayout.stretchText
		&& rawTextMode == _uICheckBoxLayout.rawTextMode
		&& textVAlign == _uICheckBoxLayout.textVAlign
		&& textHAlign == _uICheckBoxLayout.textHAlign
		&& textMargins.x1 == _uICheckBoxLayout.textMargins.x1
		&& textMargins.y1 == _uICheckBoxLayout.textMargins.y1
		&& textMargins.x2 == _uICheckBoxLayout.textMargins.x2
		&& textMargins.y2 == _uICheckBoxLayout.textMargins.y2
		&& captionOpacity == _uICheckBoxLayout.captionOpacity
		&& name == _uICheckBoxLayout.name
		&& visible == _uICheckBoxLayout.visible
		&& enabled == _uICheckBoxLayout.enabled
		&& location.x == _uICheckBoxLayout.location.x
		&& location.y == _uICheckBoxLayout.location.y
		&& size.x == _uICheckBoxLayout.size.x
		&& size.y == _uICheckBoxLayout.size.y
		&& hAlign == _uICheckBoxLayout.hAlign
		&& vAlign == _uICheckBoxLayout.vAlign
		&& keepAspectRatio == _uICheckBoxLayout.keepAspectRatio
		&& subclass == _uICheckBoxLayout.subclass
		&& scriptFile == _uICheckBoxLayout.scriptFile
		&& cursors.normal == _uICheckBoxLayout.cursors.normal
		&& cursors.dragging == _uICheckBoxLayout.cursors.dragging
		&& cursors.dragable == _uICheckBoxLayout.cursors.dragable
		&& cursors.focused == _uICheckBoxLayout.cursors.focused
		&& cursors.disabled == _uICheckBoxLayout.cursors.disabled
		&& cursors.pushing == _uICheckBoxLayout.cursors.pushing
		&& cursors.pushable == _uICheckBoxLayout.cursors.pushable
		&& subLayouts == _uICheckBoxLayout.subLayouts
		&& draggable == _uICheckBoxLayout.draggable
		&& defaultEventsCatch.mouseMove == _uICheckBoxLayout.defaultEventsCatch.mouseMove
		&& defaultEventsCatch.leftMouseDown == _uICheckBoxLayout.defaultEventsCatch.leftMouseDown
		&& defaultEventsCatch.rightMouseDown == _uICheckBoxLayout.defaultEventsCatch.rightMouseDown
		&& defaultEventsCatch.leftMouseUp == _uICheckBoxLayout.defaultEventsCatch.leftMouseUp
		&& defaultEventsCatch.rightMouseUp == _uICheckBoxLayout.defaultEventsCatch.rightMouseUp
		&& defaultEventsCatch.leftDoubleClick == _uICheckBoxLayout.defaultEventsCatch.leftDoubleClick
		&& defaultEventsCatch.rightDoubleClick == _uICheckBoxLayout.defaultEventsCatch.rightDoubleClick
		&& transparent == _uICheckBoxLayout.transparent
		&& cursorTransparent == _uICheckBoxLayout.cursorTransparent
		&& needCrop == _uICheckBoxLayout.needCrop
		&& relatedLayouts == _uICheckBoxLayout.relatedLayouts
		&& relatedTexts == _uICheckBoxLayout.relatedTexts
		&& tooltipText == _uICheckBoxLayout.tooltipText
		&& soundShow.projectName == _uICheckBoxLayout.soundShow.projectName
		&& soundShow.groupName == _uICheckBoxLayout.soundShow.groupName
		&& soundShow.eventName == _uICheckBoxLayout.soundShow.eventName
		&& soundHide.projectName == _uICheckBoxLayout.soundHide.projectName
		&& soundHide.groupName == _uICheckBoxLayout.soundHide.groupName
		&& soundHide.eventName == _uICheckBoxLayout.soundHide.eventName
		&& soundActivate.projectName == _uICheckBoxLayout.soundActivate.projectName
		&& soundActivate.groupName == _uICheckBoxLayout.soundActivate.groupName
		&& soundActivate.eventName == _uICheckBoxLayout.soundActivate.eventName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UICheckBoxLayout::Assign( const UICheckBoxLayout& _uICheckBoxLayout )
{
	highlightMaterial = _uICheckBoxLayout.highlightMaterial;
	checkedMaterial = _uICheckBoxLayout.checkedMaterial;
	highlightCheckedMaterial = _uICheckBoxLayout.highlightCheckedMaterial;
	disabledMaterial = _uICheckBoxLayout.disabledMaterial;
	disabledCheckedMaterial = _uICheckBoxLayout.disabledCheckedMaterial;
	mouseActions = _uICheckBoxLayout.mouseActions;
	soundHilite.projectName = _uICheckBoxLayout.soundHilite.projectName;
	soundHilite.groupName = _uICheckBoxLayout.soundHilite.groupName;
	soundHilite.eventName = _uICheckBoxLayout.soundHilite.eventName;
	activationBind = _uICheckBoxLayout.activationBind;
	backgroundMaterial = _uICheckBoxLayout.backgroundMaterial;
	shapeType = _uICheckBoxLayout.shapeType;
	captionText = _uICheckBoxLayout.captionText;
	fontStyle = _uICheckBoxLayout.fontStyle;
	wordWrap = _uICheckBoxLayout.wordWrap;
	stretchText = _uICheckBoxLayout.stretchText;
	rawTextMode = _uICheckBoxLayout.rawTextMode;
	textVAlign = _uICheckBoxLayout.textVAlign;
	textHAlign = _uICheckBoxLayout.textHAlign;
	textMargins = _uICheckBoxLayout.textMargins;
	captionOpacity = _uICheckBoxLayout.captionOpacity;
	name = _uICheckBoxLayout.name;
	visible = _uICheckBoxLayout.visible;
	enabled = _uICheckBoxLayout.enabled;
	location = _uICheckBoxLayout.location;
	size = _uICheckBoxLayout.size;
	hAlign = _uICheckBoxLayout.hAlign;
	vAlign = _uICheckBoxLayout.vAlign;
	keepAspectRatio = _uICheckBoxLayout.keepAspectRatio;
	subclass = _uICheckBoxLayout.subclass;
	scriptFile = _uICheckBoxLayout.scriptFile;
	cursors.normal = _uICheckBoxLayout.cursors.normal;
	cursors.dragging = _uICheckBoxLayout.cursors.dragging;
	cursors.dragable = _uICheckBoxLayout.cursors.dragable;
	cursors.focused = _uICheckBoxLayout.cursors.focused;
	cursors.disabled = _uICheckBoxLayout.cursors.disabled;
	cursors.pushing = _uICheckBoxLayout.cursors.pushing;
	cursors.pushable = _uICheckBoxLayout.cursors.pushable;
	subLayouts = _uICheckBoxLayout.subLayouts;
	draggable = _uICheckBoxLayout.draggable;
	defaultEventsCatch.mouseMove = _uICheckBoxLayout.defaultEventsCatch.mouseMove;
	defaultEventsCatch.leftMouseDown = _uICheckBoxLayout.defaultEventsCatch.leftMouseDown;
	defaultEventsCatch.rightMouseDown = _uICheckBoxLayout.defaultEventsCatch.rightMouseDown;
	defaultEventsCatch.leftMouseUp = _uICheckBoxLayout.defaultEventsCatch.leftMouseUp;
	defaultEventsCatch.rightMouseUp = _uICheckBoxLayout.defaultEventsCatch.rightMouseUp;
	defaultEventsCatch.leftDoubleClick = _uICheckBoxLayout.defaultEventsCatch.leftDoubleClick;
	defaultEventsCatch.rightDoubleClick = _uICheckBoxLayout.defaultEventsCatch.rightDoubleClick;
	transparent = _uICheckBoxLayout.transparent;
	cursorTransparent = _uICheckBoxLayout.cursorTransparent;
	needCrop = _uICheckBoxLayout.needCrop;
	relatedLayouts = _uICheckBoxLayout.relatedLayouts;
	relatedTexts = _uICheckBoxLayout.relatedTexts;
	tooltipText = _uICheckBoxLayout.tooltipText;
	soundShow.projectName = _uICheckBoxLayout.soundShow.projectName;
	soundShow.groupName = _uICheckBoxLayout.soundShow.groupName;
	soundShow.eventName = _uICheckBoxLayout.soundShow.eventName;
	soundHide.projectName = _uICheckBoxLayout.soundHide.projectName;
	soundHide.groupName = _uICheckBoxLayout.soundHide.groupName;
	soundHide.eventName = _uICheckBoxLayout.soundHide.eventName;
	soundActivate.projectName = _uICheckBoxLayout.soundActivate.projectName;
	soundActivate.groupName = _uICheckBoxLayout.soundActivate.groupName;
	soundActivate.eventName = _uICheckBoxLayout.soundActivate.eventName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UIBaseLayout::UIBaseLayout()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UIBaseLayout::operator&( IBinSaver &saver )
{
	saver.Add( 1, (UILayout*)this );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UIBaseLayout::operator&( IXmlSaver &saver )
{
	bool inheritedStates = false;
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			UIBaseLayout* parentPtr = (UIBaseLayout*)__parent.GetPtr();
			Assign( *parentPtr );
			StateSerializeHelper< UIBaseLayout > parentStateCopier( this, stateManager.states, &UIBaseLayout::NewUIBaseLayout );
			parentStateCopier.InheritStates( parentPtr, parentPtr->GetStatesManager()->states, saver );
			inheritedStates = true;
		}
	}

	SerializeSelf( saver );
	if ( !inheritedStates )
	{
		StateSerializeHelper< UIBaseLayout > reader( this, stateManager.states, &UIBaseLayout::NewUIBaseLayout );
		saver.AddPolymorphicBase( "__states", &reader );
	}
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UIBaseLayout::SerializeSelf( IXmlSaver &saver )
{
	UILayout::SerializeSelf( saver );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool UIBaseLayout::IsEqual( const UIBaseLayout& _uIBaseLayout ) const
{
	return name == _uIBaseLayout.name
		&& visible == _uIBaseLayout.visible
		&& enabled == _uIBaseLayout.enabled
		&& location.x == _uIBaseLayout.location.x
		&& location.y == _uIBaseLayout.location.y
		&& size.x == _uIBaseLayout.size.x
		&& size.y == _uIBaseLayout.size.y
		&& hAlign == _uIBaseLayout.hAlign
		&& vAlign == _uIBaseLayout.vAlign
		&& keepAspectRatio == _uIBaseLayout.keepAspectRatio
		&& subclass == _uIBaseLayout.subclass
		&& scriptFile == _uIBaseLayout.scriptFile
		&& cursors.normal == _uIBaseLayout.cursors.normal
		&& cursors.dragging == _uIBaseLayout.cursors.dragging
		&& cursors.dragable == _uIBaseLayout.cursors.dragable
		&& cursors.focused == _uIBaseLayout.cursors.focused
		&& cursors.disabled == _uIBaseLayout.cursors.disabled
		&& cursors.pushing == _uIBaseLayout.cursors.pushing
		&& cursors.pushable == _uIBaseLayout.cursors.pushable
		&& subLayouts == _uIBaseLayout.subLayouts
		&& draggable == _uIBaseLayout.draggable
		&& defaultEventsCatch.mouseMove == _uIBaseLayout.defaultEventsCatch.mouseMove
		&& defaultEventsCatch.leftMouseDown == _uIBaseLayout.defaultEventsCatch.leftMouseDown
		&& defaultEventsCatch.rightMouseDown == _uIBaseLayout.defaultEventsCatch.rightMouseDown
		&& defaultEventsCatch.leftMouseUp == _uIBaseLayout.defaultEventsCatch.leftMouseUp
		&& defaultEventsCatch.rightMouseUp == _uIBaseLayout.defaultEventsCatch.rightMouseUp
		&& defaultEventsCatch.leftDoubleClick == _uIBaseLayout.defaultEventsCatch.leftDoubleClick
		&& defaultEventsCatch.rightDoubleClick == _uIBaseLayout.defaultEventsCatch.rightDoubleClick
		&& transparent == _uIBaseLayout.transparent
		&& cursorTransparent == _uIBaseLayout.cursorTransparent
		&& needCrop == _uIBaseLayout.needCrop
		&& relatedLayouts == _uIBaseLayout.relatedLayouts
		&& relatedTexts == _uIBaseLayout.relatedTexts
		&& tooltipText == _uIBaseLayout.tooltipText
		&& soundShow.projectName == _uIBaseLayout.soundShow.projectName
		&& soundShow.groupName == _uIBaseLayout.soundShow.groupName
		&& soundShow.eventName == _uIBaseLayout.soundShow.eventName
		&& soundHide.projectName == _uIBaseLayout.soundHide.projectName
		&& soundHide.groupName == _uIBaseLayout.soundHide.groupName
		&& soundHide.eventName == _uIBaseLayout.soundHide.eventName
		&& soundActivate.projectName == _uIBaseLayout.soundActivate.projectName
		&& soundActivate.groupName == _uIBaseLayout.soundActivate.groupName
		&& soundActivate.eventName == _uIBaseLayout.soundActivate.eventName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UIBaseLayout::Assign( const UIBaseLayout& _uIBaseLayout )
{
	name = _uIBaseLayout.name;
	visible = _uIBaseLayout.visible;
	enabled = _uIBaseLayout.enabled;
	location = _uIBaseLayout.location;
	size = _uIBaseLayout.size;
	hAlign = _uIBaseLayout.hAlign;
	vAlign = _uIBaseLayout.vAlign;
	keepAspectRatio = _uIBaseLayout.keepAspectRatio;
	subclass = _uIBaseLayout.subclass;
	scriptFile = _uIBaseLayout.scriptFile;
	cursors.normal = _uIBaseLayout.cursors.normal;
	cursors.dragging = _uIBaseLayout.cursors.dragging;
	cursors.dragable = _uIBaseLayout.cursors.dragable;
	cursors.focused = _uIBaseLayout.cursors.focused;
	cursors.disabled = _uIBaseLayout.cursors.disabled;
	cursors.pushing = _uIBaseLayout.cursors.pushing;
	cursors.pushable = _uIBaseLayout.cursors.pushable;
	subLayouts = _uIBaseLayout.subLayouts;
	draggable = _uIBaseLayout.draggable;
	defaultEventsCatch.mouseMove = _uIBaseLayout.defaultEventsCatch.mouseMove;
	defaultEventsCatch.leftMouseDown = _uIBaseLayout.defaultEventsCatch.leftMouseDown;
	defaultEventsCatch.rightMouseDown = _uIBaseLayout.defaultEventsCatch.rightMouseDown;
	defaultEventsCatch.leftMouseUp = _uIBaseLayout.defaultEventsCatch.leftMouseUp;
	defaultEventsCatch.rightMouseUp = _uIBaseLayout.defaultEventsCatch.rightMouseUp;
	defaultEventsCatch.leftDoubleClick = _uIBaseLayout.defaultEventsCatch.leftDoubleClick;
	defaultEventsCatch.rightDoubleClick = _uIBaseLayout.defaultEventsCatch.rightDoubleClick;
	transparent = _uIBaseLayout.transparent;
	cursorTransparent = _uIBaseLayout.cursorTransparent;
	needCrop = _uIBaseLayout.needCrop;
	relatedLayouts = _uIBaseLayout.relatedLayouts;
	relatedTexts = _uIBaseLayout.relatedTexts;
	tooltipText = _uIBaseLayout.tooltipText;
	soundShow.projectName = _uIBaseLayout.soundShow.projectName;
	soundShow.groupName = _uIBaseLayout.soundShow.groupName;
	soundShow.eventName = _uIBaseLayout.soundShow.eventName;
	soundHide.projectName = _uIBaseLayout.soundHide.projectName;
	soundHide.groupName = _uIBaseLayout.soundHide.groupName;
	soundHide.eventName = _uIBaseLayout.soundHide.eventName;
	soundActivate.projectName = _uIBaseLayout.soundActivate.projectName;
	soundActivate.groupName = _uIBaseLayout.soundActivate.groupName;
	soundActivate.eventName = _uIBaseLayout.soundActivate.eventName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UIObjectOvertips::UIObjectOvertips()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UIObjectOvertips::operator&( IBinSaver &saver )
{
	saver.Add( 2, &plain );
	saver.Add( 3, &threeDimensional );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UIObjectOvertips::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			UIObjectOvertips* parentPtr = (UIObjectOvertips*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UIObjectOvertips::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "plain", &plain );
	saver.Add( "threeDimensional", &threeDimensional );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UIObjectOvertips::Assign( const UIObjectOvertips& _uIObjectOvertips )
{
	plain = _uIObjectOvertips.plain;
	threeDimensional = _uIObjectOvertips.threeDimensional;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UIPageTabControlLayout::UIPageTabControlLayout()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UIPageTabControlLayout::operator&( IBinSaver &saver )
{
	saver.Add( 1, (UIImageLabelLayout*)this );
	saver.Add( 2, &tabs );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UIPageTabControlLayout::operator&( IXmlSaver &saver )
{
	bool inheritedStates = false;
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			UIPageTabControlLayout* parentPtr = (UIPageTabControlLayout*)__parent.GetPtr();
			Assign( *parentPtr );
			StateSerializeHelper< UIPageTabControlLayout > parentStateCopier( this, stateManager.states, &UIPageTabControlLayout::NewUIPageTabControlLayout );
			parentStateCopier.InheritStates( parentPtr, parentPtr->GetStatesManager()->states, saver );
			inheritedStates = true;
		}
	}

	SerializeSelf( saver );
	if ( !inheritedStates )
	{
		StateSerializeHelper< UIPageTabControlLayout > reader( this, stateManager.states, &UIPageTabControlLayout::NewUIPageTabControlLayout );
		saver.AddPolymorphicBase( "__states", &reader );
	}
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UIPageTabControlLayout::SerializeSelf( IXmlSaver &saver )
{
	UIImageLabelLayout::SerializeSelf( saver );
	saver.Add( "tabs", &tabs );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool UIPageTabControlLayout::IsEqual( const UIPageTabControlLayout& _uIPageTabControlLayout ) const
{
	return tabs == _uIPageTabControlLayout.tabs
		&& backgroundMaterial == _uIPageTabControlLayout.backgroundMaterial
		&& shapeType == _uIPageTabControlLayout.shapeType
		&& captionText == _uIPageTabControlLayout.captionText
		&& fontStyle == _uIPageTabControlLayout.fontStyle
		&& wordWrap == _uIPageTabControlLayout.wordWrap
		&& stretchText == _uIPageTabControlLayout.stretchText
		&& rawTextMode == _uIPageTabControlLayout.rawTextMode
		&& textVAlign == _uIPageTabControlLayout.textVAlign
		&& textHAlign == _uIPageTabControlLayout.textHAlign
		&& textMargins.x1 == _uIPageTabControlLayout.textMargins.x1
		&& textMargins.y1 == _uIPageTabControlLayout.textMargins.y1
		&& textMargins.x2 == _uIPageTabControlLayout.textMargins.x2
		&& textMargins.y2 == _uIPageTabControlLayout.textMargins.y2
		&& captionOpacity == _uIPageTabControlLayout.captionOpacity
		&& name == _uIPageTabControlLayout.name
		&& visible == _uIPageTabControlLayout.visible
		&& enabled == _uIPageTabControlLayout.enabled
		&& location.x == _uIPageTabControlLayout.location.x
		&& location.y == _uIPageTabControlLayout.location.y
		&& size.x == _uIPageTabControlLayout.size.x
		&& size.y == _uIPageTabControlLayout.size.y
		&& hAlign == _uIPageTabControlLayout.hAlign
		&& vAlign == _uIPageTabControlLayout.vAlign
		&& keepAspectRatio == _uIPageTabControlLayout.keepAspectRatio
		&& subclass == _uIPageTabControlLayout.subclass
		&& scriptFile == _uIPageTabControlLayout.scriptFile
		&& cursors.normal == _uIPageTabControlLayout.cursors.normal
		&& cursors.dragging == _uIPageTabControlLayout.cursors.dragging
		&& cursors.dragable == _uIPageTabControlLayout.cursors.dragable
		&& cursors.focused == _uIPageTabControlLayout.cursors.focused
		&& cursors.disabled == _uIPageTabControlLayout.cursors.disabled
		&& cursors.pushing == _uIPageTabControlLayout.cursors.pushing
		&& cursors.pushable == _uIPageTabControlLayout.cursors.pushable
		&& subLayouts == _uIPageTabControlLayout.subLayouts
		&& draggable == _uIPageTabControlLayout.draggable
		&& defaultEventsCatch.mouseMove == _uIPageTabControlLayout.defaultEventsCatch.mouseMove
		&& defaultEventsCatch.leftMouseDown == _uIPageTabControlLayout.defaultEventsCatch.leftMouseDown
		&& defaultEventsCatch.rightMouseDown == _uIPageTabControlLayout.defaultEventsCatch.rightMouseDown
		&& defaultEventsCatch.leftMouseUp == _uIPageTabControlLayout.defaultEventsCatch.leftMouseUp
		&& defaultEventsCatch.rightMouseUp == _uIPageTabControlLayout.defaultEventsCatch.rightMouseUp
		&& defaultEventsCatch.leftDoubleClick == _uIPageTabControlLayout.defaultEventsCatch.leftDoubleClick
		&& defaultEventsCatch.rightDoubleClick == _uIPageTabControlLayout.defaultEventsCatch.rightDoubleClick
		&& transparent == _uIPageTabControlLayout.transparent
		&& cursorTransparent == _uIPageTabControlLayout.cursorTransparent
		&& needCrop == _uIPageTabControlLayout.needCrop
		&& relatedLayouts == _uIPageTabControlLayout.relatedLayouts
		&& relatedTexts == _uIPageTabControlLayout.relatedTexts
		&& tooltipText == _uIPageTabControlLayout.tooltipText
		&& soundShow.projectName == _uIPageTabControlLayout.soundShow.projectName
		&& soundShow.groupName == _uIPageTabControlLayout.soundShow.groupName
		&& soundShow.eventName == _uIPageTabControlLayout.soundShow.eventName
		&& soundHide.projectName == _uIPageTabControlLayout.soundHide.projectName
		&& soundHide.groupName == _uIPageTabControlLayout.soundHide.groupName
		&& soundHide.eventName == _uIPageTabControlLayout.soundHide.eventName
		&& soundActivate.projectName == _uIPageTabControlLayout.soundActivate.projectName
		&& soundActivate.groupName == _uIPageTabControlLayout.soundActivate.groupName
		&& soundActivate.eventName == _uIPageTabControlLayout.soundActivate.eventName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UIPageTabControlLayout::Assign( const UIPageTabControlLayout& _uIPageTabControlLayout )
{
	tabs = _uIPageTabControlLayout.tabs;
	backgroundMaterial = _uIPageTabControlLayout.backgroundMaterial;
	shapeType = _uIPageTabControlLayout.shapeType;
	captionText = _uIPageTabControlLayout.captionText;
	fontStyle = _uIPageTabControlLayout.fontStyle;
	wordWrap = _uIPageTabControlLayout.wordWrap;
	stretchText = _uIPageTabControlLayout.stretchText;
	rawTextMode = _uIPageTabControlLayout.rawTextMode;
	textVAlign = _uIPageTabControlLayout.textVAlign;
	textHAlign = _uIPageTabControlLayout.textHAlign;
	textMargins = _uIPageTabControlLayout.textMargins;
	captionOpacity = _uIPageTabControlLayout.captionOpacity;
	name = _uIPageTabControlLayout.name;
	visible = _uIPageTabControlLayout.visible;
	enabled = _uIPageTabControlLayout.enabled;
	location = _uIPageTabControlLayout.location;
	size = _uIPageTabControlLayout.size;
	hAlign = _uIPageTabControlLayout.hAlign;
	vAlign = _uIPageTabControlLayout.vAlign;
	keepAspectRatio = _uIPageTabControlLayout.keepAspectRatio;
	subclass = _uIPageTabControlLayout.subclass;
	scriptFile = _uIPageTabControlLayout.scriptFile;
	cursors.normal = _uIPageTabControlLayout.cursors.normal;
	cursors.dragging = _uIPageTabControlLayout.cursors.dragging;
	cursors.dragable = _uIPageTabControlLayout.cursors.dragable;
	cursors.focused = _uIPageTabControlLayout.cursors.focused;
	cursors.disabled = _uIPageTabControlLayout.cursors.disabled;
	cursors.pushing = _uIPageTabControlLayout.cursors.pushing;
	cursors.pushable = _uIPageTabControlLayout.cursors.pushable;
	subLayouts = _uIPageTabControlLayout.subLayouts;
	draggable = _uIPageTabControlLayout.draggable;
	defaultEventsCatch.mouseMove = _uIPageTabControlLayout.defaultEventsCatch.mouseMove;
	defaultEventsCatch.leftMouseDown = _uIPageTabControlLayout.defaultEventsCatch.leftMouseDown;
	defaultEventsCatch.rightMouseDown = _uIPageTabControlLayout.defaultEventsCatch.rightMouseDown;
	defaultEventsCatch.leftMouseUp = _uIPageTabControlLayout.defaultEventsCatch.leftMouseUp;
	defaultEventsCatch.rightMouseUp = _uIPageTabControlLayout.defaultEventsCatch.rightMouseUp;
	defaultEventsCatch.leftDoubleClick = _uIPageTabControlLayout.defaultEventsCatch.leftDoubleClick;
	defaultEventsCatch.rightDoubleClick = _uIPageTabControlLayout.defaultEventsCatch.rightDoubleClick;
	transparent = _uIPageTabControlLayout.transparent;
	cursorTransparent = _uIPageTabControlLayout.cursorTransparent;
	needCrop = _uIPageTabControlLayout.needCrop;
	relatedLayouts = _uIPageTabControlLayout.relatedLayouts;
	relatedTexts = _uIPageTabControlLayout.relatedTexts;
	tooltipText = _uIPageTabControlLayout.tooltipText;
	soundShow.projectName = _uIPageTabControlLayout.soundShow.projectName;
	soundShow.groupName = _uIPageTabControlLayout.soundShow.groupName;
	soundShow.eventName = _uIPageTabControlLayout.soundShow.eventName;
	soundHide.projectName = _uIPageTabControlLayout.soundHide.projectName;
	soundHide.groupName = _uIPageTabControlLayout.soundHide.groupName;
	soundHide.eventName = _uIPageTabControlLayout.soundHide.eventName;
	soundActivate.projectName = _uIPageTabControlLayout.soundActivate.projectName;
	soundActivate.groupName = _uIPageTabControlLayout.soundActivate.groupName;
	soundActivate.eventName = _uIPageTabControlLayout.soundActivate.eventName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UIProgressBarLayout::UIProgressBarLayout() :
		effectRotationType( UIROTATIONTYPE_CW )
	, progressBarType( UIPROGRESSBARTYPE_HORIZONTALSCALINGBAR )
	, maskGradientItems( 1 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UIProgressBarLayout::operator&( IBinSaver &saver )
{
	saver.Add( 1, (UIImageLabelLayout*)this );
	saver.Add( 2, &progressMaterial );
	saver.Add( 3, &rotationEffectMaterial );
	saver.Add( 4, &rotationEffectPivot );
	saver.Add( 5, &effectRotationType );
	saver.Add( 6, &progressBarType );
	saver.Add( 7, &maskGradientItems );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UIProgressBarLayout::operator&( IXmlSaver &saver )
{
	bool inheritedStates = false;
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			UIProgressBarLayout* parentPtr = (UIProgressBarLayout*)__parent.GetPtr();
			Assign( *parentPtr );
			StateSerializeHelper< UIProgressBarLayout > parentStateCopier( this, stateManager.states, &UIProgressBarLayout::NewUIProgressBarLayout );
			parentStateCopier.InheritStates( parentPtr, parentPtr->GetStatesManager()->states, saver );
			inheritedStates = true;
		}
	}

	SerializeSelf( saver );
	if ( !inheritedStates )
	{
		StateSerializeHelper< UIProgressBarLayout > reader( this, stateManager.states, &UIProgressBarLayout::NewUIProgressBarLayout );
		saver.AddPolymorphicBase( "__states", &reader );
	}
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UIProgressBarLayout::SerializeSelf( IXmlSaver &saver )
{
	UIImageLabelLayout::SerializeSelf( saver );
	saver.Add( "progressMaterial", &progressMaterial );
	saver.Add( "rotationEffectMaterial", &rotationEffectMaterial );
	saver.Add( "rotationEffectPivot", &rotationEffectPivot );
	saver.Add( "effectRotationType", &effectRotationType );
	saver.Add( "progressBarType", &progressBarType );
	saver.Add( "maskGradientItems", &maskGradientItems );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool UIProgressBarLayout::IsEqual( const UIProgressBarLayout& _uIProgressBarLayout ) const
{
	return progressMaterial == _uIProgressBarLayout.progressMaterial
		&& rotationEffectMaterial == _uIProgressBarLayout.rotationEffectMaterial
		&& rotationEffectPivot.x == _uIProgressBarLayout.rotationEffectPivot.x
		&& rotationEffectPivot.y == _uIProgressBarLayout.rotationEffectPivot.y
		&& effectRotationType == _uIProgressBarLayout.effectRotationType
		&& progressBarType == _uIProgressBarLayout.progressBarType
		&& maskGradientItems == _uIProgressBarLayout.maskGradientItems
		&& backgroundMaterial == _uIProgressBarLayout.backgroundMaterial
		&& shapeType == _uIProgressBarLayout.shapeType
		&& captionText == _uIProgressBarLayout.captionText
		&& fontStyle == _uIProgressBarLayout.fontStyle
		&& wordWrap == _uIProgressBarLayout.wordWrap
		&& stretchText == _uIProgressBarLayout.stretchText
		&& rawTextMode == _uIProgressBarLayout.rawTextMode
		&& textVAlign == _uIProgressBarLayout.textVAlign
		&& textHAlign == _uIProgressBarLayout.textHAlign
		&& textMargins.x1 == _uIProgressBarLayout.textMargins.x1
		&& textMargins.y1 == _uIProgressBarLayout.textMargins.y1
		&& textMargins.x2 == _uIProgressBarLayout.textMargins.x2
		&& textMargins.y2 == _uIProgressBarLayout.textMargins.y2
		&& captionOpacity == _uIProgressBarLayout.captionOpacity
		&& name == _uIProgressBarLayout.name
		&& visible == _uIProgressBarLayout.visible
		&& enabled == _uIProgressBarLayout.enabled
		&& location.x == _uIProgressBarLayout.location.x
		&& location.y == _uIProgressBarLayout.location.y
		&& size.x == _uIProgressBarLayout.size.x
		&& size.y == _uIProgressBarLayout.size.y
		&& hAlign == _uIProgressBarLayout.hAlign
		&& vAlign == _uIProgressBarLayout.vAlign
		&& keepAspectRatio == _uIProgressBarLayout.keepAspectRatio
		&& subclass == _uIProgressBarLayout.subclass
		&& scriptFile == _uIProgressBarLayout.scriptFile
		&& cursors.normal == _uIProgressBarLayout.cursors.normal
		&& cursors.dragging == _uIProgressBarLayout.cursors.dragging
		&& cursors.dragable == _uIProgressBarLayout.cursors.dragable
		&& cursors.focused == _uIProgressBarLayout.cursors.focused
		&& cursors.disabled == _uIProgressBarLayout.cursors.disabled
		&& cursors.pushing == _uIProgressBarLayout.cursors.pushing
		&& cursors.pushable == _uIProgressBarLayout.cursors.pushable
		&& subLayouts == _uIProgressBarLayout.subLayouts
		&& draggable == _uIProgressBarLayout.draggable
		&& defaultEventsCatch.mouseMove == _uIProgressBarLayout.defaultEventsCatch.mouseMove
		&& defaultEventsCatch.leftMouseDown == _uIProgressBarLayout.defaultEventsCatch.leftMouseDown
		&& defaultEventsCatch.rightMouseDown == _uIProgressBarLayout.defaultEventsCatch.rightMouseDown
		&& defaultEventsCatch.leftMouseUp == _uIProgressBarLayout.defaultEventsCatch.leftMouseUp
		&& defaultEventsCatch.rightMouseUp == _uIProgressBarLayout.defaultEventsCatch.rightMouseUp
		&& defaultEventsCatch.leftDoubleClick == _uIProgressBarLayout.defaultEventsCatch.leftDoubleClick
		&& defaultEventsCatch.rightDoubleClick == _uIProgressBarLayout.defaultEventsCatch.rightDoubleClick
		&& transparent == _uIProgressBarLayout.transparent
		&& cursorTransparent == _uIProgressBarLayout.cursorTransparent
		&& needCrop == _uIProgressBarLayout.needCrop
		&& relatedLayouts == _uIProgressBarLayout.relatedLayouts
		&& relatedTexts == _uIProgressBarLayout.relatedTexts
		&& tooltipText == _uIProgressBarLayout.tooltipText
		&& soundShow.projectName == _uIProgressBarLayout.soundShow.projectName
		&& soundShow.groupName == _uIProgressBarLayout.soundShow.groupName
		&& soundShow.eventName == _uIProgressBarLayout.soundShow.eventName
		&& soundHide.projectName == _uIProgressBarLayout.soundHide.projectName
		&& soundHide.groupName == _uIProgressBarLayout.soundHide.groupName
		&& soundHide.eventName == _uIProgressBarLayout.soundHide.eventName
		&& soundActivate.projectName == _uIProgressBarLayout.soundActivate.projectName
		&& soundActivate.groupName == _uIProgressBarLayout.soundActivate.groupName
		&& soundActivate.eventName == _uIProgressBarLayout.soundActivate.eventName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UIProgressBarLayout::Assign( const UIProgressBarLayout& _uIProgressBarLayout )
{
	progressMaterial = _uIProgressBarLayout.progressMaterial;
	rotationEffectMaterial = _uIProgressBarLayout.rotationEffectMaterial;
	rotationEffectPivot = _uIProgressBarLayout.rotationEffectPivot;
	effectRotationType = _uIProgressBarLayout.effectRotationType;
	progressBarType = _uIProgressBarLayout.progressBarType;
	maskGradientItems = _uIProgressBarLayout.maskGradientItems;
	backgroundMaterial = _uIProgressBarLayout.backgroundMaterial;
	shapeType = _uIProgressBarLayout.shapeType;
	captionText = _uIProgressBarLayout.captionText;
	fontStyle = _uIProgressBarLayout.fontStyle;
	wordWrap = _uIProgressBarLayout.wordWrap;
	stretchText = _uIProgressBarLayout.stretchText;
	rawTextMode = _uIProgressBarLayout.rawTextMode;
	textVAlign = _uIProgressBarLayout.textVAlign;
	textHAlign = _uIProgressBarLayout.textHAlign;
	textMargins = _uIProgressBarLayout.textMargins;
	captionOpacity = _uIProgressBarLayout.captionOpacity;
	name = _uIProgressBarLayout.name;
	visible = _uIProgressBarLayout.visible;
	enabled = _uIProgressBarLayout.enabled;
	location = _uIProgressBarLayout.location;
	size = _uIProgressBarLayout.size;
	hAlign = _uIProgressBarLayout.hAlign;
	vAlign = _uIProgressBarLayout.vAlign;
	keepAspectRatio = _uIProgressBarLayout.keepAspectRatio;
	subclass = _uIProgressBarLayout.subclass;
	scriptFile = _uIProgressBarLayout.scriptFile;
	cursors.normal = _uIProgressBarLayout.cursors.normal;
	cursors.dragging = _uIProgressBarLayout.cursors.dragging;
	cursors.dragable = _uIProgressBarLayout.cursors.dragable;
	cursors.focused = _uIProgressBarLayout.cursors.focused;
	cursors.disabled = _uIProgressBarLayout.cursors.disabled;
	cursors.pushing = _uIProgressBarLayout.cursors.pushing;
	cursors.pushable = _uIProgressBarLayout.cursors.pushable;
	subLayouts = _uIProgressBarLayout.subLayouts;
	draggable = _uIProgressBarLayout.draggable;
	defaultEventsCatch.mouseMove = _uIProgressBarLayout.defaultEventsCatch.mouseMove;
	defaultEventsCatch.leftMouseDown = _uIProgressBarLayout.defaultEventsCatch.leftMouseDown;
	defaultEventsCatch.rightMouseDown = _uIProgressBarLayout.defaultEventsCatch.rightMouseDown;
	defaultEventsCatch.leftMouseUp = _uIProgressBarLayout.defaultEventsCatch.leftMouseUp;
	defaultEventsCatch.rightMouseUp = _uIProgressBarLayout.defaultEventsCatch.rightMouseUp;
	defaultEventsCatch.leftDoubleClick = _uIProgressBarLayout.defaultEventsCatch.leftDoubleClick;
	defaultEventsCatch.rightDoubleClick = _uIProgressBarLayout.defaultEventsCatch.rightDoubleClick;
	transparent = _uIProgressBarLayout.transparent;
	cursorTransparent = _uIProgressBarLayout.cursorTransparent;
	needCrop = _uIProgressBarLayout.needCrop;
	relatedLayouts = _uIProgressBarLayout.relatedLayouts;
	relatedTexts = _uIProgressBarLayout.relatedTexts;
	tooltipText = _uIProgressBarLayout.tooltipText;
	soundShow.projectName = _uIProgressBarLayout.soundShow.projectName;
	soundShow.groupName = _uIProgressBarLayout.soundShow.groupName;
	soundShow.eventName = _uIProgressBarLayout.soundShow.eventName;
	soundHide.projectName = _uIProgressBarLayout.soundHide.projectName;
	soundHide.groupName = _uIProgressBarLayout.soundHide.groupName;
	soundHide.eventName = _uIProgressBarLayout.soundHide.eventName;
	soundActivate.projectName = _uIProgressBarLayout.soundActivate.projectName;
	soundActivate.groupName = _uIProgressBarLayout.soundActivate.groupName;
	soundActivate.eventName = _uIProgressBarLayout.soundActivate.eventName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UIRadioButtonLayout::UIRadioButtonLayout() :
		group( 0 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UIRadioButtonLayout::operator&( IBinSaver &saver )
{
	saver.Add( 1, (UICommonControl*)this );
	saver.Add( 2, &highlightMaterial );
	saver.Add( 3, &selectedMaterial );
	saver.Add( 4, &disabledMaterial );
	saver.Add( 5, &disabledSelectedMaterial );
	saver.Add( 6, &flashedMaterial );
	saver.Add( 7, &group );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UIRadioButtonLayout::operator&( IXmlSaver &saver )
{
	bool inheritedStates = false;
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			UIRadioButtonLayout* parentPtr = (UIRadioButtonLayout*)__parent.GetPtr();
			Assign( *parentPtr );
			StateSerializeHelper< UIRadioButtonLayout > parentStateCopier( this, stateManager.states, &UIRadioButtonLayout::NewUIRadioButtonLayout );
			parentStateCopier.InheritStates( parentPtr, parentPtr->GetStatesManager()->states, saver );
			inheritedStates = true;
		}
	}

	SerializeSelf( saver );
	if ( !inheritedStates )
	{
		StateSerializeHelper< UIRadioButtonLayout > reader( this, stateManager.states, &UIRadioButtonLayout::NewUIRadioButtonLayout );
		saver.AddPolymorphicBase( "__states", &reader );
	}
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UIRadioButtonLayout::SerializeSelf( IXmlSaver &saver )
{
	UICommonControl::SerializeSelf( saver );
	saver.Add( "highlightMaterial", &highlightMaterial );
	saver.Add( "selectedMaterial", &selectedMaterial );
	saver.Add( "disabledMaterial", &disabledMaterial );
	saver.Add( "disabledSelectedMaterial", &disabledSelectedMaterial );
	saver.Add( "flashedMaterial", &flashedMaterial );
	saver.Add( "group", &group );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool UIRadioButtonLayout::IsEqual( const UIRadioButtonLayout& _uIRadioButtonLayout ) const
{
	return highlightMaterial == _uIRadioButtonLayout.highlightMaterial
		&& selectedMaterial == _uIRadioButtonLayout.selectedMaterial
		&& disabledMaterial == _uIRadioButtonLayout.disabledMaterial
		&& disabledSelectedMaterial == _uIRadioButtonLayout.disabledSelectedMaterial
		&& flashedMaterial == _uIRadioButtonLayout.flashedMaterial
		&& group == _uIRadioButtonLayout.group
		&& mouseActions == _uIRadioButtonLayout.mouseActions
		&& soundHilite.projectName == _uIRadioButtonLayout.soundHilite.projectName
		&& soundHilite.groupName == _uIRadioButtonLayout.soundHilite.groupName
		&& soundHilite.eventName == _uIRadioButtonLayout.soundHilite.eventName
		&& activationBind == _uIRadioButtonLayout.activationBind
		&& backgroundMaterial == _uIRadioButtonLayout.backgroundMaterial
		&& shapeType == _uIRadioButtonLayout.shapeType
		&& captionText == _uIRadioButtonLayout.captionText
		&& fontStyle == _uIRadioButtonLayout.fontStyle
		&& wordWrap == _uIRadioButtonLayout.wordWrap
		&& stretchText == _uIRadioButtonLayout.stretchText
		&& rawTextMode == _uIRadioButtonLayout.rawTextMode
		&& textVAlign == _uIRadioButtonLayout.textVAlign
		&& textHAlign == _uIRadioButtonLayout.textHAlign
		&& textMargins.x1 == _uIRadioButtonLayout.textMargins.x1
		&& textMargins.y1 == _uIRadioButtonLayout.textMargins.y1
		&& textMargins.x2 == _uIRadioButtonLayout.textMargins.x2
		&& textMargins.y2 == _uIRadioButtonLayout.textMargins.y2
		&& captionOpacity == _uIRadioButtonLayout.captionOpacity
		&& name == _uIRadioButtonLayout.name
		&& visible == _uIRadioButtonLayout.visible
		&& enabled == _uIRadioButtonLayout.enabled
		&& location.x == _uIRadioButtonLayout.location.x
		&& location.y == _uIRadioButtonLayout.location.y
		&& size.x == _uIRadioButtonLayout.size.x
		&& size.y == _uIRadioButtonLayout.size.y
		&& hAlign == _uIRadioButtonLayout.hAlign
		&& vAlign == _uIRadioButtonLayout.vAlign
		&& keepAspectRatio == _uIRadioButtonLayout.keepAspectRatio
		&& subclass == _uIRadioButtonLayout.subclass
		&& scriptFile == _uIRadioButtonLayout.scriptFile
		&& cursors.normal == _uIRadioButtonLayout.cursors.normal
		&& cursors.dragging == _uIRadioButtonLayout.cursors.dragging
		&& cursors.dragable == _uIRadioButtonLayout.cursors.dragable
		&& cursors.focused == _uIRadioButtonLayout.cursors.focused
		&& cursors.disabled == _uIRadioButtonLayout.cursors.disabled
		&& cursors.pushing == _uIRadioButtonLayout.cursors.pushing
		&& cursors.pushable == _uIRadioButtonLayout.cursors.pushable
		&& subLayouts == _uIRadioButtonLayout.subLayouts
		&& draggable == _uIRadioButtonLayout.draggable
		&& defaultEventsCatch.mouseMove == _uIRadioButtonLayout.defaultEventsCatch.mouseMove
		&& defaultEventsCatch.leftMouseDown == _uIRadioButtonLayout.defaultEventsCatch.leftMouseDown
		&& defaultEventsCatch.rightMouseDown == _uIRadioButtonLayout.defaultEventsCatch.rightMouseDown
		&& defaultEventsCatch.leftMouseUp == _uIRadioButtonLayout.defaultEventsCatch.leftMouseUp
		&& defaultEventsCatch.rightMouseUp == _uIRadioButtonLayout.defaultEventsCatch.rightMouseUp
		&& defaultEventsCatch.leftDoubleClick == _uIRadioButtonLayout.defaultEventsCatch.leftDoubleClick
		&& defaultEventsCatch.rightDoubleClick == _uIRadioButtonLayout.defaultEventsCatch.rightDoubleClick
		&& transparent == _uIRadioButtonLayout.transparent
		&& cursorTransparent == _uIRadioButtonLayout.cursorTransparent
		&& needCrop == _uIRadioButtonLayout.needCrop
		&& relatedLayouts == _uIRadioButtonLayout.relatedLayouts
		&& relatedTexts == _uIRadioButtonLayout.relatedTexts
		&& tooltipText == _uIRadioButtonLayout.tooltipText
		&& soundShow.projectName == _uIRadioButtonLayout.soundShow.projectName
		&& soundShow.groupName == _uIRadioButtonLayout.soundShow.groupName
		&& soundShow.eventName == _uIRadioButtonLayout.soundShow.eventName
		&& soundHide.projectName == _uIRadioButtonLayout.soundHide.projectName
		&& soundHide.groupName == _uIRadioButtonLayout.soundHide.groupName
		&& soundHide.eventName == _uIRadioButtonLayout.soundHide.eventName
		&& soundActivate.projectName == _uIRadioButtonLayout.soundActivate.projectName
		&& soundActivate.groupName == _uIRadioButtonLayout.soundActivate.groupName
		&& soundActivate.eventName == _uIRadioButtonLayout.soundActivate.eventName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UIRadioButtonLayout::Assign( const UIRadioButtonLayout& _uIRadioButtonLayout )
{
	highlightMaterial = _uIRadioButtonLayout.highlightMaterial;
	selectedMaterial = _uIRadioButtonLayout.selectedMaterial;
	disabledMaterial = _uIRadioButtonLayout.disabledMaterial;
	disabledSelectedMaterial = _uIRadioButtonLayout.disabledSelectedMaterial;
	flashedMaterial = _uIRadioButtonLayout.flashedMaterial;
	group = _uIRadioButtonLayout.group;
	mouseActions = _uIRadioButtonLayout.mouseActions;
	soundHilite.projectName = _uIRadioButtonLayout.soundHilite.projectName;
	soundHilite.groupName = _uIRadioButtonLayout.soundHilite.groupName;
	soundHilite.eventName = _uIRadioButtonLayout.soundHilite.eventName;
	activationBind = _uIRadioButtonLayout.activationBind;
	backgroundMaterial = _uIRadioButtonLayout.backgroundMaterial;
	shapeType = _uIRadioButtonLayout.shapeType;
	captionText = _uIRadioButtonLayout.captionText;
	fontStyle = _uIRadioButtonLayout.fontStyle;
	wordWrap = _uIRadioButtonLayout.wordWrap;
	stretchText = _uIRadioButtonLayout.stretchText;
	rawTextMode = _uIRadioButtonLayout.rawTextMode;
	textVAlign = _uIRadioButtonLayout.textVAlign;
	textHAlign = _uIRadioButtonLayout.textHAlign;
	textMargins = _uIRadioButtonLayout.textMargins;
	captionOpacity = _uIRadioButtonLayout.captionOpacity;
	name = _uIRadioButtonLayout.name;
	visible = _uIRadioButtonLayout.visible;
	enabled = _uIRadioButtonLayout.enabled;
	location = _uIRadioButtonLayout.location;
	size = _uIRadioButtonLayout.size;
	hAlign = _uIRadioButtonLayout.hAlign;
	vAlign = _uIRadioButtonLayout.vAlign;
	keepAspectRatio = _uIRadioButtonLayout.keepAspectRatio;
	subclass = _uIRadioButtonLayout.subclass;
	scriptFile = _uIRadioButtonLayout.scriptFile;
	cursors.normal = _uIRadioButtonLayout.cursors.normal;
	cursors.dragging = _uIRadioButtonLayout.cursors.dragging;
	cursors.dragable = _uIRadioButtonLayout.cursors.dragable;
	cursors.focused = _uIRadioButtonLayout.cursors.focused;
	cursors.disabled = _uIRadioButtonLayout.cursors.disabled;
	cursors.pushing = _uIRadioButtonLayout.cursors.pushing;
	cursors.pushable = _uIRadioButtonLayout.cursors.pushable;
	subLayouts = _uIRadioButtonLayout.subLayouts;
	draggable = _uIRadioButtonLayout.draggable;
	defaultEventsCatch.mouseMove = _uIRadioButtonLayout.defaultEventsCatch.mouseMove;
	defaultEventsCatch.leftMouseDown = _uIRadioButtonLayout.defaultEventsCatch.leftMouseDown;
	defaultEventsCatch.rightMouseDown = _uIRadioButtonLayout.defaultEventsCatch.rightMouseDown;
	defaultEventsCatch.leftMouseUp = _uIRadioButtonLayout.defaultEventsCatch.leftMouseUp;
	defaultEventsCatch.rightMouseUp = _uIRadioButtonLayout.defaultEventsCatch.rightMouseUp;
	defaultEventsCatch.leftDoubleClick = _uIRadioButtonLayout.defaultEventsCatch.leftDoubleClick;
	defaultEventsCatch.rightDoubleClick = _uIRadioButtonLayout.defaultEventsCatch.rightDoubleClick;
	transparent = _uIRadioButtonLayout.transparent;
	cursorTransparent = _uIRadioButtonLayout.cursorTransparent;
	needCrop = _uIRadioButtonLayout.needCrop;
	relatedLayouts = _uIRadioButtonLayout.relatedLayouts;
	relatedTexts = _uIRadioButtonLayout.relatedTexts;
	tooltipText = _uIRadioButtonLayout.tooltipText;
	soundShow.projectName = _uIRadioButtonLayout.soundShow.projectName;
	soundShow.groupName = _uIRadioButtonLayout.soundShow.groupName;
	soundShow.eventName = _uIRadioButtonLayout.soundShow.eventName;
	soundHide.projectName = _uIRadioButtonLayout.soundHide.projectName;
	soundHide.groupName = _uIRadioButtonLayout.soundHide.groupName;
	soundHide.eventName = _uIRadioButtonLayout.soundHide.eventName;
	soundActivate.projectName = _uIRadioButtonLayout.soundActivate.projectName;
	soundActivate.groupName = _uIRadioButtonLayout.soundActivate.groupName;
	soundActivate.eventName = _uIRadioButtonLayout.soundActivate.eventName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UIRadioPanelLayout::UIRadioPanelLayout()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UIRadioPanelLayout::operator&( IBinSaver &saver )
{
	saver.Add( 1, (UIImageLabelLayout*)this );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UIRadioPanelLayout::operator&( IXmlSaver &saver )
{
	bool inheritedStates = false;
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			UIRadioPanelLayout* parentPtr = (UIRadioPanelLayout*)__parent.GetPtr();
			Assign( *parentPtr );
			StateSerializeHelper< UIRadioPanelLayout > parentStateCopier( this, stateManager.states, &UIRadioPanelLayout::NewUIRadioPanelLayout );
			parentStateCopier.InheritStates( parentPtr, parentPtr->GetStatesManager()->states, saver );
			inheritedStates = true;
		}
	}

	SerializeSelf( saver );
	if ( !inheritedStates )
	{
		StateSerializeHelper< UIRadioPanelLayout > reader( this, stateManager.states, &UIRadioPanelLayout::NewUIRadioPanelLayout );
		saver.AddPolymorphicBase( "__states", &reader );
	}
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UIRadioPanelLayout::SerializeSelf( IXmlSaver &saver )
{
	UIImageLabelLayout::SerializeSelf( saver );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool UIRadioPanelLayout::IsEqual( const UIRadioPanelLayout& _uIRadioPanelLayout ) const
{
	return backgroundMaterial == _uIRadioPanelLayout.backgroundMaterial
		&& shapeType == _uIRadioPanelLayout.shapeType
		&& captionText == _uIRadioPanelLayout.captionText
		&& fontStyle == _uIRadioPanelLayout.fontStyle
		&& wordWrap == _uIRadioPanelLayout.wordWrap
		&& stretchText == _uIRadioPanelLayout.stretchText
		&& rawTextMode == _uIRadioPanelLayout.rawTextMode
		&& textVAlign == _uIRadioPanelLayout.textVAlign
		&& textHAlign == _uIRadioPanelLayout.textHAlign
		&& textMargins.x1 == _uIRadioPanelLayout.textMargins.x1
		&& textMargins.y1 == _uIRadioPanelLayout.textMargins.y1
		&& textMargins.x2 == _uIRadioPanelLayout.textMargins.x2
		&& textMargins.y2 == _uIRadioPanelLayout.textMargins.y2
		&& captionOpacity == _uIRadioPanelLayout.captionOpacity
		&& name == _uIRadioPanelLayout.name
		&& visible == _uIRadioPanelLayout.visible
		&& enabled == _uIRadioPanelLayout.enabled
		&& location.x == _uIRadioPanelLayout.location.x
		&& location.y == _uIRadioPanelLayout.location.y
		&& size.x == _uIRadioPanelLayout.size.x
		&& size.y == _uIRadioPanelLayout.size.y
		&& hAlign == _uIRadioPanelLayout.hAlign
		&& vAlign == _uIRadioPanelLayout.vAlign
		&& keepAspectRatio == _uIRadioPanelLayout.keepAspectRatio
		&& subclass == _uIRadioPanelLayout.subclass
		&& scriptFile == _uIRadioPanelLayout.scriptFile
		&& cursors.normal == _uIRadioPanelLayout.cursors.normal
		&& cursors.dragging == _uIRadioPanelLayout.cursors.dragging
		&& cursors.dragable == _uIRadioPanelLayout.cursors.dragable
		&& cursors.focused == _uIRadioPanelLayout.cursors.focused
		&& cursors.disabled == _uIRadioPanelLayout.cursors.disabled
		&& cursors.pushing == _uIRadioPanelLayout.cursors.pushing
		&& cursors.pushable == _uIRadioPanelLayout.cursors.pushable
		&& subLayouts == _uIRadioPanelLayout.subLayouts
		&& draggable == _uIRadioPanelLayout.draggable
		&& defaultEventsCatch.mouseMove == _uIRadioPanelLayout.defaultEventsCatch.mouseMove
		&& defaultEventsCatch.leftMouseDown == _uIRadioPanelLayout.defaultEventsCatch.leftMouseDown
		&& defaultEventsCatch.rightMouseDown == _uIRadioPanelLayout.defaultEventsCatch.rightMouseDown
		&& defaultEventsCatch.leftMouseUp == _uIRadioPanelLayout.defaultEventsCatch.leftMouseUp
		&& defaultEventsCatch.rightMouseUp == _uIRadioPanelLayout.defaultEventsCatch.rightMouseUp
		&& defaultEventsCatch.leftDoubleClick == _uIRadioPanelLayout.defaultEventsCatch.leftDoubleClick
		&& defaultEventsCatch.rightDoubleClick == _uIRadioPanelLayout.defaultEventsCatch.rightDoubleClick
		&& transparent == _uIRadioPanelLayout.transparent
		&& cursorTransparent == _uIRadioPanelLayout.cursorTransparent
		&& needCrop == _uIRadioPanelLayout.needCrop
		&& relatedLayouts == _uIRadioPanelLayout.relatedLayouts
		&& relatedTexts == _uIRadioPanelLayout.relatedTexts
		&& tooltipText == _uIRadioPanelLayout.tooltipText
		&& soundShow.projectName == _uIRadioPanelLayout.soundShow.projectName
		&& soundShow.groupName == _uIRadioPanelLayout.soundShow.groupName
		&& soundShow.eventName == _uIRadioPanelLayout.soundShow.eventName
		&& soundHide.projectName == _uIRadioPanelLayout.soundHide.projectName
		&& soundHide.groupName == _uIRadioPanelLayout.soundHide.groupName
		&& soundHide.eventName == _uIRadioPanelLayout.soundHide.eventName
		&& soundActivate.projectName == _uIRadioPanelLayout.soundActivate.projectName
		&& soundActivate.groupName == _uIRadioPanelLayout.soundActivate.groupName
		&& soundActivate.eventName == _uIRadioPanelLayout.soundActivate.eventName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UIRadioPanelLayout::Assign( const UIRadioPanelLayout& _uIRadioPanelLayout )
{
	backgroundMaterial = _uIRadioPanelLayout.backgroundMaterial;
	shapeType = _uIRadioPanelLayout.shapeType;
	captionText = _uIRadioPanelLayout.captionText;
	fontStyle = _uIRadioPanelLayout.fontStyle;
	wordWrap = _uIRadioPanelLayout.wordWrap;
	stretchText = _uIRadioPanelLayout.stretchText;
	rawTextMode = _uIRadioPanelLayout.rawTextMode;
	textVAlign = _uIRadioPanelLayout.textVAlign;
	textHAlign = _uIRadioPanelLayout.textHAlign;
	textMargins = _uIRadioPanelLayout.textMargins;
	captionOpacity = _uIRadioPanelLayout.captionOpacity;
	name = _uIRadioPanelLayout.name;
	visible = _uIRadioPanelLayout.visible;
	enabled = _uIRadioPanelLayout.enabled;
	location = _uIRadioPanelLayout.location;
	size = _uIRadioPanelLayout.size;
	hAlign = _uIRadioPanelLayout.hAlign;
	vAlign = _uIRadioPanelLayout.vAlign;
	keepAspectRatio = _uIRadioPanelLayout.keepAspectRatio;
	subclass = _uIRadioPanelLayout.subclass;
	scriptFile = _uIRadioPanelLayout.scriptFile;
	cursors.normal = _uIRadioPanelLayout.cursors.normal;
	cursors.dragging = _uIRadioPanelLayout.cursors.dragging;
	cursors.dragable = _uIRadioPanelLayout.cursors.dragable;
	cursors.focused = _uIRadioPanelLayout.cursors.focused;
	cursors.disabled = _uIRadioPanelLayout.cursors.disabled;
	cursors.pushing = _uIRadioPanelLayout.cursors.pushing;
	cursors.pushable = _uIRadioPanelLayout.cursors.pushable;
	subLayouts = _uIRadioPanelLayout.subLayouts;
	draggable = _uIRadioPanelLayout.draggable;
	defaultEventsCatch.mouseMove = _uIRadioPanelLayout.defaultEventsCatch.mouseMove;
	defaultEventsCatch.leftMouseDown = _uIRadioPanelLayout.defaultEventsCatch.leftMouseDown;
	defaultEventsCatch.rightMouseDown = _uIRadioPanelLayout.defaultEventsCatch.rightMouseDown;
	defaultEventsCatch.leftMouseUp = _uIRadioPanelLayout.defaultEventsCatch.leftMouseUp;
	defaultEventsCatch.rightMouseUp = _uIRadioPanelLayout.defaultEventsCatch.rightMouseUp;
	defaultEventsCatch.leftDoubleClick = _uIRadioPanelLayout.defaultEventsCatch.leftDoubleClick;
	defaultEventsCatch.rightDoubleClick = _uIRadioPanelLayout.defaultEventsCatch.rightDoubleClick;
	transparent = _uIRadioPanelLayout.transparent;
	cursorTransparent = _uIRadioPanelLayout.cursorTransparent;
	needCrop = _uIRadioPanelLayout.needCrop;
	relatedLayouts = _uIRadioPanelLayout.relatedLayouts;
	relatedTexts = _uIRadioPanelLayout.relatedTexts;
	tooltipText = _uIRadioPanelLayout.tooltipText;
	soundShow.projectName = _uIRadioPanelLayout.soundShow.projectName;
	soundShow.groupName = _uIRadioPanelLayout.soundShow.groupName;
	soundShow.eventName = _uIRadioPanelLayout.soundShow.eventName;
	soundHide.projectName = _uIRadioPanelLayout.soundHide.projectName;
	soundHide.groupName = _uIRadioPanelLayout.soundHide.groupName;
	soundHide.eventName = _uIRadioPanelLayout.soundHide.eventName;
	soundActivate.projectName = _uIRadioPanelLayout.soundActivate.projectName;
	soundActivate.groupName = _uIRadioPanelLayout.soundActivate.groupName;
	soundActivate.eventName = _uIRadioPanelLayout.soundActivate.eventName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UIRoot::UIRoot()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UIRoot::operator&( IBinSaver &saver )
{
	saver.Add( 2, &screens );
	saver.Add( 3, &cursors );
	saver.Add( 4, &scripts );
	saver.Add( 5, &contents );
	saver.Add( 6, &consts );
	saver.Add( 7, &substitutes );
	saver.Add( 8, &styleAliases );
	saver.Add( 9, &fontStyles );
	saver.Add( 10, &preferences );
	saver.Add( 11, &votingForSurrender );
	saver.Add( 12, &healthStripes );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UIRoot::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			UIRoot* parentPtr = (UIRoot*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UIRoot::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "screens", &screens );
	saver.Add( "cursors", &cursors );
	saver.Add( "scripts", &scripts );
	saver.Add( "contents", &contents );
	saver.Add( "consts", &consts );
	saver.Add( "substitutes", &substitutes );
	saver.Add( "styleAliases", &styleAliases );
	saver.Add( "fontStyles", &fontStyles );
	saver.Add( "preferences", &preferences );
	saver.Add( "votingForSurrender", &votingForSurrender );
	saver.Add( "healthStripes", &healthStripes );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UIRoot::Assign( const UIRoot& _uIRoot )
{
	screens = _uIRoot.screens;
	cursors = _uIRoot.cursors;
	scripts = _uIRoot.scripts;
	contents = _uIRoot.contents;
	consts = _uIRoot.consts;
	substitutes = _uIRoot.substitutes;
	styleAliases = _uIRoot.styleAliases;
	fontStyles = _uIRoot.fontStyles;
	preferences = _uIRoot.preferences;
	votingForSurrender = _uIRoot.votingForSurrender;
	healthStripes.stripe1Step = _uIRoot.healthStripes.stripe1Step;
	healthStripes.stripe2Step = _uIRoot.healthStripes.stripe2Step;
	healthStripes.allyColor100 = _uIRoot.healthStripes.allyColor100;
	healthStripes.enemyColor100 = _uIRoot.healthStripes.enemyColor100;
	healthStripes.allyColor1000 = _uIRoot.healthStripes.allyColor1000;
	healthStripes.enemyColor1000 = _uIRoot.healthStripes.enemyColor1000;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UIScrollableWindowLayout::UIScrollableWindowLayout()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UIScrollableWindowLayout::operator&( IBinSaver &saver )
{
	saver.Add( 1, (UILayout*)this );
	saver.Add( 2, &scrollArea );
	saver.Add( 3, &scrollBar );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UIScrollableWindowLayout::operator&( IXmlSaver &saver )
{
	bool inheritedStates = false;
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			UIScrollableWindowLayout* parentPtr = (UIScrollableWindowLayout*)__parent.GetPtr();
			Assign( *parentPtr );
			StateSerializeHelper< UIScrollableWindowLayout > parentStateCopier( this, stateManager.states, &UIScrollableWindowLayout::NewUIScrollableWindowLayout );
			parentStateCopier.InheritStates( parentPtr, parentPtr->GetStatesManager()->states, saver );
			inheritedStates = true;
		}
	}

	SerializeSelf( saver );
	if ( !inheritedStates )
	{
		StateSerializeHelper< UIScrollableWindowLayout > reader( this, stateManager.states, &UIScrollableWindowLayout::NewUIScrollableWindowLayout );
		saver.AddPolymorphicBase( "__states", &reader );
	}
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UIScrollableWindowLayout::SerializeSelf( IXmlSaver &saver )
{
	UILayout::SerializeSelf( saver );
	saver.Add( "scrollArea", &scrollArea );
	saver.Add( "scrollBar", &scrollBar );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool UIScrollableWindowLayout::IsEqual( const UIScrollableWindowLayout& _uIScrollableWindowLayout ) const
{
	return scrollArea == _uIScrollableWindowLayout.scrollArea
		&& scrollBar == _uIScrollableWindowLayout.scrollBar
		&& name == _uIScrollableWindowLayout.name
		&& visible == _uIScrollableWindowLayout.visible
		&& enabled == _uIScrollableWindowLayout.enabled
		&& location.x == _uIScrollableWindowLayout.location.x
		&& location.y == _uIScrollableWindowLayout.location.y
		&& size.x == _uIScrollableWindowLayout.size.x
		&& size.y == _uIScrollableWindowLayout.size.y
		&& hAlign == _uIScrollableWindowLayout.hAlign
		&& vAlign == _uIScrollableWindowLayout.vAlign
		&& keepAspectRatio == _uIScrollableWindowLayout.keepAspectRatio
		&& subclass == _uIScrollableWindowLayout.subclass
		&& scriptFile == _uIScrollableWindowLayout.scriptFile
		&& cursors.normal == _uIScrollableWindowLayout.cursors.normal
		&& cursors.dragging == _uIScrollableWindowLayout.cursors.dragging
		&& cursors.dragable == _uIScrollableWindowLayout.cursors.dragable
		&& cursors.focused == _uIScrollableWindowLayout.cursors.focused
		&& cursors.disabled == _uIScrollableWindowLayout.cursors.disabled
		&& cursors.pushing == _uIScrollableWindowLayout.cursors.pushing
		&& cursors.pushable == _uIScrollableWindowLayout.cursors.pushable
		&& subLayouts == _uIScrollableWindowLayout.subLayouts
		&& draggable == _uIScrollableWindowLayout.draggable
		&& defaultEventsCatch.mouseMove == _uIScrollableWindowLayout.defaultEventsCatch.mouseMove
		&& defaultEventsCatch.leftMouseDown == _uIScrollableWindowLayout.defaultEventsCatch.leftMouseDown
		&& defaultEventsCatch.rightMouseDown == _uIScrollableWindowLayout.defaultEventsCatch.rightMouseDown
		&& defaultEventsCatch.leftMouseUp == _uIScrollableWindowLayout.defaultEventsCatch.leftMouseUp
		&& defaultEventsCatch.rightMouseUp == _uIScrollableWindowLayout.defaultEventsCatch.rightMouseUp
		&& defaultEventsCatch.leftDoubleClick == _uIScrollableWindowLayout.defaultEventsCatch.leftDoubleClick
		&& defaultEventsCatch.rightDoubleClick == _uIScrollableWindowLayout.defaultEventsCatch.rightDoubleClick
		&& transparent == _uIScrollableWindowLayout.transparent
		&& cursorTransparent == _uIScrollableWindowLayout.cursorTransparent
		&& needCrop == _uIScrollableWindowLayout.needCrop
		&& relatedLayouts == _uIScrollableWindowLayout.relatedLayouts
		&& relatedTexts == _uIScrollableWindowLayout.relatedTexts
		&& tooltipText == _uIScrollableWindowLayout.tooltipText
		&& soundShow.projectName == _uIScrollableWindowLayout.soundShow.projectName
		&& soundShow.groupName == _uIScrollableWindowLayout.soundShow.groupName
		&& soundShow.eventName == _uIScrollableWindowLayout.soundShow.eventName
		&& soundHide.projectName == _uIScrollableWindowLayout.soundHide.projectName
		&& soundHide.groupName == _uIScrollableWindowLayout.soundHide.groupName
		&& soundHide.eventName == _uIScrollableWindowLayout.soundHide.eventName
		&& soundActivate.projectName == _uIScrollableWindowLayout.soundActivate.projectName
		&& soundActivate.groupName == _uIScrollableWindowLayout.soundActivate.groupName
		&& soundActivate.eventName == _uIScrollableWindowLayout.soundActivate.eventName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UIScrollableWindowLayout::Assign( const UIScrollableWindowLayout& _uIScrollableWindowLayout )
{
	scrollArea = _uIScrollableWindowLayout.scrollArea;
	scrollBar = _uIScrollableWindowLayout.scrollBar;
	name = _uIScrollableWindowLayout.name;
	visible = _uIScrollableWindowLayout.visible;
	enabled = _uIScrollableWindowLayout.enabled;
	location = _uIScrollableWindowLayout.location;
	size = _uIScrollableWindowLayout.size;
	hAlign = _uIScrollableWindowLayout.hAlign;
	vAlign = _uIScrollableWindowLayout.vAlign;
	keepAspectRatio = _uIScrollableWindowLayout.keepAspectRatio;
	subclass = _uIScrollableWindowLayout.subclass;
	scriptFile = _uIScrollableWindowLayout.scriptFile;
	cursors.normal = _uIScrollableWindowLayout.cursors.normal;
	cursors.dragging = _uIScrollableWindowLayout.cursors.dragging;
	cursors.dragable = _uIScrollableWindowLayout.cursors.dragable;
	cursors.focused = _uIScrollableWindowLayout.cursors.focused;
	cursors.disabled = _uIScrollableWindowLayout.cursors.disabled;
	cursors.pushing = _uIScrollableWindowLayout.cursors.pushing;
	cursors.pushable = _uIScrollableWindowLayout.cursors.pushable;
	subLayouts = _uIScrollableWindowLayout.subLayouts;
	draggable = _uIScrollableWindowLayout.draggable;
	defaultEventsCatch.mouseMove = _uIScrollableWindowLayout.defaultEventsCatch.mouseMove;
	defaultEventsCatch.leftMouseDown = _uIScrollableWindowLayout.defaultEventsCatch.leftMouseDown;
	defaultEventsCatch.rightMouseDown = _uIScrollableWindowLayout.defaultEventsCatch.rightMouseDown;
	defaultEventsCatch.leftMouseUp = _uIScrollableWindowLayout.defaultEventsCatch.leftMouseUp;
	defaultEventsCatch.rightMouseUp = _uIScrollableWindowLayout.defaultEventsCatch.rightMouseUp;
	defaultEventsCatch.leftDoubleClick = _uIScrollableWindowLayout.defaultEventsCatch.leftDoubleClick;
	defaultEventsCatch.rightDoubleClick = _uIScrollableWindowLayout.defaultEventsCatch.rightDoubleClick;
	transparent = _uIScrollableWindowLayout.transparent;
	cursorTransparent = _uIScrollableWindowLayout.cursorTransparent;
	needCrop = _uIScrollableWindowLayout.needCrop;
	relatedLayouts = _uIScrollableWindowLayout.relatedLayouts;
	relatedTexts = _uIScrollableWindowLayout.relatedTexts;
	tooltipText = _uIScrollableWindowLayout.tooltipText;
	soundShow.projectName = _uIScrollableWindowLayout.soundShow.projectName;
	soundShow.groupName = _uIScrollableWindowLayout.soundShow.groupName;
	soundShow.eventName = _uIScrollableWindowLayout.soundShow.eventName;
	soundHide.projectName = _uIScrollableWindowLayout.soundHide.projectName;
	soundHide.groupName = _uIScrollableWindowLayout.soundHide.groupName;
	soundHide.eventName = _uIScrollableWindowLayout.soundHide.eventName;
	soundActivate.projectName = _uIScrollableWindowLayout.soundActivate.projectName;
	soundActivate.groupName = _uIScrollableWindowLayout.soundActivate.groupName;
	soundActivate.eventName = _uIScrollableWindowLayout.soundActivate.eventName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UIScrollAreaLayout::UIScrollAreaLayout()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UIScrollAreaLayout::operator&( IBinSaver &saver )
{
	saver.Add( 1, (UILayout*)this );
	saver.Add( 2, &handleMsgForXScroll );
	saver.Add( 3, &handleMsgForYScroll );
	saver.Add( 4, &scrollXLimits );
	saver.Add( 5, &scrollYLimits );
	saver.Add( 6, &spawnMsgOnLimitsChanged );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UIScrollAreaLayout::operator&( IXmlSaver &saver )
{
	bool inheritedStates = false;
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			UIScrollAreaLayout* parentPtr = (UIScrollAreaLayout*)__parent.GetPtr();
			Assign( *parentPtr );
			StateSerializeHelper< UIScrollAreaLayout > parentStateCopier( this, stateManager.states, &UIScrollAreaLayout::NewUIScrollAreaLayout );
			parentStateCopier.InheritStates( parentPtr, parentPtr->GetStatesManager()->states, saver );
			inheritedStates = true;
		}
	}

	SerializeSelf( saver );
	if ( !inheritedStates )
	{
		StateSerializeHelper< UIScrollAreaLayout > reader( this, stateManager.states, &UIScrollAreaLayout::NewUIScrollAreaLayout );
		saver.AddPolymorphicBase( "__states", &reader );
	}
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UIScrollAreaLayout::SerializeSelf( IXmlSaver &saver )
{
	UILayout::SerializeSelf( saver );
	saver.Add( "handleMsgForXScroll", &handleMsgForXScroll );
	saver.Add( "handleMsgForYScroll", &handleMsgForYScroll );
	saver.Add( "scrollXLimits", &scrollXLimits );
	saver.Add( "scrollYLimits", &scrollYLimits );
	saver.Add( "spawnMsgOnLimitsChanged", &spawnMsgOnLimitsChanged );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool UIScrollAreaLayout::IsEqual( const UIScrollAreaLayout& _uIScrollAreaLayout ) const
{
	return handleMsgForXScroll == _uIScrollAreaLayout.handleMsgForXScroll
		&& handleMsgForYScroll == _uIScrollAreaLayout.handleMsgForYScroll
		&& scrollXLimits.inMin == _uIScrollAreaLayout.scrollXLimits.inMin
		&& scrollXLimits.inMax == _uIScrollAreaLayout.scrollXLimits.inMax
		&& scrollXLimits.outMin == _uIScrollAreaLayout.scrollXLimits.outMin
		&& scrollXLimits.outMax == _uIScrollAreaLayout.scrollXLimits.outMax
		&& scrollYLimits.inMin == _uIScrollAreaLayout.scrollYLimits.inMin
		&& scrollYLimits.inMax == _uIScrollAreaLayout.scrollYLimits.inMax
		&& scrollYLimits.outMin == _uIScrollAreaLayout.scrollYLimits.outMin
		&& scrollYLimits.outMax == _uIScrollAreaLayout.scrollYLimits.outMax
		&& spawnMsgOnLimitsChanged == _uIScrollAreaLayout.spawnMsgOnLimitsChanged
		&& name == _uIScrollAreaLayout.name
		&& visible == _uIScrollAreaLayout.visible
		&& enabled == _uIScrollAreaLayout.enabled
		&& location.x == _uIScrollAreaLayout.location.x
		&& location.y == _uIScrollAreaLayout.location.y
		&& size.x == _uIScrollAreaLayout.size.x
		&& size.y == _uIScrollAreaLayout.size.y
		&& hAlign == _uIScrollAreaLayout.hAlign
		&& vAlign == _uIScrollAreaLayout.vAlign
		&& keepAspectRatio == _uIScrollAreaLayout.keepAspectRatio
		&& subclass == _uIScrollAreaLayout.subclass
		&& scriptFile == _uIScrollAreaLayout.scriptFile
		&& cursors.normal == _uIScrollAreaLayout.cursors.normal
		&& cursors.dragging == _uIScrollAreaLayout.cursors.dragging
		&& cursors.dragable == _uIScrollAreaLayout.cursors.dragable
		&& cursors.focused == _uIScrollAreaLayout.cursors.focused
		&& cursors.disabled == _uIScrollAreaLayout.cursors.disabled
		&& cursors.pushing == _uIScrollAreaLayout.cursors.pushing
		&& cursors.pushable == _uIScrollAreaLayout.cursors.pushable
		&& subLayouts == _uIScrollAreaLayout.subLayouts
		&& draggable == _uIScrollAreaLayout.draggable
		&& defaultEventsCatch.mouseMove == _uIScrollAreaLayout.defaultEventsCatch.mouseMove
		&& defaultEventsCatch.leftMouseDown == _uIScrollAreaLayout.defaultEventsCatch.leftMouseDown
		&& defaultEventsCatch.rightMouseDown == _uIScrollAreaLayout.defaultEventsCatch.rightMouseDown
		&& defaultEventsCatch.leftMouseUp == _uIScrollAreaLayout.defaultEventsCatch.leftMouseUp
		&& defaultEventsCatch.rightMouseUp == _uIScrollAreaLayout.defaultEventsCatch.rightMouseUp
		&& defaultEventsCatch.leftDoubleClick == _uIScrollAreaLayout.defaultEventsCatch.leftDoubleClick
		&& defaultEventsCatch.rightDoubleClick == _uIScrollAreaLayout.defaultEventsCatch.rightDoubleClick
		&& transparent == _uIScrollAreaLayout.transparent
		&& cursorTransparent == _uIScrollAreaLayout.cursorTransparent
		&& needCrop == _uIScrollAreaLayout.needCrop
		&& relatedLayouts == _uIScrollAreaLayout.relatedLayouts
		&& relatedTexts == _uIScrollAreaLayout.relatedTexts
		&& tooltipText == _uIScrollAreaLayout.tooltipText
		&& soundShow.projectName == _uIScrollAreaLayout.soundShow.projectName
		&& soundShow.groupName == _uIScrollAreaLayout.soundShow.groupName
		&& soundShow.eventName == _uIScrollAreaLayout.soundShow.eventName
		&& soundHide.projectName == _uIScrollAreaLayout.soundHide.projectName
		&& soundHide.groupName == _uIScrollAreaLayout.soundHide.groupName
		&& soundHide.eventName == _uIScrollAreaLayout.soundHide.eventName
		&& soundActivate.projectName == _uIScrollAreaLayout.soundActivate.projectName
		&& soundActivate.groupName == _uIScrollAreaLayout.soundActivate.groupName
		&& soundActivate.eventName == _uIScrollAreaLayout.soundActivate.eventName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UIScrollAreaLayout::Assign( const UIScrollAreaLayout& _uIScrollAreaLayout )
{
	handleMsgForXScroll = _uIScrollAreaLayout.handleMsgForXScroll;
	handleMsgForYScroll = _uIScrollAreaLayout.handleMsgForYScroll;
	scrollXLimits.inMin = _uIScrollAreaLayout.scrollXLimits.inMin;
	scrollXLimits.inMax = _uIScrollAreaLayout.scrollXLimits.inMax;
	scrollXLimits.outMin = _uIScrollAreaLayout.scrollXLimits.outMin;
	scrollXLimits.outMax = _uIScrollAreaLayout.scrollXLimits.outMax;
	scrollYLimits.inMin = _uIScrollAreaLayout.scrollYLimits.inMin;
	scrollYLimits.inMax = _uIScrollAreaLayout.scrollYLimits.inMax;
	scrollYLimits.outMin = _uIScrollAreaLayout.scrollYLimits.outMin;
	scrollYLimits.outMax = _uIScrollAreaLayout.scrollYLimits.outMax;
	spawnMsgOnLimitsChanged = _uIScrollAreaLayout.spawnMsgOnLimitsChanged;
	name = _uIScrollAreaLayout.name;
	visible = _uIScrollAreaLayout.visible;
	enabled = _uIScrollAreaLayout.enabled;
	location = _uIScrollAreaLayout.location;
	size = _uIScrollAreaLayout.size;
	hAlign = _uIScrollAreaLayout.hAlign;
	vAlign = _uIScrollAreaLayout.vAlign;
	keepAspectRatio = _uIScrollAreaLayout.keepAspectRatio;
	subclass = _uIScrollAreaLayout.subclass;
	scriptFile = _uIScrollAreaLayout.scriptFile;
	cursors.normal = _uIScrollAreaLayout.cursors.normal;
	cursors.dragging = _uIScrollAreaLayout.cursors.dragging;
	cursors.dragable = _uIScrollAreaLayout.cursors.dragable;
	cursors.focused = _uIScrollAreaLayout.cursors.focused;
	cursors.disabled = _uIScrollAreaLayout.cursors.disabled;
	cursors.pushing = _uIScrollAreaLayout.cursors.pushing;
	cursors.pushable = _uIScrollAreaLayout.cursors.pushable;
	subLayouts = _uIScrollAreaLayout.subLayouts;
	draggable = _uIScrollAreaLayout.draggable;
	defaultEventsCatch.mouseMove = _uIScrollAreaLayout.defaultEventsCatch.mouseMove;
	defaultEventsCatch.leftMouseDown = _uIScrollAreaLayout.defaultEventsCatch.leftMouseDown;
	defaultEventsCatch.rightMouseDown = _uIScrollAreaLayout.defaultEventsCatch.rightMouseDown;
	defaultEventsCatch.leftMouseUp = _uIScrollAreaLayout.defaultEventsCatch.leftMouseUp;
	defaultEventsCatch.rightMouseUp = _uIScrollAreaLayout.defaultEventsCatch.rightMouseUp;
	defaultEventsCatch.leftDoubleClick = _uIScrollAreaLayout.defaultEventsCatch.leftDoubleClick;
	defaultEventsCatch.rightDoubleClick = _uIScrollAreaLayout.defaultEventsCatch.rightDoubleClick;
	transparent = _uIScrollAreaLayout.transparent;
	cursorTransparent = _uIScrollAreaLayout.cursorTransparent;
	needCrop = _uIScrollAreaLayout.needCrop;
	relatedLayouts = _uIScrollAreaLayout.relatedLayouts;
	relatedTexts = _uIScrollAreaLayout.relatedTexts;
	tooltipText = _uIScrollAreaLayout.tooltipText;
	soundShow.projectName = _uIScrollAreaLayout.soundShow.projectName;
	soundShow.groupName = _uIScrollAreaLayout.soundShow.groupName;
	soundShow.eventName = _uIScrollAreaLayout.soundShow.eventName;
	soundHide.projectName = _uIScrollAreaLayout.soundHide.projectName;
	soundHide.groupName = _uIScrollAreaLayout.soundHide.groupName;
	soundHide.eventName = _uIScrollAreaLayout.soundHide.eventName;
	soundActivate.projectName = _uIScrollAreaLayout.soundActivate.projectName;
	soundActivate.groupName = _uIScrollAreaLayout.soundActivate.groupName;
	soundActivate.eventName = _uIScrollAreaLayout.soundActivate.eventName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UIScrollBarLayout::UIScrollBarLayout() :
		scrollBarType( UISCROLLBARTYPE_VERTICAL )
	, discretePositionsCount( 0 )
	, discreteType( UIDISCRETETYPE_NONE )
	, leverSize( 0 )
	, firstButtonSize( 0 )
	, secondButtonSize( 0 )
{
	leverMaterials.resize( 4 );
	firstButtonMaterials.resize( 4 );
	secondButtonMaterials.resize( 4 );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UIScrollBarLayout::operator&( IBinSaver &saver )
{
	saver.Add( 1, (UILayout*)this );
	saver.Add( 2, &scrollBarType );
	saver.Add( 3, &discretePositionsCount );
	saver.Add( 4, &discreteType );
	saver.Add( 5, &spawnMsgOnScrolled );
	saver.Add( 6, &leverAreaMaterial );
	saver.Add( 7, &leverAreaDisabledMaterial );
	saver.Add( 8, &leverMaterials );
	saver.Add( 9, &firstButtonMaterials );
	saver.Add( 10, &secondButtonMaterials );
	saver.Add( 11, &leverSize );
	saver.Add( 12, &firstButtonSize );
	saver.Add( 13, &secondButtonSize );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UIScrollBarLayout::operator&( IXmlSaver &saver )
{
	bool inheritedStates = false;
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			UIScrollBarLayout* parentPtr = (UIScrollBarLayout*)__parent.GetPtr();
			Assign( *parentPtr );
			StateSerializeHelper< UIScrollBarLayout > parentStateCopier( this, stateManager.states, &UIScrollBarLayout::NewUIScrollBarLayout );
			parentStateCopier.InheritStates( parentPtr, parentPtr->GetStatesManager()->states, saver );
			inheritedStates = true;
		}
	}

	SerializeSelf( saver );
	if ( !inheritedStates )
	{
		StateSerializeHelper< UIScrollBarLayout > reader( this, stateManager.states, &UIScrollBarLayout::NewUIScrollBarLayout );
		saver.AddPolymorphicBase( "__states", &reader );
	}
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UIScrollBarLayout::SerializeSelf( IXmlSaver &saver )
{
	UILayout::SerializeSelf( saver );
	saver.Add( "scrollBarType", &scrollBarType );
	saver.Add( "discretePositionsCount", &discretePositionsCount );
	saver.Add( "discreteType", &discreteType );
	saver.Add( "spawnMsgOnScrolled", &spawnMsgOnScrolled );
	saver.Add( "leverAreaMaterial", &leverAreaMaterial );
	saver.Add( "leverAreaDisabledMaterial", &leverAreaDisabledMaterial );
	leverMaterials.resize( 4 );
	saver.Add( "leverMaterials", &leverMaterials );
	firstButtonMaterials.resize( 4 );
	saver.Add( "firstButtonMaterials", &firstButtonMaterials );
	secondButtonMaterials.resize( 4 );
	saver.Add( "secondButtonMaterials", &secondButtonMaterials );
	saver.Add( "leverSize", &leverSize );
	saver.Add( "firstButtonSize", &firstButtonSize );
	saver.Add( "secondButtonSize", &secondButtonSize );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool UIScrollBarLayout::IsEqual( const UIScrollBarLayout& _uIScrollBarLayout ) const
{
	return scrollBarType == _uIScrollBarLayout.scrollBarType
		&& discretePositionsCount == _uIScrollBarLayout.discretePositionsCount
		&& discreteType == _uIScrollBarLayout.discreteType
		&& spawnMsgOnScrolled == _uIScrollBarLayout.spawnMsgOnScrolled
		&& leverAreaMaterial == _uIScrollBarLayout.leverAreaMaterial
		&& leverAreaDisabledMaterial == _uIScrollBarLayout.leverAreaDisabledMaterial
		&& leverMaterials == _uIScrollBarLayout.leverMaterials
		&& firstButtonMaterials == _uIScrollBarLayout.firstButtonMaterials
		&& secondButtonMaterials == _uIScrollBarLayout.secondButtonMaterials
		&& leverSize == _uIScrollBarLayout.leverSize
		&& firstButtonSize == _uIScrollBarLayout.firstButtonSize
		&& secondButtonSize == _uIScrollBarLayout.secondButtonSize
		&& name == _uIScrollBarLayout.name
		&& visible == _uIScrollBarLayout.visible
		&& enabled == _uIScrollBarLayout.enabled
		&& location.x == _uIScrollBarLayout.location.x
		&& location.y == _uIScrollBarLayout.location.y
		&& size.x == _uIScrollBarLayout.size.x
		&& size.y == _uIScrollBarLayout.size.y
		&& hAlign == _uIScrollBarLayout.hAlign
		&& vAlign == _uIScrollBarLayout.vAlign
		&& keepAspectRatio == _uIScrollBarLayout.keepAspectRatio
		&& subclass == _uIScrollBarLayout.subclass
		&& scriptFile == _uIScrollBarLayout.scriptFile
		&& cursors.normal == _uIScrollBarLayout.cursors.normal
		&& cursors.dragging == _uIScrollBarLayout.cursors.dragging
		&& cursors.dragable == _uIScrollBarLayout.cursors.dragable
		&& cursors.focused == _uIScrollBarLayout.cursors.focused
		&& cursors.disabled == _uIScrollBarLayout.cursors.disabled
		&& cursors.pushing == _uIScrollBarLayout.cursors.pushing
		&& cursors.pushable == _uIScrollBarLayout.cursors.pushable
		&& subLayouts == _uIScrollBarLayout.subLayouts
		&& draggable == _uIScrollBarLayout.draggable
		&& defaultEventsCatch.mouseMove == _uIScrollBarLayout.defaultEventsCatch.mouseMove
		&& defaultEventsCatch.leftMouseDown == _uIScrollBarLayout.defaultEventsCatch.leftMouseDown
		&& defaultEventsCatch.rightMouseDown == _uIScrollBarLayout.defaultEventsCatch.rightMouseDown
		&& defaultEventsCatch.leftMouseUp == _uIScrollBarLayout.defaultEventsCatch.leftMouseUp
		&& defaultEventsCatch.rightMouseUp == _uIScrollBarLayout.defaultEventsCatch.rightMouseUp
		&& defaultEventsCatch.leftDoubleClick == _uIScrollBarLayout.defaultEventsCatch.leftDoubleClick
		&& defaultEventsCatch.rightDoubleClick == _uIScrollBarLayout.defaultEventsCatch.rightDoubleClick
		&& transparent == _uIScrollBarLayout.transparent
		&& cursorTransparent == _uIScrollBarLayout.cursorTransparent
		&& needCrop == _uIScrollBarLayout.needCrop
		&& relatedLayouts == _uIScrollBarLayout.relatedLayouts
		&& relatedTexts == _uIScrollBarLayout.relatedTexts
		&& tooltipText == _uIScrollBarLayout.tooltipText
		&& soundShow.projectName == _uIScrollBarLayout.soundShow.projectName
		&& soundShow.groupName == _uIScrollBarLayout.soundShow.groupName
		&& soundShow.eventName == _uIScrollBarLayout.soundShow.eventName
		&& soundHide.projectName == _uIScrollBarLayout.soundHide.projectName
		&& soundHide.groupName == _uIScrollBarLayout.soundHide.groupName
		&& soundHide.eventName == _uIScrollBarLayout.soundHide.eventName
		&& soundActivate.projectName == _uIScrollBarLayout.soundActivate.projectName
		&& soundActivate.groupName == _uIScrollBarLayout.soundActivate.groupName
		&& soundActivate.eventName == _uIScrollBarLayout.soundActivate.eventName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UIScrollBarLayout::Assign( const UIScrollBarLayout& _uIScrollBarLayout )
{
	scrollBarType = _uIScrollBarLayout.scrollBarType;
	discretePositionsCount = _uIScrollBarLayout.discretePositionsCount;
	discreteType = _uIScrollBarLayout.discreteType;
	spawnMsgOnScrolled = _uIScrollBarLayout.spawnMsgOnScrolled;
	leverAreaMaterial = _uIScrollBarLayout.leverAreaMaterial;
	leverAreaDisabledMaterial = _uIScrollBarLayout.leverAreaDisabledMaterial;
	leverMaterials = _uIScrollBarLayout.leverMaterials;
	firstButtonMaterials = _uIScrollBarLayout.firstButtonMaterials;
	secondButtonMaterials = _uIScrollBarLayout.secondButtonMaterials;
	leverSize = _uIScrollBarLayout.leverSize;
	firstButtonSize = _uIScrollBarLayout.firstButtonSize;
	secondButtonSize = _uIScrollBarLayout.secondButtonSize;
	name = _uIScrollBarLayout.name;
	visible = _uIScrollBarLayout.visible;
	enabled = _uIScrollBarLayout.enabled;
	location = _uIScrollBarLayout.location;
	size = _uIScrollBarLayout.size;
	hAlign = _uIScrollBarLayout.hAlign;
	vAlign = _uIScrollBarLayout.vAlign;
	keepAspectRatio = _uIScrollBarLayout.keepAspectRatio;
	subclass = _uIScrollBarLayout.subclass;
	scriptFile = _uIScrollBarLayout.scriptFile;
	cursors.normal = _uIScrollBarLayout.cursors.normal;
	cursors.dragging = _uIScrollBarLayout.cursors.dragging;
	cursors.dragable = _uIScrollBarLayout.cursors.dragable;
	cursors.focused = _uIScrollBarLayout.cursors.focused;
	cursors.disabled = _uIScrollBarLayout.cursors.disabled;
	cursors.pushing = _uIScrollBarLayout.cursors.pushing;
	cursors.pushable = _uIScrollBarLayout.cursors.pushable;
	subLayouts = _uIScrollBarLayout.subLayouts;
	draggable = _uIScrollBarLayout.draggable;
	defaultEventsCatch.mouseMove = _uIScrollBarLayout.defaultEventsCatch.mouseMove;
	defaultEventsCatch.leftMouseDown = _uIScrollBarLayout.defaultEventsCatch.leftMouseDown;
	defaultEventsCatch.rightMouseDown = _uIScrollBarLayout.defaultEventsCatch.rightMouseDown;
	defaultEventsCatch.leftMouseUp = _uIScrollBarLayout.defaultEventsCatch.leftMouseUp;
	defaultEventsCatch.rightMouseUp = _uIScrollBarLayout.defaultEventsCatch.rightMouseUp;
	defaultEventsCatch.leftDoubleClick = _uIScrollBarLayout.defaultEventsCatch.leftDoubleClick;
	defaultEventsCatch.rightDoubleClick = _uIScrollBarLayout.defaultEventsCatch.rightDoubleClick;
	transparent = _uIScrollBarLayout.transparent;
	cursorTransparent = _uIScrollBarLayout.cursorTransparent;
	needCrop = _uIScrollBarLayout.needCrop;
	relatedLayouts = _uIScrollBarLayout.relatedLayouts;
	relatedTexts = _uIScrollBarLayout.relatedTexts;
	tooltipText = _uIScrollBarLayout.tooltipText;
	soundShow.projectName = _uIScrollBarLayout.soundShow.projectName;
	soundShow.groupName = _uIScrollBarLayout.soundShow.groupName;
	soundShow.eventName = _uIScrollBarLayout.soundShow.eventName;
	soundHide.projectName = _uIScrollBarLayout.soundHide.projectName;
	soundHide.groupName = _uIScrollBarLayout.soundHide.groupName;
	soundHide.eventName = _uIScrollBarLayout.soundHide.eventName;
	soundActivate.projectName = _uIScrollBarLayout.soundActivate.projectName;
	soundActivate.groupName = _uIScrollBarLayout.soundActivate.groupName;
	soundActivate.eventName = _uIScrollBarLayout.soundActivate.eventName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UIScrollListLayout::UIScrollListLayout() :
		placingOrigin( UILISTITEMSPLACINGORIGIN_LEFTTOP )
	, placingOrder( UILISTITEMSPLACINGORDER_BYROWS )
	, maxItemsTotal( 0 )
	, maxStrideItems( 0 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UIScrollListLayout::operator&( IBinSaver &saver )
{
	saver.Add( 1, (UIScrollAreaLayout*)this );
	saver.Add( 2, &placingOrigin );
	saver.Add( 3, &placingOrder );
	saver.Add( 4, &minItemSize );
	saver.Add( 5, &maxItemSize );
	saver.Add( 6, &maxItemsTotal );
	saver.Add( 7, &maxStrideItems );
	saver.Add( 8, &hilightMaterial );
	saver.Add( 9, &preselectMaterial );
	saver.Add( 10, &selectionMaterial );
	saver.Add( 11, &spawnMsgOnItemHighlighted );
	saver.Add( 12, &spawnMsgOnItemSelected );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UIScrollListLayout::operator&( IXmlSaver &saver )
{
	bool inheritedStates = false;
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			UIScrollListLayout* parentPtr = (UIScrollListLayout*)__parent.GetPtr();
			Assign( *parentPtr );
			StateSerializeHelper< UIScrollListLayout > parentStateCopier( this, stateManager.states, &UIScrollListLayout::NewUIScrollListLayout );
			parentStateCopier.InheritStates( parentPtr, parentPtr->GetStatesManager()->states, saver );
			inheritedStates = true;
		}
	}

	SerializeSelf( saver );
	if ( !inheritedStates )
	{
		StateSerializeHelper< UIScrollListLayout > reader( this, stateManager.states, &UIScrollListLayout::NewUIScrollListLayout );
		saver.AddPolymorphicBase( "__states", &reader );
	}
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UIScrollListLayout::SerializeSelf( IXmlSaver &saver )
{
	UIScrollAreaLayout::SerializeSelf( saver );
	saver.Add( "placingOrigin", &placingOrigin );
	saver.Add( "placingOrder", &placingOrder );
	saver.Add( "minItemSize", &minItemSize );
	saver.Add( "maxItemSize", &maxItemSize );
	saver.Add( "maxItemsTotal", &maxItemsTotal );
	saver.Add( "maxStrideItems", &maxStrideItems );
	saver.Add( "hilightMaterial", &hilightMaterial );
	saver.Add( "preselectMaterial", &preselectMaterial );
	saver.Add( "selectionMaterial", &selectionMaterial );
	saver.Add( "spawnMsgOnItemHighlighted", &spawnMsgOnItemHighlighted );
	saver.Add( "spawnMsgOnItemSelected", &spawnMsgOnItemSelected );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool UIScrollListLayout::IsEqual( const UIScrollListLayout& _uIScrollListLayout ) const
{
	return placingOrigin == _uIScrollListLayout.placingOrigin
		&& placingOrder == _uIScrollListLayout.placingOrder
		&& minItemSize.x == _uIScrollListLayout.minItemSize.x
		&& minItemSize.y == _uIScrollListLayout.minItemSize.y
		&& maxItemSize.x == _uIScrollListLayout.maxItemSize.x
		&& maxItemSize.y == _uIScrollListLayout.maxItemSize.y
		&& maxItemsTotal == _uIScrollListLayout.maxItemsTotal
		&& maxStrideItems == _uIScrollListLayout.maxStrideItems
		&& hilightMaterial == _uIScrollListLayout.hilightMaterial
		&& preselectMaterial == _uIScrollListLayout.preselectMaterial
		&& selectionMaterial == _uIScrollListLayout.selectionMaterial
		&& spawnMsgOnItemHighlighted == _uIScrollListLayout.spawnMsgOnItemHighlighted
		&& spawnMsgOnItemSelected == _uIScrollListLayout.spawnMsgOnItemSelected
		&& handleMsgForXScroll == _uIScrollListLayout.handleMsgForXScroll
		&& handleMsgForYScroll == _uIScrollListLayout.handleMsgForYScroll
		&& scrollXLimits.inMin == _uIScrollListLayout.scrollXLimits.inMin
		&& scrollXLimits.inMax == _uIScrollListLayout.scrollXLimits.inMax
		&& scrollXLimits.outMin == _uIScrollListLayout.scrollXLimits.outMin
		&& scrollXLimits.outMax == _uIScrollListLayout.scrollXLimits.outMax
		&& scrollYLimits.inMin == _uIScrollListLayout.scrollYLimits.inMin
		&& scrollYLimits.inMax == _uIScrollListLayout.scrollYLimits.inMax
		&& scrollYLimits.outMin == _uIScrollListLayout.scrollYLimits.outMin
		&& scrollYLimits.outMax == _uIScrollListLayout.scrollYLimits.outMax
		&& spawnMsgOnLimitsChanged == _uIScrollListLayout.spawnMsgOnLimitsChanged
		&& name == _uIScrollListLayout.name
		&& visible == _uIScrollListLayout.visible
		&& enabled == _uIScrollListLayout.enabled
		&& location.x == _uIScrollListLayout.location.x
		&& location.y == _uIScrollListLayout.location.y
		&& size.x == _uIScrollListLayout.size.x
		&& size.y == _uIScrollListLayout.size.y
		&& hAlign == _uIScrollListLayout.hAlign
		&& vAlign == _uIScrollListLayout.vAlign
		&& keepAspectRatio == _uIScrollListLayout.keepAspectRatio
		&& subclass == _uIScrollListLayout.subclass
		&& scriptFile == _uIScrollListLayout.scriptFile
		&& cursors.normal == _uIScrollListLayout.cursors.normal
		&& cursors.dragging == _uIScrollListLayout.cursors.dragging
		&& cursors.dragable == _uIScrollListLayout.cursors.dragable
		&& cursors.focused == _uIScrollListLayout.cursors.focused
		&& cursors.disabled == _uIScrollListLayout.cursors.disabled
		&& cursors.pushing == _uIScrollListLayout.cursors.pushing
		&& cursors.pushable == _uIScrollListLayout.cursors.pushable
		&& subLayouts == _uIScrollListLayout.subLayouts
		&& draggable == _uIScrollListLayout.draggable
		&& defaultEventsCatch.mouseMove == _uIScrollListLayout.defaultEventsCatch.mouseMove
		&& defaultEventsCatch.leftMouseDown == _uIScrollListLayout.defaultEventsCatch.leftMouseDown
		&& defaultEventsCatch.rightMouseDown == _uIScrollListLayout.defaultEventsCatch.rightMouseDown
		&& defaultEventsCatch.leftMouseUp == _uIScrollListLayout.defaultEventsCatch.leftMouseUp
		&& defaultEventsCatch.rightMouseUp == _uIScrollListLayout.defaultEventsCatch.rightMouseUp
		&& defaultEventsCatch.leftDoubleClick == _uIScrollListLayout.defaultEventsCatch.leftDoubleClick
		&& defaultEventsCatch.rightDoubleClick == _uIScrollListLayout.defaultEventsCatch.rightDoubleClick
		&& transparent == _uIScrollListLayout.transparent
		&& cursorTransparent == _uIScrollListLayout.cursorTransparent
		&& needCrop == _uIScrollListLayout.needCrop
		&& relatedLayouts == _uIScrollListLayout.relatedLayouts
		&& relatedTexts == _uIScrollListLayout.relatedTexts
		&& tooltipText == _uIScrollListLayout.tooltipText
		&& soundShow.projectName == _uIScrollListLayout.soundShow.projectName
		&& soundShow.groupName == _uIScrollListLayout.soundShow.groupName
		&& soundShow.eventName == _uIScrollListLayout.soundShow.eventName
		&& soundHide.projectName == _uIScrollListLayout.soundHide.projectName
		&& soundHide.groupName == _uIScrollListLayout.soundHide.groupName
		&& soundHide.eventName == _uIScrollListLayout.soundHide.eventName
		&& soundActivate.projectName == _uIScrollListLayout.soundActivate.projectName
		&& soundActivate.groupName == _uIScrollListLayout.soundActivate.groupName
		&& soundActivate.eventName == _uIScrollListLayout.soundActivate.eventName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UIScrollListLayout::Assign( const UIScrollListLayout& _uIScrollListLayout )
{
	placingOrigin = _uIScrollListLayout.placingOrigin;
	placingOrder = _uIScrollListLayout.placingOrder;
	minItemSize = _uIScrollListLayout.minItemSize;
	maxItemSize = _uIScrollListLayout.maxItemSize;
	maxItemsTotal = _uIScrollListLayout.maxItemsTotal;
	maxStrideItems = _uIScrollListLayout.maxStrideItems;
	hilightMaterial = _uIScrollListLayout.hilightMaterial;
	preselectMaterial = _uIScrollListLayout.preselectMaterial;
	selectionMaterial = _uIScrollListLayout.selectionMaterial;
	spawnMsgOnItemHighlighted = _uIScrollListLayout.spawnMsgOnItemHighlighted;
	spawnMsgOnItemSelected = _uIScrollListLayout.spawnMsgOnItemSelected;
	handleMsgForXScroll = _uIScrollListLayout.handleMsgForXScroll;
	handleMsgForYScroll = _uIScrollListLayout.handleMsgForYScroll;
	scrollXLimits.inMin = _uIScrollListLayout.scrollXLimits.inMin;
	scrollXLimits.inMax = _uIScrollListLayout.scrollXLimits.inMax;
	scrollXLimits.outMin = _uIScrollListLayout.scrollXLimits.outMin;
	scrollXLimits.outMax = _uIScrollListLayout.scrollXLimits.outMax;
	scrollYLimits.inMin = _uIScrollListLayout.scrollYLimits.inMin;
	scrollYLimits.inMax = _uIScrollListLayout.scrollYLimits.inMax;
	scrollYLimits.outMin = _uIScrollListLayout.scrollYLimits.outMin;
	scrollYLimits.outMax = _uIScrollListLayout.scrollYLimits.outMax;
	spawnMsgOnLimitsChanged = _uIScrollListLayout.spawnMsgOnLimitsChanged;
	name = _uIScrollListLayout.name;
	visible = _uIScrollListLayout.visible;
	enabled = _uIScrollListLayout.enabled;
	location = _uIScrollListLayout.location;
	size = _uIScrollListLayout.size;
	hAlign = _uIScrollListLayout.hAlign;
	vAlign = _uIScrollListLayout.vAlign;
	keepAspectRatio = _uIScrollListLayout.keepAspectRatio;
	subclass = _uIScrollListLayout.subclass;
	scriptFile = _uIScrollListLayout.scriptFile;
	cursors.normal = _uIScrollListLayout.cursors.normal;
	cursors.dragging = _uIScrollListLayout.cursors.dragging;
	cursors.dragable = _uIScrollListLayout.cursors.dragable;
	cursors.focused = _uIScrollListLayout.cursors.focused;
	cursors.disabled = _uIScrollListLayout.cursors.disabled;
	cursors.pushing = _uIScrollListLayout.cursors.pushing;
	cursors.pushable = _uIScrollListLayout.cursors.pushable;
	subLayouts = _uIScrollListLayout.subLayouts;
	draggable = _uIScrollListLayout.draggable;
	defaultEventsCatch.mouseMove = _uIScrollListLayout.defaultEventsCatch.mouseMove;
	defaultEventsCatch.leftMouseDown = _uIScrollListLayout.defaultEventsCatch.leftMouseDown;
	defaultEventsCatch.rightMouseDown = _uIScrollListLayout.defaultEventsCatch.rightMouseDown;
	defaultEventsCatch.leftMouseUp = _uIScrollListLayout.defaultEventsCatch.leftMouseUp;
	defaultEventsCatch.rightMouseUp = _uIScrollListLayout.defaultEventsCatch.rightMouseUp;
	defaultEventsCatch.leftDoubleClick = _uIScrollListLayout.defaultEventsCatch.leftDoubleClick;
	defaultEventsCatch.rightDoubleClick = _uIScrollListLayout.defaultEventsCatch.rightDoubleClick;
	transparent = _uIScrollListLayout.transparent;
	cursorTransparent = _uIScrollListLayout.cursorTransparent;
	needCrop = _uIScrollListLayout.needCrop;
	relatedLayouts = _uIScrollListLayout.relatedLayouts;
	relatedTexts = _uIScrollListLayout.relatedTexts;
	tooltipText = _uIScrollListLayout.tooltipText;
	soundShow.projectName = _uIScrollListLayout.soundShow.projectName;
	soundShow.groupName = _uIScrollListLayout.soundShow.groupName;
	soundShow.eventName = _uIScrollListLayout.soundShow.eventName;
	soundHide.projectName = _uIScrollListLayout.soundHide.projectName;
	soundHide.groupName = _uIScrollListLayout.soundHide.groupName;
	soundHide.eventName = _uIScrollListLayout.soundHide.eventName;
	soundActivate.projectName = _uIScrollListLayout.soundActivate.projectName;
	soundActivate.groupName = _uIScrollListLayout.soundActivate.groupName;
	soundActivate.eventName = _uIScrollListLayout.soundActivate.eventName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UITexture::UITexture() :
		importOnlyShape( false )
	, shapeAlphaThreshold( 0 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UITexture::operator&( IBinSaver &saver )
{
	saver.Add( 1, (Texture*)this );
	saver.Add( 2, &importOnlyShape );
	saver.Add( 3, &shapeAlphaThreshold );
	saver.Add( 4, &shapeFileName );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UITexture::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			UITexture* parentPtr = (UITexture*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UITexture::SerializeSelf( IXmlSaver &saver )
{
	Texture::SerializeSelf( saver );
	saver.Add( "importOnlyShape", &importOnlyShape );
	saver.Add( "shapeAlphaThreshold", &shapeAlphaThreshold );
	saver.Add( "shapeFileName", &shapeFileName );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UITexture::Assign( const UITexture& _uITexture )
{
	importOnlyShape = _uITexture.importOnlyShape;
	shapeAlphaThreshold = _uITexture.shapeAlphaThreshold;
	shapeFileName = _uITexture.shapeFileName;
	srcFileName = _uITexture.srcFileName;
	textureFileName = _uITexture.textureFileName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef VISUAL_CUTTED
CObj<Render::Texture> UITexture::Load() const
{
	return (Render::Texture *)Render::LoadTexture2D( *this );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CObj<Render::Texture> UITexture::LoadInPool( bool canBeVisualDegrade, void * texturePoolId ) const
{
	return (Render::Texture *)Render::LoadTexture2DIntoPool( *this, canBeVisualDegrade, texturePoolId );
}
#endif // #ifndef VISUAL_CUTTED
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UIViewLayout::UIViewLayout() :
		framesPerSecond( 15 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UIViewLayout::operator&( IBinSaver &saver )
{
	saver.Add( 1, (UILayout*)this );
	saver.Add( 2, &provider );
	saver.Add( 3, &address );
	saver.Add( 4, &framesPerSecond );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UIViewLayout::operator&( IXmlSaver &saver )
{
	bool inheritedStates = false;
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			UIViewLayout* parentPtr = (UIViewLayout*)__parent.GetPtr();
			Assign( *parentPtr );
			StateSerializeHelper< UIViewLayout > parentStateCopier( this, stateManager.states, &UIViewLayout::NewUIViewLayout );
			parentStateCopier.InheritStates( parentPtr, parentPtr->GetStatesManager()->states, saver );
			inheritedStates = true;
		}
	}

	SerializeSelf( saver );
	if ( !inheritedStates )
	{
		StateSerializeHelper< UIViewLayout > reader( this, stateManager.states, &UIViewLayout::NewUIViewLayout );
		saver.AddPolymorphicBase( "__states", &reader );
	}
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UIViewLayout::SerializeSelf( IXmlSaver &saver )
{
	UILayout::SerializeSelf( saver );
	saver.Add( "provider", &provider );
	saver.Add( "address", &address );
	saver.Add( "framesPerSecond", &framesPerSecond );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool UIViewLayout::IsEqual( const UIViewLayout& _uIViewLayout ) const
{
	return provider == _uIViewLayout.provider
		&& address == _uIViewLayout.address
		&& framesPerSecond == _uIViewLayout.framesPerSecond
		&& name == _uIViewLayout.name
		&& visible == _uIViewLayout.visible
		&& enabled == _uIViewLayout.enabled
		&& location.x == _uIViewLayout.location.x
		&& location.y == _uIViewLayout.location.y
		&& size.x == _uIViewLayout.size.x
		&& size.y == _uIViewLayout.size.y
		&& hAlign == _uIViewLayout.hAlign
		&& vAlign == _uIViewLayout.vAlign
		&& keepAspectRatio == _uIViewLayout.keepAspectRatio
		&& subclass == _uIViewLayout.subclass
		&& scriptFile == _uIViewLayout.scriptFile
		&& cursors.normal == _uIViewLayout.cursors.normal
		&& cursors.dragging == _uIViewLayout.cursors.dragging
		&& cursors.dragable == _uIViewLayout.cursors.dragable
		&& cursors.focused == _uIViewLayout.cursors.focused
		&& cursors.disabled == _uIViewLayout.cursors.disabled
		&& cursors.pushing == _uIViewLayout.cursors.pushing
		&& cursors.pushable == _uIViewLayout.cursors.pushable
		&& subLayouts == _uIViewLayout.subLayouts
		&& draggable == _uIViewLayout.draggable
		&& defaultEventsCatch.mouseMove == _uIViewLayout.defaultEventsCatch.mouseMove
		&& defaultEventsCatch.leftMouseDown == _uIViewLayout.defaultEventsCatch.leftMouseDown
		&& defaultEventsCatch.rightMouseDown == _uIViewLayout.defaultEventsCatch.rightMouseDown
		&& defaultEventsCatch.leftMouseUp == _uIViewLayout.defaultEventsCatch.leftMouseUp
		&& defaultEventsCatch.rightMouseUp == _uIViewLayout.defaultEventsCatch.rightMouseUp
		&& defaultEventsCatch.leftDoubleClick == _uIViewLayout.defaultEventsCatch.leftDoubleClick
		&& defaultEventsCatch.rightDoubleClick == _uIViewLayout.defaultEventsCatch.rightDoubleClick
		&& transparent == _uIViewLayout.transparent
		&& cursorTransparent == _uIViewLayout.cursorTransparent
		&& needCrop == _uIViewLayout.needCrop
		&& relatedLayouts == _uIViewLayout.relatedLayouts
		&& relatedTexts == _uIViewLayout.relatedTexts
		&& tooltipText == _uIViewLayout.tooltipText
		&& soundShow.projectName == _uIViewLayout.soundShow.projectName
		&& soundShow.groupName == _uIViewLayout.soundShow.groupName
		&& soundShow.eventName == _uIViewLayout.soundShow.eventName
		&& soundHide.projectName == _uIViewLayout.soundHide.projectName
		&& soundHide.groupName == _uIViewLayout.soundHide.groupName
		&& soundHide.eventName == _uIViewLayout.soundHide.eventName
		&& soundActivate.projectName == _uIViewLayout.soundActivate.projectName
		&& soundActivate.groupName == _uIViewLayout.soundActivate.groupName
		&& soundActivate.eventName == _uIViewLayout.soundActivate.eventName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UIViewLayout::Assign( const UIViewLayout& _uIViewLayout )
{
	provider = _uIViewLayout.provider;
	address = _uIViewLayout.address;
	framesPerSecond = _uIViewLayout.framesPerSecond;
	name = _uIViewLayout.name;
	visible = _uIViewLayout.visible;
	enabled = _uIViewLayout.enabled;
	location = _uIViewLayout.location;
	size = _uIViewLayout.size;
	hAlign = _uIViewLayout.hAlign;
	vAlign = _uIViewLayout.vAlign;
	keepAspectRatio = _uIViewLayout.keepAspectRatio;
	subclass = _uIViewLayout.subclass;
	scriptFile = _uIViewLayout.scriptFile;
	cursors.normal = _uIViewLayout.cursors.normal;
	cursors.dragging = _uIViewLayout.cursors.dragging;
	cursors.dragable = _uIViewLayout.cursors.dragable;
	cursors.focused = _uIViewLayout.cursors.focused;
	cursors.disabled = _uIViewLayout.cursors.disabled;
	cursors.pushing = _uIViewLayout.cursors.pushing;
	cursors.pushable = _uIViewLayout.cursors.pushable;
	subLayouts = _uIViewLayout.subLayouts;
	draggable = _uIViewLayout.draggable;
	defaultEventsCatch.mouseMove = _uIViewLayout.defaultEventsCatch.mouseMove;
	defaultEventsCatch.leftMouseDown = _uIViewLayout.defaultEventsCatch.leftMouseDown;
	defaultEventsCatch.rightMouseDown = _uIViewLayout.defaultEventsCatch.rightMouseDown;
	defaultEventsCatch.leftMouseUp = _uIViewLayout.defaultEventsCatch.leftMouseUp;
	defaultEventsCatch.rightMouseUp = _uIViewLayout.defaultEventsCatch.rightMouseUp;
	defaultEventsCatch.leftDoubleClick = _uIViewLayout.defaultEventsCatch.leftDoubleClick;
	defaultEventsCatch.rightDoubleClick = _uIViewLayout.defaultEventsCatch.rightDoubleClick;
	transparent = _uIViewLayout.transparent;
	cursorTransparent = _uIViewLayout.cursorTransparent;
	needCrop = _uIViewLayout.needCrop;
	relatedLayouts = _uIViewLayout.relatedLayouts;
	relatedTexts = _uIViewLayout.relatedTexts;
	tooltipText = _uIViewLayout.tooltipText;
	soundShow.projectName = _uIViewLayout.soundShow.projectName;
	soundShow.groupName = _uIViewLayout.soundShow.groupName;
	soundShow.eventName = _uIViewLayout.soundShow.eventName;
	soundHide.projectName = _uIViewLayout.soundHide.projectName;
	soundHide.groupName = _uIViewLayout.soundHide.groupName;
	soundHide.eventName = _uIViewLayout.soundHide.eventName;
	soundActivate.projectName = _uIViewLayout.soundActivate.projectName;
	soundActivate.groupName = _uIViewLayout.soundActivate.groupName;
	soundActivate.eventName = _uIViewLayout.soundActivate.eventName;
}
}; // namespace NDb
