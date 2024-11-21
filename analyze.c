#include "analyze.h"
#include "algorithm.h"
#include <bits/time.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//
// Private
//

//Creating a array with random values.
static void random_array(function_call_info* function_info)
{
    for (int i = 0; i < function_info->size; i++) {
        function_info->array[i] = (rand() % function_info->size);
    }
}

//Creating a array with decending values.
static void sorted_decending(function_call_info* function_info)
{
    for (int i = 0; i < function_info->size; i++) {
        function_info->array[i]  = (function_info->size - 1) - i;
    }
}

//Creating a array with ascending values.
static void sorted_ascending(function_call_info* function_info)
{
    for (int i = 0; i < function_info->size; i++) {
        function_info->array[i] = i;
    }
}

//Dynamicly creating a apropiate array for the algorithm that is going to be benchmarked.
static void create_array(function_call_info* function_info)
{
    int random_index;

    switch (function_info->case_type)
    {
    case best_t :    //All best cases use a ascending sorted array.
        sorted_ascending(function_info);
        function_info->search_value = SEARCH_VALUE;
        break;
    case worst_t :   //All worst cases use a decending sorted array, except binary search.
        if(function_info->algorithm_type == binary_search_t)
            sorted_ascending(function_info);
        else
            sorted_decending(function_info);
        function_info->search_value = -1;
        break;
    case average_t :      //All average cases use an array with random values, except binary search.
        random_index = rand() % function_info->size;

        if(function_info->algorithm_type == binary_search_t)
            sorted_ascending(function_info);
        else
            random_array(function_info);

        function_info->search_value = function_info->array[random_index];
        break;
    default:
        printf("Non-existing case!" );
        exit(EXIT_FAILURE);
        break;
    }

}

//Reverse the quick sort algorithm in a optimal case so that we can rig the array into the fastest execution.
static void quick_sort_reverse(int* array, int n){
    if(n <= 1){return;}

    int middle = (n - 1) / 2;

    //Swap the 2 values
    int buff = *(array);
    *(array) = *(array + middle);
    *(array + middle) = buff;

    quick_sort_reverse(array + 1, middle - 1);
    quick_sort_reverse((array + middle + 1), (n - middle - 1));
}

//Rig the array in such way we get the best execution time.
static void rig_array (function_call_info* function_info)
{
    if(function_info->case_type != best_t)     //If we dont want the best case, we dont want to rig the array
        return;

    switch (function_info->algorithm_type)
    {
    case linear_search_t :  //Best case for linear search is search value in index 0
        *(function_info->array) = function_info->search_value;
        break;
    case binary_search_t :  //Best case for binary search is search value at middle index
        *(function_info->array + (function_info->size / 2)) = function_info->search_value;
        break;
    case quick_sort_t:  //Best case for quick sort requires a reverse optimal case.
        quick_sort_reverse(function_info->array, function_info->size);
        break;
    default:
        break;
    }
}

//Passing the right address into the function pointer, as well as setting a indactor for search algorithm or not
static void select_algorithm(function_call_info* function_info)
{
    switch (function_info->algorithm_type)
    {
    case bubble_sort_t:
        function_info->sort_function_pointer = &bubble_sort;
        function_info->is_search_algorithm = false;
        break;
    case insertion_sort_t:
        function_info->sort_function_pointer = &insertion_sort;
        function_info->is_search_algorithm = false;
        break;
    case quick_sort_t:
        function_info->sort_function_pointer = &quick_sort;
        function_info->is_search_algorithm = false;
        break;
    case linear_search_t:
        function_info->search_function_pointer = &linear_search;
        function_info->is_search_algorithm = true;
        break;
    case binary_search_t:
        function_info->search_function_pointer = &binary_search;
        function_info->is_search_algorithm = true;
        break;
    default:
        perror("Non-existing algorithm!");
        exit(EXIT_FAILURE);
        break;
    }
}

//All the array preparation that is nessecary before running the algortihm
static void prepare_array(function_call_info* function_info){
    function_info->array = (int*)malloc(sizeof(int) * function_info->size);         //Allocating memory
    if (function_info->array == NULL){          //Check so memory allocation worked
        perror("Memory allocation failed, shutting down!");
        exit(EXIT_FAILURE);
    }
    create_array(function_info);
    rig_array(function_info);
}

//Loading in the right caches for better timings, this is done be running the algorithms without timing them
static void warmup(function_call_info* function_info){
    for (int i  = 0; i < ITERATIONS; i++) {
        prepare_array(function_info);
        if (function_info->is_search_algorithm == true)
            (*function_info->search_function_pointer)(function_info->array, function_info->size, function_info->search_value);
        else
            (*function_info->sort_function_pointer)(function_info->array, function_info->size);
        free(function_info->array);
    }
}

//Time the algorithm that we want to benchmark
static double time_algorithm(function_call_info* function_info){
    struct timespec start, end;
    double result = 0;

    warmup(function_info);

    for (size_t i = 0; i < ITERATIONS; i++){
        prepare_array(function_info);   //Prepare a new array before each timing

        //Call the function we are pointing to. Also measure the time it takes.
        if (function_info->is_search_algorithm) {
            clock_gettime(CLOCK_MONOTONIC, &start);
            (*function_info->search_function_pointer)(function_info->array, function_info->size, function_info->search_value);
            clock_gettime(CLOCK_MONOTONIC, &end);
        }else{
            clock_gettime(CLOCK_MONOTONIC, &start);
            (*function_info->sort_function_pointer)(function_info->array, function_info->size);
            clock_gettime(CLOCK_MONOTONIC, &end);
        }

        free(function_info->array);     //Make sure to free the memory used for the array

       double start_ns = start.tv_sec  + ((double) start.tv_nsec / 1000000000L);
       double stop_ns = end.tv_sec  + ((double) end.tv_nsec / 1000000000L);
       result += ((stop_ns - start_ns));
    }
    return ((result / ITERATIONS));     //We return a average of ITERATIONS timings for better accuracy
}

//
// Public
//

//Benchmark the algorithm with the right case,
void benchmark(const algorithm_t a, const case_t c, result_t *buf, int n){
    function_call_info function_info;
    srand(time(NULL));
    function_info.algorithm_type = a;   //Prepering the struct with the right values
    function_info.case_type = c;
    function_info.size = SIZE_START;
    select_algorithm(&function_info);   //Set the function pointer to the right algorithm

    //Loop over all the different sizes
    for (size_t i = 0; i < n; i++){
        (buf + i)->time = time_algorithm(&function_info);
        (buf + i)->size = function_info.size;
        function_info.size *= 2;
    }
}
