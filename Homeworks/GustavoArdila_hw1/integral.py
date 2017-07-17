import numpy as np
import matplotlib.pyplot as plt

#define the function to integrate
def fun(x1,x2,x3,x4,x5,x6,x7,x8,x9,x10):
    y=(x1+x2+x3+x4+x5+x6+x7+x8+x9+x10)**3
    return y


#calculations will be made following the  hands-on at metodoscomputacionales repo 
#in github and http://mathfaculty.fullerton.edu/mathews/n2003/montecarlomod.html sugestions 
#for higher dimension integration using montecarlo
#first we fix the number of generated points at 50
x1=np.linspace(0,2,1000)
x2=np.linspace(0,2,1000)
x3=np.linspace(0,2,1000)
x4=np.linspace(0,2,1000)
x5=np.linspace(0,2,1000)
x6=np.linspace(0,2,1000)
x7=np.linspace(0,2,1000)
x8=np.linspace(0,2,1000)
x9=np.linspace(0,2,1000)
x10=np.linspace(0,2,1000)



#checks for the maximum value of the function
value=fun(x1,x2,x3,x4,x5,x6,x7,x8,x9,x10)
maximum=np.amax(value)


#checks for the integral limits, note that they are the same for the 10 variables
maxvar=max(x1)




#we have 10 variables so we need to generate random numbers between the same interval to every variable
x1_rand=np.random.random(1000)*maxvar
x2_rand=np.random.random(1000)*maxvar
x3_rand=np.random.random(1000)*maxvar
x4_rand=np.random.random(1000)*maxvar
x5_rand=np.random.random(1000)*maxvar
x6_rand=np.random.random(1000)*maxvar
x7_rand=np.random.random(1000)*maxvar
x8_rand=np.random.random(1000)*maxvar
x9_rand=np.random.random(1000)*maxvar
x10_rand=np.random.random(1000)*maxvar
x_check_rand=np.random.random(1000)*maximum




#evaluate the function in the random variables and takes de difference with the check, method based in the hands on
delta= fun(x1_rand,x2_rand,x3_rand,x4_rand,x5_rand,x6_rand,x7_rand,x8_rand,x9_rand,x10_rand)- x_check_rand



#checks for the number of points below the curve
below=np.where(delta>0.0)



#generates the integral interval
interval=(max(x1))*maximum




#evaluates the integral
integral=interval*(np.size(below))


# In[11]:

#now let's calculate the integral using mean value
def promedio(n):
    
    lista=[]
    for i in range(20):
        x1_rand=np.random.random(n)*maxvar
        x2_rand=np.random.random(n)*maxvar
        x3_rand=np.random.random(n)*maxvar
        x4_rand=np.random.random(n)*maxvar
        x5_rand=np.random.random(n)*maxvar
        x6_rand=np.random.random(n)*maxvar
        x7_rand=np.random.random(n)*maxvar
        x8_rand=np.random.random(n)*maxvar
        x9_rand=np.random.random(n)*maxvar
        x10_rand=np.random.random(n)*maxvar
        x_check_rand=np.random.random(n)*maximum
        delta= fun(x1_rand,x2_rand,x3_rand,x4_rand,x5_rand,x6_rand,x7_rand,x8_rand,x9_rand,x10_rand)- x_check_rand
        below=np.where(delta>0.0)
        interval=(max(x1))*maximum
        integral=interval*(np.size(below)/(1.0*np.size(x_check_rand)))
        lista.append(integral)
        #y=fun(x_1,x_2,x_3,x_4,x_5,x_6,x_7,x_8,x_9,x_10)
        #yav=np.average(y)
        #lista.append(yav)
    prom=np.array(lista)
    tot_1=np.mean(prom)
    total=tot_1/2
    
    return (total)




#now let's vary the number of points
#create array of powers of 2
#for each point calculates the function
#save values in list
n_1=[2,2**2,2**3,2**4,2**5,2**6,2**7,2**8,2**9,2**10,2**11,2**12,2**13]
n=np.array(n_1)
gr=[]
for ni in n:
    gr.append(promedio(ni))
plt.plot(n,gr)
plt.savefig('num_integral.pdf')
plt.close()


#calculations corresponding to the analytical integral were made using mathematica
realval=1126400.0
reallist=[realval,realval,realval,realval,realval,realval,realval,realval,realval,realval,realval,realval,realval]
real=np.array(reallist)


# In[14]:

#now we create an array of the differences
dif=abs(real-gr)/real




#creates the sqrt n array
sqrtn=np.sqrt(n)


# In[17]:

#plots
plt.plot((1/sqrtn),dif)
#
plt.savefig('err_integral.pdf')


# In[ ]:



