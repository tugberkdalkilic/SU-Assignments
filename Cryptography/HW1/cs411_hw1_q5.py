# if this lib isn't installed yet --> pip install requests or pip3 intall requests
import requests
import math
import random
import fractions
from collections import Counter

uppercase = {'A': 0, 'B': 1, 'C': 2, 'D': 3, 'E': 4, 'F': 5, 'G': 6, 'H': 7, 'I': 8,
             'J': 9, 'K': 10, 'L': 11, 'M': 12, 'N': 13, 'O': 14, 'P': 15, 'Q': 16,
             'R': 17, 'S': 18,  'T': 19, 'U': 20, 'V': 21, 'W': 22, 'X': 23, 'Y': 24,
             'Z': 25,  ' ': 26, '.': 27, ',': 28, '!': 29, '?': 30}

inv_uppercase = {0: 'A', 1: 'B', 2: 'C', 3: 'D', 4: 'E', 5: 'F', 6: 'G', 7: 'H',
                 8: 'I', 9: 'J', 10: 'K', 11: 'L', 12: 'M', 13: 'N', 14: 'O', 15: 'P',
                 16: 'Q', 17: 'R', 18: 'S', 19: 'T', 20: 'U', 21: 'V', 22: 'W', 23: 'X',
                 24: 'Y', 25: 'Z', 26: '', 27: '.', 28: ',', 29: '!', 30: '?'}


def phi(n):
    amount = 0
    for k in range(1, n + 1):
        if math.gcd(n, k) == 1:
            amount += 1
    return amount


def relativelyprime(n, relativelyprimes):
    for k in range(1, n+1):
        if math.gcd(n, k) == 1:
            relativelyprimes.append(k)


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


def multipl(k, ptext):

    for i in range(k, k+1):
        letter1 = ptext[i]
        letter2 = ptext[i+1]
        letter3 = ptext[i+2]

    mult = uppercase[letter1] * uppercase[letter2] * uppercase[letter3]
    return mult


def Affine_Dec(ptext, key):

    plen = len(ptext)
    ctext = ''
    for i in range(0, plen-2, 3):
        poz = multipl(i, ptext)
        poz = (key.gamma*poz+key.theta) % 31
        ctext += inv_uppercase[poz]
    return ctext


class key(object):
    alpha = 0
    beta = 0
    gamma = 0
    theta = 0


if __name__ == '__main__':

    cipher_text = "IDSEOYLTVVDO?PSAUEKZO?LQIILQMP?LQNP!YSFNGSDBJZRZYTZTPS?EVYF,?LQ ,SAXSWTFXFD"

    # it ends with ., ".xx" was converted to "xfd"
    # 27*23*23 = alpha* (23*5*3)+ beta

    relativelyprimes = []

    relativelyprime(29791, relativelyprimes)

    for i in range(0, len(relativelyprimes)):
        key.alpha = 129
        key.beta = (14283-key.alpha*345) % 29791
        key.gamma = modinv(key.alpha, 29791)
        key.theta = 29791-(key.gamma*key.beta) % 29791
        ptext = Affine_Dec(cipher_text, key)
        print(ptext, "\n" )
