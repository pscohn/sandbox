#ifndef NPC_H_
#define NPC_H_

#include <tinyxml2.h>
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

    std::vector<std::string> getDialogue() {
        // TODO add error handling

        std::vector<std::string> message;


        tinyxml2::XMLDocument doc;
        tinyxml2::XMLElement* pRoot;
        doc.LoadFile("data/conv.xml");


        if (doc.FirstChild()->FirstChildElement("dialog") == NULL) {
            return message;
        }

        int possibleMessages = 0;
        tinyxml2::XMLElement* countRoot;
        for (countRoot = doc.FirstChild()->FirstChildElement("dialog"); countRoot != nullptr;
             countRoot = countRoot->NextSiblingElement("dialog")) {
            possibleMessages++;
        }
        int randomConversation = rand() % possibleMessages;

        pRoot = doc.FirstChild()->FirstChildElement("dialog");
        for (int i = 0; i < randomConversation; i++) {
            pRoot = pRoot->NextSiblingElement("dialog");
        }

        for (pRoot = pRoot->FirstChildElement("element"); pRoot != nullptr;
             pRoot = pRoot->NextSiblingElement("element")) {
            std::string text = pRoot->GetText();
            message.push_back(text);
        }

        return message;
    }

    bool loadTexture(SDL_Renderer* renderer) {
        texture.load("man.png", renderer);
        if (texture.texture == NULL) {
            printf("Unable to load image %s! SDL Error: %s\n",
                   "man.png", SDL_GetError());
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

    std::vector<std::string> interact(SDL_Rect player) {
        SDL_Rect box = {posX, posY, texture.width, texture.height};
        if (canInteract(player, box)) {
            return getDialogue();
        }
        std::vector<std::string> message;
        return message;
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
    SDL_Texture* dialogBg; // 240x72
    Window* window;
    TTF_Font* font;
    std::vector<std::string> currentDialog;
    int dialogIndex;
    Label message;

    NpcManager() {
        message.setPos(340, 580);
        dialogIndex = 0;
    }

    void init(Window* win, TTF_Font* fnt) {
        font = fnt;
        window = win;
        dialogBg = loadTexture("images/dialog.png", window->renderer);
    }

    void renderDialog() {
        if (currentDialog.size() > 0) {
            SDL_Rect renderQuad = {320, 560, 240 * 2, 72 * 2};
            SDL_RenderCopy(window->renderer, dialogBg, NULL, &renderQuad);
            message.create(currentDialog[dialogIndex], (SDL_Color){0, 0, 0}, font, window);
            SDL_RenderCopy(window->renderer, message.texture, NULL, &message.renderQuad);
        }
    }

    void createNpc(SDL_Renderer *renderer) {
        Npc* fred = new Npc();
        fred->loadTexture(renderer);
        npcs.push_back(fred);
    }

    void interact(SDL_Rect player, MapType map) {
        // dialog interactions currently tied to npc actions.
        // technically a player must be next to the character to
        // continue the dialog, and Game must check on NpcManager
        // to check if there is a current dialog happening to stop
        // all movement.
        // Could be refactored to a dialog manager that communicates
        // with game and npc manager
        for (int i = 0; i < npcs.size(); i++) {
            if (npcs[i]->map == map) {
                if (currentDialog.size() == 0) {
                    currentDialog = npcs[i]->interact(player);
                } else if (currentDialog.size() - 1 > dialogIndex) {
                    dialogIndex++;
                } else {
                    currentDialog.clear();
                    dialogIndex = 0;
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
