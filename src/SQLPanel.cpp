#include "wx_pch.h"
#include "SQLPanel.h"

#ifndef WX_PRECOMP
	//(*InternalHeadersPCH(SQLPanel)
	#include <wx/intl.h>
	#include <wx/string.h>
	//*)
#endif
//(*InternalHeaders(SQLPanel)
#include <wx/artprov.h>
#include <wx/bitmap.h>
#include <wx/image.h>
//*)

//(*IdInit(SQLPanel)
const long SQLPanel::ID_EXECUTEBUTTON = wxNewId();
const long SQLPanel::ID_CANCELBUTTON = wxNewId();
const long SQLPanel::ID_PANEL1 = wxNewId();
const long SQLPanel::ID_STYLEDTEXTCTRL = wxNewId();
const long SQLPanel::ID_PANEL2 = wxNewId();
const long SQLPanel::ID_MENUITEMSQLFILE = wxNewId();
const long SQLPanel::Execute = wxNewId();
//*)

BEGIN_EVENT_TABLE(SQLPanel,wxPanel)
	//(*EventTable(SQLPanel)
	//*)
END_EVENT_TABLE()

SQLPanel::SQLPanel(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size,long style,const wxString &name){

	//(*Initialize(SQLPanel)
	wxFlexGridSizer* FlexGridSizer3;
	wxFlexGridSizer* FlexGridSizer2;
	wxFlexGridSizer* FlexGridSizer1;

	Create(parent, id, wxDefaultPosition, wxSize(272,187), wxTAB_TRAVERSAL, _T("id"));
	FlexGridSizer1 = new wxFlexGridSizer(2, 1, 0, 0);
	FlexGridSizer1->AddGrowableCol(0);
	FlexGridSizer1->AddGrowableRow(1);
	Panel1 = new wxPanel(this, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
	FlexGridSizer2 = new wxFlexGridSizer(1, 5, 0, 0);
	ExecuteButton = new wxBitmapButton(Panel1, ID_EXECUTEBUTTON, wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_GO_FORWARD")),wxART_FRAME_ICON), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_EXECUTEBUTTON"));
	FlexGridSizer2->Add(ExecuteButton, 1, wxALL|wxEXPAND, 1);
	CancelButton = new wxBitmapButton(Panel1, ID_CANCELBUTTON, wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_ERROR")),wxART_FRAME_ICON), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_CANCELBUTTON"));
	FlexGridSizer2->Add(CancelButton, 1, wxALL|wxEXPAND, 1);
	Panel1->SetSizer(FlexGridSizer2);
	FlexGridSizer2->Fit(Panel1);
	FlexGridSizer2->SetSizeHints(Panel1);
	FlexGridSizer1->Add(Panel1, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	Panel2 = new wxPanel(this, ID_PANEL2, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL2"));
	FlexGridSizer3 = new wxFlexGridSizer(1, 1, 0, 0);
	FlexGridSizer3->AddGrowableCol(0);
	FlexGridSizer3->AddGrowableRow(0);
	styledTextCtrl  = new wxStyledTextCtrl(Panel2,ID_STYLEDTEXTCTRL,wxDefaultPosition,wxDefaultSize,0,_T("ID_STYLEDTEXTCTRL"));
	FlexGridSizer3->Add(styledTextCtrl , 1, wxALL|wxEXPAND, 2);
	Panel2->SetSizer(FlexGridSizer3);
	FlexGridSizer3->Fit(Panel2);
	FlexGridSizer3->SetSizeHints(Panel2);
	FlexGridSizer1->Add(Panel2, 1, wxALL|wxEXPAND, 1);
	SetSizer(FlexGridSizer1);
	MenuItemSQLFile = new wxMenuItem((&MenuSQL), ID_MENUITEMSQLFILE, _("File"), _("File"), wxITEM_NORMAL);
	MenuItemSQLFile->SetBitmap(wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_FILE_OPEN")),wxART_BUTTON));
	MenuSQL.Append(MenuItemSQLFile);
	MenuItem1 = new wxMenuItem((&MenuSQL), Execute, _("Execute"), _("Execute SQL"), wxITEM_CHECK);
	MenuSQL.Append(MenuItem1);
	SetSizer(FlexGridSizer1);
	Layout();

	Connect(ID_EXECUTEBUTTON,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SQLPanel::OnExecuteButtonClick);
	Connect(wxEVT_PAINT,(wxObjectEventFunction)&SQLPanel::OnPaint);
	//*)

	//styledTextCtrl->SetLexerLanguage("sql");

	wxColour dark_blue(50,50, 200);
	wxColour darker_blue(0,0, 150);
	wxColour light_blue(100,100, 200);
	wxColour dark_green(50,180, 50);
	wxColour dark_red(200,50, 50);
    wxColour light_gray(200,200, 200);
    wxColour orange(255,165, 0);

    /* styledTextCtrl->SetLexer(wxSTC_LEX_MSSQL);
    styledTextCtrl->StyleSetForeground(wxSTC_MSSQL_COLUMN_NAME, dark_blue );
    styledTextCtrl->StyleSetForeground(wxSTC_MSSQL_COLUMN_NAME_2 , dark_blue  );
    styledTextCtrl->StyleSetForeground(wxSTC_MSSQL_IDENTIFIER, *wxBLACK );
    styledTextCtrl->StyleSetForeground(wxSTC_MSSQL_OPERATOR , *wxBLACK );
    styledTextCtrl->StyleSetForeground(wxSTC_MSSQL_STRING  ,dark_red);
    styledTextCtrl->StyleSetForeground(wxSTC_MSSQL_COMMENT, dark_green );
    styledTextCtrl->StyleSetForeground(wxSTC_MSSQL_LINE_COMMENT, dark_green );
    styledTextCtrl->StyleSetForeground(wxSTC_MSSQL_DEFAULT, *wxBLACK );
    styledTextCtrl->StyleSetForeground(wxSTC_MSSQL_NUMBER,orange );
    styledTextCtrl->StyleSetForeground(wxSTC_MSSQL_STATEMENT , light_gray );
    */

    styledTextCtrl->SetLexer(wxSTC_LEX_SQL);

    std::string sql_reserved_words;
    sql_reserved_words.append(" ADD");
    sql_reserved_words.append(" ALL");
    sql_reserved_words.append(" ALTER");
    sql_reserved_words.append(" AND");
    sql_reserved_words.append(" ANY");
    sql_reserved_words.append(" AS");
    sql_reserved_words.append(" ASC");
    sql_reserved_words.append(" AUTHORIZATION");
    sql_reserved_words.append(" BACKUP");
    sql_reserved_words.append(" BEGIN");
    sql_reserved_words.append(" BETWEEN");
    sql_reserved_words.append(" BREAK");
    sql_reserved_words.append(" BROWSE");
    sql_reserved_words.append(" BULK");
    sql_reserved_words.append(" BY");
    sql_reserved_words.append(" CASCADE");
    sql_reserved_words.append(" CASE");
    sql_reserved_words.append(" CHECK");
    sql_reserved_words.append(" CHECKPOINT");
    sql_reserved_words.append(" CLOSE");
    sql_reserved_words.append(" CLUSTERED");
    sql_reserved_words.append(" COALESCE");
    sql_reserved_words.append(" COLLATE");
    sql_reserved_words.append(" COLUMN");
    sql_reserved_words.append(" COMMIT");
    sql_reserved_words.append(" COMPUTE");
    sql_reserved_words.append(" CONSTRAINT");
    sql_reserved_words.append(" CONTAINS");
    sql_reserved_words.append(" CONTAINSTABLE");
    sql_reserved_words.append(" CONTINUE");
    sql_reserved_words.append(" CONVERT");
    sql_reserved_words.append(" CREATE");
    sql_reserved_words.append(" CROSS");
    sql_reserved_words.append(" CURRENT");
    sql_reserved_words.append(" CURRENT_DATE");
    sql_reserved_words.append(" CURRENT_TIME");
    sql_reserved_words.append(" CURRENT_TIMESTAMP");
    sql_reserved_words.append(" CURRENT_USER");
    sql_reserved_words.append(" CURSOR");
    sql_reserved_words.append(" DATABASE");
    sql_reserved_words.append(" DBCC");
    sql_reserved_words.append(" DEALLOCATE");
    sql_reserved_words.append(" DECLARE");
    sql_reserved_words.append(" DEFAULT");
    sql_reserved_words.append(" DELETE");
    sql_reserved_words.append(" DENY");
    sql_reserved_words.append(" DESC");
    sql_reserved_words.append(" DISK");
    sql_reserved_words.append(" DISTINCT");
    sql_reserved_words.append(" DISTRIBUTED");
    sql_reserved_words.append(" DOUBLE");
    sql_reserved_words.append(" DROP");
    sql_reserved_words.append(" DUMP");
    sql_reserved_words.append(" ELSE");
    sql_reserved_words.append(" END");
    sql_reserved_words.append(" ERRLVL");
    sql_reserved_words.append(" ESCAPE");
    sql_reserved_words.append(" EXCEPT");
    sql_reserved_words.append(" EXEC");
    sql_reserved_words.append(" EXECUTE");
    sql_reserved_words.append(" EXISTS");
    sql_reserved_words.append(" EXIT");
    sql_reserved_words.append(" EXTERNAL");
    sql_reserved_words.append(" FETCH");
    sql_reserved_words.append(" FILE");
    sql_reserved_words.append(" FILLFACTOR");
    sql_reserved_words.append(" FOR");
    sql_reserved_words.append(" FOREIGN");
    sql_reserved_words.append(" FREETEXT");
    sql_reserved_words.append(" FREETEXTTABLE");
    sql_reserved_words.append(" FROM");
    sql_reserved_words.append(" FULL");
    sql_reserved_words.append(" FUNCTION");
    sql_reserved_words.append(" GOTO");
    sql_reserved_words.append(" GRANT");
    sql_reserved_words.append(" GROUP");
    sql_reserved_words.append(" HAVING");
    sql_reserved_words.append(" HOLDLOCK");
    sql_reserved_words.append(" IDENTITY");
    sql_reserved_words.append(" IDENTITY_INSERT");
    sql_reserved_words.append(" IDENTITYCOL");
    sql_reserved_words.append(" IF");
    sql_reserved_words.append(" IN");
    sql_reserved_words.append(" INDEX");
    sql_reserved_words.append(" INNER");
    sql_reserved_words.append(" INSERT");
    sql_reserved_words.append(" INTERSECT");
    sql_reserved_words.append(" INTO");
    sql_reserved_words.append(" IS");
    sql_reserved_words.append(" JOIN");
    sql_reserved_words.append(" KEY");
    sql_reserved_words.append(" KILL");
    sql_reserved_words.append(" LEFT");
    sql_reserved_words.append(" LIKE");
    sql_reserved_words.append(" LINENO");
    sql_reserved_words.append(" LOAD");
    sql_reserved_words.append(" MERGE");
    sql_reserved_words.append(" NATIONAL");
    sql_reserved_words.append(" NOCHECK");
    sql_reserved_words.append(" NONCLUSTERED");
    sql_reserved_words.append(" NOT");
    sql_reserved_words.append(" NULL");
    sql_reserved_words.append(" NULLIF");
    sql_reserved_words.append(" OF");
    sql_reserved_words.append(" OFF");
    sql_reserved_words.append(" OFFSETS");
    sql_reserved_words.append(" ON");
    sql_reserved_words.append(" OPEN");
    sql_reserved_words.append(" OPENDATASOURCE");
    sql_reserved_words.append(" OPENQUERY");
    sql_reserved_words.append(" OPENROWSET");
    sql_reserved_words.append(" OPENXML");
    sql_reserved_words.append(" OPTION");
    sql_reserved_words.append(" OR");
    sql_reserved_words.append(" ORDER");
    sql_reserved_words.append(" OUTER");
    sql_reserved_words.append(" OVER");
    sql_reserved_words.append(" PERCENT");
    sql_reserved_words.append(" PIVOT");
    sql_reserved_words.append(" PLAN");
    sql_reserved_words.append(" PRECISION");
    sql_reserved_words.append(" PRIMARY");
    sql_reserved_words.append(" PRINT");
    sql_reserved_words.append(" PROC");
    sql_reserved_words.append(" PROCEDURE");
    sql_reserved_words.append(" PUBLIC");
    sql_reserved_words.append(" RAISERROR");
    sql_reserved_words.append(" READ");
    sql_reserved_words.append(" READTEXT");
    sql_reserved_words.append(" RECONFIGURE");
    sql_reserved_words.append(" REFERENCES");
    sql_reserved_words.append(" REPLICATION");
    sql_reserved_words.append(" RESTORE");
    sql_reserved_words.append(" RESTRICT");
    sql_reserved_words.append(" RETURN");
    sql_reserved_words.append(" REVERT");
    sql_reserved_words.append(" REVOKE");
    sql_reserved_words.append(" RIGHT");
    sql_reserved_words.append(" ROLLBACK");
    sql_reserved_words.append(" ROWCOUNT");
    sql_reserved_words.append(" ROWGUIDCOL");
    sql_reserved_words.append(" RULE");
    sql_reserved_words.append(" SAVE");
    sql_reserved_words.append(" SCHEMA");
    sql_reserved_words.append(" SECURITYAUDIT");
    sql_reserved_words.append(" SELECT");
    sql_reserved_words.append(" SEMANTICKEYPHRASETABLE");
    sql_reserved_words.append(" SEMANTICSIMILARITYDETAILSTABLE");
    sql_reserved_words.append(" SEMANTICSIMILARITYTABLE");
    sql_reserved_words.append(" SESSION_USER");
    sql_reserved_words.append(" SET");
    sql_reserved_words.append(" SETUSER");
    sql_reserved_words.append(" SHUTDOWN");
    sql_reserved_words.append(" SOME");
    sql_reserved_words.append(" STATISTICS");
    sql_reserved_words.append(" SYSTEM_USER");
    sql_reserved_words.append(" TABLE");
    sql_reserved_words.append(" TABLESAMPLE");
    sql_reserved_words.append(" TEXTSIZE");
    sql_reserved_words.append(" THEN");
    sql_reserved_words.append(" TO");
    sql_reserved_words.append(" TOP");
    sql_reserved_words.append(" TRAN");
    sql_reserved_words.append(" TRANSACTION");
    sql_reserved_words.append(" TRIGGER");
    sql_reserved_words.append(" TRUNCATE");
    sql_reserved_words.append(" TRY_CONVERT");
    sql_reserved_words.append(" TSEQUAL");
    sql_reserved_words.append(" UNION");
    sql_reserved_words.append(" UNIQUE");
    sql_reserved_words.append(" UNPIVOT");
    sql_reserved_words.append(" UPDATE");
    sql_reserved_words.append(" UPDATETEXT");
    sql_reserved_words.append(" USE");
    sql_reserved_words.append(" USER");
    sql_reserved_words.append(" VALUES");
    sql_reserved_words.append(" VARYING");
    sql_reserved_words.append(" VIEW");
    sql_reserved_words.append(" WAITFOR");
    sql_reserved_words.append(" WHEN");
    sql_reserved_words.append(" WHERE");
    sql_reserved_words.append(" WHILE");
    sql_reserved_words.append(" WITH");
    sql_reserved_words.append(" WITHIN GROUP");
    sql_reserved_words.append(" WRITETEXT");

    std::transform( sql_reserved_words.begin(), sql_reserved_words.end(), sql_reserved_words.begin(), ::tolower);

    styledTextCtrl->SetKeyWords(wxSTC_SQL_WORD,sql_reserved_words  );

    styledTextCtrl->StyleSetForeground( wxSTC_SQL_COMMENT , dark_green );// 1
    styledTextCtrl->StyleSetForeground( wxSTC_SQL_COMMENTLINE , dark_green );//  2
    styledTextCtrl->StyleSetForeground( wxSTC_SQL_COMMENTDOC , dark_green );//  3
    styledTextCtrl->StyleSetForeground( wxSTC_SQL_NUMBER , orange );//  4
    styledTextCtrl->StyleSetForeground( wxSTC_SQL_WORD , *wxGREEN );//  5
    styledTextCtrl->StyleSetForeground( wxSTC_SQL_STRING , dark_red );//  6
    styledTextCtrl->StyleSetForeground( wxSTC_SQL_CHARACTER , dark_red );//  7
    styledTextCtrl->StyleSetForeground( wxSTC_SQL_SQLPLUS , dark_green );//  8
    styledTextCtrl->StyleSetForeground( wxSTC_SQL_SQLPLUS_PROMPT , *wxBLACK );//  9
    styledTextCtrl->StyleSetForeground( wxSTC_SQL_OPERATOR , *wxBLACK );//  10
    styledTextCtrl->StyleSetForeground( wxSTC_SQL_IDENTIFIER , light_blue );//  11
    styledTextCtrl->StyleSetForeground( wxSTC_SQL_SQLPLUS_COMMENT , dark_green );//  13
    styledTextCtrl->StyleSetForeground( wxSTC_SQL_COMMENTLINEDOC , dark_green );//  15
    styledTextCtrl->StyleSetForeground( wxSTC_SQL_WORD2 , dark_green );//  16
    styledTextCtrl->StyleSetForeground( wxSTC_SQL_COMMENTDOCKEYWORD , dark_green );//  17
    styledTextCtrl->StyleSetForeground( wxSTC_SQL_COMMENTDOCKEYWORDERROR , dark_green );//  18
    styledTextCtrl->StyleSetForeground( wxSTC_SQL_USER1 , darker_blue );//  19
    styledTextCtrl->StyleSetForeground( wxSTC_SQL_USER2 , darker_blue );//  20
    styledTextCtrl->StyleSetForeground( wxSTC_SQL_USER3 , darker_blue );//  21
    styledTextCtrl->StyleSetForeground( wxSTC_SQL_USER4 , darker_blue );//  22
    styledTextCtrl->StyleSetForeground( wxSTC_SQL_QUOTEDIDENTIFIER , dark_green );//  23

   // styledTextCtrl->StyleSetForeground(0, *wxBLACK);
    // styledTextCtrl->StyleSetBackground(0, wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOW));
    // styledTextCtrl->StyleSetFont(0, *wxFont );
    // styledTextCtrl->SetIndicatorCurrent(2);
    // styledTextCtrl->IndicatorFillRange(0,10);

    styledTextCtrl->SetMarginType(0,wxSTC_MARGIN_NUMBER);
    styledTextCtrl->SetMarginWidth(0,20);
    styledTextCtrl->SetZoom(2);


    // styledTextCtrl->StyleSetForeground(wxSTC_STYLE_DEFAULT , *wxBLUE );

}

//SQLPanel::SQLPanel(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
//{
//}

SQLPanel::~SQLPanel()
{
	//(*Destroy(SQLPanel)
	//*)
}


void SQLPanel::OnPaint(wxPaintEvent& event)
{

}

void SQLPanel::OnExecuteButtonClick(wxCommandEvent& event)
{
    DALUtilMSSQL::exec_update("select * from cars");
}
