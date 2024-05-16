
import pytest
import numpy as np

class Particle:
    def __init__(self):
        position = np.zeros(3)
        velocity = np.zeros(3)
        force = np.zeros(3)

class System:
  particles = []

@pytest.fixture
def SystemTest():
    # SetUp
    System.particles = [Particle() for i in range(0, 10)]
    yield 
    # TearDown
    System.particles = []

def test_is_not_empty(SystemTest):
    assert len(System.particles) == 10  
