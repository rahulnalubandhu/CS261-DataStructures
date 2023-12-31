/*
 * In this file, you will write the structures and functions needed to
 * implement a hash table.  Feel free to implement any helper functions
 * you need in this file to implement a hash table.  Make sure to add your
 * name and @oregonstate.edu email address below:
 *
 * Name: Rahul Kumar Nalubandhu     
 * Email: nalubanr@oregonstate.edu
 */

#include <stdlib.h>

#include "dynarray.h"
#include "list.h"
#include "hash_table.h"



/*
 * This is the structure that represents a hash table.  You must define
 * this struct to contain the data needed to implement a hash table.
 */
// struct ht;
struct ht {
    struct list** array; 
    
};

/*
 * This function should allocate and initialize an empty hash table and
 * return a pointer to it.
 */
int size = 0;
int htable_size= 10;

struct ht* ht_create(){
    /*
     * FIXME: 
     */
    // struct ht* htable = (struct ht *)malloc(sizeof(struct ht)* htable_size);
    struct ht* htable = (struct ht **)malloc(sizeof(struct ht));

    htable->array = (struct list **)malloc(htable_size * sizeof(struct list * ));
    for(int i=0;i<htable_size;++i){
        // htable->array[i].head->key=list_create();
        htable->array[i]=NULL;

    }
    return htable;
}

/*
 * This function should free the memory allocated to a given hash table.
 * Note that this function SHOULD NOT free the individual elements stored in
 * the hash table.  That is the responsibility of the caller.
 *
 * Params:
 *   ht - the hash table to be destroyed.  May not be NULL.
 */
void ht_free(struct ht* ht){
    /*
     * FIXME: 
     */
    if(ht != NULL){
        if(ht->array != NULL){
            list_free(ht->array);
        }
    }
    free(ht);
}

/*
 * This function should return 1 if the specified hash table is empty and
 * 0 otherwise.
 *
 * Params:
 *   ht - the hash table whose emptiness is to be checked.  May not be
 *     NULL.
 *
 * Return:
 *   Should return 1 if ht is empty and 0 otherwise.
 */
int ht_isempty(struct ht* ht){
    /*
     * FIXME: 
     */
    // for ( int i=0 ; i< htable_size; i++){
    //     if(check_empty((ht->array)[i])!=NULL)
    //         return 0;
    // }
    if (size == 0){
        return 1;
    }
    return 0;

}


/*
 * This function returns the size of a given hash table (i.e. the number of
 * elements stored in it, not the capacity).
 */
int ht_size(struct ht* ht){
    /*
     * FIXME: 
     */
    return size;
}


/*
 * This function takes a key, maps it to an integer index value in the hash table,
 * and returns it. The hash algorithm is totally up to you. Make sure to consider
 * Determinism, Uniformity, and Speed when design the hash algorithm
 *
 * Params:
 *   ht - the hash table into which to store the element.  May not be NULL.
 *   key - the key of the element to be stored
 *   convert - pointer to a function that can be passed the void* key from
 *     to convert it to a unique integer hashcode
 */
int ht_hash_func(struct ht* ht, void* key, int (*convert)(void*)){
    /*
     * FIXME: 
     */
    int key_new = convert_int(key);
    return (key_new% htable_size);
    // return -1;
}


/*
 * This function should insert a given element into a hash table with a
 * specified key.  Note that you cannot have two same keys in one hash table.
 * If the key already exists, update the value associated with the key.  
 * This function is passed a function pointer that is used to convert the key (void*) 
 * to a unique hashcode (int). 
 * Resolution of collisions is requried, use either chaining or open addressing.
 * If using chaining, double the number of buckets when the load factor is >= 4
 * If using open addressing, double the array capacity when the load factor is >= 0.75
 * load factor = (number of elements) / (hash table capacity)
 *
 * Params:
 *   ht - the hash table into which to insert an element.  May not be NULL.
 *   key - the key of the element
 *   value - the value to be inserted into ht.
 *   convert - pointer to a function that can be passed the void* key from
 *     to convert it to a unique integer hashcode
 */

void ht_insert(struct ht* ht, void* key, void* value, int (*convert)(void*)){
    /*
     * FIXME: 
     */
    float load = 0.0;
    int key_new = convert_int(key);
    int index = ht_hash_func(ht,key,convert_int);

    list_insert(ht->array[index], key);
    ht->array[index]= key_new;
    // struct list *chain = (struct node*) ht->array[index]->head;

    // struct list * element = (struct node*) malloc(sizeof(struct node));
    // element -> key = key_new;
    // element -> val = value;
    // element -> next = ht->array[index]->head;

    // // ht->array[index].head
    // ht->array[index].head = element;
    size++;
    //load factor
    // return;
}


/*
 * This function should search for a given element in a hash table with a
 * specified key provided.   
 * This function is passed a function pointer that is used to convert the key (void*) 
 * to a unique hashcode (int). 
 * If the key is found, return the corresponding value (void*) of the element,
 * otherwise, return NULL
 *
 * Params:
 *   ht - the hash table into which to loop up for an element.  May not be NULL.
 *   key - the key of the element to search for
 *   convert - pointer to a function that can be passed the void* key from
 *     to convert it to a unique integer hashcode
 */
void* ht_lookup(struct ht* ht, void* key, int (*convert)(void*)){
    /*
     * FIXME: 
     */
    int key_new = convert_int(key);
    int index = ht_hash_func(ht,key,convert_int);

    list_position((ht->array)[index],(ht->array)[index],convert_int);
    // struct list** newnode =  (ht->array)[index];

    // while( newnode!=NULL){
    //     if(newnode->key == key_new){
    //         return newnode->val;
    //     }
    //     newnode = newnode->next;
    // }
    return NULL;
}


/*
 * This function should remove a given element in a hash table with a
 * specified key provided.   
 * This function is passed a function pointer that is used to convert the key (void*) 
 * to a unique hashcode (int). 
 * If the key is found, remove the element and return, otherwise, do nothing and return 
 *
 * Params:
 *   ht - the hash table into which to remove an element.  May not be NULL.
 *   key - the key of the element to remove
 *   convert - pointer to a function that can be passed the void* key from
 *     to convert it to a unique integer hashcode
 */
void ht_remove(struct ht* ht, void* key, int (*convert)(void*)){
    /*
     * FIXME: 
     */

    void* val = ht_lookup(ht,key,convert);
    if ( val != NULL){
        int key_new = convert_int(key);
        int index = ht_hash_func(ht,key,convert_int);
        list_remove(ht->array[index],val,convert_int);
    }
   
} 
