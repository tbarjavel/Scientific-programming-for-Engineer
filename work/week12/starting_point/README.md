# Homework week12 ReadMe

Before checking the instructions below, make sure to open a terminal at thte project root directory and to move to the appropriate source code directory:
`cd work/week12/starting_point`
Once you are there, make sure to create a `build` directory:
`mkdir build`
Then move to that direcgtory, create the makefiles and build the program:

`cd build`

`ccmake ..`

`make`

## Exercise 1: Code discovery
See below in the readme or in the Doxyfile the descriptions of the newly implemented code and classes.

### MaterialPoint class

This class is meant to be used as the fundamental entity (i.e. a grid point) to compute the spatio-temporal evolution of heat on a 2D grid. To this effect, the class inherits from the Particle class and defines three additional real number attributes: temperature, heat rate, and heat distribution at the space position where the particles is placed, to be used to solve the heat equation.


### matrix.hh file

The *matrix.hh* file defines several 2D template grid classes to work with particles of any type. A particle is supposed to be a point in the grid.

#### MatrixIterator
This template is an abstract object allowing iteration over Matrix objects.
It contains a pointer to a Matrix object as well as a size and an index field referring to the size of the matrix and the current index.
It also contains several operators:
- the ++ operator handles iteration by just incrementing the index field
- the * operator (i.e. accessor) returns the content of the i-th element of the matrix (i.e. at the current index)
- the != operator checks for inequality of index fields between the current operator and another operator

#### Matrix
This template is an abstract data type representing a 2D square (NxN) matrix.
Its underlying data container is a 1D std::vector.
It also contains several methods and operators:
- the size(), rows() and cols() methods all return the size (N) of the matrix, which is the square root of the number of elements in the 1D vector (NxN)
- the resize() method resizes the matrix by resizing the underlying data vector
- the accessor operator returns, for a pair of indexes (i, j), the element of the 1D vector at the corresponding serialized index (j * N + i)
- the /= operator handles element-wise division of the matrix by a scalar
- the data() method returns the underlying data vector
- the begin() and end() methods return iterator objects that can point to the first and last elements of the matrix, which can then be used in range for loop to iterate over the matrix elements.


#### MatrixIndexIterator
This template defines a more complex type of abstract operator that inherits from MatrixIterator, but with overwritten accessor element that now returns a 3 elements (i, j, x) tuple, where x is the pointed element, i and j represent the indexes of the element along both matrix dimensions.

#### IndexedMatrix
This template defines a wrapper around the Matrix template in which the begin and end operators are of type *MatrixIndexIterator*, and can then be used in different types of range for loops.
The index() method can be used to convert a "simple" Matrix object into an IndexedMatrix object.

Finally, the std::iterator_traits template is used to define the data type used by the MatrixIterator objects when they are then used in other parts of the code.


#### MaterialPointsFactory

This class is meant to be used as the interface through which the user can initialize a collection of MaterialPoint objects and then run a simulation to compute the spatio-temporal evolution of temperature across these points. To this effect, it inherits from the generic ParticlesFactoryInterface and redefines the createParticle and createSimulation methods in the specific context of material points (e.g. making sure that number of points is square at initialization).


### fft.hh

This file defines an FFT structure that is a wrapper around the FFTW library. In particular, it defines 3 functions to work with signals of complex numbers:
- the transform() function to compute the forward FFT of a complex signal
- the itransform() function to compute the inverse FFT of a complex signal
- the computeFrequencies() function to compute the sample frequencies of the forward FFT of a complex signal (i.e. the coordinates of the signal in the Fourier space). The Laplacian of these frequencies is then used to sovle the heat equation in the Fourier space.

## Exercise 2: FFT library linking
See the Cmake list modifications, first, the path for the fft library is found and then, if the option UseFFTW in the CCMake is activated it will be linked with our library ae well as the test ones.

## Exercise 3: Interface implementation

### FFT interface

The purpose of this class is to define some easy to use wrapper around the FFTW library to then use them in the rest or our code.
The transform and itransform functions work as follows:
- we first check the memory allocation of our input matrix
- we then get the input matrix size and initialize output matrix
- we initialize input and output fftw_complex pointers from the underlying data field of our matrices
- we then create, execute and destroy our FFT plan
- finally, we return the FFT (or FFT-1) matrix

The computeFrequencies function aims at generating the corresponding frequecy coordinates in the Fourier space for an input signal of a specific size. For that, it mimicks the numpy.fft.fftfreq function and projects the 1D output onto a 2D matrix.


### FFT testings

#### forward FFT testing:
A matrix is created with values such as we can know its fft transform. We then compare the analytical values to the ones computed with the FFT transfer function.

#### inverse FFT testing:
A matrix is created with values such as we can know its ifft transform. We then compare the analytical values to the ones computed with the backward FFT transfer function.

### FFT compute frequencies:

The function is tested by comparing its output with that of the equivalent numpy.fft.fftfreq function, for both even and odd numbers.

To run the tests, simply generate the data files from the python script (make sure to have a build folder beforehand):
From the source code directory:

`python test_fftfreq.py`

And then from the `build` directory, run:

`./test_fft`

For simplicity, the computed data files have been put in the source directory, so you can simply paste them into the build sub-folder and run the test.


## Exercise 4: Solver implementation

### 1/ ComputeTemperature subclass

Takes the system of particles and compute a time step of integration of temperatures.

The class has:
- a *constructor* that handles the computation of all invariant fields (frequencies, laplacian and Fourier heat distribution)
- a *computeDerivative* method that populates a temperature matrix from the system particles, computes its FFT transform and then its time derivative from the heat equation, which is then projected back to space domain with an inverse FFT and returned.
- *compute* method that simply calls the computeDerivative method and then applies a simple forward Euler integration scheme to it in order to compute the temperature field evolution.


### 2-3/ Validating test for null / linear heat fluex and homogeneous / equilibrium temperature field

First, from the source directory, run the `generate_input.py` script as follows:

`python generate_input.py -t -H null`

which will produce a "testnull.csv" input file in the `build/dumps` folder with zero heat source and a homogeneous temperature.

Then, run the same script with the "line" option:

`python generate_input.py -t -H line`

which will produce a "testline.csv" input file in the `build/dumps` folder with bi-linear heat source and a temperature field at equilibrium.

Then, move to the build directory and run the appropriate test:

`./test_heat_eq`

which populates the system successively with the generated inputs and checks that the derivative of the temperature field is equal/close to zero.


### 4/ Implementation of  a python script to generate a heat distribution within a provided radius

To generate the csv input files containing the initial data, simply run `generate_input.py` script.

For instance, to generate an initial matrix of 16 by 16 points, with a circular heat source distribution and a random temperature field, type in (from the source directory):

`python generate_input.py -H circular -T random -n=256`

The output file (`step-00000.csv`) will be saved in an underlying `build/dumps` directory (make sure the `build` directory is created beforehand).

For more details about all the underlying options, please run:

`python generate_input.py -h`

The outputed CSV file consists of the particles positions, velocities, forces, masses, temperatures, heat rates and heat source distributions.

The particles positions will consist of a sqrt(N)xsqrt(N) matrix of points within a domain spans of [-1,1],[-1,1].

The name file is at default step-00000.csv but it can be changed as wanted (-o).

The Heat distribution can be (-H) null, line, or circular.

The circular heat radius can be defined there too ( -R Value).

The temperature field (-T) of the particles can be set as *random* within a defined range or to be *homogeneous*.

It is possible to plot (-p) the corresponding heat and temperature distributions to verify what we generate as an input.

To set a zero degrees temperature condition on the boundaries for this specific case while being able to run the previous tests, this stringent condition is maintained by a different compute object (ComputeTemperatureBoundaries), that is instanciated by the MaterialPointsFactory and therefore added in the system evolution.

### 5/ Launching a simulation which will produce dumps observable with Paraview for a grid of 512 × 512 particles.

To launch such a simulation, first the inputs have to be created. Form the source directory, run:

`python generate_input.py -n 262144 -H circular -T random -R 0.3`

This will create a matrix of 512x512 material points with the appropriate input parameters, saved in a default file named "step-00000.csv" created in the `build/dumps` sub-folder.

Then run the C++ code that will handle the system's integration. From the `build` folder:

`./particles 100 1 dumps/step-00000.csv material_point 0.001`

This will integrate the system for 100 iterations with a time step of 0.001s and 100 step-00XX.csv files in the `dumps` folder with the positions of the particles at fields 0,1,2 (spanning it the [-1,1]x[-1,1] space) and their temperatures at field 10 and their heat source location value at field 12.

These files can then be loaded into *Paraview*, which allows to display (after setting the delimiter space, keeping the values and convertion from table to points with the coordinates defined) the position of all our particles. To view the value and temperature and heate source fields, it can be done from the the property tab, where the colouring of the point can be done with one selected field (if we want to display the temperature field 10 and heat source field 12). To Glyph feature can provide a better display of the points if the visibility is not good enough.


