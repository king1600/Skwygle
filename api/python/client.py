import asyncio
import websockets
try: import ujson as Json
except: import json as Json

from auth import AuthHandler

class Protocol:
  def __init__(self, url, loop):
    self.url  = url
    self.loop = loop
    self.conn = None
    self.connected = False
    
  async def connect(self):
    if self.connected: return
    self.conn = await websockets.connect(self.url)
    self.connected = True
    
  async def recv(self, json=False):
    if self.conn is not None:
      data = await self.conn.recv()
      if json: data = Json.loads(data)
      return data
    
  async def send(self, data):
    if self.conn is not None:
      if isinstance(data, dict):
        data = Json.dumps(data)
      if not isinstance(data, str):
        data = str(data)
      if not isinstance(data, bytes):
        data = data.encode('utf-8')
      await self.conn.send(data)
      
  async def close(self):
    if self.connected:
      await self.conn.close()
      self.conn = None

class Client:
  def __init__(self, url=None, loop=None, host=None, port=None):
    self.loop = loop if loop is not None else asyncio.get_event_loop()
    if url == None:
      self.url = "ws://" + str(host)
      if port is not None: self.url += ":" + str(port)
    else:
      self.url = url
      if not self.url.startswith('ws://'):
        self.url = 'ws://' + self.url
    self.conn = Protocol(self.url, self.loop)
    self.auth = AuthHandler(self)
  
  async def close(self):
    await self.conn.close()

  async def __aenter__(self):
    await self.conn.connect()
    return self
  
  async def __aexit__(self, *exc):
    await self.conn.close()
    
  async def login(self, username, password):
    await self.auth.login(username, password)