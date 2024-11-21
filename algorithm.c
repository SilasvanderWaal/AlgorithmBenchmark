#include "algorithm.h"
#include <stddef.h>
#include <stdio.h>

//
// Private
//

//Swapping the values of the two memory adresses it recieves
static void swap(int* value_1, int* value_2)
{
    int temporary = *value_1;
    *value_1 = *value_2;
    *value_2 = temporary;
}

//Using the Hoare's partition scheme because O(n) instead of O(n²) time complexity.
static int partition(int *a, int size)
{
    int low = 0;
    int high = size - 1;
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
void bubble_sort(int *a, int n){
    bool swapped;
	for (size_t i = 0; i < n - 1; i++){
	   swapped = false;
	   for (size_t j = 0; j < n - i - 1; j++){
			if(a[j] > a[j+1]){
			    swap((a + j),( a + j + 1));
				swapped = true;
			}
		}

		if(swapped == false){
		  break;
		}
	}
}

void insertion_sort(int *a, int n){
    for (size_t i = 1; i < n; i++){
        int index = i - 1;
        int compare_value = a[i];

        while(index >= 0 && a[index] > compare_value){
            a[index+1] = a[index];
            index--;
        }

        a[index + 1] = compare_value;
    }

    return;
}

void quick_sort(int *a, int n){
    if(n > 1){
        int pivot_index = partition(a, n);
        quick_sort(a, pivot_index + 1); //Left side from zero to and with pivot
        quick_sort(a + pivot_index + 1, n - (pivot_index + 1)); //Right side from index after previous pivot
    }

    return;
}

bool linear_search(const int *a, int n, int v){
    for(int i = 0; i < n; i++){
        if(a[i] == v)
            return true;
    }

	return false;
}

bool binary_search(const int *a, int n, int v){
    if(n == 0)
        return false;

    int half_index = n / 2;

    if(a[half_index]== v)
        return true;
    else if(a[half_index] > v)
        return binary_search(a, half_index, v);     //search the left half
    else
        return binary_search(a + (half_index + 1),n - half_index - 1, v);    //search the right half
}
