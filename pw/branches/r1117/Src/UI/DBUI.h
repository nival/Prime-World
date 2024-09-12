#pragma once
// Automatically generated file, don't change it manually!

#include "../libdb/Db.h"
#include "../libdb/Animated.h"
#include "../libdb/AnimatedAlgorithms.h"
#include "../Render/DBRender.h"
#include "../Render/DBRenderResources.h"
#include "../Sound/DBSound.h"

struct IXmlSaver;
// forward declarations for factories
namespace Render
{
	class Texture;
}; //namespace Render

namespace NDb
{
struct BaseUIMaterial;
struct Preferences;
struct Texture;
struct UIBaseLayout;
struct UIContentResource;
struct UICursorBase;
struct UIFontStyle;
struct UIImageLabelLayout;
struct UILayout;
struct UIRadioButtonLayout;
struct UIScrollAreaLayout;
struct UIScrollBarLayout;
struct VotingForSurrender;

enum EImageLabelShapeType
{
	IMAGELABELSHAPETYPE_EMPTY = 0,
	IMAGELABELSHAPETYPE_SIMPLEBOX = 1,
	IMAGELABELSHAPETYPE_FROMSHAPESTYLE = 2,
	IMAGELABELSHAPETYPE_FROMBACKGROUNDSTYLE = 3,
	IMAGELABELSHAPETYPE_FROMSHAPEORBACKGROUNDSTYLE = 4,
	IMAGELABELSHAPETYPE_BYTEXT = 5,
};

const char *EnumToString( const EImageLabelShapeType value );
const EImageLabelShapeType StringToEnum_EImageLabelShapeType( const char* value );

template <>
struct KnownEnum< EImageLabelShapeType >
{
	enum { isKnown = 1 };
	enum { sizeOf = 6 };
	static const char *ToString( const EImageLabelShapeType value ) { return EnumToString( value ); }
	static const EImageLabelShapeType ToEnum( const char* value ) { return StringToEnum_EImageLabelShapeType( value ); }
	static const EImageLabelShapeType ToEnum( const string& value ) { return StringToEnum_EImageLabelShapeType( value.c_str() ); }
	static const int SizeOf() { return 6; }
};

enum EUI3DOvertipMode
{
	UI3DOVERTIPMODE_WORLD = 0,
	UI3DOVERTIPMODE_BILLBOARD = 1,
	UI3DOVERTIPMODE_AXISBILLBOARD = 2,
};

const char *EnumToString( const EUI3DOvertipMode value );
const EUI3DOvertipMode StringToEnum_EUI3DOvertipMode( const char* value );

template <>
struct KnownEnum< EUI3DOvertipMode >
{
	enum { isKnown = 1 };
	enum { sizeOf = 3 };
	static const char *ToString( const EUI3DOvertipMode value ) { return EnumToString( value ); }
	static const EUI3DOvertipMode ToEnum( const char* value ) { return StringToEnum_EUI3DOvertipMode( value ); }
	static const EUI3DOvertipMode ToEnum( const string& value ) { return StringToEnum_EUI3DOvertipMode( value.c_str() ); }
	static const int SizeOf() { return 3; }
};

enum EUIButtonViewMode
{
	UIBUTTONVIEWMODE_BYMATERIALS = 0,
	UIBUTTONVIEWMODE_BYPINS = 1,
	UIBUTTONVIEWMODE_BYPINSWITHOUTDISABLEPIN = 2,
};

const char *EnumToString( const EUIButtonViewMode value );
const EUIButtonViewMode StringToEnum_EUIButtonViewMode( const char* value );

template <>
struct KnownEnum< EUIButtonViewMode >
{
	enum { isKnown = 1 };
	enum { sizeOf = 3 };
	static const char *ToString( const EUIButtonViewMode value ) { return EnumToString( value ); }
	static const EUIButtonViewMode ToEnum( const char* value ) { return StringToEnum_EUIButtonViewMode( value ); }
	static const EUIButtonViewMode ToEnum( const string& value ) { return StringToEnum_EUIButtonViewMode( value.c_str() ); }
	static const int SizeOf() { return 3; }
};

enum EUIControlMouseActions
{
	UICONTROLMOUSEACTIONS_LEFT = 0,
	UICONTROLMOUSEACTIONS_RIGHT = 1,
	UICONTROLMOUSEACTIONS_BOTH = 2,
};

const char *EnumToString( const EUIControlMouseActions value );
const EUIControlMouseActions StringToEnum_EUIControlMouseActions( const char* value );

template <>
struct KnownEnum< EUIControlMouseActions >
{
	enum { isKnown = 1 };
	enum { sizeOf = 3 };
	static const char *ToString( const EUIControlMouseActions value ) { return EnumToString( value ); }
	static const EUIControlMouseActions ToEnum( const char* value ) { return StringToEnum_EUIControlMouseActions( value ); }
	static const EUIControlMouseActions ToEnum( const string& value ) { return StringToEnum_EUIControlMouseActions( value.c_str() ); }
	static const int SizeOf() { return 3; }
};

enum EUIDiscreteType
{
	UIDISCRETETYPE_NONE = 0,
	UIDISCRETETYPE_FIXED = 1,
	UIDISCRETETYPE_RELATIVETOITEMSCOUNT = 2,
};

const char *EnumToString( const EUIDiscreteType value );
const EUIDiscreteType StringToEnum_EUIDiscreteType( const char* value );

template <>
struct KnownEnum< EUIDiscreteType >
{
	enum { isKnown = 1 };
	enum { sizeOf = 3 };
	static const char *ToString( const EUIDiscreteType value ) { return EnumToString( value ); }
	static const EUIDiscreteType ToEnum( const char* value ) { return StringToEnum_EUIDiscreteType( value ); }
	static const EUIDiscreteType ToEnum( const string& value ) { return StringToEnum_EUIDiscreteType( value.c_str() ); }
	static const int SizeOf() { return 3; }
};

enum EUIElementAspectRatio
{
	UIELEMENTASPECTRATIO_DONTCARE = 0,
	UIELEMENTASPECTRATIO_WIDTHBASED = 1,
	UIELEMENTASPECTRATIO_HEIGHTBASED = 2,
};

const char *EnumToString( const EUIElementAspectRatio value );
const EUIElementAspectRatio StringToEnum_EUIElementAspectRatio( const char* value );

template <>
struct KnownEnum< EUIElementAspectRatio >
{
	enum { isKnown = 1 };
	enum { sizeOf = 3 };
	static const char *ToString( const EUIElementAspectRatio value ) { return EnumToString( value ); }
	static const EUIElementAspectRatio ToEnum( const char* value ) { return StringToEnum_EUIElementAspectRatio( value ); }
	static const EUIElementAspectRatio ToEnum( const string& value ) { return StringToEnum_EUIElementAspectRatio( value.c_str() ); }
	static const int SizeOf() { return 3; }
};

enum EUIElementHAlign
{
	UIELEMENTHALIGN_LEFT = 0,
	UIELEMENTHALIGN_RIGHT = 1,
	UIELEMENTHALIGN_CENTER = 2,
	UIELEMENTHALIGN_FIXEDMARGINS = 3,
	UIELEMENTHALIGN_PROPORTIONAL = 4,
};

const char *EnumToString( const EUIElementHAlign value );
const EUIElementHAlign StringToEnum_EUIElementHAlign( const char* value );

template <>
struct KnownEnum< EUIElementHAlign >
{
	enum { isKnown = 1 };
	enum { sizeOf = 5 };
	static const char *ToString( const EUIElementHAlign value ) { return EnumToString( value ); }
	static const EUIElementHAlign ToEnum( const char* value ) { return StringToEnum_EUIElementHAlign( value ); }
	static const EUIElementHAlign ToEnum( const string& value ) { return StringToEnum_EUIElementHAlign( value.c_str() ); }
	static const int SizeOf() { return 5; }
};

enum EUIElementVAlign
{
	UIELEMENTVALIGN_TOP = 0,
	UIELEMENTVALIGN_BOTTOM = 1,
	UIELEMENTVALIGN_CENTER = 2,
	UIELEMENTVALIGN_FIXEDMARGINS = 3,
	UIELEMENTVALIGN_PROPORTIONAL = 4,
};

const char *EnumToString( const EUIElementVAlign value );
const EUIElementVAlign StringToEnum_EUIElementVAlign( const char* value );

template <>
struct KnownEnum< EUIElementVAlign >
{
	enum { isKnown = 1 };
	enum { sizeOf = 5 };
	static const char *ToString( const EUIElementVAlign value ) { return EnumToString( value ); }
	static const EUIElementVAlign ToEnum( const char* value ) { return StringToEnum_EUIElementVAlign( value ); }
	static const EUIElementVAlign ToEnum( const string& value ) { return StringToEnum_EUIElementVAlign( value.c_str() ); }
	static const int SizeOf() { return 5; }
};

enum EUIListItemsPlacingOrder
{
	UILISTITEMSPLACINGORDER_BYROWS = 0,
	UILISTITEMSPLACINGORDER_BYCOLUMNS = 1,
	UILISTITEMSPLACINGORDER_BYROWSOFCOLUMNS = 2,
	UILISTITEMSPLACINGORDER_BYCOLUMNSOFROWS = 3,
};

const char *EnumToString( const EUIListItemsPlacingOrder value );
const EUIListItemsPlacingOrder StringToEnum_EUIListItemsPlacingOrder( const char* value );

template <>
struct KnownEnum< EUIListItemsPlacingOrder >
{
	enum { isKnown = 1 };
	enum { sizeOf = 4 };
	static const char *ToString( const EUIListItemsPlacingOrder value ) { return EnumToString( value ); }
	static const EUIListItemsPlacingOrder ToEnum( const char* value ) { return StringToEnum_EUIListItemsPlacingOrder( value ); }
	static const EUIListItemsPlacingOrder ToEnum( const string& value ) { return StringToEnum_EUIListItemsPlacingOrder( value.c_str() ); }
	static const int SizeOf() { return 4; }
};

enum EUIListItemsPlacingOrigin
{
	UILISTITEMSPLACINGORIGIN_LEFTTOP = 0,
	UILISTITEMSPLACINGORIGIN_RIGHTTOP = 1,
	UILISTITEMSPLACINGORIGIN_LEFTBOTTOM = 2,
	UILISTITEMSPLACINGORIGIN_RIGHTBOTTOM = 3,
};

const char *EnumToString( const EUIListItemsPlacingOrigin value );
const EUIListItemsPlacingOrigin StringToEnum_EUIListItemsPlacingOrigin( const char* value );

template <>
struct KnownEnum< EUIListItemsPlacingOrigin >
{
	enum { isKnown = 1 };
	enum { sizeOf = 4 };
	static const char *ToString( const EUIListItemsPlacingOrigin value ) { return EnumToString( value ); }
	static const EUIListItemsPlacingOrigin ToEnum( const char* value ) { return StringToEnum_EUIListItemsPlacingOrigin( value ); }
	static const EUIListItemsPlacingOrigin ToEnum( const string& value ) { return StringToEnum_EUIListItemsPlacingOrigin( value.c_str() ); }
	static const int SizeOf() { return 4; }
};

enum EUIOvertipBindPoint
{
	UIOVERTIPBINDPOINT_NONE = 0,
	UIOVERTIPBINDPOINT_CENTER = 1,
	UIOVERTIPBINDPOINT_LEFTTOP = 2,
	UIOVERTIPBINDPOINT_CENTERTOP = 3,
	UIOVERTIPBINDPOINT_RIGHTTOP = 4,
	UIOVERTIPBINDPOINT_LEFTCENTER = 5,
	UIOVERTIPBINDPOINT_RIGHTCENTER = 6,
	UIOVERTIPBINDPOINT_LEFTBOTTOM = 7,
	UIOVERTIPBINDPOINT_CENTERBOTTOM = 8,
	UIOVERTIPBINDPOINT_RIGHTBOTTOM = 9,
};

const char *EnumToString( const EUIOvertipBindPoint value );
const EUIOvertipBindPoint StringToEnum_EUIOvertipBindPoint( const char* value );

template <>
struct KnownEnum< EUIOvertipBindPoint >
{
	enum { isKnown = 1 };
	enum { sizeOf = 10 };
	static const char *ToString( const EUIOvertipBindPoint value ) { return EnumToString( value ); }
	static const EUIOvertipBindPoint ToEnum( const char* value ) { return StringToEnum_EUIOvertipBindPoint( value ); }
	static const EUIOvertipBindPoint ToEnum( const string& value ) { return StringToEnum_EUIOvertipBindPoint( value.c_str() ); }
	static const int SizeOf() { return 10; }
};

enum EUIProgressBarType
{
	UIPROGRESSBARTYPE_HORIZONTALSCALINGBAR = 0,
	UIPROGRESSBARTYPE_TEXTUREMASKEDPROGRESS = 1,
};

const char *EnumToString( const EUIProgressBarType value );
const EUIProgressBarType StringToEnum_EUIProgressBarType( const char* value );

template <>
struct KnownEnum< EUIProgressBarType >
{
	enum { isKnown = 1 };
	enum { sizeOf = 2 };
	static const char *ToString( const EUIProgressBarType value ) { return EnumToString( value ); }
	static const EUIProgressBarType ToEnum( const char* value ) { return StringToEnum_EUIProgressBarType( value ); }
	static const EUIProgressBarType ToEnum( const string& value ) { return StringToEnum_EUIProgressBarType( value.c_str() ); }
	static const int SizeOf() { return 2; }
};

enum EUIRotationType
{
	UIROTATIONTYPE_CW = 0,
	UIROTATIONTYPE_CCW = 1,
};

const char *EnumToString( const EUIRotationType value );
const EUIRotationType StringToEnum_EUIRotationType( const char* value );

template <>
struct KnownEnum< EUIRotationType >
{
	enum { isKnown = 1 };
	enum { sizeOf = 2 };
	static const char *ToString( const EUIRotationType value ) { return EnumToString( value ); }
	static const EUIRotationType ToEnum( const char* value ) { return StringToEnum_EUIRotationType( value ); }
	static const EUIRotationType ToEnum( const string& value ) { return StringToEnum_EUIRotationType( value.c_str() ); }
	static const int SizeOf() { return 2; }
};

enum EUIScrollBarElementStyle
{
	UISCROLLBARELEMENTSTYLE_NORMAL = 0,
	UISCROLLBARELEMENTSTYLE_HILITED = 1,
	UISCROLLBARELEMENTSTYLE_PRESSED = 2,
	UISCROLLBARELEMENTSTYLE_DISABLED = 3,
};

const char *EnumToString( const EUIScrollBarElementStyle value );
const EUIScrollBarElementStyle StringToEnum_EUIScrollBarElementStyle( const char* value );

template <>
struct KnownEnum< EUIScrollBarElementStyle >
{
	enum { isKnown = 1 };
	enum { sizeOf = 4 };
	static const char *ToString( const EUIScrollBarElementStyle value ) { return EnumToString( value ); }
	static const EUIScrollBarElementStyle ToEnum( const char* value ) { return StringToEnum_EUIScrollBarElementStyle( value ); }
	static const EUIScrollBarElementStyle ToEnum( const string& value ) { return StringToEnum_EUIScrollBarElementStyle( value.c_str() ); }
	static const int SizeOf() { return 4; }
};

enum EUIScrollBarType
{
	UISCROLLBARTYPE_VERTICAL = 0,
	UISCROLLBARTYPE_HORIZONTAL = 1,
};

const char *EnumToString( const EUIScrollBarType value );
const EUIScrollBarType StringToEnum_EUIScrollBarType( const char* value );

template <>
struct KnownEnum< EUIScrollBarType >
{
	enum { isKnown = 1 };
	enum { sizeOf = 2 };
	static const char *ToString( const EUIScrollBarType value ) { return EnumToString( value ); }
	static const EUIScrollBarType ToEnum( const char* value ) { return StringToEnum_EUIScrollBarType( value ); }
	static const EUIScrollBarType ToEnum( const string& value ) { return StringToEnum_EUIScrollBarType( value.c_str() ); }
	static const int SizeOf() { return 2; }
};

enum EUITextEntryType
{
	UITEXTENTRYTYPE_FREE = 0,
	UITEXTENTRYTYPE_CONSOLE = 1,
	UITEXTENTRYTYPE_NUMERIC = 2,
	UITEXTENTRYTYPE_IDENTIFIER = 3,
	UITEXTENTRYTYPE_PLAYERNAME = 4,
};

const char *EnumToString( const EUITextEntryType value );
const EUITextEntryType StringToEnum_EUITextEntryType( const char* value );

template <>
struct KnownEnum< EUITextEntryType >
{
	enum { isKnown = 1 };
	enum { sizeOf = 5 };
	static const char *ToString( const EUITextEntryType value ) { return EnumToString( value ); }
	static const EUITextEntryType ToEnum( const char* value ) { return StringToEnum_EUITextEntryType( value ); }
	static const EUITextEntryType ToEnum( const string& value ) { return StringToEnum_EUITextEntryType( value.c_str() ); }
	static const int SizeOf() { return 5; }
};

enum EUITextHAlign
{
	UITEXTHALIGN_RIGHT = 0,
	UITEXTHALIGN_CENTER = 1,
	UITEXTHALIGN_LEFT = 2,
};

const char *EnumToString( const EUITextHAlign value );
const EUITextHAlign StringToEnum_EUITextHAlign( const char* value );

template <>
struct KnownEnum< EUITextHAlign >
{
	enum { isKnown = 1 };
	enum { sizeOf = 3 };
	static const char *ToString( const EUITextHAlign value ) { return EnumToString( value ); }
	static const EUITextHAlign ToEnum( const char* value ) { return StringToEnum_EUITextHAlign( value ); }
	static const EUITextHAlign ToEnum( const string& value ) { return StringToEnum_EUITextHAlign( value.c_str() ); }
	static const int SizeOf() { return 3; }
};

enum EUITextVAlign
{
	UITEXTVALIGN_TOP = 0,
	UITEXTVALIGN_CENTER = 1,
	UITEXTVALIGN_BOTTOM = 2,
};

const char *EnumToString( const EUITextVAlign value );
const EUITextVAlign StringToEnum_EUITextVAlign( const char* value );

template <>
struct KnownEnum< EUITextVAlign >
{
	enum { isKnown = 1 };
	enum { sizeOf = 3 };
	static const char *ToString( const EUITextVAlign value ) { return EnumToString( value ); }
	static const EUITextVAlign ToEnum( const char* value ) { return StringToEnum_EUITextVAlign( value ); }
	static const EUITextVAlign ToEnum( const string& value ) { return StringToEnum_EUITextVAlign( value.c_str() ); }
	static const int SizeOf() { return 3; }
};

struct UI3DOvertipDesc
{
public:
	Ptr< UILayout > layout;
	EUI3DOvertipMode mode;
	CVec2 worldSize;
	CVec2 align;
	float depthBias;

	UI3DOvertipDesc();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct UICatchEvents
{
public:
	bool mouseMove;
	bool leftMouseDown;
	bool rightMouseDown;
	bool leftMouseUp;
	bool rightMouseUp;
	bool leftDoubleClick;
	bool rightDoubleClick;

	UICatchEvents();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	bool operator==( const UICatchEvents &_uICatchEvents ) const { return IsEqual( _uICatchEvents ); }
	bool operator!=( const UICatchEvents &_uICatchEvents ) const { return !IsEqual( _uICatchEvents ); }
	bool IsEqual ( const UICatchEvents &_uICatchEvents ) const;

	UICatchEvents& operator = ( const UICatchEvents &_uICatchEvents ) { Assign( _uICatchEvents ); return *this; }
	UICatchEvents( const UICatchEvents &_uICatchEvents ) { Assign( _uICatchEvents ); }
	virtual void Assign( const UICatchEvents &_uICatchEvents );
};

struct UIConstant
{
public:
	string name;
	string value;
	string comment;

	UIConstant();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct UIContentGroup
{
public:
	string groupId;
	vector< Ptr< UIContentResource > > resources;
	string comment;

	UIContentGroup();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct UICursorDesc
{
public:
	string cursorId;
	Ptr< UICursorBase > cursor;
	Ptr< UICursorBase > cursorOverlay;
	CTPoint<int> cursorOverlayOffset;

	UICursorDesc();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct UICursors
{
public:
	string normal;
	string dragging;
	string dragable;
	string focused;
	string disabled;
	string pushing;
	string pushable;

	UICursors();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	bool operator==( const UICursors &_uICursors ) const { return IsEqual( _uICursors ); }
	bool operator!=( const UICursors &_uICursors ) const { return !IsEqual( _uICursors ); }
	bool IsEqual ( const UICursors &_uICursors ) const;

	UICursors& operator = ( const UICursors &_uICursors ) { Assign( _uICursors ); return *this; }
	UICursors( const UICursors &_uICursors ) { Assign( _uICursors ); }
	virtual void Assign( const UICursors &_uICursors );
};

struct UIFlashProperties
{
public:
	string propertyName;
	CTextRef propertyValue;

	UIFlashProperties();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	bool operator==( const UIFlashProperties &_uIFlashProperties ) const { return IsEqual( _uIFlashProperties ); }
	bool operator!=( const UIFlashProperties &_uIFlashProperties ) const { return !IsEqual( _uIFlashProperties ); }
	bool IsEqual ( const UIFlashProperties &_uIFlashProperties ) const;
};

struct UIHealthStripes
{
public:
	float stripe1Step;
	float stripe2Step;
	Render::HDRColor allyColor100;
	Render::HDRColor enemyColor100;
	Render::HDRColor allyColor1000;
	Render::HDRColor enemyColor1000;

	UIHealthStripes();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct UIPageTabElement
{
public:
	Ptr< UIRadioButtonLayout > button;
	Ptr< UIImageLabelLayout > page;

	UIPageTabElement();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	bool operator==( const UIPageTabElement &_uIPageTabElement ) const { return IsEqual( _uIPageTabElement ); }
	bool operator!=( const UIPageTabElement &_uIPageTabElement ) const { return !IsEqual( _uIPageTabElement ); }
	bool IsEqual ( const UIPageTabElement &_uIPageTabElement ) const;
};

struct UIPlainOvertipDesc
{
public:
	EUIOvertipBindPoint bindPoint;
	Ptr< UILayout > layout;
	bool useDepth;
	float depthBias;
	CTPoint<float> offset;

	UIPlainOvertipDesc();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct UIRelatedLayout
{
public:
	string id;
	Ptr< UILayout > layout;

	UIRelatedLayout();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	bool operator==( const UIRelatedLayout &_uIRelatedLayout ) const { return IsEqual( _uIRelatedLayout ); }
	bool operator!=( const UIRelatedLayout &_uIRelatedLayout ) const { return !IsEqual( _uIRelatedLayout ); }
	bool IsEqual ( const UIRelatedLayout &_uIRelatedLayout ) const;

	UIRelatedLayout& operator = ( const UIRelatedLayout &_uIRelatedLayout ) { Assign( _uIRelatedLayout ); return *this; }
	UIRelatedLayout( const UIRelatedLayout &_uIRelatedLayout ) { Assign( _uIRelatedLayout ); }
	virtual void Assign( const UIRelatedLayout &_uIRelatedLayout );
};

struct UIRelatedText
{
public:
	string id;
	CTextRef relatedText;
	string comment;

	UIRelatedText();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	bool operator==( const UIRelatedText &_uIRelatedText ) const { return IsEqual( _uIRelatedText ); }
	bool operator!=( const UIRelatedText &_uIRelatedText ) const { return !IsEqual( _uIRelatedText ); }
	bool IsEqual ( const UIRelatedText &_uIRelatedText ) const;

	UIRelatedText& operator = ( const UIRelatedText &_uIRelatedText ) { Assign( _uIRelatedText ); return *this; }
	UIRelatedText( const UIRelatedText &_uIRelatedText ) { Assign( _uIRelatedText ); }
	virtual void Assign( const UIRelatedText &_uIRelatedText );
};

struct UIScreenDesc
{
public:
	string screenId;
	Ptr< UIBaseLayout > baseLayout;
	string comment;

	UIScreenDesc();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct UIScriptDesc
{
public:
	string scriptFile;

	UIScriptDesc();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct UIScrollLimits
{
public:
	float inMin;
	float inMax;
	int outMin;
	int outMax;

	UIScrollLimits();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	bool operator==( const UIScrollLimits &_uIScrollLimits ) const { return IsEqual( _uIScrollLimits ); }
	bool operator!=( const UIScrollLimits &_uIScrollLimits ) const { return !IsEqual( _uIScrollLimits ); }
	bool IsEqual ( const UIScrollLimits &_uIScrollLimits ) const;
};

struct UISoundDesc
{
public:

	UISoundDesc();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct UIStyleAlias
{
public:
	string name;
	Ptr< BaseUIMaterial > material;

	UIStyleAlias();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct UITextSubstitute
{
public:
	string id;
	CTextRef captionText;

	UITextSubstitute();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct UICursorBase : public DbResource
{
	DBRESOURCE_METHODS( UICursorBase );
public:

	UICursorBase();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	UICursorBase& operator = ( const UICursorBase &_uICursorBase ) { Assign( _uICursorBase ); return *this; }
	UICursorBase( const UICursorBase &_uICursorBase ) { Assign( _uICursorBase ); }
	virtual void Assign( const UICursorBase &_uICursorBase );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const UICursorBase * pOther = dynamic_cast< const UICursorBase * > ( _pResource );
		if ( pOther ) UICursorBase::Assign( *pOther );
	}
};

struct UILayout : public DbResource
{
	DBRESOURCE_METHODS( UILayout );
protected:
	mutable DBResourceStateManager stateManager;
	virtual DBResourceStateManager* GetStatesManager() const { return &stateManager; }
public:
	string name;
	bool visible;
	bool enabled;
	CTPoint<float> location;
	CTPoint<float> size;
	EUIElementHAlign hAlign;
	EUIElementVAlign vAlign;
	EUIElementAspectRatio keepAspectRatio;
	string subclass;
	string scriptFile;
	UICursors cursors;
	vector< Ptr< UILayout > > subLayouts;
	bool draggable;
	UICatchEvents defaultEventsCatch;
	bool transparent;
	bool cursorTransparent;
	bool needCrop;
	vector< UIRelatedLayout > relatedLayouts;
	vector< UIRelatedText > relatedTexts;
	CTextRef tooltipText;
	DBFMODEventDesc soundShow;
	DBFMODEventDesc soundHide;
	DBFMODEventDesc soundActivate;

	UILayout();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	bool operator==( const UILayout &_uILayout ) const { return IsEqual( _uILayout ); }
	bool operator!=( const UILayout &_uILayout ) const { return !IsEqual( _uILayout ); }
	bool IsEqual ( const UILayout &_uILayout ) const;

	UILayout& operator = ( const UILayout &_uILayout ) { Assign( _uILayout ); return *this; }
	UILayout( const UILayout &_uILayout ) { Assign( _uILayout ); }
	virtual void Assign( const UILayout &_uILayout );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const UILayout * pOther = dynamic_cast< const UILayout * > ( _pResource );
		if ( pOther ) UILayout::Assign( *pOther );
	}
};

struct UIImageLabelLayout : public UILayout
{
	DBRESOURCE_METHODS( UIImageLabelLayout );
public:
	Ptr< BaseUIMaterial > backgroundMaterial;
	EImageLabelShapeType shapeType;
	CTextRef captionText;
	string fontStyle;
	bool wordWrap;
	bool stretchText;
	bool rawTextMode;
	EUITextVAlign textVAlign;
	EUITextHAlign textHAlign;
	CTRect<float> textMargins;
	float captionOpacity;

	UIImageLabelLayout();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	bool operator==( const UIImageLabelLayout &_uIImageLabelLayout ) const { return IsEqual( _uIImageLabelLayout ); }
	bool operator!=( const UIImageLabelLayout &_uIImageLabelLayout ) const { return !IsEqual( _uIImageLabelLayout ); }
	bool IsEqual ( const UIImageLabelLayout &_uIImageLabelLayout ) const;

	UIImageLabelLayout& operator = ( const UIImageLabelLayout &_uIImageLabelLayout ) { Assign( _uIImageLabelLayout ); return *this; }
	UIImageLabelLayout( const UIImageLabelLayout &_uIImageLabelLayout ) { Assign( _uIImageLabelLayout ); }
	virtual void Assign( const UIImageLabelLayout &_uIImageLabelLayout );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const UIImageLabelLayout * pOther = dynamic_cast< const UIImageLabelLayout * > ( _pResource );
		if ( pOther ) UIImageLabelLayout::Assign( *pOther );
	}
};

struct UICommonControl : public UIImageLabelLayout
{
	DBRESOURCE_METHODS( UICommonControl );
public:
	EUIControlMouseActions mouseActions;
	DBFMODEventDesc soundHilite;
	string activationBind;

	UICommonControl();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	bool operator==( const UICommonControl &_uICommonControl ) const { return IsEqual( _uICommonControl ); }
	bool operator!=( const UICommonControl &_uICommonControl ) const { return !IsEqual( _uICommonControl ); }
	bool IsEqual ( const UICommonControl &_uICommonControl ) const;

	UICommonControl& operator = ( const UICommonControl &_uICommonControl ) { Assign( _uICommonControl ); return *this; }
	UICommonControl( const UICommonControl &_uICommonControl ) { Assign( _uICommonControl ); }
	virtual void Assign( const UICommonControl &_uICommonControl );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const UICommonControl * pOther = dynamic_cast< const UICommonControl * > ( _pResource );
		if ( pOther ) UICommonControl::Assign( *pOther );
	}
};

struct UIButtonLayout : public UICommonControl
{
	DBRESOURCE_METHODS( UIButtonLayout );
public:
	Ptr< BaseUIMaterial > highlightMaterial;
	Ptr< BaseUIMaterial > pushedMaterial;
	Ptr< BaseUIMaterial > disabledMaterial;
	Ptr< BaseUIMaterial > flashedMaterial;
	EUIButtonViewMode viewMode;

	UIButtonLayout();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	bool operator==( const UIButtonLayout &_uIButtonLayout ) const { return IsEqual( _uIButtonLayout ); }
	bool operator!=( const UIButtonLayout &_uIButtonLayout ) const { return !IsEqual( _uIButtonLayout ); }
	bool IsEqual ( const UIButtonLayout &_uIButtonLayout ) const;

	UIButtonLayout& operator = ( const UIButtonLayout &_uIButtonLayout ) { Assign( _uIButtonLayout ); return *this; }
	UIButtonLayout( const UIButtonLayout &_uIButtonLayout ) { Assign( _uIButtonLayout ); }
	virtual void Assign( const UIButtonLayout &_uIButtonLayout );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const UIButtonLayout * pOther = dynamic_cast< const UIButtonLayout * > ( _pResource );
		if ( pOther ) UIButtonLayout::Assign( *pOther );
	}
};

struct UIContentResource : public DbResource
{
	DBRESOURCE_METHODS( UIContentResource );
public:
	string contentId;

	UIContentResource();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	UIContentResource& operator = ( const UIContentResource &_uIContentResource ) { Assign( _uIContentResource ); return *this; }
	UIContentResource( const UIContentResource &_uIContentResource ) { Assign( _uIContentResource ); }
	virtual void Assign( const UIContentResource &_uIContentResource );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const UIContentResource * pOther = dynamic_cast< const UIContentResource * > ( _pResource );
		if ( pOther ) UIContentResource::Assign( *pOther );
	}
};

struct UICursor : public UICursorBase
{
	DBRESOURCE_METHODS( UICursor );
public:
	Ptr< Texture > texture;
	int hotSpotX;
	int hotSpotY;

	UICursor();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	UICursor& operator = ( const UICursor &_uICursor ) { Assign( _uICursor ); return *this; }
	UICursor( const UICursor &_uICursor ) { Assign( _uICursor ); }
	virtual void Assign( const UICursor &_uICursor );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const UICursor * pOther = dynamic_cast< const UICursor * > ( _pResource );
		if ( pOther ) UICursor::Assign( *pOther );
	}
};

struct UIAnimatedCursor : public UICursorBase
{
	DBRESOURCE_METHODS( UIAnimatedCursor );
public:
	string srcFileName;
	string dstFileName;
	int frameCount;
	int fps;
	float delay;
	int hotSpotX;
	int hotSpotY;

	UIAnimatedCursor();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	UIAnimatedCursor& operator = ( const UIAnimatedCursor &_uIAnimatedCursor ) { Assign( _uIAnimatedCursor ); return *this; }
	UIAnimatedCursor( const UIAnimatedCursor &_uIAnimatedCursor ) { Assign( _uIAnimatedCursor ); }
	virtual void Assign( const UIAnimatedCursor &_uIAnimatedCursor );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const UIAnimatedCursor * pOther = dynamic_cast< const UIAnimatedCursor * > ( _pResource );
		if ( pOther ) UIAnimatedCursor::Assign( *pOther );
	}
};

struct UIEditBoxLayout : public UIImageLabelLayout
{
	DBRESOURCE_METHODS( UIEditBoxLayout );
public:
	Ptr< BaseUIMaterial > disabledMaterial;
	Ptr< BaseUIMaterial > cursorMaterial;
	int maxLength;
	bool isPassword;
	int maxLines;
	EUITextEntryType textEntryType;

	UIEditBoxLayout();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	bool operator==( const UIEditBoxLayout &_uIEditBoxLayout ) const { return IsEqual( _uIEditBoxLayout ); }
	bool operator!=( const UIEditBoxLayout &_uIEditBoxLayout ) const { return !IsEqual( _uIEditBoxLayout ); }
	bool IsEqual ( const UIEditBoxLayout &_uIEditBoxLayout ) const;

	UIEditBoxLayout& operator = ( const UIEditBoxLayout &_uIEditBoxLayout ) { Assign( _uIEditBoxLayout ); return *this; }
	UIEditBoxLayout( const UIEditBoxLayout &_uIEditBoxLayout ) { Assign( _uIEditBoxLayout ); }
	virtual void Assign( const UIEditBoxLayout &_uIEditBoxLayout );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const UIEditBoxLayout * pOther = dynamic_cast< const UIEditBoxLayout * > ( _pResource );
		if ( pOther ) UIEditBoxLayout::Assign( *pOther );
	}
};

struct UIFlashLayout : public UILayout
{
	DBRESOURCE_METHODS( UIFlashLayout );
public:
	string srcFileName;
	bool useScissorTest;
	bool useOwnSize;
	float triangulationError;
	vector< UIFlashProperties > properties;

	UIFlashLayout();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	bool operator==( const UIFlashLayout &_uIFlashLayout ) const { return IsEqual( _uIFlashLayout ); }
	bool operator!=( const UIFlashLayout &_uIFlashLayout ) const { return !IsEqual( _uIFlashLayout ); }
	bool IsEqual ( const UIFlashLayout &_uIFlashLayout ) const;

	UIFlashLayout& operator = ( const UIFlashLayout &_uIFlashLayout ) { Assign( _uIFlashLayout ); return *this; }
	UIFlashLayout( const UIFlashLayout &_uIFlashLayout ) { Assign( _uIFlashLayout ); }
	virtual void Assign( const UIFlashLayout &_uIFlashLayout );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const UIFlashLayout * pOther = dynamic_cast< const UIFlashLayout * > ( _pResource );
		if ( pOther ) UIFlashLayout::Assign( *pOther );
	}
};

struct UIFlashLayout2 : public UIFlashLayout
{
	DBRESOURCE_METHODS( UIFlashLayout2 );
public:

	UIFlashLayout2();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	bool operator==( const UIFlashLayout2 &_uIFlashLayout2 ) const { return IsEqual( _uIFlashLayout2 ); }
	bool operator!=( const UIFlashLayout2 &_uIFlashLayout2 ) const { return !IsEqual( _uIFlashLayout2 ); }
	bool IsEqual ( const UIFlashLayout2 &_uIFlashLayout2 ) const;

	UIFlashLayout2& operator = ( const UIFlashLayout2 &_uIFlashLayout2 ) { Assign( _uIFlashLayout2 ); return *this; }
	UIFlashLayout2( const UIFlashLayout2 &_uIFlashLayout2 ) { Assign( _uIFlashLayout2 ); }
	virtual void Assign( const UIFlashLayout2 &_uIFlashLayout2 );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const UIFlashLayout2 * pOther = dynamic_cast< const UIFlashLayout2 * > ( _pResource );
		if ( pOther ) UIFlashLayout2::Assign( *pOther );
	}
};

struct UIFontStyle : public DbResource
{
	DBRESOURCE_METHODS( UIFontStyle );
public:
	string styleName;
	bool drawContour;
	Render::HDRColor primaryColor;
	Render::HDRColor secondaryColor;
	RenderState renderState;
	string ttfFileName;
	string fontFamily;
	int fontSize;
	int lineGap;
	float additionalAdvance;
	float spaceScale;
	bool bold;
	bool italic;

	UIFontStyle();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	UIFontStyle& operator = ( const UIFontStyle &_uIFontStyle ) { Assign( _uIFontStyle ); return *this; }
	UIFontStyle( const UIFontStyle &_uIFontStyle ) { Assign( _uIFontStyle ); }
	virtual void Assign( const UIFontStyle &_uIFontStyle );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const UIFontStyle * pOther = dynamic_cast< const UIFontStyle * > ( _pResource );
		if ( pOther ) UIFontStyle::Assign( *pOther );
	}
};

struct UIHealthBarLayout : public UIImageLabelLayout
{
	DBRESOURCE_METHODS( UIHealthBarLayout );
public:
	Ptr< BaseUIMaterial > healthMaterial;
	Ptr< BaseUIMaterial > shieldMaterial;
	bool showShield;
	bool showStripes;

	UIHealthBarLayout();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	bool operator==( const UIHealthBarLayout &_uIHealthBarLayout ) const { return IsEqual( _uIHealthBarLayout ); }
	bool operator!=( const UIHealthBarLayout &_uIHealthBarLayout ) const { return !IsEqual( _uIHealthBarLayout ); }
	bool IsEqual ( const UIHealthBarLayout &_uIHealthBarLayout ) const;

	UIHealthBarLayout& operator = ( const UIHealthBarLayout &_uIHealthBarLayout ) { Assign( _uIHealthBarLayout ); return *this; }
	UIHealthBarLayout( const UIHealthBarLayout &_uIHealthBarLayout ) { Assign( _uIHealthBarLayout ); }
	virtual void Assign( const UIHealthBarLayout &_uIHealthBarLayout );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const UIHealthBarLayout * pOther = dynamic_cast< const UIHealthBarLayout * > ( _pResource );
		if ( pOther ) UIHealthBarLayout::Assign( *pOther );
	}
};

struct UICheckBoxLayout : public UICommonControl
{
	DBRESOURCE_METHODS( UICheckBoxLayout );
public:
	Ptr< BaseUIMaterial > highlightMaterial;
	Ptr< BaseUIMaterial > checkedMaterial;
	Ptr< BaseUIMaterial > highlightCheckedMaterial;
	Ptr< BaseUIMaterial > disabledMaterial;
	Ptr< BaseUIMaterial > disabledCheckedMaterial;

	UICheckBoxLayout();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	bool operator==( const UICheckBoxLayout &_uICheckBoxLayout ) const { return IsEqual( _uICheckBoxLayout ); }
	bool operator!=( const UICheckBoxLayout &_uICheckBoxLayout ) const { return !IsEqual( _uICheckBoxLayout ); }
	bool IsEqual ( const UICheckBoxLayout &_uICheckBoxLayout ) const;

	UICheckBoxLayout& operator = ( const UICheckBoxLayout &_uICheckBoxLayout ) { Assign( _uICheckBoxLayout ); return *this; }
	UICheckBoxLayout( const UICheckBoxLayout &_uICheckBoxLayout ) { Assign( _uICheckBoxLayout ); }
	virtual void Assign( const UICheckBoxLayout &_uICheckBoxLayout );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const UICheckBoxLayout * pOther = dynamic_cast< const UICheckBoxLayout * > ( _pResource );
		if ( pOther ) UICheckBoxLayout::Assign( *pOther );
	}
};

struct UIBaseLayout : public UILayout
{
	DBRESOURCE_METHODS( UIBaseLayout );
public:

	UIBaseLayout();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	bool operator==( const UIBaseLayout &_uIBaseLayout ) const { return IsEqual( _uIBaseLayout ); }
	bool operator!=( const UIBaseLayout &_uIBaseLayout ) const { return !IsEqual( _uIBaseLayout ); }
	bool IsEqual ( const UIBaseLayout &_uIBaseLayout ) const;

	UIBaseLayout& operator = ( const UIBaseLayout &_uIBaseLayout ) { Assign( _uIBaseLayout ); return *this; }
	UIBaseLayout( const UIBaseLayout &_uIBaseLayout ) { Assign( _uIBaseLayout ); }
	virtual void Assign( const UIBaseLayout &_uIBaseLayout );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const UIBaseLayout * pOther = dynamic_cast< const UIBaseLayout * > ( _pResource );
		if ( pOther ) UIBaseLayout::Assign( *pOther );
	}
};

struct UIObjectOvertips : public DbResource
{
	DBRESOURCE_METHODS( UIObjectOvertips );
public:
	vector< UIPlainOvertipDesc > plain;
	vector< UI3DOvertipDesc > threeDimensional;

	UIObjectOvertips();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	UIObjectOvertips& operator = ( const UIObjectOvertips &_uIObjectOvertips ) { Assign( _uIObjectOvertips ); return *this; }
	UIObjectOvertips( const UIObjectOvertips &_uIObjectOvertips ) { Assign( _uIObjectOvertips ); }
	virtual void Assign( const UIObjectOvertips &_uIObjectOvertips );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const UIObjectOvertips * pOther = dynamic_cast< const UIObjectOvertips * > ( _pResource );
		if ( pOther ) UIObjectOvertips::Assign( *pOther );
	}
};

struct UIPageTabControlLayout : public UIImageLabelLayout
{
	DBRESOURCE_METHODS( UIPageTabControlLayout );
public:
	vector< UIPageTabElement > tabs;

	UIPageTabControlLayout();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	bool operator==( const UIPageTabControlLayout &_uIPageTabControlLayout ) const { return IsEqual( _uIPageTabControlLayout ); }
	bool operator!=( const UIPageTabControlLayout &_uIPageTabControlLayout ) const { return !IsEqual( _uIPageTabControlLayout ); }
	bool IsEqual ( const UIPageTabControlLayout &_uIPageTabControlLayout ) const;

	UIPageTabControlLayout& operator = ( const UIPageTabControlLayout &_uIPageTabControlLayout ) { Assign( _uIPageTabControlLayout ); return *this; }
	UIPageTabControlLayout( const UIPageTabControlLayout &_uIPageTabControlLayout ) { Assign( _uIPageTabControlLayout ); }
	virtual void Assign( const UIPageTabControlLayout &_uIPageTabControlLayout );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const UIPageTabControlLayout * pOther = dynamic_cast< const UIPageTabControlLayout * > ( _pResource );
		if ( pOther ) UIPageTabControlLayout::Assign( *pOther );
	}
};

struct UIProgressBarLayout : public UIImageLabelLayout
{
	DBRESOURCE_METHODS( UIProgressBarLayout );
public:
	Ptr< BaseUIMaterial > progressMaterial;
	Ptr< BaseUIMaterial > rotationEffectMaterial;
	CTPoint<float> rotationEffectPivot;
	EUIRotationType effectRotationType;
	EUIProgressBarType progressBarType;
	int maskGradientItems;

	UIProgressBarLayout();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	bool operator==( const UIProgressBarLayout &_uIProgressBarLayout ) const { return IsEqual( _uIProgressBarLayout ); }
	bool operator!=( const UIProgressBarLayout &_uIProgressBarLayout ) const { return !IsEqual( _uIProgressBarLayout ); }
	bool IsEqual ( const UIProgressBarLayout &_uIProgressBarLayout ) const;

	UIProgressBarLayout& operator = ( const UIProgressBarLayout &_uIProgressBarLayout ) { Assign( _uIProgressBarLayout ); return *this; }
	UIProgressBarLayout( const UIProgressBarLayout &_uIProgressBarLayout ) { Assign( _uIProgressBarLayout ); }
	virtual void Assign( const UIProgressBarLayout &_uIProgressBarLayout );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const UIProgressBarLayout * pOther = dynamic_cast< const UIProgressBarLayout * > ( _pResource );
		if ( pOther ) UIProgressBarLayout::Assign( *pOther );
	}
};

struct UIRadioButtonLayout : public UICommonControl
{
	DBRESOURCE_METHODS( UIRadioButtonLayout );
public:
	Ptr< BaseUIMaterial > highlightMaterial;
	Ptr< BaseUIMaterial > selectedMaterial;
	Ptr< BaseUIMaterial > disabledMaterial;
	Ptr< BaseUIMaterial > disabledSelectedMaterial;
	Ptr< BaseUIMaterial > flashedMaterial;
	int group;

	UIRadioButtonLayout();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	bool operator==( const UIRadioButtonLayout &_uIRadioButtonLayout ) const { return IsEqual( _uIRadioButtonLayout ); }
	bool operator!=( const UIRadioButtonLayout &_uIRadioButtonLayout ) const { return !IsEqual( _uIRadioButtonLayout ); }
	bool IsEqual ( const UIRadioButtonLayout &_uIRadioButtonLayout ) const;

	UIRadioButtonLayout& operator = ( const UIRadioButtonLayout &_uIRadioButtonLayout ) { Assign( _uIRadioButtonLayout ); return *this; }
	UIRadioButtonLayout( const UIRadioButtonLayout &_uIRadioButtonLayout ) { Assign( _uIRadioButtonLayout ); }
	virtual void Assign( const UIRadioButtonLayout &_uIRadioButtonLayout );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const UIRadioButtonLayout * pOther = dynamic_cast< const UIRadioButtonLayout * > ( _pResource );
		if ( pOther ) UIRadioButtonLayout::Assign( *pOther );
	}
};

struct UIRadioPanelLayout : public UIImageLabelLayout
{
	DBRESOURCE_METHODS( UIRadioPanelLayout );
public:

	UIRadioPanelLayout();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	bool operator==( const UIRadioPanelLayout &_uIRadioPanelLayout ) const { return IsEqual( _uIRadioPanelLayout ); }
	bool operator!=( const UIRadioPanelLayout &_uIRadioPanelLayout ) const { return !IsEqual( _uIRadioPanelLayout ); }
	bool IsEqual ( const UIRadioPanelLayout &_uIRadioPanelLayout ) const;

	UIRadioPanelLayout& operator = ( const UIRadioPanelLayout &_uIRadioPanelLayout ) { Assign( _uIRadioPanelLayout ); return *this; }
	UIRadioPanelLayout( const UIRadioPanelLayout &_uIRadioPanelLayout ) { Assign( _uIRadioPanelLayout ); }
	virtual void Assign( const UIRadioPanelLayout &_uIRadioPanelLayout );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const UIRadioPanelLayout * pOther = dynamic_cast< const UIRadioPanelLayout * > ( _pResource );
		if ( pOther ) UIRadioPanelLayout::Assign( *pOther );
	}
};

struct UIRoot : public DbResource
{
	DBRESOURCE_METHODS( UIRoot );
public:
	vector< UIScreenDesc > screens;
	vector< UICursorDesc > cursors;
	vector< UIScriptDesc > scripts;
	vector< UIContentGroup > contents;
	vector< UIConstant > consts;
	vector< UITextSubstitute > substitutes;
	vector< UIStyleAlias > styleAliases;
	vector< Ptr< UIFontStyle > > fontStyles;
	Ptr< Preferences > preferences;
	Ptr< VotingForSurrender > votingForSurrender;
	UIHealthStripes healthStripes;

	UIRoot();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	UIRoot& operator = ( const UIRoot &_uIRoot ) { Assign( _uIRoot ); return *this; }
	UIRoot( const UIRoot &_uIRoot ) { Assign( _uIRoot ); }
	virtual void Assign( const UIRoot &_uIRoot );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const UIRoot * pOther = dynamic_cast< const UIRoot * > ( _pResource );
		if ( pOther ) UIRoot::Assign( *pOther );
	}
};

struct UIScrollableWindowLayout : public UILayout
{
	DBRESOURCE_METHODS( UIScrollableWindowLayout );
public:
	Ptr< UIScrollAreaLayout > scrollArea;
	Ptr< UIScrollBarLayout > scrollBar;

	UIScrollableWindowLayout();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	bool operator==( const UIScrollableWindowLayout &_uIScrollableWindowLayout ) const { return IsEqual( _uIScrollableWindowLayout ); }
	bool operator!=( const UIScrollableWindowLayout &_uIScrollableWindowLayout ) const { return !IsEqual( _uIScrollableWindowLayout ); }
	bool IsEqual ( const UIScrollableWindowLayout &_uIScrollableWindowLayout ) const;

	UIScrollableWindowLayout& operator = ( const UIScrollableWindowLayout &_uIScrollableWindowLayout ) { Assign( _uIScrollableWindowLayout ); return *this; }
	UIScrollableWindowLayout( const UIScrollableWindowLayout &_uIScrollableWindowLayout ) { Assign( _uIScrollableWindowLayout ); }
	virtual void Assign( const UIScrollableWindowLayout &_uIScrollableWindowLayout );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const UIScrollableWindowLayout * pOther = dynamic_cast< const UIScrollableWindowLayout * > ( _pResource );
		if ( pOther ) UIScrollableWindowLayout::Assign( *pOther );
	}
};

struct UIScrollAreaLayout : public UILayout
{
	DBRESOURCE_METHODS( UIScrollAreaLayout );
public:
	string handleMsgForXScroll;
	string handleMsgForYScroll;
	UIScrollLimits scrollXLimits;
	UIScrollLimits scrollYLimits;
	string spawnMsgOnLimitsChanged;

	UIScrollAreaLayout();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	bool operator==( const UIScrollAreaLayout &_uIScrollAreaLayout ) const { return IsEqual( _uIScrollAreaLayout ); }
	bool operator!=( const UIScrollAreaLayout &_uIScrollAreaLayout ) const { return !IsEqual( _uIScrollAreaLayout ); }
	bool IsEqual ( const UIScrollAreaLayout &_uIScrollAreaLayout ) const;

	UIScrollAreaLayout& operator = ( const UIScrollAreaLayout &_uIScrollAreaLayout ) { Assign( _uIScrollAreaLayout ); return *this; }
	UIScrollAreaLayout( const UIScrollAreaLayout &_uIScrollAreaLayout ) { Assign( _uIScrollAreaLayout ); }
	virtual void Assign( const UIScrollAreaLayout &_uIScrollAreaLayout );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const UIScrollAreaLayout * pOther = dynamic_cast< const UIScrollAreaLayout * > ( _pResource );
		if ( pOther ) UIScrollAreaLayout::Assign( *pOther );
	}
};

struct UIScrollBarLayout : public UILayout
{
	DBRESOURCE_METHODS( UIScrollBarLayout );
public:
	EUIScrollBarType scrollBarType;
	int discretePositionsCount;
	EUIDiscreteType discreteType;
	string spawnMsgOnScrolled;
	Ptr< BaseUIMaterial > leverAreaMaterial;
	Ptr< BaseUIMaterial > leverAreaDisabledMaterial;
	vector< Ptr< BaseUIMaterial > > leverMaterials;
	vector< Ptr< BaseUIMaterial > > firstButtonMaterials;
	vector< Ptr< BaseUIMaterial > > secondButtonMaterials;
	int leverSize;
	int firstButtonSize;
	int secondButtonSize;

	UIScrollBarLayout();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	bool operator==( const UIScrollBarLayout &_uIScrollBarLayout ) const { return IsEqual( _uIScrollBarLayout ); }
	bool operator!=( const UIScrollBarLayout &_uIScrollBarLayout ) const { return !IsEqual( _uIScrollBarLayout ); }
	bool IsEqual ( const UIScrollBarLayout &_uIScrollBarLayout ) const;

	UIScrollBarLayout& operator = ( const UIScrollBarLayout &_uIScrollBarLayout ) { Assign( _uIScrollBarLayout ); return *this; }
	UIScrollBarLayout( const UIScrollBarLayout &_uIScrollBarLayout ) { Assign( _uIScrollBarLayout ); }
	virtual void Assign( const UIScrollBarLayout &_uIScrollBarLayout );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const UIScrollBarLayout * pOther = dynamic_cast< const UIScrollBarLayout * > ( _pResource );
		if ( pOther ) UIScrollBarLayout::Assign( *pOther );
	}
};

struct UIScrollListLayout : public UIScrollAreaLayout
{
	DBRESOURCE_METHODS( UIScrollListLayout );
public:
	EUIListItemsPlacingOrigin placingOrigin;
	EUIListItemsPlacingOrder placingOrder;
	CTPoint<float> minItemSize;
	CTPoint<float> maxItemSize;
	int maxItemsTotal;
	int maxStrideItems;
	Ptr< BaseUIMaterial > hilightMaterial;
	Ptr< BaseUIMaterial > preselectMaterial;
	Ptr< BaseUIMaterial > selectionMaterial;
	string spawnMsgOnItemHighlighted;
	string spawnMsgOnItemSelected;

	UIScrollListLayout();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	bool operator==( const UIScrollListLayout &_uIScrollListLayout ) const { return IsEqual( _uIScrollListLayout ); }
	bool operator!=( const UIScrollListLayout &_uIScrollListLayout ) const { return !IsEqual( _uIScrollListLayout ); }
	bool IsEqual ( const UIScrollListLayout &_uIScrollListLayout ) const;

	UIScrollListLayout& operator = ( const UIScrollListLayout &_uIScrollListLayout ) { Assign( _uIScrollListLayout ); return *this; }
	UIScrollListLayout( const UIScrollListLayout &_uIScrollListLayout ) { Assign( _uIScrollListLayout ); }
	virtual void Assign( const UIScrollListLayout &_uIScrollListLayout );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const UIScrollListLayout * pOther = dynamic_cast< const UIScrollListLayout * > ( _pResource );
		if ( pOther ) UIScrollListLayout::Assign( *pOther );
	}
};

struct UITexture : public Texture
{
	DBRESOURCE_METHODS( UITexture );
public:
	bool importOnlyShape;
	int shapeAlphaThreshold;
	string shapeFileName;

	UITexture();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	UITexture& operator = ( const UITexture &_uITexture ) { Assign( _uITexture ); return *this; }
	UITexture( const UITexture &_uITexture ) { Assign( _uITexture ); }
	virtual void Assign( const UITexture &_uITexture );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const UITexture * pOther = dynamic_cast< const UITexture * > ( _pResource );
		if ( pOther ) UITexture::Assign( *pOther );
	}

#ifndef VISUAL_CUTTED
	virtual CObj<Render::Texture> Load() const;
	virtual CObj<Render::Texture> LoadInPool( bool canBeVisualDegrade, void * texturePoolId ) const;
#endif // #ifndef VISUAL_CUTTED
};

struct UIViewLayout : public UILayout
{
	DBRESOURCE_METHODS( UIViewLayout );
public:
	string provider;
	string address;
	int framesPerSecond;

	UIViewLayout();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	bool operator==( const UIViewLayout &_uIViewLayout ) const { return IsEqual( _uIViewLayout ); }
	bool operator!=( const UIViewLayout &_uIViewLayout ) const { return !IsEqual( _uIViewLayout ); }
	bool IsEqual ( const UIViewLayout &_uIViewLayout ) const;

	UIViewLayout& operator = ( const UIViewLayout &_uIViewLayout ) { Assign( _uIViewLayout ); return *this; }
	UIViewLayout( const UIViewLayout &_uIViewLayout ) { Assign( _uIViewLayout ); }
	virtual void Assign( const UIViewLayout &_uIViewLayout );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const UIViewLayout * pOther = dynamic_cast< const UIViewLayout * > ( _pResource );
		if ( pOther ) UIViewLayout::Assign( *pOther );
	}
};

}; // namespace NDb
