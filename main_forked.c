#include "matrix_count_forked.h"

int main() {
    Matrix *mat = create_matrix_from_file("../matrix_data/matrix_10000_5000.txt");
    if (mat == NULL) {
        return -1;
    }

    if (cols_sum(mat) == -1) {
        return -1;
    }

    if (print_cols_sum(mat, "../matrix_data/matrix_forked.out") == -1) {
        return -1;
    }

    delete_matrix(mat);

    return 0;
}
