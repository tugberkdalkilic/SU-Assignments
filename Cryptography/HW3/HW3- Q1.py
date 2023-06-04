# -*- coding: utf-8 -*-
"""hw3_q1.ipynb

Automatically generated by Colaboratory.

Original file is located at
    https://colab.research.google.com/drive/1Kn64Mu1U0Q4x8qnAeHVubvhqqSdy46jg
"""

!pip install BitVector

import random
import requests
import BitVector

API_URL = 'http://cryptlygos.pythonanywhere.com'  # DON'T CHANGE THIS
my_id = 23994

endpoint = '{}/{}/{}'.format(API_URL, "poly", my_id)
response = requests.get(endpoint)
a = 0
b = 0
if response.ok:
    res = response.json()
    print(res)
    a, b = res['a'], res['b']  # Binary polynomials a and b
else:
    print(response.json())

modulus = BitVector.BitVector(bitstring='100011011')     # AES modulus
n = 8
a = BitVector.BitVector(bitstring='11001111')
b = BitVector.BitVector(bitstring='11001010')
c = a.gf_multiply_modular(b, modulus, n)
print(c)

a_inv = a.gf_MI(modulus, n)
print (a_inv)

# check result of part a
endpoint = '{}/{}/{}/{}'.format(API_URL, "mult", my_id, c)
response = requests.put(endpoint)
print(response.json())

# check result of part b
endpoint = '{}/{}/{}/{}'.format(API_URL, "inv", my_id, a_inv)
response = requests.put(endpoint)
print(response.json())