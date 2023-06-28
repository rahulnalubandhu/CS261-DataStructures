/*
 * This file is where you should implement your queue-from-stacks.  It already
 * contains skeletons of the functions you need to implement (along with
 * documentation for each function).  Feel free to implement any additional
 * functions you might need.  Also, don't forget to include your name and
 * @oregonstate.edu email address below.
 *
 * Name:  Rahul Kumar Nalubandhu	
 * Email: nalubanr@oregonstate.edu
 */

#include <stdlib.h>

#include "stack.h"
#include "queue_from_stacks.h"

/*
 * This is the structure that will be used to represent a queue using two
 * stacks.  It specifically contains two fields, each representing a stack.
 * These two stacks should be used together as the underlying data storage for
 * the queue.
 *
 * You should not modify this structure.
 */
struct queue_from_stacks {
  struct stack* s1;
  struct stack* s2;
};

/*
 * This function should allocate and initialize a new, empty queue-from-stacks
 * and return a pointer to it.
 */
struct queue_from_stacks* queue_from_stacks_create() {

	struct queue_from_stacks* qfs = malloc(sizeof(struct queue_from_stacks));
	qfs->s1=stack_create();
	qfs->s2= stack_create();

  	return qfs ;
}


/*
 * This function should free the memory associated with a queue-from-stacks.
 * While this function should up all memory used in the queue-from-stacks
 * itself, it should not free any memory allocated to the pointer values stored
 * in the queue.  This is the responsibility of the caller.
 *
 * Params:
 *   qfs - the queue-from-stacks to be destroyed.  May not be NULL.
 */
void queue_from_stacks_free(struct queue_from_stacks* qfs) {
  	//check whether s1 and s2 are null or not if not null calling free function to free.
	if(qfs !=NULL){
		if (qfs->s1 != NULL)
			stack_free(qfs->s1);
		if(qfs->s2 != NULL)
			stack_free(qfs->s2);
	}
	free(qfs);
	return;
}

/*
 * This function should indicate whether a given queue-from-stacks is currently
 * empty.  Specifically, it should return 1 if the specified queue-from-stacks
 * is empty (i.e. contains no elements) and 0 otherwise.
 *
 * Params:
 *   qfs - the queue-from-stacks whose emptiness is being questioned.  May not
 *     be NULL.
 */
int queue_from_stacks_isempty(struct queue_from_stacks* qfs) {
  	/*
	 * FIXME:
	 */
	// s1 is main 
	if(stack_isempty(qfs->s1)!=NULL)
  		return 1;
	else 
		return 0;
}

/*
 * This function should enqueue a new value into a given queue-from-stacks.
 * The value to be enqueued is specified as a void pointer.
 *
 * Params:
 *   qfs - the queue-from-stacks into which a value is to be enqueued.  May not
 *     be NULL.
 *   val - the value to be enqueued.  Note that this parameter has type void*,
 *     which means that a pointer of any type can be passed.
 */
void queue_from_stacks_enqueue(struct queue_from_stacks* qfs, void* val) {
//   checking val is null or not and if not null calling function stack_isempty to check wether s2 is empty or not.
// next if the condition is true enque the values to s1.
	if ( val != NULL){
		if(stack_isempty(qfs->s2)== 1){
			stack_push(qfs->s1, val);
		}
// if its not true call function stacks_empty2 to pop values from s2 and push into s1.
		else{
		
			queue_from_stacks_emptys2(qfs);
			stack_push(qfs->s1, val);
		}
	}
  	return ;
}

/*
 * This function should return the value stored at the front of a given
 * queue-from-stacks *without* removing that value.
 *
 * Params:
 *   qfs - the queue-from-stacks from which to query the front value.  May not be NULL.
 */
void* queue_from_stacks_front(struct queue_from_stacks* qfs) {
	// empty all the values from s1 to s2 and print the top value of s2
	  return queue_from_stacks_emptys1(qfs);
}

/*
 * This function should dequeue a value from a given queue-from-stacks and
 * return the dequeued value.
 *
 * Params:
 *   qfs - the queue-from-stacks from which a value is to be dequeued.  May not
 *     be NULL.
 *
 * Return:
 *   This function should return the value that was dequeued.
 */
void* queue_from_stacks_dequeue(struct queue_from_stacks* qfs) {
	// empty all the values from s1 to s2 and pop the top value of s2
	void* dequeue_val= queue_from_stacks_emptys1(qfs);
	stack_pop(qfs->s2);
	queue_from_stacks_emptys2(qfs);

  	return dequeue_val;
}

//empty content of s1 to s2 and retuns the top value from s2 (i.e front vlaue of queue)
void* queue_from_stacks_emptys1(struct queue_from_stacks* qfs){

	while(!stack_isempty(qfs->s1)){
		void* pop_val=stack_pop(qfs->s1);
		stack_push(qfs->s2, pop_val);
	}
	void* top_val = stack_top(qfs->s2);
	// printf("\nfront %d\n", top_val);
  	return top_val;
}
//empty contents of s2 to s1 
void* queue_from_stacks_emptys2(struct queue_from_stacks* qfs){

	while(!stack_isempty(qfs->s2)){
		void* pop_val=stack_pop(qfs->s2);
		stack_push(qfs->s1, pop_val);
	}
  	// return stack_top(qfs->s1);
}
// to print s1 and s2..
void* print_s1(struct queue_from_stacks* qfs){
	printf("\n s1\n");

	while (!stack_isempty(qfs->s1)){
		int* v=stack_pop(qfs->s1);
		printf("\n %4d\n",*v);

	}

}
void* print_s2(struct queue_from_stacks* qfs){
	printf("\n s2\n");
	while (!stack_isempty(qfs->s2)){
		int* v=stack_pop(qfs->s2);
		printf("\n %4d\n",*v);

	}

}