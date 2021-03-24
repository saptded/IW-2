#include "matrix_count_forked.h"

#include <time.h>

int main() {
    double start_time =  clock();

    FILE *ptr = fopen("../matrix_data/matrix.txt", "r");
    FILE *ptr_2 = fopen("../matrix_data/matrix_forked.txt", "w+");

    Matrix *mat = create_matrix_from_file(ptr);
    if (mat == NULL) {
        return -1;
    }
    if (print_matrix(mat, ptr_2) == -1) {
        return -1;
    }
    fflush(ptr_2);

    if (cols_sum(mat) == -1) {
        return -1;
    }
    if (print_cols_sum(mat, ptr_2) == -1) {
        return -1;
    }

    fclose(ptr);
    delete_matrix(mat);

    double end_time = clock();
    double  search_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    printf("time: %2.2f", search_time);
    return 0;
}
