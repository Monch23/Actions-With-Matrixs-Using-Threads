#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct {
    int **data;
    size_t n;
} Matrix;

void *findMax(void *info) {
    Matrix *matrix = (Matrix*)info;
    int max = matrix->data[0][0];
    int i = 0, j = 0;

    while (i < matrix->n) {
        if (max < matrix->data[i][j]) {
            max = matrix->data[i][j];
        }

        if (++j % matrix->n == 0) {
            j = 0;
            ++i;
        }
    }
    printf("max = %d \n", max);
    return NULL;
}

void *findMin(void *info) {
    Matrix *matrix = (Matrix*)info;
    int min = matrix->data[0][0];
    int i = 0, j = 0;

    while (i < matrix->n) {
        if (min > matrix->data[i][j]) {
            min = matrix->data[i][j];
        }

        if (++j % matrix->n == 0) {
            j = 0;
            ++i;
        }
    }
    printf("min = %d \n", min);
    return NULL;
}

void *printInches(void *info) {
    Matrix *matrix = (Matrix*)info;
    int spaces = matrix->n;
    int i = 0, j = 0;

    putchar(10);

    while (i < matrix->n) {
        if (i == j || i + j == matrix->n - 1) {
            printf("%d  ", matrix->data[i][j]);
        } else {
            printf("   ");
        }

        if (++j % matrix->n == 0) {
            j = 0;
            ++i;
            putchar(10);
        }
    }

    return NULL;
}

void *average(void *info) {
    Matrix *matrix = (Matrix*)info;
    float average = 0;
    int i = 0, j = 0;

    while (i < matrix->n) {
        average += matrix->data[i][j];

        if (++j % matrix->n == 0) {
            j = 0;
            ++i;
        }
    }

    printf("average = %.2f \n", average / matrix->n);

    return NULL;
}

int main() {
    Matrix matrix;
    int flag = 0;
    pthread_t thr1, thr2, thr3, thr4;
    matrix.n = 3;
    matrix.data = malloc(sizeof(int*) * matrix.n);

    for (int i = 0, j = 0; i < matrix.n;) {
        if (!flag++) {
            matrix.data[i] = malloc(sizeof(int) * matrix.n);
        }
        scanf("%d", &matrix.data[i][j]);
        if (++j % matrix.n == 0) {
            j = 0;
            ++i;
            flag = 0;
        }
    }
    
    system("clear");

    pthread_create(&thr1, NULL, findMax, (void*)&matrix);
    pthread_create(&thr2, NULL, findMin, (void*)&matrix);
    pthread_create(&thr4, NULL, average, (void*)&matrix);
    pthread_join(thr1, NULL);
    pthread_join(thr2, NULL);
    pthread_join(thr4, NULL);
    pthread_create(&thr3, NULL, printInches, (void*)&matrix);
    pthread_join(thr3, NULL);

    for (int i = 0; i < matrix.n; ++i) {
        free(matrix.data[i]);
    }
    free(matrix.data);

    return 0;
}