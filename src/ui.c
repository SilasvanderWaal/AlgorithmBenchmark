#include "../include/ui.h"
#include "../include/io.h"
#include "../include/analyze.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//
// Private
//

static void ui_line(char c, int n);

static void ui_print_time_complexity(result_t* result, time_complexity_t accurate_complexity){
	//Array for all the time complexity calculations
	double time_complexity[TIME_COMPLEXITIES];

	//Maping the time complexity headers to the right time complexity calculation
	const char* time_complexity_headers[TIME_COMPLEXITIES] = {"T/1","T/log(n)","T/n","T/n*log(n)","T/n²","T/n³"};

	//Making sure the value mapped to the time accurate complexity never becomes zero
	accurate_complexity = (accurate_complexity == 0) ? accurate_complexity + 1 : accurate_complexity;
	
	//Printing out the headers
    printf("|%-5s\t", "Size");
    printf("|%-11s\t", "Time T(s)");
	printf("|%-11s\t", time_complexity_headers[accurate_complexity- 1]);
    printf("|%-11s\t", time_complexity_headers[accurate_complexity]);
    printf("|%-11s\n", time_complexity_headers[accurate_complexity + 1]);
	
	//Looping over all the calculations for different sizes
	for (size_t i = 0; i < RESULT_ROWS; i++)
	{
		int size = result[i].size;
		double time = result[i].time;

		time_complexity[one] = time / 1;
		time_complexity[log_n] = time / log2(size);
		time_complexity[n_log_n] = time / (log2(size) * size);
		time_complexity[n] = time / size;
		time_complexity[n2] = time / pow(size, 2);
		time_complexity[n3] = time / pow(size, 3);

        printf("|%-5d\t", size);
        printf("|%.9lf\t", time);
        printf("|%e\t", time_complexity[accurate_complexity - 1]);
        printf("|%e\t", time_complexity[accurate_complexity]);
        printf("|%e\n", time_complexity[accurate_complexity + 1]);
	}
}

static void ui_print_results(result_t results[RESULT_ROWS], char menu_option[], algorithm_t a, time_complexity_t accurate_time_complexity){
	ui_line('*', RESULT_MENU_WIDTH);
    printf ("%*s\n",(int) (RESULT_MENU_WIDTH / 2 + strlen(menu_option) / 2), menu_option);
	ui_line('-', RESULT_MENU_WIDTH);
	ui_print_time_complexity(results, accurate_time_complexity);
	ui_line('-', RESULT_MENU_WIDTH);
}

static void ui_invalid_input()
{
	printf("info> bad input\n");
}

static void ui_exit()
{
	printf("info> bye\n");
}

static char ui_get_choice()
{
	char buf[3];

	printf("input> ");
	return read_line(buf, 3) ? buf[0] : 0;
}

static void ui_line(char c, int n)
{
	while (n-- > 0) {
		putchar(c);
	}
	putchar('\n');
}

static void ui_menu_options(const char *options[], int num_options)
{
	int i;

	for (i=0; i<num_options; i++) {
		printf("    %c) %s\n", 'a'+i, options[i]);
	}
}

static void ui_menu()
{
	const char *options[] = {
		"Menu",
		"Exit\n",
		"Bubble sort best case",
		"Bubble sort worst case",
		"Bubble sort average case\n",
		"Insertion sort best case",
		"Insertion sort worst case",
		"Insertion sort average case\n",
		"Quick sort best case",
		"Quick sort worst case",
		"Quick sort average case\n",
		"Linear search best case",
		"Linear search worst case",
		"Linear search average case\n",
		"Binary search best case",
		"Binary search worst case",
		"Binary search average case",
	};

	ui_line('=', MENU_WIDTH);
	ui_menu_options(options, sizeof(options) / sizeof(char *));
	ui_line('-', MENU_WIDTH);
}

//
// Public
//
void ui_run()
{
	bool running, show_menu;
	result_t result[RESULT_ROWS];

	show_menu = true;
	running = true;
	while (running) {
		if (show_menu) {
			show_menu = false;
			ui_menu();
		}
		switch (ui_get_choice()) {
			// House keeping
			case 'a':
				show_menu = true;
				break;
			case 'b':
				running = false;
				break;
			case 'c':
				benchmark(bubble_sort_t, best_t, result, RESULT_ROWS);
				ui_print_results(result, "Bubble sort: Best case", bubble_sort_t, n);
				break;
			case 'd':
				benchmark(bubble_sort_t, worst_t, result, RESULT_ROWS);
				ui_print_results(result, "Bubble sort: Worst case", bubble_sort_t, n2);
				break;
			case 'e':
				benchmark(bubble_sort_t, average_t, result, RESULT_ROWS);
				ui_print_results(result, "Bubble sort: Average case", bubble_sort_t, n2);
				break;
			case 'f':
				benchmark(insertion_sort_t, best_t, result, RESULT_ROWS);
				ui_print_results(result, "Insertion sort: Best case", insertion_sort_t, n);
				break;
			case 'g':
				benchmark(insertion_sort_t, worst_t, result, RESULT_ROWS);
				ui_print_results(result, "Insertion sort: Worst case", insertion_sort_t, n2);
				break;
			case 'h':
				benchmark(insertion_sort_t, average_t, result, RESULT_ROWS);
				ui_print_results(result, "Insertion sort: Average case", insertion_sort_t, n2);
				break;
			case 'i':
				benchmark(quick_sort_t, best_t, result, RESULT_ROWS);
				ui_print_results(result, "Quick sort: Best case", quick_sort_t, n_log_n);
				break;
			case 'j':
				benchmark(quick_sort_t, worst_t, result, RESULT_ROWS);
				ui_print_results(result, "Quick sort: Worst case", quick_sort_t, n2);
				break;
			case 'k':
				benchmark(quick_sort_t, average_t, result, RESULT_ROWS);
				ui_print_results(result, "Quick sort: Average case", quick_sort_t, n_log_n);
				break;
			case 'l':
				benchmark(linear_search_t, best_t, result, RESULT_ROWS);
				ui_print_results(result, "Linear search: Best case", linear_search_t, one);
				break;
			case 'm':
				benchmark(linear_search_t, worst_t, result, RESULT_ROWS);
				ui_print_results(result, "Linear search: Worst case", linear_search_t, n);
				break;
			case 'n':
				benchmark(linear_search_t, average_t, result, RESULT_ROWS);
				ui_print_results(result, "Linear search: Average case", linear_search_t, n);
				break;
			case 'o':
				benchmark(binary_search_t, best_t, result, RESULT_ROWS);
				ui_print_results(result, "Binary search: Best case", binary_search_t, one);
				break;
			case 'p':
				benchmark(binary_search_t, worst_t, result, RESULT_ROWS);
				ui_print_results(result, "Binary search: Worst case", binary_search_t, log_n);
				break;
			case 'q':
				benchmark(binary_search_t, average_t, result, RESULT_ROWS);
				ui_print_results(result, "Binary search: Average case", binary_search_t, log_n);
				break;
			// Invalid input
			default:
				show_menu = false;
				ui_invalid_input();
				break;
		}
	}
	ui_exit();
}
