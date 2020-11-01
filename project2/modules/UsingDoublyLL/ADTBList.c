///////////////////////////////////////////////////////////
//
// Υλοποίηση του ADT BList μέσω διπλά συνδεδεμένης λίστας.
//
///////////////////////////////////////////////////////////

#include <stdlib.h>
#include <assert.h>

#include "common_types.h"
#include "ADTBList.h"

// Blist is a pointer to struct blist
struct blist {
	BListNode dummy; //pointer to the last element of a list
	BListNode first; //first element of the struct
	int size;
	DestroyFunc destroy;
};

// BlistNode is a pointer to struct blist_node
struct blist_node {
	BListNode next;
	BListNode prev;
	Pointer value;
};


BList blist_create(DestroyFunc destroy_value) {
	BList blist = malloc(sizeof(*blist)); //malloc the necesary memory 
	blist->size = 0; //the struct is empty
	blist->destroy = destroy_value; //set destroy as the destroy value given

	blist->dummy = malloc(sizeof(*blist->dummy)); //malloc the dummy node
	blist->dummy->prev = NULL; //both next and previous of dummy is NULL
	blist->dummy->next = NULL;

	blist->first=blist->dummy; //empty struct->first=dummy

	return blist;
}

int blist_size(BList blist) {
	return blist->size;
}

void blist_insert(BList blist, BListNode node, Pointer value) {
	if (node == NULL) //if node = BLIST_EOF or BLIST_BOF
		node = blist->dummy; //node is a pointer to the last element of the list

	BListNode new = malloc(sizeof(*new)); //create a new node
	new->value = value;	//set his value as th given 

	new->prev = node->prev; //connect the new node with the rest of the struct
	new->next = node;
	node->prev = new;

	blist->size++; //increase its size 
	if (blist->dummy->prev == node){
		blist->dummy->prev = new;
	}
}

void blist_remove(BList blist, BListNode node) {
	if(node==NULL) 
		node=blist->dummy->prev; //the last element of the list
	
	BListNode removed = node; 
	if(removed!=blist_last(blist)){ //if node is different than the last element of the list
		removed->prev->next = removed->next; //connect it by this way with the rest of the blist
	}
	else{
		blist->dummy->prev=removed->prev; 
	}

	if (blist->destroy != NULL) //free the allocated memory
		blist->destroy (removed->value);
	free(removed);

	blist->size--; //change the size
	if (blist->first == node){
		blist->first = node->next;
	}
}

Pointer blist_find(BList blist, Pointer value, CompareFunc compare) {
	BListNode node = blist_find_node(blist, value, compare);
	return node == NULL ? NULL : node->value;
}

DestroyFunc blist_set_destroy_value(BList blist, DestroyFunc destroy_value) {
	DestroyFunc old = blist->destroy;
	blist->destroy = destroy_value;
	return old;
}

void blist_destroy(BList blist) {
	BListNode node = blist->dummy->prev; //beggining from the end cross the blist and free every node
	while (node != NULL) {				
		BListNode prev = node->prev;	
		if (node != blist->dummy && blist->destroy != NULL)
			blist->destroy(node->value);
		free(node);
		node = prev;
	}
	free(blist->first); //free the first node
	free(blist); //free the struct itself
}


BListNode blist_first(BList blist) {
	assert(blist->first!=NULL);
	return blist->first;
}

BListNode blist_last(BList blist) {
	assert(blist->dummy->prev!=NULL);
	return blist->dummy->prev;
}

BListNode blist_next(BList blist, BListNode node) {
	assert(node!=NULL);
	return node->next;
}

BListNode blist_previous(BList blist, BListNode node) {
	assert(node!=NULL);
	return node->prev;
}

Pointer blist_node_value(BList blist, BListNode node) {
	if(node!=NULL)
		return node->value;
	return NULL;
}

BListNode blist_find_node(BList blist, Pointer value, CompareFunc compare) {
	for (BListNode node = blist->dummy->prev; node != NULL; node = node->prev){
		if (compare(value, node->value) == 0)
			return node;
	}
	return NULL;
}