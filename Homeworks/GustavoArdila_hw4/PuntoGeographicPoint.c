#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
//number of rows and columns as global constants
#define rows 500
#define cols 744
#define pi 3.1415926535
//creates a pointer in order to create the matrix
int **data;
//creates a function to read the file in order to make the main as simple as possible
void initial(){
    int i;
    data=malloc(rows*sizeof(int *));
    for(i=0;i<rows;i++){
        data[i]=malloc(cols*sizeof(int *));
    }
}
void read_file(){
    FILE *file;
    file=fopen("map_data.txt","r");
    const char *delim;
    delim=" ";
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
//metropolis hastings to be implemented for the area
double area(int x0, int y0){
    int x=x0;
    int y=y0;
    int r=0;
    double area;
    //checks if the circle surpasses the box, idea from Santiago Salazar
    while(data[x+r][y]!=1&& data[x-r][y]!=1 && data[x][y+r]!=1 && data[x][y-r]!=1){
    if(y+r>= cols-1){
         y=0;
     }  
    if(y-r<0){
        y=cols-1;
    }
    if(x-r<0){
        break;
    }
    if(x+r>=rows-1){
        break;
    }
    
    r+=1;
    }
    area=pi*pow(r,2);
    return area;
}
int main(){
    initial();
    read_file();
    return 0;
}