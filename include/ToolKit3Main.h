/***************************************************************
 * Name:      ToolKit3Main.h
 * Purpose:   Defines Application Frame
 * Author:    Christopher Plewright (chris@createng.com)
 * Created:   2016-10-08
 * Copyright: Christopher Plewright (www.createng.com)
 * License:
 **************************************************************/

#ifndef ToolKit3MAIN_H
#define ToolKit3MAIN_H

#include "wx_pch.h"
#include <wx/msgdlg.h>
#include "SettingsFrame.h"
#include "SQLPanel.h"


//(*Headers(ToolKit3Frame)
#include <wx/srchctrl.h>
#include <wx/treectrl.h>
#include <wx/notebook.h>
#include <wx/sizer.h>
#include <wx/menu.h>
#include <wx/textctrl.h>
#include <wx/splitter.h>
#include <wx/panel.h>
#include <wx/grid.h>
#include <wx/bmpbuttn.h>
#include <wx/frame.h>
#include <wx/statusbr.h>
//*)

class ToolKit3Frame: public wxFrame
{
    public:

        ToolKit3Frame(wxWindow* parent,wxWindowID id = -1);
        virtual ~ToolKit3Frame();

    private:

        //(*Handlers(ToolKit3Frame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnSettings(wxCommandEvent& event);
        void OnPanel1Paint(wxPaintEvent& event);
        void OnNotebook2PageChanged(wxNotebookEvent& event);
        void OnPanelLogPaint(wxPaintEvent& event);
        //*)


        static const long ID_SQLPANEL;
        //(*Identifiers(ToolKit3Frame)
        static const long ID_SEARCHCTRL1;
        static const long ID_TREECTRL1;
        static const long ID_PANEL1;
        static const long ID_NOTEBOOK1;
        static const long ID_BITMAPBUTTON1;
        static const long ID_PANEL3;
        static const long ID_GRID1;
        static const long ID_PANEL4;
        static const long ID_PANEL2;
        static const long ID_SPLITTERWINDOW2;
        static const long ID_PANEL5;
        static const long ID_PANEL6;
        static const long ID_PANEL7;
        static const long ID_NOTEBOOK2;
        static const long ID_TEXTCTRLLOG;
        static const long ID_PANELLOG;
        static const long ID_NOTEBOOK3;
        static const long ID_SPLITTERWINDOW3;
        static const long ID_SPLITTERWINDOW1;
        static const long idMenuSettings;
        static const long idMenuQuit;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        //*)

        SQLPanel* sqlPanel;
        //(*Declarations(ToolKit3Frame)
        wxPanel* Panel5;
        wxPanel* Panel_Screens;
        wxNotebook* Notebook1;
        wxPanel* PanelLog;
        wxPanel* Panel4;
        wxTextCtrl* TextCtrlLog;
        wxSplitterWindow* SplitterWindow2;
        wxGrid* Grid1;
        wxBitmapButton* BitmapButton1;
        wxPanel* Panel6;
        wxPanel* Panel3;
        wxMenuItem* MenuItem3;
        wxPanel* Panel7;
        wxStatusBar* StatusBar1;
        wxSplitterWindow* SplitterWindow3;
        wxTreeCtrl* TreeCtrl1;
        wxPanel* Panel2;
        wxNotebook* Notebook2;
        wxSplitterWindow* SplitterWindow1;
        wxNotebook* Notebook3;
        wxSearchCtrl* SearchCtrl1;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // ToolKit3MAIN_H
