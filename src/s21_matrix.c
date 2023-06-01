#include "s21_matrix.h"

/*
@brief Проверка матрицы на валидность
@param *A
*/
int is_ok(matrix_t *A) {
  int res;
  if (A->rows >= 1 && A->columns >= 1 && A != NULL && A->matrix != NULL)
    res = 1;
  else
    res = 0;
  return res;
}

/*
@brief Выделение памяти под матрицу и ее создание
@param rows
@param columns
@param *result
*/
int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int res = 0;
  if (rows < 1 || columns < 1)
    res = 1;
  else {
    result->rows = rows;
    result->columns = columns;
    result->matrix = (double **)calloc(rows, sizeof(double *));
    if (result->matrix == NULL) {
      res = 1;
    } else {
      for (int i = 0; i < rows; i++) {
        result->matrix[i] = (double *)calloc(columns, sizeof(double));
        if (result->matrix[i] == NULL) {
          for (int j = 0; j < i; j++) {
            free(result->matrix[j]);
          }
          free(result->matrix);
          res = 1;
          break;
        }
      }
    }
  }
  return res;
}

/*
@brief Обнуление матрицы и освобождение памяти
@param *A
*/
void s21_remove_matrix(matrix_t *A) {
  if (A->matrix) {
    for (int i = 0; i < A->rows; i++) {
      if (A->matrix[i]) {
        free(A->matrix[i]);
        A->matrix[i] = NULL;
      }
    }
    free(A->matrix);
    A->matrix = NULL;
  }
  A->rows = 0;
  A->columns = 0;
}

/*
@brief Сравнение матриц
@param *A
@param *B
@return 1 - одинаковые
*/
int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int res = 0;
  if (is_ok(A) && is_ok(B)) {
    res = 0;
    if (A->rows == B->rows && A->columns == B->columns) {
      res = 1;
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          if (fabs(A->matrix[i][j] - B->matrix[i][j]) > 1e-6) {
            res = 0;
          }
        }
      }
    }
  }
  return res;
}

/*
@brief Сложение матриц
@param *A
@param *B
@param *result
*/
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = 1;
  if (is_ok(A) && is_ok(B)) {
    res = 2;
    if (A->rows == B->rows && A->columns == B->columns) {
      res = s21_create_matrix(A->rows, A->columns, result);
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
        }
      }
    }
  }
  return res;
}

/*
@brief Вычитание матриц
@param *A
@param *B
@param *result
*/
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = 1;
  if (is_ok(A) && is_ok(B)) {
    res = 2;
    if (A->rows == B->rows && A->columns == B->columns) {
      res = s21_create_matrix(A->rows, A->columns, result);
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
        }
      }
    }
  }
  return res;
}

/*
@brief Умножение матрицы на число
@param *A
@param number
@param *result
*/
int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int res = 1;
  if (is_ok(A)) {
    res = s21_create_matrix(A->rows, A->columns, result);
    if (res == 0) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] * number;
        }
      }
    }
  }
  return res;
}

/*
@brief Умножение одной матрицы на другую
@param *A
@param *B
@param *result
*/
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = 1;
  if (is_ok(A) && is_ok(B)) {
    if (A->columns == B->rows) {
      res = s21_create_matrix(A->rows, B->columns, result);
      if (res == 0) {
        for (int i = 0; i < A->rows; i++) {
          for (int j = 0; j < B->columns; j++) {
            for (int k = 0; k < B->rows; k++) {
              result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
            }
          }
        }
      }
    } else {
      res = 2;
    }
  }
  return res;
}

/*
@brief Транспонирование матрицы
@param *A
@param *result
*/
int s21_transpose(matrix_t *A, matrix_t *result) {
  int res = 0;
  if (is_ok(A)) {
    s21_create_matrix(A->columns, A->rows, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[j][i] = A->matrix[i][j];
      }
    }
  }
  return res;
}

/*
@brief Получение минора матрицы
@param row
@param column
@param *A
@param *result
*/
int s21_minor(int row, int column, matrix_t *A, matrix_t *result) {
  int res = 1;
  if (A->matrix != NULL) {
    res = s21_create_matrix(A->rows - 1, A->columns - 1, result);
    if (res == 0) {
      int a, b;
      for (int i = 0; i < A->rows; i++) {
        a = i;
        if (i > row - 1) a--;
        for (int j = 0; j < A->columns; j++) {
          b = j;
          if (j > column - 1) b--;
          if (i != row - 1 && j != column - 1)
            result->matrix[a][b] = A->matrix[i][j];
        }
      }
    }
  }
  return res;
}

/*
@brief Вычисление определителя матрицы, проверка на ошибки
@param *A
@param *result
*/
int s21_determinant(matrix_t *A, double *result) {
  int res = 1;
  if (is_ok(A)) {
    res = 2;
    if (A->rows == A->columns) {
      res = 0;
      *result = A->matrix[0][0];
      if (A->rows != 1) {
        *result = s21_determinant_part_2(A);
      }
    }
  }
  return res;
}

/*
@brief Вторая часть вычисления определителя, основная
@param *A
*/
double s21_determinant_part_2(matrix_t *A) {
  double res = 0;
  if (A->rows == 2) {
    res = A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
  } else {
    for (int i = 0; i < A->rows; i++) {
      matrix_t minor;
      s21_minor(1, i + 1, A, &minor);
      res += pow((-1), i) * A->matrix[0][i] * s21_determinant_part_2(&minor);
      s21_remove_matrix(&minor);
    }
  }
  return res;
}

/*
@brief Вычисления матрицы алгебраических дополнений, проверка на ошибки
@param *A
@param *result
*/
int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int res = 1;
  if (is_ok(A)) {
    res = 2;
    if (A->rows == A->columns) {
      res = s21_create_matrix(A->rows, A->columns, result);
      if (res == 0) {
        res = s21_calc_part_2(A, result);
      }
    }
  }
  return res;
}

/*
@brief вторая часть вычисления матрицы алгебраических дополнений, основная
@param *A
@param *result
*/
int s21_calc_part_2(matrix_t *A, matrix_t *result) {
  int res = 1;
  result->matrix[0][0] = 1;
  if (A->rows != 1) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        double determ;
        matrix_t minor;
        res = s21_minor(i + 1, j + 1, A, &minor);
        if (res == 0) {
          res = s21_determinant(&minor, &determ);
          if (res == 0) {
            result->matrix[i][j] = pow((-1), i + j) * determ;
          }
        }
        s21_remove_matrix(&minor);
      }
    }
  }
  return res;
}

/*
@brief Обратная матрица, отталкиваемся от определителя "determ"
@param *A
@param *result
*/
int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int res = 1;
  if (is_ok(A)) {
    res = 2;
    double determ;
    s21_determinant(A, &determ);
    if (fabs(determ - 0) > 1e-6) {
      matrix_t calc;
      res = s21_calc_complements(A, &calc);
      if (res == 0) {
        matrix_t transpose;
        res = s21_transpose(&calc, &transpose);
        if (res == 0) {
          s21_mult_number(&transpose, 1 / determ, result);
        }
        s21_remove_matrix(&transpose);
      }
      s21_remove_matrix(&calc);
    }
  }
  return res;
}