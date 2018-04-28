import os
import numpy as np

if __name__ == '__main__':
    size = 1000
    step = 0.0167
    with open('my_bat.dat', "w") as file:
        for i in range(size):
            for j in range(size):
                file.write("{i}\t{j}\t{v}\n".format(i=i * step, j=j * step,
                                                    v=5 if ((i * step - 8.016) ** 2 + (j*step - 8.016) ** 2) ** (1 / 2.) <= 0.25 else -i))
