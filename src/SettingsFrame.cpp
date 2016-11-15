#include "wx_pch.h"
#include "SettingsFrame.h"


#ifndef WX_PRECOMP
	//(*InternalHeadersPCH(SettingsFrame)
	#include <wx/intl.h>
	#include <wx/string.h>
	//*)
#endif
//(*InternalHeaders(SettingsFrame)
#include <wx/artprov.h>
#include <wx/bitmap.h>
#include <wx/icon.h>
#include <wx/image.h>
//*)

//(*IdInit(SettingsFrame)
const long SettingsFrame::ID_PANEL2 = wxNewId();
const long SettingsFrame::ID_SEARCHCTRL1 = wxNewId();
const long SettingsFrame::ID_GRID_SETTINGS = wxNewId();
const long SettingsFrame::ID_PANEL1 = wxNewId();
const long SettingsFrame::Button_Save_Settings = wxNewId();
const long SettingsFrame::ID_TOOLBAR1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(SettingsFrame,wxFrame)
	//(*EventTable(SettingsFrame)
	//*)
END_EVENT_TABLE()

SettingsFrame::SettingsFrame(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(SettingsFrame)
	wxFlexGridSizer* FlexGridSizer3;
	wxFlexGridSizer* FlexGridSizer2;
	wxFlexGridSizer* FlexGridSizer1;

	Create(parent, wxID_ANY, _("Settings"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
	SetClientSize(wxSize(600,553));
	{
		wxIcon FrameIcon;
		FrameIcon.CopyFromBitmap(wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_EXECUTABLE_FILE")),wxART_FRAME_ICON));
		SetIcon(FrameIcon);
	}
	FlexGridSizer1 = new wxFlexGridSizer(1, 1, 0, 0);
	FlexGridSizer1->AddGrowableCol(0);
	FlexGridSizer1->AddGrowableRow(0);
	Panel1 = new wxPanel(this, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
	Panel1->SetMinSize(wxSize(-1,-1));
	Panel1->SetMaxSize(wxSize(-1,-1));
	FlexGridSizer2 = new wxFlexGridSizer(3, 1, 0, 0);
	FlexGridSizer2->AddGrowableCol(0);
	FlexGridSizer2->AddGrowableRow(2);
	Panel2 = new wxPanel(Panel1, ID_PANEL2, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL2"));
	Panel2->SetMinSize(wxSize(-1,-1));
	Panel2->SetMaxSize(wxSize(-1,-1));
	FlexGridSizer3 = new wxFlexGridSizer(0, 3, 0, 0);
	FlexGridSizer3->AddGrowableCol(0);
	FlexGridSizer3->AddGrowableCol(1);
	FlexGridSizer3->AddGrowableCol(2);
	FlexGridSizer3->AddGrowableRow(0);
	Panel2->SetSizer(FlexGridSizer3);
	FlexGridSizer3->Fit(Panel2);
	FlexGridSizer3->SetSizeHints(Panel2);
	FlexGridSizer2->Add(Panel2, 1, wxALL|wxEXPAND, 2);
	SearchCtrl1 = new wxSearchCtrl(Panel1, ID_SEARCHCTRL1, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_SEARCHCTRL1"));
	SearchCtrl1->SetMinSize(wxSize(-1,-1));
	SearchCtrl1->SetMaxSize(wxSize(-1,-1));
	FlexGridSizer2->Add(SearchCtrl1, 1, wxALL|wxEXPAND, 2);
	Grid_Settings = new wxGrid(Panel1, ID_GRID_SETTINGS, wxDefaultPosition, wxDefaultSize, 0, _T("ID_GRID_SETTINGS"));
	Grid_Settings->CreateGrid(0,2);
	Grid_Settings->SetMinSize(wxSize(-1,-1));
	Grid_Settings->SetMaxSize(wxSize(-1,-1));
	Grid_Settings->EnableEditing(true);
	Grid_Settings->EnableGridLines(true);
	Grid_Settings->SetRowLabelSize(20);
	Grid_Settings->SetDefaultCellFont( Grid_Settings->GetFont() );
	Grid_Settings->SetDefaultCellTextColour( Grid_Settings->GetForegroundColour() );
	FlexGridSizer2->Add(Grid_Settings, 1, wxALL|wxEXPAND, 2);
	Panel1->SetSizer(FlexGridSizer2);
	FlexGridSizer2->Fit(Panel1);
	FlexGridSizer2->SetSizeHints(Panel1);
	FlexGridSizer1->Add(Panel1, 1, wxALL|wxEXPAND, 0);
	SetSizer(FlexGridSizer1);
	ToolBar1 = new wxToolBar(this, ID_TOOLBAR1, wxDefaultPosition, wxDefaultSize, wxTB_HORIZONTAL|wxNO_BORDER, _T("ID_TOOLBAR1"));
	ToolBarItem1 = ToolBar1->AddTool(Button_Save_Settings, _("Save Settings"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_FILE_SAVE")),wxART_BUTTON), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_FILE_SAVE")),wxART_BUTTON), wxITEM_NORMAL, _("Save Settings"), wxEmptyString);
	ToolBar1->Realize();
	SetToolBar(ToolBar1);
	SetSizer(FlexGridSizer1);
	Layout();
	Center();

	Connect(Button_Save_Settings,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&SettingsFrame::OnSaveButtonClicked);
	Connect(wxEVT_PAINT,(wxObjectEventFunction)&SettingsFrame::OnPaint);
	//*)

    this->initialize();
}

void SettingsFrame::initialize(){
    // m_settings_dao = new SettingsDAO();
    m_settings = SettingsDAO::get_all_properties();
    wxGridStringTable* settings_table_data = new wxGridStringTable(m_settings->size(), 2 );

    settings_table_data->SetColLabelValue(0,"Property Name");   //m_colLabels({"Property Name","Property Value"});
    settings_table_data->SetColLabelValue(1,"Property Value");

    Grid_Settings->SetTable(settings_table_data);

    int row_no = 0;
    for( settings_map::iterator i = m_settings->begin() ; i != m_settings->end() ;  i++ ){
        property_t prop = i->second;

        Logger::log(std::to_string(row_no).append(" ").append(prop.name).append(" : [").append(prop.value).append("]") , Logger::kLogLevelDebug);
        settings_table_data->SetValue(row_no,0,prop.name);
        settings_table_data->SetValue(row_no,1,prop.value);
        Grid_Settings->SetReadOnly(row_no,0);
        if( ! prop.editable) {
          Grid_Settings->SetReadOnly(row_no,1);
        }
        if(prop.name.find("password")!=std::string::npos){
             Grid_Settings->SetCellValue(row_no,1,"********");
        }
        row_no++;
    }

    Grid_Settings->SetColSize(0,160);
    Grid_Settings->SetColSize(1,420);
}

SettingsFrame::~SettingsFrame()
{
    this->SaveSettings();

	//(*Destroy(SettingsFrame)
	//*)
}


void SettingsFrame::OnPaint(wxPaintEvent& event)
{
}

//void SettingsFrame::OnClose(wxCloseEvent& event)
//{
//    // Close();
//}

void SettingsFrame::OnSaveButtonClicked(wxCommandEvent& event) {
    this->SaveSettings();
}

void SettingsFrame::SaveSettings(){
    Grid_Settings->SaveEditControlValue();
    Grid_Settings->HideCellEditControl();
    Grid_Settings->ClearSelection();


    wxGridStringTable* settings_table_data = static_cast<wxGridStringTable*>(Grid_Settings->GetTable());
    Logger::log("SaveSettings : settings_table_data->GetNumberRows() = " + std::to_string(settings_table_data->GetNumberRows() ) ,Logger::kLogLevelDebug);

    // Grid_Settings->GetCellValue();
    for( int i = 0 ; i < settings_table_data->GetNumberRows() ;  i++ ){
        property_t prop;
        prop.name = settings_table_data->GetValue(i,0);
        prop.value = settings_table_data->GetValue(i,1);
        if ( ! Grid_Settings->IsReadOnly(i,1)  &&
             ( prop.name.find("password")==std::string::npos ||
               ( prop.name.find("password")!=std::string::npos
                  && prop.value!="********" ) ) ) {
             prop.editable = true;
             SettingsDAO::set_property(prop);
        }
    }

    m_settings = SettingsDAO::get_all_properties();
    Grid_Settings->ForceRefresh();

}
