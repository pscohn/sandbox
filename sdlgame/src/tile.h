#ifndef TILE_H_
#define TILE_H_

#include "utils.h"

class Tile {
public:
    SDL_Rect box;
    int type;
    bool solid;
    bool wasRendered;
    Tile(int x, int y, int tileType, bool collides) {
        box.x = x;
        box.y = y;
        box.w = TILE_WIDTH * SPRITE_SCALE;
        box.h = TILE_HEIGHT * SPRITE_SCALE;
        type = tileType;
        solid = collides;
        wasRendered = false;
    }

    void debug() {
        printf("tile type: %i, x: %i, y: %i, w: %i, h: %i\n", type, box.x, box.y, box.w, box.h);
    }

    bool render(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect* clip, SDL_Rect& camera) {
        if (checkCollision(box, camera)) {
            SDL_Rect renderQuad = {box.x - camera.x, box.y - camera.y, box.w, box.h};
            SDL_RenderCopy(renderer, texture, clip, &renderQuad);
            return true;
        }
        return false;
    }

};

#endif
