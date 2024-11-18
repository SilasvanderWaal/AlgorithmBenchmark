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
static void random_array(int* a)
{
    srand(time(NULL));
    for (int i = 0; i < MAX_SIZE; i++) {
        a[i] = (rand() % MAX_SIZE);
    }
}

static void sorted_decending(int* a)
{
    for (int i = 0; i < MAX_SIZE; i++) {
        a[i]  = (MAX_SIZE - 1) - i;
    }
}

static void sorted_ascending(int* a)
{
    for (int i = 0; i < MAX_SIZE; i++) {
        a[i] = i;
    }
}

//Passing the right address into the function pointer, as well as returning a indactor for search algorithm or not
static void select_algorithm(const algorithm_t* a, function_call_info* function_prep)
{
    switch (*a)
    {
    case bubble_sort_t:
        function_prep->sort_function_pointer = &bubble_sort;
        break;
    case insertion_sort_t:
        function_prep->sort_function_pointer = &insertion_sort;
        break;
    case quick_sort_t:
        function_prep->sort_function_pointer = &quick_sort;
        break;
    case linear_search_t:
        function_prep->search_function_pointer = &linear_search;
        break;
    case binary_search_t:
        function_prep->search_function_pointer = &binary_search;
        break;
    default:
        printf("Non-existing algorithm!");
        break;
    }
}

static bool is_search_algorithm(const algorithm_t *a)
{
    switch (*a)
    {
    case bubble_sort_t:
        return false;
    case insertion_sort_t:
        return false;
    case quick_sort_t:
        return false;
    case linear_search_t:
        return true;
    case binary_search_t:
        return true;
    default:
        printf("Non-existing algorithm!");
        break;
    }

    return false;
}

static void select_array(const case_t* c, const algorithm_t* a, int* array)
{
    switch (*c)
    {
    case best_t:
        sorted_ascending(array);
        break;
    case worst_t:
        sorted_decending(array);
        break;
    case average_t:
        random_array(array);
        break;
    default:
        printf("Non-existing case!" );
        break;
    }

}

static double time_algorithm(function_call_info* function_info)
{
    struct timespec start;
    struct timespec end;
    double results = 0;

    for (int i = 0; i < ITERATIONS; i++)
    {
        if (function_info->is_search_algorithm) {
            clock_gettime(CLOCK_MONOTONIC, &start);
            (*function_info->search_function_pointer)(function_info->array, function_info->size, function_info->search_number);
            clock_gettime(CLOCK_MONOTONIC, &end);
        }else{
            clock_gettime(CLOCK_MONOTONIC, &start);
            (*function_info->sort_function_pointer)(function_info->array, function_info->size);
            clock_gettime(CLOCK_MONOTONIC, &end);
        }

        results += (double)(end.tv_nsec - start.tv_nsec);
    }

    return (results / ITERATIONS);
}

//
// Public
//
void benchmark(const algorithm_t a, const case_t c, result_t *buf, int n)
{
    function_call_info function_prep;

    //Allocating memory for tha array
    function_prep.array = (int*)malloc(sizeof(int) * MAX_SIZE);

    //Preping the function arguments
    select_algorithm(&a, &function_prep);
    select_array(&c, &a, function_prep.array);
    function_prep.is_search_algorithm = is_search_algorithm(&a);

    for (int i = 0; i < n; i++)
    {
        function_prep.size = (i + 1) * SIZE_START;
        (buf+ i)->time = time_algorithm(&function_prep);
    }

    free(function_prep.array);
}
