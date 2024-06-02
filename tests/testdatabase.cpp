#include "testdatabase.hpp"

void TestDatabase::initTestCase()
{
    db = new Database(":memory:"); // Use an in-memory database for testing
    db->createTables();
}
void TestDatabase::cleanupTestCase() { delete db; }

void TestDatabase::testAddText()
{
    db->addText("John", "john@example.com", "chanel1", "token123");
    UserInfo user = db->getAllTexts();

    QCOMPARE(user.firstname, std::string("John"));
    QCOMPARE(user.email, std::string("john@example.com"));
    QCOMPARE(user.chanelid, std::string("chanel1"));
    QCOMPARE(user.token, std::string("token123"));
}

void TestDatabase::testGetUserByEmailAndPassword()
{
    db->addText("Jane", "jane@example.com", "chanel2", "token456");
    bool userExists = db->getUserByEmailAndPassword("jane@example.com", "token456");
    QVERIFY(userExists);
    
    bool userNotExists = db->getUserByEmailAndPassword("jane@example.com", "wrongtoken");
    QVERIFY(!userNotExists);
}
