import math
import warnings


def gcd(a, b):
    """Calculate the Greatest Common Divisor of a and b.

    Unless b==0, the result will have the same sign as b (so that when
    b is divided by it, the result comes out positive).
    """
    while b:
        a, b = b, a%b
    return a

def egcd(a, b):
    x,y, u,v = 0,1, 1,0
    while a != 0:
        q, r = b//a, b%a
        m, n = x-u*q, y-v*q
        b,a, x,y, u,v = a,r, u,v, m,n
    gcd = b
    return gcd, x, y

def modinv(a, m):
    gcd, x, y = egcd(a, m)
    if gcd != 1:
        return None  # modular inverse does not exist
    else:
        return x % m
      
def q3(a, b, n):
    solutions = []
    d = gcd(a, n)
    if b % d != 0:
        print("Not divisible")
    else:
        if d == 1:
            solutions.append(pow(b, modinv(a, n), n))
        else:
            for i in range(d):
                solutions.append((modinv(a // d, n // d) * (b // d)) % (n // d) + i * (n // d))
    return solutions

n = 97289040915427312142046186233204893375
a = 61459853434867593821323745103091100940
b = 22119567361435062372463814709890918083

print ("1.question solutions are")
solutions = q3(a, b, n)

if (solutions != None):
    for x in range(len(solutions)): 
        print (solutions[x])

n = 97289040915427312142046186233204893375
a = 87467942514366097632147785951765210855
b = 3291682454206668645932879948693825640

solutions = q3(a, b, n)

if (solutions != None):
    print ("2. question solutions are:")
    for x in range(len(solutions)): 
        print (solutions[x])

n = 97289040915427312142046186233204893375
a = 74945727802091171826938590498744274413
b = 54949907590247169540755431623509626593

solutions = q3(a , b , n)

if (solutions != None):
    print ("3. question solutions are:")
    for x in range(len(solutions)): 
        print (solutions[x])