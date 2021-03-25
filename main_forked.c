#include "matrix_count_forked.h"

#include <time.h>

int main() {

    FILE *ptr = fopen("../matrix_data/matrix_10_5.txt", "r");
    FILE *ptr_2 = fopen("../matrix_data/matrix_forked.out", "w+");

    Matrix *mat = create_matrix_from_file(ptr);
    if (mat == NULL) {
        return -1;
    }
//    print_matrix(mat, stdout);

    double start_time =  clock();
    if (cols_sum(mat) == -1) {
        return -1;
    }
    double end_time = clock();

//    if (print_cols_sum(mat, stdout) == -1) {
//        return -1;
//    }

    fclose(ptr);
    fclose(ptr_2);
    delete_matrix(mat);

    double  search_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    printf("time: %2.4f", search_time);
    return 0;
}
