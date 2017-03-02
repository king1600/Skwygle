import sys
import asyncio

from consts import *
from client import Client

async def main(loop):
  try:
    async with Client('ws://localhost:48500/') as client:
      await client.login('username', 'password')
  except Exception as err:
    print("[x] Error:", err.code, err.reason)

if __name__ == '__main__':
  loop = asyncio.get_event_loop()
  try:
    loop.run_until_complete(main(loop))
  except KeyboardInterrupt:
    pass
  sys.exit()