#!/usr/bin/python

import numpy as np
import math
import matplotlib.pyplot as plt

################################################################


def evalFunction(f, xmin, xmax, npoints):
    x = np.linspace(xmin, xmax, npoints)
    y = f(x)
    return x, y

################################################################


def myPlot(x, y, fig, label=None,
           linestyle='-', marker='', xlabel='', ylabel='', title='', axe=None):

    x = np.array(x)
    y = np.array(y)

    if axe is None:
        axe = fig.add_subplot(111)
    axe.plot(x, y, linestyle=linestyle, marker=marker, label=label)
    axe.set_title(title)
    axe.set_xlabel(xlabel)
    axe.set_ylabel(ylabel)
    if label is not None:
        axe.legend()

################################################################


def exo1():

    x = [0., 2., 4., 6., 8., 10.]
    y = [0., 0., 0., 1., 1., 1.]
    myPlot(x, y, plt.figure())
    myPlot(x, y, plt.figure(), marker='x', linestyle='--')


################################################################

def exo2():

    x = np.array([0., 2., 4., 6., 8., 10.])
    y = np.array([0., 0., 0., 1., 1., 1.])
    fig = plt.figure()
    axe = fig.add_subplot(111)
    myPlot(x, y, fig, title='my super cool plot',
           xlabel='my X', ylabel='my Y', label='step', axe=axe)
    myPlot(x, -1.*y, fig, title='my super cool plot',
           xlabel='my X', ylabel='my Y', label='$-y$', axe=axe)
    fig.savefig('myfigure.pdf')

################################################################


def exo3():
    xmin = 0.
    xmax = 2.*math.pi
    npoints = 100
    x = np.linspace(xmin, xmax, npoints)
    y = np.sin(x)
    myPlot(x, y, plt.figure(), label='$sin(x)$')

################################################################


def exo4():
    fdata = np.loadtxt('data.plot')
    print(fdata.shape)
    fig = plt.figure()
    axe = fig.add_subplot(111)
    myPlot(fdata[:, 0], fdata[:, 1], fig, label='analytic', axe=axe)
    myPlot(fdata[:, 0], fdata[:, 2], fig, label='measure', axe=axe)
    fig2 = plt.figure()
    error_val = np.sqrt((fdata[:, 1]-fdata[:, 2])**2)
    myPlot(fdata[:, 0], error_val, fig2, label='error')

    fig3 = plt.figure()
    axe = fig3.add_subplot(111)
    axe.errorbar(fdata[:, 0], fdata[:, 1], error_val,
                 marker='D', linestyle='--', label='prediction')
################################################################


exo1()
exo2()
exo3()
exo4()

plt.show()
