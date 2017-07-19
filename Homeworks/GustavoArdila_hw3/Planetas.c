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
double acc_x(int planeta, int tiempo);
double acc_y(int planeta, int tiempo);
double acc_z(int planeta, int tiempo);
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
        mass[k]=datos_true[k][0];
    }
}
//double acc_x(int planeta, int tiempo){
    
//}