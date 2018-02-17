import os
import numpy as np

if __name__ == '__main__':
    size = 1000
    step = 0.0167
    bathymetry = np.ndarray([size, size], dtype=np.float32)
    for i in range(size):
        for j in range(size):
            if 1<=i<=998 and 1<=j<=998:
                bathymetry[i][j] = -100
            else:
                bathymetry[i][j] = 10

    with open('bat.dat', "w") as file:
        for i in range(size):
            for j in range(size):
                file.write("{i}\t{j}\t{v}\n".format(i=i*step, j=j*step, v=bathymetry[i][j]))
