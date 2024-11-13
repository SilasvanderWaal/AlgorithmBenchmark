#include "analyze.h"
#include "algorithm.h"

//
// Private
//
static int select_algorithm(algorithm_t* a)
{
    switch (*a)
    {
    case bubble_sort_t:
        return &bubble_sort;
        break;
    case insertion_sort_t:
        return &insertion_sort;
        break;
    case quick_sort_t:
        return &quick_sort;
        break;
    case linear_search_t:
        return &linear_search;
        break;
    case binary_search_t:
        return &binary_search;
        break;
    default:
        printf("Non-existing algorithm!");
        return -1;
        break;
    }
}

static int select_case(case_t* c)
{
    switch (*c)
    {
    case best_t:
        return ;
        break;
    case worst_t:
        return ;
        break;
    case average_t:
        return ;
        break;
    default:
        printf("Non-existing case!");
        return -1;
        break;
    }
}

//
// Public
//
void benchmark(const algorithm_t a, const case_t c, result_t *buf, int n)
{
    int (*alg)(int*, int) = select_algorithm(&a);
    int* selected_case = select_case(&c);

    //ITERATIONS IS CURRENTLY SET TO 4, SHOULD IT NOT BE 6?
    for (int i = 0; i < ITERATIONS; i++)
    {
        (*alg)(selected_case, (i + 1) * SIZE_START);
    }
}
