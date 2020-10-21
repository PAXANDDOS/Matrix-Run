#include "header.h"

int mx_input_your_name(SDL_Renderer *renderer, int score){
    char text[16] = "\0";
    bool flag = true;
    bool done = false;
    int choice = 3;
    SDL_StartTextInput();

    TTF_Font* font = TTF_OpenFont("resource/fonts/joystix.ttf", 90); // Загружаем шрифт
    TTF_Font* fontsmall = TTF_OpenFont("resource/fonts/joystix.ttf", 50);
    SDL_Color white = {255, 255, 255, 255};
    SDL_Color red = {255, 0, 0, 255};

    SDL_Surface* titleSurface = TTF_RenderText_Solid(font, "THE MATRIX CONSUMED YOU", red); //Making a title surface
    SDL_Texture* titleTexture = SDL_CreateTextureFromSurface(renderer, titleSurface); //Making a title texture
    SDL_Rect titleRect = {(WINDOW_WIDTH/2) - (titleSurface->w/2), 200, titleSurface->w, titleSurface->h}; //Making a rectangle for a title

    SDL_Surface* enterSurface = TTF_RenderText_Solid(fontsmall, "ENTER YOUR NAME, AGENT", white); //Making a title surface
    SDL_Texture* enterTexture = SDL_CreateTextureFromSurface(renderer, enterSurface); //Making a title texture
    SDL_Rect enterRect = {(WINDOW_WIDTH/2) - (enterSurface->w/2), 450, enterSurface->w, enterSurface->h}; //Making a rectangle for a title

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // the rect color (solid black)
    SDL_Rect background_rect = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};

    while (!done) {

        SDL_RenderFillRect(renderer, &background_rect);
        SDL_RenderCopy(renderer, titleTexture, NULL, &titleRect);
        SDL_RenderCopy(renderer, enterTexture, NULL, &enterRect);

        if (strlen(text)) {
            SDL_Surface *nameSurface = TTF_RenderText_Solid(font, text, white); // Переносим на поверхность текст с заданным шрифтом и цветом
            SDL_Texture *Name = SDL_CreateTextureFromSurface(renderer, nameSurface); //now you can convert it into a texture
            SDL_Rect nameRect = {(WINDOW_WIDTH - 48 * strlen(text))/2, 600, 48 * strlen(text), 48}; //create a rect
            SDL_RenderCopy(renderer, Name, NULL, &nameRect);
            SDL_FreeSurface(nameSurface);
        }
        
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) {
                    done = true;
                    choice = 0;
            }
            else if (event.key.keysym.sym == SDLK_RETURN) {
                if (!strlen(text)) {
                    strcpy(text, "unknown");
                }
                file_write(board_updated(mx_read_leaderboard_file(), text, score));
                done = true;
                score = 0;
            }
            else if (event.key.keysym.sym == SDLK_BACKSPACE) {
                if (flag) {
                    if (strlen(text)) {
                        text[strlen(text)-1]='\0';
                        flag = false;
                    }
                }
                else {
                    flag = true;
                }
            }
            else if (event.type == SDL_TEXTINPUT) {
                if (strlen(text) < 16-1)
                    strcat(text, event.text.text);
            }
        }
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyTexture(enterTexture);
    SDL_FreeSurface(enterSurface);
    SDL_DestroyTexture(titleTexture);
    SDL_FreeSurface(titleSurface);
    TTF_CloseFont(font);
    SDL_StopTextInput();
    return choice;
}

int mx_game_over(SDL_Renderer *renderer, int score) {
    Mix_Music *deathSound = Mix_LoadMUS("./resource/sounds/death_screen/determination.mp3");
    Mix_PlayMusic(deathSound, -1);
    SDL_ShowCursor(SDL_ENABLE);

    int choice = 0;
    if (score) {
            t_player_stats stats = mx_read_leaderboard_file();
            if (stats.scores[10-1] < score)
                choice = mx_input_your_name(renderer, score);
        }
    if (choice == 0) {
        Mix_FreeMusic(deathSound);
        return choice;
    }

    bool menu = true;
    SDL_Event event;

    Mix_Chunk *deathClick = Mix_LoadWAV("./resource/sounds/main_menu/menu_click.wav");

    SDL_Color white = {255, 255, 255, 255}; // Тип для цвета. 4 числа — R, G, B и A, соответственно.
    SDL_Color red = {255, 0, 0, 255};

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // the rect color (solid black)
    SDL_Rect rect = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT}; // the rectangle

    TTF_Font* joystixBig = TTF_OpenFont("resource/fonts/joystix.ttf", 90); //Making a font
    TTF_Font* joystixSmall = TTF_OpenFont("resource/fonts/joystix.ttf", 50);

    SDL_Surface* titleSurface = TTF_RenderText_Solid(joystixBig, "THE MATRIX CONSUMED YOU", red); //Making a title surface
    SDL_Texture* titleTexture = SDL_CreateTextureFromSurface(renderer, titleSurface); //Making a title texture
    SDL_Rect titleRect = {(WINDOW_WIDTH/2) - (titleSurface->w/2), 200, titleSurface->w, titleSurface->h}; //Making a rectangle for a title

    SDL_Surface* startSurface = TTF_RenderText_Solid(joystixSmall, "RESTART", white);
    SDL_Texture* startTexture = SDL_CreateTextureFromSurface(renderer, startSurface);
    SDL_Rect startRect = {(WINDOW_WIDTH/2) - (startSurface->w/2), 450, startSurface->w, startSurface->h};

    SDL_Surface* exitSurface = TTF_RenderText_Solid(joystixSmall, "GO TO MAIN MENU", white);
    SDL_Texture* exitTexture = SDL_CreateTextureFromSurface(renderer, exitSurface);
    SDL_Rect exitRect = {(WINDOW_WIDTH/2) - (exitSurface->w/2), 600, exitSurface->w, exitSurface->h};

    while(menu) {
        SDL_RenderFillRect(renderer, &rect);
        SDL_RenderCopy(renderer, titleTexture, NULL, &titleRect);
        SDL_RenderCopy(renderer, startTexture, NULL, &startRect);
        SDL_RenderCopy(renderer, exitTexture, NULL, &exitRect);

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    menu = false;
                    choice = 0;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    Mix_PlayChannel(-1, deathClick, 0);
                    SDL_Delay(100);
                    if (event.button.button == SDL_BUTTON_LEFT
                        && event.button.x >= (WINDOW_WIDTH/2) - (startSurface->w/2)
                        && event.button.x <= (WINDOW_WIDTH/2) - (startSurface->w/2) + startSurface->w
                        && event.button.y >= 450
                        && event.button.y <= 450 + startSurface->h) {
                        choice = 1;
                        SDL_ShowCursor(SDL_DISABLE);
                        menu = false;
                        }
                    else if (event.button.button == SDL_BUTTON_LEFT
                        && event.button.x >= (WINDOW_WIDTH/2) - (exitSurface->w/2)
                        && event.button.x <= (WINDOW_WIDTH/2) - (exitSurface->w/2) + exitSurface->w
                        && event.button.y >= 600
                        && event.button.y <= 600 + exitSurface->h) {
                        choice = 3;
                        menu = false;
                        }
                    break;
            }
        }
        SDL_RenderPresent(renderer);
    }

    // SDL_Delay(1000);

    SDL_DestroyTexture(exitTexture); // Уничтожаем текстуру
    SDL_FreeSurface(exitSurface); // Освобождаем поверхность
    SDL_DestroyTexture(startTexture); 
    SDL_FreeSurface(startSurface);
    SDL_DestroyTexture(titleTexture);
    SDL_FreeSurface(titleSurface);

    TTF_CloseFont(joystixBig); // Закрываем шрифты
    TTF_CloseFont(joystixSmall);

    Mix_FreeMusic(deathSound);

    return choice;
    
}
