/*
 * In this file, you'll implement Dijkstra's algorithm to find the least
 * expensive paths in the graph defined in `airports.dat`.  Don't forget to
 * include your name and @oregonstate.edu email address below.
 *
 * Name:Rahul Kumar Nalubandhu
 * Email: nalubanr@oregonstate.edu
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "pq.h"
#define DATA_FILE "airports.dat"
#define START_NODE 0


void print_path(int arr[], int i){
  if(i != -1){
    print_path(arr, arr[i]);
    printf(" %d ", i);
  }
}

struct node{
  int N;
  int prev_N; 
};
	/*
	 * Write your code here to find the
	 * least-cost paths from node 0 to all other nodes in the graph.  Make sure
	 * to print out the least-cost paths you find at the end.
	 *
	 * FIXME: 
 	 */
  int main(int argc, char const *argv[]) {
	FILE* file = fopen(DATA_FILE, "r");
  int n_nodes, n_edges;
  fscanf(file, "%d %d", &n_nodes,&n_edges);
	// printf("%d %d\n",n_nodes,n_edges);//checking
  int arr[n_nodes][n_nodes];
  //for reading data from graph
  for (int i=0; i<n_nodes; i++){
    for (int j=0; j< n_nodes; j++){
      arr[i][j] = -1;
    }
  }
  // assigning the values from .dat file to node_i, node_j, cost_i_j
  for(int i= 0; i<n_edges; i++){
    int node_i, node_j, cost_i_j;
    fscanf(file, "%d %d %d", &node_i, &node_j, &cost_i_j); // generating matrix from .dat file.
    arr[node_i][node_j] = cost_i_j;
    }
  fclose(file);

  int N_start;
  N_start = 0;// marking the distance to start node N_start to be 0.

  int cost[n_nodes];
  int prev[n_nodes];

  struct node* new_node = malloc(sizeof(struct node));
  new_node->N = 0;
  new_node->prev_N = -1;

  for (int i=0; i<n_nodes; i++ ){
    cost[i] = __INT_MAX__; //to specify that an integer variable cannot store any value beyond the limit.
    prev[i] = -1;
  }

  // using priority queue of key value pairs to tell which node to visit based on sorted min value.
  struct pq* pq = pq_create();
  pq_insert(pq, new_node, 0); // inserting into priority queue and loop while pq is not empty pulling out next promising pair.

  while(!pq_isempty(pq)){
    int c = pq_first_priority(pq); //c is the total cost of the path to N
    struct node* current = pq_remove_first(pq);

    if (c < cost[current->N]){
      cost[current->N] = c;
      prev[current->N] = current->prev_N;
      int c_i;
    for (int i=0; i<n_nodes; i++){
      if(arr[current->N][i] != -1){
        c_i = arr[current->N][i];
        new_node = malloc(sizeof(struct node));
        new_node->N = i;
        new_node->prev_N = current->N;
        pq_insert(pq, new_node, c_i+c);
        }
      }
    }
    free(current);
  }
//  for test cases
  //reading data
  for(int i=0; i<n_nodes; i++){
    printf("The shortest cost path from o to %d is %d ", i, cost[i]);
    printf("( via ");
    print_path(prev, i);
    printf(")");
    printf("\n");
  }
  pq_free(pq);//frees memory
  return 0;
}
