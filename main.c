#include "matrix_count.h"

#include <time.h>

int main() {
    double start_time =  clock();

    FILE *ptr = fopen("../matrix_data/matrix.txt", "w+");

    Matrix *mat = create_matrix(3, 3);
    if (mat == NULL) {
        return -1;
    }
    if (print_matrix(mat, ptr) == -1) {
        return -1;
    }

    if (cols_sum(mat) == -1) {
        return -1;
    }
    if (print_cols_sum(mat, ptr) == -1) {
        return -1;
    }

    fclose(ptr);
    delete_matrix(mat);

    double end_time = clock();
    double  search_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    printf("time: %2.2f", search_time);
    return 0;
}
