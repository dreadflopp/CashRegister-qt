#ifndef CASHREGISTER_DATABASE_H
#define CASHREGISTER_DATABASE_H
#include <sqlite3.h>
#include <QDebug>
#include "Receipt.h"

class Database {
public:
    static Database &getInstance() {
        static Database instance;
        return instance;
    }

    static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
        int i;
        for(i = 0; i<argc; i++) {
            printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
        }
        printf("\n");
        return 0;
    }

    bool init() {

        char *errorMsg;
        int rc;

        rc = sqlite3_open("test.db", &database);

        std::cout << "open db: " << rc;

        if( rc ) {
            fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(database));
            return false;
        } else {
            fprintf(stderr, "Opened database successfully\n");
        }
        // Create receipt table
        char const *sql = "CREATE TABLE receipt("
                          "id INT PRIMARY KEY NOT NULL,"
                          "time INT NOT NULL);"

                          "CREATE TABLE seller("
                          "id INT PRIMARY KEY NOT NULL,"
                          "surname TEXT,"
                          "lastname TEXT);"

                          "CREATE TABLE item("
                          "id INT PRIMARY KEY NOT NULL,"
                          "price REAL NOT NULL,"
                          "discount REAL NOT NULL);"
                          "FOREIGN KEY(receipt_id) REFERENCES receipt(id),"
                          "FOREIGN key(seller_id) REFERENCES seller(id));";

        rc = sqlite3_exec(database, sql, callback, nullptr, &errorMsg);
        if( rc != SQLITE_OK ){
            fprintf(stderr, "SQL error: %s\n", errorMsg);
            sqlite3_free(errorMsg);
        } else {
            fprintf(stdout, "Table created successfully\n");
            return false;
        }

        return true;
    }
//    void open() { sqlite3_open("cashregister.db", &database); }
//    void close() { sqlite3_close(database); }
    void addReceipt(const Receipt &receipt) {

    }

private:
    static Database *instance;
    sqlite3* database;
};

#endif //CASHREGISTER_DATABASE_H
