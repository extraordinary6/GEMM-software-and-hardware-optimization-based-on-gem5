// This file is a GEMM based on matrix partitioning and B-matrix transpose storage
// Author: hcf

#include <stdio.h>
#include <time.h>

#define SIZE 128
#define BLOCK_SIZE 32  // Use the sub block size of BLOCK_SIZE x BLOCK_SIZE

void matmul_block_transpose(int A[SIZE][SIZE], int B[SIZE][SIZE], int C[SIZE][SIZE]) {
    int i, j, k, ii, jj, kk;

    // Block matrix multiplication
    for (ii = 0; ii < SIZE; ii += BLOCK_SIZE) {
        for (jj = 0; jj < SIZE; jj += BLOCK_SIZE) {
            for (kk = 0; kk < SIZE; kk += BLOCK_SIZE) {
                for (i = ii; i < ii + BLOCK_SIZE && i < SIZE; i++) {
                    for (j = jj; j < jj + BLOCK_SIZE && j < SIZE; j++) {
                        for (k = kk; k < kk + BLOCK_SIZE && k < SIZE; k++) {
                            C[i][j] += A[i][k] * B[j][k];
                        }
                    }
                }
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
	
	for (int j = 0; j < SIZE; j++) {
        for (int i = 0; i < SIZE; i++) { 
            B[j][i] = i - j;  
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
    matmul_block_transpose(A, B, C);
	
	// End timing
    clock_t end_time = clock();
	
	// Calculate elapsed time
    double time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    // Print result matrix C
    printf("GEMM based on both methods finished, took %f seconds!\n", time_taken);
    // print_matrix(C);

    return 0;
}
