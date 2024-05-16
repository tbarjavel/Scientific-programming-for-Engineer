from __future__ import print_function
from series import Series
################################################################


class ComputeAlgebraic(Series):

    def __init__(self):
        Series.__init__(self)

    def __del__(self):
        pass

    def getAnalyticPrediction(self):
        return 1.*self.current_term*(self.current_term+1)/2.

    def computeTerm(self, k):
        return 1.*k
