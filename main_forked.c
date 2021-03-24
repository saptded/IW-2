#include "matrix_count_forked.h"

int main() {
    FILE *ptr = fopen("../matrix_data/matrix_forked.txt", "w+");

    Matrix *mat = create_matrix(10, 5);
    if (mat == NULL) {
        return -1;
    }

    if (print_matrix(mat, ptr) == -1) {
        return -1;
    }
    fprintf(ptr, "\n");

//    if (cols_sum(mat) == -1) {
//        return -1;
//    }
//
//    if (print_cols_sum(mat, ptr) == -1) {
//        return -1;
//    }

    fclose(ptr);

    return 0;
}
