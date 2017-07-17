//packages
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
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
    double datos[10][7];
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
         if(j!=0){
             datos[i][j-1]=atof(split);
             printf("Item in line:%s\n",split);
         }
         split=strtok(NULL,delim);
         j+=1;
     }
        i+=1;
    }
}
