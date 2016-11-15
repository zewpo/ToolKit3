#ifndef ODBCVER
#define ODBCVER 0x0351
#endif

#ifndef DALUTILMSSQL_H
#define DALUTILMSSQL_H

#include <windows.h>

#include <stdint.h>
#include <sql.h>
#include <sqlext.h>

#include "SettingsDAO.h"

#include <exception>
#include <string>
#include <locale>
#include <sstream>
#include <vector>

#include <wx/msgdlg.h>

namespace DALUtilMSSQL
{
    void show_message(const std::string& str, long style = wxICON_ERROR);
    void show_sql_message(unsigned int handletype, const SQLHANDLE& handle, long style = wxICON_ERROR );
    int exec_update(const std::string& sql);
    SQLWCHAR* to_sqlwchar(const std::string& str);
    std::string to_narrow( const std::wstring & ws, char dfault = '?', const std::locale& loc = std::locale() );
    std::string to_narrow( const wchar_t* s );

}

#endif // DALUTILMSSQL_H
