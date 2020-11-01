//////////////////////////////////////////////////////////////////
//
// Unit tests για τον ADT BList.
// Οποιαδήποτε υλοποίηση οφείλει να περνάει όλα τα tests.
//
//////////////////////////////////////////////////////////////////

#include "acutest.h"			// Απλή βιβλιοθήκη για unit testing

#include "ADTBList.h"
#include <stdio.h>

void test_create(void) {
	BList blist = blist_create(NULL);
	blist_set_destroy_value(blist, NULL);

	TEST_ASSERT(blist != NULL);
	TEST_ASSERT(blist_size(blist) == 0);

	blist_destroy(blist);
}

void test_insert(void) {
BList blist = blist_create(NULL);
	
	// Θα προσθέτουμε, μέσω της insert, δείκτες ως προς τα στοιχεία του πίνακα
	int N = 5;
	int array[N];					

	for (int i = 0; i < N; i++) {
		// LIST_BOF για εισαγωγή στην αρχή
		blist_insert(blist, BLIST_EOF, &array[i]);
		
		// Ελέγχουμε εάν ενημερώθηκε (αυξήθηκε) το μέγεθος της λίστας.
		TEST_ASSERT(blist_size(blist) == (i + 1));	

		// Ελέγχουμε εάν ο πρώτος κόμβος περιέχει σαν τιμή τον δείκτη που μόλις κάναμε insert								
		TEST_ASSERT(blist_node_value(blist, blist_last(blist)) == &array[i]);	
	}

	// Ελέγχουμε εάν τα στοιχεία έχουν μπει με την αντίστροφη σειρά
	BListNode node = blist_last(blist);

	for (int i=N-1 ; i >= 0; i--) {
		TEST_ASSERT(blist_node_value(blist, node) == &array[i]);
		node = blist_previous(blist, node);
	}

	// Εισαγωγή σε ενδιάμεσο κόμβο: προσθέτουμε το NULL σαν δεύτερο κόμβο
	BListNode first_node = blist_first(blist);
	blist_insert(blist, first_node, NULL);
	TEST_ASSERT(blist_node_value(blist, blist_next(blist, first_node)) == NULL);

	blist_destroy(blist);
}

void test_remove(void) {
BList blist = blist_create(free);
	int N = 5;
	int* array[N];
	for (int i = 0; i < N; i++) {
		array[i]  = malloc(sizeof(int));
		*array[i] = i;
		blist_insert(blist, BLIST_EOF, array[i]);
	}

	for (int i = N-1 ; i >=0 ; i--) {
		TEST_ASSERT(blist_node_value(blist, blist_last(blist)) == array[i]);
		blist_remove(blist, BLIST_EOF);
		TEST_ASSERT(blist_size(blist) == i);
	}

	for (int i = 0; i < N; i++) {
		array[i]  = malloc(sizeof(int));
		*array[i] = i;
		blist_insert(blist, BLIST_BOF, array[i]);
	}	

	blist_remove(blist, blist_last(blist));
	TEST_ASSERT(blist_size(blist) == N - 1);

	blist_destroy(blist);
}

int compare_ints(Pointer a, Pointer b) {
	return *(int*)a - *(int*)b;
}

void test_find() {
	BList blist = blist_create(NULL);
	int N = 1000;
	int array[N];

	for (int i = 0; i < N; i++) {
		array[i] = i;
		blist_insert(blist, BLIST_EOF, &array[i]);
	}

	for (int i = 0; i < N; i++) {
		int* value = blist_find(blist, &i, compare_ints); 
		TEST_ASSERT(value == &array[i]);
	}

	// Δοκιμάζουμε, για μια τυχαία τιμή που δεν μπορεί πιθανώς να υπάρχει στην λίστα,
	// αν η list_find γυρνάει σωστά NULL pointer
	int not_exists = -1;
	TEST_ASSERT(blist_find(blist, &not_exists, compare_ints) == NULL);

	blist_destroy(blist);
}

void test_find_node() {
	BList blist = blist_create(NULL);

	// Εισαγωγή τιμών στον πίνακα
	int N = 5;
	int array[N];

	for (int i = 0; i < N; i++) {
		array[i] = i;
		blist_insert(blist, BLIST_EOF, &array[i]);
	}

	// Ξεκινάμε από την αρχή της λίστας
	BListNode node = blist_last(blist);

	for (int i = N-1; i >= 0; i--) {

		BListNode found_node = blist_find_node(blist, &i, compare_ints); 
		TEST_ASSERT(found_node == node);
		TEST_ASSERT(blist_node_value(blist, found_node) == &array[i]);
		node = blist_previous(blist, node);
	}

	blist_destroy(blist);
}


// Λίστα με όλα τα tests προς εκτέλεση
TEST_LIST = {
    { "blist_create", test_create },
	{ "blist_insert", test_insert },
    { "blist_remove", test_remove },
	{ "blist_find", test_find },
	{ "blist_find_node", test_find_node },
	{ NULL, NULL } // τερματίζουμε τη λίστα με NULL
};