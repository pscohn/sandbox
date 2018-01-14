#include "synth.h"

int start = 60;
int noteA = start;
int noteW = start + 1;
int noteS = start + 2;
int noteE = start + 3;
int noteD = start + 4;
int noteF = start + 5;
int noteT = start + 6;
int noteG = start + 7;
int noteY = start + 8;
int noteH = start + 9;
int noteU = start + 10;
int noteJ = start + 11;
int noteK = start + 12;
int noteO = start + 13;
int noteL = start + 14;
int noteP = start + 15;
int noteSemi = start + 16;
int noteQuote = start + 17;

class Piano {
private:
    Mix_Chunk *c4;
    Mix_Chunk *d4;
    Mix_Chunk *e4;
    Mix_Chunk *f4;
    Mix_Chunk *g4;
    Mix_Chunk *a4;
    Mix_Chunk *b4;
    Mix_Chunk *c5;

public:
    bool isOpen;
    void checkEvent();
    SDL_Texture* pianoBg;
    Window* window;
    TTF_Font* font;
    int noteLimit;
    Synth synth;

    Piano() {
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

    ~Piano() {
        // Mix_FreeChunk(c4);
    }

    void init(Window* win, TTF_Font* fnt) {
        font = fnt;
        window = win;
        pianoBg = loadTexture("images/piano.png", window->renderer);
    }

    void render() {
        if (isOpen) {
            SDL_Rect renderQuad = {200, 400, 471, 107};
            SDL_RenderCopy(window->renderer, pianoBg, NULL, &renderQuad);
        }
    }

    void open() {
        isOpen = true;
    }
    void close() {
        isOpen = false;
    }

    void checkEvent(SDL_Event& e) {
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

    bool loadSounds() {
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
};
