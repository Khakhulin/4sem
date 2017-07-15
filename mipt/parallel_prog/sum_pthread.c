#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>


#define LEN 10000000

pthread_mutex_t mutex;

int sum = 0;
int* array;

struct arg_th{
    int start;
    int finish;    
};

void* sum_elements(void* args){
    struct arg_th* data_of_th = (struct arg_th*)args;
    int start_index = data_of_th->start;
    int finish_index = data_of_th->finish;
    pthread_mutex_lock(&mutex);
        for (int i = start_index; i < finish_index; i++){
            sum += array[i];
        }
    pthread_mutex_unlock(&mutex);

}

int main(int argc, char* argv[]){
    if (argc < 2)
        exit(1);
    
    int N = atoi(argv[1]);
    pthread_t* thread_ids = (pthread_t*)malloc(N*sizeof(pthread_t));
    struct arg_th* arguments = (struct arg_th*)malloc(N*sizeof(struct arg_th));
    array = (int*)malloc(LEN*sizeof(int));
    pthread_mutex_init(&mutex, NULL);
    int len_part = LEN / N;
   
    for( int i =0; i < LEN; i++)
        array[i] = 1;

    for( int i =0; i < N; i++){
        if (i < N-1){
         arguments[i].start = i*len_part;
         arguments[i].finish = (i+1)*len_part;
        }
        else{
         arguments[N-1].start = arguments[N-2].finish;
         arguments[N-1].finish = LEN;
        }

    }

    for (int i = 0; i < N; i++ ){
        pthread_create(&thread_ids[i], NULL, sum_elements, &arguments[i]);
    }

    for (int i = 0; i < N; i++) {
        pthread_join(thread_ids[i], NULL);
    }
    
    
    printf("Sum  %d", sum);
    free(thread_ids);
    free(arguments);
    free(array);
}

