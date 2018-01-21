#include <sdl2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <sdl2_mixer/SDL_mixer.h>
#include "constants.h"
#include "synth.h"
#include "piano.h"
#include "player.h"
#include "window.h"

const int start = 60;
const int noteA = start;
const int noteW = start + 1;
const int noteS = start + 2;
const int noteE = start + 3;
const int noteD = start + 4;
const int noteF = start + 5;
const int noteT = start + 6;
const int noteG = start + 7;
const int noteY = start + 8;
const int noteH = start + 9;
const int noteU = start + 10;
const int noteJ = start + 11;
const int noteK = start + 12;
const int noteO = start + 13;
const int noteL = start + 14;
const int noteP = start + 15;
const int noteSemi = start + 16;
const int noteQuote = start + 17;

Piano::Piano() {
    isOpen = false;
    noteLimit = 0;
    // c4 = NULL;
    // d4 = NULL;
    // e4 = NULL;
    // f4 = NULL;
    // g4 = NULL;
    // a4 = NULL;
    // b4 = NULL;
    // c5 = NULL;
}

Piano::~Piano() {
    // Mix_FreeChunk(c4);
}

void Piano::init(Window* win, TTF_Font* fnt, Player* ply) {
    font = fnt;
    window = win;
    player = ply;
    pianoBg = loadTexture("images/piano.png", window->renderer);
}

void Piano::render() {
    if (isOpen) {
        SDL_Rect renderQuad = {200, 400, 471, 107};
        SDL_RenderCopy(window->renderer, pianoBg, NULL, &renderQuad);
    }
}

void Piano::open() {
//        if (player->hasItem(BASIC_PIANO)) {
    isOpen = true;
//        }
}

void Piano::close() {
    isOpen = false;
}

void Piano::checkEvent(SDL_Event& e) {
    if (isOpen) {
        if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
            switch (e.key.keysym.sym) {
            case SDLK_v:
                synth.playSong();
                break;
            case SDLK_n:
                synth.nextInstrument();
                break;
            case SDLK_m:
                synth.prevInstrument();
                break;
            case SDLK_a:
                synth.playNote(noteA);
                break;
            case SDLK_s:
                synth.playNote(noteS);
                break;
            case SDLK_d:
                synth.playNote(noteD);
                break;
            case SDLK_f:
                synth.playNote(noteF);
                break;
            case SDLK_g:
                synth.playNote(noteG);
                break;
            case SDLK_h:
                synth.playNote(noteH);
                break;
            case SDLK_j:
                synth.playNote(noteJ);
                break;
            case SDLK_k:
                synth.playNote(noteK);
                break;
            case SDLK_l:
                synth.playNote(noteL);
                break;
            case SDLK_w:
                synth.playNote(noteW);
                break;
            case SDLK_e:
                synth.playNote(noteE);
                break;
            case SDLK_t:
                synth.playNote(noteT);
                break;
            case SDLK_y:
                synth.playNote(noteY);
                break;
            case SDLK_u:
                synth.playNote(noteU);
                break;
            case SDLK_o:
                synth.playNote(noteO);
                break;
            case SDLK_p:
                synth.playNote(noteP);
                break;
            case SDLK_SEMICOLON:
                synth.playNote(noteSemi);
                break;
            case SDLK_QUOTE:
                synth.playNote(noteQuote);
                break;
            case SDLK_c:
                close();
                break;
            default:
                break;
            }
        } else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
            switch (e.key.keysym.sym) {
            case SDLK_a:
                synth.releaseNote(noteA);
                break;
            case SDLK_s:
                synth.releaseNote(noteS);
                break;
            case SDLK_d:
                synth.releaseNote(noteD);
                break;
            case SDLK_f:
                synth.releaseNote(noteF);
                break;
            case SDLK_g:
                synth.releaseNote(noteG);
                break;
            case SDLK_h:
                synth.releaseNote(noteH);
                break;
            case SDLK_j:
                synth.releaseNote(noteJ);
                break;
            case SDLK_k:
                synth.releaseNote(noteK);
                break;
            case SDLK_l:
                synth.releaseNote(noteL);
                break;
            case SDLK_w:
                synth.releaseNote(noteW);
                break;
            case SDLK_e:
                synth.releaseNote(noteE);
                break;
            case SDLK_t:
                synth.releaseNote(noteT);
                break;
            case SDLK_y:
                synth.releaseNote(noteY);
                break;
            case SDLK_u:
                synth.releaseNote(noteU);
                break;
            case SDLK_o:
                synth.releaseNote(noteO);
                break;
            case SDLK_p:
                synth.releaseNote(noteP);
                break;
            case SDLK_SEMICOLON:
                synth.releaseNote(noteSemi);
                break;
            case SDLK_QUOTE:
                synth.releaseNote(noteQuote);
                break;
            default:
                break;
            }
        }
    } else {
        switch (e.key.keysym.sym) {
        case SDLK_s:
            open();
            break;
        default:
            break;
        }

    }
}

bool Piano::loadSounds() {
    c4 = Mix_LoadWAV("sounds/c4.wav");
    if (c4 == NULL) {
        printf("failed to load sound c4: %s", Mix_GetError());
        return false;
    }
    d4 = Mix_LoadWAV("sounds/d4.wav");
    if (d4 == NULL) {
        printf("failed to load sound d4: %s", Mix_GetError());
        return false;
    }
    e4 = Mix_LoadWAV("sounds/e4.wav");
    if (e4 == NULL) {
        printf("failed to load sound e4: %s", Mix_GetError());
        return false;
    }
    f4 = Mix_LoadWAV("sounds/f4.wav");
    if (f4 == NULL) {
        printf("failed to load sound f4: %s", Mix_GetError());
        return false;
    }
    g4 = Mix_LoadWAV("sounds/g4.wav");
    if (g4 == NULL) {
        printf("failed to load sound g4: %s", Mix_GetError());
        return false;
    }
    a4 = Mix_LoadWAV("sounds/a4.wav");
    if (a4 == NULL) {
        printf("failed to load sound a4: %s", Mix_GetError());
        return false;
    }
    b4 = Mix_LoadWAV("sounds/b4.wav");
    if (b4 == NULL) {
        printf("failed to load sound b4: %s", Mix_GetError());
        return false;
    }
    c5 = Mix_LoadWAV("sounds/c5.wav");
    if (c5 == NULL) {
        printf("failed to load sound c5: %s", Mix_GetError());
        return false;
    }
    return true;
}
