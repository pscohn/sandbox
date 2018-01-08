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
    TTF_Font *font;
    Window *window;

    Label() : width(100), height(100), x(200), y(200), texture(NULL) {
        renderQuad.x = x;
        renderQuad.y = y;
        renderQuad.w = width;
        renderQuad.h = height;
    }

    bool create(std::string newText, SDL_Color newColor, TTF_Font *fnt, Window *win) {
        text = newText;
        color = newColor;
        window = win;
        font = fnt;
        bool success = updateTexture();
        return success;
    }

    bool updateTexture() {
        SDL_Surface *textSurface = TTF_RenderText_Solid(font, text.c_str(), color);
        if (textSurface == NULL) {
            printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
            return false;
        } else {
            texture = SDL_CreateTextureFromSurface(window->renderer, textSurface);
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

    void updateText(std::string newText) {
        text = newText;
        updateTexture();
    }

    void debug() {
        printf("w: %i, h: %i, x: %i, y: %i\n", width, height, x, y);
        if (texture == NULL) {
            printf("texture is null\n");
        }
    }

    void setPos(int newX, int newY) {
        x = newX;
        y = newY;
        renderQuad.x = newX;
        renderQuad.y = newY;
    }

    bool wasClicked(int clickX, int clickY) {
        bool wasClicked = doesIntersect(clickX, clickY, width, height, x, y);
        return wasClicked;
    }
};

#endif
