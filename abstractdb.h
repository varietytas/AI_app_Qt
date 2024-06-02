#ifndef ABSTRACTDB_H
#define ABSTRACTDB_H

#include <sqlite3.h>
#include <string>


class AbstractDB
{
public:
    AbstractDB(const std::string& path)
    {
        exit = sqlite3_open(path.c_str(), &DB);
    }
    ~AbstractDB() { sqlite3_close(DB); }

    virtual void createTables() = 0;

protected:
    sqlite3* DB;
    int exit;
};

#endif // ABSTRACTDB_H
