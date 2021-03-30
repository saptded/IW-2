#include <gtest/gtest.h>
#include <cstring>
#include <cmath>

#include "matrix_count.h"

TEST(create_matrix, create_matrix) {
    Matrix *mat = create_matrix(10, 10);

    EXPECT_TRUE(mat->matrix != nullptr);
    for (size_t i = 0; i < mat->rows; ++i) {
        for (size_t j = 0; j < mat->cols; ++j) {
            EXPECT_TRUE(mat->matrix[i * mat->cols + j] >= 0 && mat->matrix[i * mat->cols + j] <= 10);
        }
    }
    EXPECT_TRUE(mat->cols_sum != nullptr);
}

TEST(create_matrix_form_file, create_matrix_form_file) {
    Matrix *mat = create_matrix_from_file("../matrix_data/matrix_10_5.txt");

    EXPECT_TRUE(mat->matrix != nullptr);
    for (size_t i = 0; i < mat->rows; ++i) {
        for (size_t j = 0; j < mat->cols; ++j) {
            EXPECT_TRUE(mat->matrix[i * mat->cols + j] >= 0 && mat->matrix[i * mat->cols + j] <= 10);
        }
    }
    EXPECT_TRUE(mat->cols_sum != nullptr);
}

TEST(print_matrix, print_matrix) {
    Matrix *mat_exp = create_matrix(10, 5);

    print_matrix(mat_exp, "../matrix_data/test_mat.txt");

    Matrix *mat_got = create_matrix_from_file("../matrix_data/test_mat.txt");

    EXPECT_TRUE(mat_exp->rows == mat_got->rows);
    EXPECT_TRUE(mat_exp->cols == mat_got->cols);

    for (size_t i = 0; i < mat_exp->rows; ++i) {
        for (size_t j = 0; j < mat_exp->cols; ++j) {
            EXPECT_TRUE(
                std::fabs(mat_exp->matrix[i * mat_exp->cols + j] - mat_got->matrix[i * mat_got->cols + j]) < 0.01);
        }
    }
}

TEST(cols_sum, cols_sum) {
    Matrix *mat = create_matrix_from_file("../matrix_data/matrix_3_2.txt");
    cols_sum(mat);

    EXPECT_EQ(mat->cols_sum[0], 25.35);
    EXPECT_EQ(mat->cols_sum[1], 13.90);
}

//TEST(print_cols_sum, print_cols_sum) {
//    Matrix *mat = create_matrix_from_file("../matrix_data/matrix_10000_5000.txt");
//    cols_sum(mat);
//    print_cols_sum(mat, "../matrix_data/test_cols_sum.txt");
//
//    double col_sum = 0;
//    FILE *ptr = fopen("../matrix_data/test_cols_sum.txt", "r");
//
//    for (size_t i = 0; i < mat->cols; ++i) {
//        fscanf(ptr, "%lf", &col_sum);
//        EXPECT_TRUE(fabs(mat->cols_sum[i] - col_sum) < 0.01);
//    }
//
//    fclose(ptr);
//}

//TEST(time, time) {
//    Matrix *mat = create_matrix_from_file("../matrix_data/matrix_10000_5000.txt");
//
//    double general_time = 0;
//    double average_time;
//    double timer;
//
//    for (size_t i = 0; i < 5; ++i) {
//        timer = clock();
//        cols_sum(mat);
//        timer = clock() - timer;
//        general_time +=timer;
//    }
//    average_time = general_time / 5 / CLOCKS_PER_SEC;
//
//    FILE *ptr = fopen("../matrix_data/test_time.txt", "w+");
//    fprintf(ptr, "%lf", average_time);
//    fclose(ptr);
//}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
