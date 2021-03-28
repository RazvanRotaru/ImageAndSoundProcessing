import matplotlib.pyplot as plt
import numpy as np
import sys
import os

def get_filename(file) :
    return os.path.splitext(file)[0] 

def magnitude_file(file) :
    return 'magnitudes_{}.csv'.format(get_filename(file))

data1 = np.genfromtxt('output/{}'.format(magnitude_file(sys.argv[1])), delimiter=",", names=["x", "y"])
data2 = np.genfromtxt('output/{}'.format(magnitude_file(sys.argv[2])), delimiter=",", names=["x", "y"])
data3 = np.genfromtxt('output/{}'.format(magnitude_file(sys.argv[3])), delimiter=",", names=["x", "y"])

fig, axarr = plt.subplots(2, sharex=True, sharey=True)

axarr[0].plot(data1['x'], data1['y'], label='{}_data'.format(get_filename(sys.argv[1])))
axarr[0].plot(data2['x'], data2['y'], label='{}_data'.format(get_filename(sys.argv[2])))
axarr[0].legend(loc="upper right")


axarr[1].plot(data3['x'], data3['y'], label='{}_data'.format(get_filename(sys.argv[3])), color='brown')
axarr[1].legend(loc="upper right")


fig.text(0.5, 0.05, 'Sample', ha='center', va='center')
fig.text(0.05, 0.5, 'Magnitude', ha='center', va='center', rotation='vertical')
fig.text(0.5, 0.92, 'Comparison chart', weight='bold', ha='center', va='center')

# plt.show()
plt.savefig('output/chart.png')