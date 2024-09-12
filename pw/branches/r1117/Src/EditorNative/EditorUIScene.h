#pragma once
#include "../UI/Window.h"
#include "Editor2DSceneBase.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace EditorNative
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
public ref class EditorUIScene sealed : public Editor2DSceneBase
{
private:
	Weak<UI::Window> * pRootLayout;
  Strong<UI::ScreenLogicBase> * pScreenLogic;

protected:
  virtual void DrawInternal( System::IntPtr hWnd, int width, int height ) override;

internal:
	property UI::Window* RootLayout { UI::Window* get(); }

public:
  typedef System::Collections::Generic::List<libdb::DB::DBID^> TWindowsDbList;

	EditorUIScene( System::IntPtr hWnd );
	~EditorUIScene();
	!EditorUIScene();

  void LoadLayout( libdb::DB::DBID^ dbId, System::String^ stateName );
  TWindowsDbList^ PickWindows( int x, int y );
  TWindowsDbList^ PickWindows( System::Drawing::Rectangle area );
  System::Drawing::Rectangle GetWindowScreenPosition( libdb::DB::DBID^ wnd );
  libdb::DB::DBID^ GetWindowParent( libdb::DB::DBID^ wnd );
  void SetVisible( libdb::DB::DBID^ wnd, bool visible );
  void SetState( libdb::DB::DBID^ wnd, System::String^ stateName );
  System::String^ GetState( libdb::DB::DBID^ wnd );

  System::Collections::Generic::List<System::Drawing::Rectangle>^ GetAllWindowBounds();

  static System::Collections::Generic::List<System::String^>^ GetFlashPublicFields( System::String^ source );

  static void StoreTextsCache( System::String^ fileName );
  static int StoreTextsCache( System::String^ fileName, System::Collections::Generic::List<System::String^>^ textFiles );

private:
  UI::Window * FindWindow( libdb::DB::DBID^ wnd );
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}