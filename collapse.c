#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define MAX_SIZE 2000  // Max matrix size

// Function to initialize matrix
void initialize_matrix(double A[MAX_SIZE][MAX_SIZE], int N) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            A[i][j] = (i + j) * 0.01;
}

// **Loop Interchange (Optimized for Cache Locality)**
void loop_interchange_c(double A[MAX_SIZE][MAX_SIZE], double B[MAX_SIZE][MAX_SIZE], int N) {
    double start = omp_get_wtime();
    
    #pragma omp parallel for collapse(2)
    for (int j = 0; j < N; j++) {   // Interchanged loop order (column major)
        for (int i = 0; i < N; i++) {
            A[i][j] += B[i][j];
        }
    }

    double end = omp_get_wtime();
    printf("Loop Interchange  coloum Time: %.6f sec\n", end - start);
}

// **Row-Major (Baseline for Comparison)**

void loop_interchange_r(double A[MAX_SIZE][MAX_SIZE], double B[MAX_SIZE][MAX_SIZE], int N) {
    double start = omp_get_wtime();
    
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < N; i++) {   // Interchanged loop order (row major)
        for (int j = 0; j < N; j++) {
            A[i][j] += B[i][j];
        }
    }

    double end = omp_get_wtime();
    printf("Loop Interchange row Time: %.6f sec\n", end - start);
}

void collapse(double A[MAX_SIZE][MAX_SIZE], double B[MAX_SIZE][MAX_SIZE], int N) {
    double start = omp_get_wtime();

    #pragma omp parallel for collapse(2)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] += B[i][j];
        }
    }

    double end = omp_get_wtime();
    printf("collapse Time: %.6f sec\n", end - start);
}

int main() {
    int sizes[] = {512, 1024, 2000};  // Test different array sizes
    int num_threads[] = {1, 4, 8};    // Test different thread counts

    for (int t = 0; t < 3; t++) {
        omp_set_num_threads(num_threads[t]);
        printf("\n--- Testing with %d Threads ---\n", num_threads[t]);

        for (int s = 0; s < 3; s++) {
            int N = sizes[s];
            printf("\nMatrix Size: %d x %d\n", N, N);

            static double A[MAX_SIZE][MAX_SIZE], B[MAX_SIZE][MAX_SIZE];
            initialize_matrix(A, N);
            initialize_matrix(B, N);

            
            loop_interchange_c(A, B, N);
            loop_interchange_r(A, B, N);
            collapse(A, B, N);
        }
    }

    return 0;
}