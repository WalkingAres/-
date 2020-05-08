#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

int global;

static int  s;

void * f1() {
    global = 1;
    return NULL; 
}

void *f2() {
    s = 2;
    for(int i=0; i <10 ; i++){
        printf("f2:%d\n",s);
        sleep(1);
    }
    return NULL;
}

void *f3() {
    s = 3;
    for(int i=0; i <10 ; i++){
        printf("f3:%d\n",s);
        sleep(1);
    }
    return NULL;
}

int main(void) {
    pthread_t t1, t2 , t3, t4;
    // pthread_create(&t1,NULL,f1,NULL);
    // pthread_create(&t2,NULL,f1,NULL);
    pthread_create(&t3,NULL,f2,NULL);
    pthread_create(&t4,NULL,f3,NULL);
    // pthread_join(t1,NULL);
    // pthread_join(t2,NULL);
    pthread_join(t3,NULL);
    pthread_join(t4,NULL);
    return 0;
}
