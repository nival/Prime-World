#include "Stdafx.h"

#include "Root.h"

#include "Cursor.h"
#include "FontRender.h"
#include "SkinStyles.h"
#include "Scripts.h"
#include "DebugVarsRender.h"

#include "Render/UIRenderer.h"
#include "Flash/GameSWFIntegration/FlashPlayer.h"
#include "Render/FlashRendererInterface.h"
#include "Render/Material.h"
#include "Scripts/Script.h"
#include "User.h"
#include "Resolution.h"
#include "FontStyle.h"

namespace
{
static bool initialized = false;

Strong<UI::User> g_user;

DECLARE_NULL_RENDER_FLAG
}



namespace UI
{

NDb::Ptr<NDb::UIRoot> g_rootHolder;


const NDb::UIRoot *GetUIRoot()
{
  return g_rootHolder.GetPtr();
}

void SetUIRoot( const NDb::UIRoot *pRoot )
{
	g_rootHolder = pRoot;
}

typedef hash_map<string,NDb::Ptr<NDb::UIBaseLayout> > TUIScreens;
TUIScreens g_screens;

struct UIMaterialPreloader : public NDb::IResourcesProcessor
{
  virtual bool Call( const NDb::DBID& dbid, const NDb::DbResource* pResource )
  {
    const NDb::UIBaseLayout* baseLayout = dynamic_cast<const NDb::UIBaseLayout*>( pResource );

    if ( baseLayout )
    {
      AddScriptFile( baseLayout->scriptFile );
    }

    const NDb::Material* material = dynamic_cast<const NDb::Material*>( pResource );

    if ( material )
    {
      Render::Material* renderMaterial = Render::CreateRenderMaterial( material );
      delete renderMaterial;
      return false;
    }

    const NDb::Texture* dbTexture = dynamic_cast<const NDb::Texture *>( pResource );

    if ( dbTexture )
    {
      CObj<Render::Texture> texture = dbTexture->Load();
      texture = 0;
    }

    const NDb::UIImageLabelLayout* dbImageLayout = dynamic_cast<const NDb::UIImageLabelLayout *>( pResource ); 

    if ( dbImageLayout )
    {
      const NDb::UIFontStyle* dbFontStyle = SkinStyles::GetFontStyle( dbImageLayout->fontStyle );

      if ( dbFontStyle && ( dbFontStyle->fontSize > 0 ) )
      {
        Strong<UI::FontStyle> fontStyle = new UI::FontStyle( dbFontStyle );
      }
    }

    return true;
  }

  virtual bool LoadResources() { return true; }
};


const NDb::UIBaseLayout *GetScreenLayout( const string & screenId )
{
	TUIScreens::iterator it = g_screens.find( screenId );
	
  if ( it == g_screens.end() )
		return 0;

  if ( !it->second.GetRawResourcePtr()->NeedReload() )
    return it->second;

  NDb::Ptr<NDb::UIBaseLayout> layout = NDb::Precache<NDb::UIBaseLayout>( it->second.GetRawResourcePtr()->GetDBID(), 30 );

  UIMaterialPreloader preloadFunctor;
  layout.Traverse( 100, &preloadFunctor );

  it->second = layout;
  return layout;
}


void SetCursor( const string & cursorId )
{
	NCursors::Select( cursorId, 0 ); //IREF
}


void FreezeCursor( bool freeze )
{
	NCursor::Freeze( freeze );
}


typedef hash_map<string,NDb::Ptr<NDb::UIContentResource> > TUIContentMap;
typedef hash_map<string,TUIContentMap> TUIContents;
TUIContents g_contents;


const NDb::UIContentResource *GetContentResource( const string & groupId, const string & contentId )
{
	TUIContents::const_iterator it = g_contents.find( groupId );
	if ( it == g_contents.end() )
		return 0;
	const TUIContentMap & contentMap = it->second;
	TUIContentMap::const_iterator it2 = contentMap.find( contentId );
	if ( it2 == contentMap.end() )
		return 0;
	return it2->second.GetPtr();
}


struct SUIConstValue { string s; int n; float f; bool b; };
typedef hash_map<string,SUIConstValue> TUIConsts;
TUIConsts g_consts;


const string & GetConstant( const string & constId )
{
	static string empty;
	TUIConsts::const_iterator it = g_consts.find( constId );
	NI_VERIFY( it != g_consts.end(), NStr::StrFmt( "UIRoot: Constant does not exist! (%s)", constId.c_str() ), return empty );
	return it->second.s;
}


const int GetIntConstant( const string & constId )
{
	TUIConsts::const_iterator it = g_consts.find( constId );
	NI_VERIFY( it != g_consts.end(), NStr::StrFmt( "UIRoot: Constant does not exist! (%s)", constId.c_str() ), return 0 );
	return it->second.n;
}


const float GetFloatConstant( const string & constId )
{
	TUIConsts::const_iterator it = g_consts.find( constId );
	NI_VERIFY( it != g_consts.end(), NStr::StrFmt( "UIRoot: Constant does not exist! (%s)", constId.c_str() ), return 0.0f );
	return it->second.f;
}


const bool GetBoolConstant( const string & constId )
{
	TUIConsts::const_iterator it = g_consts.find( constId );
	NI_VERIFY( it != g_consts.end(), NStr::StrFmt( "UIRoot: Constant does not exist! (%s)", constId.c_str() ), return false );
	return it->second.b;
}


typedef map<wstring, wstring> TTextSubsts;
static TTextSubsts s_textSubsts;

static const wchar_t * s_ALPHANUM = L"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

void SubstituteTextImpl( wstring & result, const wchar_t * source, ICustomSubstitutes * customSubsts, int depth )
{
  const wchar_t * src = source;
  while( true )
  {
    const wchar_t * open = wcsstr( src, L"$(" );
    if( !open )
    {
      result.append( src );
      return;
    }

    size_t count = open - src;
    result.append( src, src + count );

    const wchar_t * tag = open + 2;

    size_t tagLen = wcsspn( tag, s_ALPHANUM );

    if( tag[tagLen] == L')' )
    {
      wstring id( tag, tagLen );

      TTextSubsts::iterator it = s_textSubsts.find( id );

      src = tag + tagLen + 1;

      NI_DATA_VERIFY( depth <= 10, NStr::StrFmt( "String substitute '%S' depth exceeded. Source text was '%S'", id.c_str(), source ), result = src; return );

      if( it != s_textSubsts.end() )
      {
        wstring tmp;
        SubstituteTextImpl( tmp, it->second.c_str(), customSubsts, depth + 1 );
        result += tmp;
        continue;
      }

      if ( customSubsts )
      {
        const wstring * subst = customSubsts->GetSubstitute( id );
        if ( subst )
        {
          wstring tmp;
          SubstituteTextImpl( tmp, subst->c_str(), customSubsts, depth + 1 );
          result += tmp;
          continue;
        }
      }

      result.append( open, src );
      continue;
    }

    //wrong tag format or tag not found
    src = tag + tagLen;
    result.append( open, src );
  }
}



void SubstituteText( wstring & result, const wchar_t * source, ICustomSubstitutes * customSubsts )
{
  SubstituteTextImpl( result, source, customSubsts, 0 );
}



void ApplyNewParams( unsigned long width, unsigned long height, bool isFullScreen )
{
  UpdateScreenResolution( width, height, false );
}


DWORD g_syncTime = 0;


DWORD GetSyncTime()
{
	return g_syncTime;
}



User * GetUser()
{
  return g_user;
}



void NewFrame( DWORD time )
{
	g_syncTime = time;
	NCursors::Reset();
}


void PresentFrame( DWORD time, bool active )
{
  NCursor::Update( time );

	if ( active )
		NCursor::Render();
}


void Release()
{
  Initialize(0); // clean up, IREF
}

#pragma code_seg(push, "~")

//Re-init supported
//Not really, already...
void Initialize( const NDb::UIRoot *pRoot )
{
  STARFORCE_STOPWATCH();

  PushDXPoolGuard dxPool("UI");

  g_user = 0;

  flash::ReleaseFlash();

  // Clean up
  NCursors::Release();
  NCursor::Release();
  NDebug::Release();

  if ( initialized )
    UI::GetFontRenderer()->Release();
  //UI::Scripts::ClearScripts();

  g_screens.clear();
  g_contents.clear();
  g_consts.clear();

  UI::SkinStyles::ReleaseAliases();

  // Set root
  g_rootHolder = pRoot;
  if ( !pRoot )
    return;

  if ( pRoot )
  {
    UI::GetFontRenderer()->Initialize();
    initialized = true;
  }

  NDebug::Initialize();

  // Screens
  for ( int i = 0; i < pRoot->screens.size(); ++i )
  {
    const string & screenId = pRoot->screens[i].screenId;
    NDb::Ptr<NDb::UIBaseLayout> pLayout = pRoot->screens[i].baseLayout;
    NI_VERIFY( !screenId.empty(), NStr::StrFmt( "UIRoot: Empty screen ID! (#%d)", i ), continue );
    NI_VERIFY( g_screens.find( screenId ) == g_screens.end(), NStr::StrFmt( "UIRoot: Screen ID (%s) already registered! (#%d)", screenId.c_str(), i ), continue );
    NI_VERIFY( !pLayout.IsEmpty(), NStr::StrFmt( "UIRoot: Null screen with ID (%s) in list! (#%d)", screenId.c_str(), i ), continue );
    g_screens[ screenId ] = pLayout;
  }

  // Cursors
  for ( int i = 0; i < pRoot->cursors.size(); ++i )
  {
    const string & cursorId = pRoot->cursors[i].cursorId;
    NI_VERIFY( !cursorId.empty(), NStr::StrFmt( "UIRoot: Empty cursor ID! (#%d)", i ), continue );

    const NDb::UICursorBase *pCursor = pRoot->cursors[i].cursor.GetPtr();
    const NDb::UICursorBase *pCursorOverlay = pRoot->cursors[i].cursorOverlay.GetPtr();
    const CTPoint<int> cursorOverlayOffset = pRoot->cursors[i].cursorOverlayOffset;

    NCursor::Image cursor;
    NCursor::Image overlay;

    if ( !cursor.Load( pCursor ) )
      continue;
    if ( overlay.Load( pCursorOverlay ) )
      cursor.Blit( cursorOverlayOffset.x, cursorOverlayOffset.y, overlay, 0,0 );

    if ( cursorId == "default" ) //IREF
      NCursor::SetDefault( &cursor ); //IREF

    NCursors::Register( cursorId, &cursor );
  }

  // Style aliases
  UI::SkinStyles::InitAliases( pRoot );

  // Scripts
  for ( int i = 0; i < pRoot->scripts.size(); ++i )
  {
    //UI::Scripts::RegisterScript( pRoot->scripts[i].scriptFile );
  }

  // Contents
  for( int i = 0; i < pRoot->contents.size(); ++i )
  {
    const string & groupId = pRoot->contents[i].groupId;
    NI_VERIFY( !groupId.empty(), NStr::StrFmt( "UIRoot: Empty content group ID! (#%d)", i ), continue );
    NI_VERIFY( g_contents.find( groupId ) == g_contents.end(), NStr::StrFmt( "UIRoot: Content group (%s) already registered! (#%d)", groupId, i ), continue );
    g_contents[ groupId ] = TUIContentMap();
    TUIContentMap & contentMap = g_contents[ groupId ];
    const vector<NDb::Ptr<NDb::UIContentResource> > resources = pRoot->contents[i].resources;
    for ( int j = 0; j < resources.size(); ++j )
    {
      NDb::Ptr<NDb::UIContentResource> pResource = resources[j];
      NI_VERIFY( !pResource.IsEmpty(), NStr::StrFmt( "Null content resource in content group (%s)! (#%d/%d)", groupId, i,j ), continue );
      const string & contentId = resources[j]->contentId;
      NI_VERIFY( !contentId.empty(), NStr::StrFmt( "UIRoot: Empty content resource ID in content group (%s)! (#%d/%d)", groupId, i,j ), continue );
      NI_VERIFY( contentMap.find( contentId ) == contentMap.end(), NStr::StrFmt( "UIRoot: Content resource (%s) already registered in content group (%s)! (#%d/%d)", contentId, groupId, i,j ), continue );
      contentMap[ contentId ] = pResource;
    }
  }

  // Constants
  for( int i = 0; i < pRoot->consts.size(); ++i )
  {
    const string & constId = pRoot->consts[i].name;
    NI_VERIFY( !constId.empty(), NStr::StrFmt( "UIRoot: Empty constant ID! (#%d)", i ), continue );
    NI_VERIFY( g_consts.find( constId ) == g_consts.end(), NStr::StrFmt( "UIRoot: Constant (%s) already registered! (#%d)", constId, i ), continue );

    const string & constValue = pRoot->consts[i].value;

    SUIConstValue val;
    val.s = constValue;
    val.n = atoi(val.s.c_str());
    val.f = atof(val.s.c_str());
    val.b = ( val.s == "true" );

    g_consts[ constId ] = val;
  }

  //Text substitutes
  s_textSubsts.clear();
  for ( int i = 0; i < pRoot->substitutes.size(); ++i )
  {
    wstring id = NStr::ToUnicode( pRoot->substitutes[i].id );
    s_textSubsts[id] = pRoot->substitutes[i].captionText.GetText();
  }

  // Startup
  UI::GetUIScript()->RegisterGlobals(); //IREF
  NCursor::Init(); //IREF

  flash::InitializeFlash();

  // Create User object
  g_user = new UI::User;
}

#pragma code_seg(pop)

}
