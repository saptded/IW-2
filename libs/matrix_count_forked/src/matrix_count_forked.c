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
    mat->cols_sum = (double *) calloc(mat->cols, sizeof(double));
    if (mat->cols_sum == NULL) {
        free(mat->matrix);
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

Matrix *create_matrix_from_file(FILE *ptr) {
    if (ptr == NULL) {
        return NULL;
    }

    Matrix *mat = (Matrix *) calloc(1, sizeof(Matrix));
    if (mat == NULL) {
        return NULL;
    }
    if (fscanf(ptr, "%zu %zu", &mat->rows, &mat->cols) != 2) {
        free(mat);
        return NULL;
    }
    mat->matrix = (double *) calloc(mat->rows * mat->cols, sizeof(double));
    if (mat->matrix == NULL) {
        free(mat);
        return NULL;
    }
    mat->cols_sum = (double *) calloc(mat->cols, sizeof(double));
    if (mat->cols_sum == NULL) {
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



//    for (size_t i = 0; i < mat->rows; i++) {
//        for (size_t j = 0; j < mat->cols; j++) {
//            if (fscanf(file, "%lf", &mat->data[i][j]) != 1) {
//                fclose(file);
//                free_matrix(mat);
//                return NULL;
//            }
//        }
//    }
//
//    fclose(file);

    return mat;

}

int print_matrix(Matrix *mat, FILE *ptr) {
    if (mat == NULL || ptr == NULL) {
        return -1;
    }

    fprintf(ptr, "%zu %zu\n", mat->rows, mat->cols);
    for (size_t i = 0; i < mat->rows; ++i) {
        for (size_t j = 0; j < mat->cols; ++j) {
            fprintf(ptr, "%3.2lf\t", mat->matrix[i * mat->cols + j]);
        }
        fprintf(ptr, "\n");
    }

    return 0;
}

int cols_sum(Matrix *mat) {
    if (mat == NULL) {
        return -1;
    }
    size_t max_forks = sysconf(_SC_NPROCESSORS_ONLN) / 2;

    size_t arr_size = sizeof(double) * mat->cols;
    double *shared_cols_sum = mmap(NULL, arr_size, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, 0, 0);
    if (shared_cols_sum == NULL) {
        return -1;
    }

    double col_sum = 0;
    pid_t pids[max_forks];
    for (size_t k = 0; k < max_forks; ++k) {
        pids[k] = fork();
        if (pids[k] == 0) {
            for (size_t i = k; i < mat->cols; i += max_forks) {
                for (size_t j = 0; j < mat->rows; ++j) {
                    col_sum += mat->matrix[j * mat->cols + i];
                }
                shared_cols_sum[i] = col_sum;
                col_sum = 0;
            }
            exit(1);
        }
    }

    for (size_t k = 0; k < max_forks; ++k) {
        waitpid(pids[k], 0, 0);
    }
    for (size_t i = 0; i < mat->cols; ++i) {
        mat->cols_sum[i] = shared_cols_sum[i];
    }

    munmap(shared_cols_sum, arr_size);
    return 0;
}

int print_cols_sum(Matrix *mat, FILE *ptr) {
    if (mat == NULL || ptr == NULL) {
        return -1;
    }

    for (size_t i = 0; i < mat->cols; ++i) {
        fprintf(ptr, "%3.2lf\n", mat->cols_sum[i]);
    }

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

