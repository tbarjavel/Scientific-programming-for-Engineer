from __future__ import print_function
import math
from series import Series
################################################################


class ComputePi(Series):

    def __init__(self,):
        Series.__init__(self)
        self.current_value = 0

    def __del__(self):
        pass

    def compute(self, N):
        Series.compute(self, N)
        return math.sqrt(6.*self.current_value)

    def computeTerm(self, k):
        return 1./(1.*k*k)

    def getAnalyticPrediction(self):
        return math.pi
