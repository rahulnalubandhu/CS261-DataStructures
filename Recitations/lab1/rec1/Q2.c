/* CS261- Recitation 1 - Q.2
 * Solution description: call the function foo using "reference" to see the values before and after the function
 */
 
#include <stdio.h>
#include <stdlib.h>

int foo(int* a, int* b, int c){
   *a = *a * 2; /*Set a to double its original value*/

   *b = *b/2; /*Set b to half its original value*/

    c = *a + *b; /*Assign a+b to c*/

    return c; /*Return c*/
    return 0;
}

int main(){
   int x = 7 , y = 8 , z = 9; /*Declare three integers x,y and z and initialize them to 7, 8, 9 respectively*/
	
    
   printf("x = %d y = %d z = %d\n",x,y,z); /*Print the values of x, y and z*/

   int D = foo(&x,&y,z); /*Call foo() appropriately, passing x,y,z as parameters*/

   printf("Value returned by foo =%d\n",D); /*Print the value returned by foo*/

   printf("x = %d y = %d z = %d\n",x,y,z); /*Print the values of x, y and z again*/

    /*Is the return value different than the value of z?  Why? */
    return 0;
}
    
/* The value given by foo() function is 18, but z remains the same 9. This is because there is no local function in foo() to perform function on z. here the a nd b values in foo function are considerd as values of x and y and c = *a+*b is carried out using x and y and stored in c so the z values remain unchanged hence it gives the same output.*/        
