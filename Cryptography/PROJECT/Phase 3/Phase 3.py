import math
import timeit
import random
import sympy
import warnings
from random import randint, seed
import sys
from ecpy.curves import Curve,Point
from Crypto.Hash import SHA3_256, SHA256, HMAC
import requests
from Crypto.Cipher import AES
from Crypto import Random
from Crypto.Util.Padding import pad
from Crypto.Util.Padding import unpad
import random
import hashlib, hmac, binascii
import json
import pickle
from os import path

def sign(k, m, decode = True):
    global P
    R = k * P
    r = R.x % n
    
    if decode:
        h = int.from_bytes(SHA3_256.new(m.to_bytes((m.bit_length() + 7) // 8, byteorder= "big") + r.to_bytes((r.bit_length() + 7) // 8, byteorder="big")).digest(), byteorder="big") % n
    else:
        h = int.from_bytes(SHA3_256.new(m + r.to_bytes((r.bit_length() + 7) // 8, byteorder="big")).digest(), byteorder="big") % n
    s = (sL * h + k) % n

    return h, s

def ver(s, h, m, qA):
	global P
	sP = int(s) * P
	hA = int(h) * qA
	V = sP - hA
	v = V.x % n
	hnew = int.from_bytes(SHA3_256.new(m.encode("utf-8") + v.to_bytes((v.bit_length() + 7) // 8, byteorder= "big")).digest(), byteorder= "big") % n
	return h == hnew

def genKey():
    global n
    global P

    sA = random.randint(0, n - 1)
    qA = sA * P

    return (sA, qA)

API_URL = 'http://cryptlygos.pythonanywhere.com'

stuID =  23994
stuID_B = 18007

#create a long term key
E = Curve.get_curve('secp256k1')
n = E.order
P = E.generator

#create a long term key
sL = 23927729476774547655045008832834504310921797729497501158914766546192068080855
ql = sL * P

lkey = ql

#

k = random.randint(1, n - 1)
h, s = sign(k, str(stuID).encode("utf-8"), False)

# KEY RESET BEGIN
mes = {'ID': stuID, 'S': s, 'H': h}
print(mes)
response = requests.get('{}/{}'.format(API_URL, "RstEKey"), json = mes)
print(response.json())
# KEY RESET END

msgSet = ['The world is full of lonely people afraid to make the first move.',
        'I don’t like sand. It’s all coarse, and rough, and irritating. And it gets everywhere.',
        'Hate is baggage. Life’s too short to be pissed off all the time. It’s just not worth it.',
        'Well, sir, it’s this rug I have, it really tied the room together.',
        'Love is like taking a dump, Butters. Sometimes it works itself out. But sometimes, you need to give it a nice hard slimy push.']
####Register Long Term Key

mes = {'ID':stuID, 'H': h, 'S': s, 'LKEY.X': lkey.x, 'LKEY.Y': lkey.y}
response = requests.put('{}/{}'.format(API_URL, "RegLongRqst"), json = mes)
print(response.json())

code = 0

mes = {'ID':stuID, 'CODE': code}
response = requests.put('{}/{}'.format(API_URL, "RegLong"), json = mes)
print(response.json())

#Check Status
mes = {'ID_A':stuID, 'H': h, 'S': s}
response = requests.get('{}/{}'.format(API_URL, "Status"), json = mes)
print("Status ", response.json())

eKeys = []
if not path.exists("eKeys.pkl"):
    eKeySave = []
    for i in range(10):
        eKeys.append(genKey())
        eKeySave.append(eKeys[-1][0])

        sE, qE = eKeys[-1]
        h, s = sign(randint(1, n - 2), (str(qE.x) + str(qE.y)).encode("utf-8"), False)

        #Send Ephemeral keys
        mes = {'ID': stuID, 'KEYID': i , 'QAI.X': qE.x, 'QAI.Y': qE.y, 'Si': s, 'Hi': h}
        response = requests.put('{}/{}'.format(API_URL, "SendKey"), json = mes)
        print(response.json())

    with open("eKeys.pkl", "wb") as handle:
        pickle.dump(eKeySave, handle, protocol= pickle.HIGHEST_PROTOCOL)
else:
    with open("eKeys.pkl", "rb") as handle:
        eKeysSave = pickle.load(handle)
        for e in eKeysSave:
            eKeys.append((e, e * P))

for i in range(len(eKeys)):
    h, s = sign(k, str(stuID_B).encode("utf-8"), False)

    ### Get key of the Student B
    mes = {'ID_A': stuID, 'ID_B':stuID_B, 'S': s, 'H': h}
    response = requests.get('{}/{}'.format(API_URL, "ReqKey"), json = mes)
    res = response.json()
    print(res)

    j = res["j"]
    QBJ = Point(res["QBJ.x"], res["QBJ.y"], E)
    QBI = eKeys[i][0]
    T = QBI * QBJ
    U = str(T.x) + str(T.y) + "NoNeedToRunAndHide"
    KENC = SHA3_256.new(U.encode("utf-8"))
    KMAC = SHA3_256.new(KENC.digest())

    msg = msgSet[i]
    aes = AES.new(KENC.digest(), AES.MODE_CTR)
    msg = aes.encrypt(msg.encode("utf-8"))

    mac = HMAC.new(KMAC.digest(), digestmod= SHA256)
    mac = mac.update(msg)
    msg = aes.nonce + msg + mac.digest()
    msg = int.from_bytes(msg, byteorder= "big")

    ### Send message to student B
    mes = {'ID_A': stuID, 'ID_B':stuID_B, 'I': i, 'J':j, 'MSG': msg}
    response = requests.put('{}/{}'.format(API_URL, "SendMsg"), json = mes)
    print(response.json())

    ## Get your message
    h, s = sign(k, str(stuID).encode("utf-8"), False)
    mes = {'ID_A': stuID, 'S': s, 'H': h}
    response = requests.get('{}/{}'.format(API_URL, "ReqMsg_PH3"), json = mes)
    print(response.json())
    if(response.ok): ## Decrypt message
        response = response.json()
        if response != "You dont have any new messages":
            k = random.randint(1, n - 2)
            ctext = response["MSG"].to_bytes((response["MSG"].bit_length() + 7) // 8, byteorder= "big")
            SEKey = Point(int(response["QBJ.X"]), int(response["QBJ.Y"]), E)
            T = eKeys[int(response["KEYID"])][0] * SEKey
            U = str(T.x) + str(T.y) + "NoNeedToRunAndHide"
            KENC = SHA3_256.new(U.encode("utf-8"))
            KMAC = SHA3_256.new(KENC.digest())
            
            msg = ctext[:-32]
            h = HMAC.new(KMAC.digest(), digestmod=SHA256)
            h.update(msg[8:])
            
            try:
                h.verify(ctext[-32:])
            except :
                print("Message could not verified")
                continue

            aes = AES.new(KENC.digest(), AES.MODE_CTR, nonce= msg[0:8])
            dec = aes.decrypt(msg[8:])
            decMsg = str(dec, encoding= "utf-8")

            print(decMsg)