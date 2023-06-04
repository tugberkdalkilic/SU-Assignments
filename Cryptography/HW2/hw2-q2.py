import requests
import math


API_URL = 'http://cryptlygos.pythonanywhere.com'

my_id = 23994

endpoint = '{}/{}/{}'.format(API_URL, "q2", my_id )
response = requests.get(endpoint) 	
if response.ok:	
  r = response.json()
  p, q, e, c = r['p'], r['q'], r['e'], r['cipher']    #Use these variables to calculate m
  print(c)
else:  print(response.json())

def egcd(a, b):
    x, y, u, v = 0, 1, 1, 0
    while a != 0:
        q, r = b//a, b % a
        m, n = x-u*q, y-v*q
        b, a, x, y, u, v = a, r, u, v, m, n
    gcd = b
    return gcd, x, y


def modinv(a, m):
    if a < 0:
        a = m+a
    gcd, x, y = egcd(a, m)
    if gcd != 1:
        return None  # modular inverse does not exist
    else:
        return x % m

##SOLUTION

n = p*q
phi_n = (p-1)*(q-1)
d = modinv(e,phi_n)
m = pow(c,d,n)

m_bytes = m.to_bytes((m.bit_length() + 7) // 8, byteorder='big')

m_= m_bytes.decode(encoding="utf-8")

print(m_)

## END OF SOLUTION

m_text = "Change this to the message you found from m by decoding. Yes, it is a meaningful text."


#query result
endpoint = '{}/{}/{}/{}'.format(API_URL, "q2c", my_id, m_ )    #send your answer as a string
response = requests.put(endpoint) 	
print(response.json())
