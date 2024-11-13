#include "algorithm.h"
#include <stddef.h>
#include <stdio.h>

//
// Private
//
static void swap(int* value_1, int* value_2)
{
    int temporary = *value_1;
    *value_1 = *value_2;
    *value_2 = temporary;
}

//Using the Hoare's partition scheme because O(n) instead of O(n²) time complexity.
//Low is the starting index
//High is the ending index
static int partition(int *a,int low, int high)
{
    int pivot = a[low];
    int left_index = low - 1;
    int right_index = high + 1;

    while(true)
    {
        do{
            left_index++;
        }while(a[left_index] < pivot);

        do{
            right_index--;
        }while(a[right_index] > pivot);

        if(left_index >= right_index)
            return right_index;

        swap(a + left_index, a + right_index);
    }
}

//
// Public
//
void bubble_sort(int *a, int n)
{
    int buff;
	for (size_t i = 0; i < n - 1; i++)
	{
	   for (size_t j = 0; j < n - i - 1; j++)
		{
			if(a[j] > a[j+1])
			{
			    buff = a[j];
				a[j] = a[j+1];
				a[j+1] = buff;
			}
		}
	}
}

void insertion_sort(int *a, int n)
{
    for (size_t i = 1; i < n; i++)
    {
        int index = i - 1;
        int compare_value = a[i];

        while(index >= 0 && a[index] > compare_value)
        {
            a[index+1] = a[index];
            index--;
        }

        a[index + 1] = compare_value;
    }
}

void quick_sort(int *a, int n)
{
    int pivot_index = partition(a, 0, n - 1);
    quick_sort(a, pivot_index - 1);
    quick_sort(a + pivot_index + 1, n - 1);
}

bool linear_search(const int *a, int n, int v)
{
	return false; // TODO: linear search
}

bool binary_search(const int *a, int n, int v)
{
	return false; // TODO: binary search
}
