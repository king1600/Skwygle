#ifndef UTILS_H
#define UTILS_H

#include <map>
#include <string>
#include <memory>
#include <vector>
#include <utility>
#include <fstream>
#include <iostream>
#include <streambuf>
#include <uWS/uWS.h>
#include <rapidjson/document.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

using namespace uWS;

/* Name simplifications */

// by typedefs
typedef Hub UHub;
typedef sql::SQLString SQLString;
typedef std::shared_ptr<sql::ResultSet> SQLResult;
typedef std::shared_ptr<sql::PreparedStatement> SQLPrepare;

// by defines
#define UServer SERVER
#define UOpCode OpCode
#define UWebSock WebSocket
#define JSON rapidjson::Document
#define UHttpReq HttpRequest
#define MAX_THREADS 16

// API Specific constants
const char* REQUIRED[] = {"code", "data"};
std::map<int, const char*> CODES;

// Initalize anything needed
void InitUtils()
{
  CODES.insert(std::make_pair(100, "auth"));
  CODES.insert(std::make_pair(200, "message"));
  CODES.insert(std::make_pair(300, "community"));
  CODES.insert(std::make_pair(400, "module"));
}

// Compact packet for each message
typedef struct
{
  UWebSock<UServer> conn;
  std::string content;
  UOpCode opcode;

  // send data with specified opcode
  void send(std::string data, UOpCode code) {
    conn.send(data.c_str(), data.size(), code);
  }
  void send(char *data, UOpCode code) {
    conn.send(data, strlen(data), code);
  }
  void send(const char *data, UOpCode code) {
    conn.send(data, strlen(data), code);
  }

  // reply using the same opcode
  void reply(std::string data) {
    conn.send(data.c_str(), data.size(), opcode);
  }
  void reply(char *data) {
    conn.send(data, strlen(data), opcode);
  }
  void reply(const char *data) {
    conn.send(data, strlen(data), opcode);
  }

} WSPacket;

// Easy, non-bufferoverflow, readfile
std::string readFile(const char *fname)
{
  std::ifstream file(fname);
  std::string data;
  file.seekg(0, std::ios::end);
  data.reserve(file.tellg());
  file.seekg(0, std::ios::beg);
  data.assign(
    (std::istreambuf_iterator<char>(file)),
     std::istreambuf_iterator<char>()
  );
  return data;
}

// Multi-Param logging
template <typename T>
void Log__(T obj) { std::cout << obj << ' '; }

void __Log() { std::cout << std::endl; }

template <typename T, typename ...Args>
void __Log(T && t, Args &&... args)
{
  Log__(t); __Log(std::forward<Args>(args)...);
}

template <typename ...Args>
void Log(Args &&... args) { __Log(std::forward<Args>(args)...); }


#endif // !UTILS_H