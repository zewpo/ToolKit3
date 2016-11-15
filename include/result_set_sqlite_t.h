#ifndef RESULT_SET_SQLITE_T_H
#define RESULT_SET_SQLITE_T_H

#include <string>
#include <vector>
#include "sqlite3.h"
#include "Logger.h"


enum s_sqlite_t {
    s_integer_sqlite_t = SQLITE_INTEGER,
    s_double_sqlite_t = SQLITE_FLOAT,
    s_string_sqlite_t = SQLITE_TEXT,
    s_blob_sqlite_t = SQLITE_BLOB,
    s_null_sqlite_t = SQLITE_NULL
};

struct s_cell_sqlite_t {
    s_sqlite_t cell_type;
    std::string cell_name;
    int cell_integer;
    double cell_double;
    std::string cell_string;
    std::vector<unsigned char> cell_blob;
    // cell_blob.reserve(fileSize);
};

class s_row_sqlite_t : public std::vector<s_cell_sqlite_t>
{
    public:
        s_row_sqlite_t();
        virtual ~s_row_sqlite_t();
        s_cell_sqlite_t* get_cell_by_name(const std::string cell_name);
    protected:
    private:
};

class result_set_sqlite_t : public std::vector<s_row_sqlite_t>
{
    public:
        result_set_sqlite_t();
        virtual ~result_set_sqlite_t();
        s_row_sqlite_t* get_row(const int& row);

        // s_cell_sqlite_t get_cell_in_row(int& row);

    protected:

    private:
};

#endif // RESULT_SET_SQLITE_T_H
