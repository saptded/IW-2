#ifndef IW_2_LIBS_MATRIX_COUNT_FORKED_INCLUDE_MATRIX_COUNT_FORKED_H_
#define IW_2_LIBS_MATRIX_COUNT_FORKED_INCLUDE_MATRIX_COUNT_FORKED_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct Matrix {
    double *matrix;
    double *cols_sum;
    size_t rows;
    size_t cols;
} Matrix;

Matrix *create_matrix(size_t rows, size_t cols);
int print_matrix(Matrix *mat, FILE *ptr);
int cols_sum(Matrix *mat);
int print_cols_sum(Matrix *mat, FILE *ptr);

#endif // IW_2_LIBS_MATRIX_COUNT_FORKED_INCLUDE_MATRIX_COUNT_FORKED_H_
