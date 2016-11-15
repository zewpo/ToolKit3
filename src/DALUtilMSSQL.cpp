#include "DALUtilMSSQL.h"

namespace DALUtilMSSQL
{
    SQLWCHAR* to_sqlwchar(const std::string& str)
    {
        return static_cast<SQLWCHAR*>(wcsdup(std::wstring(str.begin(), str.end() ).c_str()));
    }


    std::string to_narrow( const wchar_t* s )
    {
        return to_narrow( std::wstring(s) );
    }

    std::string to_narrow( const std::wstring & ws, char dfault , const std::locale& loc )
    {
        const wchar_t *s = ws.data();
        std::ostringstream stm;
        while( *s != L'\0' )
        {
            stm << std::use_facet< std::ctype<wchar_t> >( loc ).narrow( *s++, dfault );
        }
        return stm.str();
    }

    void show_message(std::string const & message, long style )
    {
       Logger::log(message,Logger::kLogLevelError);
       wxMessageBox(wxString(message), wxString("DALUtilMSSQL message") , style | wxSTAY_ON_TOP );
    }

    void show_sql_message(unsigned int handletype, const SQLHANDLE& handle, long style)
    {
        SQLWCHAR sqlstate[1024];
        SQLWCHAR sqlmsg[1024];
        if(SQL_SUCCESS == SQLGetDiagRec(handletype, handle, 1, sqlstate, NULL, sqlmsg, 1024, NULL))
        {
            std::string lstr_sqlmsg = to_narrow(std::wstring(sqlmsg));
            std::string lstr_sqlstate = to_narrow(std::wstring(sqlstate));

            wxString msg("Message: " + lstr_sqlmsg + "\nSQLSTATE: " + lstr_sqlstate);

            if ( msg.find("Changed database context") == std::string::npos )
            {
                Logger::log(std::string(msg.c_str()),Logger::kLogLevelError);
                wxMessageBox(msg, wxString("MS-SQL Message") , style | wxSTAY_ON_TOP );
            }
        }
    }

    int exec_update(const std::string& sql)
    {

        try{
            SQLHANDLE sqlenvhandle;
            SQLHANDLE sqlconnectionhandle;
            SQLHANDLE sqlstatementhandle;
            SQLRETURN retcode;

            std::string host( SettingsDAO::get_property("dada.db.server.host"));
            std::string port( SettingsDAO::get_property("dada.db.server.port"));
            std::string dbname( SettingsDAO::get_property("dada.db.database.name"));
            std::string dbuser( SettingsDAO::get_property("dada.db.database.user"));
            std::string dbpassword( SettingsDAO::get_property("dada.db.database.password"));

            std::string conn_string;
            conn_string.append("DRIVER={SQL Server};");
            conn_string.append("SERVER=").append(host).append(", ").append(port).append(";");
            conn_string.append("DATABASE=").append(dbname).append(";");
            conn_string.append("UID=").append(dbuser).append(";");
            conn_string.append("PWD=").append(dbpassword).append(";");


            do
            {
                if(SQL_SUCCESS!=SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &sqlenvhandle))
                    break;

                if(SQL_SUCCESS!=SQLSetEnvAttr(sqlenvhandle,SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0))
                    break;

                if(SQL_SUCCESS!=SQLAllocHandle(SQL_HANDLE_DBC, sqlenvhandle, &sqlconnectionhandle))
                    break;

                Logger::log( "Connecting to : "+conn_string , Logger::kLogLevelDebug);

                SQLWCHAR retconstring[1024];
                switch(SQLDriverConnect (sqlconnectionhandle, NULL,
                        to_sqlwchar(conn_string),
                        SQL_NTS, retconstring, 1024, NULL,SQL_DRIVER_NOPROMPT))
                {
                    case SQL_SUCCESS_WITH_INFO:
                        Logger::log( "SQL_SUCCESS_WITH_INFO", Logger::kLogLevelError);
                        show_sql_message(SQL_HANDLE_DBC, sqlconnectionhandle,wxICON_INFORMATION);
                        break;
                    case SQL_INVALID_HANDLE:
                    case SQL_ERROR:
                        Logger::log( "SQL_INVALID_HANDLE or SQL_ERROR", Logger::kLogLevelError);
                        show_sql_message(SQL_HANDLE_DBC, sqlconnectionhandle);
                        retcode = -1;
                        break;
                    default:
                        break;
                }

                if(retcode == -1)
                    break;

                if(SQL_SUCCESS!=SQLAllocHandle(SQL_HANDLE_STMT, sqlconnectionhandle, &sqlstatementhandle))
                    break;

                SQLWCHAR* sqls = to_sqlwchar( sql );
                Logger::log("sql = "+ sql, Logger::kLogLevelDebug );

                if(SQL_SUCCESS!=SQLExecDirect(sqlstatementhandle,sqls, SQL_NTS))
                {
                    show_sql_message(SQL_HANDLE_STMT, sqlstatementhandle);
                    break;
                }
                else
                {

                    retcode = SQL_SUCCESS;
                    int r=0;
                    while( retcode == SQL_SUCCESS || retcode  == SQL_SUCCESS_WITH_INFO ) // while there is each new row...
                    {   // and not SQLCancel Function
                       retcode = SQLFetch(sqlstatementhandle);
                        //Logger::log( " | SQLFetch retcode " + std::to_string(retcode) , Logger::kLogLevelDebug);

                        ++r;

                        //if(retcode  == SQL_SUCCESS_WITH_INFO){
                        //    show_sql_message(SQL_HANDLE_STMT, sqlstatementhandle);
                       // }

                        switch(retcode)
                        {
                            case SQL_SUCCESS:
                                // Logger::log( " | SQLFetch retcode : SQL_SUCCESS " + std::to_string(retcode) , Logger::kLogLevelDebug);
                                break;
                            case SQL_SUCCESS_WITH_INFO:
                                Logger::log( " | SQLFetch retcode : SQL_SUCCESS_WITH_INFO " + std::to_string(retcode) , Logger::kLogLevelDebug);
                                show_sql_message(SQL_HANDLE_STMT, sqlstatementhandle);
                                break;
                            case SQL_NO_DATA:
                                Logger::log( " | SQLFetch retcode : SQL_NO_DATA " + std::to_string(retcode) , Logger::kLogLevelDebug);
                                break;
                            case SQL_STILL_EXECUTING:
                                Logger::log( " | SQLFetch retcode : SQL_STILL_EXECUTING " + std::to_string(retcode) , Logger::kLogLevelDebug);
                                break;
                            case SQL_ERROR:
                                Logger::log( " | SQLFetch retcode : SQL_ERROR " + std::to_string(retcode) , Logger::kLogLevelDebug);
                                show_sql_message(SQL_HANDLE_STMT, sqlstatementhandle);
                                break;
                            case SQL_INVALID_HANDLE:
                                Logger::log( " | SQLFetch retcode : SQL_INVALID_HANDLE " + std::to_string(retcode) , Logger::kLogLevelDebug);
                                show_message("SQL_INVALID_HANDLE");
                                break;
                            default:
                                Logger::log( " | SQLFetch retcode : DIDNT SWITCH ON " + std::to_string(retcode) , Logger::kLogLevelDebug);
                                show_message("retcode : DIDNT SWITCH ON " + std::to_string(retcode) );

                        }


                        short column_count;

                        SQLNumResultCols( sqlstatementhandle,&column_count);
                        // Logger::log( " | Columns : " + std::to_string(column_count) + " " , Logger::kLogLevelDebug);

                        //SQLUSMALLINT u_column_count = static_cast<SQLUSMALLINT>(column_count);
                        //Logger::log( " | U Columns : " + std::to_string(u_column_count) + " " , Logger::kLogLevelDebug);

                        for (unsigned short i = 1; i <= column_count; i++ )  // for each column in the row.
                        {

                            SQLWCHAR*    column_name;
                            SQLSMALLINT  column_name_length;
                            SQLSMALLINT  column_type;
                            SQLULEN      column_length;
                            SQLSMALLINT  number_of_decimal_digits;
                            SQLSMALLINT  column_nullable;

                            SQLPOINTER   column_value;
                            SQLLEN*      value_length_or_null;

                            SQLRETURN sqlr = SQL_SUCCESS;

                            try{
                                sqlr = SQLDescribeCol(
                                      sqlstatementhandle,        // [input]    SQLHSTMT   StatementHandle
                                      i,                         // [input]    SQLUSMALLINT   ColumnNumber
                                      column_name,              // [Output]   SQL(W)CHAR *      ColumnName
                                      128,                       // [input]    SQLSMALLINT    BufferLength
                                      &column_name_length,       // [Output]   SQLSMALLINT *  NameLengthPtr
                                      &column_type,              // [Output]   SQLSMALLINT *  DataTypePtr
                                      &column_length,            // [Output]   SQLULEN *      ColumnSizePtr
                                      &number_of_decimal_digits, // [Output]   SQLSMALLINT *  DecimalDigitsPtr
                                      &column_nullable);         // [Output]   SQLSMALLINT *  NullablePtr

                                // Logger::log( " | SQLRETURN sqlr " + std::to_string(sqlr), Logger::kLogLevelDebug);

                            }catch(std::exception& e){
                                Logger::log( e.what(), Logger::kLogLevelError );
                                try{ show_sql_message(SQL_HANDLE_STMT, sqlstatementhandle); } catch (...){}
                                show_message(e.what());
                            }catch(...){
                                Logger::log( "Error getting: DALUtilMSSQL.exec_update() SQLDescribeCol!!!", Logger::kLogLevelError );
                                try{ show_sql_message(SQL_HANDLE_STMT, sqlstatementhandle); } catch (...){}
                                show_message("Error getting: DALUtilMSSQL.exec_update() SQLDescribeCol!!!");
                            }

                            switch(sqlr)
                            {
                                case SQL_SUCCESS:
                                    //  Logger::log( " | sqlr : SQL_SUCCESS " + std::to_string(sqlr) , Logger::kLogLevelDebug);
                                    break;
                                case SQL_SUCCESS_WITH_INFO:
                                    Logger::log( " | sqlr : SQL_SUCCESS_WITH_INFO " + std::to_string(sqlr) , Logger::kLogLevelDebug);
                                    break;
                                case SQL_STILL_EXECUTING:
                                    Logger::log( " | sqlr : SQL_STILL_EXECUTING " + std::to_string(sqlr) , Logger::kLogLevelDebug);
                                    break;
                                case SQL_ERROR:
                                    Logger::log( " | sqlr : SQL_ERROR " + std::to_string(sqlr) , Logger::kLogLevelDebug);
                                    break;
                                case SQL_INVALID_HANDLE:
                                    Logger::log( " | sqlr : SQL_INVALID_HANDLE " + std::to_string(sqlr) , Logger::kLogLevelDebug);
                                    break;
                                default:
                                    Logger::log( " | SQLDescribeCol sqlr : DIDN'T SWITCH ON " + std::to_string(sqlr) , Logger::kLogLevelDebug);
                            }

                            std::string msg_init(" | r: "+std::to_string(r)+", c: " + std::to_string(i) + ", " + to_narrow(column_name) +",  ["+std::to_string(column_type)+" : ");
                            std::string msg_post("");

                            SQLRETURN sqlr_get_data;
                            if(sqlr == SQL_SUCCESS || sqlr == SQL_SUCCESS_WITH_INFO){

                                //SQLRETURN sqlr_data_available;
                                //SQLPOINTER*   value_ptr_ptr;
                                //sqlr_data_available = SQLParamData(sqlstatementhandle,value_ptr_ptr );

                                //msg_post.append(" BUFFER HAS DATA ? ").append(std::to_string(sqlr_data_available)).append(" , COLUMN_LENGTH = ").append(std::to_string(column_length)).append(" ");
                                //if(SQL_PARAM_DATA_AVAILABLE == sqlr_data_available){
                         //           sqlr_get_data = SQLGetData(
                         //               sqlstatementhandle,                 // SQLHSTMT StatementHandle [aka SQLHANDLE]
                         //               i,                                  // SQLUSMALLINT ColumnNumber
                         //               column_type,                        // SQLSMALLINT TargetType
                         //               column_value,                       // SQLPOINTER TargetValue
                         //               static_cast<SQLLEN>(column_length), // SQLLEN BufferLength
                         //               value_length_or_null);              // SQLLEN* StrLen_or_Ind
                               //     msg_post.append(" BUFFER HAS DATA ");
                               // }else {
                               //     msg_post.append(" BUFFER HAS NO DATA ");
                               // }


                                    // SQLUSMALLINT j = 0;
                                    //void* val;



                                    //signed long long* len =  static_cast<signed long long *>(value_length_or_null);
                                    //signed long long ln = *len;

                                if( i==9 )
                                {
                                // http://www.easysoft.com/developer/languages/c/odbc-tutorial-fetching-results.html
                                SQLPOINTER val;
                                //long int* val;
                                //unsigned char* val;
                                // http://www.cplusplus.com/forum/general/36365/
                                sqlr_get_data = SQLGetData(
                                         sqlstatementhandle,                 // SQLHSTMT StatementHandle [aka SQLHANDLE]
                                         i,                                  // SQLUSMALLINT ColumnNumber
                                         column_type,                        // SQL_WLONGVARCHAR,  // SQLSMALLINT TargetType
                                         &val,                               // SQLPOINTER TargetValue
                                         static_cast<SQLLEN>(column_length), // SQLLEN BufferLength
                                         value_length_or_null);              // SQLLEN* StrLen_or_Ind

                                    //long* id_p = static_cast<long*>(val);

                                    //long id = *id_p;  // std::to_string(id)
                                    //msg_post.append(" VAL = ").append("").append(" | Len()= ").append(std::to_string(ln)).append(" ");
                                    // msg_post.append(" VAL = ").append( st_val ).append(" | Len() = ").append( std::to_string( vl_len )  ).append(" ");
                                }
                                //
                                //
                                //
                                if( i==2 || i==3 )
                                {


                                    // SQL_DESC_LENGTH;


                                    //SQLPOINTER val;
                                    wchar_t wst_val [8];
                                    //long int* val;
                                    //unsigned char* val;
                                    // http://www.cplusplus.com/forum/general/36365/
                                    sqlr_get_data = SQLGetData(
                                         sqlstatementhandle,                 // [INPUT]  SQLHSTMT StatementHandle [aka SQLHANDLE]
                                         i,                                  // [INPUT]  SQLUSMALLINT ColumnNumber
                                         SQL_C_WCHAR,                        // [INPUT]  SQL_WLONGVARCHAR,  // SQLSMALLINT TargetType
                                         wst_val,                            // [OUTPUT] SQLPOINTER TargetValue
                                         8, //static_cast<SQLLEN>(column_length) // [INPUT]  SQLLEN BufferLength
                                         NULL);              // [OUTPUT] SQLLEN* StrLen_or_Ind

                                    //char* st_val = static_cast<char*>(val);
                                    //wchar_t* wst_val = static_cast<wchar_t*>(val);
                                    std::string st_val(to_narrow(wst_val));

                                    signed long long int vl_len = *value_length_or_null;

                                    //char* st_val = (char*)val;
                                    msg_post.append(" VAL = ").append( st_val ).append(" | Len() = ").append( std::to_string( vl_len / 2 )  ).append(" ");
                                }

                                    //const wchar_t* id = static_cast<const wchar_t*>(val);
                                   // std::string val_str;
                                    //val_str.append(to_narrow(id));  // sizeof(id)

                            }

                           // https://msdn.microsoft.com/en-us/library/ms714556(v=vs.85).aspx

                            switch(column_type)
                            {
                                case SQL_WVARCHAR:
                                    //  wchar_t*
                                    msg_post.append("SQL_WVARCHAR");
                                    break;
                                case SQL_WLONGVARCHAR:
                                    //  wchar_t*
                                    msg_post.append("SQL_WLONGVARCHAR / nvarchar(max)");
                                    break;
                                case SQL_C_CHAR:
                                 //   unsigned char*
                                    msg_post.append("SQL_C_CHAR");
                                    break;
                                case SQL_C_WCHAR:
                                  //  wchar_t*
                                    msg_post.append("SQL_C_WCHAR");
                                    break;
                                case SQL_C_SHORT:
                                    msg_post.append("SQL_C_SHORT");
                                  //  short int
                                    break;
                                case SQL_C_SSHORT:
                                    msg_post.append("SQL_C_SSHORT");
                                  //  short int
                                    break;
                                case SQL_C_USHORT:
                                    msg_post.append("SQL_C_USHORT");
                                   // unsigned short int
                                    break;
                                case SQL_C_LONG: // same as SQL_INTEGER
                                    msg_post.append("SQL_C_LONG / SQL_INTEGER");
                                  //  int
                                    break;
                                case SQL_C_SLONG:
                                    msg_post.append("SQL_C_SLONG");
                                  //  long int
                                    break;
                                case SQL_C_ULONG:
                                    msg_post.append("SQL_C_ULONG");
                                  //  unsigned long int
                                    break;
                                case SQL_C_FLOAT:
                                    msg_post.append("SQL_C_FLOAT");
                                   // float
                                    break;
                                case SQL_C_DOUBLE:
                                    msg_post.append("SQL_C_DOUBLE");
                                  //  double
                                    break;
                                case SQL_C_BIT:
                                    msg_post.append("SQL_C_BIT");
                                  //  unsigned char
                                    break;
                                case SQL_C_TINYINT: // SQL_TINYINT;
                                    msg_post.append("SQL_C_TINYINT");
                                  //  signed char???
                                    break;
                                case SQL_C_STINYINT:
                                    msg_post.append("SQL_C_STINYINT");
                                  //  signed char
                                    break;
                                case SQL_C_UTINYINT:
                                    msg_post.append("SQL_C_UTINYINT");
                                  //  unsigned char
                                    break;
                                case SQL_C_SBIGINT:
                                    msg_post.append("SQL_C_SBIGINT");
                                  //  int64_t
                                    break;
                                case SQL_C_UBIGINT: // same as SQL_C_BOOKMARK
                                    msg_post.append("SQL_C_UBIGINT");
                                  //  unsigned int64_t
                                    break;
                                case SQL_C_BINARY:  // same as SQL_C_VARBOOKMARK
                                    msg_post.append("SQL_C_BINARY");
                                  //  unsigned char*
                                    break;
                                case SQL_C_TYPE_DATE:
                                    msg_post.append("SQL_C_TYPE_DATE");
                                  //  SQL_DATE_STRUCT
                                    break;
                                case SQL_C_TYPE_TIME:
                                    msg_post.append("SQL_C_TYPE_TIME");
                                  //  SQL_TIME_STRUCT
                                    break;
                                case SQL_C_TYPE_TIMESTAMP:
                                    msg_post.append("SQL_C_TYPE_TIMESTAMP");
                                  //  SQL_TIMESTAMP_STRUCT
                                    break;
                                case SQL_C_NUMERIC:
                                    msg_post.append("SQL_C_NUMERIC");
                                    SQL_NUMERIC;
                                  //  SQL_NUMERIC_STRUCT
                                    break;
                                case SQL_C_GUID:
                                    msg_post.append("SQL_C_GUID");
                                  //  SQLGUID
                                    break;
                                default:
                                    msg_post.append("switch didnt stop for this type:");
                          /*      case MONTH:
                                case YEAR:
                                case YEAR_TO_MONTH:
                                case DAY:
                                case HOUR:
                                case MINUTE:
                                case SECOND:
                                case DAY_TO_HOUR:
                                case DAY_TO_MINUTE:
                                case DAY_TO_SECOND:
                                case HOUR_TO_MINUTE:
                                case HOUR_TO_SECOND:
                                case MINUTE_TO_SECOND:
                                   // SQL_INTERVAL_STRUCT
                                    break;
                            */
                            }

                            Logger::log( msg_init + msg_post + "]", Logger::kLogLevelDebug );

                        }

                        // SQLNumResultCols

                        // SQLGetData(sqlstatementhandle, 1, SQL_C_ULONG, &id, 0, NULL);
                        // SQLGetData(sqlstatementhandle, 2, SQL_C_CHAR, name, 64, NULL);
                        // SQLGetData(sqlstatementhandle, 3, SQL_C_CHAR, address, 64, NULL);
                        // SQLGetData(sqlstatementhandle, 4, SQL_C_CHAR, address, 64, NULL);
                        // Logger::log( std::to_string(id) + " " + name +" " + address , Logger::kLogLevelDebug);
                    }
                }
            }
            while(FALSE);

            SQLFreeHandle(SQL_HANDLE_STMT, sqlstatementhandle );
            SQLDisconnect(sqlconnectionhandle);
            SQLFreeHandle(SQL_HANDLE_DBC, sqlconnectionhandle);
            SQLFreeHandle(SQL_HANDLE_ENV, sqlenvhandle);

        }catch(std::exception& e){
            Logger::log( e.what(), Logger::kLogLevelError );
            show_message(e.what());
        }catch(...){
            Logger::log( "Error getting: DALUtilMSSQL.exec_update() !!!", Logger::kLogLevelError );
            show_message("Error getting: DALUtilMSSQL.exec_update() !!!");
        }

        return 0;
    }


}
