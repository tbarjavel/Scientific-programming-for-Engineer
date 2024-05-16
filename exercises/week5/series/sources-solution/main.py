################################################################
from __future__ import print_function
import sys
from compute_pi import ComputePi
from compute_algebraic import ComputeAlgebraic
from print_series import PrintSeries
from plot_series import PlotSeries
################################################################


def main():

    argc = len(sys.argv)
    if argc < 5:
        print('Usage: python3 main.py series_type dumper_type maxiter freq\n\n'
              '\tseries_type: pi/algebraic\n'
              '\tdumper_type: print/plot\n'
              '\tmaxiter: number of loop iteration to compute the series\n'
              '\tfreq: frequency at which dumps/plots are made\n\n')
        sys.exit(-1)

    series_type = sys.argv[1]
    dumper_type = sys.argv[2]
    maxiter = int(sys.argv[3])
    freq = int(sys.argv[4])

    outfile = ""
    if argc == 6:
        outfile = sys.argv[5]

    if series_type == "pi":
        serie_object = ComputePi()
    elif series_type == "algebraic":
        serie_object = ComputeAlgebraic()
    else:
        raise RuntimeError("unknown series type: " + series_type)

    if dumper_type == "print":
        dumper_object = PrintSeries(serie_object, maxiter, freq)
    elif dumper_type == "plot":
        dumper_object = PlotSeries(serie_object, maxiter, freq)
    else:
        print("unknown dumper type: " + dumper_type)
        sys.exit(-1)

    dumper_object.setPrecision(20)

    if outfile != "":
        _file = open(outfile, 'w')
        _file.write(str(dumper_object))
    else:
        print(dumper_object)


main()
