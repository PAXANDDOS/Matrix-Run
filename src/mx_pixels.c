#include "header.h"

void mx_pixels(SDL_Renderer *renderer, SDL_Texture *pixelsTexture, SDL_Texture *dropsTexture, t_player *neo,
               int *px_cols, int *px_count, int *px_count_last, int *last_pixel, int *distance, bool score_changed, int ticks) {
    if (score_changed)
        if (*px_cols > 0) {
            *distance = *distance - 200;
            if (*px_count < 5 || *distance > 50000)
                *px_cols = *px_cols - 1;
        }
        //printf("%d\n", *distance);
    for (int i = 0; i < *px_cols; i++) {
        int ii = i == 0 ? 2 : i;
        for (int j = 0; j < 9; j++) {
            if (i == 0 && j == 0)
                continue;
            int pixel = (ticks / 220 + 5 * j * ii) % 9;
            SDL_Rect srcrectPixel = { pixel * PIXEL_WIDTH, 0, PIXEL_WIDTH, PIXEL_HEIGHT };
            SDL_Rect pixelPos = { 100 * i, 100 * j, PIXEL_SIZE, PIXEL_SIZE };
            SDL_RenderCopy(renderer, pixelsTexture, &srcrectPixel, &pixelPos);
        }

        int drop = (ticks / 210 + 6 * ii) % 9;
        SDL_Rect srcrectDrop = { drop * PIXEL_WIDTH, 0, PIXEL_WIDTH, PIXEL_HEIGHT };
        SDL_Rect dropPos = { 100 * i, 100 * 9, PIXEL_SIZE, PIXEL_SIZE };
        SDL_RenderCopy(renderer, dropsTexture, &srcrectDrop, &dropPos);
    }

    *last_pixel = 0;
    *px_count = *distance / 200 % 10;
    for (int i = 0; i < *px_count; i++) {
        if (*px_cols == 0 && i == 0)
            continue;
        int pixel = (ticks / 220 + 5 * i) % 9;
        SDL_Rect srcrectPixel = { pixel * PIXEL_WIDTH, 0, PIXEL_WIDTH, PIXEL_HEIGHT };
        SDL_Rect pixelPos = { 100 * *px_cols, 100 * i, PIXEL_SIZE, PIXEL_SIZE };
        SDL_RenderCopy(renderer, pixelsTexture, &srcrectPixel, &pixelPos);
        *last_pixel = *last_pixel + 1;
    }
    int drop = (ticks / 210 + 7) % 9;
    SDL_Rect srcrectDrop = { drop * PIXEL_WIDTH, 0, PIXEL_WIDTH, PIXEL_HEIGHT };
    if (!(*px_cols == 0 && *last_pixel == 0)) {
        SDL_Rect dropPos = { 100 * *px_cols, 100 * *last_pixel, PIXEL_SIZE, PIXEL_SIZE };
        SDL_RenderCopy(renderer, dropsTexture, &srcrectDrop, &dropPos);
    }
    if (*px_count == 0 && *px_count_last != *px_count)
        *px_cols = *px_cols + 1;
    if (*px_count_last != *px_count)
        *px_count_last = *px_count;
    //printf("%d %d\n", px_cols, px_count);

    //printf("%f %f\n %d %d\n\n", neo->pos.x, neo->pos.y, *px_cols * 100, *px_count * 100);
    if (neo->pos.x <= *px_cols * 100 && neo->pos.y <= *px_count * 100)
        neo->health = 0;
}
