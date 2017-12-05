class Floop {
public:
    int num;
    Floop() : num(0) {
    }
    void addFloop() {
        num++;
    }
    std::string display() {
        // refactor - converting c string to std to c in label.h
        char s[8+4];
        sprintf(s, "Floops: %i", num);
        std::string result = s;
        return result;
    }
};
