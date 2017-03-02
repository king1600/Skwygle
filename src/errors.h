#ifndef ERRORS_H
#define ERRORS_H

#include <exception>

const char *err_nodata  = "No data was provided";
const char *err_invalid = "Invalid data provided";
const char *err_nonjson = "Data provided is not accepted JSON";
const char *err_nonapi  = "API call not found / not implemented";

const size_t err_nonapi_l  = strlen(err_nonapi);
const size_t err_nondata_l = strlen(err_nodata);
const size_t err_nonjson_l = strlen(err_nonjson);
const size_t err_invalid_l = strlen(err_invalid);

int APINotImplementedError(WSPacket packet) {
  packet.conn.close(1002, err_nonapi, err_nonapi_l);
  return 0;
}

int InvalidError(WSPacket packet) {
  packet.conn.close(1003, err_invalid, err_invalid_l);
  return 0;
}

int JsonError(WSPacket packet) {
  packet.conn.close(1003, err_nonjson, err_nonjson_l);
  return 0;
}

int DataNullError(WSPacket packet) {
  packet.conn.close(1003, err_nodata, err_nondata_l);
  return 0;
}

int ExceptionError(WSPacket packet, std::exception ex) {
  packet.conn.close(1011, ex.what(), strlen(ex.what()));
  return 0;
}

int DefinedError(WSPacket packet, int code, char *err, size_t len) {
  packet.conn.close(code, err, len);
  return 0;
}

#endif // !ERRORS_H