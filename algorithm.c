#include "algorithm.h"
#include <stddef.h>

//
// Private
//

//
// Public
//
void bubble_sort(int *a, int n)
{
    int buff;
	for (size_t i = 0; i < n - 1; i++) {
	   for (size_t j = i + 1; j < n; j++) {
			if(a[j] > a[j+1]){
			    a[j] = buff;
				a[j] = a[j+1];
				a[j+1] = buff;
			}
		}
	}
}

void insertion_sort(int *a, int n)
{

}

void quick_sort(int *a, int n)
{

}

bool linear_search(const int *a, int n, int v)
{
	return false; // TODO: linear search
}

bool binary_search(const int *a, int n, int v)
{
	return false; // TODO: binary search
}
