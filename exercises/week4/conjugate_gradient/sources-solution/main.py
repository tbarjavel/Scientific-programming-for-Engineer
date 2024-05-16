#!/usr/bin/env python3

from conjugate_gradient import solve as cgSolve
from optimizer import solve as scipySolve
from optimizer import plot
import numpy as np
import argparse

################################################################
# definitions of the quadratic form
################################################################
A = np.array([[4, 1], [1, 3]])
b = np.array([1, 2])
c = 6


def func(X):
    "functor calculation of the quadratic form"

    # makes a long array of shape [:, 2]
    X = np.array(X).flatten()
    X = X.reshape((X.shape[0]//2, 2))

    # computes the quadratic form
    res = 0.5*np.einsum('ai,ij,aj->a', X, A, X)
    res -= np.einsum('i,ai->a', b, X) + c
    return res


def jac(x):
    return A.dot(x) - b


def hess(x):
    return A


################################################################
# generic optimization program
################################################################

def optimize(method='cg'):
    tol = 1e-6
    x0 = np.array([2, 1])

    if method == 'BFGS':
        optimizer = scipySolve

    elif method == 'cg':
        optimizer = cgSolve

    else:
        raise RuntimeError('unknown solve method: ' + str(method))

    iterations = []
    iterations.append(x0)

    res = optimizer(
        func, x0, tol=tol, jac=jac, hess=hess,
        callback=lambda Xi: iterations.append(Xi))

    print('Method: ', method, ' Solution :', res)
    plot(func, iterations, method)


################################################################
# main function: parsing of program arguments
################################################################

if __name__ == '__main__':

    parser = argparse.ArgumentParser(
        description='Optimization exercise in python')

    parser.add_argument(
        '-m', '--method', type=str,
        help=('Specify the method to use for the optimization.'
              ' Can be cg/BFGS'), default='cg')

    args = parser.parse_args()
    optimize(args.method)
