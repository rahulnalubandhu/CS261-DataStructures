/*
 * This file is where you should implement your binary search tree.  It already
 * contains skeletons of the functions you need to implement (along with
 * documentation for each function).  Feel free to implement any additional
 * functions you might need.  Also, don't forget to include your name and
 * @oregonstate.edu email address below.
 *
 * Name: Rahul Kumar Nalubandhu   
 * Email: nalubanr@oregonstate.edu
 */

#include <stdlib.h>
#include <assert.h>
#include "bst.h"
#include "stack.h"

/*
 * This structure represents a single node in a BST.  In addition to containing
 * pointers to its two child nodes (i.e. `left` and `right`), it contains two
 * fields representing the data stored at this node.  The `key` field is an
 * integer value that should be used as an identifier for the data in this
 * node.  Nodes in the BST should be ordered based on this `key` field.  The
 * `value` field stores data associated with the key.
 *
 * You should not modify this structure.
 */
struct bst_node {
  int key;
  void* value;
  struct bst_node* left;
  struct bst_node* right;
};


/*
 * This structure represents an entire BST.  It specifically contains a
 * reference to the root node of the tree.
 *
 * You should not modify this structure.
 */
struct bst {
  struct bst_node* root;
};

/*
 * This function should allocate and initialize a new, empty, BST and return
 * a pointer to it.
 */
struct bst* bst_create() {
  /*
   * FIXME:
   */
  struct bst *bst = malloc(sizeof(struct bst));
  bst->root = NULL;
  return bst;
}

/*
 * This function should free the memory associated with a BST.  While this
 * function should up all memory used in the BST itself, it should not free
 * any memory allocated to the pointer values stored in the BST.  This is the
 * responsibility of the caller.
 *
 * Params:
 *   bst - the BST to be destroyed.  May not be NULL.
 */
// recursively
void free_helper(struct bst_node* node){
    if (node){
        free_helper(node->left);
        free_helper(node->right);
        free(node);
    }
}

void bst_free(struct bst* bst)
{   
    free_helper(bst->root);
    bst->root=NULL;
    free(bst);
}

/*
 * This function should return the total number of elements stored in a given
 * BST.
 *
 * Params:
 *   bst - the BST whose elements are to be counted.  May not be NULL.
 */
// recursive
int size_of_bst(struct bst_node* node){
  if (node)
    return 1 + size_of_bst(node->left) + size_of_bst(node->right);
  return 0;
}

int bst_size(struct bst* bst)
{
  if (bst->root==NULL) return 0;
  
  return 1 + size_of_bst(bst->root->left) + size_of_bst(bst->root->right);
}


/*
 * This function should insert a new key/value pair into the BST.  The key
 * should be used to order the key/value pair with respect to the other data
 * stored in the BST.  The value should be stored along with the key, once the
 * right location in the tree is found.
 *
 * Params:
 *   bst - the BST into which a new key/value pair is to be inserted.  May not
 *     be NULL.
 *   key - an integer value that should be used to order the key/value pair
 *     being inserted with respect to the other data in the BST.
 *   value - the value being inserted into the BST.  This should be stored in
 *     the BST alongside the key.  Note that this parameter has type void*,
 *     which means that a pointer of any type can be passed.
 */
// recurssive function
struct bst_node* insertion_helper(struct bst_node* node, struct bst_node* new_node){
      if(node == NULL)
      {
        return new_node;
      }
      else if(node->key > new_node->key)
      {
        node->left = insertion_helper(node->left, new_node);
      }
      else
      {
          node->right = insertion_helper(node->right, new_node);
      }
      return node;
}

void bst_insert(struct bst* bst, int key, void* value)
{
    struct bst_node* new_node = (struct bst_node*) malloc(sizeof(struct bst_node));
    new_node->key = key;
    new_node->value = value;
    new_node->left=NULL;
    new_node->right=NULL;
    bst->root = insertion_helper(bst->root, new_node);
}

/*
 * This function should remove a key/value pair with a specified key from a
 * given BST.  If multiple values with the same key exist in the tree, this
 * function should remove the first one it encounters (i.e. the one closest to
 * the root of the tree).
 *
 * Params:
 *   bst - the BST from which a key/value pair is to be removed.  May not
 *     be NULL.
 *   key - the key of the key/value pair to be removed from the BST.
 */
struct bst_node* find_minimum(struct bst_node* root){
  while(root->left)
      root= root->left;
  return root;
}

// recursive function
struct bst_node* helper(struct bst_node* root, int key){
  if(root==NULL)
    return NULL;
  if (root->key<key)
    root->right = helper(root->right, key);
  else if(root->key>key)
    root->left = helper(root->left, key);
  else
  {
    if(root->left==NULL && root->right==NULL){
      free(root);
      return NULL;
    }
    else if(root->left==NULL || root->right==NULL){
      struct bst_node *temp = root->left?root->left:root->right;
      free(root);
      return temp;
    }
    else{
      struct bst_node *temp = find_minimum(root->right);
      root->key = temp->key;
      root->value = temp->value;
      root->right = helper(root->right, temp->key);
    }
  }
  return root;
}

void bst_remove(struct bst* bst, int key)
{
  bst->root = helper(bst->root, key);
}

/*
 * This function should return the value associated with a specified key in a
 * given BST.  If multiple values with the same key exist in the tree, this
 * function should return the first one it encounters (i.e. the one closest to
 * the root of the tree).  If the BST does not contain the specified key, this
 * function should return NULL.
 *
 * Params:
 *   bst - the BST from which a key/value pair is to be removed.  May not
 *     be NULL.
 *   key - the key of the key/value pair whose value is to be returned.
 *
 * Return:
 *   Should return the value associated with the key `key` in `bst` or NULL,
 *   if the key `key` was not found in `bst`.
 */
void* bst_get(struct bst* bst, int key){
  struct bst_node *root = bst->root;
  while (root){
    if (root->key==key)
      return root->value;
    else if (root->key<key)
      root = root->right;
    else
      root=root->left;
  }
  return NULL;
}


/*****************************************************************************
 **
 ** BST puzzle functions
 **
 *****************************************************************************/

/*
 * This function should return the height of a given BST, which is the maximum
 * depth of any node in the tree (i.e. the number of edges in the path from
 * the root to that node).  Note that the height of an empty tree is -1 by
 * convention.
 *
 * Params:
 *   bst - the BST whose height is to be computed
 *
 * Return:
 *   Should return the height of bst.
 */

int bst_find_height(struct bst_node* root){
  // empty tree has height -1
  if (root == NULL){
    return -1;
  }

  // recursively find height of left subtree
  int left = bst_find_height(root->left);

  // recursively find height of right subtree
  int right = bst_find_height(root->right);
  
  // return highest height in the tree below the "root" node
  if (left > right){
    return left + 1;
  }else{
    return right + 1;
  }
}
 int bst_height(struct bst* bst) {
  /*
   * FIXME:
   */
  return bst_find_height(bst->root);
  }

/*
 * This function should determine whether a specified value is a valid path
 * sum within a given BST.  In other words, this function should check whether
 * the given BST contains any path from the root to a leaf in which the keys
 * sum to the specified value.
 *
 * Params:
 *   bst - the BST whose paths sums to search
 *   sum - the value to search for among the path sums of `bst`
 *
 * Return:
 *   Should return 1 if `bst` contains any path from the root to a leaf in
 *   which the keys add up to `sum`.  Should return 0 otherwise.
 */
int bst_has_path_sum(int sum, struct bst_node* root) {
  // case: when empty tree is passed in
  if (root == NULL){
    return (sum == 0);
  }else{
    int boolean = 0;
    int sub_sum = sum - root->key;

    // if we are at a leaf of a tree, the path sum EXISTS
    if (sub_sum == 0 && root->right == NULL && root->left == NULL){
      return 1;
    }
    
    /*
    * recursive algorithm to determine if the right or left side of the current "root" node
    * have sums equal to the current sub-sum
    */
    if(root->left != NULL){
      boolean = bst_has_path_sum(sub_sum, root->left);
    }if(root->right != NULL){
      boolean = boolean || bst_has_path_sum(sub_sum, root->right);
    }

    return boolean;
       
  }
}
int bst_path_sum(struct bst* bst, int sum) {
  /*
   * FIXME:
   */
  return bst_has_path_sum(sum, bst->root);
}

/*
 * This function should compute a range sum in a given BST.  Specifically, it
 * should compute the sum of all keys in the BST between a given lower bound
 * and a given upper bound.  For full credit, you should not process any subtree
 * whose keys cannot be included in the range sum.
 *
 * Params:
 *   bst - the BST within which to compute a range sum
 *   lower - the lower bound of the range over which to compute a sum; this
 *     should be considered an *inclusive* bound; in other words a key that's
 *     equal to this bound should be included in the sum
 *   upper - the upper bound of the range over which to compute a sum; this
 *     should be considered an *inclusive* bound; in other words a key that's
 *     equal to this bound should be included in the sum
 *
 * Return:
 *   Should return the sum of all keys in `bst` between `lower` and `upper`.
 */
void bst_range_sum_helper(struct bst_node* root, int lower, int upper, int *sum){

  if( root == NULL){//if there is no root return null
    return ;
  }
  if ( root->key >= lower && root->key <= upper ){ // checking if the root->key is within the range
    *sum += root->key;// calculating the sum
    bst_range_sum_helper(root->left, lower, upper,sum); // tranverse in hte left subtreerecursively
    bst_range_sum_helper(root->right, lower, upper,sum);    // traverse to the right subtree recursively
  }else if(root-> key > upper){
    // check to see if the root->key is greter than the upper range, 
    //if so we traverse the left subtree because the key may be larger than the upper range and we dont need to traverse it
    //
    bst_range_sum_helper(root->left, lower, upper , sum);
  }else {
     // check to see if the root->key is lesser than the lower range, 
    //if so we traverse the right subtree because the key may be lesser than the lower range and we dont need to traverse it
    bst_range_sum_helper(root->right, lower, upper, sum);

  } 

}
int bst_range_sum(struct bst* bst, int lower, int upper) {
  /*
   * FIXME:
   */
  int sum = 0;
  struct bst_node *root = bst->root;
  bst_range_sum_helper(root, lower, upper, &sum );// calling the helper fucntion to calcualte the sum
  // printf("summmmmmm : %d\n", sum);
  return sum;
}

/*****************************************************************************
 **
 ** BST iterator definition (extra credit only)
 **
 *****************************************************************************/

/*
 * Structure used to represent a binary search tree iterator.  It contains
 * only a reference to a stack to be used to implement the iterator.
 *
 * You should not modify this structure.
 */
struct bst_iterator {
  struct stack* stack;
};

/*
 * This function should allocate and initialize an iterator over a specified
 * BST and return a pointer to that iterator.
 *
 * Params:
 *   bst - the BST for over which to create an iterator.  May not be NULL.
 */
struct bst_iterator* bst_iterator_create(struct bst* bst) {
  /*
   * FIXME:
   */
  struct bst_iterator* iter = malloc(sizeof(struct bst_iterator*));
  iter->stack = stack_create();
  
  //traverse to the far left side of the tree. This is where the iterator will start
  struct bst_node* root = bst->root;
  while(root != NULL){
    stack_push(iter->stack, root);
    root = root->left;
  }

  return iter;
}
/*
 * This function should free all memory allocated to a given BST iterator.
 * It should NOT free any memory associated with the BST itself.  This is the
 * responsibility of the caller.
 *
 * Params:
 *   iter - the BST iterator to be destroyed.  May not be NULL.
 */
void bst_iterator_free(struct bst_iterator* iter) {
  /*
   * FIXME:
   */
  stack_free(iter->stack);
  free(iter);
}

/*
 * This function should indicate whether a given BST iterator has more nodes
 * to visit.  It should specifically return 1 (true) if the iterator has at
 * least one more node to visit or 0 (false) if it does not have any more
 * nodes to visit.
 *
 * Param:
 *   iter - the BST iterator to be checked for remaining nodes to visit.  May
 *     not be NULL.
 */
int bst_iterator_has_next(struct bst_iterator* iter) {
  /*
   * FIXME:
   */
 	if (stack_isempty(iter->stack) == 1)
	  return 0;
	else 
		return 1;
}


/*
 * This function should return both the value and key associated with the
 * current node pointed to by the specified BST iterator and advnce the
 * iterator to point to the next node in the BST (in in-order order).
 *
 * Because a function can't return two things, the key associated with the
 * current node should be returned the normal way, while its value should be
 * returned via the argument `value`.  Specifically, the argument `value`
 * is a pointer to a void pointer.  The current BST node's value (a void
 * pointer) should be stored at the address represented by `value` (i.e. by
 * dereferencing `value`).  This will look something like this:
 *
 *   *value = current_node->value;
 *
 * Parameters:
 *   iter - BST iterator.  The key and value associated with this iterator's
 *     current node should be returned, and the iterator should be updated to
 *     point to the next node in the BST (in in-order order).  May not be NULL.
 *   value - pointer at which the current BST node's value should be stored
 *     before this function returns.
 *
 * Return:
 *   This function should return the key associated with the current BST node
 *   pointed to by `iter`.
 */
int bst_iterator_next(struct bst_iterator* iter, void** value) {

  //pointer to current node 
  if (value) {

    struct bst_node* node = stack_pop(iter->stack);
  
    *value = node->value;
   
 
  //traverse right side of current node and add the values to the stack
    struct bst_node* child = node->right;
    while(child != NULL){
      stack_push(iter->stack, child);
      child = child->left;
    }
    return node->key;
  }
  // value of current node we will be returning
  
  return 0;
  // return value;
}
