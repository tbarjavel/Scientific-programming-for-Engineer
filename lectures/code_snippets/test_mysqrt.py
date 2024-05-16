
import pytest
import math

class NegativeException(Exception): 
    pass

def mysqrt(x):
    if (x < 0.):
        raise NegativeException();
    return math.sqrt(x);

def test_mysqrt_int():
    assert mysqrt(4) == 2

def test_mysqrt_double():
    assert mysqrt(2) == math.sqrt(2)

def test_mysqrt_negative():
    with pytest.raises(NegativeException):
        mysqrt(-1)
