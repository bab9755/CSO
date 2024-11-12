#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/***********************************************************

This program implements a simple priority queue using a heap.
The items being sorted are records, where each record contains a last name, a 
first name, and an ID number.  The records will be sorted according 
to their ID numbers, from smallest to largest.

A heap (in this context) is a binary tree with the following 
properties:
- The value at a parent node is greater than the value at 
  either child node.
- The heap is implemented using an array. Each element of the
  array is a pointer to a record. 
- For a parent node at index i of the array, the children are 
  found at indices (i*2)+1 and (i*2)+2. All parent nodes
  have two children, except for the very last parent node.
- For a child node at index i of the array, the parent is
  found at index (x-1)/2 (using integer division).

************************************************************/

// This is the declaration of the RECORD type

typedef struct  {
  char *last_name;
  char *first_name;
  long id_number;
} RECORD;


RECORD *read_record();

/* This function reads in the data for a single record from the
   standard input by calling scanf. If scanf succeeds in 
   reading the data, a new RECORD is allocated, populated
   with the data, and a pointer to the record is returned 
*/

RECORD *read_record()
{
  char lastname[100], firstname[100];
  RECORD *p;
  long id;
  int res = scanf("%s %s %ld", lastname, firstname, &id);
  if (res == EOF)   // EOF is -1
    return NULL;
  p = malloc(sizeof(RECORD));
  p->last_name = malloc(strlen(lastname)+1);
  strcpy(p->last_name, lastname);
  p->first_name = malloc(strlen(lastname)+1);
  strcpy(p->first_name, firstname);  
  p->id_number = id;
  return p;
}
    

/*
  These are macros that are convenient for finding the parent,
  left child, and right child of a node at index x of the array.
*/

#define PARENT(x) ((x-1)>>1)
#define LEFT(x) ((x<<1)+1)
#define RIGHT(x) ((x<<1)+2)


// This is the fixed size of the heap array.

#define SIZE 500

// The heap is an array of pointers to records
RECORD *heap[SIZE];

// This is a count of the number of nodes in the head.
// It is also the index of the next available slot in the
// array.

int heap_count = 0;
// extern int heap_count; // in assembly

void heap_swap(int i, int j);

/* 
  This function simply swaps the contents of the heap
  array at indices i and j.  The contents of each 
  element of the array is just a pointer to a record.
*/

void heap_swap(int i, int j) {
  RECORD *temp = heap[i];
  heap[i] = heap[j];
  heap[j] = temp;
}


void sift_up(int i);

/* 
   This is the heap "sift up" function. It starts with a leaf, at array index i, that has just
   been added to the tree and might violate the heap requirement (i.e. the value of the leaf
   may be less than that of its parent). It works by comparing the node at index i to 
   its parent.  If the value of the node is not less than its parent, the heap property
   has been maintained and the function can return.  Otherwise, the values at the node and at its
   parent are swapped, i is set to the index of the parent node (since the value at the parent now 
   may be less than at the grandparent), and the process iterates until either the heap property
   is satisfied or the root (at index 0) is reached.
*/


void sift_up(int i)
{
  while (i != 0) {
    if (heap[i]->id_number >= heap[PARENT(i)]->id_number)   // correct situation, no need to continue
	return;
    // otherwise, need to swap with parent
    heap_swap(i, PARENT(i));
    i = PARENT(i);
  }
}


void sift_down();


/* 
   This function performs the heap "sift down" process, which occurs when
   a new value has been inserted at the root of the tree (i.e. when the 
   existing root is removed and the last leaf in the tree is inserted at
   the root). Starting at the root as the parent node, the values of the 
   two child nodes are compared to each other. Then if the value at the
   parent is greater than the value at the smaller child, the values at
   the parent and the smaller child are swapped, and the process
   continues with the smaller child being considered the parent in the
   next iteration.  The process terminates when a leaf is reached.

   At any point, if the value at the parent is not greater than the 
   smaller child, the heap property has been preserved and the function
   can return. If a parent ony has one child (which must be the left 
   child), then the left child is considered the smaller child.
*/


void sift_down()
{
  int i = 0;
  int last_parent = PARENT(heap_count - 1);
  int min_child;
  
  while (i <= last_parent) {
    if ((RIGHT(i) >= heap_count) ||
	(heap[LEFT(i)]->id_number <= heap[RIGHT(i)]->id_number))
      min_child = LEFT(i);
    else
      min_child = RIGHT(i);
    if (heap[i]->id_number > heap[min_child]->id_number) {
      heap_swap(i, min_child);
      i = min_child;
    }
    else // done sifting down
      return;
  }
}



void heap_insert(RECORD *p);

/*
   This function inserts a new record into the 
   heap. It does so by adding a pointer to the 
   record at index heap_count (the first open
   slot) in the array and then calling
   sift_up(), above, to restore the heap property.
*/


void heap_insert(RECORD *p)
{
  if (heap_count >= SIZE) {
    printf("Error: Heap is full\n");
    exit(1);
  }
  heap[heap_count] = p;
  sift_up(heap_count);
  heap_count++;
}


RECORD *heap_remove();

/* 
    This function removes the smallest  value in the heap, i.e.
    the value at the root node (at array index 0), and returns 
    that smallest value (which is a pointer to a record).
    Before returning, it writes the value of the last
    leaf (at index heap_count-1 of the array) into to the 
    root node and then calls    sift_down(), above, to 
    restore the heap property.
*/

RECORD *heap_remove()  
{
  if (heap_count <= 0) {
    printf("Error: Heap is empty\n");
    exit(1);
  }
  RECORD *result = heap[0];
  heap_count--;
  heap[0] = heap[heap_count];
  sift_down();
  return result;
}



/* 

   This is the main function, which repeatedly calls read_record and
   heap_insert to insert pointers to records into the heap. Once
   all the data has been read, it repeatedly calls heap_remove()
   to print out the records in sorted order, according the ID number
*/

int main() {
  RECORD *p = NULL;
  p = read_record();
  while (p != NULL) {
    heap_insert(p);
    p = read_record();
  }
  
  printf("Sorted\n------\n");
  while (heap_count != 0) {
    p = heap_remove();
    printf("%ld: %s, %s\n", p->id_number, p->last_name, p->first_name);
  }
}


