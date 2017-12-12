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

    Piano() {
        isOpen = false;
        c4 = NULL;
        d4 = NULL;
        e4 = NULL;
        f4 = NULL;
        g4 = NULL;
        a4 = NULL;
        b4 = NULL;
        c5 = NULL;
    }

    ~Piano() {
        Mix_FreeChunk(c4);
    }

    void checkEvent(SDL_Keycode key) {
        Mix_HaltChannel(-1); // halts all channels
        switch (key) {
        case SDLK_a:
            Mix_PlayChannel(-1, c4, 0);
            break;
        case SDLK_s:
            Mix_PlayChannel(-1, d4, 0);
            break;
        case SDLK_d:
            Mix_PlayChannel(-1, e4, 0);
            break;
        case SDLK_f:
            Mix_PlayChannel(-1, f4, 0);
            break;
        case SDLK_g:
            Mix_PlayChannel(-1, g4, 0);
            break;
        case SDLK_h:
            Mix_PlayChannel(-1, a4, 0);
            break;
        case SDLK_j:
            Mix_PlayChannel(-1, b4, 0);
            break;
        case SDLK_k:
            Mix_PlayChannel(-1, c5, 0);
            break;
        default:
            break;
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
