/* CS 261 Recitation 4: Anagram Detector
 */

#include <stdio.h>
#include <string.h> 
#include <stdlib.h>  
/*
  The Function checks two given strings (a, b) and return
  1 if they are anagram, and 0 otherwise
  Assuming:
  1. a and b are of the same length
  2. a and b are made up of symbols from the set of 26 lowercase characters
 */

int check_anagram(char *a, char *b)
{
  int achrctr[256] = {0}, bchrctr[256] = {0};
  int ctr;
   /* check the length of equality of Two Strings */
    if(strlen(a) != strlen(b))
    {
        return 0;
    }
    //count frequency of characters in a 
    for(ctr = 0; a[ctr] != '\0'; ctr++)
    {
        achrctr[a[ctr]]++;
    }
    //count frequency of characters in b 
    for(ctr = 0; b[ctr] != '\0'; ctr++)
    {
        bchrctr[b[ctr]]++;
    }
    //compare character counts of both strings 
    for(ctr = 0; ctr < 256; ctr++)
    {
        if(achrctr[ctr] != bchrctr[ctr])
            return 0;
    }
    return 1;
}


int main()
{
  char a[100], b[100];
   if(check_anagram(a, b) == 1)
  {
       a[strlen(a)-1] = '\0';
       b[strlen(b)-1] = '\0';

  printf("Test 1.....\n");
  printf("\"heart\", \"earth\"\n");
  printf("Expected: 1 \n");
  printf("Acutal: %d\n\n", check_anagram("heart", "earth"));


  printf("Test 2.....\n");
  printf("\"python\", \"typhon\"\n");
  printf("Expected: 1 \n");
  printf("Acutal: %d\n\n", check_anagram("python", "typhon"));

  printf("Test 3.....\n");
  printf("\"race\", \"care\"\n");
  printf("Expected: 1 \n");
  printf("Acutal: %d\n\n", check_anagram("race", "care"));

  printf("Test 4.....\n");
  printf("\"listen\", \"silent\"\n");
  printf("Expected: 1 \n");
  printf("Acutal: %d\n\n", check_anagram("listen", "silent"));

  printf("Test 5.....\n");
  printf("\"seal\", \"leaf\"\n");
  printf("Expected: 0 \n");
  printf("Acutal: %d\n\n", check_anagram("seal", "leaf"));

  printf("Test 6.....\n");
  printf("\"asdfghjkl\", \"aasdfghjk\"\n");
  printf("Expected: 0 \n");
  printf("Acutal: %d\n\n", check_anagram("asdfghjkl", "aasdfghjk"));
  }
 else
 {
       a[strlen(a)-1] = '\0';
       b[strlen(b)-1] = '\0';
       printf(" %s and %s are not Anagram.\n\n",a,b);
 }
    return 0;
}
 
 
