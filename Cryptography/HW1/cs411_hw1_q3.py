# if this lib isn't installed yet --> pip install requests or pip3 intall requests
import requests
import math
import random
import fractions
from collections import Counter
# You can use the Turkish alphabet for Question 3
# Note that encyrption and decryption algorithms are slightly different for
# Turkish texts
turkish_alphabet = {'A': 0, 'B': 1, 'C': 2, 'Ç': 3, 'D': 4, 'E': 5, 'F': 6, 'G': 7, 'Ğ': 8, 'H': 9, 'I': 10,
                    'İ': 11, 'J': 12, 'K': 13, 'L': 14, 'M': 15, 'N': 16, 'O': 17, 'Ö': 18, 'P': 19,
                    'R': 20, 'S': 21,  'Ş': 22, 'T': 23, 'U': 24, 'Ü': 25, 'V': 26, 'Y': 27,
                    'Z': 28}

inv_turkish_alphabet = {0: 'A', 1: 'B', 2: 'C', 3: 'Ç', 4: 'D', 5: 'E', 6: 'F', 7: 'G', 8: 'Ğ', 9: 'H',
                        10: 'I', 11: 'İ', 12: 'J', 13: 'K', 14: 'L', 15: 'M', 16: 'N', 17: 'O', 18: 'Ö',
                        19: 'P', 20: 'R', 21: 'S',  22: 'Ş', 23: 'T', 24: 'U', 25: 'Ü', 26: 'V',
                        27: 'Y', 28: 'Z'}

letter_count = {'A': 0, 'B': 0, 'C': 0, 'D': 0, 'E': 0, 'F': 0, 'G': 0, 'H': 0, 'I': 0,
                'J': 0, 'K': 0, 'L': 0, 'M': 0, 'N': 0, 'O': 0, 'P': 0, 'Q': 0,
                'R': 0, 'S': 0,  'T': 0, 'U': 0, 'V': 0, 'W': 0, 'X': 0, 'Y': 0, 'Z': 0}


def phi(n):
    amount = 0
    for k in range(1, n + 1):
        if math.gcd(n, k) == 1:
            amount += 1
    return amount

# The extended Euclidean algorithm (EEA)


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

# Dont forget to open vpn
# ATTN: This is the current server (do not change unless being told so)


def Affine_Dec(ptext, key):

    plen = len(ptext)
    ctext = ''
    for i in range(0, plen):
        letter = ptext[i]
        if letter in turkish_alphabet:
            poz = turkish_alphabet[letter]
            poz = (key.gamma*poz+key.theta) % 29
            # print poz
            ctext += inv_turkish_alphabet[poz]
        else:
            ctext += ptext[i]
    return ctext


def most_frequent_char(str1):

    dict1 = {}

    max_repeat_count = 0

    for letter in str1:

        if letter not in dict1:

            dict1[letter] = 1

        elif (letter.isalnum()):

            dict1[letter] += 1

        if dict1[letter] > max_repeat_count:

            max_repeat_count = dict1[letter]

            most_repeated_char = letter

    return most_repeated_char


API_URL = 'http://10.36.52.109:5000'


class key(object):
    alpha = 0
    beta = 0
    gamma = 0
    theta = 0


if __name__ == '__main__':
    my_id = 23994

    cipher_text = None
    letter = None

    endpoint = '{}/{}/{}'.format(API_URL, "affine_game", my_id)
    # get your ciphertext and most freq. letter
    response = requests.get(endpoint)
    if response.ok:  # if you get your ciphertext succesfully
        c = response.json()
        cipher_text = c[0]  # this is your ciphertext
        letter = c[1]  # the most frequent letter in your plaintext
        print("Most Frequent Character : " + most_frequent_char(cipher_text))

        # y = alpha* x + beta
        # 1 (b) = alpha* 0 (A) + beta ---> beta should be 1 in every case

        # i should try all values 1 to 28, both included, the true answer will be 13 for alpha

        for i in range(28):
            key.alpha = i+1
            key.beta = 1
            key.gamma = modinv(key.alpha, 29)
            key.theta = 29-(key.gamma*key.beta) % 29

            ptext = Affine_Dec(cipher_text, key)
            print(i+1)
            
            # CHECK YOUR ANSWER HERE
            # Below is the sample code for sending your response back to the server
            query = ptext
            endpoint = '{}/{}/{}/{}'.format(API_URL,
                                            "affine_game", my_id, query)
            response = requests.put(endpoint)
            if response.ok:
                c = response.json()
                print(c)
                successfultext = query
            elif(response.status_code == 404):
                print("check paramater types")
            elif(response.status_code == 406):
                print("Nope, Try again")
            elif(response.status_code == 401):
                print("Check your ID number")
            else:
                print("How did you get in here? Contact your TA")

    elif(response.status_code == 404):
        print("We dont have a student with this ID. Check your id num")
    else:
        print("It was supposed to work:( Contact your TA")

print (successfultext)
