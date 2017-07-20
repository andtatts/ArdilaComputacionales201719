
# coding: utf-8

# In[1]:

import numpy as np
import matplotlib.pyplot as plt


# In[2]:

#loads the data and creates a numpy array
datos_x=np.loadtxt('datos_x.txt')
datos_y=np.loadtxt('datos_y.txt')
datos_z=np.loadtxt('datos_z.txt')
planetas=10;
n=1000


# In[3]:

#runs over the cols
plt.figure(1)
for i in range(0,planetas):
    plt.scatter(datos_x[:,i],datos_y[:,i])
plt.title('Orbitas')
plt.savefig('orbitas.png')

