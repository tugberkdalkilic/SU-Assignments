import random
import requests
import math

API_URL = 'http://cryptlygos.pythonanywhere.com'  # DON'T Change this
my_id = 23994

# server communication. Try to get p and t
endpoint = '{}/{}/{}'.format(API_URL, "q1", my_id)
response = requests.get(endpoint)
p = 0
t = 0
if response.ok:
    res = response.json()
    print(res)
    # p is your prime number. t is the order of a subgroup. USE THESE TO SOLVE THE QUESTION
    p, t = res['p'], res['t']
    print(p, t)
else:
    print(response.json())

arr = []

for k in range(2, p):
    if math.gcd(p, k) == 1:
        arr.append(k)

finishouterloop = 0

while finishouterloop == 0:
    for i in arr:
        arrtemp = []
        finishinnerloop = 0
        while finishinnerloop == 0:
            for k in range(1, p):
                if (i ** k) % p != 1:
                    arrtemp.append(i ^ k)   
                else:
                    if len(arrtemp) == len(arr):
                        finishouterloop = 1
                        g = i
                    else:
                        finishinnerloop = 1

gH = 0
for k in range(1, p):
  elements = []
  for j in range(1, p):
    if (k ** j) % p in elements:
      break
    else:
      elements.append((k ** j) % p)
  
  if len(elements) == t:
    gH = k

# You can CHECK result of PART A here
endpoint = '{}/{}/{}/{}'.format(API_URL, "q1ac", my_id, g)
response = requests.put(endpoint)
print(response.json())
# You can CHECK result of PART B here
# gH is generator of your subgroup
endpoint = '{}/{}/{}/{}'.format(API_URL, "q1bc", my_id, gH)
response = requests.put(endpoint)  # check result
print(response.json())
