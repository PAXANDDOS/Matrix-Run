#include "header.h"

bool mx_generate_bluepill(t_position *neo_pos, t_position *bluepill_pos, int *lives, int *distance) {
    int shift = 200;
    bool changed = false;
    if ((neo_pos->x >= bluepill_pos->x - shift && neo_pos->x <= bluepill_pos->x) &&
        (neo_pos->y + 100 >= bluepill_pos->y && neo_pos->y - 100 <= bluepill_pos->y)) {
        *lives = *lives - 1;
        *distance = 0;
        bluepill_pos->x = WINDOW_WIDTH * 3 + rand() % WINDOW_WIDTH;
        bluepill_pos->y = WINDOW_HEIGHT - 200;

        changed = true;
    }
    else if (*distance > WINDOW_WIDTH) {
        *distance = 0;
        bluepill_pos->x = WINDOW_WIDTH * 3 + rand() % WINDOW_WIDTH;
        bluepill_pos->y = WINDOW_HEIGHT - 200;
    }
    return changed;
}
