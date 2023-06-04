import random
import requests
from functools import reduce

API_URL = 'http://cryptlygos.pythonanywhere.com'

my_id = 23994

endpoint = '{}/{}/{}'.format(API_URL, "RSA_Oracle", my_id )
response = requests.get(endpoint) 	
c, N, e = 0,0,0 
if response.ok:	
  res = response.json()
  print(res)
  c, N, e = res['c'], res['N'], res['e']    #get c, N, e
else: print(response.json())

######

c_ = (pow(2,e,N)*c) % N 

###### Query Oracle it will return corresponding plaintext
endpoint = '{}/{}/{}/{}'.format(API_URL, "RSA_Oracle_query", my_id, c_)
response = requests.get(endpoint) 	
if(response.ok): m_ = (response.json()['m_'])
else:print(response)

####
m_ = m_ // 2
res = m_.to_bytes((m_.bit_length() + 7) // 8, byteorder="big")

print(res)

###Send your answer to the server.
endpoint = '{}/{}/{}/{}'.format(API_URL, "RSA_Oracle_checker", my_id, res)
response = requests.put(endpoint)
print(response.json())