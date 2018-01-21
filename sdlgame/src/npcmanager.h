#ifndef NPCMANAGER_H_
#define NPCMANAGER_H_

#include "npc.h"
#include "map.h"
#include "texture.h"
#include "label.h"
#include "QuestManager.h"

class NpcManager {
public:
    std::vector<Npc*> npcs;
    SDL_Texture* dialogBg; // 240x72
    Window* window;
    TTF_Font* font;
    std::vector<std::string> currentDialog;
    int dialogIndex;
    int activeNpc;
    QuestManager* questManager;
    Label message;

    NpcManager() {
        message.setPos(340, 580);
        dialogIndex = 0;
        activeNpc = -1;
    }

    void init(Window* win, TTF_Font* fnt, QuestManager* quests) {
        font = fnt;
        window = win;
        dialogBg = loadTexture("images/dialog.png", window->renderer);
        questManager = quests;
    }

    void renderDialog() {
        if (currentDialog.size() > 0) {
            SDL_Rect renderQuad = {320, 560, 240 * 2, 72 * 2};
            SDL_RenderCopy(window->renderer, dialogBg, NULL, &renderQuad);
            std::string m = npcs[activeNpc]->name + ": " + currentDialog[dialogIndex];
            message.create(m, (SDL_Color){0, 0, 0}, font, window);
            SDL_RenderCopy(window->renderer, message.texture, NULL, &message.renderQuad);
        }
    }

    void createNpc() {
        // should load dynamically based on map data?
        Npc* fred = new Npc("Fred", "images/fred.png", "data/fred.xml", CAVE);
        fred->loadTexture(window->renderer);
        npcs.push_back(fred);

        Npc* bob = new Npc("Bob", "images/bob.png", "data/bob.xml", CAVE);
        bob->x = 250;
        bob->loadTexture(window->renderer);
        npcs.push_back(bob);
    }

    void interact(SDL_Rect player, MapType map, std::string interaction) {
        // dialog interactions currently tied to npc actions.
        // technically a player must be next to the character to
        // continue the dialog, and Game must check on NpcManager
        // to check if there is a current dialog happening to stop
        // all movement.
        // Could be refactored to a dialog manager that communicates
        // with game and npc manager
        for (int i = 0; i < npcs.size(); i++) {
            if (npcs[i]->map == map && npcs[i]->canPlayerInteract(player)) {
                if (currentDialog.size() == 0 && interaction == "songBegin") {
                    activeNpc = i;
                    currentDialog = npcs[i]->getSongBeginDialog();
                } else if (currentDialog.size() == 0 && interaction == "songEnd") {
                    activeNpc = i;
                    currentDialog = npcs[i]->getSongEndDialog();
                } else if (currentDialog.size() == 0) {
                    activeNpc = i;
                    int newQuestId = questManager->checkForAvailableQuest(npcs[i]->possibleQuests);
                    if (newQuestId > 0) {
                        questManager->begin(newQuestId);
                        currentDialog = questManager->getDialogStart(newQuestId);
                    } else {
                        currentDialog = npcs[i]->getDialogue();
                    }
                } else if (currentDialog.size() - 1 > dialogIndex) {
                    dialogIndex++;
                } else {
                    currentDialog.clear();
                    dialogIndex = 0;
                    activeNpc = -1;
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
