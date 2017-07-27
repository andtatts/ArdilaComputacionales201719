import numpy as np
import matplotlib.pyplot as plt

#imports the data and creates a  numpy array
mapamundi=np.genfromtxt("map_data.txt")
#imports the data generated from the c script and creates an array
data=np.loadtxt('coordinates.txt')
#from data creates the corresponding coordinates
coordx=data[0]
coordy=data[1]
radio=data[2]

#mapamundi=np.loadtxt('map_data.txt')
xy=(coordx,coordy)
#print data


#plots
plt.figure(1)
#as a suggestion from Alfredo Ricci, the map has been plotted using an imshow
plt.imshow(mapamundi)
#scatter to plot the point
plt.scatter(coordx,coordy)
#searching in the matplotlib documentation, the function circle creates the circle we need
plt.Circle(xy, radius=radio)
plt.savefig('PuntoNemo.pdf')






