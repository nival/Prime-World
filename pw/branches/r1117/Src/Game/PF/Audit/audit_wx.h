#ifndef _AUDIT_WX_H_
#define _AUDIT_WX_H_


// wxWindows includes
#include "wx/app.h"
#include "wx/log.h"
#include "wx/frame.h"
#include "wx/panel.h"
#include "wx/stattext.h"
#include "wx/statbox.h"
#include "wx/menu.h"
#include "wx/layout.h"
#include "wx/msgdlg.h"
#include "wx/icon.h"
#include "wx/button.h"
#include "wx/checkbox.h"
#include "wx/sizer.h"
#include "wx/textctrl.h"
#include "wx/button.h"
#include "wx/slider.h"
#include "wx/dcclient.h"
#include "wx/busyinfo.h"
#include "wx/statusbr.h"
#include "wx/settings.h"

#define wxUSE_GLCANVAS 1
#include "wx/glcanvas.h"


class AuditApp : public wxApp
{
  public:
    // this one is called on application startup and is a good place for the app
    // initialization (doing it here and not in the ctor allows to have an error
    // return: if OnInit() returns false, the application terminates)
    bool OnInit();
   ~AuditApp();
};

class AuditPanel;
class AuditCanvas: public wxGLCanvas
{
  friend class MyFrame;
public:
  AuditCanvas(  wxWindow *parent, wxWindowID id = wxID_ANY,
    const wxPoint& pos = wxDefaultPosition,
    const wxSize& size = wxDefaultSize,
    long style = 0, const wxString& name = _T("PF-Audit") );
  ~AuditCanvas();

  void OnIdle(wxIdleEvent &evt);
  void OnPaint(wxPaintEvent& event);
  void OnSize(wxSizeEvent& event);
  void OnEraseBackground(wxEraseEvent& event);
  void OnEnterWindow(wxMouseEvent& event);

  void  OnMouseLeftDown(wxMouseEvent& event);
  void  OnMouseLeftUp(wxMouseEvent& event);
  void  OnMouseMotion(wxMouseEvent& event);
  void  OnMouseWheel(wxMouseEvent& event);

  void  OnMouseRightDown(wxMouseEvent& evt);
  
  void  OnKeyDown(wxKeyEvent& evt);
  void  OnKeyUp(wxKeyEvent& event);
  
  void  setAuditPanel(AuditPanel *pan)
  {
    m_auditPanel = pan;
  }
  void  SetFrame(wxFrame *frame)
  {
    m_parentFrame = frame;
  }

  void Render();
  void InitGL();
  void Rotate(GLfloat deg);
  static GLfloat CalcRotateSpeed(unsigned long acceltime);
  static GLfloat CalcRotateAngle( unsigned long lasttime,
    unsigned long acceltime );
  void Action( long code, unsigned long lasttime,
    unsigned long acceltime );

private:
  bool        m_initGL;
  bool        m_initWorld;
  bool        m_inLoading;
  
  long        m_mousePressed;
  wxCoord     m_mousePrevX;
  wxCoord     m_mousePrevY;
  
  AuditPanel  *m_auditPanel;
  wxFrame     *m_parentFrame;

  char        m_textBuffer[1024 * 8];

  DECLARE_EVENT_TABLE()
};

enum 
{
  wxID_BUTTON_FIRST = 10,
  

  wxID_BUTTON_ZOOMALL,
  wxID_SLIDER_TIME,
  wxID_BUTTON_PAUSE,
  wxID_BUTTON_PLAY,
  
  wxID_CHECKBOX_HEIGHTMAP,
  wxID_CHECKBOX_WARFOG,
  
  wxID_EDIT_PROPERTY,

  wxID_CHECKBOX_DISPATHES,
  
  wxID_CHECKBOX_SUMMON,
  wxID_CHECKBOX_CREEP,
  wxID_CHECKBOX_SCREEP,
  wxID_CHECKBOX_NCREEP,
  wxID_CHECKBOX_TOWER,
  wxID_CHECKBOX_BUILDING,
  wxID_CHECKBOX_SHOP,
  wxID_CHECKBOX_TREE,
  wxID_CHECKBOX_PET,
  wxID_CHECKBOX_PICKABLE,
  wxID_CHECKBOX_MINIGAMEPLACE,
  wxID_CHECKBOX_DEADBOY,
  
};

class AuditPanel : public wxPanel
{
public:
  AuditPanel(wxFrame *frame);

  void            OnButtonPause(  wxCommandEvent& evt);
  void            OnButtonPlay(   wxCommandEvent& evt);
  void            OnButtonZoomAll(wxCommandEvent& evt);
  void            OnSliderTime(   wxScrollEvent&  evt);

  void            OnCheckDispatches(wxCommandEvent& WXUNUSED(evt)){ OnCheck(wxID_CHECKBOX_DISPATHES); }

  void            OnCheckSummon(  wxCommandEvent& WXUNUSED(evt)){ OnCheck(wxID_CHECKBOX_SUMMON); }
  void            OnCheckCreep(   wxCommandEvent& WXUNUSED(evt)){ OnCheck(wxID_CHECKBOX_CREEP); }
  void            OnCheckSCreep(  wxCommandEvent& WXUNUSED(evt)){ OnCheck(wxID_CHECKBOX_SCREEP); }
  void            OnCheckNCreep(  wxCommandEvent& WXUNUSED(evt)){ OnCheck(wxID_CHECKBOX_NCREEP); }
  void            OnCheckTower(   wxCommandEvent& WXUNUSED(evt)){ OnCheck(wxID_CHECKBOX_TOWER); }
  void            OnCheckBuilding(wxCommandEvent& WXUNUSED(evt)){ OnCheck(wxID_CHECKBOX_BUILDING); }
  void            OnCheckShop(    wxCommandEvent& WXUNUSED(evt)){ OnCheck(wxID_CHECKBOX_SHOP); }
  void            OnCheckTree(    wxCommandEvent& WXUNUSED(evt)){ OnCheck(wxID_CHECKBOX_TREE); }
  void            OnCheckPet(     wxCommandEvent& WXUNUSED(evt)){ OnCheck(wxID_CHECKBOX_PET); }
  void            OnCheckPickable(wxCommandEvent& WXUNUSED(evt)){ OnCheck(wxID_CHECKBOX_PICKABLE); }
  void            OnCheckMiniGamePlace(wxCommandEvent& WXUNUSED(evt)){ OnCheck(wxID_CHECKBOX_MINIGAMEPLACE); }
  void            OnCheckDeadboy( wxCommandEvent& WXUNUSED(evt)){ OnCheck(wxID_CHECKBOX_DEADBOY); }
  
  void            OnCheckHeightMap(wxCommandEvent& evt);
  void            OnCheckWarFog(wxCommandEvent& evt);
  
  wxCheckBox      *GetCheckHeightMap()  { return m_checkHeightMap;  }
  wxCheckBox      *GetCheckWarFog()     { return m_checkWarFog;     }
  wxTextCtrl      *GetTextProperty()    { return m_textProperty;    }

  
protected:
  void            OnCheck(int checkType);

private:
  AuditCanvas     *m_renderWindow;
  
  wxBoxSizer      *m_mainHorSizer;
  wxBoxSizer      *m_rightHorSizer;
  wxBoxSizer      *m_rightVertSizer;

  wxButton        *m_buttonZoomAll;
  
  wxSlider        *m_sliderTime;

  wxStaticText    *m_textPlay;
  wxButton        *m_buttonPause;
  wxButton        *m_buttonPlay;

  wxStaticText    *m_textMaps;
  wxCheckBox      *m_checkHeightMap;
  wxCheckBox      *m_checkWarFog;

  wxStaticText    *m_textDispatches;
  wxCheckBox      *m_checkDispatches;

  wxStaticText    *m_textObjects;
  wxCheckBox      *m_checkSummon;
  wxCheckBox      *m_checkCreep;
  wxCheckBox      *m_checkSCreep;
  wxCheckBox      *m_checkNCreep;
  wxCheckBox      *m_checkTower;
  wxCheckBox      *m_checkBuilding;
  wxCheckBox      *m_checkShop;
  wxCheckBox      *m_checkTree;
  wxCheckBox      *m_checkPet;
  wxCheckBox      *m_checkPickable;
  wxCheckBox      *m_checkMiniGamePlace;
  wxCheckBox      *m_checkDeadBoy;

  wxStaticText    *m_labelProperty;
  wxTextCtrl      *m_textProperty;
  
  DECLARE_EVENT_TABLE()
};


enum
{
  // menu items
  Audit_File_About    = wxID_ABOUT,
  Audit_File_Quit     = wxID_EXIT,
};

// Define a new frame type: this is going to be our main frame
class AuditFrame : public wxFrame
{
public:
  // ctor(s)
  AuditFrame(const wxString& title, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize);

  // event handlers (these functions should _not_ be virtual)
  void OnQuit(wxCommandEvent& evt);
  void OnAbout(wxCommandEvent& evt);


private:
  AuditPanel      *m_panel;

  // any class wishing to process wxWidgets events must use this macro
  DECLARE_EVENT_TABLE()
};





#endif


