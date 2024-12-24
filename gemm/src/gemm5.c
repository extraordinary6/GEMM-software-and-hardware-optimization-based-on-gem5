// This file is a GEMM based on outer product
// Author: hcf

#include <stdio.h>
#include <time.h>

#define SIZE 128

// Outer product of two vectors
void outer_product(int A_col[SIZE], int B_row[SIZE], int C[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            C[i][j] += A_col[i] * B_row[j];
        }
    }
}

// Matrix multiplication A * B = C using outer product
void matmul_outer_product(int A[SIZE][SIZE], int B[SIZE][SIZE], int C[SIZE][SIZE]) {
	int A_col[SIZE];
	int B_row[SIZE];
	
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			A_col[j] = A[j][i];
			B_row[j] = B[i][j];
		}
		outer_product(A_col, B_row, C);
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
	
    // Perform matrix multiplication using outer product
    matmul_outer_product(A, B, C);
	
	// End timing
    clock_t end_time = clock();
	
	// Calculate elapsed time
    double time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    // Print result matrix C
    printf("GEMM based on outer product finished, took %f seconds!\n", time_taken);
    // print_matrix(C);

    return 0;
}