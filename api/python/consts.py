import websockets

REQ = {
  'code': None,
  'data': None
}

CODES = {
  100: 'auth',
  200: 'message',
  300: 'community',
  400: 'module',
  500: 'status'
}