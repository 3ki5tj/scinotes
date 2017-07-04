import math, random
def estpi(n):
    hits = 0
    for i in range(n):
        x = random.random() * 2 - 1
        y = random.random() * 2 - 1
        if x*x + y*y < 1:
            hits += 1
    p = 4.0*hits/n
    print "pi %g, error %g" % (p, p - math.pi)
estpi(10000)
