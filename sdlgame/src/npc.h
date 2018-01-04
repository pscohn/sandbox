#ifndef NPC_H_
#define NPC_H_

#include <tinyxml2.h>
#include "map.h"
#include "texture.h"

class Npc {
public:
    Texture texture;
    std::string name;
    std::string path;
    std::string dialogPath;
    MapType map;
    int x, y;

    Npc(std::string name, std::string path, std::string dialogPath, MapType map)
        : name(name), path(path), dialogPath(dialogPath), map(map) {
        x = 100;
        y = 100;
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
        doc.LoadFile(dialogPath.c_str());

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
            std::string text = name + ": " + pRoot->GetText();
            message.push_back(text);
        }

        return message;
    }

    bool loadTexture(SDL_Renderer* renderer) {
        texture.load(path, renderer);
        if (texture.texture == NULL) {
            printf("Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
            return false;
        }
        texture.width = texture.width * SPRITE_SCALE;
        texture.height = texture.height * SPRITE_SCALE;
        printf("loaded link\n");
        return true;
    }

    void render(SDL_Renderer *renderer, int camX, int camY) {
        texture.render(renderer, x - camX, y - camY);
    }

    bool canPlayerInteract(SDL_Rect player) {
        SDL_Rect box = {x, y, texture.width, texture.height};
        return canInteract(player, box);
    }

    bool collides(SDL_Rect player) {
        SDL_Rect box = {x, y, texture.width, texture.height};
        return checkCollision(player, box);
    }

    void moveTo(int posX, int posY) {
        x = posX;
        y = posY;
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

    void createNpc() {
        Npc* fred = new Npc("Fred", "images/fred.png", "data/fred.xml", CAVE);
        fred->loadTexture(window->renderer);
        npcs.push_back(fred);

        Npc* bob = new Npc("Bob", "images/bob.png", "data/bob.xml", CAVE);
        bob->x = 250;
        bob->loadTexture(window->renderer);
        npcs.push_back(bob);
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
            if (npcs[i]->map == map && npcs[i]->canPlayerInteract(player)) {
                if (currentDialog.size() == 0) {
                    currentDialog = npcs[i]->getDialogue();
                } else if (currentDialog.size() - 1 > dialogIndex) {
                    dialogIndex++;
                } else {
                    currentDialog.clear();
                    dialogIndex = 0;
                }
                break;
            }
        }
    }

    bool inDialog() {
        return currentDialog.size() > 0;
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
