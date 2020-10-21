#include "header.h"

const char *mx_pickmusic()
{
    int choice = rand() % 5;
    const char *name = NULL;
    switch(choice){
        case 0: name = "./resource/sounds/background_music/hm0.mp3"; break;
        case 1: name = "./resource/sounds/background_music/hm1.mp3"; break;
        case 2: name = "./resource/sounds/background_music/hm2.mp3"; break;
        case 3: name = "./resource/sounds/background_music/hm3.mp3"; break;
        case 4: name = "./resource/sounds/background_music/hm4.mp3"; break;
    }  
    return name;
}
