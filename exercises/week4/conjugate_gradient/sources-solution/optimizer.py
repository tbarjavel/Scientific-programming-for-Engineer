#!/usr/bin/env python3

import matplotlib.pyplot as plt
import numpy as np
import scipy.optimize
from mpl_toolkits.mplot3d import Axes3D


def plot(func, iterations, title):
    'Plotting function for plane and iterations'

    x = np.linspace(-3, 3, 100)
    y = np.linspace(-3, 3, 100)
    x, y = np.meshgrid(x, y)

    X = np.stack([x.flatten(), y.flatten()], axis=1)
    z = func(X).reshape((100, 100))

    xy = np.array(iterations)
    zs = func(xy)

    fig = plt.figure()
    ax = Axes3D(fig)
    ax.plot_surface(x, y, z, linewidth=0, antialiased=True,
                    cmap=plt.cm.viridis, alpha=0.2)
    ax.contour(x, y, z, 10, colors="k", linestyles="solid")
    ax.plot(xy[:, 0], xy[:, 1], zs, 'ro--')
    ax.grid(False)
    ax.set_title(title)

    plt.xlabel('$x$')
    plt.ylabel('$y$')
    plt.show()


def solve(fun, x0, tol='1e-8', callback=None, **kwargs):
    'Minimize function with BFGS'

    res = scipy.optimize.minimize(
        fun, x0, method='BFGS',
        callback=callback,
        tol=tol)

    return res.x
