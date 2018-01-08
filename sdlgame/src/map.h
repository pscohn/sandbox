#ifndef MAP_H_
#define MAP_H_

#include "Tmx.h"
#include "tile.h"

struct MapEvent {
    std::string type;
    std::string name;
};

enum MapType {
    MAIN,
    CAVE,
};

class Map {
public:
    Tmx::Map *tmxmap;
    MapType type;
    int totalWidth; // sprite width * map width * sprite scale
    int totalHeight;

    //int tilesX;
    //int tilesY;
    int totalTiles; // total tiles in the level. tilesX * tilesY
    int entryX;
    int entryY;

    //std::string path;
    //std::vector<Tile*> tiles;

    //int totalTileSprites; // number of sprites in the tilesheet

    void init(std::string map) {

        if (map == "overworld.tmx") {
            type = MAIN;
        } else if (map == "cave.tmx") {
            type = CAVE;
        }

        tmxmap = new Tmx::Map();
        tmxmap->ParseFile(map);


        if (tmxmap->HasError())
        {
            printf("error code: %d\n", tmxmap->GetErrorCode());
            printf("error text: %s\n", tmxmap->GetErrorText().c_str());

            // return tmxmap->GetErrorCode();
        }
        printf("Width: %d\n", tmxmap->GetWidth());
        printf("Height: %d\n", tmxmap->GetHeight());
        printf("Tile Width: %d\n", tmxmap->GetTileWidth());
        printf("Tile Height: %d\n", tmxmap->GetTileHeight());
        printf("Layers: %d\n", tmxmap->GetNumTileLayers());

        totalTiles = tmxmap->GetWidth() * tmxmap->GetHeight();
        totalWidth = TILE_WIDTH * tmxmap->GetWidth() * SPRITE_SCALE;
        totalHeight = TILE_HEIGHT * tmxmap->GetHeight() * SPRITE_SCALE;

        entryX = tmxmap->GetProperties().GetIntProperty("entry_x") * SPRITE_SCALE * TILE_WIDTH;
        entryY = tmxmap->GetProperties().GetIntProperty("entry_y") * SPRITE_SCALE * TILE_HEIGHT;
        printf("entry %i %i\n", entryX, entryY);

        //if (tmxmap->GetProperties().GetIntProperty("IntProperty"))
    }

    MapEvent collides(SDL_Rect player) {
        MapEvent event = {"none", "none"};
        if (tmxmap->GetNumObjectGroups() > 0) {
            const Tmx::ObjectGroup *objectGroup = tmxmap->GetObjectGroup(0);
            for (int i = 0; i < objectGroup->GetNumObjects(); i++) {
                const Tmx::Object *object = objectGroup->GetObject(i);
                // printf("Object Name: %s\n", object->GetName().c_str());
                // printf("Object Position: (%03d, %03d)\n", object->GetX(),
                //        object->GetY());
                // printf("Object Size: (%03d, %03d)\n", object->GetWidth(),
                //        object->GetHeight());
                SDL_Rect box =
                {object->GetX() * SPRITE_SCALE, object->GetY() * SPRITE_SCALE, object->GetWidth() * SPRITE_SCALE,
                 object->GetHeight() * SPRITE_SCALE};
                bool collision = checkCollision(player, box);
                if (collision) {
                    if (object->GetType() == "transition") {
                        event.type = "transition";
                        event.name = object->GetProperties().GetStringProperty("transition");
                        break;
                    } else if (object->GetType() == "item") {
                        event.type = "item";
                        break;
                    }
                    event.type = "collision";
                    break;
                }
            }
        }
        return event;
    }

    void render(SDL_Renderer* renderer, SDL_Texture* spritesheet, std::vector<SDL_Rect>& tileClips, SDL_Rect camera) {
        // // why reference parameter
        // for (int i = 0; i < totalTiles; i++) {
        //     bool rendered = tiles[i]->render(renderer, spritesheet, &tileClips[tiles[i]->type], camera);
        //     tiles[i]->wasRendered = rendered;
        // }
        const Tmx::TileLayer *tileLayer = tmxmap->GetTileLayer(0);
        const Tmx::Tileset *tileset = tmxmap->GetTileset(0);

        for (int y = 0; y < tileLayer->GetHeight(); ++y) {
            for (int x = 0; x < tileLayer->GetWidth(); ++x) {
                //printf("%i, %i\n", x, y);
                if (tileLayer->GetTileTilesetIndex(x, y) == -1) {
                } else {
                    // Get the tile's id and gid.
                    int tileId = tileLayer->GetTileId(x, y);
                    //printf("%03d", tileId);
                    SDL_Rect box =
                    {x * SPRITE_SCALE * TILE_WIDTH, y * SPRITE_SCALE * TILE_HEIGHT, SPRITE_SCALE * TILE_WIDTH,
                     SPRITE_SCALE * TILE_HEIGHT};
                    SDL_Rect renderQuad = {box.x - camera.x, box.y - camera.y, box.w, box.h};
                    if (checkCollision(camera, box)) {
                        SDL_RenderCopy(renderer, spritesheet, &tileClips[tileId], &renderQuad);
                    }

                    //printf("%03d(%03d)", tileLayer->GetTileId(x, y), tileLayer->GetTileGid(x, y));

                    // Find a tileset for that id.
                    //const Tmx::Tileset *tileset = map->FindTileset(layer->GetTileId(x, y));

                    if (tileLayer->IsTileFlippedHorizontally(x, y)) {
                    } else {
                    }
                    if (tileLayer->IsTileFlippedVertically(x, y)) {
                    } else {
                    }
                    if (tileLayer->IsTileFlippedDiagonally(x, y)) {
                    } else {
                    }
                }
            }
        }
    }
};

#endif
