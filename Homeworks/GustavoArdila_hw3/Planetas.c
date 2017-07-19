//packages
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
int main (void){
    //reads the file and saves data to a matrix
    //creates a pointer in order to save the csv data
    FILE *file;
    //opens the file and reads it
    file=fopen("coordinates.csv","r");
    // sets a maximun length for the elements
    int length=500;
    //creates a char array to read the data lines
    char line_read[length];
    //creates a pointer to save the splitted data
    char *split;
    //as a suggestion from Juan, initiallize a delimiter as a constant character pointer
    const char *delim;
    delim=",";
    //initiallize the matrix
    double **datos;
    //initiallize counters for rows and columns
    int i=0;
    int j=0;
    //read a line and saves it 
    while(fgets(line_read, length, file)){
        //prints the line info
        printf("Line is: %s", line_read);
        //splits the data by ","
        split=strtok(line_read,delim);
     while(split!=NULL){
         
         datos[i][j-1]=atof(split);
         printf("Item in line:%s\n",split);
         split=strtok(NULL,delim);
         j+=1;
         
         
         
     }
        j=0;
        i+=1;
        
        for(i=0;i<10;i++){
		for(j=0;j<7;j++){
      			datos_true[i][j]=datos[i][j+1];
      }

     }
   
    }
    printf("masa:%e\n",datos[9][1]);
    /*
    funcion a usar es la eq de movimiento para cada planeta
    
    create a matrix for each variable, i is planet, j is the time :x,y,z,vx,vy,vz
    intermediate velocities create just three arrays 
    
    create a function for calculating the velocity this will make the sum for x,y and z
    */
    
}
