//packages
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

//initiallize the matrix, a double matrix was created as suggestion from Santiago Salazar
double datos[10][8];
double datos_true[10][7];

//initiallize counters for rows and columns
int i=0;
int j=0;
//now define the constants used in the functions
//define the number of iterations
#define iterations 1000
//time interval between consecutive points
double dt;

//define the number of planets given in the csv
#define np 10
//Universal G constant
double G;
//masses
double mass[np];
//function of the initial conditions
void initial_conditions();
//as the force includes a summatory, as a recomendation from Juan it is better to make functions for each  component
//each acceleration correspond to a matrix where the rows are the plannets and the columns are the time
double acc_x(int planeta, int t);
double acc_y(int planeta, int t);
double acc_z(int planeta, int t);
//creates a function that uses leapfrog for calculating the velocities
double v_x(int planeta, int t);
double v_y(int planeta, int t);
double v_z(int planeta, int t);

//on monday Juan gave another suggestion, creating matrices for positions and velocities
double x[np][iterations];
double y[np][iterations];
double z[np][iterations];
double v_x[np][iterations];
double v_y[np][iterations];
double v_z[np][iterations];
//creates a pointer in order to save the csv data
FILE *file;

// sets a maximun length for the elements
//
//creates a char array to read the data lines
char line_read[500];
//creates a pointer to save the splitted data
char *split;
//as a suggestion from Juan, initiallize a delimiter as a constant character pointer
const char *delim;

int main (void){
    //starts the initial conditions
    initial_conditions();
    int length=500;
    //opens the file and reads it
    file=fopen("coordinates.csv","r");
    //sets the delimiter
    delim=",";
    //read a line and saves it 
    while(fgets(line_read, length, file)){
        //prints the line info
        printf("Line is: %s", line_read);
        //splits the data by ","
        split=strtok(line_read,delim);
     while(split!=NULL){
         //if(j!=0){
             datos[i][j]=atof(split);
             printf("Item in line:%s\n",split);
             split=strtok(NULL,delim);
         //}
         j+=1;
         
         
     }
        j=0;
        i+=1;
   
    }
 	for(i=0;i<10;i++){
		for(j=0;j<7;j++){
      			datos_true[i][j]=datos[i][j+1];
      }

     }
    printf("masa:%e\n",datos_true[1][0]);
    /*
    funcion a usar es la eq de movimiento para cada planeta
    
    create a matrix for each variable, i is planet, j is the time :x,y,z,vx,vy,vz
    intermediate velocities create just three arrays 
    
    create a function for calculating the velocity this will make the sum for x,y and z
    */
    
    
}
void initial_conditions(){
    //sets the time interval
    dt=0.03;
    //universal constant value, Juan suggested on monday to use 4*pi^2
    G=4*pow(3.14159265358979323846264,2.0);
    //sets a counter
    int a;
    //fills the matrices
    for(a=0;a<np;a++){
        //gets the mass as an array
        mass[k]=datos_true[k][0];
        //sets the first column of the matrices as the initial condition, suggestion from Juan given on monday
        x[k][0]=datos_true[k][1];
        y[k][0]=datos_true[k][2];
        z[k][0]=datos_true[k][3];
        vx[k][0]=datos_true[k][4];
        vy[k][0]=datos_true[k][5];
        vz[k][0]=datos_true[k][6];
        
    }
}
double acc_x(int planeta, int t){
    //has to loop over all planets except itself
    int p;
    for(p=0;p<np;p++){
        //sets the condition over not calculating its own acceleration
        if(p==planeta){
            //searching in the documentation, continue is used to ignore a part in the loop
            continue;
        }
    //calculates the distance, the square root will be implemented using the sqrt function from math.h
        d=sqrt(pow(x[p][t]-x[planeta][t],2.0)+pow(y[p][t]-y[planeta][t])+pow(z[p][t]-z[planeta][t]));
    //gets the mass
        m=mass[p];
        ax+=G*(m/pow(d,3.0))*(x[p][t]-x[planeta][t]);
    
    }
    return ax;
}
double acc_y(int planeta, int t){
    int p;
    for(p=0;p<np;p++){
        //sets the condition over not calculating its own acceleration
        if(p==planeta){
            //searching in the documentation, continue is used to ignore a part in the loop
            continue;
        }
    //calculates the distance, the square root will be implemented using the sqrt function from math.h
        d=sqrt(pow(x[p][t]-x[planeta][t],2.0)+pow(y[p][t]-y[planeta][t])+pow(z[p][t]-z[planeta][t]));
    //gets the mass
        m=mass[p];
        ay+=G*(m/pow(d,3.0))*(y[p][t]-y[planeta][t]);
    
    }
    return ay;
    
}
double acc_z(int planeta, int t){
    int p;
    for(p=0;p<np;p++){
        //sets the condition over not calculating its own acceleration
        if(p==planeta){
            //searching in the documentation, continue is used to ignore a part in the loop
            continue;
        }
    //calculates the distance, the square root will be implemented using the sqrt function from math.h
        d=sqrt(pow(x[p][t]-x[planeta][t],2.0)+pow(y[p][t]-y[planeta][t])+pow(z[p][t]-z[planeta][t]));
    //gets the mass
        m=mass[p];
        az+=G*(m/pow(d,3.0))*(z[p][t]-z[planeta][t]);
    
    }
    return az;
}
double v_x(int planeta, int t){
    /*
        according to wikipedia's article on leapfrog the velocity can be calculated as
        v_(i+1)=v_i+0.5*(a_i+a_(i+1))*dt
        where i is the time step
    */
    //need to loop over the whole planets
    
}