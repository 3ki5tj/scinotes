import random
def randsum(ntimes):
    # initialize an empty histogram of 10 bins
    hist = [0]*10
    dx = 2.0/10 # set the bin width
    for t in range(ntimes):
        # add 10 random numbers between -1 and 1
        s = 0
        for i in range(10):
            s += random.random()*2 - 1
        s /= 10 # divide the sum by 10
        # find the bin index
        binid = int((s + 1) / dx)
        # update the histogram
        hist[binid] += 1
    # compute the distribution and plot it
    print "\nDistribution, %d trials:" % ntimes
    for binid in range(10):
        y = hist[binid]/(ntimes*dx) # normalize
        bar = "#" * int(y*50)
        print "%10.8f%s" % (y, bar)

randsum(100)
randsum(1000)
randsum(100000)
