# -*- coding: utf-8 -*-
# @Author: Theo Lemaire
# @Date:   2018-10-09 13:25:52
# @Last Modified by:   Theo Lemaire
# @Last Modified time: 2018-10-09 16:07:42


import numpy as np
from scipy.optimize import minimize
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D


def S(x, y):
    ''' The function to optimize. '''
    return 2 * x**2 + 3 / 2 * y**2 + x * y - x - 2 * y + 6


def optimizer(fun, x0, method, tol):
    ''' The optimizer. '''
    return minimize(fun, x0, tol=tol, callback=getIterationSteps,
                    method=method)


def getIterationSteps(coords):
    ''' Optimizer callback, appending current x and y coordinates to an existing list. '''
    x_opt.append(coords)


def plotSurface(fun, x_opt, y_opt, fs=12):
    ''' Plot the 2D surface and the optimization solution at each iteration step. '''
    fig = plt.figure(figsize=(8, 6))
    ax = Axes3D(fig)
    ax.set_xlabel('x', fontsize=fs)
    ax.set_ylabel('y', fontsize=fs)
    ax.set_zlabel('S(x, y)', fontsize=fs)
    ax.view_init(elev=30, azim=130)

    x = np.linspace(-3, 3, 100)
    X, Y = np.meshgrid(x, x)
    ax.contour(X, Y, fun(X, Y), levels=np.linspace(5, 40, 10), colors='k', origin='lower')
    ax.plot_surface(X, Y, fun(X, Y), rstride=1, cstride=1, cmap='coolwarm', alpha=0.5)
    ax.plot(x_opt, y_opt, S(x_opt, y_opt), 'o--', c='r')

    return fig


if __name__ == '__main__':
    x_opt = [(2, 2)]
    method = 'BFGS'
    tol = 1e-9
    res = optimizer(lambda x: S(*x), x_opt[0], method, tol)
    x, y = zip(*x_opt)
    fig = plotSurface(S, np.array(x), np.array(y))
    fig.suptitle('{} (tol = {:.0e}, {} iterations)'.format(
        method, tol, res['nfev']), fontsize=15)

    plt.show()
