# -*- coding: utf-8 -*-
# @Author: Theo Lemaire
# @Date:   2018-10-16 11:52:15
# @Last Modified by:   Theo Lemaire
# @Last Modified time: 2018-10-23 18:57:39

import os
from argparse import ArgumentParser
import matplotlib.pyplot as plt
import numpy as np


def plotSeries(iterations, values, fs=15, lw=2):

    fig, ax = plt.subplots(figsize=(10, 6))
    ax.set_xlabel('# iterations', fontsize=fs)
    ax.set_ylabel('value', fontsize=fs)
    ax.plot(iterations, values, label='series', linewidth=lw)
    for item in ax.get_xticklabels() + ax.get_yticklabels():
        item.set_fontsize(fs)
    return fig


def main():

    # Define argument parser
    ap = ArgumentParser()
    ap.add_argument('-i', '--inputfile', type=str, help='Input filename')

    # Parse arguments
    args = ap.parse_args()
    filepath = args.inputfile

    # Infer separator character from file extension
    filename = os.path.basename(filepath)
    filecode, ext = os.path.splitext(filename)
    print(filecode, ext)
    if ext == '.csv':
        separator = ','
    elif ext == '.txt':
        separator = '\t'
    elif ext == '.psv':
        separator = '|'

    # Load data
    data = np.genfromtxt(filepath, delimiter=separator)
    iterations = data[1:, 0]
    values = data[1:, 1]

    # Plot series
    fs = 20
    fig = plotSeries(iterations, values, fs=fs)
    fig.suptitle('{} evolution'.format(filecode), fontsize=fs)
    plt.show()


if __name__ == '__main__':
    main()
