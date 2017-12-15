#include "texture.h"
#include "map.h"

class Player {
public:
    int health;
    int attack;
    int defense;
    int speed;

    static const int velocity = 5;
    Texture texture;
    int posX, posY;
    int velX, velY;
    Player() : health(100), attack(10), defense(10), speed(100) {
        posX = 0;
        posY = 0;
        velX = 0;
        velY = 0;
    }

    ~Player() {
        texture.free();
    }
    void debug() {
        printf("health: %i\n", health);
        printf("attack: %i\n", attack);
        printf("defense: %i\n", defense);
        printf("speed: %i\n", speed);
    }

    bool loadTexture(SDL_Renderer* renderer) {
        texture.load("images/51niHMPxChL.jpg", renderer);
        if (texture.texture == NULL) {
            printf("Unable to load image %s! SDL Error: %s\n",
                   "images/51niHMPxChL.jpg", SDL_GetError());
            return false;
        }
        texture.width = 50;
        texture.height = 50;
        return true;
    }

    void render(SDL_Renderer *renderer, int camX, int camY) {
        texture.render(renderer, posX - camX, posY - camY);
    }

    bool touchesWall(SDL_Rect box, Map* map) {
        bool collision = false;
        // optimize? it goes through ever tile
        // in map even if not rendered
        for (int i = 0; i < map->totalTiles; i++) {
            if (map->tiles[i]->solid == true) {
                if (checkCollision(box, map->tiles[i]->box)) {
                    collision = true;
                    break;
                }
            }
        }
        return collision;
    }

    void move(Map* map) {
        posX += velX;
        posY += velY;

        SDL_Rect box = {posX, posY, texture.width, texture.height};

        if ((posX < 0) || (posX + texture.width > map->totalWidth) || (touchesWall(box, map))) {
            posX -= velX;
        }
        if ((posY < 0) || (posY + texture.height > map->totalHeight) || (touchesWall(box, map))) {
            posY -= velY;
        }
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
