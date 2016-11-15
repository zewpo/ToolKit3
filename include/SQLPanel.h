#ifndef SQLPANEL_H
#define SQLPANEL_H
#include <wx/stc/stc.h>

#include "DALUtilMSSQL.h"

#ifndef WX_PRECOMP
	//(*HeadersPCH(SQLPanel)
	#include <wx/sizer.h>
	#include <wx/menu.h>
	#include <wx/panel.h>
	#include <wx/bmpbuttn.h>
	//*)
#endif
//(*Headers(SQLPanel)
//*)

class SQLPanel: public wxPanel
{
	public:

              //  Notebook2,        ID_SQLPANEL,                     wxDefaultPosition,                  wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_SQLPANEL")
        SQLPanel(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize,long style=wxTAB_TRAVERSAL,const wxString &name=wxPanelNameStr);
		// SQLPanel(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~SQLPanel();

		//(*Declarations(SQLPanel)
		wxMenuItem* MenuItem1;
		wxPanel* Panel1;
		wxMenu MenuSQL;
		wxMenuItem* MenuItemSQLFile;
		wxPanel* Panel2;
		wxBitmapButton* ExecuteButton;
		wxStyledTextCtrl* styledTextCtrl ;
		wxBitmapButton* CancelButton;
		//*)

	protected:

		//(*Identifiers(SQLPanel)
		static const long ID_EXECUTEBUTTON;
		static const long ID_CANCELBUTTON;
		static const long ID_PANEL1;
		static const long ID_STYLEDTEXTCTRL;
		static const long ID_PANEL2;
		static const long ID_MENUITEMSQLFILE;
		static const long Execute;
		//*)

	private:

		//(*Handlers(SQLPanel)
		void OnPaint(wxPaintEvent& event);
		void OnExecuteButtonClick(wxCommandEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
