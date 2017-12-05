#include <vector>
#include "window.h"
#include "button.h"
#include "label.h"
#include "floop.h"

class Game {
public:
    Window window;
    std::vector<Button> buttons;
    std::vector<Label> labels;
    Label floopLabel;
    Label newFloop;
    Floop floops;
    TTF_Font *gFont;

    Game() {
        printf("Game constructor called\n");
    }

    ~Game() {
        printf("Game destructor called\n");
        window.close();
        // TTF_CloseFont(gFont);
        gFont = NULL;
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
        // need to free textures/buttons?
    }

    bool init() {
        // returns success

        if (!window.init()) {
            printf("Failed to initalize\n");
            return false;
        }

        gFont = TTF_OpenFont("fonts/open-sans/OpenSans-Regular.ttf", 38);

        Button button;
        SDL_Texture *hello = loadTexture("images/51niHMPxChL.jpg", window);
        if (hello == NULL) {
            printf("Unable to load image %s! SDL Error: %s\n",
                   "images/51niHMPxChL.jpg", SDL_GetError());
            return false;
        }

        button.setTexture(hello);
        addButton(button);
        //
        // Label label;
        // if (!label.create("Floops: 0", (SDL_Color){0, 0, 0}, gFont, window)) {
        //     return false;
        // }
        // addLabel(label);

        if (!floopLabel.create("Floops: 0", (SDL_Color){0, 0, 0}, gFont, window)) {
            return false;
        }

        newFloop.setPos(300, 400);
        if (!newFloop.create("Add Floop", (SDL_Color){0, 0, 0}, gFont, window)) {
            return false;
        }

        return true;
    }

    void addButton(Button b) {
        buttons.push_back(b);
    }

    void addLabel(Label b) {
        labels.push_back(b);
    }

    void renderLabels() {
        for (int i = 0; i < labels.size(); i++) {
            SDL_RenderCopy(window.renderer, labels[i].texture, NULL, &labels[i].renderQuad);
        }
        SDL_RenderCopy(window.renderer, floopLabel.texture, NULL, &floopLabel.renderQuad);
        SDL_RenderCopy(window.renderer, newFloop.texture, NULL, &newFloop.renderQuad);
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
            floopLabel.create(floops.display(), (SDL_Color){0, 0, 0}, gFont, window);
        }
    }
};
