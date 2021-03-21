import matplotlib.pyplot as plt
import numpy as np

data = np.genfromtxt("output/histogram_values.csv", delimiter=",", names=["x", "y"])
plt.plot(data['x'], data['y'])
plt.xlabel('Sample value')
plt.ylabel('Appearances')
plt.title('Histogram')

plt.show()
plt.savefig('output/histogram.png')