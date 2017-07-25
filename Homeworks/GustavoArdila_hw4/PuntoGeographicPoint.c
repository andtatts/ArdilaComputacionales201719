#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
//number of rows and columns as global constants
#define rows 500
#define cols 744
#define pi 3.1415926535
#define iterations 380000
//creates a pointer in order to create the matrix
int **data;
//test variables
float tstx;
float tsty;
float tsta;
//variables from the initial step
float c_x;
float c_y;
float c_a;
//M-H variabñes
float alpha;
float beta;
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
    char line_buffer[1200];
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
// generates random numbers from normal distribution, based on https://rosettacode.org/wiki/Statistics/Normal_distribution#C
double random_normal(int mu){
    double sigma=1.0;
    double x1,x;
    double y1,y;
    double z;
    double p;
    x=2.0*rand()/RAND_MAX -1.0;
    y=2.0*rand()/RAND_MAX -1.0;
    z=pow(x,2)+pow(y,2);
    while(z>=1.0||z==0.0){
        p=sqrt(-2.0*log(z)/z);
        x=p*x1;
        y=p*y1;
    }
   double m=mu+sigma*x;
    return m;
}
//tried implementing MH algorithm in a function but got confused so will implemeted in the main function
int main(){
    initial();
    read_file();
    /*
    Metropolis Hastings:
    Take an initial step within the box, dont include the 0th 
    */
    c_x=(int)(rows-2)*rand()/RAND_MAX;
    c_y=(int)(cols-1)*rand()/RAND_MAX;
    //calculate the area
    c_a=area(c_x,c_y);
    //iterates using metropolis hastings algorithm
    int k;
    //creates a counter to count the number of zeros in the circle
    int count=0;
    for(k=0;k<iterations;k++){
        counter+=1;
        tstx= (int)random_normal(c_x);
        tsty= (int)random(c_y);
        tsta= area(tstx,tsty);
        
    }
    return 0;
}