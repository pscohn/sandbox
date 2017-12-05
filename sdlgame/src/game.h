#include <vector>
#include "window.h"
#include "button.h"
#include "label.h"

class Game {
public:
    Window window;
    std::vector<Button> buttons;
    std::vector<Label> labels;
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

        Label label;

        SDL_Color textColor = {0, 0, 0};
        if (!label.create("Hello", textColor, gFont, window)) {
            return false;
        }

        addLabel(label);

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
    }
};
