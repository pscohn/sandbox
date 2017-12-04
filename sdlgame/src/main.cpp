//#include <sdl2/SdL.h>
#include <sdl2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <stdio.h>
#include <string>
#include "player.h"
#include "window.h"

enum KeyPressSurfaces {
  KEY_PRESS_SURFACE_DEFAULT,
  KEY_PRESS_SURFACE_UP,
  KEY_PRESS_SURFACE_DOWN,
  KEY_PRESS_SURFACE_LEFT,
  KEY_PRESS_SURFACE_RIGHT,
  KEY_PRESS_SURFACE_TOTAL,
};

bool loadMedia();
void close();
SDL_Surface* loadSurface(std::string path);

SDL_Surface* gScreenSurface = NULL;
SDL_Surface* gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];
SDL_Surface* gCurrentSurface = NULL;
SDL_Texture* gHelloWorld = NULL; // image
SDL_Texture* mTexture;
int mWidth, mHeight;
TTF_Font *gFont = NULL;

SDL_Surface* loadSurface(std::string path) {
  SDL_Surface* optimizedSurface = NULL;
  SDL_Surface* loadedSurface = IMG_Load(path.c_str());
  if (loadedSurface == NULL) {
    printf("Unable to load image %s. SDL Error: %s\n", path.c_str(), IMG_GetError());
  } else {
    optimizedSurface = SDL_ConvertSurface(loadedSurface, gScreenSurface->format, 0);
    if (optimizedSurface == NULL) {
      printf("Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
    }
    SDL_FreeSurface(loadedSurface);
  }
  return optimizedSurface;
}

SDL_Texture* loadTexture(std::string path, Window win) {
  // final texture
  SDL_Texture* newTexture = NULL;
  SDL_Surface* loadedSurface = IMG_Load(path.c_str());
  if (loadedSurface == NULL) {
    printf("Unable to load image %s. SDL Error: %s\n", path.c_str(), IMG_GetError());
  } else {
    newTexture = SDL_CreateTextureFromSurface(win.renderer, loadedSurface);
    if (newTexture == NULL) {
      printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
    }
    SDL_FreeSurface(loadedSurface);
  }
  return newTexture;
}

bool loadMedia(Window win) {
  bool success = true;
  gHelloWorld = loadTexture("images/51niHMPxChL.jpg", win);
  if (gHelloWorld == NULL) {
    printf("Unable to load image %s! SDL Error: %s\n", "images/51niHMPxChL.jpg", SDL_GetError());
    success = false;
  }

  gFont = TTF_OpenFont( "fonts/open-sans/OpenSans-Regular.ttf", 38 );
  SDL_Color textColor = { 0, 0, 0 };
  SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, "Hello", textColor);
  if (textSurface == NULL) {
     printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
     success = false;
  } else {
     mTexture = SDL_CreateTextureFromSurface(win.renderer, textSurface);
     if( mTexture == NULL ) {
       printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
       success = false;
     } else {
       //Get image dimensions
       mWidth = textSurface->w;
       mHeight = textSurface->h;
     }
     SDL_FreeSurface( textSurface );
   }
  return success;
}

void close(Window win) {
  printf("closing\n");
  win.close();
//  SDL_FreeSurface(gHelloWorld);
  TTF_CloseFont(gFont);
  gFont = NULL;
  gHelloWorld = NULL;
  TTF_Quit();
  IMG_Quit();
  SDL_Quit();
}

bool doesIntersect(int pointX, int pointY, int targetWidth, int targetHeight, int targetX, int targetY) {
  int targetRight = targetWidth + targetX;
  int targetBottom = targetHeight + targetY;
  if (pointX < targetX) {
    return false;
  } else if (pointY < targetY) {
    return false;
  } else if (pointX > targetRight) {
    return false;
  } else if (pointY > targetBottom) {
    return false;
  }
  return true;
}

void poll_events(SDL_Event e, bool* quit) {
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
      bool clickedButton = doesIntersect(x, y, mWidth, mHeight, ( SCREEN_WIDTH - mWidth ) / 2, ( SCREEN_HEIGHT - mHeight ) / 2);
      if (clickedButton) {
        printf("Clicked button\n");
      }
    }
  }
}

void render(Window win) {
  // SDL_RenderClear( gRenderer );

  // //Render texture to screen
  SDL_RenderCopy( win.renderer, mTexture, NULL, NULL );
  SDL_RenderCopy( win.renderer, gHelloWorld, NULL, NULL );

  // clear screen
  SDL_SetRenderDrawColor( win.renderer, 0x00, 0xFF, 0xFF, 0xFF );
  SDL_RenderClear( win.renderer );

	//Render current frame
	SDL_Rect renderQuad = { ( SCREEN_WIDTH - mWidth ) / 2, ( SCREEN_HEIGHT - mHeight ) / 2, mWidth, mHeight };

	 //Set clip rendering dimensions
  SDL_Rect* clip = NULL;
	if( clip != NULL )
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	SDL_RenderCopyEx( win.renderer, gHelloWorld, clip, &renderQuad, 0.0, NULL, SDL_FLIP_NONE );
	SDL_RenderCopyEx( win.renderer, mTexture, clip, &renderQuad, 0.0, NULL, SDL_FLIP_NONE );

  //Update screen
  SDL_RenderPresent( win.renderer );

  //SDL_BlitSurface(gHelloWorld, NULL, gScreenSurface, NULL);
  //SDL_UpdateWindowSurface(gWindow);

  //Fill the surface white
  // SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0xBB, 0xBB, 0xBB ) );
}

void run() {
  Window window;
  if (!window.init()) {
    printf("Failed to initalize\n");
  } else {
    printf("init done\n");
    //FIX? window passed by value?
    if (!loadMedia(window)) {
      printf("Failed to load media\n");
    } else {
      bool quit = false;
      SDL_Event e; // event handler

      while (!quit) {
        poll_events(e, &quit);
        render(window);
      }
    }
  }
  close(window);
}

int main(int argc, char* args[]) {
  Player pl;
  pl.health = 349;
  pl.debug();
  run();
  return 0;
}
