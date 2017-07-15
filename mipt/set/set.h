#ifndef SET_H_
#define SET_H_
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>

typedef struct set_st{
    int* items;
    int num_items;
    int max_set_size;
} set_s;

typedef struct Iterator{
    set_s* set;
    int index;
    int begin;
    int end;
}iterator_s;

//create set
set_s *set_creator(size_t max_size);
//delete set
void set_delete(set_s *set);
//insert elements
int set_insert(set_s *set, int value);
//
int is_element_of(set_s *set, int value);
//is empty
int is_empty(set_s *set);
//return numbers elements of set
int set_size(set_s *set);
//print all elements in set
int set_dump(set_s *set);
// change max size of set
int set_resize(set_s* set,int new_max_size);
//remove element with value from set
int set_remove(set_s *set, int value);

//create a set iterator
iterator_s *set_iterator(set_s* set);
//return the value of the current index
int get_elem(iterator_s* iter);
//return 1 can advance
int iter_has_next(iterator_s* iter);
//
int get_next(iterator_s* iter);
//delete iterator
int delete_iter(iterator_s* iter);

int set_for_each(set_s* set, int (*foo)( int elem, void *data), void* data);

#endif
