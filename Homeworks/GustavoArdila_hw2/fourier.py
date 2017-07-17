
# coding: utf-8

# In[1]:

#problem solution requires to use wavfile from scipy according to the pdf
import numpy as np
import matplotlib.pyplot as plt
from scipy.io import wavfile as wv
from scipy.fftpack import *


# In[2]:

#read the wav file and gives sample rate and the signal converted to a numpy array
rate,data=wv.read('Do.wav')


# In[3]:

#as the sample rate is known the discrete fourier transform can be implemented
# searching for a range of high frequencies is needed, so first  a plot of the data was made, after that, it can be seen that the maximum frequency is 50KHz    
#implementation of the fourier transform is based on a suggestion from Veronica.


# In[4]:

#dt or h is defined as 1/s where s is the sample rate
dt=1.0/rate
#we have 49600 points
N=49600
#creates the space of k's
k=np.linspace(0,(N-1),N)


# In[5]:

#makes the loops and calculates the fourier transform
value=np.zeros(np.size(data),dtype=complex)
for n in range(N):
    exponente=np.exp(-2*1j*np.pi*n/N)
    kernel=exponente**k
    valor=kernel*data
    value[n]=np.sum(valor)


# In[6]:

#after getting the fourier transform the frequencies are needed, they are calculated using the documentation of fftpack.fftfreq
mag=abs(value)
f=np.linspace(0,(N/2)-1,N/2)
g=np.linspace(-N/2,-1,N/2)
h=np.concatenate((f,g))/(N*dt)


# In[38]:

value_1=np.copy(value)
mag_1=np.copy(mag)
mag2=np.copy(mag)
def del_higher():
    for i in range(0,np.size(mag)):
        if mag[i]>=200000.0:
            mag_1[i]=0.0
            value_1[i]=complex(0.0,0.0)
del_higher()
data2=ifft(value_1)
data2=np.real(data2)
wv.write('Do_pico.wav',rate,data2)


# In[37]:

value2=np.copy(value)
def low_pass(x):
    for i in range(0,np.size(mag)):
        if x[i]>1000.0:
            mag2[i]=0.0
            value2[i]=complex(0.0,0.0)
        elif x[i]<-1000.0:
            mag2[i]=0.0
            value2[i]=complex(0.0,0.0)
low_pass(h)
data3=ifft(value2)
data3=np.real(data3)
wv.write('Do_pasabajos.wav',rate,data3)


# In[18]:

#in order to change the note, a ratio  between the G frequency and the C one must be found, this will give the change of the frequencies and the sample rate 
quo=391.0/260.0
frec_cg=np.copy(h)
frec_cg=frec_cg*quo
#a normalization of data is needed


# In[19]:

#get the inverse fourier transform and creates the audio with the new sample rate
do_sol=ifft(value)
real=np.real(do_sol)
new_rate=rate*quo
wv.write('Do_Sol.wav',new_rate,real)


# In[27]:

#plots
plt.figure(1)
plt.subplot(3,1,1)
plt.plot(data)
plt.title('Original')
plt.tight_layout()

plt.subplot(3,1,2)
plt.plot(data2)
plt.title('Filtro 1')
plt.tight_layout()
plt.xlim(0,10000)

plt.subplot(3,1,3)
plt.plot(data3)
plt.title('Pasa Bajas')
plt.xlim(0,10000)
plt.tight_layout()

plt.savefig('DoFiltros.pdf')


# In[36]:

rg,datasol=wv.read('Sol.wav')
datasol=fft(datasol)
datasol=ifft(datasol)
datasol=np.real(datasol)

plt.figure(2)
plt.plot(datasol)
plt.plot(real)
plt.savefig('DoSol.pdf')


# In[ ]:



