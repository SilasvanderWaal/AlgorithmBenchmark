#ifndef ANALYZE_H
#define ANALYZE_H

#define SIZE_START 512
#define ITERATIONS 7
#define MAX_SIZE 16384
#define SEARCH_VALUE 1337
#define NANO 10E9

#include <stdbool.h>

// algorithm_t defines different algorithms
typedef enum {
	bubble_sort_t,
	insertion_sort_t,
	quick_sort_t,
	linear_search_t,
	binary_search_t
} algorithm_t;

// case_t defines different cases
typedef enum {
	best_t,
	worst_t,
	average_t,
} case_t;

// result_t defines a timed measurement for a given array size
typedef struct {
	int size;
	double time;
} result_t;

typedef struct{
    void (*sort_function_pointer)(int*, int);
    bool (*search_function_pointer)(const int*, int, int);
    algorithm_t algorithm_type;
    case_t case_type;
    int* array;
    int size;
    bool is_search_algorithm;
    int search_value;
} function_call_info;

// benchmark benchmarks an algorithm a for a specific case c, writing n results
// to the result buffer buf
void benchmark(const algorithm_t a, const case_t c, result_t *buf, int n);

#endif
