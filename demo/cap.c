#include <stdio.h>
#include <math.h>
#include "cap.h"
double geo_c(double z, int n)
{
    double geo_sum = 0;
    int i;
    for (i=0; i<n; i++){
        /* pow(x,y) function raises x to the power of y - it is from <math.h> */
        geo_sum += pow(z,i);
     }
    return geo_sum;
}

int main() {
   // printf() displays the string inside quotation
   printf("Hello, World!\n");
   printf("%f",geo_c(0.5,100));
   return 0;
}