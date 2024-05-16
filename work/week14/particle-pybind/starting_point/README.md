### How to run the code

We assume here that you have a Linux distribution with all the necessary packages (eigen, fftw3, pybind11) installed, and a Python3 distribution with the necessary packages as well (argparse, pybind11, numpy, matplotlib, etc.). We also assume that your `python` alias refers to Python 3.

Once you've cloned the repository, go to the source code directory. From the repo's root folder:

`cd work/week14/particle-pybind/starting_point`

Then create a build directory and move to it:

```
mkdir build
cd build
```

Now, configure the compilation utilities using Cmake:

`ccmake ..`

This will prompt a GUI in the terminal. Hit `c` to configure (i.e. find the FFTW and PyBind libraries) and then `g` to generate the makefiles. It will also generate a copied verison of the `main.py` and `generate_inpute.py` files from the parent source directory in the `build` folder.

Compile the C++ code:

`make`

Then using the `generate_input.py` file, create a `dumps subfolder` and generate an `init.csv` input file inside it containing the particles parameters, using the following command:

`python generate_input.py -n 262144 -H circular -T random -R 0.3 -o init.csv`

or with any parameters specified ( use `python generate_input.py -h` to see the help associated with the `generate_input.py` file).

To run a material point simulation of 10 steps with the `init.csv` initial file, a timestep of 0.1s and a dump frequency of 1, use:

`python ./main.py 10 1 dumps/init.csv material_point 0.1`

The output files, following a pattern of `step-XXXXX.csv`, will be created in the `build` folder



### Overloaded *createSimulation* method

The original *createSimulation* method of the *MaterialPointsFactory* class had 2 main roles:
- create unique *System* and *SystemEvolution* objects, and fill the System object with particles parsed from an input file
- create specific *Compute* object(s) that are going to be called at each iteration of our simulation

The main drawback of this method is that the creation and registration of *Compute* objects for this factory is **hard-coded**, meaning that the user has no flexibility in the type / number of *Compute* objects to be called at runtime.

We would now like to be able to register those *Compute* objects from the `main.py` python script, such that the user can possibly decide which one(s) to consider by simply modifying this python script, or even better, based on command line arguments.

This is done by overloading the *createSimulation* method with another declaration inside the class *MaterialPointsFactory*, taking a functor as an extra parameter. This functor object is registered as a method of the class, called *createComputes*, in charge of creating the *Compute* objects. The overloaded *createSimulation* method then calls the "original" one, which in turns calls the method *createComputes* method previously defined.

This mechanism allows to define which *Compute* objects are created and registered through the custom *createComputes* method **defined in Python** thanks to the *pybinder* functionalities.


### Management of *Compute* objects in python

*Compute* objects are created inside a function `createComputes` in our python script. If no holder type template argument is provided upon binding, these objects are created as `std::unique_ptr` by default. Unfortunately, such objects cannot then be used as function arguments, since that would imply that python needs to give up ownership of an object that is passed to this function, which is not possible.

This is an issue in our case, since we want to add these objects to the System Evolution by calling the addCompute(<compute_object>) method. Trying to pass such objects restuls in a runtime error:

`RuntimeError: Unable to load a custom holder type from a default-holder instance`

Moreover, using `std::unique_ptr` references means that the objects are deallocated when python’s reference count goes to zero, i.e. at the end of the `createComputes` function, which might affect their existence in the C++ world.

Hence, we define a `std::shared_ptr` holder upon binding of the *Compute* classes, such that the objects can be passed as function arguments.


### Management of *Factory* objects in python

*Factory* objects are accessed in the python script via their `getInstance` method that return singleton objects, and thus does not allow to return copies. Hence, we specify a reference return policy when binding these functions (`py::return_value_policy::reference`), which creates references to these objects, without python taking any ownership. The C++ side is responsible for managing the object’s lifetime and deallocating it when it is no longer used.

This scheme is affordable in our case since *Factory* objects are just used once, in order create a *SystemEvolution* object that is then completely independent from them. Hence, when the C++ side will delte those objects, they will not be use anymore in python.

A similar strategy is used to bind the `createSimulation` methods of the different factories, to match their C++ implementation that specifies a reference return.
