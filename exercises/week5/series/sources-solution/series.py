from abc import ABC, abstractmethod


class Series(ABC):

    def __init__(self):
        self.current_term = 0
        self.current_value = 0

    def __del__(self):
        pass

    def compute(self, N):
        if self.current_term <= N:
            N -= self.current_term
        else:
            self.current_value = 0.
            self.current_term = 0

        for k in range(0, N):
            self.addTerm()

        return self.current_value

    @abstractmethod
    def getAnalyticPrediction(self):
        pass

    def addTerm(self):
        self.current_term += 1
        self.current_value += self.computeTerm(self.current_term)

    def computeTerm(self, k):
        pass
