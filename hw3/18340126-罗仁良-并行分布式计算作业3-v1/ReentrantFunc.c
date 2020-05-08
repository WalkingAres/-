#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

//=============  使用全局变量 ==============

int value = 1;

void *f1() {
    value = 4;
    return NULL;
}

//============= 使用堆 ==================

void *f2() {
    int *p = malloc(8*sizeof(int));
    for(int i=0; i < 8; i++) {
        p[i] = i;
    }
    return NULL;
}

//============= 调用不可重入函数 ============

void *f3() {
    f1();
    return NULL;
}

//============= 系统调用 I/O ==============

void *f4() {
    printf("stdio\n");
    return NULL;
}

//============ 返回全局变量 ================

void *f5() {
    return &value;
}
//============ 可重入函数 =================
void *f(){
    return NULL;
}

int fff(int a) {
    return a+1;
}



