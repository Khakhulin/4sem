#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>
#include <pthread.h>


#define ERROR(message)      \
        do {                 \
            perror(message);  \
            exit(EXIT_FAILURE);\
        } while(0);

#define f(x) (x)

#define EPSILON (0.000001)
#define FROM     (-1000)
#define TO       ( 1000)


typedef struct data_main
        {
        long        numb_of_threads;
        long double epsilon;

        long double from;
        long double to;

        long double* arr_of_thread_numbs;
        } data_t;

long double simpsons_rule_formula  (long double left_end, long double right_end);
void* simpsons_rule_integral (void* thread_numb);


int main (int argc, char* argv[])
{
int i = 0;
long numb_of_threads = 0;

data_t* data_main = NULL;
long double result = 0;



errno = 0;
numb_of_threads = atoi(argv[1]);

data_main = (data_t*)calloc (1, sizeof (data_t) +
                                              sizeof (*(data_main->arr_of_thread_numbs)) * numb_of_threads);
if (data_main == 0)
        ERROR("calloc");

data_main->numb_of_threads = numb_of_threads;
data_main->epsilon        = EPSILON;
data_main->from            = FROM;
data_main->to              = TO;


data_main->arr_of_thread_numbs = (long double*)(data_main + 1);

for (i = 0; i < numb_of_threads; i++)
        data_main->arr_of_thread_numbs[i] = i;

pthread_t      thread_ids[numb_of_threads];

for (i = 0; i < numb_of_threads; i++)
      pthread_create (&thread_ids[i],
                                       NULL,
                                       simpsons_rule_integral,
                                       (data_main->arr_of_thread_numbs + i));



for (i = 0; i < numb_of_threads; i++)
        pthread_join (thread_ids[i], NULL);

for (i = 0; i < numb_of_threads; i++)
        result += data_main->arr_of_thread_numbs[i];

printf ("result = %Lf\n", result);

free (data_main); data_main = NULL;

return 0;
}


void* simpsons_rule_integral (void* thread_numb)
{
long double* num_ptr = (long double*)thread_numb;
long double  num     = *num_ptr;

long double i = 0;
long double th_from = 0, th_to = 0, epsilon = 0;
long double my_result = 0;


data_t* data_main = (data_t*)(num_ptr - (size_t)num) - 1;

if (num == 0)
        th_from = data_main->from;
else
        th_from  = (data_main->to - data_main->from) * num       / (data_main->numb_of_threads) + data_main->from;

if (num == (data_main->numb_of_threads - 1))
        th_to = data_main->to;
else
        th_to    = (data_main->to - data_main->from) * (num + 1) / (data_main->numb_of_threads) + data_main->from;

epsilon = data_main->epsilon;

for (i = th_from; i < th_to; i += epsilon)
        my_result += simpsons_rule_formula (i, i + epsilon);

*num_ptr = my_result;

pthread_exit (NULL);
}

long double simpsons_rule_formula (long double from, long double to){
    return ((to - from) / 6 * (f(from) + 4*f((from + to)/2) + f(to)));
}
