#include "matrix_count_forked.h"

Matrix *create_matrix(const size_t rows, const size_t cols) {
    Matrix *mat = (Matrix *) calloc(1, sizeof(Matrix));
    if (mat == NULL) {
        return NULL;
    }

    mat->rows = rows;
    mat->cols = cols;
    mat->matrix = (double *) mmap(NULL,
                                  sizeof(double) * mat->cols * mat->rows,
                                  PROT_READ | PROT_WRITE,
                                  MAP_SHARED | MAP_ANONYMOUS,
                                  0,
                                  0);
    if (mat->matrix == NULL) {
        free(mat);
        return NULL;
    }
    for (size_t i = 0; i < rows * cols; ++i) {
        mat->matrix[i] = (double) rand() / RAND_MAX * 10;
    }

    mat->cols_sum =
        (double *) mmap(NULL, sizeof(double) * mat->cols, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, 0, 0);
    if (mat->cols_sum == NULL) {
        free(mat->matrix);
        free(mat);
        return NULL;
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
    mat->matrix = (double *) mmap(NULL,
                                  sizeof(double) * mat->cols * mat->rows,
                                  PROT_READ | PROT_WRITE,
                                  MAP_SHARED | MAP_ANONYMOUS,
                                  0,
                                  0);
    if (mat->matrix == NULL) {
        fclose(ptr);
        free(mat);
        return NULL;
    }
    mat->cols_sum =
        (double *) mmap(NULL, sizeof(double) * mat->cols, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, 0, 0);
    if (mat->cols_sum == NULL) {
        fclose(ptr);
        munmap(mat->matrix, sizeof(double) * mat->cols * mat->rows);
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

    struct mymsgbuf {
        size_t mtype;
        size_t numb;
    };
    struct mymsgbuf qbuf = {1, 0};
    pid_t q_id = msgget(IPC_PRIVATE, IPC_CREAT | 0660);
    pid_t pid = fork();
    if (pid == 0) {
        for (size_t i = 0; i < mat->cols; ++i) {
            qbuf.numb = i;
            msgsnd(q_id, &qbuf, sizeof(size_t), 0);
        }
        exit(1);
    }

    size_t max_forks = sysconf(_SC_NPROCESSORS_ONLN);
    double col_sum = 0;
    pid_t pids[max_forks];
    for (size_t k = 0; k < max_forks; ++k) {
        pids[k] = fork();
        if (pids[k] == 0) {
            while (msgrcv(q_id, &qbuf, sizeof(size_t), qbuf.mtype, IPC_NOWAIT) == sizeof(size_t)) {
                for (size_t j = 0; j < mat->rows; ++j) {
                    col_sum += mat->matrix[j * mat->cols + qbuf.numb];
                }
                mat->cols_sum[qbuf.numb] = col_sum;
                col_sum = 0;
            }
            exit(1);
        }
    }

    waitpid(pid, 0, 0);
    for (size_t k = 0; k < max_forks; ++k) {
        waitpid(pids[k], 0, 0);
    }

    msgctl(q_id, IPC_RMID, NULL);
    return 0;
}

int print_cols_sum(const Matrix *mat, const char *file_path) {
    if (mat == NULL) {
        return -1;
    }
    FILE *ptr = fopen(file_path, "w+");
    if (ptr == NULL) {
        return -1;
    }

    for (size_t i = 0; i < mat->cols; ++i) {
        fprintf(ptr, "%3.2lf\n", mat->cols_sum[i]);
    }

    fclose(ptr);
    return 0;
}

int delete_matrix(Matrix *mat) {
    if (mat == NULL) {
        return -1;
    }

    munmap(mat->cols_sum, sizeof(double) * mat->cols);
    munmap(mat->matrix, sizeof(double) * mat->cols * mat->rows);
    free(mat);

    return 0;
}

