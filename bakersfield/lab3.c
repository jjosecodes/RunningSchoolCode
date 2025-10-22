#include <stdio.h>
#include <stdlib.h>

// Black box function prototypes
extern int registerme(int);
extern void startsort();
extern int compareballs(int, int);
extern void verifysort(int *);
extern void startmatch(int);
extern int fitsin(int i, int j);
extern void verifymatch(int *);

/**
 * @brief Sorts an array of ball indices using the merge sort algorithm.
 * * This function recursively divides the array and merges the sorted halves
 * by comparing balls using the compareballs() black box function.
 * @param S Array of ball indices to be sorted.
 * @param n The number of elements in the array.
 * @param ncall Pointer to an integer to count the black box calls.
 */
void mergesort(int *S, int n, int *ncall) {
    if (n <= 1) return;

    int m = n / 2;
    mergesort(S, m, ncall);
    mergesort(S + m, n - m, ncall);

    int *T = (int *)malloc(n * sizeof(int));
    int i = 0, j = m, k = 0;

    while (i < m && j < n) {
        ++(*ncall);
        if (compareballs(S[i], S[j]) < 0) {
            T[k++] = S[i++];
        } else {
            T[k++] = S[j++];
        }
    }

    while (i < m) {
        T[k++] = S[i++];
    }
    while (j < n) {
        T[k++] = S[j++];
    }

    for (k = 0; k < n; ++k) {
        S[k] = T[k];
    }
    free(T);
}

/**
 * @brief Wrapper function to initialize and start the merge sort process.
 * @param n The total number of balls.
 * @param ncall Pointer to an integer to count the black box calls.
 * @return A dynamically allocated array of sorted ball indices.
 */
int *sortballs(int n, int *ncall) {
    int i, *S;
    S = (int *)malloc(n * sizeof(int));
    for (i = 0; i < n; ++i) S[i] = i;
    mergesort(S, n, ncall);
    return S;
}

/**
 * @brief Sorts balls and boxes simultaneously using a randomized quicksort.
 * * This function uses the first ball S[0] as a pivot to partition both the
 * ball array S and the box array T.
 * @param S Array of ball indices.
 * @param T Array of box indices.
 * @param n The number of elements in the arrays.
 * @param ncall Pointer to an integer to count the black box calls.
 */
void quicksort1(int S[], int T[], int n, int *ncall) {
    if (n <= 1) return;

    int *SL, *SG, *TL, *TG;
    int i, l, g, P, cmpres;

    SL = (int *)malloc(n * sizeof(int));
    SG = (int *)malloc(n * sizeof(int));
    TL = (int *)malloc(n * sizeof(int));
    TG = (int *)malloc(n * sizeof(int));

    l = g = 0;
    for (i = 0; i < n; ++i) {
        ++(*ncall);
        cmpres = fitsin(S[0], T[i]);
        if (cmpres == 0) P = i;
        else if (cmpres > 0) TG[g++] = T[i];
        else TL[l++] = T[i];
    }

    l = g = 0;
    for (i = 1; i < n; ++i) {
        ++(*ncall);
        cmpres = fitsin(S[i], T[P]);
        if (cmpres > 0) SL[l++] = S[i];
        else SG[g++] = S[i];
    }

    for (i = 0; i < l; ++i) { S[i] = SL[i]; T[i] = TL[i]; }
    S[l] = S[0]; T[l] = T[P];
    for (i = 0; i < g; ++i) { S[l + 1 + i] = SG[i]; T[l + 1 + i] = TG[i]; }

    free(TL); free(TG); free(SL); free(SG);

    quicksort1(S, T, l, ncall);
    quicksort1(S + l + 1, T + l + 1, g, ncall);
}

/**
 * @brief Finds matching boxes for balls using quicksort1.
 * * This method does not depend on a pre-sorted array of balls.
 * @param n The total number of balls/boxes.
 * @param ncall Pointer to an integer to count the black box calls.
 * @return A dynamically allocated match array M where M[ball_index] = box_index.
 */
int *findmatch1(int n, int *ncall) {
    int *S, *T, *M, i;

    S = (int *)malloc(n * sizeof(int));
    T = (int *)malloc(n * sizeof(int));
    for (i = 0; i < n; ++i) S[i] = T[i] = i;
    
    quicksort1(S, T, n, ncall);

    M = (int *)malloc(n * sizeof(int));
    for (i = 0; i < n; ++i) M[S[i]] = T[i];

    free(S); free(T);
    return M;
}

/**
 * @brief Sorts boxes using a pre-sorted ball array to ensure best-case quicksort performance.
 *
 * This function uses the middle element of the sorted ball array S as a pivot,
 * which guarantees that the partitions of the box array T are balanced.
 * @param S Pre-sorted array of ball indices.
 * @param T Array of box indices to be sorted.
 * @param n The number of elements in the arrays.
 * @param ncall Pointer to an integer to count the black box calls.
 */
void quicksort2(int S[], int T[], int n, int *ncall) {
    if (n <= 1) return;

    int *TL, *TG;
    int m, i, l, g, P, cmpres;

    TL = (int *)malloc(n * sizeof(int));
    TG = (int *)malloc(n * sizeof(int));
    
    // Use the middle element of the sorted S array as the pivot.
    // This guarantees a balanced partition, achieving O(n log n) performance.
    m = n / 2;
    l = 0;
    g = 0;

    // Partition the box array T using the pivot ball S[m].
    for (i = 0; i < n; ++i) {
        ++(*ncall);
        cmpres = fitsin(S[m], T[i]);
        if (cmpres == 0) P = i;
        else if (cmpres < 0) TL[l++] = T[i];
        else TG[g++] = T[i];
    }
    
    // Reconstruct T with smaller elements, the pivot, and then larger elements.
    for (i = 0; i < l; ++i) T[i] = TL[i];
    // Place the pivot box in its correct sorted position.
    T[m] = T[P];
    for (i = 0; i < g; ++i) T[m + 1 + i] = TG[i];

    free(TL); free(TG);

    // Recursive calls on the sub-arrays.
    quicksort2(S, T, m, ncall);
    quicksort2(S + m + 1, T + m + 1, n - m - 1, ncall);
}

/**
 * @brief Finds matching boxes using the optimized quicksort2.
 * * This method uses the pre-sorted ball array S from Part 1 to guide the
 * partitioning of the box array T for optimal performance.
 * @param S The pre-sorted array of ball indices from sortballs().
 * @param n The total number of balls/boxes.
 * @param ncall Pointer to an integer to count the black box calls.
 * @return A dynamically allocated match array M.
 */
int *findmatch2(int S[], int n, int *ncall) {
    int *T, *M, i;

    T = (int *)malloc(n * sizeof(int));
    for (i = 0; i < n; ++i) T[i] = i;

    // Sort T using the pre-sorted S for effective partitioning.
    quicksort2(S, T, n, ncall);

    // Prepare the final matching array.
    M = (int *)malloc(n * sizeof(int));
    for (i = 0; i < n; ++i) M[S[i]] = T[i];

    free(T);
    return M;
}

int main() {
    int n = 1000000;
    int *S;
    int *M;
    int ncall;

    registerme(n);

    printf("\n+++ Sorting the balls...\n");
    startsort();
    ncall = 0;
    S = sortballs(n, &ncall);
    printf("    Number of black-box queries = %d\n", ncall);
    verifysort(S);

    printf("\n+++ Finding the matching boxes: Method 1...\n");
    startmatch(0);
    ncall = 0;
    M = findmatch1(n, &ncall);
    printf("    Number of black-box queries = %d\n", ncall);
    verifymatch(M);
    free(M);

    printf("\n+++ Finding the matching boxes: Method 2...\n");
    startmatch(1);
    ncall = 0;
    M = findmatch2(S, n, &ncall);
    printf("    Number of black-box queries = %d\n", ncall);
    verifymatch(M);
    free(M);

    free(S);
    
    exit(0);
}