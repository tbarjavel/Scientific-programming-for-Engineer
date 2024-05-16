import sys
import series


def main():

    if (not len(sys.argv) == 2):
        print("Not enough parameters for the program {0}".format(sys.argv[0]))
        return

    print("sys.argv is of type {0}".format(type(sys.argv)))
    prog_name = sys.argv[0]
    N = int(sys.argv[1])

    print("{0} says: Hello {1} {2}".format(
        prog_name, series.computeSeries(N), N*(N+1)/2))


if __name__ == '__main__':
    main()
