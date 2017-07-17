#import numpy and pyplot packages 
import numpy as np
import matplotlib.pyplot as plt
#create and define the class associated with the charges
class cargas:
#according to the hw1.pdf a value for coulomb constant is needed
	k=2.306e-2
#each charge in the class will have three atributes: charge, x position and y position
	def __init__(self,q0,dx0,dy0):
		self.q=q0
		self.x=dx0
		self.y=dy0
#now each charge in the class has a potential, this will be calculated using a simple function
	def potencial(self,x,y):
#calculates the distance to a certain point
		distancia=np.sqrt((x+self.x)**2 + (y+self.y)**2)
		V=cargas.k*(self.q/(distancia+0.5))
		return(V)
#define the charges in the square centered at the origin
carga_1=cargas(+1,-0.5,-0.5)
carga_2=cargas(-1,-0.5,+0.5)
carga_3=cargas(+1,+0.5,+0.5)
carga_4=cargas(-1,+0.5,-0.5)
#in order to work in a certain space a x, y coordinates must be generated
x=np.linspace(-1,1,100)
y=np.linspace(-1,1,100)
#from a basic electromagnetism course and the Griffiths book it is easy to see that the potential depends on the quadrupolar momentum i.e, the potential must be a matrix
#a zeros matrix is needed so the potential values can be added
pot=np.zeros((len(x),len(y)))
#initiallize indexes in order to be able to work in a loop, this indexes will be related to the matrix positions
i=0
j=0
#use a double loop to calculate the potential and then add it to the corresponding position in the pot matrix
for xi in x:
    
    for yj in y:
        pot[i,j]=carga_1.potencial(xi,yj)+carga_2.potencial(xi,yj)+carga_3.potencial(xi,yj)+carga_4.potencial(xi,yj)
        j+=1
    j=0
    i+=1
#now a gradient calculation is needed, as a recomendation given by Alfredo Ricci np.roll() should be useful to calculate the central differences in the matrices
#here, the separations in x and y are the same
h=x[1]-x[0]
#to know how np.roll() works, a search in the documentation has been made
#calculate the central difference as a difference between two rolls
roll_plus= np.roll(pot,1,axis=0)
roll_minus=np.roll(pot,-1,axis=0)
cdx=(roll_plus-roll_minus)/(2*h)
#calculate the central difference in y as a difference between two rolls
roll_1=np.roll(pot,1,axis=1)
roll_2=np.roll(pot,-1,axis=1)
cdy=(roll_1-roll_2)/(2*h)
#take the minus sign in order to define the electric field components
Ex=-cdx
Ey=-cdy
#plot the electric field following the pdf instructions 
plt.subplot2grid((1,4),(0,0))
plt.imshow(pot)
plt.subplot2grid((1,4),(0,1),colspan=3)
plt.streamplot(x,y,Ex,Ey)
plt.savefig('cargas.pdf')
