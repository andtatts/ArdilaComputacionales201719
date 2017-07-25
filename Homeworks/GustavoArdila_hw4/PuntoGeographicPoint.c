#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
//number of rows and columns as global constants
#define rows 500
#define cols 744
//creates a pointer in order to create the matrix
double **data;
//creates a function to read the file in order to make the main as simple as possible
void read_file(){
    FILE *file;
    file=fopen("map_data.txt","r");
    const char *delim;
    delim=",";
    char *split;
    char line_buffer[800];
    int i;
    int j;
    while(fgets(line_buffer, sizeof(line_buffer),file)){
        split=strtok(line_buffer,delim);
        while(split!=NULL){
            data[i][j]=atof(split);
            split=strtok(NULL,delim);
            j+=1;
        }
        j=0;
        i+=1;
    }
    
}
int main(){
    read_file();
    return 0;
}