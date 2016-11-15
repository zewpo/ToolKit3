#include "result_set_sqlite_t.h"

s_row_sqlite_t::s_row_sqlite_t()
{
    //ctor
}

s_row_sqlite_t::~s_row_sqlite_t()
{
    //dtor
}

// public std::vector<s_cell_sqlite_t>
s_cell_sqlite_t* s_row_sqlite_t::get_cell_by_name(const std::string cell_name){
    int i = 0;
    for ( s_cell_sqlite_t l_cell : *this ) {
        if(l_cell.cell_name == cell_name ) {
            return &(this->at(i));
        }
        i++;
    }
    return nullptr;
}

result_set_sqlite_t::result_set_sqlite_t()
{
    //ctor
}

result_set_sqlite_t::~result_set_sqlite_t()
{
    //dtor
}

s_row_sqlite_t* result_set_sqlite_t::get_row(const int& int_row){
    return &(this->at(int_row));
}
