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

static void ui_print_time_complexity_1(result_t* result){
    printf("%s\t\t", "T/1");
    printf("%s\t", "T/log(n)");
    printf("%s\n", "T/n*log(n)");
    for (size_t i = 0; i < RESULT_ROWS; i++) {
        int size = result[i].size;
        double time_nano_seconds = result[i].time * BILLION;
        printf("%d\t", size);
        printf("%.9lf\t", result[i].time);
        printf("%e\t", (time_nano_seconds / 1));
        printf("%e\t", (time_nano_seconds / (log2(size))));
        printf("%e\n", (time_nano_seconds / size * (log2(size))));
    }
}

static void ui_print_time_complexity_n(result_t* result){
    printf("%s\t", "T/n*log(n)");
    printf("%s\t\t", "T/n");
    printf("%s\n", "T/n²");
    for (size_t i = 0; i < RESULT_ROWS; i++) {
        int size = result[i].size;
        double time_nano_seconds = result[i].time * BILLION;
        printf("%d\t", size);
        printf("%.9lf\t", result[i].time);
        printf("%e\t", (time_nano_seconds / size * log2(size)));
        printf("%e\t", (time_nano_seconds / size));
        printf("%e\n", (time_nano_seconds / pow(size, 2)));
    }
}

static void ui_print_time_complexity_nlogn(result_t* result){
    printf("%s\t", "T/log(n)");
    printf("%s\t", "T/n*log(n)");
    printf("%s\n", "T/n");
    for (size_t i = 0; i < RESULT_ROWS; i++) {
        int size = result[i].size;
        double time_nano_seconds = result[i].time * BILLION;
        printf("%d\t", size);
        printf("%.9lf\t", result[i].time);
        printf("%e\t", (time_nano_seconds / log2(size)));
        printf("%e\t", (time_nano_seconds / (size * log2(size))));
        printf("%e\n", (time_nano_seconds / pow(size, 2) ));
    }
}

static void ui_print_time_complexity_n_squared(result_t* result){
    printf("%s\t", "T/n*log(n)");
    printf("%s\t\t", "T/n²");
    printf("%s\n", "T/n³");
    for (size_t i = 0; i < RESULT_ROWS; i++) {
        int size = result[i].size;
        double time_nano_seconds = result[i].time * BILLION;
        printf("%d\t", size);
        printf("%.9lf\t", result[i].time);
        printf("%e\t", (time_nano_seconds / size * log2(size)));
        printf("%e\t", (time_nano_seconds / pow(size, 2)));
        printf("%e\n", (time_nano_seconds / pow(size, 3)));
    }
}

static void ui_print_time_complexity_logn(result_t* result){
    printf("%s\t\t", "T/1");
    printf("%s\t", "T/log(n)");
    printf("%s\n", "T/n*log(n)");
    for (size_t i = 0; i < RESULT_ROWS; i++) {
        int size = result[i].size;
        double time_nano_seconds = result[i].time * BILLION;
        printf("%d\t", size);
        printf("%.9lf\t", result[i].time);
        printf("%e\t", (time_nano_seconds / 1));
        printf("%e\t", (time_nano_seconds / log2(size)));
        printf("%e\n", (time_nano_seconds / (log2(size) * size)));
    }
}

static void ui_print_results(result_t results[RESULT_ROWS], char menu_option[], algorithm_t a, time_complexity_t tc){
    for (int i = 0; i < RESULT_MENU_WIDTH; i++) {
        printf("*");
    }
    printf("\n");

    printf ("%*s\n",(int) (RESULT_MENU_WIDTH / 2 + strlen(menu_option) / 2), menu_option);

    for (int i = 0; i < RESULT_MENU_WIDTH; i++) {
        printf("-");
    }
    printf("\n");

    printf("%s\t", "Size");
    printf("%s\t", "Time T(s)");
    switch (tc) {
        case one:
            ui_print_time_complexity_1(results);
            break;
        case log_n:
            ui_print_time_complexity_logn(results);
            break;
        case n_log_n:
            ui_print_time_complexity_nlogn(results);
            break;
        case n:
            ui_print_time_complexity_n(results);
            break;
        case n2:
            ui_print_time_complexity_n_squared(results);
            break;
        default:
            perror("Something went wrong!");
            exit(EXIT_FAILURE);
    }

    for (int i = 0; i < RESULT_MENU_WIDTH; i++) {
        printf("-");
    }
    printf("\n");
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
