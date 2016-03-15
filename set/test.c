#include <stdlib.h>
#include <time.h>
#include "set.h"
#include <sys/time.h>
#include <sys/resource.h>
#include <limits.h>

const unsigned int MAXELEM = 10000;
const unsigned int SIZE1=13;
const unsigned int SIZE3=10;
const unsigned int SIZE41=10;
const unsigned int SIZE42=20;
const unsigned int SIZE43=5;
const unsigned int SIZE5=1000000000;
int print(int item, void* data){
    printf("\t %d\n", item);
    return 0;
}
int untrue(int item, void* data){
    return -1;
}
int sqr(int item, void *data)
{
	  item = item*item;
	return 0;
}

int main(){
    set_s *set1 = NULL;
    unsigned int i = 0;
    int x = 0;
    int errors = 0;
    srand(time(NULL));
    int a[4] = {1, 2, 4, 5};
    set_s set_p = {a, 4, 10};
    set_s* set_test = &set_p;


    printf("********************\n" );
    printf("TES0\n");
    printf("Calloc Null\n");
    printf("********************\n" );
    struct rlimit r1;
    set_s* set = NULL;
    getrlimit(RLIMIT_AS, &r1);
    r1.rlim_cur = 0;
    //rlim.rlim_max = 10;
    if(setrlimit(RLIMIT_AS, &r1) < 0)
        perror("setrlimit:");
    set = set_creator(1000);
    if(set == NULL)
        errors++;
    printf("\tDone with %d errors\n",errors);
    errors = 0;
    if(set_for_each(set_test,(*sqr),NULL) < 0)
        errors++;
    printf("\tDone with %d errors\n",errors);
    errors = 0;
    if(set_remove(set_test,1) < 0)
        errors++;
    printf("\tDone with %d errors\n",errors);
    errors = 0;
    r1.rlim_cur =  RLIM_INFINITY;
    setrlimit(RLIMIT_AS, &r1);
    if(set == NULL)
        errors++;
    printf("\tDone with %d errors\n",errors);
    set_delete(set);


    printf("********************\n" );
    printf("TEST1::\n" );
    printf("********************\n" );
    set1 = set_creator(SIZE1 + 2);
    if(set1 == NULL) errors++;
    printf("\tDone with %d errors\n",errors);
    printf("Inserting\n" );
    for(i = 0; i < SIZE1; i++){
        x = rand()%MAXELEM;
        if(set_insert(set1,x) < 0)
            errors++;
    }
    printf("\tDone with %d errors\n",errors);
    errors = 0;
    printf("Inserting existing element\n" );
    if(set_insert(set1,10) < 0)
        errors++;
    if(set_insert(set1,10) < 0)
        errors++;
    printf("\tDone with %d errors\n",errors);
    errors = 0;
    printf("Dumping:\n" );
    if(set_dump(set1) < 0)
        errors++;
    printf("\tDone with %d errors\n",errors);
    errors = 0;

    if(set_insert(set1,MAXELEM + 1) < 0) errors++;
    for(i = 0; i < SIZE1; i++){
        if(is_element_of(set1,x = rand()%MAXELEM) < 0)
            errors++;
    }
    printf("\t Iterator::");
    if(set_for_each(set1,(*sqr), NULL) < 0) errors++;
    printf("Test of removing elemnt from set\n" );
    if(set_remove(set1,10) < 0)
        errors++;
    printf("\tDone with %d errors\n",errors);
    errors = 0;
    if(set_remove(set1,10) < 0)
        errors++;
    printf("\tDone with %d errors\n",errors);
    errors = 0;
    printf("Function with negative value\n");
    if(set_for_each(set1,(*untrue),NULL) < 0)
        errors++;
    printf("\tDone with %d errors\n",errors);
    set_delete(set1);
    printf("\tTest1 done \n");

    printf("********************\n" );
    printf("TEST2...\n" );
    printf("Zero set size. Working with empty set\n" );
    printf("********************\n" );
    errors = 0;
    printf("Creating...\n" );
    set_s* set2 = set_creator(0);
    if(set2 == NULL)
        errors++;
    printf("\tDone with %d errors\n",errors);
    errors = 0;
    printf("Inserting element\n");
    if(set_insert(set2, 10) < 0)
        errors++;
    perror("insert");
    printf("\tDone with %d errors\n",errors);
    errors = 0;
    printf("Removing\n");
    if(set_remove(set2, 10) < 0)
        errors++;
    printf("\tDone with %d errors\n",errors);
    errors = 0;
    printf("Iterator\n" );
    printf("LOG::: SET_NUM_UTEMS - %d\n",set2->max_set_size );
    if(set_for_each(set2, (*sqr), NULL) < 0)
        errors++;
    printf("\tDone with %d errors\n",errors);
    errors = 0;
    set_delete(set2);
    printf("TEST2 done\n");


    printf("********************\n" );
    printf("TEST3\n");
    printf("Null set.\n" );
    printf("********************\n" );
    errors = 0;
    if(set_insert(NULL,10) < 0)
        errors++;
    if(set_remove(NULL,10) < 0)
        errors++;
    if(set_dump(NULL) < 0)
        errors++;
    if(set_for_each(NULL,(*sqr),NULL) < 0)
        errors++;
    if(is_element_of(NULL,10) < 0)
        errors++;
    if(set_size(NULL) < 0)
        errors++;
    if(is_empty(NULL) < 0)
        errors++;
    if(set_resize(NULL,1) < 0)
        errors++;
    if(set_for_each(set1,NULL, NULL) < 0)
        errors++;
    iterator_s *it = NULL;
    if((it = set_iterator(NULL)) == NULL )
        errors++;
    if(get_elem(NULL) < 0)
        errors++;
    if(delete_iter(it) < 0)
        errors++;
    if(iter_has_next(NULL) < 0)
        errors++;
    set_delete(NULL);
    if(errno)
        errors++;
    printf("\tDone with %d errors\n",errors);
    errors = 0;


    printf("********************\n" );
    printf("TEST4\n");
    printf("Normal resize.Size1 = %d, Size2 = %d, Size3 = %d\n",SIZE41,SIZE42,SIZE43);
    printf("********************\n" );
    errors = 0;
    printf("Creating...\n" );
    set_s *set4 = set_creator(SIZE41);
    if(set4 == NULL)
        errors++;
    printf("Inserting %d elements...\n",SIZE41 );
    for(i = 0; i < SIZE41; i++){
        x = rand()%MAXELEM;
        if(set_insert(set4,x) < 0) errors++;
    }
    printf("\tDone with %d errors\n",errors);
    errors = 0;
    printf("Printing...\n" );
    if(set_for_each(set4,(*print), NULL) < 0)
        errors++;
    printf("\tDone with %d errors\n",errors);
    errors = 0;
    printf("Resizing %d to %d\n",SIZE41,SIZE42);
    if(set_resize(set4,SIZE42) < 0)
        errors++;
    printf("\tDone with %d errors\n",errors);
    errors = 0;
    printf("Printing...\n" );
    if(set_for_each(set4,(*print), NULL) < 0)
        errors++;
    printf("\tDone with %d errors\n",errors);
    errors = 0;
    printf("Resizing %d to %d\n",SIZE42,SIZE43);
    if(set_resize(set4,SIZE43) < 0)
        errors++;
    printf("\tDone with %d errors\n",errors);
    errors = 0;
    printf("Printing...\n" );
    if(set_for_each(set4,(*print), NULL) < 0)
        errors++;
    printf("\tDone with %d errors\n",errors);
    errors = 0;
    set_delete(set4);
    printf("TEST4 done\n");

    printf("********************\n" );
    printf("TEST5\n");
    printf("Memory limit\n");
    printf("********************\n" );
    struct rlimit r;
    r.rlim_cur = SIZE5;
    r.rlim_max = 2 * SIZE5;
    setrlimit(RLIMIT_AS, &r);
    errors = 0;
    printf("Creating with size = %d...\n", SIZE5*5);
    set1 = set_creator(SIZE5*5);
    if(set1 == NULL) errors++;
    printf("\tDone with %d errors\n",errors);
    errors = 0;
    set_delete(set1);
    printf("Creating with size = %d...\n", SIZE1);
    set1 = set_creator(SIZE1);
    if(set1 == NULL) errors++;
    printf("\tDone with %d errors\n",errors);
    errors = 0;
    printf("Settings %d elements...\n",SIZE1 );
    for(i = 0; i < SIZE1; i++){
        x = rand()%MAXELEM;
        if(set_insert(set1,x) < 0)
            errors++;
    }
    printf("\tDone with %d errors\n",errors);
    errors = 0;
    printf("Printing...\n" );
    if(set_for_each(set1,(*print), NULL) < 0)
        errors++;
    printf("\tDone with %d errors\n",errors);
    errors = 0;
    printf("Resizing set from %d to %d...\n", SIZE1, SIZE5*5);
    if(set_resize(set1,SIZE5*5) < 0)
        errors++;
    printf("\tDone with %d errors\n",errors);
    errors = 0;
    printf("\tDone with %d errors\n",errors);
    errors = 0;
    printf("Resizing set from %d to %d...\n", SIZE1, SIZE5/2);
    if(set_resize(set1,SIZE5/2) < 0)
        errors++;
    printf("\tDone with %d errors\n",errors);
    errors = 0;
    printf("Printing...\n" );
    if(set_for_each(set1,(*print), NULL) < 0)
        errors++;
    printf("\tDone with %d errors\n",errors);
    errors = 0;
    set_delete(set1);

    printf("********************\n" );
    printf("TEST6\n");
    printf("Resizing to zero size\n");
    printf("********************\n" );
    errors = 0;
    printf("Creating with %d size...\n", SIZE1);
    set1 = set_creator(SIZE1);
    if(set1 == NULL) errors++;
    printf("\tDone with %d errors\n",errors);
    errors = 0;
    printf("Settings %d elements...\n",SIZE1 );
    for(i = 0; i < SIZE1; i++){
        x = rand()%MAXELEM;
        if(set_insert(set1,x) < 0)
            errors++;
    }
    printf("\tDone with %d errors\n",errors);
    errors = 0;
    printf("Printing...\n" );
    if(set_for_each(set1,(*print), NULL) < 0)
        errors++;
    printf("\tDone with %d errors\n",errors);
    errors = 0;
    printf("Resizing set from %d to %d...\n", SIZE1, 0);
    if(set_resize(set1,0) < 0)
        errors++;
    printf("\tDone with %d errors\n",errors);
    errors = 0;
    set_delete(set1);


    return 0;
}
