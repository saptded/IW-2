#include <stdio.h>

#include "matrix_count.h"

int main() {
    Matrix *mat = create_matrix(10, 5);
    if (mat == NULL) {
        return -1;
    }

    print_matrix(stderr, mat);

    return 0;
}
