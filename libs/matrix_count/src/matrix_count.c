#include "matrix_count.h"

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
        mat->matrix[i] = (double)rand() / RAND_MAX * 100;
    }

    return mat;
}

int print_matrix(FILE *ptr, Matrix *mat) {
    if (ptr == NULL || mat == NULL) {
        return -1;
    }

    for (size_t i = 0; i < mat->cols; ++i) {
        fprintf(ptr, "\t  %zu ", i);
    }
    fprintf(ptr, "\n");
    for (size_t i = 0; i < mat->rows; ++i) {
        fprintf(ptr, "%zu\t", i);
        for (size_t j = 0; j < mat->cols; ++j) {
            fprintf(ptr, "%3.2f\t",mat->matrix[i * mat->cols + j]);
        }
        fprintf(ptr, "\n");
    }

    return 0;
}
