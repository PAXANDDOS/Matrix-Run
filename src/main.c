#include "header.h"
    
int main() 
{
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    TTF_Init();

    SDL_Window * window = SDL_CreateWindow("Matrix Run", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    
    SDL_Renderer *renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED);

    SDL_Cursor* cursor;
    SDL_Surface* cursor_image;
    cursor_image = SDL_LoadBMP("./resource/images/cursor.bmp");
    cursor = SDL_CreateColorCursor(cursor_image, 7, 7);
    SDL_SetCursor(cursor);

    srand(time(NULL));
    int choice = 0;
    int score = 0;
    bool quit = false;
    choice = mx_main_menu(renderer);
    while(!quit) {
        switch(choice) {
            case 1:
                SDL_ShowCursor(SDL_DISABLE);
                choice = mx_start(renderer, &score);
                break;
            case 2:
                SDL_ShowCursor(SDL_ENABLE);
                choice = mx_leaderboard(renderer);
                // choice = mx_game_over(renderer, 2);
                break;
            case 3:
                SDL_ShowCursor(SDL_ENABLE);
                choice = mx_main_menu(renderer);
                break;
            case 4:
                SDL_ShowCursor(SDL_ENABLE);
                choice = mx_game_over(renderer, score);
                break;
            case 0:
                quit = true;
                break;
        }
    }

    SDL_FreeCursor(cursor);
    SDL_FreeSurface(cursor_image);
    Mix_CloseAudio();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
    return 0;
}
