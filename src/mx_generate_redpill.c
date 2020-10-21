#include "header.h"

bool mx_generate_redpill(t_position *neo_pos, t_position *redpill_pos, int *score, int *distance) {
    int shift = 140;
    bool changed = false;

    if ((neo_pos->x >= redpill_pos->x - shift && neo_pos->x <= redpill_pos->x + shift / 2) &&
        (neo_pos->y >= redpill_pos->y - shift && neo_pos->y <= redpill_pos->y + shift / 2)) {
        *score = *score + SCORE_INCREASE;
        *distance = 0;
        redpill_pos->x = WINDOW_WIDTH + rand() % (WINDOW_WIDTH);
        redpill_pos->y = WINDOW_HEIGHT - 300 - rand() % 300;

        changed = true;
    }
    else if (*distance > WINDOW_WIDTH) {
        *distance = 0;
        redpill_pos->x = WINDOW_WIDTH + rand() % (WINDOW_WIDTH);
        redpill_pos->y = WINDOW_HEIGHT - 300 - rand() % 300;
    }
    return changed;
}
