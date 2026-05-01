#include"Shape.h"
#include<string>

Shape:: Shape(int type){
    size = 3;
    matrix = new int[size * size];
    for(int i = 0;i < size*size;i++)
    {
        matrix[i] = 0;
    }

    if(type==0){
        matrix[0] = 1;
        matrix[1] = 1;
        matrix[3] = 1;
        matrix[4] = 1;

    }
    else if (type==1){
       
            matrix[0]=1;
            matrix [1]=1;
            matrix[2]=1;

    }
    else if(type==2){
      
       matrix[1]=1;
       matrix[3]=1;
       matrix[4]=1;
       matrix[5]=1;
    }
    
    else if(type==3){
       
        matrix[2]=1;
        matrix[3]=1;
        matrix[4]=1;
        matrix[5]=1;

    }
    else if (type==4){
        matrix[0]=1;
        matrix[3]=1;
        matrix[4]=1;
        matrix[5]=1;
        
    }
    else if(type==5){
        matrix[1]=1;
        matrix[2]=1;
        matrix[3]=1;
        matrix[4]=1;
    }
    else if (type==6){
        matrix[0]=1;
        matrix[1]=1;
        matrix[4]=1;
        matrix[5]=1;
    
    }
}

//destructor
Shape:: ~Shape(){
    delete []matrix;
}
//right rotation
void Shape:: rotateRight(){
    int* rotated = new int[size*size];
    for(int i=0;i<size;i++){  //i =row
        for(int j=0;j<size;j++){ //j = column
            rotated[(j*size)+(size-1-i)]=matrix[(i*size)+j];

        }
    }
    delete [] matrix;
    matrix=rotated;
}
//left rotation
void Shape:: rotateLeft(){
    int* rotated =new int [size*size];
    for(int i=0;i<size;i++){ //i = rows
        for (int j=0;j<size;j++){ // j=column
            rotated[(size-1-j)* size +i]=matrix[(i*size)+j];

        }
    }
    delete [] matrix;
    matrix =rotated;
}
//getters
int Shape:: getPixel(int x,int y) const{
    if(x>=0 && x< size && y>=0 && y<size ){
        return matrix[y*size+x];
    }
    return 0;
   
}
int Shape:: getSize() const {
    return size;
}
