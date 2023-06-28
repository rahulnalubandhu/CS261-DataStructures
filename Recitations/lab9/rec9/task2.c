#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


/*
 * return true (1) if n is happy, false (0) otherwise
 */
int divde_nd_square(int n){
    int sqr = 0;
    int mod;
    while(n>0){
        mod = n % 10;
        n = n / 10;
        sqr += (mod * mod);
    }
    return sqr;
}

bool isHappy(int n){
    
    int hashmap[10000] = {};
    
    if(n == 1)
        return true;
    while(true){
        n = divde_nd_square(n);
        if(n == 1)
            return true;
        if(hashmap[n] == -1)
            return false;
        hashmap[n]=-1;
    }
}

/*
 * Below are testing functions... DO NOT MODIFY!!!
 */

void show_result(int e, int r){
	printf("Expected: %d\nActual: %d...", e, r);
	if (r != e) 
        printf("FAIL\n\n\n");
    else 
        printf("OK\n\n\n");
}



int main()
{
	printf("\nTEST 1...19\n");
	show_result(1, isHappy(19));

	printf("\nTEST 2...2\n");
	show_result(0, isHappy(2));

	printf("\nTEST 3...7\n");
	show_result(1, isHappy(7));

	printf("\nTEST 4...176\n");
	show_result(1, isHappy(176));

	printf("\nTEST 5...36\n");
	show_result(0, isHappy(36));

	

	return 0;
}
