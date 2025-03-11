#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define MAX_SIZE 2000  // Maximum array size (1D array)

// Function to initialize array
void initialize_array(double A[MAX_SIZE], int N) {
    srand(time(0));
    for (int i = 0; i < N; i++) {
        A[i] = rand() % 10000 + 1;
    }
}

int main() {
    int sizes[] = {512, 1024, 2000};  // Different array sizes
    
    

        for (int s = 0; s < 3; s++) {
            int N = sizes[s];
            printf("\nArray Size: %d\n", N);

            static double A[MAX_SIZE];  // 1D array
            initialize_array(A, N);

        }
    

    return 0;
}
