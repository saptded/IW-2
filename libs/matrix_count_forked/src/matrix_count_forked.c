#include "matrix_count_forked.h"

Matrix *create_matrix(const size_t rows, const size_t cols) {
    Matrix *mat = (Matrix *) calloc(1, sizeof(Matrix));
    if (mat == NULL) {
        return NULL;
    }

    mat->matrix = (double *) calloc(rows * cols, sizeof(double));
    if (mat->matrix == NULL) {
        free(mat);
        return NULL;
    }
    mat->rows = rows;
    mat->cols = cols;

    for (size_t i = 0; i < rows * cols; ++i) {
        mat->matrix[i] = (double) rand() / RAND_MAX * 10;
    }

    return mat;
}

int print_matrix(Matrix *mat, FILE *ptr) {
    if (mat == NULL || ptr == NULL) {
        return -1;
    }

//    for (size_t i = 0; i < mat->cols; ++i) {
//        fprintf(ptr, "\t  %zu ", i);
//    }
//    fprintf(ptr, "\n");

    for (size_t i = 0; i < mat->rows; ++i) {
//        fprintf(ptr, "%zu\t", i);
        for (size_t j = 0; j < mat->cols; ++j) {
            fprintf(ptr, "%3.2f\t", mat->matrix[i * mat->cols + j]);
        }
        fprintf(ptr, "\n");
    }

    return 0;
}

int cols_sum(Matrix *mat) {
    if (mat == NULL) {
        return -1;
    }

    return 0;
}

int print_cols_sum(Matrix *mat, FILE *ptr) {
    if (mat == NULL || ptr == NULL) {
        return -1;
    }

    for (size_t i = 0; i < mat->cols; ++i) {
//        fprintf(ptr, "col sum %zu: ", i);
        fprintf(ptr, "%3.2f\n", mat->cols_sum[i]);
    }

    return 0;
}
