# use "pip install pyprimes" if pyprimes is not installed
# use "pip install pycryptodome" if pycryptodome is not installed
import math
import random
import sympy
import requests
from Crypto.Hash import SHAKE128, SHAKE256

API_URL = 'http://cryptlygos.pythonanywhere.com'

my_id = 23994  

k0 = 8
k1 = 128

def egcd(a, b):
    x,y, u,v = 0,1, 1,0
    while a != 0:
        q, r = b//a, b%a
        m, n = x-u*q, y-v*q
        b,a, x,y, u,v = a,r, u,v, m,n
    gcd = b
    return gcd, x, y

def modinv(a, m):
    if a < 0:
        a = a+m
    gcd, x, y = egcd(a, m)
    if gcd != 1:
        return None  # modular inverse does not exist
    else:
        return x % m

def RSA_OAEP_Dec(c, d, N):
    k = N.bit_length()-2
    m_ = pow(c, d, N)
    m0k1GR = m_ >> k0
    RHm0k1GR =  m_ % 2**k0
    shake = SHAKE128.new(m0k1GR.to_bytes((m0k1GR.bit_length()+7)//8, byteorder='big'))
    Hm0k1GR =  shake.read(k0//8)
    R = int.from_bytes(Hm0k1GR, byteorder='big') ^ RHm0k1GR
    shake = SHAKE128.new(R.to_bytes(k0//8, byteorder='big'))
    GR =  shake.read((k-k0)//8)
    m0k1 = m0k1GR ^ int.from_bytes(GR, byteorder='big')
    m = m0k1 >> k1
    return m

endpoint = '{}/{}/{}'.format(API_URL, "RSA_OAEP", my_id )   
response = requests.get(endpoint) 	
c, N, e = 0,0,0 
if response.ok:	
  res = response.json()
  print(res)
  c, N, e = res['c'], res['N'], res['e']    ##get c, N, e
else: print(response.json())

########

## n = p*q --> I calculated them manually

p =227972470347154993164296932340535173077
q= 306474784356775396317825875674753603733

phi_n = (p-1)*(q-1)
d = modinv(e,phi_n)

PIN_= RSA_OAEP_Dec (c,d,N)

print(PIN_)

########

# Client sends PIN_ to server
endpoint = '{}/{}/{}/{}'.format(API_URL, "RSA_OAEP", my_id, PIN_)
response = requests.put(endpoint)
print(response.json())