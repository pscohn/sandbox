#ifndef PIANO_H_
#define PIANO_H_
#include "synth.h"
#include "window.h"
#include "player.h"

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
    Player* player;
    int noteLimit;
    Synth synth;

    Piano();
    ~Piano();
    void init(Window* win, TTF_Font* fnt, Player* ply);
    void render();
    void open();
    void close();
    void checkEvent(SDL_Event& e);
    bool loadSounds();
};

#endif
