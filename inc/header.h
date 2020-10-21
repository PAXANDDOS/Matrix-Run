#ifndef ENDGAME_H
#define ENDGAME_H

#define WINDOW_WIDTH    1920
#define WINDOW_HEIGHT   1080
#define NEO_WIDTH       280
#define NEO_HEIGHT      230
#define PIXEL_WIDTH     128
#define PIXEL_HEIGHT    128
#define PIXEL_SIZE      100
#define MOVE_STEP       3
#define JUMP_STEP       7
#define JUMP_HEIGHT     300
#define LEFT_LIMIT      220
#define RIGHT_LIMIT     1000

#define MAINMENU_TITLE_X        100
#define MAINMENU_TITLE_Y        100
#define MAINMENU_STARTBUTTON_X  100
#define MAINMENU_STARTBUTTON_Y  279
#define MAINMENU_LEADERBUTTON_X 100
#define MAINMENU_LEADERBUTTON_Y 349
#define MAINMENU_EXITBUTTON_X   100
#define MAINMENU_EXITBUTTON_Y   419
#define MAINMENU_KEYBOARD_X     100
#define MAINMENU_KEYBOARD_Y     700

#define TEXTSCORE_X             WINDOW_WIDTH - 185
#define TEXTSCORE_Y             20
#define TEXTLIVE_X              20
#define TEXTLIVE_Y              20
#define LIVECOUNT_X             20
#define LIVECOUNT_Y             60
#define SCORE_X                 WINDOW_WIDTH - 185
#define SCORE_Y                 60

#define SCORE_INCREASE          10

// SDL2 Frameworks
#include <SDL2/SDL.h>
#include "SDL2_image/SDL_image.h"
#include "SDL2_mixer/SDL_mixer.h"
#include "SDL2_ttf/SDL_ttf.h"

// Sytem Libriaries
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <time.h>

enum e_orientation {
    POS_RIGHT,
    POS_LEFT
};

typedef struct s_position {
    float x;
    float y;
}              t_position;

typedef struct s_player_stats {
    char names[10][16];
    int scores[10];
}               t_player_stats;

typedef struct s_player {
    t_position pos;
    int health;
    bool death;
    //t_weapon *cur_weapon;
}               t_player;

typedef struct s_bullet {
     t_position pos;
     struct s_bullet *next;
     struct s_bullet *prev;
}              t_bullet;

typedef struct s_enemy {
    t_position pos;
    int health;
    int damage;
    int attack_time;
    unsigned int attack_speed;
    // struct s_enemy *next;
    // struct s_enemy *prev;
}               t_enemy;

// typedef struct s_weapon {
//     double firerate;
//     int damage;
//     int bullet_speed;
//     int type;
//     int bullets_count;
//     t_bullet *bullets_live;
// }               t_weapon;

int mx_start(SDL_Renderer*, int*);
const char *mx_pickmusic();
void mx_scroll_bg(t_position*, int*, float*, float*, int*, float*, float*);
SDL_Renderer *mx_jump(SDL_Renderer*, bool*, bool*, t_position*, int*, t_position*, t_position*, int*, int*, int*, t_position*, float, bool, bool);
int mx_main_menu(SDL_Renderer*);
char *mx_itoa(int number);
int mx_leaderboard(SDL_Renderer*);
t_player_stats mx_read_leaderboard_file(void);
void file_write(t_player_stats);
int mx_game_over(SDL_Renderer*, int );
int mx_input_your_name(SDL_Renderer*, int );
t_player_stats board_updated(t_player_stats , char new_name[16], int);
void mx_draw_bullets(SDL_Renderer*, SDL_Texture*);
bool mx_generate_redpill(t_position*, t_position*, int*, int*);
bool mx_generate_bluepill(t_position*, t_position*, int*, int*);
void mx_pixels(SDL_Renderer*, SDL_Texture*, SDL_Texture*, t_player*, int*, int*, int*, int*, int*, bool, int);

// typedef struct s_gamestate {
//     unsigned int last_time;
//     enum e_scenestate scene;
//     bool input_name;
//     t_player *player;
//     t_enemy *enemies;
//     int kill_count;
//     unsigned int enemies_spawn_time;
//     unsigned int wave_number;
//     t_corpse *corpses;
//     t_ingameSound *sounds;
//     SDL_Texture **textures;
//     Mix_Music *backgroundSound;

// }               t_gamestate;

#endif
