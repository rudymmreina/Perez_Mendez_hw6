import os # http://www.tutorialspoint.com/python/os_file_methods.htm
import shutil # http://python.readthedocs.org/en/latest/library/shutil.html
import scipy
import scipy.linalg 
import sys
import numpy as np
import random
import matplotlib.pyplot as plt
from numpy import *

filename = sys.argv[1]

file = open(filename, 'r') #Open files from Brahe-3141-f/ directory
t, x, y= loadtxt(file, unpack=True) 


filename2 = filename.split('.')

plt.plot(x,y, 'ro')
plt.title('Grafica')
plt.ylabel('Y variable')
plt.xlabel('X variable')
plt.savefig(filename2[0] +'.pdf')
