//packages
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
//define the number of iterations
#define ITERATIONS 1000
//define the number of planets given in the csv
#define NP 10
//initiallize the matrix, a double matrix was created as suggestion from Santiago Salazar
double datos[10][8];
double datos_true[10][7];

//initiallize counters for rows and columns
int i=0;
int j=0;
//now define the constants used in the functions

//time interval between consecutive points
double dt;


//Universal G constant
double G;
//masses
double mass[NP];
//function of the initial conditions
void initial_conditions();
//function that creates the files
void create_txt();
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
double x[NP][ITERATIONS];
double y[NP][ITERATIONS];
double z[NP][ITERATIONS];
double vx[NP][ITERATIONS];
double vy[NP][ITERATIONS];
double vz[NP][ITERATIONS];
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
    //sun's mass
    double sol;
    sol=datos_true[0][0];
    //change of units in the mass
    for(i=0;i<10;i++){
        datos_true[i][0]=datos_true[i][0]/sol;
    }
    //initialize the conditions
    initial_conditions();
    /*
    funcion a usar es la eq de movimiento para cada planeta
    
    create a matrix for each variable, i is planet, j is the time :x,y,z,vx,vy,vz
    intermediate velocities create just three arrays 
    
    create a function for calculating the velocity this will make the sum for x,y and z
    */
     /*
        according to wikipedia's article on leapfrog the velocity can be calculated as
        v_(i+1)=v_i+0.5*(a_i+a_(i+1))*dt
        where i is the time 
    */
    //need to loop over the whole planets
    
    int p;
    int q;
    /*
        according to the same wikipedia article the position can be calculated as
        x_(i+1)=x_i+v_i*dt+0.5*a_i*dt^2
        here i means also time
    */
    for(p=0;p<ITERATIONS-1;p++){
        for(q=0;q<NP;q++){
            x[q][p+1]=x[q][p]+vx[q][p]*dt+0.5*acc_x(q,p)*pow(dt,2.0);
            y[q][p+1]=y[q][p]+vy[q][p]*dt+0.5*acc_y(q,p)*pow(dt,2.0);
            z[q][p+1]=z[q][p]+vz[q][p]*dt+0.5*acc_z(q,p)*pow(dt,2.0);
        }
    }
   
    for(p=0;p<ITERATIONS-1;p++){
        for(q=0;q<NP;q++){
            //adds the data to a new column of the matrix
            vx[q][p+1]=vx[q][p]+0.5*(acc_x(q,p)+acc_x(q,p+1))*dt;
            vy[q][p+1]=vy[q][p]+0.5*(acc_y(q,p)+acc_y(q,p+1))*dt;
            vz[q][p+1]=vz[q][p]+0.5*dt*(acc_z(q,p)+acc_z(q,p+1));
            
        }
    
    }
   
    
    //creates the files
    create_txt();
    //finally after a week of blood and tears the code is finished, thank you R'hollor.
}
void initial_conditions(){
    //sets the time interval
    dt=0.0003;
    //universal constant value, Juan suggested on monday to use 4*pi^2
    G=4*pow(3.141592,2);
    //sets a counter
    int a;
    
    //fills the matrices
    for(a=0;a<NP;a++){
        //gets the mass as an array
        mass[a]=datos_true[a][0];
        
        
        //sets the first column of the matrices as the initial condition, suggestion from Juan given on monday
        x[a][0]=datos_true[a][1];
        y[a][0]=datos_true[a][2];
        z[a][0]=datos_true[a][3];
        vx[a][0]=datos_true[a][4];
        vy[a][0]=datos_true[a][5];
        vz[a][0]=datos_true[a][6];
        
    }
}
double acc_x(int planeta, int t){
    //has to loop over all planets except itself
    int p;
    double d;
    double m;
    double ax=0;
    for(p=0;p<NP;p++){
        //sets the condition over not calculating its own acceleration
        if(p==planeta){
            //searching in the documentation, continue is used to ignore a part in the loop
            continue;
        }
    //calculates the distance, the square root will be implemented using the sqrt function from math.h
        d=sqrt(pow(x[p][t]-x[planeta][t],2)+pow(y[p][t]-y[planeta][t],2)+pow(z[p][t]-z[planeta][t],2));
    //gets the mass
        m=mass[p];
        ax+=G*(m/pow(d,3))*(x[p][t]-x[planeta][t]);
    
    }
    
    return ax;
    
}
//printf(" the acceleration is %f",acc_x(0,1));
double acc_y(int planeta, int t){
    int p;
    double d;
    double m;
    double ay=0;
    for(p=0;p<NP;p++){
        //sets the condition over not calculating its own acceleration
        if(p==planeta){
            //searching in the documentation, continue is used to ignore a part in the loop
            continue;
        }
    //calculates the distance, the square root will be implemented using the sqrt function from math.h
        d=sqrt(pow(x[p][t]-x[planeta][t],2)+pow(y[p][t]-y[planeta][t],2)+pow(z[p][t]-z[planeta][t],2));
    //gets the mass
        m=mass[p];
        ay+=G*(m/pow(d,3))*(y[p][t]-y[planeta][t]);
    
    }
    return ay;
    
}
double acc_z(int planeta, int t){
    int p;
    double d;
    double m;
    double az=0;
    for(p=0;p<NP;p++){
        //sets the condition over not calculating its own acceleration
        if(p==planeta){
            //searching in the documentation, continue is used to ignore a part in the loop
            continue;
        }
    //calculates the distance, the square root will be implemented using the sqrt function from math.h
        d=sqrt(pow(x[p][t]-x[planeta][t],2)+pow(y[p][t]-y[planeta][t],2)+pow(z[p][t]-z[planeta][t],2));
    //gets the mass
        m=mass[p];
        az+=G*(m/pow(d,3))*(z[p][t]-z[planeta][t]);
    
    }
    return az;
}
void create_txt(){
    //searching in tutorial points it can be seen that a file would be written when using fopen function
    //creates the pointers for each file
    //only position data will be saved
    FILE *solx;
    FILE *soly;
    FILE *solz;
    //opens the txt files, saves the data and also reads it using the "w+" parameter
    solx=fopen("datos_x.txt","w+");
    soly=fopen("datos_y.txt","w+");
    solz=fopen("datos_z.txt","w+");
    //saves the data printing it in the file using fprintf looping over all the cols  and then closes it
    int i;
    for( i=0;i<ITERATIONS;i++){
        fprintf(solx, "%f %f %f %f %f %f %f %f %f %f \n", x[0][i], x[1][i], x[2][i], x[3][i], x[4][i], x[5][i], x[6][i], x[7][i], x[8][i], x[9][i]);
    }
    for( i=0;i<ITERATIONS;i++){
        fprintf(soly, "%f %f %f %f %f %f %f %f %f %f \n", y[0][i], y[1][i], y[2][i], y[3][i], y[4][i], y[5][i], y[6][i], y[7][i], y[8][i], y[9][i]);
    }
    
    for(i=0;i<ITERATIONS;i++){
        fprintf(solz, "%f %f %f %f %f %f %f %f %f %f \n", z[0][i], z[1][i], z[2][i], z[3][i], z[4][i], z[5][i], z[6][i], z[7][i], z[8][i], z[9][i]);
}
    fclose(solx);
    fclose(soly);
    fclose(solz);
}
//double v_x(int planeta, int t){
    /*
        according to wikipedia's article on leapfrog the velocity can be calculated as
        v_(i+1)=v_i+0.5*(a_i+a_(i+1))*dt
        where i is the time step
    */
    //need to loop over the whole planets
    //int p;
    //for(p=0;p<np;p++){
      //  vx[p][]
    //}
    //tried setting it as a function but got confused so I worked it on the main function
//}