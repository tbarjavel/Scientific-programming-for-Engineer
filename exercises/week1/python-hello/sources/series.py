

def computeSeries(Niterations):
    s = 0
    for k in range(1, Niterations + 1):  # n additions are necessary
        s += k
    return s
