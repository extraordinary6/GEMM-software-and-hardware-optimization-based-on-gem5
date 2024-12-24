// This file serves as the baseline GEMM
// Author: hcf

#include <stdio.h>
#include <time.h>

#define SIZE 128

// Matrix multiplication A * B = C
void matmul(int A[SIZE][SIZE], int B[SIZE][SIZE], int C[SIZE][SIZE]) {
    int i, j, k;

    // Matrix multiplication operation
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            for (k = 0; k < SIZE; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

// Printing matrix
void print_matrix(int matrix[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int A[SIZE][SIZE], B[SIZE][SIZE], C[SIZE][SIZE];
    
    // Initialization of A, B, C
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            A[i][j] = i + j;    
        }
    }
	
	for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) { 
            B[i][j] = i - j;  
        }
    }
	
	for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            C[i][j] = 0;
        }
    }

	// Start timing
    clock_t start_time = clock();
	
    // Perform matrix multiplication
    matmul(A, B, C);
	
	// End timing
    clock_t end_time = clock();
	
	// Calculate elapsed time
    double time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    // Print result matrix C
    printf("GEMM finished, took %f seconds!\n", time_taken);
    // print_matrix(C);

    return 0;
}
