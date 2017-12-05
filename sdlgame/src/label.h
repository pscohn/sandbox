#ifndef LABEL_H_
#define LABEL_H_

#include "utils.h"

class Label {
public:
    int width;
    int height;
    int x;
    int y;
    SDL_Rect renderQuad;
    std::string text;
    SDL_Texture *texture;
    SDL_Color color;

    Label() : width(100), height(100), x(200), y(200), text("Hello"), texture(NULL) {
        printf("label constructor\n");
        // why?
        SDL_Rect quad = {x, y, width, height};
        renderQuad = quad;
    }

    bool create(std::string text, SDL_Color color, TTF_Font *font, Window window) {
        text = text;
        color = color;
        SDL_Surface *textSurface = TTF_RenderText_Solid(font, "Hello", color);
        if (textSurface == NULL) {
            printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
            return false;
        } else {
            texture = SDL_CreateTextureFromSurface(window.renderer, textSurface);
            if (texture == NULL) {
                printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
                return false;
            } else {
                // Get image dimensions
                width = textSurface->w;
                height = textSurface->h;
                SDL_Rect quad = {x, y, width, height};
                renderQuad = quad;

            }
            SDL_FreeSurface(textSurface);
        }
        return true;
    }

    void debug() {
        printf("%i, %i, %i, %i\n", width, height, x, y);
        if (texture == NULL) {
            printf("texture is null\n");
        }
    }

    void setPos(int x, int y) {
        x = x;
        y = y;
    }

    bool wasClicked(int clickX, int clickY) {
        bool wasClicked = doesIntersect(clickX, clickY, width, height, x, y);
        if (wasClicked == true) {
            printf("ha\n");
        }
        return wasClicked;
    }
};

#endif
