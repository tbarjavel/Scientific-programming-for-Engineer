from abc import ABC, abstractmethod


class DumperSeries(ABC):

    def __init__(self, series):
        self.series = series
        self.precision = 4

    def __del__(self):
        pass

    @abstractmethod
    def dump(self):
        pass

    def setPrecision(self, precision):
        self.precision = precision

    def __str__(self):
        return self.dump()
