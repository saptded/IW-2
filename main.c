#include "matrix_count.h"

#include <time.h>

int main() {

    FILE *ptr = fopen("../matrix_data/matrix_10000_5000.txt", "r");
    FILE *ptr_2 = fopen("../matrix_data/matrix.out", "w+");

    Matrix *mat = create_matrix_from_file(ptr);
    if (mat == NULL) {
        return -1;
    }
//    print_matrix(mat, ptr_2);
//
    double start_time =  clock();
    if (cols_sum(mat) == -1) {
        return -1;
    }
    double end_time = clock();

    if (print_cols_sum(mat, ptr_2) == -1) {
        return -1;
    }

    fclose(ptr);
    fclose(ptr_2);
    delete_matrix(mat);

    double  search_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    printf("time: %2.4f", search_time);
    return 0;
}
