from consts import *

class AuthHandler:
  def __init__(self, client=None, username=None, password=None):
    self.client = client
    self._user  = username
    self._pass  = password
    self.token  = ""
    
  def encrypt(self, key):
    bpos = 0
    pos = [int(str(ord(c))[0]) for c in self._pass]
    for p in pos:
      key[bpos], key[p] = key[p], key[bpos]
    return key
  
  async def login(self, _user, _pass):
    """ Authenticate the client """
    self._user = _user
    self._pass = _pass
    req = REQ.copy()
    req['code'] = 100
    
    # step 1
    req['data'] = {'step':1, 'key':self._user}
    await self.client.conn.send(req)
    
    # step 2
    data = await self.client.conn.recv(json=True)
    print(data)
    enc  = self.encrypt(data['data']['key'])
    req['data'] = {'step':2, 'key':enc}
    await self.client.conn.send(req)
    
    # step 3
    data = await self.client.conn.recv(json=True)
    print(data)
    self.key = data['data']['key']
  