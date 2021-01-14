import matplotlib.pyplot as plt
import numpy as np


data = np.genfromtxt(fname='./out.csv', dtype = np.int64, skip_header = 1)
plt.plot(data[:,1], data[:,0]);
plt.xlabel("Number of Pages");
plt.ylabel("Time Per Access");
plt.show();