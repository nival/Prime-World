// $Id: ConfigurationViewer.cpp 80826 2008-03-04 14:51:23Z wotte $
#ifdef __GNUG__
    #pragma implementation "minimal.cpp"
    #pragma interface "minimal.cpp"
#endif

#include "stdafx.h"
#include "MainFrame.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

// the application icon
#if defined(__WXGTK__) || defined(__WXMOTIF__)
    #include "mondrian.xpm"
#endif

class ConfigurationViewerApp : public wxApp
{
public:
    virtual bool OnInit();
};

IMPLEMENT_APP(ConfigurationViewerApp)

bool ConfigurationViewerApp::OnInit()
{
  // Create the main application window
  MainFrame *frame = new MainFrame("Configuration Viewer",
                               wxPoint(50, 50), wxSize(450, 340));

    // Give it an icon
#ifdef __WXMSW__
  frame->SetIcon(wxIcon("mondrian"));
#else
  frame->SetIcon(wxIcon( mondrian_xpm ));
#endif

  frame->Show(TRUE);
  SetTopWindow(frame);

  return TRUE;
}

