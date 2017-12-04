//#include <sdl2/SdL.h>
#include <sdl2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <stdio.h>
#include <string>
#include "window.h"
#include "game.h"
#include "player.h"
#include "button.h"
#include "utils.h"

void poll_events(SDL_Event e, bool* quit, Game* game) {
  while (SDL_PollEvent(&e) != 0) {
    if (e.type == SDL_QUIT) {
      printf("goodbye\n");
      *quit = true;
    } else if (e.type == SDL_KEYDOWN) {
      switch (e.key.keysym.sym) {
        case SDLK_UP:
          printf("up\n");
          break;
        case SDLK_j:
          printf("j\n");
          break;
        default:
          printf("keypress: %i\n", e.key.keysym.sym);
          break;
      }
    } else if (e.type == SDL_MOUSEBUTTONDOWN) {
      int x, y;
      SDL_GetMouseState(&x, &y);
      game->checkButtonsClicked(x, y);
    }
  }
}

void render(Game* game) {
  // clear screen
  SDL_RenderClear( game->window.renderer );

  game->renderButtons();
  game->renderFont();

  //Update screen
  SDL_RenderPresent( game->window.renderer );
}

void run() {
  Game game;
  if (game.init()) {
    printf("init done\n");
    bool quit = false;
    SDL_Event e; // event handler

    while (!quit) {
      poll_events(e, &quit, &game);
      render(&game);
    }
  }
}

int main(int argc, char* args[]) {
  Player pl;
  pl.health = 349;
  pl.debug();
  run();
  return 0;
}
