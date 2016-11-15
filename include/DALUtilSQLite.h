#ifndef DALUTILSQLITE_H
#define DALUTILSQLITE_H

#include "sqlite3.h"
#include <exception>
#include <stdint.h>
#include <string>
#include <vector>

#include "Logger.h"
#include "result_set_sqlite_t.h"
#include <wx/msgdlg.h>

namespace DALUtilSQLite
{

    void show_message(std::string const & message, long style = wxICON_ERROR );
    int exec_update(std::string const& sql, std::string db_file_name );
    result_set_sqlite_t exec_read_to_rs(std::string const& sql, std::string db_file_name );
    std::string exec_read_to_xml(std::string const& sql, std::string db_file_name );
    std::string result_set_sqlite_to_string(result_set_sqlite_t const& rs);
}

#endif // DALUTILSQLITE_H
