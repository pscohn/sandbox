class Window {
public:
    SDL_Window* window;
    SDL_Renderer* renderer;
    int width;
    int height;
    int someInt;
    Window() : window(NULL), width(640), height(480), renderer(NULL), someInt(0) {
    }

    void set(int integer) {
        someInt = integer;
    }

    void close() {
        SDL_DestroyWindow(window);
        SDL_DestroyRenderer(renderer);
        window = NULL;
        renderer = NULL;
    }

    bool init() {
        bool success = true;
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            printf("SDL could not intialize. SDL_Error: %s\n", SDL_GetError());
            success = false;
        } else {
            if (!SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) ) {
                printf( "Warning: Linear texture filtering not enabled!" );
            }

            // Create window
            window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width,
                                      height, SDL_WINDOW_SHOWN);
            if (window == NULL) {
                printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
                success = false;
            } else {
                // create vsynced renderer for window
                renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED);
                if( renderer == NULL )
                {
                    printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                    success = false;
                } else {
                    //Initialize renderer color
                    SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );

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
            }
        }
        return success;
    }
};
