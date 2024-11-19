#include "ui.h"
#include "io.h"
#include "analyze.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

//
// Private
//

static void ui_print_results(result_t results[RESULT_ROWS], char menu_option[]){
    int size = SIZE_START;

    printf("\n");
    for (int i = 0; i < MENU_WIDTH; i++) {
        printf("*");
    }
    printf("\n");

    printf ("%*s\n",(int) (MENU_WIDTH / 2 + strlen(menu_option) / 2), menu_option);

    for (int i = 0; i < MENU_WIDTH; i++) {
        printf("-");
    }

    printf("\n");
    printf("%5s \t", "size");
    printf("%9s \t", "time T(s)");
    printf("%5s \t", "T/logn");
    printf("%5s \t", "T/n");
    printf("%5s \t\n", "T/nlog");

    for (int i = 0; i < RESULT_ROWS; i++) {

        double time_seconds = results[i].time;
        printf("%5d \t %.9lf\n", size, time_seconds);
        size *= 2;
    }

    for (int i = 0; i < MENU_WIDTH; i++) {
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
			// Bubble sort
			case 'c':
				benchmark(bubble_sort_t, best_t, result, RESULT_ROWS);
				ui_print_results(result, "Bubble sort: Best case");
				break;
			case 'd':
				benchmark(bubble_sort_t, worst_t, result, RESULT_ROWS);
				ui_print_results(result, "Bubble sort: Worst case");
				break;

			case 'e':
				benchmark(bubble_sort_t, average_t, result, RESULT_ROWS);
				ui_print_results(result, "Bubble sort: Average case");
				break;

			case 'f':
				benchmark(insertion_sort_t, best_t, result, RESULT_ROWS);
				ui_print_results(result, "Insertion sort: Best case");
				break;

			case 'g':
				benchmark(insertion_sort_t, worst_t, result, RESULT_ROWS);
				ui_print_results(result, "Insertion sort: Worst case");
				break;
			case 'h':
				benchmark(insertion_sort_t, average_t, result, RESULT_ROWS);
				ui_print_results(result, "Insertion sort: Average case");
				break;
			case 'i':
				benchmark(quick_sort_t, best_t, result, RESULT_ROWS);
				ui_print_results(result, "Quick sort: Best case");
				break;
			case 'j':
				benchmark(quick_sort_t, worst_t, result, RESULT_ROWS);
				ui_print_results(result, "Quick sort: Worst case");
				break;
			case 'k':
				benchmark(quick_sort_t, average_t, result, RESULT_ROWS);
				ui_print_results(result, "Quick sort: Average case");
				break;
			case 'l':
				benchmark(linear_search_t, best_t, result, RESULT_ROWS);
				ui_print_results(result, "Linear search: Best case");
				break;
			case 'm':
				benchmark(linear_search_t, worst_t, result, RESULT_ROWS);
				ui_print_results(result, "Linear search: Worst case");
				break;
			case 'n':
				benchmark(linear_search_t, average_t, result, RESULT_ROWS);
				ui_print_results(result, "Linear search: Average case");
				break;
			case 'o':
				benchmark(binary_search_t, best_t, result, RESULT_ROWS);
				ui_print_results(result, "Binary search: Best case");
				break;
			case 'p':
				benchmark(binary_search_t, worst_t, result, RESULT_ROWS);
				ui_print_results(result, "Binary search: Worst case");
				break;
			case 'q':
				benchmark(binary_search_t, average_t, result, RESULT_ROWS);
				ui_print_results(result, "Binary search: Average case");
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
