//------------------
//////integral/////
//----------------

//сalculation the integral by simpson's rule
#include <stdio.h>
#include <math.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <pthread.h>

inline double f(double x){
    return x;
}
#define A (-2000.0)
#define B (2000.0)
#define EPSILON (0.000001)
#define ERROR(message)      \
        do {                 \
            perror(message);  \
            exit(EXIT_FAILURE);\
        } while(0);

inline double simpsons_formula(double from, double to){
    return ((to - from) / 6 * (f(from) + 4*f((from + to)/2) + f(to)));
}

typedef struct data_n {
    int thread_num;
    double epsilon;
    double from;
    double to;
    double *sum;
} data_t;

void* integral_func(void* thread_num);

int main(int argc, char* argv[]){
    if(argc != 2)
        ERROR("Num of threads");
    int num_threads = 0;
    int i = 0;
    double result = 0;
    num_threads = atoi(argv[1]);
    if(num_threads < 0)
        ERROR("Num of threads must be positive");
    data_t* data_main = NULL;
    data_main = (data_t*)calloc(1, sizeof(data_t) + sizeof(double) * num_threads);
    if(data_main == NULL)
        ERROR("Allocation memmory:")
    data_main->thread_num = num_threads;
    data_main->from = A;
    data_main->to = B;
    data_main->epsilon = EPSILON;
    data_main->sum = (double*)(data_main + 1);

    for(i = 0; i < num_threads; i++){
        data_main->sum[i] = i;
    }
    pthread_t thread_ids[num_threads];
    for(i = 0; i < num_threads; i++){
        pthread_create(&thread_ids[i], NULL, integral_func,  data_main->sum + i);
    }
    for(i = 0; i < num_threads; i++){
        pthread_join(thread_ids[i], NULL);//
    }


    for(i = 0; i < num_threads; i++){
        result += data_main->sum[i];
    }
    printf("Intergrate sum:%f\n", result);
    free(data_main);
    data_main = NULL;
    return 0;
}



void* integral_func(void* thread_num){

    double* num_ptr = (double*)thread_num;
    double num = *num_ptr;

    double i = 0;
    double th_from = 0, th_to = 0, th_epsilon = 0;
    double result = 0;

    data_t* data_main = (data_t*)(num_ptr - (size_t)num) - 1;

    th_from = (data_main->to - data_main->from) * num / (data_main->thread_num) + data_main->from;

    th_to = (data_main->to - data_main->from) * (num + 1) / (data_main->thread_num) + data_main->from;

    th_epsilon = data_main->epsilon;

    for(i = th_from; i < th_to; i += th_epsilon){
        result += simpsons_formula(i, i + th_epsilon);
    }

    *num_ptr = result;
    pthread_exit(NULL);
}
