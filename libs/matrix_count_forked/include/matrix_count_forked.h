#ifndef IW_2_LIBS_MATRIX_COUNT_FORKED_INCLUDE_MATRIX_COUNT_FORKED_H_
#define IW_2_LIBS_MATRIX_COUNT_FORKED_INCLUDE_MATRIX_COUNT_FORKED_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <sys/msg.h>


typedef struct Matrix {
    double *matrix;
    double *cols_sum;
    size_t rows;
    size_t cols;
} Matrix;

Matrix *create_matrix(size_t rows, size_t cols);
Matrix *create_matrix_from_file(const char *file_path);
int print_matrix(const Matrix *mat, const char *file_path);
int cols_sum(Matrix *mat);
int print_cols_sum(const Matrix *mat, const char *file_path);
int delete_matrix(Matrix *mat);

#ifdef __cplusplus
}
#endif

#endif // IW_2_LIBS_MATRIX_COUNT_FORKED_INCLUDE_MATRIX_COUNT_FORKED_H_
