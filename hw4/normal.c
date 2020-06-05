#include <stdio.h>
#include <stdlib.h>

#define MAX 1000

int result[MAX];

int main(void) {
    int **matrix;
    int *vector;

    matrix = malloc(sizeof(int *)*MAX);
    vector = malloc(sizeof(int)*MAX);

    for(int i=0;i < MAX; i++) {
        matrix[i] = malloc(sizeof(int)*MAX);
        for(int j = 0; j < MAX; j++) 
            matrix[i][j] = j;
    }
    for(int i=0; i < MAX; i++) 
        vector[i] = 1;

    for(int i=0; i < MAX; i++) {
        for(int j=0;j< MAX;j++)
            result[i] += matrix[i][j]*vector[j];
    }

    for(int i=0; i<10; i++) printf("%d : %d\n", i, result[i]);

}
