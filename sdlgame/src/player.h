#include "texture.h"
#include "map.h"

class Player {
public:
    static const int velocity = 5;
    Texture texture;
    int posX, posY;
    int velX, velY;
    Player() {
        posX = 0;
        posY = 0;
        velX = 0;
        velY = 0;
    }

    ~Player() {
        texture.free();
    }
    void debug() {
    }

    bool loadTexture(SDL_Renderer* renderer) {
        texture.load("link.png", renderer);
        if (texture.texture == NULL) {
            printf("Unable to load image %s! SDL Error: %s\n",
                   "link.png", SDL_GetError());
            return false;
        }
        texture.width = 10 * SPRITE_SCALE;
        texture.height = 16 * SPRITE_SCALE;
        return true;
    }

    void render(SDL_Renderer *renderer, int camX, int camY) {
        texture.render(renderer, posX - camX, posY - camY);
    }

    // bool touchesWall(SDL_Rect box, Map* map, int totalTiles) {
    //     bool collision = false;
    //     // optimize? it loops through every tile
    //     // in map even if not rendered
    //     for (int i = 0; i < totalTiles; i++) {
    //         if (map->tiles[i]->wasRendered == true && map->tiles[i]->solid == true) {
    //             if (checkCollision(box, map->tiles[i]->box)) {
    //                 collision = true;
    //                 // if (map->tiles[i]->type == 487) {
    //                 //     // change maps
    //                 // }
    //                 break;
    //             }
    //         }
    //     }
    //     return collision;
    // }

    MapEvent move(Map* map) {
        posX += velX;
        posY += velY;

        SDL_Rect box = {posX, posY, texture.width, texture.height};

        MapEvent event = map->collides(box);

        bool collision = event.type == "collision";

        if ((posX < 0) || (posX + texture.width > map->totalWidth) || collision) {
            posX -= velX;
        }
        if ((posY < 0) || (posY + texture.height > map->totalHeight) || collision) {
            posY -= velY;
        }
        return event;
    }

    void moveTo(int x, int y) {
        posX = x;
        posY = y;
    }

    void handleEvent(SDL_Event& e) {
        if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
            switch (e.key.keysym.sym) {
            case SDLK_UP:
                velY -= velocity;
                break;
            case SDLK_DOWN:
                velY += velocity;
                break;
            case SDLK_LEFT:
                velX -= velocity;
                break;
            case SDLK_RIGHT:
                velX += velocity;
                break;
            }
        } else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
            switch (e.key.keysym.sym) {
            case SDLK_UP:
                velY += velocity;
                break;
            case SDLK_DOWN:
                velY -= velocity;
                break;
            case SDLK_LEFT:
                velX += velocity;
                break;
            case SDLK_RIGHT:
                velX -= velocity;
                break;
            }
        }
    }
};
