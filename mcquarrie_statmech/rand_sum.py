#!/usr/bin/env python3

from numpy import random
import matplotlib.pyplot as plt

def randsum(ntimes):
    return random.uniform(-1, 1, (ntimes, 10)).sum(axis=1)/10

plt.hist(randsum(1000), bins=10)
plt.show()

