class Player {
public:
    int health;
    int attack;
    int defense;
    int speed;
    Player() : health(100), attack(10), defense(10), speed(100) {
    }
    void debug() {
        printf("health: %i\n", health);
        printf("attack: %i\n", attack);
        printf("defense: %i\n", defense);
        printf("speed: %i\n", speed);
    }
};
