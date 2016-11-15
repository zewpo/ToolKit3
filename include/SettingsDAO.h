#ifndef SETTINGSDAO_H
#define SETTINGSDAO_H

#include <string>
#include <vector>
#include <map>
#include "sqlite3.h"

#include "DALUtilSQLite.h"

struct property_t {
    std::string name;
    std::string value;
    bool editable = true;
};

typedef std::map<std::string, property_t> settings_map;

class SettingsDAO
{
    public:
        // SettingsDAO();
        // virtual ~SettingsDAO();
        static void initializeDB();
        static std::string get_property(std::string const& prp_name);
        static void set_property(std::string const& prp_name, std::string const& prp_value, const bool& editable = true );
        static void set_property(property_t const& p_proprty );
        static settings_map* get_all_properties();

    protected:

    private:
        sqlite3* settings_db;

};

#endif // SETTINGSDAO_H
