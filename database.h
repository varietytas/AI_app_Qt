#include "abstractdb.h"
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

class Database : public AbstractDB
{
public:
    Database(const std::string& path = "userdata.db") : AbstractDB(path) {}
    ~Database() {}

    void createTables() override
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
                 std::string chanelid = " ", std::string token = "")
    {
        char *messaggeError;

        std::string deleteQuery = "DELETE FROM text";
        exit = sqlite3_exec(DB, deleteQuery.c_str(), NULL, NULL, &messaggeError);

        std::string query = "INSERT INTO text (firstname, email, chanelid, token) VALUES ('" + firstname + "', '" + email + "', '" + chanelid + "', '" + token + "')";

        exit = sqlite3_exec(DB, query.c_str(), NULL, NULL, &messaggeError);
    }

    UserInfo getAllTexts()
    {
        char* messaggeError;

        std::string query = "SELECT * FROM text LIMIT 1;";
        std::vector<UserInfo> data;
        exit = sqlite3_exec(DB, query.c_str(), textCallback, &data, &messaggeError);

        if (!data.empty())
        {
            return data[0]; // Возвращаем первую запись из результата запроса
        }
        else
        {
            // Возвращаем пустой объект UserInfo, если нет результатов
            return UserInfo();
        }
    }

    bool getUserByEmailAndPassword(const std::string& email, const std::string& password)
    {
        char* messaggeError;
        std::vector<UserInfo> data;
        std::string query = "SELECT * FROM text WHERE email = '" + email + "' AND token = '" + password + "'";
        exit = sqlite3_exec(DB, query.c_str(), textCallback, &data, &messaggeError);
        return !data.empty();
    }

private:
    static int textCallback(void *data, int numOfColumns, char **row, char **columnsNames)
    {
        std::vector<UserInfo> *_data = static_cast<std::vector<UserInfo> *>(data);
        _data->push_back({std::stoi(row[0]), row[1], row[2], row[3], row[4]});

        return 0;
    }
};
