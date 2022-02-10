from numpy import random

def estimate_pi(n):
    r2 = (random.uniform(-1,1,(n,2))**2).sum(axis=1)
    hits = (r2 < 1).sum()
    return 4.0*hits/n

print (estimate_pi(10000))
