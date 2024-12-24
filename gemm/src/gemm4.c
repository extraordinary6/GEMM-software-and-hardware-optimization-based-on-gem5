// This file is a GEMM based on loop unrolling
// Author: hcf

#include <stdio.h>
#include <time.h>

#define SIZE 128

// Matrix multiplication A * B = C
void matmul_loop_unroll(int A[SIZE][SIZE], int B[SIZE][SIZE], int C[SIZE][SIZE]) {
    int i, j, k;

    // Matrix multiplication operation
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            for (k = 0; k < SIZE; k=k+8) {
                C[i][j] += A[i][k] * B[k][j];
				C[i][j] += A[i][k+1] * B[k+1][j];
				C[i][j] += A[i][k+2] * B[k+2][j];
				C[i][j] += A[i][k+3] * B[k+3][j];
				
				C[i][j] += A[i][k+4] * B[k+4][j];
				C[i][j] += A[i][k+5] * B[k+5][j];
				C[i][j] += A[i][k+6] * B[k+6][j];
				C[i][j] += A[i][k+7] * B[k+7][j];
				
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
    matmul_loop_unroll(A, B, C);
	
	// End timing
    clock_t end_time = clock();
	
	// Calculate elapsed time
    double time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    // Print result matrix C
    printf("GEMM based on loop unrolling finished, took %f seconds!\n", time_taken);
    // print_matrix(C);

    return 0;
}
