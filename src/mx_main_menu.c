#include "header.h"

int mx_main_menu(SDL_Renderer *renderer){
    int choice = 0;
    bool menu = true;
    SDL_Event event;

    SDL_Texture* background = IMG_LoadTexture(renderer, "./resource/images/main_menu.png"); //Making a bg texture

    SDL_Texture* redpill = IMG_LoadTexture(renderer, "./resource/images/redpill.png");
    SDL_Rect redpillRect = {65, 279, 35, 35};
    SDL_Texture* bluepill = IMG_LoadTexture(renderer, "./resource/images/bluepill.png");
    SDL_Rect bluepillRect = {65, 419, 35, 35};

    Mix_Music *mainSound = Mix_LoadMUS("./resource/sounds/main_menu/maintheme.mp3"); //ПОМЕНЯТЬ МУЗЫКУ
    Mix_PlayMusic(mainSound, -1);

    Mix_Chunk *mainClick = Mix_LoadWAV("./resource/sounds/main_menu/menu_click.wav");

    SDL_Color white = {255, 255, 255, 255}; // Тип для цвета. 4 числа — R, G, B и A, соответственно. // Зададим параметры цвета
    SDL_Color red = {255, 0, 0, 255};
    SDL_Color blue = {0, 0, 255, 255};
    TTF_Font* joystixBig = TTF_OpenFont("resource/fonts/1982font.ttf", 64); //Making a font
    TTF_Font* joystixSmall = TTF_OpenFont("resource/fonts/1982font.ttf", 32);

    SDL_Surface* titleSurface = TTF_RenderText_Solid(joystixBig, "MATRIX RUN", white); //Making a title surface
    SDL_Texture* titleTexture = SDL_CreateTextureFromSurface(renderer, titleSurface); //Making a title texture
    SDL_Rect titleRect = {MAINMENU_TITLE_X, MAINMENU_TITLE_Y, titleSurface->w, titleSurface->h}; //Making a rectangle for a title

    SDL_Surface* startSurface = TTF_RenderText_Solid(joystixSmall, "TAKE the RED PILL", red);
    SDL_Texture* startTexture = SDL_CreateTextureFromSurface(renderer, startSurface);
    SDL_Rect startRect = {MAINMENU_STARTBUTTON_X, MAINMENU_STARTBUTTON_Y, startSurface->w, startSurface->h};
    
    SDL_Surface* leaderSurface = TTF_RenderText_Solid(joystixSmall, "BEST AGENTS", white);
    SDL_Texture* leaderTexture = SDL_CreateTextureFromSurface(renderer, leaderSurface);
    SDL_Rect leaderRect = {MAINMENU_LEADERBUTTON_X, MAINMENU_LEADERBUTTON_Y, leaderSurface->w, leaderSurface->h};
    
    SDL_Surface* exitSurface = TTF_RenderText_Solid(joystixSmall, "TAKE THE BLUE PILL", blue);
    SDL_Texture* exitTexture = SDL_CreateTextureFromSurface(renderer, exitSurface);
    SDL_Rect exitRect = {MAINMENU_EXITBUTTON_X, MAINMENU_EXITBUTTON_Y, exitSurface->w, exitSurface->h};

    SDL_Texture* keyboard = IMG_LoadTexture(renderer, "./resource/images/keyboard.png"); //Making a keyboard texture
    SDL_Rect keyboardRect = {MAINMENU_KEYBOARD_X, MAINMENU_KEYBOARD_Y, 607, 317};

    while(menu) {
        SDL_RenderCopy(renderer, background, NULL, NULL);
        SDL_RenderCopy(renderer, redpill, NULL, &redpillRect);
        SDL_RenderCopy(renderer, bluepill, NULL, &bluepillRect);
        SDL_RenderCopy(renderer, titleTexture, NULL, &titleRect);
        SDL_RenderCopy(renderer, startTexture, NULL, &startRect);
        SDL_RenderCopy(renderer, leaderTexture, NULL, &leaderRect);
        SDL_RenderCopy(renderer, exitTexture, NULL, &exitRect);
        SDL_RenderCopy(renderer, keyboard, NULL, &keyboardRect);

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    menu = false;
                    choice = 0;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    Mix_PlayChannel(-1, mainClick, 0);
                    SDL_Delay(100);
                    if (event.button.button == SDL_BUTTON_LEFT
                        && event.button.x >= MAINMENU_STARTBUTTON_X
                        && event.button.x <= MAINMENU_STARTBUTTON_X + startSurface->w
                        && event.button.y >= MAINMENU_STARTBUTTON_Y
                        && event.button.y <= MAINMENU_STARTBUTTON_Y + startSurface->h) {
                            choice = 1;
                            menu = false;
                        }
                    else if (event.button.button == SDL_BUTTON_LEFT
                        && event.button.x >= MAINMENU_LEADERBUTTON_X
                        && event.button.x <= MAINMENU_LEADERBUTTON_X + leaderSurface->w
                        && event.button.y >= MAINMENU_LEADERBUTTON_Y
                        && event.button.y <= MAINMENU_LEADERBUTTON_Y + leaderSurface->h) {
                            choice = 2;
                            menu = false;
                        }
                    else if (event.button.button == SDL_BUTTON_LEFT
                        && event.button.x >= MAINMENU_EXITBUTTON_X
                        && event.button.x <= MAINMENU_EXITBUTTON_X + exitSurface->w
                        && event.button.y >= MAINMENU_EXITBUTTON_Y
                        && event.button.y <= MAINMENU_EXITBUTTON_Y + exitSurface->h) {
                            choice = 0;
                            menu = false;
                        }
                    break;
            }
        }
        SDL_RenderPresent(renderer);
    }

    // SDL_Delay(1000);

    SDL_DestroyTexture(keyboard);
    SDL_DestroyTexture(exitTexture); // Уничтожаем текстуру
    SDL_FreeSurface(exitSurface); // Освобождаем поверхность
    SDL_DestroyTexture(leaderTexture); 
    SDL_FreeSurface(leaderSurface);
    SDL_DestroyTexture(startTexture); 
    SDL_FreeSurface(startSurface);
    SDL_DestroyTexture(titleTexture);
    SDL_FreeSurface(titleSurface);

    TTF_CloseFont(joystixBig); // Закрываем шрифты
    TTF_CloseFont(joystixSmall);

    Mix_FreeMusic(mainSound);

    SDL_DestroyTexture(redpill);
    SDL_DestroyTexture(bluepill);
    SDL_DestroyTexture(background); // Удаляем текстуру фона
    return choice;
}
