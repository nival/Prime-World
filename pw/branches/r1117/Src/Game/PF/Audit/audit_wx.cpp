#include "stdafx.h"

#include "audit_wx.h"
#include "audit.xpm"

#include "../System/SyncProcessorState.h"
#include "../System/HPTimer.h"
#include "../System/meminfo.h"
#include "../System/WinFileSystem.h"
#include "../System/LogFileName.h"

#include "../Core/CoreFSM.h"
#include "../Core/MessagesLobby.h"
#include "../Core/MessagesInGame.h"

#include "../PF_GameLogic/PFWorld.h"
#include "../Core/StateInGameSingle.h"

#include "../PF_GameLogic/MapStartup.hpp"
#include "../PF_GameLogic/DBUnit.h"

#include "../PF_GameLogic/PFDispatch.h"
#include "../PF_GameLogic/PFApplicator.h"
#include "../PF_GameLogic/PFLogicObject.h"
#include "../PF_GameLogic/PFLogicDebug.h"


#include "../WorldDraw/WorldDraw.h"


#include "SceneStub.h"
#include "audit.h"

// ************************************************************************************

#define   KEYBOARD_SHIFT_DIST   16.0f


// ************************************************************************************

static WorldDraw::RenderOpenGL              s_glRender;
static CObj<AuditCore::AuditCore>           s_audit = new AuditCore::AuditCore();


// ************************************************************************************

IMPLEMENT_APP(AuditApp)

bool AuditApp::OnInit()
{
  NDebug::SetProductNameAndVersion( "PFAudit", "PRIVATE", 0, 0, 0, 0 );

  // Create the main application window
  AuditFrame *frame = new AuditFrame(_T("PF-Audit"),wxPoint(10, 50), wxSize(1000, 790)    );
  frame->Show(true);
  // success: wxApp::OnRun() will be called which will enter the main message
  // loop and the application will run. If we returned false here, the
  // application would exit immediately.
  return true;
}

AuditApp::~AuditApp()
{
  s_audit->Close();
}

// ************************************************************************************
BEGIN_EVENT_TABLE(AuditFrame, wxFrame)

EVT_MENU(Audit_File_Quit,  AuditFrame::OnQuit)
EVT_MENU(Audit_File_About, AuditFrame::OnAbout)

//EVT_UPDATE_UI(Calendar_Cal_Year, AuditFrame::OnAllowYearUpdate)

END_EVENT_TABLE()

AuditFrame::AuditFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
: wxFrame((wxFrame *)NULL, wxID_ANY, title, pos, size)
{
  // set the frame icon
  SetIcon(wxIcon(audit_xpm));

  // create a menu bar
  wxMenu *menuFile = new wxMenu;
  menuFile->Append(Audit_File_About, _T("&About...\tCtrl-A"), _T("Show about dialog"));
  menuFile->AppendSeparator();
  menuFile->Append(Audit_File_Quit, _T("E&xit\tAlt-X"), _T("Quit this program"));

  /*
  wxMenu *menuCal = new wxMenu;
  menuCal->Append(Calendar_Cal_Monday,
    _T("Monday &first weekday\tCtrl-F"),
    _T("Toggle between Mon and Sun as the first week day"),
    true);
  */
      
  // now append the freshly created menu to the menu bar...
  wxMenuBar *menuBar = new wxMenuBar;
  menuBar->Append(menuFile, _T("&File"));
  //menuBar->Append(menuCal, _T("&Calendar"));

  // ... and attach this menu bar to the frame
  SetMenuBar(menuBar);
  
  wxStatusBar *statBar = new wxStatusBar(this);
  SetStatusBar(statBar);
  SetStatusText("Loading...");

  m_panel = new AuditPanel(this);
}

void AuditFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
  // true is to force the frame to close
  Close(true);
}
static const char *s_aboutMessage = 
_T("Primal Forces Audit Application\n\n\
Keys:\n\n\
H - Show Height Map\n\
V - Show War Fog\n\
W - Map shift up\n\
S - Map shift down\n\
A - Map shift left\n\
D - Map shift right\n\
\n\
PF-Audit is OpenGL based application for Windows & Linux platform.\n\
It allowed to play game replays\n\
with simple 2d map graphics\n\
and track what happends during game session.\n\
(c) 2009 Driver-Inter / Nival Entertainment\n\
Vlad Shubnikov");

void AuditFrame::OnAbout(wxCommandEvent& WXUNUSED(event))
{
  wxMessageBox(s_aboutMessage,
    _T("About PF-Audit"), wxOK | wxICON_INFORMATION, this);
}

// *******************************************************************************************************************
BEGIN_EVENT_TABLE(AuditCanvas, wxGLCanvas)

  EVT_SIZE(               AuditCanvas::OnSize)
  EVT_PAINT(              AuditCanvas::OnPaint)
  EVT_ERASE_BACKGROUND(   AuditCanvas::OnEraseBackground)
  
  EVT_KEY_DOWN(           AuditCanvas::OnKeyDown )


  EVT_LEFT_DOWN(          AuditCanvas::OnMouseLeftDown )
  EVT_LEFT_UP(            AuditCanvas::OnMouseLeftUp )
  EVT_MOTION(             AuditCanvas::OnMouseMotion )
  EVT_MOUSEWHEEL(         AuditCanvas::OnMouseWheel)

  EVT_RIGHT_DOWN(         AuditCanvas::OnMouseRightDown )
  
  EVT_IDLE(               AuditCanvas::OnIdle)
  


END_EVENT_TABLE()


AuditCanvas::AuditCanvas(
                          wxWindow *parent, 
                          wxWindowID id,
                          const wxPoint& pos, 
                          const wxSize& size, 
                          long style, 
                          const wxString& name
                         )
: wxGLCanvas(parent, (wxGLCanvas*) NULL, id, pos, size, style|wxFULL_REPAINT_ON_RESIZE , name )
{
  m_initGL    = false;
  m_initWorld = false;
  m_inLoading = false;
  m_mousePressed = 0;
  m_mousePrevX = -1;
  m_auditPanel  = NULL;
  m_parentFrame = NULL;
  m_textBuffer[0] = 0;
}
AuditCanvas::~AuditCanvas()
{
}

void AuditCanvas::OnIdle(wxIdleEvent& WXUNUSED(evt))
{
  int   ok;
  if (!m_initWorld)
  {
    m_initWorld = true;
    m_inLoading = true;
    SetCursor(wxCURSOR_WAIT);
    {
      wxBusyInfo dialogBusy("Loading world. Please wait ...", this);
      ok = s_audit->Open();
      //ok = s_audit.Open( "c:/1" );
    }
    if (ok != 0)
    {
      wxMessageDialog dialogMsg(this, wxString("Error loading world"), wxString("ERROR"),wxOK );
      dialogMsg.ShowModal();
      m_parentFrame->Destroy();
      return;
    }    
    m_parentFrame->SetStatusText(wxString("First updates..."));
    return;
  }


  if (s_audit->Update() == false)
  {
    wxMessageDialog dialogMsg(this, wxString("Game session is finished"), wxString("GAME OVER"),wxOK );
    dialogMsg.ShowModal();
    m_parentFrame->Destroy();
    return;
  }
  else
    Refresh(false);
}

void AuditCanvas::OnPaint( wxPaintEvent& WXUNUSED(evt) )
{
  Render();
}
void AuditCanvas::OnSize(wxSizeEvent& event)
{
  // this is also necessary to update the context on some platforms
  wxGLCanvas::OnSize(event);

  // set GL viewport (not called by wxGLCanvas::OnSize on all platforms...)
  int w, h;
  GetClientSize(&w, &h);
  if (GetContext())
  {
    SetCurrent();
    s_glRender.Resize(w, h);
  }
}
void AuditCanvas::OnEraseBackground(wxEraseEvent& WXUNUSED(event))
{
  // Do nothing, to avoid flashing.
}

void  AuditCanvas::OnKeyDown(wxKeyEvent& evt)
{
  int code = evt.GetKeyCode();
  wxCheckBox    *checkBox = NULL;
  if (code == 'h' || code == 'H')
  {
    checkBox = m_auditPanel->GetCheckHeightMap();
    bool state = !checkBox->IsChecked();
    checkBox->SetValue(state);
    WorldDraw::VisualSettings *set = s_glRender.GetSettings();
    set->m_showHeightMap = state;
  }
  if (code == 'v' || code == 'V')
  {
    checkBox = m_auditPanel->GetCheckWarFog();
    bool state = !checkBox->IsChecked();
    checkBox->SetValue(state);
    WorldDraw::VisualSettings *set = s_glRender.GetSettings();
    set->m_showWarFog = state;
  }
  if (code == 'a' || code == 'A')
    s_glRender.Shift(-KEYBOARD_SHIFT_DIST, 0.0f);
  if (code == 'd' || code == 'D')
    s_glRender.Shift(+KEYBOARD_SHIFT_DIST, 0.0f);
  if (code == 'w' || code == 'W')
    s_glRender.Shift(0.0f, +KEYBOARD_SHIFT_DIST);
  if (code == 's' || code == 'S')
    s_glRender.Shift(0.0f, -KEYBOARD_SHIFT_DIST);

}

void  AuditCanvas::OnMouseRightDown(wxMouseEvent& evt)
{
  SetFocus();
  long x = (long)evt.GetX();
  long y = (long)evt.GetY();

  wxTextCtrl *texCtrl = m_auditPanel->GetTextProperty();
  NWorld::PFLogicObject *obj = s_glRender.GetObjectByMouse(x, y);
  if (obj != NULL)
  {
    m_textBuffer[0] = 0;
    DumpLogicObjectInfo( obj, (char*)m_textBuffer, sizeof(m_textBuffer) );
    texCtrl->Clear();
    texCtrl->WriteText(wxString(m_textBuffer));
    texCtrl->ShowPosition(0);
    texCtrl->SetToolTip(wxString(m_textBuffer));
  }
  else
  {
    texCtrl->Clear();
  }
}

void  AuditCanvas::OnMouseLeftDown(wxMouseEvent& evt)
{
  SetFocus();
  m_mousePressed = 1;
  //CaptureMouse();
  
}
void  AuditCanvas::OnMouseLeftUp(wxMouseEvent&)
{
  m_mousePressed = 0;
  if (HasCapture())
    ReleaseMouse();
}
void  AuditCanvas::OnMouseMotion(wxMouseEvent& event)
{
  wxCoord x = event.GetX();    
  wxCoord y = event.GetY();    
  if (m_mousePrevX == -1)
  {
    m_mousePrevX = x;
    m_mousePrevY = y;
  }
  
  if (m_parentFrame && m_inLoading)
  {
    if (s_glRender.GetNumVisibleObjects() == 0)
      m_parentFrame->SetStatusText("First updates...");
  }
  
  // show mouse position in world
  if (m_parentFrame && !m_inLoading)
  {
    if (s_glRender.GetNumVisibleObjects() != 0)
    {
      float fx, fy;
      s_glRender.GetWorldPositionByMouse( (int)x, (int)y, &fx, &fy);
      wxString str;
      str.Printf("World position = ( %3.1f , %3.1f )", fx, fy);
      m_parentFrame->SetStatusText( str, 0 );
    }
  }
  

  if (m_mousePressed)
  {
    if (!HasCapture())
      CaptureMouse();
        
    int dx = (int)x - (int)m_mousePrevX;
    int dy = (int)y - (int)m_mousePrevY;
    if (dx != 0 || dy != 0)
      s_glRender.Shift(-dx, dy);
  }
  m_mousePrevX = x;
  m_mousePrevY = y;
}

void  AuditCanvas::OnMouseWheel(wxMouseEvent &evt)
{
  int w = evt.GetWheelRotation() / evt.GetWheelDelta();
  if (w < 0)
    s_glRender.ZoomIn();
  if (w > 0)
    s_glRender.ZoomOut();
  
}

void AuditCanvas::InitGL()
{
  SetCurrent();
  s_glRender.Start();
}


void AuditCanvas::Render()
{
  wxPaintDC dc(this);
  
  if (!GetContext()) return;

  SetCurrent();
  
  // Init OpenGL once, but after SetCurrent
  if (!m_initGL)
  {
    InitGL();
    m_initGL = true;
  }
  
  
  const NWorld::PFWorld *world = s_audit->GetWorld(0);
  s_glRender.Render(world);
  SwapBuffers();
  
  wxCursor cur = GetCursor();
  if (world != NULL && m_inLoading && s_glRender.GetNumVisibleObjects() > 0)
  {
    m_inLoading = false;
    SetCursor(wxCURSOR_ARROW);
  }
  
}

// *******************************************************************************************************************
BEGIN_EVENT_TABLE(AuditPanel, wxPanel)

  EVT_BUTTON( wxID_BUTTON_PAUSE,      AuditPanel::OnButtonPause)
  EVT_BUTTON( wxID_BUTTON_PLAY,       AuditPanel::OnButtonPlay)
  EVT_BUTTON( wxID_BUTTON_ZOOMALL,    AuditPanel::OnButtonZoomAll)
  
  EVT_COMMAND_SCROLL(wxID_SLIDER_TIME     , AuditPanel::OnSliderTime        )

  EVT_CHECKBOX(wxID_CHECKBOX_HEIGHTMAP    , AuditPanel::OnCheckHeightMap    )
  EVT_CHECKBOX(wxID_CHECKBOX_WARFOG       , AuditPanel::OnCheckWarFog       )

  EVT_CHECKBOX(wxID_CHECKBOX_DISPATHES    , AuditPanel::OnCheckDispatches   )
  
  EVT_CHECKBOX(wxID_CHECKBOX_SUMMON       , AuditPanel::OnCheckSummon       )
  EVT_CHECKBOX(wxID_CHECKBOX_CREEP        , AuditPanel::OnCheckCreep        )
  EVT_CHECKBOX(wxID_CHECKBOX_SCREEP       , AuditPanel::OnCheckSCreep       )
  EVT_CHECKBOX(wxID_CHECKBOX_NCREEP       , AuditPanel::OnCheckNCreep       )
  EVT_CHECKBOX(wxID_CHECKBOX_TOWER        , AuditPanel::OnCheckTower        )
  EVT_CHECKBOX(wxID_CHECKBOX_BUILDING     , AuditPanel::OnCheckBuilding     )
  EVT_CHECKBOX(wxID_CHECKBOX_SHOP         , AuditPanel::OnCheckShop         )
  EVT_CHECKBOX(wxID_CHECKBOX_TREE         , AuditPanel::OnCheckTree         )
  EVT_CHECKBOX(wxID_CHECKBOX_PET          , AuditPanel::OnCheckPet          )
  EVT_CHECKBOX(wxID_CHECKBOX_PICKABLE     , AuditPanel::OnCheckPickable     )
  EVT_CHECKBOX(wxID_CHECKBOX_MINIGAMEPLACE, AuditPanel::OnCheckMiniGamePlace)
  EVT_CHECKBOX(wxID_CHECKBOX_DEADBOY      , AuditPanel::OnCheckDeadboy      )

  
END_EVENT_TABLE()

static wxString s_HelpInfo("\
Here you will see unit property. \n\
“ут можно будет прочитать вс€кие свойства объекта на карте.\n\
”величьте карту враща€ колесо мыши, и выбирите интересуемый фрагмент,\n\
нажав левую кнопку и потащив мышь. “кните на объекте правой кнопкой мыши.\n\
\n\
 нопки:\n\
H: карта высот\n\
V: туман войны\n\
A: карту влево\n\
D: карту вправо\n\
W: карту вверх\n\
S: карту вниз");

AuditPanel::AuditPanel(wxFrame *frame)
: wxPanel(frame, wxID_ANY)
{
  wxString date;
  date.Printf(wxT("Selected date: %s"),
    wxDateTime::Today().FormatISODate().c_str());
  
  m_renderWindow = new AuditCanvas(this, wxID_ANY, wxPoint(0,0), wxSize(700, 700));

  m_mainHorSizer    = new wxBoxSizer( wxHORIZONTAL );
  m_rightVertSizer  = new wxBoxSizer( wxVERTICAL );
  m_rightHorSizer   = new wxBoxSizer( wxHORIZONTAL );

  m_buttonZoomAll   = new wxButton(this, wxID_BUTTON_ZOOMALL, wxString("Zoom all") );
  #if wxUSE_TOOLTIPS
    m_buttonZoomAll->SetToolTip(wxString("Zoom all extends for world map (see all)"));
  #endif  
  
  m_sliderTime      = new wxSlider(this, wxID_SLIDER_TIME, 10, 5, 50, wxPoint(0,0), wxSize(160,50), wxSL_AUTOTICKS | wxSL_LABELS );
  m_sliderTime->SetTickFreq(5, 0);
  #if wxUSE_TOOLTIPS
    m_sliderTime->SetToolTip(wxString("Game play speed"));
  #endif  
  
  m_textPlay      = new wxStaticText(this, wxID_ANY, wxString("Play time controls") , wxPoint(0,0), wxSize(160,20));
  m_buttonPause   = new wxButton(this, wxID_BUTTON_PAUSE, wxString("Pause") );
  #if wxUSE_TOOLTIPS
    m_buttonPause->SetToolTip(wxString("Stop game internal Step. Just visualize"));
  #endif  
  m_buttonPlay    = new wxButton(this, wxID_BUTTON_PLAY,  wxString("Play") );
  #if wxUSE_TOOLTIPS
    m_buttonPlay->SetToolTip(wxString("Resume game internal Steps"));
  #endif  
  m_buttonPlay->Enable(false);
  m_rightHorSizer->Add(m_buttonPause,  0, wxALIGN_CENTER | wxALL, 10);
  m_rightHorSizer->Add(m_buttonPlay,   0, wxALIGN_CENTER | wxALL, 10);

  m_textMaps        =  new wxStaticText(this, wxID_ANY, wxString("Maps:") , wxPoint(0,0), wxSize(160,20));
  m_checkHeightMap  =  new wxCheckBox(this, wxID_CHECKBOX_HEIGHTMAP,  wxString("Height map")  , wxPoint(0,0), wxSize(160,18) );
  m_checkWarFog     =  new wxCheckBox(this, wxID_CHECKBOX_WARFOG,     wxString("War fog")     , wxPoint(0,0), wxSize(160,18));

  m_textDispatches  =  new wxStaticText(this, wxID_ANY, wxString("War dispatches:") , wxPoint(0,0), wxSize(160,20));
  m_checkDispatches =  new wxCheckBox(this, wxID_CHECKBOX_DISPATHES,  wxString("Dispatches")  , wxPoint(0,0), wxSize(160,18));

  m_textObjects     =  new wxStaticText(this, wxID_ANY, wxString("Objects:") , wxPoint(0,0), wxSize(160,20));
  m_checkSummon     =  new wxCheckBox(this, wxID_CHECKBOX_SUMMON,     wxString("Summon")      , wxPoint(0,0), wxSize(160,18));
  m_checkCreep      =  new wxCheckBox(this, wxID_CHECKBOX_CREEP,      wxString("Creep")       , wxPoint(0,0), wxSize(160,18));
  m_checkSCreep     =  new wxCheckBox(this, wxID_CHECKBOX_SCREEP,     wxString("Seige Creep") , wxPoint(0,0), wxSize(160,18));
  m_checkNCreep     =  new wxCheckBox(this, wxID_CHECKBOX_NCREEP,     wxString("Neutral Creep"),wxPoint(0,0), wxSize(160,18));
  m_checkTower      =  new wxCheckBox(this, wxID_CHECKBOX_TOWER,      wxString("Tower")        ,wxPoint(0,0), wxSize(160,18));
  m_checkBuilding   =  new wxCheckBox(this, wxID_CHECKBOX_BUILDING,   wxString("Building")     ,wxPoint(0,0), wxSize(160,18));
  m_checkShop       =  new wxCheckBox(this, wxID_CHECKBOX_SHOP,       wxString("Shop")         ,wxPoint(0,0), wxSize(160,18));
  m_checkTree       =  new wxCheckBox(this, wxID_CHECKBOX_TREE,       wxString("Tree")         ,wxPoint(0,0), wxSize(160,18));
  m_checkPet        =  new wxCheckBox(this, wxID_CHECKBOX_PET,        wxString("Pet")          ,wxPoint(0,0), wxSize(160,18));
  m_checkPickable   =  new wxCheckBox(this, wxID_CHECKBOX_PICKABLE,   wxString("Pickable")     ,wxPoint(0,0), wxSize(160,18));
  m_checkMiniGamePlace=new wxCheckBox(this, wxID_CHECKBOX_MINIGAMEPLACE,wxString("Mini game place"),wxPoint(0,0),wxSize(160,18));
  m_checkDeadBoy    =  new wxCheckBox(this, wxID_CHECKBOX_DEADBOY,    wxString("Dead boy")     ,wxPoint(0,0), wxSize(160,18));
  
  m_labelProperty   =  new wxStaticText(this, wxID_ANY, wxString("Property:"), wxPoint(0,0), wxSize(160,20));
  m_textProperty    =  new wxTextCtrl( this, wxID_EDIT_PROPERTY, s_HelpInfo,
                                      wxPoint(0,0), wxSize(180, 250),
                                      wxTE_MULTILINE | wxTE_WORDWRAP | wxTE_READONLY );
  
  m_renderWindow->setAuditPanel(this);
  m_renderWindow->SetFrame(frame);
  
  WorldDraw::VisualSettings *set = s_glRender.GetSettings();
  
  m_checkHeightMap->SetValue(set->m_showHeightMap);
  m_checkWarFog->SetValue(set->m_showWarFog);

  m_checkDispatches->SetValue(true);

  m_checkSummon->SetValue(true);
  m_checkCreep->SetValue(true);
  m_checkSCreep->SetValue(true);
  m_checkNCreep->SetValue(true);
  m_checkTower->SetValue(true);
  m_checkBuilding->SetValue(true);
  m_checkShop->SetValue(true);
  m_checkTree->SetValue(true);
  m_checkPet->SetValue(true);
  m_checkPickable->SetValue(true);
  m_checkMiniGamePlace->SetValue(true);
  m_checkDeadBoy->SetValue(true);
  
  m_rightVertSizer->Add(m_buttonZoomAll,      0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL, 10);
  m_rightVertSizer->AddStretchSpacer(0);
  m_rightVertSizer->Add(m_sliderTime,         0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL, 10);
  m_rightVertSizer->AddStretchSpacer(0);
  m_rightVertSizer->Add(m_textPlay,           0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL, 10);
  m_rightVertSizer->AddStretchSpacer(0);
  m_rightVertSizer->Add(m_rightHorSizer,      0);
  m_rightVertSizer->AddStretchSpacer(0);
  m_rightVertSizer->Add(m_textMaps,           0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL, 10);
  m_rightVertSizer->Add(m_checkHeightMap,     0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL, 10);
  m_rightVertSizer->Add(m_checkWarFog,        0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL, 10);

  m_rightVertSizer->AddStretchSpacer(0);
  m_rightVertSizer->Add(m_textDispatches,     0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL, 10);
  m_rightVertSizer->AddStretchSpacer(0);
  m_rightVertSizer->Add(m_checkDispatches,    0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL, 10);


  m_rightVertSizer->AddStretchSpacer(0);
  m_rightVertSizer->Add(m_textObjects,        0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL, 10);
  m_rightVertSizer->AddStretchSpacer(0);
  m_rightVertSizer->Add(m_checkSummon,        0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL, 10);
  m_rightVertSizer->Add(m_checkCreep,         0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL, 10);
  m_rightVertSizer->Add(m_checkSCreep,        0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL, 10);
  m_rightVertSizer->Add(m_checkNCreep,        0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL, 10);
  m_rightVertSizer->Add(m_checkTower,         0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL, 10);
  m_rightVertSizer->Add(m_checkBuilding,      0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL, 10);
  m_rightVertSizer->Add(m_checkShop,          0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL, 10);
  m_rightVertSizer->Add(m_checkTree,          0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL, 10);
  m_rightVertSizer->Add(m_checkPet,           0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL, 10);
  m_rightVertSizer->Add(m_checkPickable,      0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL, 10);
  m_rightVertSizer->Add(m_checkMiniGamePlace, 0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL, 10);
  m_rightVertSizer->Add(m_checkDeadBoy,       0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL, 10);
  m_rightVertSizer->AddStretchSpacer(0);
  m_rightVertSizer->Add(m_labelProperty,        0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL, 10);
  m_rightVertSizer->AddStretchSpacer(0);
  m_rightVertSizer->Add(m_textProperty,       0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL, 10);
  
  
  m_mainHorSizer->Add(m_renderWindow,   1, wxALIGN_CENTER | wxALL, 10 );
  m_mainHorSizer->Add(m_rightVertSizer, 0);

  SetSizer( m_mainHorSizer );
  m_mainHorSizer->SetSizeHints(this);
}
void  AuditPanel::OnButtonZoomAll(wxCommandEvent& WXUNUSED(evt))
{
  s_glRender.ZoomAll();    
  m_renderWindow->SetFocus();
}

void  AuditPanel::OnSliderTime(wxScrollEvent&  evt)
{
  int pos = evt.GetPosition();
  //  5 = 0.5f
  // 10 = 1.0f
  // 50 = 5.0f
  float speed = (float)pos * 0.1f;
  s_audit->SetPlaySpeed(speed);
}

void  AuditPanel::OnButtonPause(wxCommandEvent& WXUNUSED(evt))
{
  m_buttonPause->Enable(false);
  m_buttonPlay->Enable(true);
  s_audit->SetPause(true);
  
  m_renderWindow->SetFocus();
}
void  AuditPanel::OnButtonPlay(wxCommandEvent& WXUNUSED(evt))
{
  m_buttonPlay->Enable(false);
  m_buttonPause->Enable(true);
  s_audit->SetPause(false);
  
  m_renderWindow->SetFocus();
}

void  AuditPanel::OnCheckHeightMap(wxCommandEvent& evt)
{
  WorldDraw::VisualSettings *set = s_glRender.GetSettings();
  set->m_showHeightMap = !set->m_showHeightMap;
  m_renderWindow->SetFocus();
}
void  AuditPanel::OnCheckWarFog(wxCommandEvent& evt)
{
  WorldDraw::VisualSettings *set = s_glRender.GetSettings();
  set->m_showWarFog = !set->m_showWarFog;
  m_renderWindow->SetFocus();
}

void            AuditPanel::OnCheck(int checkType)
{
  WorldDraw::VisualSettings *set = s_glRender.GetSettings();
  switch (checkType)  
  {
    case wxID_CHECKBOX_DISPATHES:
      set->m_showDispatches = !set->m_showDispatches;
      break;
    case wxID_CHECKBOX_SUMMON:
      set->m_showSummon = !set->m_showSummon;
      break;
    case wxID_CHECKBOX_CREEP:
      set->m_showCreep = !set->m_showCreep;
      break;
    case wxID_CHECKBOX_SCREEP:
      set->m_showSeigeCreep = !set->m_showSeigeCreep;
      break;
    case wxID_CHECKBOX_NCREEP:
      set->m_showNeutralCreep = !set->m_showNeutralCreep;
      break;
    case wxID_CHECKBOX_TOWER:
      set->m_showTower = !set->m_showTower;
      break;
    case wxID_CHECKBOX_BUILDING:
      set->m_showBuilding = !set->m_showBuilding;
      break;
    case wxID_CHECKBOX_SHOP:
      set->m_showShop = !set->m_showShop;
      break;
    case wxID_CHECKBOX_TREE:
      set->m_showTree = !set->m_showTree;
      break;
    case wxID_CHECKBOX_PET:
      set->m_showPet = !set->m_showPet;
      break;
    case wxID_CHECKBOX_PICKABLE:
      set->m_showPickable = !set->m_showPickable;
      break;
    case wxID_CHECKBOX_MINIGAMEPLACE:
      set->m_showMiniGamePlace = !set->m_showMiniGamePlace;
      break;
    case wxID_CHECKBOX_DEADBOY:
      set->m_showDeadBody = !set->m_showDeadBody;
      break;
    default:
      break;
  } // switch
  
  m_renderWindow->SetFocus();
}


