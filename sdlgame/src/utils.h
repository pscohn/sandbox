#ifndef UTILS_H_
#define UTILS_H_

SDL_Surface* gScreenSurface = NULL;

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



SDL_Texture* loadTexture(std::string path, SDL_Renderer* renderer) {
    // final texture
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL) {
        printf("Unable to load image %s. SDL Error: %s\n", path.c_str(), IMG_GetError());
    } else {
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if (newTexture == NULL) {
            printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        }
        SDL_FreeSurface(loadedSurface);
    }
    return newTexture;
}

bool doesCollide(SDL_Rect a, SDL_Rect b, int range) {
    int leftA = a.x;
    int rightA = a.x + a.w;
    int topA = a.y;
    int bottomA = a.y + a.h;
    int leftB = b.x;
    int rightB = b.x + b.w;
    int topB = b.y;
    int bottomB = b.y + b.h;

    if (bottomA + range < topB) {
        return false;
    }

    if (topA - range > bottomB) {
        return false;
    }

    if (leftA - range > rightB) {
        return false;
    }

    if (rightA + range < leftB) {
        return false;
    }

    return true;
}

bool checkCollision(SDL_Rect a, SDL_Rect b) {
    return doesCollide(a, b, 0);
}

bool canInteract(SDL_Rect a, SDL_Rect b) {
    return doesCollide(a, b, 32);
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

#endif
