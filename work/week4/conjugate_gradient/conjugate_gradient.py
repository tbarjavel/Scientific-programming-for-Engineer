# -*- coding: utf-8 -*-
# @Author: Theo Lemaire
# @Date:   2018-10-09 14:18:16
# @Last Modified by:   Theo Lemaire
# @Last Modified time: 2018-10-09 16:08:19

import numpy as np
import matplotlib.pyplot as plt

from optimizer import S, plotSurface


# dSdx = 4x + y - 1
# dSdy = 3y + x - 2
A = np.array([[4, 1], [1, 3]])  # 2nd derivative matrix (D2{S(x, y)})
b = np.array([1, 2])  # (x, y) vector that cancels D{S(x, y)}


def getIterationSteps(coords):
    ''' Optimizer callback, appending current x and y coordinates to an existing list. '''
    x_opt.append(coords)


def ConjugateGradient(A, b, x, tol):
    ''' Conjugate Gradient implementation (from Wikipedia) to find the minimum
        of a quadratic function.

        :param A: function's 2nd derivative matrix
        :param b: vector that cancels the function's derivative matrix
        :param x: vector of initial coordinates
        :param tol: residual absolute tolerance
        :return: vector of final coordinates
    '''

    # make sure input is float typed
    x = np.array(x, dtype=float)

    # initialize residual and basis vector
    r = b - np.einsum('ik,k->i', A, x)
    p = r
    rsold = np.einsum('k,k->', r.T, r)

    # iterate until residual is below given tolerance
    rsnew = np.inf
    niter = 0
    while np.sqrt(rsnew) >= tol:
        Ap = np.einsum('ik,k->i', A, p)
        alpha = rsold / np.einsum('k,k->', p.T, Ap)
        x += alpha * p
        r -= alpha * Ap
        rsnew = np.einsum('k,k->', r.T, r)
        p = r + rsnew / rsold * p
        rsold = rsnew
        getIterationSteps(x)
        niter += 1
    return x, niter


if __name__ == '__main__':
    x_opt = [(2, 2)]
    tol = 1e-9
    _, niter = ConjugateGradient(A, b, x_opt[0], tol)
    x, y = zip(*x_opt)
    fig = plotSurface(S, np.array(x), np.array(y))
    fig.suptitle('Custom Conjugate Gradient (tol = {:.0e}, {} iterations)'.format(
        tol, niter), fontsize=15)
    plt.show()
