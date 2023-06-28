#include <stdio.h>
 
void function (int *x, int n) {
    int i, t, j = n, s = 1;
    while (s) {
        s = 0;
        for (i = 1; i < j; i++) {
            if (x[i] < x[i - 1]) {
                t = x[i];
                x[i] = x[i - 1];
                x[i - 1] = t;
                s = 1;
            }
        }
        j--;
    }
}
 
int main () {
    int x[] = {15, 56, 12, -21, 1, 659, 3, 83, 51, 3, 135, 0};
    int n = sizeof(x) / sizeof(x[0]);
    int i;
    for (i = 0; i < n; i++)
        printf("%d%s", x[i], i == n - 1 ? "\n" : " ");
    function(x, n);
    for (i = 0; i < n; i++)
        printf("%d%s", x[i], i == n - 1 ? "\n" : " ");
    return 0;
}
// In this  function here we define int *x as an array and int n is the length of the array so we use s = 0 is false and s = 1 is true.
// so here this function is checking the number sequence like if the set of numbers in array are not arranged properly and  this function helps min function to arrange the numbers in ascending order.

