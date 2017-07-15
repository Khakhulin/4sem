#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>


void *test_pthread(void* a){
    printf("---------------\n");
    int a_2 = (*(int*)a);
    printf("num of thread :: %d\n", a_2);
    printf("---------------\n");
    pthread_exit(NULL);
}

int main(int argc, char* argv[]){
    int count_p = 0;
    int num = 0;
    num = atoi(argv[1]);
    while (count_p < num) {
        pthread_t th_id;
        int *val;
        if(pthread_create(&th_id, NULL, test_pthread, (void*)&count_p) < 0)
            printf("Error in creating pthread %d\n",count_p);
        else{
            pthread_join(th_id, (void**)&val);
            count_p++;
        }
    }
    return 0;
}
