#ifndef DATABASE_H
#define DATABASE_H

#include <memory>
#include <stdlib.h>
#include <exception>
#include "../utils.h"
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>

/* Database class handles SQL interaction */
class Database
{
public:
  Database(JSON &conf);
  ~Database();

  // used to check if the database successfully loaded or not
  bool isLoaded = false;
  
  // execute an SQL query with const
  void execute(const char *query) {
    shared_stmt->execute(query);
  }

  // execute an SQL query with const
  void execute(char *query) {
    shared_stmt->execute(query);
  }

  // execute an SQL query with const and fetch result
  SQLResult executeQuery(const char *query) {
    SQLResult ret(shared_stmt->executeQuery(query));
    return ret;
  }

  // execute an SQL query and fetch result
  SQLResult executeQuery(char *query) {
    SQLResult ret(shared_stmt->executeQuery(query));
    return ret;
  }

  // prepare an sql statement with const
  SQLPrepare prepare(const char *query) {
    SQLPrepare ret(conn->prepareStatement(query));
    return ret;
  }

  // prepare an sql statement
  SQLPrepare prepare(char *query) {
    SQLPrepare ret(conn->prepareStatement(query));
    return ret;
  }

private:
  // SQL connection info
  char *username;
  char *password;
  char *database;
  char *sql_db_url;

  // SQL Objects
  sql::Driver *driver = nullptr;
  sql::Connection *conn = nullptr;
  sql::Statement *shared_stmt = nullptr;
};

// Initialize a connection to database on constructor
Database::Database(JSON &conf)
{
  try {
    // get login info from config file
    sql_db_url = (char *)conf["db_url"].GetString();
    username   = (char *)conf["db_user"].GetString();
    password   = (char *)conf["db_pass"].GetString();
    database   = (char *)conf["db_name"].GetString();

    // get driver and connect to MySQL database
    driver = get_driver_instance();
    conn   = driver->connect(
      (const char*)sql_db_url,
      (const char*)username,
      (const char*)password
    );

    // set the database to use and finish loading
    conn->setSchema((const char*)database);
    shared_stmt = conn->createStatement();
    isLoaded = true;

  // catch any errors or exceptions
  } catch (sql::SQLException &ex) {
    Log("[x] SQL Error:", ex.getErrorCode(), ex.what());
  } catch (std::exception &ex) {
    Log("[x] Database Error:", ex.what());
  } catch (...) {
    Log("[x] Database Unknown Error!");
  }
}

// On destructor, delete the pointers
Database::~Database()
{
  delete shared_stmt;
  delete conn;
}

#endif // !DATABASE_H