#include "SettingsDAO.h"


void SettingsDAO::initializeDB(){
    std::string sql;
    int lint_rows(0);

    sql.append("select * from prp_property ; ");
    lint_rows = DALUtilSQLite::exec_update(sql,"settings.sqlite");

    sql.clear();
    sql.append("create table if not exists prp_property  ");
    sql.append( "( prp_id INTEGER, " );
    sql.append( "  prp_name TEXT UNIQUE, ");
    sql.append( "  prp_value TEXT, ");
    sql.append( "  prp_editable TEXT ); ");
    lint_rows = DALUtilSQLite::exec_update(sql,"settings.sqlite");
    //Logger::log( sql, Logger::kLogLevelDebug );
    //Logger::log( "Rows updated: " + std::to_string(lint_rows) , Logger::kLogLevelDebug );

    property_t prop;
    prop.name = "last_openned";
    prop.value = Logger::get_now_string();
    prop.editable = false;
    set_property(prop);
    sql.clear();
    sql.append( " INSERT INTO prp_property (prp_name, prp_value, prp_editable)" );
    sql.append( " select 'dada.db.server.host', 'localhost', 'Y' " );
    sql.append( " where not exists ( select 1 from prp_property where prp_name = 'dada.db.server.host' ) ;" );
    lint_rows = DALUtilSQLite::exec_update(sql,"settings.sqlite");
    // Logger::log( sql, Logger::kLogLevelDebug );
    // Logger::log( "Rows updated: " + std::to_string(lint_rows) , Logger::kLogLevelDebug );

    sql.clear();
    sql.append( " INSERT INTO prp_property (prp_name, prp_value, prp_editable)" );
    sql.append( " select 'dada.db.server.port', '1433', 'Y'  " );
    sql.append( " where not exists ( select 1 from prp_property where prp_name = 'dada.db.server.port' ) ; " );
    lint_rows = DALUtilSQLite::exec_update(sql,"settings.sqlite");
    // Logger::log( sql, Logger::kLogLevelDebug );
    // Logger::log( "Rows updated: " + std::to_string(lint_rows) , Logger::kLogLevelDebug );

    sql.clear();
    sql.append( " INSERT INTO prp_property (prp_name, prp_value, prp_editable)" );
    sql.append( " select 'dada.db.database.name', 'dadatitheslive', 'Y'  " );
    sql.append( " where not exists ( select 1 from prp_property where prp_name = 'dada.db.database.name' ) ; " );
    lint_rows = DALUtilSQLite::exec_update(sql,"settings.sqlite");
    // Logger::log( sql, Logger::kLogLevelDebug );
    // Logger::log( "Rows updated: " + std::to_string(lint_rows) , Logger::kLogLevelDebug );

    sql.clear();
    sql.append( " INSERT INTO prp_property (prp_name, prp_value, prp_editable)" );
    sql.append( " select 'dada.db.database.user', 'sa', 'Y'  " );
    sql.append( " where not exists ( select 1 from prp_property where prp_name = 'dada.db.database.user' ) ; " );
    lint_rows = DALUtilSQLite::exec_update(sql,"settings.sqlite");
    //Logger::log( sql, Logger::kLogLevelDebug );
    //Logger::log( "Rows updated: " + std::to_string(lint_rows) , Logger::kLogLevelDebug );

    sql.clear();
    sql.append( " INSERT INTO prp_property (prp_name, prp_value, prp_editable)" );
    sql.append( " select 'dada.db.database.password', 'cecils', 'Y'  " );
    sql.append( " where not exists ( select 1 from prp_property where prp_name = 'dada.db.database.password' ) ; " );
    lint_rows = DALUtilSQLite::exec_update(sql,"settings.sqlite");
    //Logger::log( sql, Logger::kLogLevelDebug );
    //Logger::log( "Rows updated: " + std::to_string(lint_rows) , Logger::kLogLevelDebug );

    //  DRIVER={SQL Server};SERVER=localhost, 1433;DATABASE=cars;UID=sa;PWD=cecils;

    //Logger::log( "OUTPUT String ------- : " +  DALUtilSQLite::result_set_sqlite_to_string(DALUtilSQLite::exec_read_to_rs( "select * from prp_property;","settings.sqlite") ) , Logger::kLogLevelDebug );
    //Logger::log( "OUTPUT XML  ------- : " +  DALUtilSQLite::exec_read_to_xml( "select * from prp_property;","settings.sqlite") , Logger::kLogLevelDebug );

    //Logger::log("last_openned : "+SettingsDAO::get_property("last_openned"), Logger::kLogLevelDebug );
    //Logger::log("done!" , Logger::kLogLevelDebug) ;
}


std::string SettingsDAO::get_property(std::string const& prp_name){
    std::string lstr_value;
    result_set_sqlite_t rs;
    std::string sql;
    sql.append("select prp_value from prp_property where prp_name = '").append(prp_name).append("' ; ");
    rs = DALUtilSQLite::exec_read_to_rs(sql,"settings.sqlite");
    lstr_value = rs.get_row(0)->get_cell_by_name("prp_value")->cell_string;
    return lstr_value;
}

void SettingsDAO::set_property(std::string const& prp_name, std::string const& prp_value, const bool& editable ){

    std::string sql;
    sql.append("INSERT OR REPLACE INTO prp_property (prp_name, prp_value, prp_editable)" );
    sql.append( " VALUES ( '").append(prp_name).append("', " );
    sql.append( "  '").append(prp_value).append("',  ");
    sql.append( "  '").append( (editable)?"Y":"N" ).append("' ) ;  ");

    int lint_rows = DALUtilSQLite::exec_update(sql,"settings.sqlite");
    if(lint_rows<1)
    {
        Logger::log( sql, Logger::kLogLevelDebug );
        Logger::log( "Rows updated: " + std::to_string(lint_rows) , Logger::kLogLevelDebug );
    }
}


void SettingsDAO::set_property(property_t const& p_proprty){
    set_property(p_proprty.name , p_proprty.value, p_proprty.editable );
}


settings_map* SettingsDAO::get_all_properties() {
    settings_map* return_settings = new settings_map();
    property_t l_prop;
    l_prop.name = "last_read";
    l_prop.value = Logger::get_now_string();
    l_prop.editable = false;
    return_settings->insert({l_prop.name,l_prop});

    result_set_sqlite_t rs;
    std::string sql;
    sql.append("select prp_name,prp_value,prp_editable from prp_property order by prp_name, prp_value; ");
    rs = DALUtilSQLite::exec_read_to_rs(sql,"settings.sqlite");


    for ( s_row_sqlite_t l_row : rs ) {
        property_t prop;

        prop.name = l_row.get_cell_by_name("prp_name")->cell_string;
        prop.value = l_row.get_cell_by_name("prp_value")->cell_string;
        prop.editable = l_row.get_cell_by_name("prp_editable")->cell_string=="Y";
        return_settings->insert({prop.name,prop});
    }

    return return_settings;
}


