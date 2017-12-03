//#include <sdl2/SdL.h>
#include <sdl2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <stdio.h>
#include <string>
#include "player.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
enum KeyPressSurfaces {
  KEY_PRESS_SURFACE_DEFAULT,
  KEY_PRESS_SURFACE_UP,
  KEY_PRESS_SURFACE_DOWN,
  KEY_PRESS_SURFACE_LEFT,
  KEY_PRESS_SURFACE_RIGHT,
  KEY_PRESS_SURFACE_TOTAL,
};

bool init();
bool loadMedia();
void close();
SDL_Surface* loadSurface(std::string path);

SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];
SDL_Surface* gCurrentSurface = NULL;
SDL_Surface* gHelloWorld = NULL; // image
SDL_Renderer* gRenderer = NULL;
TTF_Font *gFont = NULL;

bool init() {
  bool success = true;

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not intialize. SDL_Error: %s\n", SDL_GetError());
    success = false;
  } else {
    if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
    {
      printf( "Warning: Linear texture filtering not enabled!" );
    }

    // Create window
    gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == NULL) {
      printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
      success = false;
    } else {
      // create vsynced renderer for window
			//gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( gRenderer != NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			} else {
        printf("hey");
				//Initialize renderer color
				// SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

        // init png loading
        int imgFlags = IMG_INIT_PNG;
        printf("Image flags: %i\n", imgFlags);
        if (!(IMG_Init(imgFlags) & imgFlags)) {
          printf("SDL_Image could not initialize: %s\n", IMG_GetError());
          success = false;
        }

        if (TTF_Init() == -1) {
          printf("SDL_ttf could not initialize: %s\n", TTF_GetError());
          success = false;
        }
      }


        //Get window surface
        gScreenSurface = SDL_GetWindowSurface(gWindow);
    }

  }
  return success;
}

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

bool loadMedia() {
  bool success = true;
  gHelloWorld = loadSurface("images/51niHMPxChL.jpg");
  if (gHelloWorld == NULL) {
    printf("Unable to load image %s! SDL Error: %s\n", "images/51niHMPxChL.jpg", SDL_GetError());
    success = false;
  }
  return success;
}

void close() {
  printf("closing\n");
  SDL_FreeSurface(gHelloWorld);
  TTF_CloseFont(gFont);
  SDL_DestroyWindow(gWindow);
  SDL_DestroyRenderer(gRenderer);
  gFont = NULL;
  gHelloWorld = NULL;
  gWindow = NULL;
  gRenderer = NULL;
  TTF_Quit();
  IMG_Quit();
  SDL_Quit();
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
    }
  }
}

void run() {
  if (!init()) {
    printf("Failed to initalize\n");
  } else {
    printf("init done\n");
    if (!loadMedia()) {
      printf("Failed to load media\n");
    } else {
      bool quit = false;
      SDL_Event e; // event handler
      while (!quit) {
        poll_events(e, &quit);
        gFont = TTF_OpenFont( "16_true_type_fonts/lazy.ttf", 28 );
        SDL_Color textColor = { 0, 0, 0 };
        SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, "Hello", textColor);
        if (textSurface == NULL) {
           printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
        } else {
          // SDL_Texture* mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
          // int mWidth, mHeight;
          // if( mTexture == NULL ) {
          //   printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
          // } else {
          //   //Get image dimensions
          //   mWidth = textSurface->w;
          //   mHeight = textSurface->h;
          // }
          // SDL_FreeSurface( textSurface );
          // SDL_RenderClear( gRenderer );
          //
          // //Render texture to screen
          // SDL_RenderCopy( gRenderer, mTexture, NULL, NULL );

          //mTexture.render( ( SCREEN_WIDTH - mWidth ) / 2, ( SCREEN_HEIGHT - mHeight ) / 2 );
        	// SDL_Rect renderQuad = { ( SCREEN_WIDTH - mWidth ) / 2, ( SCREEN_HEIGHT - mHeight ) / 2, mWidth, mHeight };
          //
        	// //Set clip rendering dimensions
          // SDL_Rect* clip = NULL;
        	// if( clip != NULL )
        	// {
        	// 	renderQuad.w = clip->w;
        	// 	renderQuad.h = clip->h;
        	// }

        	//Render to screen
        	//SDL_RenderCopyEx( gRenderer, mTexture, clip, &renderQuad, 0, NULL, SDL_FLIP_NONE );

          //Update screen
        //  SDL_RenderPresent( gRenderer );

        }
        //SDL_BlitSurface(gHelloWorld, NULL, gScreenSurface, NULL);
        SDL_UpdateWindowSurface(gWindow);
      }
    }
  }
  //Fill the surface white
  // SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0xBB, 0xBB, 0xBB ) );

  close();
}

int main(int argc, char* args[]) {
  Player pl;
  pl.health = 349;
  pl.debug();
  run();
  return 0;
}
