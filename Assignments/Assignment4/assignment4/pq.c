/*
 * In this file, you will write the structures and functions needed to
 * implement a priority queue.  Feel free to implement any helper functions
 * you need in this file to implement a priority queue.  Make sure to add your
 * name and @oregonstate.edu email address below:
 *
 * Name:Rahul Kumar Nalubandhu
 * Email:nalubanr@oregonstate.edu
 */

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#include "pq.h"
#include "dynarray.h"

/*
 * This is the structure that represents a priority queue.  You must define
 * this struct to contain the data needed to implement a priority queue.
 */
struct pq
{
    struct dynarray* queue;
};
struct node{
    int priority;
    void* data;
};


/*
 * This function should allocate and initialize an empty priority queue and
 * return a pointer to it.
 */
struct pq* pq_create()
{
    struct pq* start = (struct pq*) malloc(sizeof(struct pq)); //to allocate memory
    start->queue = dynarray_create();
    return start;
};


/*
 * This function should free the memory allocated to a given priority queue.
 * Note that this function SHOULD NOT free the individual elements stored in
 * the priority queue.  That is the responsibility of the caller.
 *
 * Params:
 *   pq - the priority queue to be destroyed.  May not be NULL.
 */
void pq_free(struct pq* pq)
{
    while(dynarray_size(pq->queue)){
        pq_remove_first(pq);
    }
    dynarray_free(pq->queue);
    free(pq);
}


/*
 * This function should return 1 if the specified priority queue is empty and
 * 0 otherwise.
 *
 * Params:
 *   pq - the priority queue whose emptiness is to be checked.  May not be
 *     NULL.
 *
 * Return:
 *   Should return 1 if pq is empty and 0 otherwise.
 */
int pq_isempty(struct pq* pq)
{
    return dynarray_size(pq->queue)==0; //gives the size of the array to show if it is empty or not
}


/*
 * This function should insert a given element into a priority queue with a
 * specified priority value.  Note that in this implementation, LOWER priority
 * values are assigned to elements with HIGHER priority.  In other words, the
 * element in the priority queue with the LOWEST priority value should be the
 * FIRST one returned.
 *
 * Params:
 *   pq - the priority queue into which to insert an element.  May not be
 *     NULL.
 *   value - the value to be inserted into pq.
 *   priority - the priority value to be assigned to the newly-inserted
 *     element.  Note that in this implementation, LOWER priority values
 *     should correspond to elements with HIGHER priority.  In other words,
 *     the element in the priority queue with the LOWEST priority value should
 *     be the FIRST one returned.
 */
void pq_insert(struct pq* pq, void* value, int priority)
{
    struct node* output;
    struct node* newNode = (struct node*) malloc(sizeof(struct node));//creates the struct to access the elements
    newNode->data=value;//gets the value
    newNode->priority = priority;//gets the priority number
    dynarray_insert(pq->queue,newNode);//inserts the element into the heap array
    
    int left=0, right=dynarray_size(pq->queue)-1;//gets where in the heap to inser the next element
    
    while(left>=0){
        left = (right - 1)/2;//how to get the correct parent (where to start)
        output = (struct node*)dynarray_get(pq->queue, left);//gets the parents vals so it acts as the parent
        if (output->priority > newNode->priority){//percolates the newly added element in order to make sure that every parent has a smaller priority than children 
            dynarray_set(pq->queue, left, newNode);//at the parent index, set the index with the inserted value
            dynarray_set(pq->queue, right, output);//set with the parent original information
            right = left;
        }
       else{
            break;
        }
    }
    output = NULL;//set to NULL if the parent value is less than 0
}


/*
 * This function should return the value of the first item in a priority
 * queue, i.e. the item with LOWEST priority value.
 *
 * Params:
 *   pq - the priority queue from which to fetch a value.  May not be NULL or
 *     empty.
 *
 * Return:
 *   Should return the value of the first item in pq, i.e. the item with
 *   LOWEST priority value.
 */
void* pq_first(struct pq* pq)
{
    struct node* firstelem = NULL;
    firstelem = (struct node*)dynarray_get(pq->queue, 0);//gets the actual element in the first position 
    if (firstelem != NULL){//if there is an element
        return firstelem->data;//return the data
    }
    else
    {
        return NULL;
    }
}


/*
 * This function should return the priority value of the first item in a
 * priority queue, i.e. the item with LOWEST priority value.
 *
 * Params:
 *   pq - the priority queue from which to fetch a priority value.  May not be
 *     NULL or empty.
 *
 * Return:
 *   Should return the priority value of the first item in pq, i.e. the item
 *   with LOWEST priority value.
 */
int pq_first_priority(struct pq* pq)
{
    struct node* firstelem = NULL;
    firstelem = (struct node*)dynarray_get(pq->queue, 0);//gets the actual element in the first position
    if (firstelem != NULL){ //if there is an element
        return firstelem->priority;//return the priority integer
    }
    else
    {
        return 0;
    }
}


/*
 * This function should return the value of the first item in a priority
 * queue, i.e. the item with LOWEST priority value, and then remove that item
 * from the queue.
 *
 * Params:
 *   pq - the priority queue from which to remove a value.  May not be NULL or
 *     empty.
 *
 * Return:
 *   Should return the value of the first item in pq, i.e. the item with
 *   LOWEST priority value.
 */
void* pq_remove_first(struct pq* pq)
{
    struct node* first = NULL; //access first element
    struct node* last = NULL;//access last element
    first =(struct node*)dynarray_get(pq->queue, 0);//the highest priority element is at the 0 index so this should be where the first element shoudl be set.
    last = (struct node*)dynarray_get(pq->queue, dynarray_size(pq->queue)-1);//the last element has the lowest priority.
    dynarray_set(pq->queue, 0, last); //replaces the highest priority element
    dynarray_remove(pq->queue, dynarray_size(pq->queue)-1);//removes tht element from the array after everything is copied over.
    last = NULL;
    int curr = 0,lft = 0,rght = 0,min = 0;//left child element,right child element,min
    struct node* tmp1;//temp to get an element
    struct node* tmp2;//temp to get an element
   
    while (1)//while true
    {
        lft = (2 * curr) + 1;//set to left
        rght = (2 * curr) + 2;//set to right
       
        if (lft > dynarray_size(pq->queue) - 1)
            break;
        else if (lft == dynarray_size(pq->queue) - 1)
            min = lft;
        else
        {   if (((struct node*)dynarray_get(pq->queue, lft))->priority > ((struct node*)dynarray_get(pq->queue, rght))->priority)//makes sure every node's priority value is smaller than the children 
                min = rght;//if left is bigger than right, the minimum is the right
            else
                min = lft;//if right is bigger than left, the minimum is the left
        }
        if ((((struct node*)dynarray_get(pq->queue, curr))->priority) > (((struct node*)
        dynarray_get(pq->queue, min))->priority))
        {
            tmp1 = (struct node*)dynarray_get(pq->queue, min);//temp gets the min information
            tmp2 = (struct node*)dynarray_get(pq->queue, curr);//temp 2 gets the curr element information
            dynarray_set(pq->queue, min, tmp2);
            dynarray_set(pq->queue, curr, tmp1);
            curr = min;
        }
        else
            break;
    }
    if (first != NULL)
    {
        void *data = first->data;
        free(first);//frees memory
        return data;
    }
    return NULL;

}

