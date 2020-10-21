#include "header.h"

void mx_scroll_bg(t_position *pos, int *bg_num1, float *bg1_pos, float *bg2_pos, int *bg_num2, float *bg_rail1_pos, float *bg_rail2_pos) {
    if (pos->x >= RIGHT_LIMIT) {
        pos->x = RIGHT_LIMIT;

        // far bg
        if (*bg_num1 == 1) {
            if (*bg2_pos == -WINDOW_WIDTH)
                    *bg2_pos = WINDOW_WIDTH - MOVE_STEP;
            if (*bg1_pos == -WINDOW_WIDTH + MOVE_STEP) {
                *bg_num1 = 2;
                *bg1_pos = WINDOW_WIDTH;
            }
            *bg1_pos = *bg1_pos - MOVE_STEP / 3;
            *bg2_pos = *bg2_pos - MOVE_STEP / 3;
        }
        else {
            if (*bg1_pos == -WINDOW_WIDTH)
                    *bg1_pos = WINDOW_WIDTH - MOVE_STEP;
            if (*bg2_pos == -WINDOW_WIDTH + MOVE_STEP) {
                *bg_num1 = 1;
                *bg2_pos = WINDOW_WIDTH;
            }
            *bg1_pos = *bg1_pos - MOVE_STEP / 3;
            *bg2_pos = *bg2_pos - MOVE_STEP / 3;
        }

        // near bg
        if (*bg_num2 == 1) {
            if (*bg_rail2_pos == -WINDOW_WIDTH)
                *bg_rail2_pos = WINDOW_WIDTH - MOVE_STEP;
            if (*bg_rail1_pos == -WINDOW_WIDTH + MOVE_STEP) {
                *bg_num2 = 2;
                *bg_rail1_pos = WINDOW_WIDTH;
            }
            *bg_rail1_pos = *bg_rail1_pos - MOVE_STEP;
            *bg_rail2_pos = *bg_rail2_pos - MOVE_STEP;
        }
        else {
            if (*bg_rail1_pos == -WINDOW_WIDTH)
                *bg_rail1_pos = WINDOW_WIDTH - MOVE_STEP;
            if (*bg_rail2_pos == -WINDOW_WIDTH + MOVE_STEP) {
                *bg_num2 = 1;
                *bg_rail2_pos = WINDOW_WIDTH;
            }
            *bg_rail1_pos = *bg_rail1_pos - MOVE_STEP;
            *bg_rail2_pos = *bg_rail2_pos - MOVE_STEP;
        }

    }
    else if (pos->x <= LEFT_LIMIT) {
        pos->x = LEFT_LIMIT;

        // far bg
        if (*bg_num1 == 1) {
            if (*bg2_pos == WINDOW_WIDTH)
                *bg2_pos = -WINDOW_WIDTH + MOVE_STEP;
            if (*bg1_pos == WINDOW_WIDTH - MOVE_STEP) {
                *bg_num1 = 2;
                *bg1_pos = -WINDOW_WIDTH;
            }
            *bg1_pos = *bg1_pos + MOVE_STEP / 3;
            *bg2_pos = *bg2_pos + MOVE_STEP / 3;
        }
        else {
            if (*bg1_pos == WINDOW_WIDTH)
                *bg1_pos = -WINDOW_WIDTH + MOVE_STEP;
            if (*bg2_pos == WINDOW_WIDTH - MOVE_STEP) {
                *bg_num1 = 1;
                *bg2_pos = -WINDOW_WIDTH;
            }
            *bg1_pos = *bg1_pos + MOVE_STEP / 3;
            *bg2_pos = *bg2_pos + MOVE_STEP / 3;
        }

        // near bg
        if (*bg_num2 == 1) {
            if (*bg_rail2_pos == WINDOW_WIDTH)
                *bg_rail2_pos = -WINDOW_WIDTH + MOVE_STEP;
            if (*bg_rail1_pos == WINDOW_WIDTH - MOVE_STEP) {
                *bg_num2 = 2;
                *bg_rail1_pos = -WINDOW_WIDTH;
            }
            *bg_rail1_pos = *bg_rail1_pos + MOVE_STEP;
            *bg_rail2_pos = *bg_rail2_pos + MOVE_STEP;
        }
        else {
            if (*bg_rail1_pos == WINDOW_WIDTH)
                *bg_rail1_pos = -WINDOW_WIDTH + MOVE_STEP;
            if (*bg_rail2_pos == WINDOW_WIDTH - MOVE_STEP) {
                *bg_num2 = 1;
                *bg_rail2_pos = -WINDOW_WIDTH;
            }
            *bg_rail1_pos = *bg_rail1_pos + MOVE_STEP;
            *bg_rail2_pos = *bg_rail2_pos + MOVE_STEP;
        }
    }
}
