#include "header.h"

void mx_draw_bullets(SDL_Renderer *renderer, SDL_Texture *tex) {
    t_bullet *bullet = NULL;

    while (bullet != NULL) {
        SDL_Rect rect = { bullet->pos.x, //- 140/ 2,
                          bullet->pos.y, //- 140 / 2,
                          140,
                          140
        };

        SDL_RenderCopy(renderer, tex, NULL, &rect);

        bullet->pos.x += 10;
        bullet = bullet->next;
    }
}
