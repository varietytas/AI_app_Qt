#include <sqlite3.h>
#include <string>
#include <vector>
 

struct UserInfo
{
    int id;
    std::string firstname;
    std::string email;
    std::string chanelid;
    std::string token;
};


class Database
{
public:
    Database(const std::string& path = "userdata.db")
    {
        exit = sqlite3_open(path.c_str(), &DB);
    }
    ~Database() { sqlite3_close(DB); }

    void createTables()
    {
        char* messaggeError;
        std::string query_text = "CREATE TABLE IF NOT EXISTS text("
                                 "ID INTEGER PRIMARY KEY  AUTOINCREMENT,"
                                 "firstname TEXT,"
                                 "email TEXT,"
                                 "chanelid TEXT,"
                                 "token TEXT);";
        exit = sqlite3_exec(DB, query_text.c_str(), NULL, NULL, &messaggeError);
        // TODO: Error message output

        std::string query_resouce = "CREATE TABLE IF NOT EXISTS resource("
                                    "ID INTEGER PRIMARY KEY  AUTOINCREMENT,"
                                    "type TEXT  NOT NULL,"
                                    "description TEXT);";
        exit = sqlite3_exec(DB, query_resouce.c_str(), NULL, NULL, &messaggeError);
        // TODO: Error message output
    }

    void addText(std::string firstname, std::string email,
                 std::string  chanelid = " ", std::string token = "")
    {
        char* messaggeError;

        std::string query = "INSERT INTO text (firstname, email, chanelid, token) VALUES ('" + firstname + "', '" + email + "', '" + chanelid + "', '" + token + "')";

        exit = sqlite3_exec(DB, query.c_str(), NULL, NULL, &messaggeError);
    }

    std::vector<UserInfo> getAllTexts()
    {
        char* messaggeError;

        std::string query = "SELECT * FROM text;";
        std::vector<UserInfo> data;
        exit = sqlite3_exec(DB, query.c_str(), textCallback, &data, &messaggeError);
        
        return data;
    }

private:
    sqlite3* DB;
    int exit;

    static int textCallback(void* data, int numOfColumns, char** row, char** columnsNames)
    {
        std::vector<UserInfo>* _data = static_cast<std::vector<UserInfo>*>(data);
        _data->push_back({std::stoi(row[0]), row[1], row[2], row[3], row[4]});

        return 0;
    }
};
