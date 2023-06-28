/* CS261- Recitation 1 - Q. 1*
 * Solution description: check the properties, like value and address, of pointer
 */
 
#include <stdio.h>
#include <stdlib.h>

void fooA(int* iptr){
     printf("The value pointed to iptr = %d\n",*iptr); /*Print the value pointed to by iptr*/
	
     printf("The address pointed to by iptr = %p",iptr);  /*Print the address pointed to by iptr*/	

     printf("\nAddress of iptr %p",&iptr);  /*Print the address of iptr itself*/	 
}

int main(){
    
   int x = 0; /*declare an integer x and initialize it with 0*/
   
   :printf("Address of *x = %p\n",&x); /*print the address of x*/
   
   fooA(&x); /*Call fooA() with the address of x*/
   
   printf("%d\n",x); /*print the value of x*/

   return 0;
}
