#include "header.h"

int mx_start(SDL_Renderer *renderer, int *score) {
    bool game = true; int escape = 0;   // Keep game running
    SDL_Event event;                    // For event processing

////// Loading required textures
    SDL_Texture* bg1 = IMG_LoadTexture(renderer, "./resource/images/background.png");
    SDL_Texture* bg2 = IMG_LoadTexture(renderer, "./resource/images/background.png");
    SDL_Texture* bg_rail1 = IMG_LoadTexture(renderer, "./resource/images/bg_railings.png");
    SDL_Texture* bg_rail2 = IMG_LoadTexture(renderer, "./resource/images/bg_railings.png");
    SDL_Texture* moon = IMG_LoadTexture(renderer, "./resource/images/moon.png");
    SDL_Texture* neo_standR = IMG_LoadTexture(renderer, "./resource/images/neo_stand.png");
    SDL_Texture* neo_runL = IMG_LoadTexture(renderer, "./resource/images/neo_run.png");
    SDL_Texture* neo_jumpL = IMG_LoadTexture(renderer, "./resource/images/neo_jump.png");
    SDL_Texture* neo_dodge = IMG_LoadTexture(renderer, "./resource/images/neo_dodge.png");
    SDL_Texture* neo_shoot = IMG_LoadTexture(renderer, "./resource/images/neo_shoot.png");
    SDL_Texture* redpill_tex = IMG_LoadTexture(renderer, "./resource/images/redpill.png");
    SDL_Texture* bluepill_tex = IMG_LoadTexture(renderer, "./resource/images/bluepill.png");

    SDL_Texture* smith_standL = IMG_LoadTexture(renderer, "./resource/images/smith_stand.png");
    SDL_Texture* smith_shootL = IMG_LoadTexture(renderer, "./resource/images/smith_shoot.png");
    //SDL_Texture* smith_deathL = IMG_LoadTexture(renderer, "./resource/images/smith_death.png");
    SDL_Texture* bulletTexture = IMG_LoadTexture(renderer, "./resource/images/bluepill.png");

    SDL_Texture* pixelsTexture = IMG_LoadTexture(renderer, "./resource/images/pixels_sprite.png");
    SDL_Texture* dropsTexture = IMG_LoadTexture(renderer, "./resource/images/drops_sprite.png");
////// Loading fonts
    TTF_Font* joystixSmall = TTF_OpenFont("resource/fonts/joystix.ttf", 32);

////// Loading music
    Mix_Music *backgroundSound = Mix_LoadMUS(mx_pickmusic());                       // Picking music for the game
    Mix_Chunk *shootSound = Mix_LoadWAV("./resource/sounds/shoot.wav");             // Shooting sound effect
    //Mix_Chunk *hitSound = Mix_LoadWAV("./resource/sounds/hit2.wav");              // Hit sound effect
    Mix_Chunk *bluepillSound = Mix_LoadWAV("./resource/sounds/item_bluepill.wav");  // Pill picking sound effect
    Mix_Chunk *redpillSound = Mix_LoadWAV("./resource/sounds/item_redpill.wav");    // Pill picking sound effect
    Mix_PlayMusic(backgroundSound, -1);                                             // Playing music and looping
    Mix_Volume(2,MIX_MAX_VOLUME);

////// Text color
    SDL_Color white = { 255, 255, 255, 0 };
    SDL_Color red = { 200, 0, 0, 255 }; 

    const char *scoreChar = NULL;
    SDL_Surface *scoreSurface = NULL;
    SDL_Texture *scoreTexture = NULL;

    const char *live_countChar = NULL;
    SDL_Surface *live_countSurface = NULL;
    SDL_Texture *live_countTexture = NULL;

////// Player & enemy trackers
    t_player neo;
    t_enemy smith;
    t_position redpill_pos, bluepill_pos;
    neo.pos.x = 440, neo.pos.y = WINDOW_HEIGHT - 300;
    neo.health = 4;
    smith.pos.x = WINDOW_WIDTH, smith.pos.y = WINDOW_HEIGHT - 310;
    smith.health = 2;
    redpill_pos.x = neo.pos.x, redpill_pos.y = neo.pos.y;
    bluepill_pos.x = neo.pos.x, bluepill_pos.y = neo.pos.y;

////// Movement trackers
    *score = -SCORE_INCREASE;
    int distance = 0, jump_count = 1, bg_num1 = 1, bg_num2 = 1, redpill_distance = 0, bluepill_distance = 0, pixels_distance = 0;
    enum e_orientation orientation = POS_RIGHT;
    float ground = neo.pos.y;
    float bg1_pos = 0, bg2_pos = WINDOW_WIDTH;
    float bg_rail1_pos = 0, bg_rail2_pos = WINDOW_WIDTH;
    bool walk = false, jump_process = false, jump_down_process = false, runR = false, runL = false, bulletif = true, dodgeon = false, shooting = false;
    bool redpill_pickup = true;

    int last_pixel = 0, px_count = 0, px_count_last = 0, px_cols = 0;
    const char *key; // Input variable

    Uint32 ticks, stand, run, jump, dodge; // Tick counters for animation

///////////////////// Static rectangles
    SDL_Rect moonPos = { 1200, -145, 534, 539 };
    SDL_Rect scoreRect = { SCORE_X, SCORE_Y, 0, 0 };
    SDL_Rect live_countRect = { LIVECOUNT_X, LIVECOUNT_Y, 0, 0 };
///////////////////////////////////////

//////Rendering livecounter and text
    live_countChar = mx_itoa(neo.health - 1); // Live counter
    live_countSurface = TTF_RenderText_Solid(joystixSmall, live_countChar, white);
    live_countTexture = SDL_CreateTextureFromSurface(renderer, live_countSurface);
    live_countRect.x = LIVECOUNT_X;
    live_countRect.y = LIVECOUNT_Y; 
    live_countRect.w = live_countSurface->w; 
    live_countRect.h = live_countSurface->h;

    SDL_Surface* textScoreSurface = TTF_RenderText_Solid(joystixSmall, "SCORE", white);
    SDL_Texture* textScoreTexture = SDL_CreateTextureFromSurface(renderer, textScoreSurface);
    SDL_Rect textScoreRect = {TEXTSCORE_X, TEXTSCORE_Y, textScoreSurface->w, textScoreSurface->h};

    SDL_Surface* textHPSurface = TTF_RenderText_Solid(joystixSmall, "HP", red);
    SDL_Texture* textHPTexture = SDL_CreateTextureFromSurface(renderer, textHPSurface);
    SDL_Rect textHPRect = {TEXTLIVE_X, TEXTLIVE_Y, textHPSurface->w, textHPSurface->h};
/////////////////////////////

    while (game) // Main loop
    {
////////// Getting ticks for each animation
        ticks = SDL_GetTicks();
        stand = (ticks / 300) % 5;
        run = (ticks / 150) % 6;
        jump = jump_count / 11;
        dodge = (ticks / 150) % 4;
        if (jump > 7) jump = 7;
        dodge = (ticks / 150) % 4;
/////////////////////////

////////// Posing objects
        SDL_Rect background1 = { bg1_pos, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
        SDL_Rect background2 = { bg2_pos, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
        SDL_Rect background_rail1 = { bg_rail1_pos, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
        SDL_Rect background_rail2 = { bg_rail2_pos, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
        SDL_Rect srcrectStand = { stand * NEO_WIDTH, 0, NEO_WIDTH, NEO_HEIGHT };
        SDL_Rect srcrectRun = { run * NEO_WIDTH, 0, NEO_WIDTH, NEO_HEIGHT };
        SDL_Rect srcrectJump = { jump * NEO_WIDTH, 0, NEO_WIDTH, NEO_HEIGHT };
        SDL_Rect srcrectDodge = { dodge * NEO_WIDTH, 0, 280, 230 };
        SDL_Rect neo_shootRect = { neo.pos.x, neo.pos.y, 236, 230 };
        SDL_Rect dstrect = { neo.pos.x, neo.pos.y, NEO_WIDTH, NEO_HEIGHT };
        SDL_Rect redpill = { redpill_pos.x, redpill_pos.y, 80, 80 };
        SDL_Rect bluepill = { bluepill_pos.x, bluepill_pos.y, 80, 80 };
        //SDL_Rect bulletPos = { bullet.pos.x, bullet.pos.y, 140, 140 };

        SDL_RenderCopy(renderer, bg1, NULL, &background1);
        SDL_RenderCopy(renderer, bg2, NULL, &background2);
        SDL_RenderCopy(renderer, bg_rail1, NULL, &background_rail1);
        SDL_RenderCopy(renderer, bg_rail2, NULL, &background_rail2);
        SDL_RenderCopy(renderer, moon, NULL, &moonPos);
            
        SDL_RenderCopy(renderer, textScoreTexture, NULL, &textScoreRect);
        SDL_RenderCopy(renderer, textHPTexture, NULL, &textHPRect);

        SDL_RenderCopy(renderer, redpill_tex, NULL, &redpill);
        SDL_RenderCopy(renderer, bluepill_tex, NULL, &bluepill);

        while (SDL_PollEvent(&event)) { // Event handling
            switch (event.type) {
                case SDL_QUIT:
                    game = false;
                    break;
                case SDL_KEYDOWN:
                    walk = true;
                    key = SDL_GetKeyName(event.key.keysym.sym);
                    break;
                case SDL_KEYUP:
                    walk = false;
                    runL = false;
                    runR = false;
                    dodgeon = false;
                    shooting = false;
                    if (neo.pos.x >= RIGHT_LIMIT)
                        neo.pos.x = RIGHT_LIMIT - 1;
                    else if (neo.pos.x <= LEFT_LIMIT)
                        neo.pos.x = LEFT_LIMIT + 1;
                    break;
            }
        }
////////////////////////////////////////////////

////////// Animation for Neo standing and moving
        if(!walk && !(jump_down_process || jump_process)) {
            if (orientation == POS_RIGHT)
                SDL_RenderCopy(renderer, neo_standR, &srcrectStand, &dstrect);
            else
                SDL_RenderCopyEx(renderer, neo_standR, &srcrectStand, &dstrect, 0, 0, SDL_FLIP_HORIZONTAL);
        }
        else {
            if(strcmp(key, "Escape") == 0){
                game = false; 
                escape = 3;  // Return to menu (pressed ESC) 
            }
            else if(strcmp(key, "A") == 0) {
                neo.pos.x -= MOVE_STEP;
                runL = true;
                orientation = POS_LEFT;
                if(neo.pos.x <= LEFT_LIMIT && !(jump_down_process || jump_process))
                    smith.pos.x += MOVE_STEP;
            }
            else if(strcmp(key, "D") == 0) { 
                neo.pos.x += MOVE_STEP;
                runR = true;
                orientation = POS_RIGHT;
                if(neo.pos.x >= RIGHT_LIMIT && !(jump_down_process || jump_process))
                    smith.pos.x -= MOVE_STEP;
            }
            else if (strcmp(key, "S") == 0) {
                dodgeon = true;
            }
            else if(strcmp(key, "W") == 0) { 
                if (!jump_down_process)
                    jump_process = true;
            }
            else
                walk = false;
        }

////////// Score counting and rendering
        bool scoreChanged = mx_generate_redpill(&neo.pos, &redpill_pos, score, &redpill_distance);
        bool healthChanged = mx_generate_bluepill(&neo.pos, &bluepill_pos, &neo.health, &bluepill_distance);

        if(scoreChanged){
            scoreChar = mx_itoa(*score);
            scoreSurface = TTF_RenderText_Solid(joystixSmall, scoreChar, white);
            scoreTexture = SDL_CreateTextureFromSurface(renderer, scoreSurface);
            scoreRect.x = SCORE_X;
            scoreRect.y =  SCORE_Y; 
            scoreRect.w = scoreSurface->w;
            scoreRect.h =  scoreSurface->h;
        
            if(redpill_pickup == true) redpill_pickup = false;
            else Mix_PlayChannel(-1, redpillSound, 0);
            SDL_RenderCopy(renderer, scoreTexture, NULL, &scoreRect);
        }
        else if(healthChanged){
            live_countChar = mx_itoa(neo.health); // Live counter
            live_countSurface = TTF_RenderText_Solid(joystixSmall, live_countChar, white);
            live_countTexture = SDL_CreateTextureFromSurface(renderer, live_countSurface);
            live_countRect.x = LIVECOUNT_X;
            live_countRect.y = LIVECOUNT_Y; 
            live_countRect.w = live_countSurface->w; 
            live_countRect.h = live_countSurface->h;
            
            if(neo.health != 4) Mix_PlayChannel(-1, bluepillSound, 0);
            SDL_RenderCopy(renderer, live_countTexture, NULL, &live_countRect);
        }
        else {
            SDL_RenderCopy(renderer, scoreTexture, NULL, &scoreRect);
            SDL_RenderCopy(renderer, live_countTexture, NULL, &live_countRect);
        }
////////////////////

////////// Animation
        SDL_Renderer *jump_renderer = mx_jump(renderer, &jump_process, &jump_down_process, &neo.pos,
                                              &jump_count, &redpill_pos, &bluepill_pos, &redpill_distance,
                                              &bluepill_distance, &distance, &smith.pos, ground, runL, runR);
        if (jump_process || jump_down_process) {
            if (orientation == POS_LEFT)
                SDL_RenderCopy(jump_renderer, neo_jumpL, &srcrectJump, &dstrect);
            else
                SDL_RenderCopyEx(jump_renderer, neo_jumpL, &srcrectJump, &dstrect, 0, 0, SDL_FLIP_HORIZONTAL);
        }
        else if (runL && walk) {
            distance--;
            redpill_distance--;
            if (neo.pos.x <= LEFT_LIMIT) {
                redpill_pos.x += MOVE_STEP;
                bluepill_pos.x += MOVE_STEP;
            }
            SDL_RenderCopy(renderer, neo_runL, &srcrectRun, &dstrect);
        }
        else if (runR && walk) {
            distance++;
            redpill_distance++;
            if (neo.pos.x >= RIGHT_LIMIT) {
                redpill_pos.x -= MOVE_STEP;
                bluepill_pos.x -= MOVE_STEP;
            }
            SDL_RenderCopyEx(renderer, neo_runL, &srcrectRun, &dstrect, 0, 0, SDL_FLIP_HORIZONTAL);
        }
        else if(dodgeon) SDL_RenderCopy(renderer, neo_dodge, &srcrectDodge, &dstrect);
        else if(shooting) {
            SDL_RenderCopy(renderer, neo_shoot, NULL, &neo_shootRect);
            if (!Mix_Playing(2))
                    Mix_PlayChannelTimed(2, shootSound, 0, 2000);
            //mx_draw_bullets(renderer, bulletTexture);
            bulletif = true;

        }

        mx_pixels(renderer, pixelsTexture, dropsTexture, &neo, &px_cols, &px_count, &px_count_last, &last_pixel, &pixels_distance, scoreChanged, ticks);

        if (neo.health == 0) {
            game = false;
            escape = 4; // Return to death screen
        }

        mx_scroll_bg(&neo.pos, &bg_num1, &bg1_pos, &bg2_pos, &bg_num2, &bg_rail1_pos, &bg_rail2_pos);
        if (distance < 5000)
            pixels_distance++;
        else if (distance < 10000)
            pixels_distance += 2;
        else
            pixels_distance += 3;
        SDL_RenderPresent(renderer);
        SDL_Delay(5);
        SDL_RenderClear(renderer);
    }

////// Clearing textures, stopping music, leaving function
    Mix_FreeMusic(backgroundSound);
    SDL_DestroyTexture(bg1);
    SDL_DestroyTexture(bg2);
    SDL_DestroyTexture(moon);

    SDL_DestroyTexture(pixelsTexture);
    SDL_DestroyTexture(dropsTexture);
    SDL_DestroyTexture(bulletTexture);
    SDL_DestroyTexture(smith_standL);
    SDL_DestroyTexture(smith_shootL);
    //SDL_DestroyTexture(smith_deathL);

    SDL_FreeSurface(scoreSurface);
    SDL_DestroyTexture(scoreTexture);
    SDL_FreeSurface(live_countSurface);
    SDL_DestroyTexture(live_countTexture);

    SDL_DestroyTexture(neo_standR);
    SDL_DestroyTexture(neo_runL);
    SDL_DestroyTexture(neo_jumpL);
    SDL_DestroyTexture(neo_dodge);
    SDL_DestroyTexture(neo_shoot);
    return escape;      
}
