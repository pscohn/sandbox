#include <vector>
#include "button.h"

class Game {
public:
  Window window;
  std::vector<Button> buttons;
  SDL_Texture* mTexture;
  TTF_Font *gFont;
  int mWidth, mHeight;
  Game() : gFont(NULL) {
    printf("Game constructor called\n");
  }

  ~Game() {
    printf("Game destructor called\n");
  window.close();
//  SDL_FreeSurface(gHelloWorld);
//  TTF_CloseFont(gFont);
//  gFont = NULL;
//  gHelloWorld = NULL;
    //TTF_CloseFont(gFont);
    gFont = NULL;
  TTF_Quit();
  IMG_Quit();
  SDL_Quit();
  }

  bool init() {
    // returns success

    if (!window.init()) {
      printf("Failed to initalize\n");
      return false;
    }
    Button button;
    SDL_Texture* hello = loadTexture("images/51niHMPxChL.jpg", window);
    if (hello == NULL) {
      printf("Unable to load image %s! SDL Error: %s\n", "images/51niHMPxChL.jpg", SDL_GetError());
      return false;
    }

    button.setTexture(hello);
    addButton(button);

    gFont = TTF_OpenFont( "fonts/open-sans/OpenSans-Regular.ttf", 38 );
    SDL_Color textColor = { 0, 0, 0 };
    SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, "Hello", textColor);
    if (textSurface == NULL) {
       printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
       return false;
    } else {
       mTexture = SDL_CreateTextureFromSurface(window.renderer, textSurface);
       if( mTexture == NULL ) {
         printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
         return false;
       } else {
         //Get image dimensions
         mWidth = textSurface->w;
         mHeight = textSurface->h;
       }
       SDL_FreeSurface( textSurface );
     }
    return true;
  }

  void addButton(Button b) {
    buttons.push_back(b);
  }
  void renderFont() {
    SDL_Rect renderQuad = { ( SCREEN_WIDTH - mWidth ) / 2, ( SCREEN_HEIGHT - mHeight ) / 2, mWidth, mHeight };
    SDL_RenderCopy( window.renderer, mTexture, NULL, &renderQuad );
  }
  void renderButtons() {
    for(int i=0; i < buttons.size(); i++) {
      SDL_RenderCopy( window.renderer, buttons[i].texture, NULL, &buttons[i].renderQuad );
    }
  }

  void checkButtonsClicked(int x, int y) {
    for(int i=0; i < buttons.size(); i++){
      buttons[i].wasClicked(x, y);
    }
  }
};
