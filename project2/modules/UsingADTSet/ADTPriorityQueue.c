#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#include "ADTPriorityQueue.h"
#include "ADTVector.h"
#include "ADTSet.h"

struct priority_queue{
    Set set;
    CompareFunc compare;
    DestroyFunc destroy_value;
};

struct priority_queue_node{
    Pointer value;
	PriorityQueue owner;
};

typedef struct priority_queue_node* PriorityQueueNode;

static int compare_priority_queue_nodes(PriorityQueueNode a, PriorityQueueNode b) {  //compare function for the pqnodes(uses the given compare)
	return a->owner->compare(a->value, b->value);
}

static void destroy_priority_queue_node(PriorityQueueNode node) { //destroy function for the pqnodes(uses the given destroy_value)

	if (node->owner->destroy_value != NULL)
		node->owner->destroy_value(node->value);

	free(node);
}

PriorityQueue pqueue_create(CompareFunc compare, DestroyFunc destroy_value, Vector values) {
	PriorityQueue pqueue = malloc(sizeof(*pqueue)); //dunamic allocates memory for the pqueue
	pqueue->compare = compare;
	pqueue->destroy_value = destroy_value;
	pqueue->set = set_create((CompareFunc)(compare_priority_queue_nodes),(DestroyFunc)(destroy_priority_queue_node));
	if (values != NULL){ //initialize the pqueue by the values of a vector
        for(int i=0;i<vector_size(values);i++){
			PriorityQueueNode node = malloc(sizeof(*node));
			node->value = vector_get_at(values,i);
			node->owner = pqueue;
		    set_insert(pqueue->set,node);
		}
    }
	return pqueue;
}

int pqueue_size(PriorityQueue pqueue) {
	return set_size(pqueue->set); //return the size of the set includes the elements of the pqueue
}

Pointer pqueue_max(PriorityQueue pqueue) {
	PriorityQueueNode node;
	node=set_node_value(pqueue->set, set_last(pqueue->set));	
	return node->value;	 //return the value of the last element of the pqueue->set
}

PriorityQueueNode pqueue_insert(PriorityQueue pqueue, Pointer value) {

	struct priority_queue_node search_node = { .value = value, .owner = pqueue};

	PriorityQueueNode node = set_find(pqueue->set, &search_node); //search if this element already exists in the pqueue
	if(node!=NULL){
		if(value!=node->value && pqueue->destroy_value!=NULL) //if already exists destroy it
			pqueue->destroy_value(node->value);
		
		node->value = value;
		return node;
	}
	node = malloc(sizeof(*node));
	node->value = value;
	node->owner = pqueue;

	set_insert(pqueue->set,node); //anfd insert it
	return node;

}

void pqueue_remove_max(PriorityQueue pqueue) {
    set_remove(pqueue->set,set_node_value(pqueue->set, set_last(pqueue->set)));	//remove the last element of the pqueue->set 
}

DestroyFunc pqueue_set_destroy_value(PriorityQueue pqueue, DestroyFunc destroy_value) {
	DestroyFunc old = pqueue->destroy_value;
	pqueue->destroy_value = destroy_value;
	return old;
}

void pqueue_destroy(PriorityQueue pqueue) {
	set_destroy(pqueue->set); //free the memory
	free(pqueue);
}

 Pointer pqueue_node_value(PriorityQueue pqueue, PriorityQueueNode node) {
	 return node->value;
 }

void pqueue_remove_node(PriorityQueue pqueue, PriorityQueueNode node) {
	struct priority_queue_node search_node = { .value=node->value, .owner=node->owner};

	PriorityQueueNode noder = set_find(pqueue->set,&search_node); //search for the element
	if(noder==NULL) //if exists return
		return;
	
	set_remove(pqueue->set,noder); //else remove it
}

void pqueue_update_order(PriorityQueue pqueue, PriorityQueueNode node) {

}