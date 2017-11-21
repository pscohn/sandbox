#include <SDL.h>
#include <stdio.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
enum KeyPressSurfaces {
  KEY_PRESS_SURFACE_DEFAULT,
  KEY_PRESS_SURFACE_UP,
  KEY_PRESS_SURFACE_DOWN,
  KEY_PRESS_SURFACE_LEFT,
  KEY_PRESS_SURFACE_RIGHT,
  KEY_PRESS_SURFACE_TOTAL,
}


bool init();
bool loadMedia();
void close();
SDL_Surface* loadSurface(std::string path);

SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];
SDL_Surface* gCurrentSurface = NULL;
SDL_Surface* gHelloWorld = NULL; // image

bool init() {
  bool success = true;
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not intialize. SDL_Error: %s\n", SDL_GetError());
    success = false;
  } else {
    // Create window
    gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == NULL) {
      printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
      success = false;
    } else {
       //Get window surface
       gScreenSurface = SDL_GetWindowSurface(gWindow);
     }
  }
  return success;
}

SDL_Surface* loadSurface(std::string path) {
  SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
  if (loadedSurface == NULL) {
    printf("Unable to load image %s. SDL Error: %s\n", path.c_str(), SDL_GetError());
  }
  return loadedSurface;
}

bool loadMedia() {
  bool success = true;
  gHelloWorld = loadSurface("images/hello_world.bmp");
  if (gHelloWorld == NULL) {
    printf("Unable to load image %s! SDL Error: %s\n", "images/hello_world.bmp", SDL_GetError());
    success = false;
  }
  return success;
}

void close() {
  SDL_FreeSurface(gHelloWorld);
  gHelloWorld = NULL;
  SDL_DestroyWindow(gWindow);
  gWindow = NULL;
  SDL_Quit();
}

int main(int argc, char* args[]) {
  if (!init()) {
    printf("Failed to initalize\n");
  } else {
    if (!loadMedia()) {
      printf("Failed to load media\n");
    } else {
      bool quit = false;
      SDL_Event e; // event handler
      while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
          if (e.type == SDL_QUIT) {
            quit = true;
          }
        }
        SDL_BlitSurface(gHelloWorld, NULL, gScreenSurface, NULL);
        SDL_UpdateWindowSurface(gWindow);
      }
    }
  }

  //Fill the surface white
  // SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0xBB, 0xBB, 0xBB ) );

  close();
  return 0;
}
