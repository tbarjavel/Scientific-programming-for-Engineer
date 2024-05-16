import numpy as np

# size of matrix dimensions
for n in [8, 9]:

    #  Generate 1D frequency coordinates
    freq1d = np.fft.fftfreq(n) * n

    #  Generate 2D frequency coordinates
    freq2d = np.einsum('i,j->ij', np.ones(n), freq1d)

    #  Store 2D frequency coordinates
    np.savetxt("build/test_computeFrequencies_n_{}.txt".format(n), freq2d, delimiter=" ", fmt='%.2f')
