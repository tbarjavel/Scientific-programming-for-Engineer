# -*- coding: utf-8 -*-
# @Author: Theo Lemaire
# @Date:   2018-10-16 11:52:15
# @Last Modified by:   Theo Lemaire
# @Last Modified time: 2018-10-16 14:31:19

from argparse import ArgumentParser
import matplotlib.pyplot as plt

from series import ComputeArithmetic, ComputePi


class DumperSeries:
    def __init__(self, series):
        self.series = series

    def dump(self):
        raise Exception("pure virtual function")


class PrintSeries(DumperSeries):
    def __init__(self, series, frequency, maxiter):
        super().__init__(series)
        self.frequency = frequency
        self.maxiter = maxiter

    def dump(self):
        for n in range(1, self.maxiter + 1, self.frequency):
            s = self.series.compute(n)
            try:
                delta = self.series.getAnalyticPrediction() - s
                delta_str = ' (Delta = {:.2e})'.format(delta)
            except Exception as e:
                delta_str = ''
            print('{}({}) = {:.5f} {}'.format(self.series, n, s, delta_str))


class PlotSeries(DumperSeries):
    def __init__(self, series, maxiter):
        super().__init__(series)
        self.maxiter = maxiter

    def dump(self, fs=15, lw=2):
        iterations = range(1, self.maxiter + 1)
        fig, ax = plt.subplots(figsize=(10, 6))
        ax.set_title('{} convergence'.format(self.series), fontsize=fs)
        ax.plot(iterations, [self.series.compute(n) for n in iterations],
                label='series', linewidth=lw)
        try:
            ax.axhline(self.series.getAnalyticPrediction(),
                       linestyle='--', linewidth=lw, c='k', label='analytic prediction')
        except Exception as e:
            print('series does not have constant analytical prediction')
        ax.set_xlabel('# iterations', fontsize=fs)
        ax.set_ylabel('{} value []'.format(self.series), fontsize=fs)
        for item in ax.get_xticklabels() + ax.get_yticklabels():
            item.set_fontsize(fs)
        ax.legend(frameon=False, fontsize=fs)
        plt.show()


def main():

    # Define argument parser
    ap = ArgumentParser()
    ap.add_argument('-n', '--niter', type=int, default=5, help='Number of iterations')
    ap.add_argument('-s', '--seriestype', type=str, default='Ar', help='Series type (Ar or Pi)')
    ap.add_argument('-f', '--frequency', type=int, default=1, help='Dumping frequency')
    ap.add_argument('-p', '--plot', default=False, action='store_true', help='Plot results')

    # Parse arguments
    args = ap.parse_args()
    n = args.niter
    f = args.frequency
    s = args.seriestype.lower()
    if n < 0:
        raise ValueError('N must be positive')

    # Instantiate appropriate series
    if s == 'ar':
        series = ComputeArithmetic()
    elif s == 'pi':
        series = ComputePi()
    else:
        raise ValueError('Unknown series type')

    # Instantiate appropriate dumper series
    if args.plot:
        ps = PlotSeries(series, n)
    else:
        ps = PrintSeries(series, f, n)

    # Call dump method
    ps.dump()

    # Initial complexity:
    # 1 series output at specific N: S = sum(k=1 -> N, ...) -> O(N)
    # series output from 1 to maxiter: sum(N=1 -> maxiter, sum(k=1 -> N, ...))
    #                                  -> O(sum(N=1 -> maxiter, O(N))
    #                                  -> O(maxiter*(maxiter + 1) / 2)

    # New complexity: O(maxiter) !

    # With reversed computation of Pi, we cannot optimize the complexity of the dump method
    # by storing intermediate values, hence complexity is bound to O(maxiter*(maxiter + 1) / 2)


if __name__ == '__main__':
    main()
