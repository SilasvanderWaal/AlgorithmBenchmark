#ifndef UI_H
#define UI_H

#define MENU_WIDTH 40
#define RESULT_MENU_WIDTH 70
#define RESULT_ROWS 6
#define TIME_COMPLEXITIES 6
#define NANO 10E-9

// ui_run starts a terminal-based user interface
void ui_run();

//time_complexity_t defines different time complexities
typedef enum{
    one = 0,
    log_n = 1,
    n = 2,
    n_log_n = 3,
    n2 = 4,
    n3 = 5
}time_complexity_t;

#endif
