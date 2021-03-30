#include "matrix_count.h"

int main() {
    Matrix *mat = create_matrix(10000, 5000);
    if (mat == NULL) {
        return -1;
    }

    print_matrix(mat, "../matrix_data/matrix_10000_5000.txt");

    delete_matrix(mat);
    return 0;
}
