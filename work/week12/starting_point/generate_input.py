import os
import numpy as np
import math
import argparse
import matplotlib.pyplot as plt


def isSquare(n):
    ''' Check if an integer value is a perfect square or not. '''
    x = n // 2
    seen = set([x])
    while x * x != n:
        x = (x + (n // x)) // 2
        if x in seen:
            return False
        seen.add(x)
    return True


def plotDistributions(hv2d, temp2d):
    ''' Plot 2D heat and temperature distributions. '''
    fig, axes = plt.subplots(1, 2, figsize=(12, 5))

    ax = axes[0]
    ax.set_title('Heat source distribution')
    ax.set_xlabel('Y')
    ax.set_ylabel('X')
    ax.imshow(hv2d, extent=[-1, 1, -1, 1])

    ax = axes[1]
    ax.set_title('Temperature distribution')
    ax.set_xlabel('Y')
    ax.set_ylabel('X')
    ax.imshow(temp2d, extent=[-1, 1, -1, 1])

    return fig


def main():

    parser = argparse.ArgumentParser()
    parser.add_argument('-n', '--number', type=int, default=None,
                        help='Number of particles')
    parser.add_argument('-o', '--outfile', type=str, default=None,
                        help='Name of output file')
    parser.add_argument('-H', '--heatfield', type=str, default='circular',
                        help='Heat distribution type ("null", "line" or "circular")')
    parser.add_argument('-T', '--tempfield', type=str, default=None,
                        help='Initial temperature field ("random" or "homogeneous"),\
                        only used for non-test heatfields')
    parser.add_argument('-t', '--test', default=False, action='store_true',
                        help='Test configuration (temperature field automtcially generated')
    parser.add_argument('-R', '--radius', type=float, default=1 / 3,
                        help='Heat source radius (if heatfield is set to "circular")')
    parser.add_argument('-p', '--plot', default=False, action='store_true',
                        help='Plot heat and temperature distribution')
    parser.add_argument('--hr', type=float, default=1,
                        help='Specific heat rate')

    args = parser.parse_args()

    # Check for input validity
    test_error_str = 'cannot be specified for test configurations'
    if args.test:
        if args.outfile is not None:
            raise ValueError('output file {}'.format(test_error_str))
        if args.tempfield is not None:
            raise ValueError('temperature field {}'.format(test_error_str))
        if args.number is not None:
            raise ValueError('number of particles {}'.format(test_error_str))

    # Get number of particles and square root of it
    N = int(args.number) if args.number is not None else 16**2
    if not(isSquare(N)):
        raise ValueError('number of particles must be square')
    sqrtN = int(math.sqrt(N))

    # Set initial positions on a 2D rectilinear grid (z = 0)
    x = np.linspace(-1, 1, sqrtN)
    pos2d = np.array(np.meshgrid(x, x)).T

    # Set heat volumetric source according to user input
    hv2d = np.zeros((sqrtN, sqrtN))
    if args.heatfield == 'null':
        if args.test:
            # Test configuration: set constant temperature field
            theta2d = np.ones((sqrtN, sqrtN))
            outfile = 'testnull.csv'

    elif args.heatfield == 'line':
        # Set punctual (dirac) heat distribution
        hv2d[int(sqrtN / 4), :] = -sqrtN
        hv2d[int(3 * sqrtN / 4), :] = sqrtN

        # Test configuration: set corresponding temperature field from analytical solution
        if args.test:
            outfile = 'testline.csv'
            L = 2
            freqs = np.fft.fftfreq(sqrtN) * 2 * np.pi / L * sqrtN
            freqs_2d = np.einsum('i,j->ij', np.ones(sqrtN), freqs)
            freqs = freqs_2d**2 + freqs_2d.T**2
            freqs[0, 0] = 1.
            T = np.fft.fft2(hv2d) / freqs
            T[0, 0] = 0.
            T = np.fft.ifft2(T)
            theta2d = T.real

    elif args.heatfield == 'circular':
        if args.test:
            raise ValueError('no test configuration available for "circular" heat field')

        # Set circular heat distribution
        R = args.radius
        if R < 0:
            raise ValueError('radius must be positive')
        for i in range(sqrtN):
            for j in range(sqrtN):
                if (x[i]**2 + x[j]**2 < R):
                    hv2d[i, j] = sqrtN

    else:
        raise ValueError('heatfield must be "null", "line" or "circular"')

    if not args.test:
        # Set temperature field according to user input
        if args.tempfield == 'random' or args.tempfield is None:
            # Random field (between zero and 2)
            theta2d = np.random.random((sqrtN, sqrtN)) * 2
        elif args.tempfield == 'homogeneous':
            # Homogeneous field (all equal to one)
            theta2d = np.ones((sqrtN, sqrtN))
        else:
            raise ValueError('tempfield must be "random" or "homogeneous"')

        # Set output file according to user input
        outfile = args.outfile if args.outfile is not None else 'step-00000.csv'

    # Reshape matrices into serialized vectors
    positions = np.hstack((pos2d.reshape(N, 2), np.zeros((N, 1))))
    hv = np.reshape(hv2d, (hv2d.size, 1))
    theta = np.reshape(theta2d, (theta2d.size, 1))

    # Generate serialized vectors for other, constant quantities
    hr = args.hr * np.ones((N, 1))
    velocities = np.zeros((N, 3))
    forces = np.zeros((N, 3))
    masses = np.ones((N, 1))

    # Save data into csv file
    file_data = np.hstack((positions, velocities, forces, masses, theta, hr, hv))
    outdir = os.path.join(os.getcwd(), 'build', 'dumps')
    if not os.path.isdir(outdir):
        os.makedirs(outdir)
    filepath = os.path.join(os.getcwd(), 'build', 'dumps', outfile)
    np.savetxt(filepath, file_data, delimiter=" ")

    # Plot the heat and temperature fields
    if args.plot:
        plotDistributions(hv2d, theta2d)
        plt.show()


if __name__ == '__main__':
    try:
        main()
    except ValueError as e:
        print('Error:', e)
        quit()
