#include "set.h"
#include <assert.h>
#include <string.h>


set_s *set_creator(size_t max_size) {

    set_s *set = NULL;
    set = (set_s*)calloc(1, sizeof(set_s));
    if (set == NULL){
        errno = ENOMEM;
        return NULL;
    }
    set->max_set_size = max_size;
    set->items = (int*)calloc(max_size,sizeof(int));
    if (set->items == NULL) {
        free(set);
        errno = ENOMEM;
        return NULL;
    }
    errno = 0;
    return set;
}

int set_size(set_s *set) {
    if (set == NULL) {
        errno = EINVAL;
        return -1;
    }
    return set->num_items;
}

int is_empty(set_s *set){
	if (set == NULL) {
        errno = EINVAL;
        return -1;
    }
    errno = 0;
	if (set->num_items != 0)
		return 0;
	else
		return 1;
}

void set_delete(set_s *set) {
    if (set == NULL) {
        errno = EINVAL;
        return ; //
    }
    free(set->items);
    free(set);
    errno = 0;
    return;
}

int set_insert(set_s *set, int value){
	if (set == NULL) {
		errno = EINVAL;
		return -1;
    }
    if (set->num_items  == set->max_set_size){
        errno = EADDRNOTAVAIL;
        return -1;
    }
    if (!is_element_of(set, value)) {
        set->items[set->num_items++] = value;
    }
    errno = 0;
    return 0;
}

int is_element_of(set_s *set, int value){
    if (set == NULL) {
		errno = EINVAL;
		return -1;
    }
    int i = 0;
    for(i = 0; i < set_size(set); i++){
        if (set->items[i] == value) {
            errno = 0;
            return 1;
        }
    }
    errno = 0;
    return 0;
}

int set_resize(set_s* set,int new_max_size){
    if(set == NULL){
        errno = EINVAL;
        return -1;
    }
    if(!new_max_size){
        errno = EINVAL;
        return -1;
    }
    int *temp = (int*)calloc(new_max_size,sizeof(int));
    if(temp == NULL){
        errno = ENOMEM;
        return -1;
    }
    memset(temp,0,new_max_size);
    int min = set->num_items;
    if(new_max_size < min){
        min = new_max_size;
        set->num_items = new_max_size;
    }
    int i = 0;
    for(i = 0; i < min; i++){
        temp[i] = set->items[i];
    }
    free(set->items);
    set->max_set_size = new_max_size;
    set->items = temp;
    errno = 0;
    return new_max_size;
}

int set_remove(set_s *set, int value){
    if(set == NULL){
        errno = EINVAL;
        return -1;
    }
    if(!is_element_of(set,value)){
        errno = EINVAL;
        return -1;
    }
    int i = 0, k = 0;
    int *temp = (int*)calloc(set->max_set_size,sizeof(int));
    if(temp == NULL){
        return -1;
    }
    for(i = 0; i < set->num_items; i++){
        if(set->items[i] != value)
            temp[k++] = set->items[i];
    }
    set->num_items--;
    free(set->items);
    set->items = (int*)temp;
    return 0;
}

int set_dump(set_s* set){
    if (set == NULL) {
		errno = EINVAL;
		return -1;
    }
    if (set->num_items != 0)
    {
        int i = 0;
        for(i = 0; i < set_size(set); i++){
            printf("%d\n",set->items[i]);
        }
    }
    return 0;
}

/////////////////////
////////////////////
///ITERATOR////////
//////////////////
/////////////////

iterator_s *set_iterator(set_s* set){
    if(set == NULL){
        errno = EINVAL;
        return NULL;
    }
    if(set->num_items == 0){
        errno = EINVAL;
        return NULL;
    }
    iterator_s* iter = (iterator_s*)calloc(1,sizeof(iterator_s));
    if(iter == NULL){
        errno = ENOMEM;
        return NULL;
    }
    iter->set = set;
    iter->begin = iter->set->items[0];
    int max_it = iter->set->num_items;
    iter->end = iter->set->items[max_it- 1];
    iter->index = 0;
    errno = 0;
    return iter;
}

int delete_iter(iterator_s* iter){
    if(iter == NULL){
        errno = EINVAL;
        return -1;
    }
    free(iter);
    errno = 0;
    return 0;
}

int iter_has_next(iterator_s* iter){
    if(iter == NULL){
        errno = EINVAL;
        return -1;
    }
    if((iter->set->num_items == 0) || (iter->index > iter->set->num_items))
        return 0;
    errno = 0;
    return 1;
}

int get_elem(iterator_s* iter){
    if(iter == NULL) {
		errno = EINVAL;
		return -1;
    }
    errno = 0;
    return iter->set->items[iter->index++];
}

int set_for_each(set_s* set, int (*foo)( int elem, void *data), void* data){
    if(set == NULL){
        errno = EBADR;
        return -1;
    }
    if(foo == NULL){
        errno = EBADR;
        return -1;
    }
    iterator_s* it = set_iterator(set);
    int i = 0;
    if (it == NULL ){
        errno = EFAULT;
        return -1;
    }
    int result = 0;
    do{
        i = get_elem(it);
        result = (*foo)(i, data);
        if(result < 0){
            errno = EINVAL;
            delete_iter(it);
            return -1;
        }
    }while(i != it->end);
    delete_iter(it);
    errno = 0;
    return 0;
}
