#!/usr/bin/env python3

import numpy as np


def solve(func, x0, jac=None, hess=None,
          max_iter=50, tol=1e-8,
          callback=None):
    'Minimize function with home-made conjugate gradient'

    if jac is None:
        raise RuntimeError('this method needs a jacobian to be provided')

    if hess is None:
        raise RuntimeError('this method needs a hessian to be provided')

    x_old = x0
    r_old = -jac(x0)
    p_old = r_old

    # conjugate iteration loop
    for i in range(0, max_iter):

        # fetch the hessian
        A = hess(x_old)

        Ap_old = np.einsum('ij,j->i', A, p_old)

        alpha = (np.einsum('i,i->', r_old, r_old) /
                 np.einsum('i,i->', p_old, Ap_old))

        x_new = x_old + alpha * p_old
        r_new = r_old - alpha * Ap_old

        # call the callback over iterations
        if callback:
            callback(x_new)

        # evaluate stop criterion
        if np.linalg.norm(x_new-x_old) < tol:
            return x_new

        beta = (np.einsum('i,i->', r_new, r_new) /
                np.einsum('i,i->', r_old, r_old))

        p_old = r_new + beta * p_old
        r_old = r_new
        x_old = x_new

    return False
