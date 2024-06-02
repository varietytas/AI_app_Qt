#ifndef TESTDATABASE_HPP
#define TESTDATABASE_HPP

#include "../database.h"
#include <QObject>
#include <QTest>


class TestDatabase : public QObject
{
    Q_OBJECT
    
private slots:
    void initTestCase();    // Initializes the unit test
    void cleanupTestCase(); // Cleans up after all tests are done

    void testAddText();     // Tests Database::addText() and Database::getAllTexts()
    void testGetUserByEmailAndPassword(); // Tests Database::getUserByEmailAndPassword()

private:
    Database* db;
};

#endif // TESTDATABASE_HPP
