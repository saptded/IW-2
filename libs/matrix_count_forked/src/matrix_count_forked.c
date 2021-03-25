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

    struct mymsgbuf {
        size_t mtype;
        size_t numb;
    };
    struct mymsgbuf qbuf = {1, 0};
    struct mymsgbuf qbuf1 = {1, 0};
    pid_t msgqid = msgget(IPC_PRIVATE, IPC_CREAT | 0660);
    struct msqid_ds buf;


    pid_t pid = fork();
    if (pid == 0) {
        for (size_t i = 0; i < 10; ++i) {
            qbuf.numb = i;
            msgsnd(msgqid, &qbuf, sizeof(size_t), 0);
        }
        exit(1);
    }

//    pid_t pids[8];
//    for (size_t k = 0; k < 8; ++k) {
//        pids[k] = fork();
//        if (pids[k] == 0) {
            for (size_t i = 0; i < 100; i += 1) {
//                msgctl(msgqid, IPC_STAT, &buf);
//                msg = (uint)(buf.msg_qnum);
//                if (msg == 0) {
//                    exit(1);
//                }
                msgrcv(msgqid, &qbuf1, sizeof(size_t), qbuf1.mtype, IPC_NOWAIT);
                printf("%zu fork: \n", qbuf1.numb);



            }
//            exit(1);
//        }
//    }

    waitpid(pid, 0, 0);
//    sleep(5);


    msgctl(msgqid, IPC_STAT, &buf);
//    uint msg = (uint)(buf.msg_qnum);

//    while (1) {
//        if (msg == 0) {
//            break;
//        }
//    }

//    for (size_t k = 0; k < 8; ++k) {
//        waitpid(pids[k], 0, 0);
//    }

//    pid_t pid1 = fork();
//    if (pid1 == 0) {
//        for (size_t i = 0; i < 10; ++i) {
//            msgrcv(msgqid, &qbuf1, 3, qbuf1.mtype, 0);
//            printf("%zu\n", qbuf1.numb);
//        }
//        exit(1);
//    }

//    for (size_t i = 0; i < 10; ++i) {
//        msgrcv(msgqid, &qbuf1, 3, qbuf1.mtype, 0);
//        printf("%zu\n", qbuf1.numb);
//    }
//    msgctl(msgqid, IPC_RMID, NULL);

//    _Atomic size_t acnt = 0;

//    struct mymsgbuf {
//        size_t mtype;
//        size_t numb;
//    };
//    struct mymsgbuf qbuf = {1, 0};
//    struct mymsgbuf qbuf1 = {1, 0};
//    pid_t msgqid = msgget(IPC_PRIVATE, IPC_CREAT | 0660);
////    struct msqid_ds buf;
//    for (size_t i = 0; i < 4900; ++i) {
//        qbuf.numb = i;
//        msgsnd(msgqid, &qbuf, 1, 0);
//    }
//
//    size_t max_forks = 1;
//
//    size_t arr_size = sizeof(double) * mat->cols;
//    double *shared_cols_sum = mmap(NULL, arr_size, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, 0, 0);
//    if (shared_cols_sum == NULL) {
//        return -1;
//    }
////    msgctl(msgqid, IPC_STAT, &buf);
////    uint msg;
//
//    double col_sum = 0;
//    pid_t pids[max_forks];
//    for (size_t k = 0; k < max_forks; ++k) {
//        pids[k] = fork();
//        if (pids[k] == 0) {
//            for (size_t i = k; i < 10000; i += 1) {
////            while((msg = (uint)(buf.msg_qnum)) != 0) {
//                msgrcv(msgqid, &qbuf1, 4, qbuf1.mtype, IPC_NOWAIT);
//                for (size_t j = 0; j < mat->rows; ++j) {
//                    col_sum += mat->matrix[j * mat->cols + qbuf1.numb];
//                }
//                printf("fork: %zu col: %zu col_sum: %3.2lf\n", k, qbuf1.numb, col_sum);
//                shared_cols_sum[qbuf1.numb] = col_sum;
//                col_sum = 0;
//            }
//            exit(1);
//        }
//    }
//
//    for (size_t k = 0; k < max_forks; ++k) {
//        waitpid(pids[k], 0, 0);
//    }
//    for (size_t i = 0; i < mat->cols; ++i) {
//        mat->cols_sum[i] = shared_cols_sum[i];
//    }
//
//    msgctl(msgqid, IPC_RMID, NULL);
//    munmap(shared_cols_sum, arr_size);
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

