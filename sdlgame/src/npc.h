#ifndef NPC_H_
#define NPC_H_

#include "map.h"
#include "texture.h"
#include "datareader.h"

class Npc {
public:
    Texture texture;
    std::string name;
    std::string path;
    std::string dialogPath;
    MapType map;
    std::vector<int> possibleQuests;
    int x, y;

    Npc(std::string name, std::string path, std::string dialogPath, MapType map)
        : name(name), path(path), dialogPath(dialogPath), map(map) {
        x = 100;
        y = 100;
        possibleQuests = reader::getNpcQuests(dialogPath);
        if (possibleQuests.size() > 0) {
            printf("quest: %i\n", possibleQuests[0]);
        }
    }

    ~Npc() {
        texture.free();
    }

    void debug() {
    }

    std::vector<std::string> getDialogue() {
        return reader::getRandomDialog(dialogPath);
    }

    std::vector<int> checkForQuest() {
        return reader::getNpcQuests(dialogPath);
    }

    std::vector<std::string> getSongBeginDialog() {
        return reader::getRandomSongBeginDialog(dialogPath);
    }

    std::vector<std::string> getSongEndDialog() {
        return reader::getRandomSongEndDialog(dialogPath);
    }

    bool loadTexture(SDL_Renderer* renderer) {
        texture.load(path, renderer);
        if (texture.texture == NULL) {
            printf("Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
            return false;
        }
        texture.width = texture.width * SPRITE_SCALE;
        texture.height = texture.height * SPRITE_SCALE;
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

#endif
