import numpy as np
import matplotlib.pyplot as plt


datos = np.loadtxt('trayectoria_0.25_30.dat')
t= datos[:,0]
x= datos[:,1]
y= datos[:,2]
z= datos[:,3]

fig = plt.figure()
ax = plt.axes()
ax.set_xlabel("t")
ax.set_ylabel("x")
ax.set_title("Posicion en X ")
plt.scatter(t,x, label="trayectoria x")
ax.legend()
plt.show()
filename = 'posicion_x'
plt.savefig(filename + '.pdf',format = 'pdf', transparent=True)
plt.close()

fig = plt.figure()
ax = plt.axes()
ax.set_xlabel("t")
ax.set_ylabel("y")
ax.set_title("Posicion en Y ")
plt.scatter(t,y, label="trayectoria y")
ax.legend()
plt.show()
filename = 'posicion_y'
plt.savefig(filename + '.pdf',format = 'pdf', transparent=True)
plt.close()

fig = plt.figure()
ax = plt.axes()
ax.set_xlabel("t")
ax.set_ylabel("x")
ax.set_title("Posicion en Z ")
plt.scatter(t,z, label="trayectoria")
ax.legend()
plt.show()
filename = 'posicion_z'
plt.savefig(filename + '.pdf',format = 'pdf', transparent=True)
plt.close()
