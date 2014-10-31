import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import sys

d=sys.argv[1]

datos = np.loadtxt(d)
t= datos[:,0]
x= datos[:,1]
y= datos[:,2]
z= datos[:,3]


fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
o=fig.gca(projection='3d')
o.scatter(x,y,z)
o.set_xlabel('x')
o.set_ylabel('y')
o.set_zlabel('z')
plt.savefig('trayectoria3d.pdf')



fig = plt.figure()
ax = plt.axes()
ax.set_xlabel("x")
ax.set_ylabel("y")
ax.set_title("x vs y")
plt.scatter(x,y)
ax.legend()
plt.savefig('proyeccion2d.pdf')
plt.close()


