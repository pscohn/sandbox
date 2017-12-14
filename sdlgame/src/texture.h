#ifndef TEXTURE_H_
#define TEXTURE_H_

class Texture {
public:
    SDL_Texture* texture;
    int width;
    int height;
    Texture() {
        texture = NULL;
    }

    ~Texture() {
        free();
    }

    void free() {
        if (texture != NULL) {
            SDL_DestroyTexture(texture);
            texture = NULL;
            width = 0;
            height = 0;
        }
    }

    void render(SDL_Renderer* renderer, int x, int y) {
        SDL_Rect renderQuad = {x, y, width, height};
        SDL_RenderCopy(renderer, texture, NULL, &renderQuad);
    }

    void load(std::string path, SDL_Renderer* renderer) {
        // final texture
        SDL_Surface* loadedSurface = IMG_Load(path.c_str());
        if (loadedSurface == NULL) {
            printf("Unable to load image %s. SDL Error: %s\n", path.c_str(), IMG_GetError());
        } else {
            texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
            if (texture == NULL) {
                printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
            } else {
                width = loadedSurface->w;
                height = loadedSurface->h;
            }
            SDL_FreeSurface(loadedSurface);
        }
    }
};

#endif
