#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>
//number of rows and columns as global constants
#define rows 500
#define cols 744
#define pi 3.1415926535
#define iterations 372000
//creates a pointer in order to create the matrix
int **data;
//int *data[rows];
//test variables
/*
float tstx;
float tsty;
float tsta;*/
int tstx;
int tsty;
double tsta;
//variables from the initial step
/*
float c_x;
float c_y;
float c_a;*/
int c_x;
int c_y;
double c_a;
//M-H variabñes
float alpha;
float beta;
//creates a function to read the file in order to make the main as simple as possible
void initial(){
    alpha=0;
    beta=0;
    c_a=0;
    int i;
    data=malloc(cols*sizeof(int *));
    for(i=0;i<cols;i++){
        data[i]=malloc(rows*sizeof(int));
        //data[i]=(int *)malloc(cols*sizeof(int));
    }
    
}
void read_file(){
    FILE *file;
    file=fopen("map_data.txt","r");
    if(file==NULL){
        printf("paila\n");
    }
    const char *delim;
    delim=" ";
    char *split;
    char line_buffer[1800];
    int i=0;
    int j=0;
    while(fgets(line_buffer, sizeof(line_buffer),file)!=NULL){
        split=strtok(line_buffer,delim);
        while(split!=NULL){
            data[i][j]=atof(split);
            split=strtok(NULL,delim);
            j+=1;
        }
        j=0;
        i+=1;
    }
    fclose(file);
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
    if(y-r<=0){
        y=cols-1;
    }
    if(x-r<=0){
        break;
    }
    if(x+r>=rows-1){
        break;
    }
    
    r+=1;
    //printf("%d %d %d %d %d \n",x+r,x-r,y+r,y-r,r);
        
    }
    area=pi*pow(r,2);
    
    return area;
}
// generates random numbers from normal distribution, based on and https://phoxis.org/2013/05/04/generating-random-numbers-from-normal-distribution-in-c/
/*double random_normal(int mu){
    double sigma=1.0;
    double x1,x;
    double y1,y;
    double z;
    double p;
    x1=2.0*(double)rand()/RAND_MAX -1.0;
    y1=2.0*(double)rand()/RAND_MAX -1.0;
    z=pow(x,2)+pow(y,2);
    while(z>=1.0||z==0.0){
        x1=2.0*(double)rand()/RAND_MAX -1.0;
        y1=2.0*(double)rand()/RAND_MAX -1.0;
        z=pow(x1,2)+pow(y1,2);
       
    }
    p=sqrt(-2.0*log(z)/z);
    x=x1*p;
   double m=mu+sigma*x;
    return m;
}*/
//tried implementing MH algorithm in a function but got confused so will implemeted in the main function
int main(){
    initial();
    read_file();
    
    printf("wiiii\n");
    int c_xp=500;
    int c_yp=744;
    /*
    Metropolis Hastings:
    Take an initial step within the box, dont include the 0th because it's the 0th col or row
    */
    //SEEDS
    srand(time(NULL));
    srand48(time(NULL));
    c_x=(int)(rows-1)*(double)rand()/RAND_MAX;
    c_y=(int)(cols-1)*(double)rand()/RAND_MAX;
    printf("%d %d \n", c_x,c_y);
    //checks if the random numbers are different to 1
    //if(data[c_x][c_y]==1){
    while(data[c_x][c_y]==1){
        c_x=(int)(rows-2)*(double)rand()/RAND_MAX;
        c_y=(int)(cols-1)*(double)rand()/RAND_MAX;
        //printf("%d %d ",c_x,c_y);
    }
    //calculate the area
    c_a=area(c_x,c_y);
    //printf("ola\n");
    //iterates using metropolis hastings algorithm
    int k;
    //creates a counter to count the number of zeros in the circle
    int rad=0;
    for(k=0;k<iterations;k++){
        rad+=1;
        //tstx= (int)random_normal(c_x);
        //tsty= (int)random_normal(c_y);
        tstx=(rows-1)*drand48();
        tsty=(cols-1)*drand48();
        //printf("%d %d",tstx,tsty);
        tsta= area(tstx,tsty);
        //checks the condition of non producing a 1 or being out of bounds
        while(data[tstx][tsty]==1||tstx+1>rows||tsty+1>cols|| tstx<0||tsty<0){
             //tstx= (int)random_normal(c_x);
             //tsty= (int)random_normal(c_y);
             tstx=(rows-1)*drand48();
            tsty=(cols-1)*drand48();
            //printf("%d %d",tstx,tsty);
        }
        //gets the area of the test point
        tsta=area(tstx,tsty);
        //printf("ola\n");
        //calculates the alpha from MH
        alpha=tsta/c_a;
        //checks the condition on alpha
        if(alpha>1){
            c_x=tstx;
            c_y=tsty;
            c_a=tsta;
        }
        //if not followed check beta
        else{
            //where is it centered?
            //beta=(double) rand()/RAND_MAX;
            beta=(double)drand48();
            if(beta<alpha){
                c_x=tstx;
                c_y=tsty;
                c_a=tsta;
            }
            else{
                c_x=c_x;
                c_y=c_y;
                c_a=c_a;
            }
        }
        if(data[c_x][c_y]==1){
            continue;
        }
        
       
        
    }
    printf("%d %d %d \n",c_x,c_y,rad);
    FILE *coordinates;
    coordinates= fopen("coordinates.txt","w+");
    fprintf(coordinates,"%d %d %d \n",c_x,c_y,rad);
    fclose(coordinates);
    
    return 0;
}