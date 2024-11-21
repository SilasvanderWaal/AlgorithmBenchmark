#include "ui.h"
#include "io.h"
#include "analyze.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

//
// Private
//

//Function that prints out the time complexities for sort or search algorithms
static void ui_print_analysis_header(algorithm_t a){
    printf("\n");
    printf("%s \t", "size");
    printf("%s \t", "Time T(s)");

    switch (a) {
        //Cases when a sort algorithm is benchmarked
        case quick_sort_t:
        case bubble_sort_t:
        case insertion_sort_t:
            printf("%s\t\t", "T/n");
            printf("%s\t", "T/n*log(n)");
            printf("%s\n", "T/n²");
            break;
        //Cases when a search algorithm is bechmarked
        case binary_search_t:
        case linear_search_t:
            printf("%s\t\t", "T/1");
            printf("%s\t", "T/log(n)");
            printf("%s\n", "T/n");
            break;
        default:
            perror("Error occured when printing the results");
            break;
    }
}

//Function that prints out the time complexity results, these also depend on what algorithm we benchmark
static void ui_print_analysis(algorithm_t a, result_t results[]){
    for (int i = 0; i < RESULT_ROWS; i++) {
        int size = results[i].size;
        double time_seconds = results[i].time;
        double time_nano_seconds = results[i].time *NANO;

        printf("%d\t", size);
        printf("%.9lf\t", time_seconds);

        switch (a) {
            //The results that will be printed when we run a sorting algorithm
            case quick_sort_t:
            case bubble_sort_t:
            case insertion_sort_t:
                printf("%e\t", (time_nano_seconds / size));
                printf("%e\t", (time_nano_seconds / (log2(size) * size)));
                printf("%e\n", (time_nano_seconds / pow(size, 2)));
                break;
            //The results that will be printed when we run a sorting algorithm
            case binary_search_t:
            case linear_search_t:
                printf("%e\t", (time_nano_seconds / 1));
                printf("%e\t", (time_nano_seconds / (log2(size))));
                printf("%e\n", (time_nano_seconds / size));
                break;
            default:
                perror("Error occured when printing the results");
                break;
        }
    }
}

static void ui_print_results(result_t results[RESULT_ROWS], char menu_option[], algorithm_t a){
    for (int i = 0; i < RESULT_MENU_WIDTH; i++) {
        printf("*");
    }
    printf("\n");

    printf ("%*s\n",(int) (RESULT_MENU_WIDTH / 2 + strlen(menu_option) / 2), menu_option);

    for (int i = 0; i < RESULT_MENU_WIDTH; i++) {
        printf("-");
    }

    ui_print_analysis_header(a);
    ui_print_analysis(a, results);

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
				ui_print_results(result, "Bubble sort: Best case", bubble_sort_t);
				break;
			case 'd':
				benchmark(bubble_sort_t, worst_t, result, RESULT_ROWS);
				ui_print_results(result, "Bubble sort: Worst case", bubble_sort_t);
				break;
			case 'e':
				benchmark(bubble_sort_t, average_t, result, RESULT_ROWS);
				ui_print_results(result, "Bubble sort: Average case", bubble_sort_t);
				break;
			case 'f':
				benchmark(insertion_sort_t, best_t, result, RESULT_ROWS);
				ui_print_results(result, "Insertion sort: Best case", insertion_sort_t);
				break;
			case 'g':
				benchmark(insertion_sort_t, worst_t, result, RESULT_ROWS);
				ui_print_results(result, "Insertion sort: Worst case", insertion_sort_t);
				break;
			case 'h':
				benchmark(insertion_sort_t, average_t, result, RESULT_ROWS);
				ui_print_results(result, "Insertion sort: Average case", insertion_sort_t);
				break;
			case 'i':
				benchmark(quick_sort_t, best_t, result, RESULT_ROWS);
				ui_print_results(result, "Quick sort: Best case", quick_sort_t);
				break;
			case 'j':
				benchmark(quick_sort_t, worst_t, result, RESULT_ROWS);
				ui_print_results(result, "Quick sort: Worst case", quick_sort_t);
				break;
			case 'k':
				benchmark(quick_sort_t, average_t, result, RESULT_ROWS);
				ui_print_results(result, "Quick sort: Average case", quick_sort_t);
				break;
			case 'l':
				benchmark(linear_search_t, best_t, result, RESULT_ROWS);
				ui_print_results(result, "Linear search: Best case", linear_search_t);
				break;
			case 'm':
				benchmark(linear_search_t, worst_t, result, RESULT_ROWS);
				ui_print_results(result, "Linear search: Worst case", linear_search_t);
				break;
			case 'n':
				benchmark(linear_search_t, average_t, result, RESULT_ROWS);
				ui_print_results(result, "Linear search: Average case", linear_search_t);
				break;
			case 'o':
				benchmark(binary_search_t, best_t, result, RESULT_ROWS);
				ui_print_results(result, "Binary search: Best case", binary_search_t);
				break;
			case 'p':
				benchmark(binary_search_t, worst_t, result, RESULT_ROWS);
				ui_print_results(result, "Binary search: Worst case", binary_search_t);
				break;
			case 'q':
				benchmark(binary_search_t, average_t, result, RESULT_ROWS);
				ui_print_results(result, "Binary search: Average case", binary_search_t);
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
