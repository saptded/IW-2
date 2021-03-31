#include "matrix_count.h"

#include <errno.h>
#include <string.h>


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

    mat->cols_sum = (double *) calloc(mat->cols, sizeof(double));
    if (mat->cols_sum == NULL) {
        free(mat->matrix);
        free(mat);
        return NULL;
    }

    for (size_t i = 0; i < rows * cols; ++i) {
        mat->matrix[i] = (double) rand() / RAND_MAX * 10;
    }

    return mat;
}

Matrix *create_matrix_from_file(const char *file_path) {
    if (file_path == NULL) {
        return NULL;
    }
    FILE *ptr = fopen(file_path, "r");
    if (ptr == NULL) {
        return NULL;
    }

    Matrix *mat = (Matrix *) calloc(1, sizeof(Matrix));
    if (mat == NULL) {
        fclose(ptr);
        return NULL;
    }

    if (fscanf(ptr, "%zu %zu", &mat->rows, &mat->cols) != 2) {
        fclose(ptr);
        free(mat);
        return NULL;
    }

    mat->matrix = (double *) calloc(mat->rows * mat->cols, sizeof(double));
    if (mat->matrix == NULL) {
        fclose(ptr);
        free(mat);
        return NULL;
    }
    mat->cols_sum = (double *) calloc(mat->cols, sizeof(double));
    if (mat->cols_sum == NULL) {
        fclose(ptr);
        free(mat->matrix);
        free(mat);
        return NULL;
    }

    for (size_t i = 0; i < mat->rows; i++) {
        for (size_t j = 0; j < mat->cols; j++) {
            if (fscanf(ptr, "%lf", &mat->matrix[i * mat->cols + j]) != 1) {
                delete_matrix(mat);
                return NULL;
            }
        }
    }

    fclose(ptr);
    return mat;
}

int print_matrix(const Matrix *mat, const char *file_path) {
    if (mat == NULL || file_path == NULL) {
        return -1;
    }

    FILE *ptr = fopen(file_path, "w+");
    if (ptr == NULL) {
        return -1;
    }

    fprintf(ptr, "%zu %zu\n", mat->rows, mat->cols);
    for (size_t i = 0; i < mat->rows; ++i) {
        for (size_t j = 0; j < mat->cols; ++j) {
            fprintf(ptr, "%3.2lf\t", mat->matrix[i * mat->cols + j]);
        }
        fprintf(ptr, "\n");
    }

    fclose(ptr);
    return 0;
}

int cols_sum(Matrix *mat) {
    if (mat == NULL) {
        return -1;
    }

    double col_sum = 0;
    for (size_t i = 0; i < mat->cols; ++i) {
        for (size_t j = 0; j < mat->rows; ++j) {
            col_sum += mat->matrix[j * mat->cols + i];
        }
        mat->cols_sum[i] = col_sum;
        col_sum = 0;
    }

    return 0;
}

int print_cols_sum(const Matrix *mat, const char *file_path) {
    if (mat == NULL || file_path == NULL) {
        return -1;
    }

    FILE *ptr = fopen(file_path, "w+");

    printf("%s", strerror(errno));
    if (ptr == NULL) {
        return -1;
    }

    for (size_t i = 0; i < mat->cols; ++i) {
        fprintf(ptr, "%3.2lf\n", *(mat->cols_sum + i));
    }

    fclose(ptr);
    return 0;
}

int delete_matrix(Matrix *mat) {
    if (mat == NULL) {
        return -1;
    }

    free(mat->cols_sum);
    free(mat->matrix);
    free(mat);

    return 0;
}
