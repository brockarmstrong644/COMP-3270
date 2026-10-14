#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

void exchange(int A[], long i, long j) {
    int t = A[i]; A[i] = A[j]; A[j] = t;
}

long partition(int A[], long p, long r) {
    int x = A[r];
    long i = p - 1;
    for (long j = p; j <= r - 1; j++) {
        if (A[j] <= x) {
            i = i + 1;
            exchange(A, i, j);
        }
    }
    exchange(A, i + 1, r);
    return i + 1;
}

void quicksort(int A[], long p, long r) {
    if (p < r) {
        long q = partition(A, p, r);
        quicksort(A, p, q - 1);
        quicksort(A, q + 1, r);
    }
}

long long now_ns(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (long long)ts.tv_sec * 1000000000LL + ts.tv_nsec;
}

void demo(void) {
    int A[12];
    for (int i = 0; i < 12; i++) A[i] = rand() % 100;
    printf("Original array:");
    for (int i = 0; i < 12; i++) printf(" %d", A[i]);
    quicksort(A, 0, 11);
    printf("\nSorted array:  ");
    for (int i = 0; i < 12; i++) printf(" %d", A[i]);
    printf("\n");
}

void collectData(long L) {
    int *G = malloc(L * sizeof(int));
    int *A = malloc(L * sizeof(int));
    for (long k = 0; k < L; k++) G[k] = rand();
    FILE *F = fopen("quicksort_data.csv", "w");
    fprintf(F, "n,T(n)_ns,T(n)/n,T(n)/n^2,T(n)/(n*log2(n))\n");
    for (long n = 15000; n <= L; n += 2500) {
        memcpy(A, G, n * sizeof(int));
        long long start = now_ns();
        quicksort(A, 0, n - 1);
        long long end = now_ns();
        double T = (double)(end - start);
        fprintf(F, "%ld,%.0f,%.6f,%.12e,%.6f\n", n, T, T / n,
                T / ((double)n * n), T / (n * log2((double)n)));
    }
    fclose(F);
    printf("Data written to quicksort_data.csv\n");
}

int main(int argc, char *argv[]) {
    srand(time(NULL));
    demo();
    if (argc > 1 && strcmp(argv[1], "demo") == 0) return 0;
    collectData(1000000);
    return 0;
}