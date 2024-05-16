from __future__ import print_function
import math
from dumper_series import DumperSeries
################################################################


class PrintSeries(DumperSeries):

    def __init__(self, series, maxiter, freq):

        DumperSeries.__init__(self, series)

        self.maxiter = maxiter
        self.freq = freq

    def __del__(self):
        pass

    def dump(self):
        out = ""
        for i in range(1, int(self.maxiter/self.freq)):
            res = self.series.compute(i*self.freq-1)
            res2 = self.series.compute(i*self.freq)

            my_format = '{:.' + str(self.precision) + 'e}'
            out += str(i*self.freq) + " "
            out += my_format.format(res) + " "
            out += my_format.format(res2 - res)

            try:
                out += " " + my_format.format(
                    math.fabs(res2 - self.series.getAnalyticPrediction()))

            except Exception as e:
                pass

            out += "\n"
        return out
