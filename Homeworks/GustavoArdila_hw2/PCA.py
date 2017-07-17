#problem will be solved using pandas
import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

#reads the csv as a pandas data frame
dataframe=pd.read_csv('DatosBancoMundial5.csv')

#delete the string columns
dataframe=dataframe.drop('Time', axis=1)
dataframe=dataframe.drop('Time Code',axis=1)
dataframe=dataframe.drop('Series Name',axis=1)
dataframe=dataframe.drop('Series Code',axis=1)

#turns data to numeric values
data=dataframe.apply(pd.to_numeric)

#turns data to a matrix, each array corresponds to a row of the csv
data_matrix=data.as_matrix()

#normalize data: (data- mean)/std 
filas= np.size(data_matrix,0)
data_norm=np.zeros((np.size(data_matrix,0),np.size(data_matrix,1)))
for i in range(filas):
    mean=np.mean(data_matrix[i,:])
    std=np.std(data_matrix[i,:])
    data_norm[i,:]=(data_matrix[i,:]-mean)/std

#plots using subplot command
plt.figure(1)
plt.subplot(5,1,1)
plt.plot(data_norm[0,:])
plt.title(' Normalized data exploration')
plt.ylabel('T.T.Rate ')

plt.subplot(5,1,2)
plt.plot(data_norm[1,:])
plt.ylabel('Cost')

plt.subplot(5,1,3)
plt.plot(data_norm[2,:])
plt.ylabel('U.female')

plt.subplot(5,1,4)
plt.plot(data_norm[3,:])
plt.ylabel('U.male')

plt.subplot(5,1,5)
plt.plot(data_norm[4,:])
plt.ylabel('Ratio')

plt.savefig('ExploracionDatos.pdf')


#calculates the covariance matrix using the class techniques
cov=data_norm.dot(data_norm.T)/222
print cov


#calculates the eigenvalues and eigenvectors using numpy subpackage linalg
values, vectors= np.linalg.eig(cov)

#ndarray.tolist converts a numpy array into a list
print 'La primera componente principal es: ', np.ndarray.tolist(vectors[0])
print'La segunda componente principal es: ', np.ndarray.tolist(vectors[1])


#makes the projection of data to the new frame

proj= np.dot(vectors.T, data_norm)
#plots data corresponding to  pc1 vs pc2, based in the hands on example 
plt.figure(2)
plt.scatter(proj[0,:],proj[1,:])
plt.xlabel('PCA1')
plt.ylabel('PCA2')
plt.savefig('PCAdatos.pdf')
#plots
plt.figure(3)
plt.subplot(3,1,1)
plt.scatter(proj[1,:],proj[3,:])
plt.title('Correlaciones')
plt.ylabel('1 vs 3')

plt.subplot(3,1,2)
plt.scatter(proj[1,:],proj[4,:])
plt.ylabel('1vs4')

plt.subplot(3,1,3)
plt.scatter(proj[2,:],proj[0,:])
plt.ylabel('0vs2')
plt.savefig('PCAvariables.pdf')
#correlated variables are 1,3 and 4
#correlated variables are 0 and 2
print 'Las variables correlacionadas son: 0,2 y 1,3,4'

