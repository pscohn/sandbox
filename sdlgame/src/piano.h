#include "synth.h"

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
                case SDLK_a:
                    synth.playNote(60);
                    break;
                case SDLK_s:
                    synth.playNote(62);
                    break;
                case SDLK_d:
                    synth.playNote(64);
                    break;
                case SDLK_f:
                    synth.playNote(65);
                    break;
                case SDLK_g:
                    synth.playNote(67);
                    break;
                case SDLK_h:
                    synth.playNote(69);
                    break;
                case SDLK_j:
                    synth.playNote(71);
                    break;
                case SDLK_k:
                    synth.playNote(72);
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
                    synth.releaseNote(60);
                    break;
                case SDLK_s:
                    synth.releaseNote(62);
                    break;
                case SDLK_d:
                    synth.releaseNote(64);
                    break;
                case SDLK_f:
                    synth.releaseNote(65);
                    break;
                case SDLK_g:
                    synth.releaseNote(67);
                    break;
                case SDLK_h:
                    synth.releaseNote(69);
                    break;
                case SDLK_j:
                    synth.releaseNote(71);
                    break;
                case SDLK_k:
                    synth.releaseNote(72);
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
