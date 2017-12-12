
class Player {
public:
    int health;
    int attack;
    int defense;
    int speed;

    static const int velocity = 5;
    SDL_Texture* texture;
    int w, h;
    int posX, posY;
    int velX, velY;
    Player() : health(100), attack(10), defense(10), speed(100) {
        posX = 0;
        posY = 0;
        velX = 0;
        velY = 0;
        w = 50;
        h = 50;
        texture = NULL;
    }

    ~Player() {
        texture = NULL;
    }
    void debug() {
        printf("health: %i\n", health);
        printf("attack: %i\n", attack);
        printf("defense: %i\n", defense);
        printf("speed: %i\n", speed);
    }

    bool loadTexture(Window *window) {
        texture = ::loadTexture("images/51niHMPxChL.jpg", *window);
        if (texture == NULL) {
            printf("Unable to load image %s! SDL Error: %s\n",
                   "images/51niHMPxChL.jpg", SDL_GetError());
            return false;
        }
        return true;
    }

    void render(Window *window, int camX, int camY) {
        printf("camY %i\n", camY);
        SDL_Rect renderQuad = {posX - camX, posY - camY, w, h};
        SDL_RenderCopy(window->renderer, texture, NULL, &renderQuad);
    }

    void move() {
        posX += velX;
        posY += velY;

        if ((posX < 0) || posX + w > LEVEL_WIDTH) {
            posX -= velX;
        }
        if ((posY < 0) || posY + h > LEVEL_HEIGHT) {
            posY -= velY;
        }
    }

    void handleEvent(SDL_Event& e) {
        if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
            switch (e.key.keysym.sym) {
            case SDLK_UP:
                velY -= velocity;
                break;
            case SDLK_DOWN:
                velY += velocity;
                break;
            case SDLK_LEFT:
                velX -= velocity;
                break;
            case SDLK_RIGHT:
                velX += velocity;
                break;
            }
        } else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
            switch (e.key.keysym.sym) {
            case SDLK_UP:
                velY += velocity;
                break;
            case SDLK_DOWN:
                velY -= velocity;
                break;
            case SDLK_LEFT:
                velX += velocity;
                break;
            case SDLK_RIGHT:
                velX -= velocity;
                break;
            }

        }
    }
};
