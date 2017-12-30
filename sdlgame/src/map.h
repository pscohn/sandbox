#ifndef MAP_H_
#define MAP_H_

#include "tile.h"

class Map {
public:
    int totalWidth; // sprite width * map width * sprite scale
    int totalHeight;

    int tilesX;
    int tilesY;
    int totalTiles; // total tiles in the level. tilesX * tilesY

    std::string path;
    std::vector<Tile*> tiles;

    int totalTileSprites; // number of sprites in the tilesheet

    void render(SDL_Renderer* renderer, SDL_Texture* spritesheet, std::vector<SDL_Rect>& tileClips, SDL_Rect camera) {
        // why reference parameter
        for (int i = 0; i < totalTiles; i++) {
            bool rendered = tiles[i]->render(renderer, spritesheet, &tileClips[tiles[i]->type], camera);
            tiles[i]->wasRendered = rendered;
        }
    }

    void init(std::string map, int tilesXNum, int tilesYNum, int totalTileSpritesNum, int* collisionTiles,
              int numCollisionTiles) {
        path = map;
        totalTiles = tilesXNum * tilesYNum;
        tilesX = tilesXNum;
        tilesY = tilesYNum;
        totalWidth = TILE_WIDTH * tilesX * SPRITE_SCALE;
        totalHeight = TILE_HEIGHT * tilesY * SPRITE_SCALE;

        totalTileSprites = totalTileSpritesNum;

        tiles.reserve(totalTiles);
        setTiles(collisionTiles, numCollisionTiles);
    }

    bool setTiles(int* collisionTiles, int numCollisionTiles) {
        bool tilesLoaded = true;
        int x = 0, y = 0; // tile offsets
        std::ifstream map(path);
        if (!map.is_open()) {
            printf("Unable to load map file\n");
            tilesLoaded = false;
        } else {
            for (int i = 0; i < totalTiles; i++) {
                int tileType;
                map >> tileType;
                if (map.fail()) {
                    // stop loading map
                    printf("Error loading map, unexpected EOF\n");
                    tilesLoaded = false;
                    break;
                }

                // check if number is valid
                if ((tileType >= 0) && (tileType < totalTileSprites)) {
                    bool collides = false;
                    for (int j = 0; j < numCollisionTiles; j++) {
                        // could optimize with tilesheet format that
                        // includes collision data?
                        if (tileType == collisionTiles[j]) {
                            collides = true;
                            break;
                        }
                    }
                    tiles[i] = new Tile(x, y, tileType, collides);
                } else {
                    printf("Invalid tile number at %d\n", i);
                    tilesLoaded = false;
                    break;
                }
                x += TILE_WIDTH * SPRITE_SCALE;
                if (x >= totalWidth) {
                    x = 0;
                    y += TILE_WIDTH * SPRITE_SCALE;
                }
            }
        }
        map.close(); // close file
        return tilesLoaded;
    }

};

#endif
