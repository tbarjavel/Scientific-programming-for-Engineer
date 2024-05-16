# -*- coding: utf-8 -*-
# @Author: Theo Lemaire
# @Date:   2018-10-16 11:32:08
# @Last Modified by:   Theo Lemaire
# @Last Modified time: 2018-10-16 14:34:50

import math
from argparse import ArgumentParser


class Series:
    def __init__(self):
        self.current_term = 0
        self.current_value = 0

    def compute(self, N):
        raise Exception("pure virtual function")

    def getAnalyticPrediction(self):
        raise Exception("pure virtual function")


class ComputeArithmetic(Series):
    def __init__(self):
        super().__init__()

    def __str__(self):
        return 'ComputeArithmetic'

    def compute(self, N):
        # series_value = 0
        series_value = self.current_value
        # for k in range(1, N + 1):
        for k in range(self.current_term + 1, N + 1):
            series_value += k
        self.current_term = N
        self.current_value = series_value
        return self.current_value


class ComputePi(Series):
    def __init__(self):
        super().__init__()

    def __str__(self):
        return 'ComputePi'

    def compute(self, N):
        # sum = 0
        sum = self.current_value**2 / 6
        # for k in range(1, N + 1):
        for k in range(self.current_term + 1, N + 1):
            sum += 1 / k**2
        self.current_term = N
        self.current_value = math.sqrt(6 * sum)
        return self.current_value

    def getAnalyticPrediction(self):
        return math.pi


def main():

    # Define argument parser
    ap = ArgumentParser()
    ap.add_argument('-n', '--niter', type=int, default=5, help='Number of iterations')
    ap.add_argument('-s', '--seriestype', type=str, default='Ar', help='Series type (Ar or Pi)')

    # Parse arguments
    args = ap.parse_args()
    n = args.niter
    s = args.seriestype.lower()
    if n < 0:
        raise ValueError('N must be positive')

    # Instantiate appropriate series
    if s == 'ar':
        obj = ComputeArithmetic()
    elif s == 'pi':
        obj = ComputePi()
    else:
        raise ValueError('Unknown series type')

    # Call compute method
    print('{}({}) = {}'.format(obj, n, obj.compute(n)))


if __name__ == '__main__':
    main()
