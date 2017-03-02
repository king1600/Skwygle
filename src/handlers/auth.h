#ifndef AUTH_H
#define AUTH_H

#include <exception>
#include "../utils.h"
#include "../errors.h"

const char *err_badkey     = "Invalid key provided";
const char *err_badstep    = "Invalid auth step";
const char *err_uerror     = "Unknown auth exception";



// Get the encrypted user key
void getUserKey(WSPacket req, const JSON &json)
{

}

// compare client token to actual token
bool compareToken(WSPacket req, const JSON &json)
{

}

/* Handle Authorization packets */
int handleAuth(WSPacket req, const JSON &json)
{
  try {
    // handle invalid keys
    if (!json["data"].HasMember("key") || 
        !json["data"].HasMember("step"))
      return DefinedError(req, 1003, (char *)err_badkey, strlen(err_badkey));

    // decide for different auth steps
    switch (json["data"].GetInt("step"))
    {
      case 1:
        getUserKey(req, json);
        break;
      case 2:
        compareKeys(req, json);
        break;
      default:
        return DefinedError(req, 1003, (char*)err_badstep, strlen(err_badstep))''
    }

    // successful run
    return 1;

  // catch any errors
  } catch (std::exception &ex) {
    return ExceptionError(req, ex);
  } catch (...) {
    return DefinedError(req, 1101, err_uerror, strlen(err_uerror));
  }
}

#endif // !AUTH_H