#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "ADTVector.h"

int* create_int(int value) { //function that create ints so to be inserted at the vector
	int* p = malloc(sizeof(int));
	*p = value;
	return p;
}

int main(int argc, char*argv[]){
    if(strcmp(argv[1],"real")==0){ 
        Vector vec = vector_create(0,free); //create an empty vector
        for(int i=1; i<=10000; i++){
            vector_insert_last(vec,create_int(i)); //insert the new element
            printf("%d,%d\n", i,vector_steps(vec)); //print the steps that have been done
        }
        vector_destroy(vec); //destroy the vector
    }
    else if(strcmp(argv[1],"amortized")==0){
    Vector vec1 = vector_create(0,free); //create an empty vector
    int count = 0; //steps counter
        for(int i=1; i<=10000; i++){
            vector_insert_last(vec1,create_int(i)); //insert the new element
            count+=vector_steps(vec1); //calculation of 
            double aver = (float)count/i; //amortized time
            printf("%d,%f\n",i, aver); //print the amortized time
        }
        vector_destroy(vec1); //destroy the vector
    }
    return 0;
}