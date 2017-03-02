#ifndef HANDLE_H
#define HANDLE_H

#include "utils.h"
#include "errors.h"
#include "handlers/auth.h"

/* Complete message handler */
int handlePacket(WSPacket packet)
{
  // check if correct json
  if (packet.content.c_str()[0] != '{'
      || packet.content.back() != '}')
    return JsonError(packet);
  JSON req;
  req.Parse(packet.content.c_str());

  // Check if valid api request/response
  for (const char *r : REQUIRED)
    if (!req.HasMember(r))
      return InvalidError(packet);
  if (!req["code"].IsInt())
    return InvalidError(packet);

  // Handle API Calls
  switch (req["code"].GetInt())
  {

    // Authentication
    case 100:
    {
      handleAuth(packet, req);
      break;
    }

    // Messages
    case 200:
    {
      break;
    }

    // Community
    case 300:
    {
      break;
    }

    // Modules
    case 400:
    {
      break;
    }

    // Non-Implemented Call
    default:
    {
      return APINotImplementedError(packet);
    }
  }

  return 1;
}

#endif // !HANDLE_H