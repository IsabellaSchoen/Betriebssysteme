import matplotlib.pyplot as plt
import numpy as np


data = np.genfromtxt(fname='./out.csv', dtype = np.int64, skip_header = 1)
print(data)
plt.plot(data[0:9], data[:10]);
plt.xlabel("Size of memory");
plt.ylabel("Bandwith");
plt.show();