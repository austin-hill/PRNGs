import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

s = np.zeros(100002)
s[0] = np.random.randint(2**31)
m = 2**31

for i in range(100001):
    s[i+1] = (65539*s[i]) % m

x = s[0:100000] / m
y = s[1:100001] / m
z = s[2:100002] / m

fig = plt.figure()
ax = Axes3D(fig)
ax.view_init(-160, -123)
ax.set_xlabel(r'$u_{i}$')
ax.set_ylabel(r'$u_{i+1}$')
ax.set_zlabel(r'$u_{i+2}$')
ax.scatter(x, y, z, s=0.1)
plt.show()
