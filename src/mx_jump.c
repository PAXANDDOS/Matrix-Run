#include "header.h"

SDL_Renderer *mx_jump(SDL_Renderer *renderer, bool *jump, bool *down, t_position *pos, int *count,
                      t_position *redpill_pos, t_position *bluepill_pos, int *redpill_distance,
                      int *bluepill_distance, int *distance, t_position *smith_pos, float ground, bool runL, bool runR) {
    if (*jump) {
        if (pos->y > ground - JUMP_HEIGHT) {
            *count = *count + 1;
            pos->y -= JUMP_STEP;
            if (runL) {
                *distance = *distance - 1;
                *redpill_distance = *redpill_distance - 1;
                *bluepill_distance = *bluepill_distance - 1;
                pos->x -= MOVE_STEP;
                if (pos->x <= LEFT_LIMIT) {
                    redpill_pos->x += MOVE_STEP;
                    bluepill_pos->x += MOVE_STEP;
                    smith_pos->x += MOVE_STEP;
                }
            }
            else if (runR) {
                *distance = *distance + 1;
                *redpill_distance = *redpill_distance + 1;
                *bluepill_distance = *bluepill_distance + 1;
                pos->x += MOVE_STEP;
                if (pos->x >= RIGHT_LIMIT) {
                    redpill_pos->x -= MOVE_STEP;
                    bluepill_pos->x -= MOVE_STEP * 2;
                    smith_pos->x -= MOVE_STEP;
                }
            }
        }
        else if (pos->y <=  ground - JUMP_HEIGHT) {
            *jump = false;
            *down = true;
        }
    }
    else {
        if (pos->y != ground) {
            *count = *count + 1;
            pos->y += JUMP_STEP;
            if (runL) {
                *distance = *distance - 1;
                *redpill_distance = *redpill_distance - 1;
                *bluepill_distance = *bluepill_distance - 1;
                pos->x -= MOVE_STEP;
                if (pos->x <= LEFT_LIMIT) {
                    redpill_pos->x += MOVE_STEP;
                    bluepill_pos->x += MOVE_STEP;
                    smith_pos->x += MOVE_STEP;
                }
            }
            else if (runR) {
                *distance = *distance + 1;
                *redpill_distance = *redpill_distance + 1;
                *bluepill_distance = *bluepill_distance + 1;
                pos->x += MOVE_STEP;
                if (pos->x >= RIGHT_LIMIT) {
                    redpill_pos->x -= MOVE_STEP;
                    bluepill_pos->x -= MOVE_STEP * 2;
                    smith_pos->x -= MOVE_STEP;
                }
            }
        }
        else if (*down == true){
            *count = 1;
            *down = false;
            if (pos->x >= RIGHT_LIMIT)
                pos->x = RIGHT_LIMIT - 1;
            else if (pos->x <= LEFT_LIMIT)
                pos->x = LEFT_LIMIT + 1;
        }
    }
    return renderer;
}
