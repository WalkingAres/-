#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define MAX 1000


typedef struct mul_set
{
    int * vector_row;
    int * vector_col;
    int n;
    int result;
}mul_set;

typedef struct thread_argv
{
    int **mat;
    int *vector;
    int row;
    int size;
}targv;

int result[MAX];

/***
 *  将矩阵与向量乘积分解为 A的行向量与向量b相乘的结果
 *  eg. A*b = c (A为矩阵，b、c为向量) A=（a1，a2，a3，...，an) , b = (b1,b2,b3,...,bn)
 *  c=(c1,c2,c3,...cn) , ci= a1*b;
 * * */
void vector_mul(mul_set* A) {
    A->result = 0;
    for(int i=0;i < A->n; i++) {
        A->result += A->vector_row[i]*A->vector_col[i];
    }
}


void * thread_task(void * argv) {
    targv * p = (targv *) argv;
    mul_set A;
    for(int i=0; i < p->size; i++) {
        A.vector_row = p->mat[p->row+i];
        A.vector_col = p->vector;
        A.n = MAX;
        vector_mul(&A);
        result[p->row+i] = A.result;
    }
    return NULL;
}


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

    int thread_nums = 4;
    targv a[thread_nums];
    pthread_t t[thread_nums];
    int row = 0;
    int size = MAX/4;
    for(int i=0; i<thread_nums; i++) {
        a[i].mat = matrix;
        a[i].vector = vector;
        a[i].size = size;
        a[i].row = row;
        pthread_create(&t[i],NULL,thread_task,&(a[i]));
        printf("Thread(thread id): %d begin!\n", t[i]);
        row += size;
    }
    
    pthread_join(t[0],NULL);
    pthread_join(t[1],NULL);
    pthread_join(t[2],NULL);
    pthread_join(t[3],NULL);

    for(int i=0; i<MAX; i++) printf("%d : %d\n", i, result[i]);

    return 0;
}