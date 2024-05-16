#!/usr/bin/python

import numpy as np
import random 

a = 0.1

npoints = 100

data = np.zeros([3,npoints])
random.seed = 100

for i in range(0,npoints):
    data[0,i] = float(i)
    data[1,i] = float(i)*a
    data[2,i] = float(i)*a + random.gauss(0., 1.)

f = open('data.plot', 'w')

for i in range(0,npoints):
    line = "{0}\t{1}\t{2}\n".format(data[0,i],data[1,i],data[2,i])
    f.write(line)

f.close()
