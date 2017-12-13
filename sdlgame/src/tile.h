#include "utils.h"

class Tile {
public:
    SDL_Rect box;
    int type;
    Tile(int x, int y, int tileType) {
        box.x = x;
        box.y = y;
        box.w = TILE_WIDTH * SPRITE_SCALE;
        box.h = TILE_HEIGHT * SPRITE_SCALE;
        type = tileType;
    }

    bool render(Window *window, SDL_Texture* texture, SDL_Rect* clip, SDL_Rect& camera) {
        if (checkCollision(box, camera)) {
            SDL_Rect renderQuad = {box.x - camera.x, box.y - camera.y, box.w, box.h};
            SDL_RenderCopy(window->renderer, texture, clip, &renderQuad);
            return true;
        }
        return false;
    }

};
