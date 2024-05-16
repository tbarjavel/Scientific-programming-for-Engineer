
### How to run code for homework 2

It is assumed here that you are running the code on a **Linux** distribution with a **recent C++ compiler** (C++14 compatible, e.g. gcc 5.0+) and a **recent cmake version** (2.6+)

- Open a terminal to the root of the repository
- Pull the latest content from the remote repository: `git pull`
- Move to the appropriate subfolder: `cd work/week6/series/homework2`
- Create a build subfolder: `mkdir build`
- Move to the build subfolder: `cd build`
- Generate the compiler Makefile with cmake: `cmake ..`
- Compile the code to build the executable: `make`

You can run the executable with the appropriate command line arguments:

`src/main <SERIES> <NUMBER_OF_ITERATIONS> <DUMP_METHOD< <FREQUENCY/SEPARATION> <PRECISION>`

Here are the different command line arguments:
- **SERIES**: can be "pi" or "ar" to compute pi series or arithmetic series respectively.
- **NUMBER_OF_ITERATIONS**: number of iterations (>0) in the selected series.
- **DUMP_METHOD**: "print" or "write" to either print or write on a file the evolution of the series.
- **FREQUENCY** (optional, default = 1, valid only if DUMP_METHOD = "print"): logging frequency during the series computation.
- **SEPARATION** (optional, default = "\t" , valid only if DUMP_METHOD = "write"): character delimiting the separation between columns in the output file to be written ("," for .csv file, "|" for a .psv file, and "" or "\t" for a .txt file).
- **PRECISION** (optional, default = 10): sets the decimal precision to be used to format floating-point values on output operations.

The resulting output will be displayed on the terminal.

If you've chosen to write the series computation onto a file, you can plot the results using a custom-made **Python 3 script**:
- Move to the src folder: `cd ../src`
- Execute the script: `python plot_results.py -i <INPUTFILE>`
where **INPUTFILE** is a string representing the absolute or relative path to the data file, e.g.:
`python plot_results.py -i ../build/computepi.csv`

### Work division strategy (3 people)

1. Definition of top-level code interface:
- Tristan: Series class (`series.hh`)
- Théo: define DumperSeries class (`dumper.hh`)

2. Definition and implementation of Series subclasses:
- Tristan: ComputePi class (`pi.hh` and `pi.cc`)
- Théo: ComputeArithmetic class (`arithmetic.hh` and `arithmetic.cc`)
- Théo: modification of main to execute series (`main.cc`)

3. Definition and implementation of DumperSeries subclasses:
- Tristan: PrintSeries class (`print.hh` and `print.cc`)
- Théo: WriteSeries class (`write.hh` and `write.cc`)

4. Re-definition of printing methods in DumperSeries:
- Tristan: modify DumperSeries and PrintSeries classes

5. Evluation of complexity:
- Flavio: modify Series, ComputePi and ComputeArithmetic classes to optimize computation

6. "Bonus":
- Flavio: Implementation of exhaustive, robust testing and options in main file
