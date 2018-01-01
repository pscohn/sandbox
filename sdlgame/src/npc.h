#ifndef NPC_H_
#define NPC_H_

#include "map.h"
#include "texture.h"

class Npc {
public:
    Texture texture;
    std::string name;
    MapType map;
    int posX, posY;

    Npc() {
        name = "Fred";
        posX = 100;
        posY = 100;
        map = CAVE;
        //texture = new Texture();
    }

    ~Npc() {
        texture.free();
    }

    void debug() {
    }

    std::string getDialogue() {
        return "Hello";
    }

    bool loadTexture(SDL_Renderer* renderer) {
        texture.load("man.png", renderer);
        if (texture.texture == NULL) {
            printf("Unable to load image %s! SDL Error: %s\n",
                   "link.png", SDL_GetError());
            return false;
        }
        texture.width = 16 * SPRITE_SCALE;
        texture.height = 16 * SPRITE_SCALE;
        printf("loaded link\n");
        return true;
    }

    void render(SDL_Renderer *renderer, int camX, int camY) {
        texture.render(renderer, posX - camX, posY - camY);
    }

    void interact(SDL_Rect player) {
        SDL_Rect box = {posX, posY, texture.width, texture.height};
        if (canInteract(player, box)) {
            printf("%s\n", getDialogue().c_str());
        }
    }

    bool collides(SDL_Rect player) {
        SDL_Rect box = {posX, posY, texture.width, texture.height};
        return checkCollision(player, box);
    }

    void moveTo(int x, int y) {
        posX = x;
        posY = y;
    }
};

class NpcManager {
public:
    std::vector<Npc*> npcs;
    void createNpc(SDL_Renderer *renderer) {
        Npc* fred = new Npc();
        fred->loadTexture(renderer);
        npcs.push_back(fred);
    }
    void interact(SDL_Rect player, MapType map) {
        for (int i = 0; i < npcs.size(); i++) {
            if (npcs[i]->map == map) {
                npcs[i]->interact(player);
            }

        }
    }
    bool collides(SDL_Rect player, MapType map) {
        for (int i = 0; i < npcs.size(); i++) {
            if (npcs[i]->map == map) {
                if (npcs[i]->collides(player)) {
                    return true;
                }
            }

        }
        return false;
    }
    void render(SDL_Renderer *renderer, int camX, int camY, MapType map) {
        for (int i = 0; i < npcs.size(); i++) {
            if (npcs[i]->map == map) {
                npcs[i]->render(renderer, camX, camY);
            }

        }
    }
};


#endif
