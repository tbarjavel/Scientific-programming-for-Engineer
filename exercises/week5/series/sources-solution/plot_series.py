from __future__ import print_function
from dumper_series import DumperSeries
import matplotlib.pyplot as plt
################################################################


class PlotSeries(DumperSeries):

    def __init__(self, series, maxiter, freq):

        DumperSeries.__init__(self, series)

        self.maxiter = maxiter
        self.freq = freq

    def __del__(self):
        pass

    def dump(self):

        fig = plt.figure()
        axe = fig.add_subplot(1, 1, 1)
        x = []
        numerical = []
        analytic = []

        for i in range(1, int(self.maxiter/self.freq)):
            res = self.series.compute(i*self.freq-1)
            x.append(i*self.freq)
            numerical.append(res)
            analytic.append(self.series.getAnalyticPrediction())

        axe.plot(x, numerical, marker='o', label='Numerical')
        axe.plot(x, analytic, label='Analytical')
        axe.set_xlabel(r'$k$')
        axe.set_ylabel(r'Series')
        axe.legend()
        plt.show()

        return "Plotted"
