import sys

if (not len(sys.argv) == 2):
    print("Not enough parameters for the program {0}".format(sys.argv[0]))
    sys.exit()

print("sys.argv is of type {0}".format(type(sys.argv)))
prog_name = sys.argv[0]
N = sys.argv[1]

print("{0} says: Hello {1}".format(prog_name, N))
