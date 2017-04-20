#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>
#include <string.h>

//void merge_sort(int* leftArr, int* rightArr, int left_point, int right_point);
//void merge(int* sortArr, int* resArr, int left_point, int right_point, int middle_point);

void merge(int *, int *, int, int, int);
void merge_sort(int *, int *, int, int);

int main(int argc, char* argv[]){
    if (argc < 2)
        exit(EXIT_FAILURE);
    int n = atoi(argv[1]);


    srand(time(NULL));
    /***Populate the unsorted array***/
    int* ordinary_array = NULL;
    ordinary_array = (int*)malloc(sizeof(int)  * n);
    for (int i  = 0; i < n; i++){
            ordinary_array[i] = rand() % n;
    }
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0){
        for (int i  = 0; i < n; i++)
            printf("|%d|", ordinary_array[i]);
    }
    printf("\n");

    int size_of_chunk = n / size;
    /***Divide our array to all proccess ***/
    /** Mpi Scatter send buffer to all proc ex:
                [ABC]       [A]
                []   -->    [B]
                []          [C]
    **/

    int* sub_array = (int*)malloc(sizeof(int) * size_of_chunk);
    MPI_Scatter(ordinary_array, size_of_chunk, MPI_INT, sub_array, size_of_chunk, MPI_INT, 0, MPI_COMM_WORLD);
    /**each proccess should sort its part of array**/
    int* temp_buf_of_proc = (int*)malloc(sizeof(int) * size_of_chunk);
    merge_sort(sub_array, temp_buf_of_proc, 0, size_of_chunk-1);


    /**merge into one proccess 
                [A]       [ABC]
                [B]   -->    []
                [C]          []     
    **/
    int* sorted_array = NULL;
    if (rank == 0){
        sorted_array = (int*)malloc(sizeof(int) * n);
        memset(sorted_array, 0, sizeof(sorted_array));
    }

    MPI_Gather(sub_array, size_of_chunk, MPI_INT, sorted_array, size_of_chunk ,MPI_INT, 0, MPI_COMM_WORLD);

    if(rank == 0){
        printf("This is the sorted array: ");
        int* other_array = calloc(n,sizeof(int));

        merge_sort(sorted_array, other_array, 0, n-1);
        for (int i = 0; i < n; i++) {
            printf("|%d|", sorted_array[i]);
        }
        printf("\n");

        free(other_array);
        free(sorted_array);
        free(ordinary_array);

    }
    free(sub_array);
    free(temp_buf_of_proc);
    
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize();

}

void merge_sort(int* leftArr, int* rightArr, int left_point, int right_point){
    int middle_point = 0;    
    if (left_point < right_point) {
        middle_point = (left_point + right_point) / 2;
        merge_sort(leftArr, rightArr, left_point, middle_point);
        merge_sort(leftArr, rightArr, middle_point + 1, right_point);
        merge(leftArr, rightArr, left_point, middle_point, right_point);
    }    

}

void merge(int *to_sort, int *temp_arr, int l, int m, int r) {
    
    int global_iterator, k;
    int iter1 = l;
    global_iterator = l;
    int iter2 = m + 1;
    
    while((iter1 <= m) && (iter2 <= r)) {
        
    if(to_sort[iter1] <= to_sort[iter2]) {
            temp_arr[global_iterator] = to_sort[iter1];
            iter1++;
        }
        else {
            temp_arr[global_iterator] = to_sort[iter2];
            iter2++;
            
        }
        global_iterator++;
    }
        
    if(m < iter1) {
        for(k = iter2; k <= r; k++) {
            temp_arr[global_iterator] = to_sort[k];
            global_iterator++;
            }
        }
        
    else {
        for(k = iter1; k <= m; k++) {
            temp_arr[global_iterator] = to_sort[k];
            global_iterator++;
            }
        }
    for(k = l; k <= r; k++) 
        to_sort[k] = temp_arr[k];
        
    }
