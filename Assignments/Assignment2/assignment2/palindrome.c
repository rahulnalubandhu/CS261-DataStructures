#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "queue.h"
#include "stack.h"

#define MAX_STR_LEN 256

struct palindrome{
  struct stack* stack;
  struct queue* queue;
};
/*
 * This function prompts the user for input and stores a maximum of `n`
 * characters of the string they enter into `dest`.  Any trailing line ending
 * characters are removed from the input string.  Returns 1 if a string was
 * successfully read from the user or 0 otherwise.
 */
int get_user_str(char* dest, int n) {
  printf("\nEnter a string, and we'll check whether it's a palindrome:\n");
  if (fgets(dest, MAX_STR_LEN, stdin) != NULL) {
  
    dest[strcspn(dest, "\r\n")] = '\0';
    return 1;
  } else {
    return 0;
  }
}
void free_mem(struct palindrome* palindrome){
  stack_free(palindrome->stack);
  queue_free(palindrome->queue);
  free(palindrome);
}
void print_res(struct palindrome* palindrome,int flag){
  if (flag == 1){
      free_mem(palindrome);
      printf("\npalindrome");
    }
    else{
      free_mem(palindrome);
      printf("\nnot a palindrome");
      return ;

    }
}
int main(int argc, char const *argv[]) {
  char* in = malloc(MAX_STR_LEN * sizeof(char));
  // get_user_str(in, MAX_STR_LEN);
  
  while (get_user_str(in, MAX_STR_LEN)) {
    // printf("chr  %d\n",strlen(in));
    int flag = 0;
    // creating and allocating memory for palindrome
    struct palindrome* palindrome = malloc(sizeof(struct palindrome)); 
    // storing the given input in stack and queue
    palindrome->stack= stack_create();
    palindrome->queue = queue_create();
    int len =0;
    int length= strlen(in);
    for ( int i=0; i< length ; i++){
      if(isalpha(in[i])){
          len++;
          // if sring send it to stack push which is entering
          stack_push(palindrome->stack,tolower(in[i]));
          // also for queue
          queue_enqueue(palindrome->queue,tolower(in[i]));
          // i++;
      }
    }
    for ( int i=0; i< len;i++){
      // printf(" ssssstack %c",queue_dequeue(palindrome->queue));
      // to compare pop and deque.
      if(stack_pop(palindrome->stack) != queue_dequeue(palindrome->queue)){
        // printf("\nnot a palindrome\n");
        flag=0;
        break;
      }
      else{
        flag = 1;
      }

    }
    // printf("flag %d",flag);
    print_res(palindrome,flag);
  }
  
  free(in);
  return 0;
}
