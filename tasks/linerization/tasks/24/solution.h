#pragma once

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef int32_t** Matrix;
typedef int32_t* Row;

typedef struct {
    size_t start;
    size_t end;
} Slice;

#define Sign(x, y) (y >= x) ? 1 : -1

void Swap(size_t* n, size_t* m) {
    size_t t = *n;
    *n = *m;
    *m = t;
}

// Заполняет массив числами по спирали, начиная с левого нижнего угла и двигаясь по часовой стрелке
void Fill(Matrix matrix, size_t n, size_t m) {
    int32_t element = 1;

    Slice vertical = {n - 1, 0};
    Slice horizontal = {m - 1, 0};

    int32_t is_horizontal = 0;
    int32_t sign = 0;

    while (element <= (int32_t)(n * m)) {
        if (is_horizontal) {
            sign = Sign(horizontal.start, horizontal.end);
            for (size_t j = horizontal.start; j != horizontal.end + sign; j += sign) {
                if (matrix[vertical.end][j] != 0) {
                    break;
                }
                matrix[vertical.end][j] = element++;
            }

            Swap(&vertical.start, &vertical.end);
            vertical.start += Sign(vertical.start, vertical.end);
        } else {
            sign = Sign(vertical.start, vertical.end);
            for (size_t i = vertical.start; i != vertical.end + sign; i += sign) {
                if (matrix[i][horizontal.end] != 0) {
                    break;
                }
                matrix[i][horizontal.end] = element++;
            }

            Swap(&horizontal.start, &horizontal.end);
            horizontal.start += Sign(horizontal.start, horizontal.end);
        }

        is_horizontal = !is_horizontal;
    }
}

void Linerization(Matrix matrix, Row lin_matrix, size_t n, size_t m) {
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < m; ++j) {
            lin_matrix[i * m + j] = matrix[i][j];
        }
    }
}

void PrintMatrix(Matrix matrix, size_t n, size_t m) {
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < m; ++j) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void PrintRow(Row row, size_t n) {
    for (size_t i = 0; i < n; ++i) {
        printf("%d ", row[i]);
    }
    printf("\n");
}

const size_t N = 6;
const size_t M = 9;

int Task() {
    size_t n = N;
    size_t m = M;
    // scanf("%lu%lu", &n, &m);

    // Инициализируем матрицу
    Row lin_matrix = (Row)calloc(n * m, sizeof(Row));
    Matrix matrix = (Matrix)calloc(n, sizeof(Row));
    for (size_t i = 0; i < n; ++i) {
        matrix[i] = (Row)calloc(m, sizeof(Row));
    }

    // Решаем задачу
    Fill(matrix, n, m);
    Linerization(matrix, lin_matrix, n, m);

    // Выводим результат
    PrintMatrix(matrix, n, m);
    printf("\n");
    PrintRow(lin_matrix, n * m);

    // Освобождаем память
    for (size_t i = 0; i < n; ++i) {
        free(matrix[i]);
    }
    free(matrix);
    free(lin_matrix);

    return 0;
}
