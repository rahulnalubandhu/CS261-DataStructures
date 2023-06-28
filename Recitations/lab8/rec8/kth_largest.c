#include <stdio.h>
#include <stdlib.h>
#define LEFT(i) (i << 1) + 1 //left child
#define RIGHT(i) (i << 1) + 2 // right child

struct heap{
    int heap_size;
    int* arr;
};

 void swap(int* a, int* b) { //swap 2 values inplace
    int temp = *a;
    *a = *b;
    *b = temp;
}

/* this is with O(log n) time complexity*/
 void max_heap(struct heap* h, int i) {  // heapify
    int l, r, max = i;

    l = LEFT(i); //
    r = RIGHT(i); //

    if (l < h->heap_size && h->arr[l] > h->arr[max]) // if left child is max 
        max = l; //assign max with left child 
    if (r < h->heap_size && h->arr[r] > h->arr[max]) // if right child is max
        max = r; // assign max with right child

    if (max != i) { // if max is not root
        swap(&h->arr[i], &h->arr[max]); // swap the root with max
        max_heap(h, max); // heapify the array
    }
}

/*this is with O(n) time complexity*/ 
static struct heap* build_max_heap(int* arr, int len) { // to build heap sort and sort the array
    struct heap* ret;
    int i;

    if ((ret = (struct heap*)malloc(sizeof(*ret))) == NULL)
        return NULL;

    ret->arr = arr;
    ret->heap_size = len;

    for (i = len / 2; i >= 0; i--)
        max_heap(ret, i); // heapify the array

    return ret;
}

int heap_extract_max(struct heap* h) { //heapsort swap
    int max;

    if (h->heap_size < 1)
        return -1;

    max = h->arr[0];
    h->arr[0] = h->arr[h->heap_size - 1]; // swap root with last elemnt
    h->heap_size--;
    max_heap(h, 0);//heapify the array
    
    return max;
}

int findKthLargest(int* nums, int numsSize, int k){
    struct heap* h;
    int i, ret;
    
    h = build_max_heap(nums, numsSize); // sort the array
    
    for(i = 0; i < k; i++)
        ret = heap_extract_max(h); // copy thge array
    
    free(h);
    
    return ret; //return largest elemnt
}

int main(int argc, char **argv)
{
    
    printf("\nTest 1...\n");
    int num1[6] = {3,2,1,5,6,4};
    printf("2nd largest in [3 2 1 5 6 4]\n");
    printf("Expected: 5\n");
    printf("Actual: %d\n", findKthLargest(num1, 6, 2));

    printf("\nTest 2...\n");
    int num2[9] = {3,2,3,1,2,4,5,5,6};
    printf("4th largest in [3 2 3 1 2 4 5 5 6]\n");
    printf("Expected: 4\n");
    printf("Actual: %d\n", findKthLargest(num2, 9, 4));


    printf("\nTest 3...\n");
    int num3[5] = {10,10,10,10,10};
    printf("5th largest in [10 10 10 10 10]\n");
    printf("Expected: 10\n");
    printf("Actual: %d\n", findKthLargest(num3, 5, 5));

    printf("\nTest 4...\n");
    int num4[7] = {-10,10,-10,10,-10,10,0};
    printf("4th largest in [-10 10 -10 10 -10 10 0]\n");
    printf("Expected: 0\n");
    printf("Actual: %d\n", findKthLargest(num4, 7, 4));

    printf("\nTest 5...\n");
    int num5[10] = {10,9,8,7,6,5,4,3,2,1};
    printf("1st largest in [10 9 8 7 6 5 4 3 2 1]\n");
    printf("Expected: 10\n");
    printf("Actual: %d\n", findKthLargest(num5, 10, 1));


    return 0;
}
