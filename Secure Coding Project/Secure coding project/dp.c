#include <stdio.h> 
#include <stdlib.h>  

int main()  
{  
   int *ptr = (int *)malloc(sizeof(int)); // Dynamically allocate memory
   if (ptr == NULL) {                    // Check for allocation failure
       printf("Memory allocation failed\n");
       return 1; // Exit with error
   }

   *ptr = 560; // Assign value to the allocated memory
   printf("Pointer value: %d\n", *ptr); // Access and print the value
   printf("Pointer addr val %ld",&ptr);

   free(ptr); // Free the allocated memory
   *ptr = 660; // Set pointer to NULL to avoid dangling pointer
   printf("Pointer value: %d\n", *ptr); // Memory gets re written and initial memory gets lost
   printf("Pointer addr val %ld",&ptr);

   return 0;  
}  
