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

    std::string interact(SDL_Rect player) {
        SDL_Rect box = {posX, posY, texture.width, texture.height};
        if (canInteract(player, box)) {
            return getDialogue();
        }
        return "";
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
    SDL_Texture* dialog; // 240x72
    Window* window;
    TTF_Font* font;
    std::string currentDialog;
    Label message;

    NpcManager() {
        message.setPos(340, 580);
    }

    void renderDialog() {
        if (currentDialog != "") {
            SDL_Rect renderQuad = {320, 560, 240 * 2, 72 * 2};
            SDL_RenderCopy(window->renderer, dialog, NULL, &renderQuad);
            message.create(currentDialog, (SDL_Color){0, 0, 0}, font, window);
            SDL_RenderCopy(window->renderer, message.texture, NULL, &message.renderQuad);
        }
    }

    void init(Window* win, TTF_Font* fnt) {
        font = fnt;
        window = win;
        dialog = loadTexture("images/dialog.png", window->renderer);
    }

    void createNpc(SDL_Renderer *renderer) {
        Npc* fred = new Npc();
        fred->loadTexture(renderer);
        npcs.push_back(fred);
    }

    void interact(SDL_Rect player, MapType map) {
        for (int i = 0; i < npcs.size(); i++) {
            if (npcs[i]->map == map) {
                if (currentDialog == "") {
                    currentDialog = npcs[i]->interact(player);
                } else {
                    currentDialog = "";
                }
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
        renderDialog();
        for (int i = 0; i < npcs.size(); i++) {
            if (npcs[i]->map == map) {
                npcs[i]->render(renderer, camX, camY);
            }

        }
    }
};


#endif
