#ifndef IW_2_LIBS_STATIC_INCLUDE_MATRIX_COUNT_H_
#define IW_2_LIBS_STATIC_INCLUDE_MATRIX_COUNT_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct Matrix {
    double *matrix;
    double *cols_sum;
    size_t rows;
    size_t cols;
} Matrix;

Matrix *create_matrix(size_t rows, size_t cols);
Matrix *create_matrix_from_file(FILE *ptr);
int print_matrix(Matrix *mat, FILE *ptr);
int cols_sum(Matrix *mat);
int print_cols_sum(Matrix *mat, FILE *ptr);
int delete_matrix(Matrix *mat);

#endif // IW_2_LIBS_STATIC_INCLUDE_MATRIX_COUNT_H_
