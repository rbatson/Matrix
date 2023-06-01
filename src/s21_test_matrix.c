#include <check.h>
#include <stdio.h>

#include "s21_matrix.h"

#define SUCCESS 1
#define FAILURE 0
#define OK 0
#define ERROR 2

START_TEST(test_s21_create_matrix) {
  matrix_t A;
  int res = s21_create_matrix(4, 4, &A);
  ck_assert_int_eq(res, 0);
  s21_remove_matrix(&A);

  res = s21_create_matrix(-4, 4, &A);
  ck_assert_int_eq(res, 1);
  s21_remove_matrix(&A);

  res = s21_create_matrix(-4, 0, &A);
  ck_assert_int_eq(res, 1);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_s21_eq_matrix) {
  matrix_t A, B;
  s21_create_matrix(4, 4, &A);
  s21_create_matrix(4, 4, &B);
  int res = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(res, 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);

  res = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(res, 0);

  s21_create_matrix(4, 4, &A);
  s21_create_matrix(5, 4, &B);
  res = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(res, 0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);

  s21_create_matrix(4, 4, &A);
  s21_create_matrix(4, 4, &B);
  A.matrix[0][0] = 4;
  res = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(res, 0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);

  s21_create_matrix(4, 4, &A);
  s21_create_matrix(4, 4, &B);
  A.matrix[0][0] = 4;
  B.matrix[0][0] = 4;
  res = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(res, 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_s21_sum_matrix) {
  matrix_t A, B, res_my, res_org;
  s21_create_matrix(4, 4, &A);
  s21_create_matrix(4, 4, &B);
  s21_create_matrix(4, 4, &res_org);
  int res = s21_sum_matrix(&A, &B, &res_my);
  ck_assert_int_eq(res, 0);
  res = s21_eq_matrix(&res_my, &res_org);
  ck_assert_int_eq(res, 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&res_my);
  s21_remove_matrix(&res_org);

  s21_create_matrix(4, 5, &A);
  s21_create_matrix(4, 4, &B);
  res = s21_sum_matrix(&A, &B, &res_my);
  ck_assert_int_eq(res, 2);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);

  s21_create_matrix(4, 5, &A);
  s21_create_matrix(4, 4, &B);
  res = s21_sum_matrix(&A, &B, &res_my);
  ck_assert_int_eq(res, 2);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);

  s21_create_matrix(4, 4, &A);
  s21_create_matrix(4, 4, &B);
  s21_create_matrix(4, 4, &res_org);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      A.matrix[i][j] = i + j;
      res_org.matrix[i][j] = i + j;
    }
  }
  res = s21_sum_matrix(&A, &B, &res_my);
  ck_assert_int_eq(res, 0);
  res = s21_eq_matrix(&res_my, &res_org);
  ck_assert_int_eq(res, 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&res_my);
  s21_remove_matrix(&res_org);

  s21_create_matrix(4, 4, &A);
  s21_create_matrix(4, 4, &B);
  s21_create_matrix(4, 4, &res_org);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      A.matrix[i][j] = i + j;
      B.matrix[i][j] = i + j;
      res_org.matrix[i][j] = (i + j) * 2;
    }
  }
  res = s21_sum_matrix(&A, &B, &res_my);
  ck_assert_int_eq(res, 0);
  res = s21_eq_matrix(&res_my, &res_org);
  ck_assert_int_eq(res, 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&res_my);
  s21_remove_matrix(&res_org);
}
END_TEST

START_TEST(test_s21_sub_matrix) {
  matrix_t A, B, res_my, res_org;
  s21_create_matrix(4, 4, &A);
  s21_create_matrix(4, 4, &B);
  s21_create_matrix(4, 4, &res_org);
  int res = s21_sub_matrix(&A, &B, &res_my);
  ck_assert_int_eq(res, 0);
  res = s21_eq_matrix(&res_my, &res_org);
  ck_assert_int_eq(res, 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&res_my);
  s21_remove_matrix(&res_org);

  s21_create_matrix(4, 5, &A);
  s21_create_matrix(4, 4, &B);
  res = s21_sub_matrix(&A, &B, &res_my);
  ck_assert_int_eq(res, 2);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);

  s21_create_matrix(4, 4, &B);
  res = s21_sub_matrix(&A, &B, &res_my);
  ck_assert_int_eq(res, 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);

  s21_create_matrix(4, 4, &A);
  s21_create_matrix(4, 4, &B);
  s21_create_matrix(4, 4, &res_org);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      A.matrix[i][j] = i + j;
      res_org.matrix[i][j] = i + j;
    }
  }
  res = s21_sub_matrix(&A, &B, &res_my);
  ck_assert_int_eq(res, 0);
  res = s21_eq_matrix(&res_my, &res_org);
  ck_assert_int_eq(res, 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&res_my);
  s21_remove_matrix(&res_org);

  s21_create_matrix(4, 4, &A);
  s21_create_matrix(4, 4, &B);
  s21_create_matrix(4, 4, &res_org);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      A.matrix[i][j] = i + j;
      B.matrix[i][j] = i + j;
    }
  }
  res = s21_sub_matrix(&A, &B, &res_my);
  ck_assert_int_eq(res, 0);
  res = s21_eq_matrix(&res_my, &res_org);
  ck_assert_int_eq(res, 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&res_my);
  s21_remove_matrix(&res_org);
}
END_TEST

START_TEST(test_s21_mult_number) {
  matrix_t A, res_my, res_org;
  s21_create_matrix(4, 4, &A);
  s21_create_matrix(4, 4, &res_org);
  int res = s21_mult_number(&A, 5, &res_my);
  ck_assert_int_eq(res, 0);
  res = s21_eq_matrix(&res_my, &res_org);
  ck_assert_int_eq(res, 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&res_my);
  s21_remove_matrix(&res_org);

  s21_create_matrix(4, 4, &A);
  s21_create_matrix(4, 4, &res_org);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      A.matrix[i][j] = i + j;
      res_org.matrix[i][j] = (i + j) * (-3);
    }
  }
  res = s21_mult_number(&A, -3, &res_my);
  ck_assert_int_eq(res, 0);
  res = s21_eq_matrix(&res_my, &res_org);
  ck_assert_int_eq(res, 1);
  s21_remove_matrix(&res_my);
  s21_remove_matrix(&res_org);

  s21_create_matrix(4, 4, &res_org);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      A.matrix[i][j] = i + j;
    }
  }
  res = s21_mult_number(&A, 0, &res_my);
  ck_assert_int_eq(res, 0);
  res = s21_eq_matrix(&res_my, &res_org);
  ck_assert_int_eq(res, 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&res_my);
  s21_remove_matrix(&res_org);
}
END_TEST

START_TEST(test_s21_mult_matrix) {
  matrix_t A, B, res_mat, res_org;

  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);
  s21_create_matrix(2, 2, &res_org);
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      A.matrix[i][j] = i + j + 1;
      B.matrix[i][j] = i + j + 1;
    }
  }
  res_org.matrix[0][0] = 5;
  res_org.matrix[0][1] = 8;
  res_org.matrix[1][0] = 8;
  res_org.matrix[1][1] = 13;
  int res = s21_mult_matrix(&A, &B, &res_mat);
  ck_assert_int_eq(res, 0);
  res = s21_eq_matrix(&res_mat, &res_org);
  ck_assert_int_eq(res, 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&res_mat);
  s21_remove_matrix(&res_org);

  s21_create_matrix(3, 2, &A);
  s21_create_matrix(2, 2, &B);
  s21_create_matrix(3, 2, &res_org);
  res = s21_mult_matrix(&A, &B, &res_mat);
  ck_assert_int_eq(res, 0);
  res = s21_eq_matrix(&res_mat, &res_org);
  ck_assert_int_eq(res, 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&res_mat);
  s21_remove_matrix(&res_org);

  s21_create_matrix(2, 7, &A);
  s21_create_matrix(2, 2, &B);
  res = s21_mult_matrix(&A, &B, &res_mat);
  ck_assert_int_eq(res, 2);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_s21_transpose) {
  matrix_t A, res_mat, res_org;

  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &res_org);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 3;
  A.matrix[1][1] = 4;
  res_org.matrix[0][0] = 1;
  res_org.matrix[0][1] = 3;
  res_org.matrix[1][0] = 2;
  res_org.matrix[1][1] = 4;
  int res = s21_transpose(&A, &res_mat);
  ck_assert_int_eq(res, 0);
  res = s21_eq_matrix(&res_mat, &res_org);
  ck_assert_int_eq(res, 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&res_mat);
  s21_remove_matrix(&res_org);

  double matrix[2][2] = {
      {1, 2},
      {3, 4},
  };
  double ress[2][2] = {{1, 3}, {2, 4}};
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &res_org);
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      A.matrix[i][j] = matrix[i][j];
    }
  }
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      res_org.matrix[i][j] = ress[i][j];
    }
  }
  res = s21_transpose(&A, &res_mat);
  ck_assert_int_eq(res, 0);
  res = s21_eq_matrix(&res_mat, &res_org);
  ck_assert_int_eq(res, 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&res_mat);
  s21_remove_matrix(&res_org);
}
END_TEST

START_TEST(test_s21_determinant) {
  double result;
  matrix_t matrix1;
  matrix_t matrix2;
  matrix_t matrix3;
  s21_create_matrix(3, 3, &matrix1);
  s21_create_matrix(2, 6, &matrix2);
  s21_create_matrix(3, 3, &matrix3);
  matrix3.matrix[0][0] = 2;
  matrix3.matrix[0][1] = 5;
  matrix3.matrix[0][2] = 7;
  matrix3.matrix[1][0] = 6;
  matrix3.matrix[1][1] = 3;
  matrix3.matrix[1][2] = 4;
  matrix3.matrix[2][0] = 5;
  matrix3.matrix[2][1] = -2;
  matrix3.matrix[2][2] = -3;
  s21_determinant(&matrix1, &result);
  ck_assert_double_eq_tol(result, 0.0, 1e-6);
  s21_determinant(&matrix2, &result);
  ck_assert_double_eq_tol(result, 0.0, 1e-6);
  s21_determinant(&matrix3, &result);
  ck_assert_double_eq_tol(result, -1.0, 1e-6);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
  s21_remove_matrix(&matrix3);
}
END_TEST

START_TEST(test_s21_calc_complements) {
  double m[3][3] = {{1, 2, 3}, {0, 4, 2}, {5, 2, 1}};
  double r[3][3] = {{0, 10, -20}, {4, -14, 8}, {-8, -2, 4}};
  matrix_t matrix, res_org, res_my;
  s21_create_matrix(3, 3, &matrix);
  s21_create_matrix(3, 3, &res_org);
  for (int i = 0; i < matrix.rows; i++) {
    for (int j = 0; j < matrix.columns; j++) {
      matrix.matrix[i][j] = m[i][j];
    }
  }
  for (int i = 0; i < matrix.rows; i++) {
    for (int j = 0; j < matrix.columns; j++) {
      res_org.matrix[i][j] = r[i][j];
    }
  }
  int ret = s21_calc_complements(&matrix, &res_my);
  ck_assert_int_eq(ret, 0);
  ret = s21_eq_matrix(&res_org, &res_my);
  ck_assert_int_eq(ret, 1);
  s21_remove_matrix(&matrix);
  s21_remove_matrix(&res_my);
  s21_remove_matrix(&res_org);
}
END_TEST

START_TEST(test_s21_inverse_matrix) {
  double m[3][3] = {{2, 5, 7}, {6, 3, 4}, {5, -2, -3}};
  double r[3][3] = {{1, -1, 1}, {-38, 41, -34}, {27, -29, 24}};
  matrix_t matrix, res_org, res_my;
  s21_create_matrix(3, 3, &matrix);
  s21_create_matrix(3, 3, &res_org);
  for (int i = 0; i < matrix.rows; i++) {
    for (int j = 0; j < matrix.columns; j++) {
      matrix.matrix[i][j] = m[i][j];
    }
  }
  for (int i = 0; i < matrix.rows; i++) {
    for (int j = 0; j < matrix.columns; j++) {
      res_org.matrix[i][j] = r[i][j];
    }
  }
  int ret = s21_inverse_matrix(&matrix, &res_my);
  ck_assert_int_eq(ret, 0);
  ret = s21_eq_matrix(&res_org, &res_my);
  ck_assert_int_eq(ret, 1);
  s21_remove_matrix(&matrix);
  s21_remove_matrix(&res_my);
  s21_remove_matrix(&res_org);
}
END_TEST

Suite *s21_matrix_suite() {
  Suite *s = suite_create("s21_matrix_test");

  TCase *tc_s21_create_matrix = tcase_create("test_s21_create matrix");
  suite_add_tcase(s, tc_s21_create_matrix);
  tcase_add_test(tc_s21_create_matrix, test_s21_create_matrix);

  TCase *tc_s21_eq_matrix = tcase_create("test_s21_eq_matrix");
  suite_add_tcase(s, tc_s21_eq_matrix);
  tcase_add_test(tc_s21_eq_matrix, test_s21_eq_matrix);

  TCase *tc_s21_sum_matrix = tcase_create("test_s21_sum_matrix");
  suite_add_tcase(s, tc_s21_sum_matrix);
  tcase_add_test(tc_s21_sum_matrix, test_s21_sum_matrix);

  TCase *tc_s21_sub_matrix = tcase_create("test_s21_sub_matrix");
  suite_add_tcase(s, tc_s21_sub_matrix);
  tcase_add_test(tc_s21_sub_matrix, test_s21_sub_matrix);

  TCase *tc_s21_mult_number = tcase_create("test_s21_mult_number");
  suite_add_tcase(s, tc_s21_mult_number);
  tcase_add_test(tc_s21_mult_number, test_s21_mult_number);

  TCase *tc_s21_mult_matrix = tcase_create("test_s21_mult_matrix");
  suite_add_tcase(s, tc_s21_mult_matrix);
  tcase_add_test(tc_s21_mult_matrix, test_s21_mult_matrix);

  TCase *tc_s21_transpose = tcase_create("test_s21_transpose");
  suite_add_tcase(s, tc_s21_transpose);
  tcase_add_test(tc_s21_transpose, test_s21_transpose);

  TCase *tc_s21_determinant = tcase_create("test_s21_determinant");
  suite_add_tcase(s, tc_s21_determinant);
  tcase_add_test(tc_s21_determinant, test_s21_determinant);

  TCase *tc_s21_calc_complements = tcase_create("test_s21_calc_complements");
  suite_add_tcase(s, tc_s21_calc_complements);
  tcase_add_test(tc_s21_calc_complements, test_s21_calc_complements);

  TCase *tc_s21_inverse_matrix = tcase_create("test_s21_inverse_matrix");
  suite_add_tcase(s, tc_s21_inverse_matrix);
  tcase_add_test(tc_s21_inverse_matrix, test_s21_inverse_matrix);

  return s;
}

int main() {
  int fail = 0;

  Suite *s = s21_matrix_suite();

  SRunner *runner = srunner_create(s);

  srunner_run_all(runner, CK_NORMAL);
  fail = srunner_ntests_failed(runner);
  srunner_free(runner);

  return (fail == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}