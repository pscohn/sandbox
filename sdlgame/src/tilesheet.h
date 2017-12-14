class Tilesheet {
public:
    int numTiles; // number of total sprites in sheet
    int columns; // number of sprites per row
    std::vector<SDL_Rect> tileClips;
    Texture texture;

    ~Tilesheet() {
        texture.free();
    }

    void init(std::string path, int tiles, int numColumns, SDL_Renderer* renderer) {
        numTiles = tiles;
        columns = numColumns;
        texture.load(path, renderer);
        tileClips.reserve(numTiles);

        int x = 0, y = 0;
        for (int i = 0; i < numTiles; i++) {
            tileClips[i].x = x;
            tileClips[i].y = y;
            tileClips[i].w = TILE_WIDTH;
            tileClips[i].h = TILE_HEIGHT;
            x += TILE_WIDTH;
            if (x >= columns * TILE_WIDTH) {
                // total width of sprite sheet
                x = 0;
                y += TILE_HEIGHT;
            }
        }

    }
};
