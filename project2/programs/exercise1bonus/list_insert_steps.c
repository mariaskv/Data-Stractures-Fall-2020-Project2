#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "ADTList.h"

int* create_int(int value) { //function that create ints so to be inserted at the listtor
	int* p = malloc(sizeof(int));
	*p = value;
	return p;
}

int main(int argc, char*argv[]){
    if(strcmp(argv[1],"real")==0){ 
        List list = list_create(free); //create an empty listtor
        for(int i=1; i<=10000; i++){
            list_insert_next(list,list_last(list),create_int(i)); //insert the new element
            printf("%d,%d\n", i,list_steps(list)); //print the steps that have been done
        }
        list_destroy(list); //destroy the list
    }
    else if(strcmp(argv[1],"amortized")==0){
    List list1  = list_create(free); //create an empty listtor
    int count = 0; //steps counter
        for(int i=1; i<=10000; i++){
            list_insert_next(list1,list_last(list1),create_int(i)); //insert the new element
            count+=list_steps(list1); //calculation of 
            double aver = (float)count/i; //amortized time
            printf("%d,%f\n",i, aver); //print the amortized time
        }
        list_destroy(list1); //destroy the list
    }
    return 0;
}