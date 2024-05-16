#!/usr/bin/python

import numpy as np
import subprocess
import scipy.optimize
import os
import argparse
import matplotlib.pyplot as plt


# Argument parsing
parser = argparse.ArgumentParser(
    description='Optimize to find correct orbit of Mercury')
parser.add_argument('particle_executable', metavar='path',
                    type=str, help='path to executable of particle code')

args = parser.parse_args()

dump_path = './dumps'
trajectory_path = './trajectories'

exec_path = os.path.join('./', args.particle_executable)


init_file = './init.csv'


################################################################
def launchParticles(exe, input, nb_steps, freq, time_step):
    ret = subprocess.call([exe, str(nb_steps), str(freq),
                           input, 'planet', str(time_step)])
    if (not ret == 0):
        raise Exception("Problem in executing program " + str([exe,input,str(nb_steps),str(freq),str(time_step)]) + ": " + str(ret))


################################################################
launchParticles(exec_path, init_file, 365, 1, 1)
################################################################


def readPositions(planet_name, directory):
    positions = []
    for step in range(0, 365):
        filename = os.path.join(directory, "step-{0:04d}.csv".format(step))
        f = open(filename, 'r')

        for line in f:
            entries = line.split()
            if entries[0][0] == '#':
                continue
            if not entries[11] == planet_name:
                continue

            X = (float(entries[1]), float(entries[2]), float(entries[3]))
            positions.append(X)
    return np.array(positions)


################################################################
positions = readPositions('mercury', trajectory_path)
print('Reference Positions = ', positions)
################################################################


def computeError(positions, positions_ref):
    sq = (positions - positions_ref)**2
    ssq = np.sum(sq)
    return ssq


def readPositionsParticleCode(planet_name, directory):
    positions = []
    for step in range(0, 365):
        filename = os.path.join(directory, "step-{0:05d}.csv".format(step))
        f = open(filename, 'r')

        for line in f:
            entries = line.split()
            if entries[0][0] == '#':
                continue
            if not entries[10] == planet_name:
                continue

            X = (float(entries[1]), float(entries[2]), float(entries[3]))
            positions.append(X)
    return np.array(positions)


################################################################
positions_ref = readPositions('mercury', trajectory_path)
positions = readPositionsParticleCode('mercury', dump_path)
err = computeError(positions, positions_ref)
print('Error = ', err)
################################################################


def generateInput(scale, planet_name, input_filename, output_filename):
    f = open(input_filename, 'r')
    fout = open(output_filename, 'w')
    positions = []
    for line in f:
        if line[0] == '#':
            fout.write(line)
            continue

        entries = line.split()

        if (entries[10] == planet_name):
            VX = np.array((float(entries[3]),float(entries[4]),float(entries[5])))

            VX *= scale
            entries[3] = str(VX[0])
            entries[4] = str(VX[1])
            entries[5] = str(VX[2])

        for i in entries:
            fout.write(i + " ")

        fout.write("\n")


################################################################
generateInput(2.5, 'mercury', init_file, 'init2.csv')
################################################################


def runAndComputeError(scale, planet_name, input, exe, nb_steps, freq, time_step, trajectory_path, dump_path):
    generateInput(scale, planet_name, input,'tmp.csv')
    launchParticles(exe, './tmp.csv', nb_steps, freq, time_step)
    positions_ref = readPositions('mercury', trajectory_path)
    positions = readPositionsParticleCode('mercury', dump_path)
    err = computeError(positions, positions_ref)
    #print "{0} {1}".format(scale,err)
    return err


################################################################
runAndComputeError(2,'mercury', init_file, exec_path, 365, 1, 1, trajectory_path, dump_path)
################################################################

# Computing the error for different scales
res = []
nsteps = 100
_min = 0.25
_max = 0.75
for i in range(0, nsteps):
    s = 1.*i/nsteps*(_max-_min) + _min
    res.append((s, runAndComputeError(s, 'mercury',
                                      init_file, exec_path, 365, 1, 1, trajectory_path, dump_path)))

res = np.array(res)

fig = plt.figure()
axe = fig.add_subplot(1, 1, 1)
axe.plot(res[:, 0], res[:, 1])
plt.xlabel('scale')
plt.ylabel('Error')
plt.show()

# finding the scaling value which minimizes the error
initial_guess = 0.5
res = scipy.optimize.fmin(runAndComputeError, initial_guess, args=('mercury', init_file,
                                                                   exec_path, 365, 1, 1,trajectory_path, dump_path))
print('Scale = ', res)
err = runAndComputeError(res[0], 'mercury', init_file, exec_path, 365, 1, 1, trajectory_path, dump_path)
print('Error = ', err)
