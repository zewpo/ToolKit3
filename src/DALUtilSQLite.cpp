#include "DALUtilSQLite.h"

namespace DALUtilSQLite
{

    void show_message(std::string const & message, long style )
    {
       Logger::log(message,Logger::kLogLevelError);
       wxMessageBox(wxString(message), wxString("SQLite Message") , style | wxSTAY_ON_TOP );
    }


    int exec_update(std::string const& sql, std::string db_file_name )
    {
        int32_t l_int_rows_returned(0);
        int32_t l_int_rows_updated(0);

        sqlite3* db;
        int l_err;
        char* err_msg = NULL;

        l_err = sqlite3_open(db_file_name.c_str(), &db);
        if( l_err ){
            Logger::log( err_msg, Logger::kLogLevelError );
            show_message(std::string(sqlite3_errmsg(db)));
        }
        else{
            l_err = sqlite3_exec(
                db,
                sql.c_str(),
                [] (void* int_return_p, int col_count, char** col_values, char** col_names) -> int {
                    int32_t* inner_int_return_p = static_cast<int32_t*>(int_return_p);
                    *inner_int_return_p += 1;
                    return 0;
                },
                static_cast<void*>(&l_int_rows_returned),
                &err_msg );

            // Logger::log( "DALUtilSQLite.exec_update() : SQL:\r\n"+sql+std::string("\r\nReturned rows: ")+std::to_string(l_int_rows_returned), Logger::kLogLevelError );

            if( l_err != SQLITE_OK ){
                Logger::log( err_msg, Logger::kLogLevelError );
                show_message(err_msg);
                sqlite3_free(err_msg);
            }
            // https://github.com/leethomason/tinyxml2
        }

        try{
            l_int_rows_updated = sqlite3_changes(db);
        }catch(std::exception& e){
            Logger::log( e.what(), Logger::kLogLevelError );
            show_message(e.what());
        }catch(...){
            Logger::log( "Error getting: DALUtilSQLite.exec_update() !!!", Logger::kLogLevelError );
            show_message("Error getting: DALUtilSQLite.exec_update() !!!");
        }

        // Logger::log( "DALUtilSQLite.exec_update() : SQL:\r\n"+sql+std::string("\r\n Updated rows: ")+std::to_string(l_int_rows_updated), Logger::kLogLevelDebug );

        try{
            sqlite3_close(db);
        }catch(...){
        }

        return l_int_rows_updated;
    }


    result_set_sqlite_t exec_read_to_rs(std::string const& sql, std::string db_file_name ){
        /*
             1. sqlite3_open()
             2. sqlite3_prepare_v2()
             3. sqlite3_step()...
                4. sqlite3_column()...
             5. sqlite3_finalize()
             6. sqlite3_close()

            1  SQLITE_INTEGER    64-bit signed integer [int sqlite3_column_int(sqlite3_stmt*, int iCol);]
            2  SQLITE_FLOAT      64-bit IEEE floating point number  [double sqlite3_column_double(sqlite3_stmt*, int iCol);]
            3  SQLITE_TEXT       string    [const unsigned char *sqlite3_column_text(sqlite3_stmt*, int iCol);]
            4  SQLITE_BLOB       BLOB   [const void *sqlite3_column_blob(sqlite3_stmt*, int iCol);]
            5  SQLITE_NULL       NULL   [null pointer, or 0]

            int sqlite3_column_bytes(sqlite3_stmt*, int iCol);
            int sqlite3_column_bytes16(sqlite3_stmt*, int iCol);

            const void *sqlite3_column_text16(sqlite3_stmt*, int iCol);

            int sqlite3_column_type(sqlite3_stmt*, int iCol);
            ?? sqlite3_value *sqlite3_column_value(sqlite3_stmt*, int iCol);
        */

        result_set_sqlite_t l_result_set;

        sqlite3* db;
        int l_err;
        // char* err_msg = NULL;
        sqlite3_stmt* stmt;

        l_err = sqlite3_open(db_file_name.c_str(), &db);
        if( l_err ){
            Logger::log( sqlite3_errmsg(db), Logger::kLogLevelError );
        }
        else{
            sqlite3_prepare_v2(
                    db,            /* sqlite3 *db           Database handle */
                    sql.c_str(),   /* const char *zSql      SQL statement, UTF-8 encoded */
                    -1,            /* int nByte             Maximum length of zSql in bytes. */
                    &stmt,         /* sqlite3_stmt **ppStmt OUT: Statement handle */
                    NULL           /* const char **pzTail   OUT: Pointer to unused portion of zSql */
                );
            while ( (l_err = sqlite3_step(stmt)) == SQLITE_ROW) {
                int l_int_cols = sqlite3_column_count(stmt);
                s_row_sqlite_t l_row;
                l_row.reserve(l_int_cols);

                for(int i=0 ; i< l_int_cols ; i++){
                    s_cell_sqlite_t l_cell;
                    l_cell.cell_name = std::string(sqlite3_column_name(stmt, i));
                    l_cell.cell_type = static_cast<s_sqlite_t>(sqlite3_column_type(stmt, i));

                    switch(sqlite3_column_type(stmt, i)){
                        case SQLITE_INTEGER :
                           l_cell.cell_integer = sqlite3_column_int(stmt, i);
                           break;
                        case SQLITE_FLOAT :
                           l_cell.cell_double = sqlite3_column_double(stmt, i);
                           break;
                        case SQLITE_TEXT :
                           l_cell.cell_string = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, i)));
                           break;
                        case SQLITE_BLOB :
                            int lint_blob_length = sqlite3_column_bytes(stmt, i);
                            const unsigned char* uc_blob_data = static_cast<const unsigned char*>(sqlite3_column_blob(stmt, i));
                            l_cell.cell_blob = std::vector<unsigned char>( uc_blob_data , uc_blob_data + lint_blob_length );
                           break;
                        //case s_null_sqlite_t :
                        //default :
                            // nothing else to do..
                    }
                    l_row.push_back(l_cell);
                }
                l_result_set.push_back(l_row);
            }

            try{
                sqlite3_finalize(stmt);
            } catch(...){}
        }

        try{
            sqlite3_close(db);
        } catch(...){}

        return l_result_set;
    }

    std::string result_set_sqlite_to_string(result_set_sqlite_t const& rs) {
        std::string lstr_return;

        // std::vector<std::vector<s_cell_sqlite_t>>
        for ( s_row_sqlite_t l_row : rs ) {
            lstr_return.append(" { ");
            for ( s_cell_sqlite_t l_cell : l_row ) {
                lstr_return.append("[");
                lstr_return.append( l_cell.cell_name );
                switch(l_cell.cell_type) {
                    case SQLITE_INTEGER :
                        lstr_return.append("(int)=");
                        lstr_return.append(std::to_string(l_cell.cell_integer) );
                        break;
                    case SQLITE_FLOAT :
                        lstr_return.append("(double)=");
                        lstr_return.append(std::to_string(l_cell.cell_double ) );
                        break;
                    case SQLITE_TEXT :
                        lstr_return.append("(string)=");
                        lstr_return.append( l_cell.cell_string );
                        break;
                    case SQLITE_BLOB :
                        lstr_return.append("(blob)=");
                        // lstr_return.append( l_cell.cell_blob ); // to Base 64
                       break;
                    case SQLITE_NULL :
                        lstr_return.append("(null)=NULL");
                }
                lstr_return.append("], ");
            }
            lstr_return.pop_back();
            lstr_return.pop_back();
            lstr_return.append(" } \r\n");
        }
        lstr_return.pop_back();
        lstr_return.pop_back();
        return lstr_return;
    }


    std::string exec_read_to_xml(std::string const& sql, std::string db_file_name ){

        sqlite3* db;

        std::string str_xml;
        str_xml.append("<xml>");

        //const char* c_sql = sql.c_str();

        int l_err;
        char* err_msg = NULL;
        l_err = sqlite3_open(db_file_name.c_str(), &db);
        if( l_err ){
            str_xml.append("<error>");
            str_xml.append("Can't open database: ");
            str_xml.append( sqlite3_errmsg(db) );
            str_xml.append("</error></xml>");
        }
        else{
            l_err = sqlite3_exec(
                db,
                sql.c_str(),
                [] (void* inner_str_xml_vp, int col_count, char** col_values, char** col_names) -> int {

                    std::string* inner_str_xml = static_cast<std::string*>(inner_str_xml_vp);

                    inner_str_xml->append("<row>");
                    for(int x = 0; x < col_count; x++) {
                       inner_str_xml->append("<").append(col_names[x]).append(">");
                       inner_str_xml->append(col_values[x] ? col_values[x] : ""  );
                       inner_str_xml->append("</").append(col_names[x]).append(">");
                    }
                    inner_str_xml->append("</row>");
                    return 0;
                },
                static_cast<void*>(&str_xml),
                &err_msg );
            if( l_err != SQLITE_OK ){
                str_xml.append("<error>");
                str_xml.append("SQL error: ");
                str_xml.append( err_msg );
                str_xml.append("</error></xml>");

                Logger::log( err_msg, Logger::kLogLevelError );
                sqlite3_free(err_msg);
            }
            // https://github.com/leethomason/tinyxml2
        }


        try{
            sqlite3_close(db);
        } catch(...){
        }

        return str_xml;
    }

}
