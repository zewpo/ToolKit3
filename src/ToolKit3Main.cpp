/***************************************************************
 * Name:      ToolKit3Main.cpp
 * Purpose:   Code for Application Frame
 * Author:    Christopher Plewright (chris@createng.com)
 * Created:   2016-10-08
 * Copyright: Christopher Plewright (www.createng.com)
 * License:
 **************************************************************/

#include "ToolKit3Main.h"

//(*InternalHeaders(ToolKit3Frame)
#include <wx/artprov.h>
#include <wx/bitmap.h>
#include <wx/icon.h>
#include <wx/settings.h>
#include <wx/intl.h>
#include <wx/image.h>
#include <wx/string.h>
//*)

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

const long ToolKit3Frame::ID_SQLPANEL = wxNewId();

//(*IdInit(ToolKit3Frame)
const long ToolKit3Frame::ID_SEARCHCTRL1 = wxNewId();
const long ToolKit3Frame::ID_TREECTRL1 = wxNewId();
const long ToolKit3Frame::ID_PANEL1 = wxNewId();
const long ToolKit3Frame::ID_NOTEBOOK1 = wxNewId();
const long ToolKit3Frame::ID_BITMAPBUTTON1 = wxNewId();
const long ToolKit3Frame::ID_PANEL3 = wxNewId();
const long ToolKit3Frame::ID_GRID1 = wxNewId();
const long ToolKit3Frame::ID_PANEL4 = wxNewId();
const long ToolKit3Frame::ID_PANEL2 = wxNewId();
const long ToolKit3Frame::ID_SPLITTERWINDOW2 = wxNewId();
const long ToolKit3Frame::ID_PANEL5 = wxNewId();
const long ToolKit3Frame::ID_PANEL6 = wxNewId();
const long ToolKit3Frame::ID_PANEL7 = wxNewId();
const long ToolKit3Frame::ID_NOTEBOOK2 = wxNewId();
const long ToolKit3Frame::ID_TEXTCTRLLOG = wxNewId();
const long ToolKit3Frame::ID_PANELLOG = wxNewId();
const long ToolKit3Frame::ID_NOTEBOOK3 = wxNewId();
const long ToolKit3Frame::ID_SPLITTERWINDOW3 = wxNewId();
const long ToolKit3Frame::ID_SPLITTERWINDOW1 = wxNewId();
const long ToolKit3Frame::idMenuSettings = wxNewId();
const long ToolKit3Frame::idMenuQuit = wxNewId();
const long ToolKit3Frame::idMenuAbout = wxNewId();
const long ToolKit3Frame::ID_STATUSBAR1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(ToolKit3Frame,wxFrame)
    //(*EventTable(ToolKit3Frame)
    //*)
END_EVENT_TABLE()

ToolKit3Frame::ToolKit3Frame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(ToolKit3Frame)
    wxFlexGridSizer* FlexGridSizer4;
    wxMenuItem* MenuItem2;
    wxFlexGridSizer* FlexGridSizer3;
    wxMenuItem* MenuItem1;
    wxFlexGridSizer* FlexGridSizer2;
    wxMenu* Menu1;
    wxBoxSizer* BoxSizer1;
    wxMenuBar* MenuBar1;
    wxFlexGridSizer* FlexGridSizer1;
    wxMenu* Menu2;

    Create(parent, wxID_ANY, _("ToolKit v3"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    SetClientSize(wxSize(845,450));
    SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOW));
    {
    	wxIcon FrameIcon;
    	FrameIcon.CopyFromBitmap(wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_REDO")),wxART_FRAME_ICON));
    	SetIcon(FrameIcon);
    }
    SplitterWindow1 = new wxSplitterWindow(this, ID_SPLITTERWINDOW1, wxPoint(-104,0), wxDefaultSize, wxSP_3D, _T("ID_SPLITTERWINDOW1"));
    SplitterWindow1->SetMinSize(wxSize(10,10));
    SplitterWindow1->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_SCROLLBAR));
    SplitterWindow1->SetMinimumPaneSize(10);
    SplitterWindow1->SetSashGravity(0.2);
    SplitterWindow2 = new wxSplitterWindow(SplitterWindow1, ID_SPLITTERWINDOW2, wxPoint(307,435), wxDefaultSize, wxSP_3D, _T("ID_SPLITTERWINDOW2"));
    SplitterWindow2->SetMinSize(wxSize(10,10));
    SplitterWindow2->SetMinimumPaneSize(10);
    SplitterWindow2->SetSashGravity(0.6);
    Notebook1 = new wxNotebook(SplitterWindow2, ID_NOTEBOOK1, wxDefaultPosition, wxDefaultSize, 0, _T("ID_NOTEBOOK1"));
    Panel_Screens = new wxPanel(Notebook1, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    FlexGridSizer3 = new wxFlexGridSizer(2, 1, 0, 0);
    FlexGridSizer3->AddGrowableCol(0);
    FlexGridSizer3->AddGrowableRow(1);
    SearchCtrl1 = new wxSearchCtrl(Panel_Screens, ID_SEARCHCTRL1, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_SEARCHCTRL1"));
    FlexGridSizer3->Add(SearchCtrl1, 1, wxALL|wxEXPAND, 0);
    TreeCtrl1 = new wxTreeCtrl(Panel_Screens, ID_TREECTRL1, wxDefaultPosition, wxDefaultSize, wxTR_DEFAULT_STYLE, wxDefaultValidator, _T("ID_TREECTRL1"));
    FlexGridSizer3->Add(TreeCtrl1, 1, wxALL|wxEXPAND, 0);
    Panel_Screens->SetSizer(FlexGridSizer3);
    FlexGridSizer3->Fit(Panel_Screens);
    FlexGridSizer3->SetSizeHints(Panel_Screens);
    Notebook1->AddPage(Panel_Screens, _("Screens"), false);
    Panel2 = new wxPanel(SplitterWindow2, ID_PANEL2, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL2"));
    FlexGridSizer1 = new wxFlexGridSizer(2, 1, 0, 0);
    FlexGridSizer1->AddGrowableCol(0);
    FlexGridSizer1->AddGrowableRow(1);
    Panel3 = new wxPanel(Panel2, ID_PANEL3, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL3"));
    FlexGridSizer2 = new wxFlexGridSizer(0, 5, 0, 0);
    BitmapButton1 = new wxBitmapButton(Panel3, ID_BITMAPBUTTON1, wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_LIST_VIEW")),wxART_BUTTON), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON1"));
    FlexGridSizer2->Add(BitmapButton1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    Panel3->SetSizer(FlexGridSizer2);
    FlexGridSizer2->Fit(Panel3);
    FlexGridSizer2->SetSizeHints(Panel3);
    FlexGridSizer1->Add(Panel3, 1, wxLEFT|wxRIGHT|wxEXPAND, 1);
    Panel4 = new wxPanel(Panel2, ID_PANEL4, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL4"));
    Panel4->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOW));
    FlexGridSizer4 = new wxFlexGridSizer(1, 1, 0, 0);
    FlexGridSizer4->AddGrowableCol(0);
    FlexGridSizer4->AddGrowableRow(0);
    Grid1 = new wxGrid(Panel4, ID_GRID1, wxDefaultPosition, wxDefaultSize, 0, _T("ID_GRID1"));
    Grid1->CreateGrid(0,1);
    Grid1->SetMaxSize(wxSize(0,0));
    Grid1->EnableEditing(true);
    Grid1->EnableGridLines(true);
    Grid1->SetDefaultCellFont( Grid1->GetFont() );
    Grid1->SetDefaultCellTextColour( Grid1->GetForegroundColour() );
    FlexGridSizer4->Add(Grid1, 1, wxALL|wxEXPAND, 1);
    Panel4->SetSizer(FlexGridSizer4);
    FlexGridSizer4->Fit(Panel4);
    FlexGridSizer4->SetSizeHints(Panel4);
    FlexGridSizer1->Add(Panel4, 1, wxALL|wxEXPAND, 0);
    Panel2->SetSizer(FlexGridSizer1);
    FlexGridSizer1->Fit(Panel2);
    FlexGridSizer1->SetSizeHints(Panel2);
    SplitterWindow2->SplitHorizontally(Notebook1, Panel2);
    SplitterWindow3 = new wxSplitterWindow(SplitterWindow1, ID_SPLITTERWINDOW3, wxDefaultPosition, wxDefaultSize, wxSP_3D, _T("ID_SPLITTERWINDOW3"));
    SplitterWindow3->SetMinSize(wxSize(10,10));
    SplitterWindow3->SetMinimumPaneSize(10);
    SplitterWindow3->SetSashGravity(0.8);
    Notebook2 = new wxNotebook(SplitterWindow3, ID_NOTEBOOK2, wxPoint(106,91), wxDefaultSize, 0, _T("ID_NOTEBOOK2"));
    Panel5 = new wxPanel(Notebook2, ID_PANEL5, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL5"));
    Panel6 = new wxPanel(Notebook2, ID_PANEL6, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL6"));
    Panel7 = new wxPanel(Notebook2, ID_PANEL7, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL7"));
    Notebook2->AddPage(Panel5, _("Controls"), false);
    Notebook2->AddPage(Panel6, _("Visual"), false);
    Notebook2->AddPage(Panel7, _("Code"), false);
    Notebook3 = new wxNotebook(SplitterWindow3, ID_NOTEBOOK3, wxDefaultPosition, wxDefaultSize, 0, _T("ID_NOTEBOOK3"));
    PanelLog = new wxPanel(Notebook3, ID_PANELLOG, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANELLOG"));
    BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
    TextCtrlLog = new wxTextCtrl(PanelLog,ID_TEXTCTRLLOG,wxEmptyString,wxDefaultPosition,wxDefaultSize,wxTE_MULTILINE | wxTE_READONLY | wxTE_AUTO_URL | wxTE_DONTWRAP,wxDefaultValidator,_T("ID_TEXTCTRLLOG"));
    BoxSizer1->Add(TextCtrlLog, 1, wxALL|wxEXPAND, 2);
    PanelLog->SetSizer(BoxSizer1);
    BoxSizer1->Fit(PanelLog);
    BoxSizer1->SetSizeHints(PanelLog);
    Notebook3->AddPage(PanelLog, _("Log"), false);
    SplitterWindow3->SplitHorizontally(Notebook2, Notebook3);
    SplitterWindow1->SplitVertically(SplitterWindow2, SplitterWindow3);
    MenuBar1 = new wxMenuBar();
    Menu1 = new wxMenu();
    MenuItem3 = new wxMenuItem(Menu1, idMenuSettings, _("Settings"), _("Configure application Settings"), wxITEM_NORMAL);
    Menu1->Append(MenuItem3);
    MenuItem1 = new wxMenuItem(Menu1, idMenuQuit, _("Quit\tAlt-F4"), _("Quit the application"), wxITEM_NORMAL);
    Menu1->Append(MenuItem1);
    MenuBar1->Append(Menu1, _("&File"));
    Menu2 = new wxMenu();
    MenuItem2 = new wxMenuItem(Menu2, idMenuAbout, _("About\tF1"), _("Show info about this application"), wxITEM_NORMAL);
    Menu2->Append(MenuItem2);
    MenuBar1->Append(Menu2, _("Help"));
    SetMenuBar(MenuBar1);
    StatusBar1 = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    StatusBar1->SetFieldsCount(1,__wxStatusBarWidths_1);
    StatusBar1->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar1);
    Center();

    Connect(idMenuSettings,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&ToolKit3Frame::OnSettings);
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&ToolKit3Frame::OnQuit);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&ToolKit3Frame::OnAbout);
    //*)


    //  Panel7 = new wxPanel(Notebook2, ID_PANEL7, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL7"));

    sqlPanel = new SQLPanel(Notebook2, ID_SQLPANEL, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_SQLPANEL"));
    Notebook2->AddPage(sqlPanel, _("SQL"), false);

    wxFont TextCtrlLogFont(10,wxFONTFAMILY_MODERN,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Consolas"),wxFONTENCODING_DEFAULT);
    TextCtrlLog->SetFont(TextCtrlLogFont);

    Logger::setTxtCtrlLog(TextCtrlLog);

    SettingsDAO::initializeDB();

}

ToolKit3Frame::~ToolKit3Frame()
{
    //(*Destroy(ToolKit3Frame)
    //*)
}

void ToolKit3Frame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void ToolKit3Frame::OnAbout(wxCommandEvent& event)
{
    wxString msg("Built with GCC 6.1 C++14 and \r\n" + wxbuildinfo(long_f) +"\r\nby Christopher Plewright - chris@createng.com") ;
    wxMessageBox(msg, _("Welcome to ToolKit V3 ..."));
}

void ToolKit3Frame::OnSettings(wxCommandEvent& event)
{
        //wxMessageBox("Connect...", "Connection dialog" );

    // custDiag(nullptr, wxID_ANY, "Custom Dialog");

    SettingsFrame* settings_frame = new SettingsFrame(this, wxID_ANY);

    // sqlConnDlg.t
    settings_frame->Show(true);

    // return true;
}
