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

const int SCREEN_FPS = 60;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;


class Game {
public:
    Window window;
    std::vector<Button> buttons;
    std::vector<Label> labels;

    Piano piano;
    Player player;

    SDL_Rect camera;
    SDL_Texture* bg;

    Tilesheet tilesheet;
    Tilesheet gbsheet;
    Map map;
    Map* currentMap;

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

    Game() {
        printf("Game constructor called\n");
        startTime = 0;
        countedFrames = 0;
    }

    ~Game() {
        printf("Game destructor called\n");
        window.close();
        // TTF_CloseFont(gFont);
        gFont = NULL;
        TTF_Quit();
        IMG_Quit();
        Mix_Quit();
        SDL_Quit();
        // need to free textures/buttons?
    }

    void setStartTime() {
        startTime = SDL_GetTicks();
    }

    void initGB() {
        // avoid duplicate work?
        tilesheet.init("grayscale.png", 400, 40, window.renderer);
        map.init("gb.map", 100, 100, tilesheet.numTiles, NULL, 0);
    }

    void initOverworld() {
        int collisionTiles[15] = {564, 565, 566, 364, 404, 444, 484, 485, 524, 525, 366, 406, 446, 486, 526};
        tilesheet.init("Overworld.png", 1440, 40, window.renderer);
        map.init("overworld.csv", 100, 100, tilesheet.numTiles, &collisionTiles[0], 15);
    }

    bool init() {
        // returns success

        if (!window.init()) {
            printf("Failed to initalize\n");
            return false;
        }

        gFont = TTF_OpenFont("fonts/open-sans/OpenSans-Regular.ttf", 18);

        camera.x = 0;
        camera.y = 0;
        camera.w = SCREEN_WIDTH;
        camera.h = SCREEN_HEIGHT;

        player.loadTexture(window.renderer);

        bg = loadTexture("images/bg.png", window);

        initOverworld();

        if (!floopLabel.create("Floops: 0", (SDL_Color){0, 0, 0}, gFont, &window)) {
            return false;
        }

        flooperLabel.setPos(400, 300);
        if (!flooperLabel.create(floops.flooperLabel(), (SDL_Color){0, 0, 0}, gFont, &window)) {
            return false;
        }

        timeLabel.setPos(200, 100);
        if (!timeLabel.create("Time: 0", (SDL_Color){0, 0, 0}, gFont, &window)) {
            return false;
        }

        fpsTimer.start();
        fpsLabel.setPos(10, 10);
        if (!fpsLabel.create("fps: 0", (SDL_Color){0, 0, 0}, gFont, &window)) {
            return false;
        }

        newFloop.setPos(100, 400);
        if (!newFloop.create("Add Floop", (SDL_Color){0, 0, 0}, gFont, &window)) {
            return false;
        }

        buyFlooper.setPos(400, 400);
        if (!buyFlooper.create(floops.buyFlooperLabel(), (SDL_Color){0, 0, 0}, gFont, &window)) {
            return false;
        }

        if (!piano.loadSounds()) {
            return false;
        }

        return true;
    }

    void run() {
        if (init()) {
            printf("init done\n");
            bool quit = false;
            SDL_Event e; // event handler

            while (!quit) {
                poll_events(e, &quit);
                render();
            }
        }
    }

    void addButton(Button b) {
        buttons.push_back(b);
    }

    void addLabel(Label b) {
        labels.push_back(b);
    }

    void poll_events(SDL_Event e, bool* quit) {
        while (SDL_PollEvent(&e) != 0) {
            player.handleEvent(e);
            if (e.type == SDL_QUIT) {
                printf("goodbye\n");
                *quit = true;
            } else if (e.type == SDL_KEYDOWN) {
                if (piano.isOpen) {
                    piano.checkEvent(e.key.keysym.sym);
                }
                switch (e.key.keysym.sym) {
                case SDLK_q:
                    *quit = true;
                    break;
                case SDLK_m:
                    initGB();
                    break;
                case SDLK_n:
                    initOverworld();
                    break;
                case SDLK_UP:
                    break;
                case SDLK_RETURN:
                    setStartTime();
                    break;
                default:
                    break;
                }
            } else if (e.type == SDL_MOUSEBUTTONDOWN) {
                int x, y;
                SDL_GetMouseState(&x, &y);
                checkButtonsClicked(x, y);
            }
        }
    }

    void render() {
        // clear screen
        SDL_RenderClear(window.renderer);

        capTimer.start();

        player.move(&map);
        camera.x = (player.posX + player.texture.width / 2) - SCREEN_WIDTH / 2;
        camera.y = (player.posY + player.texture.height / 2) - SCREEN_HEIGHT / 2;
        if (camera.x < 0) camera.x = 0;
        if (camera.y < 0) camera.y = 0;
        if (camera.x > map.totalWidth - camera.w) camera.x = map.totalWidth - camera.w;
        if (camera.y > map.totalHeight - camera.h) camera.y = map.totalHeight - camera.h;

        //SDL_Rect renderQuad = {0, 0, camera.w, camera.h};
        //SDL_RenderCopyEx(window.renderer, bg, &camera, &renderQuad, 0.0, NULL, SDL_FLIP_NONE);

        map.render(window.renderer, tilesheet.texture.texture, tilesheet.tileClips, camera);

        player.render(window.renderer, camera.x, camera.y);

        renderButtons();
        renderLabels();

        int frameTicks = capTimer.getTicks();
        if (frameTicks < SCREEN_TICKS_PER_FRAME) {
            SDL_Delay(SCREEN_TICKS_PER_FRAME - frameTicks);
        }

        //Update screen
        SDL_RenderPresent(window.renderer);
    }

    void renderLabels() {
        for (int i = 0; i < labels.size(); i++) {
            SDL_RenderCopy(window.renderer, labels[i].texture, NULL, &labels[i].renderQuad);
        }
        floops.workFloopers();
        floopLabel.updateText(floops.display());
        SDL_RenderCopy(window.renderer, floopLabel.texture, NULL, &floopLabel.renderQuad);
        SDL_RenderCopy(window.renderer, flooperLabel.texture, NULL, &flooperLabel.renderQuad);
        SDL_RenderCopy(window.renderer, newFloop.texture, NULL, &newFloop.renderQuad);
        SDL_RenderCopy(window.renderer, buyFlooper.texture, NULL, &buyFlooper.renderQuad);

        timeText.str("");
        timeText << "Millseconds since startTime: " << SDL_GetTicks() - startTime;
        timeLabel.updateText(timeText.str());
        SDL_RenderCopy(window.renderer, timeLabel.texture, NULL, &timeLabel.renderQuad);

        float avgFps = countedFrames / (fpsTimer.getTicks() / 1000.f);
        countedFrames++;
        fpsText.str("");
        fpsText << "fps: " << avgFps;
        fpsLabel.updateText(fpsText.str());
        SDL_RenderCopy(window.renderer, fpsLabel.texture, NULL, &fpsLabel.renderQuad);
    }

    void renderButtons() {
        for (int i = 0; i < buttons.size(); i++) {
            SDL_RenderCopy(window.renderer, buttons[i].texture, NULL, &buttons[i].renderQuad);
        }
    }

    void checkButtonsClicked(int x, int y) {
        for (int i = 0; i < buttons.size(); i++) {
            buttons[i].wasClicked(x, y);
        }
        for (int i = 0; i < labels.size(); i++) {
            labels[i].wasClicked(x, y);
        }
        if (newFloop.wasClicked(x, y)) {
            floops.addFloop();
            floopLabel.create(floops.display(), (SDL_Color){0, 0, 0}, gFont, &window);
        }
        if (buyFlooper.wasClicked(x, y) && floops.num >= floops.flooperCost()) {
            floops.buyFlooper();
            floopLabel.updateText(floops.display());
            buyFlooper.updateText(floops.buyFlooperLabel());
            flooperLabel.updateText(floops.flooperLabel());
        }
    }
};
