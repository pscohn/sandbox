#ifndef BUTTON_H_
#define BUTTON_H_

#include "utils.h"

class Button {
public:
  int width;
  int height;
  int x;
  int y;
  SDL_Rect renderQuad;
  std::string label;
  SDL_Texture* texture;
  Button() : width(100), height(100), x(50), y(50), label("Hello"), texture(NULL) {
    SDL_Rect quad = { x, y, width, height };
    renderQuad = quad;
  }

  void setTexture(SDL_Texture* txt) {
    texture = txt;
  }

  void debug() {
    printf("%i, %i, %i, %i\n", width, height, x, y);
    if (texture == NULL) {
      printf("texture is null\n");
    }
  }

  bool wasClicked(int clickX, int clickY) {
    bool wasClicked = doesIntersect(clickX, clickY, width, height, x, y);
    if (wasClicked == true) {
      printf("heya\n");
    }
    return wasClicked;
  }

  // SDL_Rect renderQuad() {
  //   SDL_Rect quad = { x, y, width, height };
  //   return quad;
  // }
};

#endif
