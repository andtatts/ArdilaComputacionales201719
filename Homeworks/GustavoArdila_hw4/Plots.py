
# coding: utf-8

# In[17]:

import numpy as np
import matplotlib.pyplot as plt


# In[22]:

mapamundi=np.genfromtxt("map_data.txt")
data=np.loadtxt('coordinates.txt')
coordx=data[0]
coordy=data[1]
radio=data[2]
#mapamundi=np.loadtxt('map_data.txt')
xy=(coordx,coordy)
print data


# In[23]:

plt.figure(1)
plt.imshow(mapamundi)
plt.scatter(coordx,coordy)
plt.Circle(xy, radius=radio)
plt.savefig('PuntoNemo.pdf')


# In[ ]:



