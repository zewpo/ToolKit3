#ifndef SETTINGSFRAME_H
#define SETTINGSFRAME_H

#include "SettingsDAO.h"

#ifndef WX_PRECOMP
	//(*HeadersPCH(SettingsFrame)
	#include <wx/srchctrl.h>
	#include <wx/sizer.h>
	#include <wx/toolbar.h>
	#include <wx/panel.h>
	#include <wx/frame.h>
	//*)
#endif
//(*Headers(SettingsFrame)
#include <wx/grid.h>
//*)

class SettingsFrame: public wxFrame
{
	public:

		SettingsFrame(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~SettingsFrame();

		//(*Declarations(SettingsFrame)
		wxToolBar* ToolBar1;
		wxPanel* Panel1;
		wxToolBarToolBase* ToolBarItem1;
		wxPanel* Panel2;
		wxGrid* Grid_Settings;
		wxSearchCtrl* SearchCtrl1;
		//*)

	protected:

		//(*Identifiers(SettingsFrame)
		static const long ID_PANEL2;
		static const long ID_SEARCHCTRL1;
		static const long ID_GRID_SETTINGS;
		static const long ID_PANEL1;
		static const long Button_Save_Settings;
		static const long ID_TOOLBAR1;
		//*)

	private:

	    // SettingsDAO* m_settings_dao;
	    settings_map* m_settings;

		//(*Handlers(SettingsFrame)
		void OnPaintSettingsFrame(wxCloseEvent& event);
		void OnCloseSettingsFrame(wxCloseEvent& event);
		void OnPaint(wxPaintEvent& event);
		void OnClose(wxCloseEvent& event);
		void OnSaveButtonClicked(wxCommandEvent& event);
		//*)

        void initialize();
        void SaveSettings();

		DECLARE_EVENT_TABLE()
};

#endif
