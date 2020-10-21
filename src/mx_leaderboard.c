#include "header.h"

t_player_stats mx_read_leaderboard_file(void) {
    t_player_stats stats;
    FILE *board;
    board = fopen("./resource/text/leaderboard.txt", "r+");
    for (int i = 0; i < 10; i++) {
        fscanf(board, "%d %s", &stats.scores[i], stats.names[i]);
    }
    fclose(board);
    return stats;
}

void file_write(t_player_stats stats) {
    FILE *board;
    board = fopen("./resource/text/leaderboard.txt", "w+");
    for (int i = 0; i < 10; i++)
        fprintf(board, "%d %s\n", stats.scores[i], stats.names[i]);
    fclose(board);
}

t_player_stats board_updated(t_player_stats stats, char new_name[16], int new_score) {
    int i = 0;
    for(int j = 0; j < 16; j++)
        if(new_name[j] == ' ')
            new_name[j] = '_';
    while (i < 10 && new_score <= stats.scores[i])
        i++;
    if (i < 10) {
        for (int j = 10-2; j >= i; j--) {
            stats.scores[j+1] = stats.scores[j];
            strcpy(stats.names[j+1], stats.names[j]);
        }
        stats.scores[i] = new_score;
        strcpy(stats.names[i], new_name);
    }
    return stats;
}

int mx_leaderboard(SDL_Renderer *renderer) {
    bool leaderboard = true;
    int choice = 3;
    SDL_Event event;

    Mix_Music *mainSound = Mix_LoadMUS("./resource/sounds/leaderboard.mp3");
    Mix_PlayMusic(mainSound, -1);

    Mix_Chunk *leadClick = Mix_LoadWAV("./resource/sounds/main_menu/menu_click.wav");

    SDL_Texture* background = IMG_LoadTexture(renderer, "./resource/images/backgroundDarken.png");
    SDL_Texture* moon = IMG_LoadTexture(renderer, "./resource/images/moon.png");
    SDL_Color white = {255, 255, 255, 255};
    TTF_Font* karmatic = TTF_OpenFont("resource/fonts/joystix.ttf", 42);
    TTF_Font* joystix = TTF_OpenFont("resource/fonts/joystix.ttf", 64);

    SDL_Surface* exitSurface = TTF_RenderText_Solid(karmatic, "Back to menu", white);
    SDL_Texture* exitTexture = SDL_CreateTextureFromSurface(renderer, exitSurface);
    SDL_Rect exitRect = {960 - (exitSurface->w)/2, 960, exitSurface->w, exitSurface->h};

    SDL_Rect moonPos = { 1200, -145, 534, 539 };

    SDL_RenderCopy(renderer, background, NULL, NULL);
    SDL_RenderCopy(renderer, moon, NULL, &moonPos);
    SDL_RenderCopy(renderer, exitTexture, NULL, &exitRect);

    t_player_stats stats = mx_read_leaderboard_file();
    for(int i = 0; i < 10; i++) {
        SDL_Surface * nameSurface = TTF_RenderText_Blended(joystix, stats.names[i], white);
        SDL_Texture* name = SDL_CreateTextureFromSurface(renderer, nameSurface);
        SDL_Rect Message_rect;
        Message_rect.x = 250;
        Message_rect.y = 165 + i * 70;
        Message_rect.w = 48 * strlen(stats.names[i]);
        Message_rect.h = 48;
        SDL_RenderCopy(renderer, name, NULL, &Message_rect); 

        SDL_Rect destScore;
        destScore.x = 1147;
        destScore.y = 165 + i * 70;
        char score_text[11];
        sprintf(score_text, "%.5d", stats.scores[i]);
        SDL_Surface *score_surface = TTF_RenderText_Blended(joystix, score_text, white);
        SDL_Texture *score = SDL_CreateTextureFromSurface(renderer, score_surface);

        SDL_Rect score_rect = {1400, 165 + i * 70, 48 * strlen(score_text), 48};

        SDL_RenderCopy(renderer, score, NULL, &score_rect);

        SDL_FreeSurface(nameSurface);
        SDL_FreeSurface(score_surface);
        SDL_DestroyTexture(name);
        SDL_DestroyTexture(score);
    }

    SDL_RenderPresent(renderer);

    while(leaderboard){
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    leaderboard = false;
                    choice = 0;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    Mix_PlayChannel(-1, leadClick, 0);
                    SDL_Delay(100);
                    if (event.button.button == SDL_BUTTON_LEFT
                        && event.button.x >= 960 - (exitSurface->w)/2
                        && event.button.x <= (960 - (exitSurface->w)/2) + exitSurface->w
                        && event.button.y >= 960
                        && event.button.y <= 960 + exitSurface->h) {
                            leaderboard = false;
                        }
            }
        }
    }

    TTF_CloseFont(karmatic);
    TTF_CloseFont(joystix);
    Mix_FreeMusic(mainSound);
    SDL_DestroyTexture(moon);
    SDL_DestroyTexture(background);
    return choice;
}
