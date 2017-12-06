#include <math.h>

class Floop {
public:
    int num;
    int floopers;
    Floop() : num(0), floopers(0) {
    }
    void addFloop() {
        num++;
    }
    void workFloopers() {
        num += floopers;
    }
    void buyFlooper() {
        spend(flooperCost());
        floopers++;
    }
    void spend(int less) {
        num = num - less;
    }
    int flooperCost() {
        if (floopers == 0) {
            return 10;
        }
        return pow(2, floopers);
    }
    std::string flooperLabel() {
        // refactor - converting c string to std to c in label.h
        char s[16];
        int flooperCst = flooperCost();
        sprintf(s, "Floopers: %i", floopers);
        std::string result = s;
        return result;
    }

    std::string buyFlooperLabel() {
        // refactor - converting c string to std to c in label.h
        char s[22];
        int flooperCst = flooperCost();
        sprintf(s, "Buy Flooper: %i", flooperCost());
        std::string result = s;
        return result;
    }
    std::string display() {
        // refactor - converting c string to std to c in label.h
        char s[8+9];
        sprintf(s, "Floops: %i", num);
        std::string result = s;
        return result;
    }
};
