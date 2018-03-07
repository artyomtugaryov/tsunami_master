import os
import numpy as np

if __name__ == '__main__':
    size = 100
    step = 0.0167
    bathymetry = np.ndarray([size, size], dtype=np.float32)
    for i in range(size):
        for j in range(size):
            if 20 <= i <= 980 and 20 <= j <= 980:
                bathymetry[i][j] = -5000
            else:
                bathymetry[i][j] = 10

    with open('my_bat.dat', "w") as file:
        for i in range(size):
            for j in range(size):
                file.write("{i}\t{j}\t{v}\n".format(i=i * step, j=j * step, v=bathymetry[i][j]))
