#ifndef GAME_H_
#define GAME_H_

//#include <sdl2/SdL.h>
#include <sdl2_image/SDL_image.h>
#include <sdl2_mixer/SDL_mixer.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <fstream>
#include <stdio.h>
#include <string>
#include <vector>
#include <sstream>
#include "constants.h"
#include "window.h"
#include "button.h"
#include "label.h"
#include "floop.h"
#include "timer.h"
#include "player.h"
#include "piano.h"
#include "utils.h"
#include "tilesheet.h"
#include "tile.h"
#include "map.h"
#include "npcmanager.h"
#include "QuestManager.h"

const int SCREEN_FPS = 60;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

class Game {
public:
    Window window;

    Piano piano;
    Player player;

    SDL_Rect camera;
    SDL_Texture* bg;

    Tilesheet tilesheet;
    Tilesheet gbsheet;
    Map map;
    Map* currentMap;
    NpcManager npcManager;
    QuestManager* questManager;

    bool paused;

    Label floopLabel;
    Label flooperLabel;
    Label newFloop;
    Label buyFlooper;
    Label timeLabel;
    Floop floops;
    TTF_Font *gFont;
    Uint32 startTime;
    std::stringstream timeText;

    // fps counter
    Timer fpsTimer;
    Timer capTimer;
    std::stringstream fpsText;
    int countedFrames;
    Label fpsLabel;

    Game();
    ~Game();

    void setStartTime();
    void loadMap(std::string name);
    bool init();
    void run();
    void poll_events(SDL_Event e, bool* quit);
    void render();
    void renderLabels();
    void checkButtonsClicked(int x, int y);
};

#endif
