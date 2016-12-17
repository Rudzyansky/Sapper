#ifndef SAPPER_SAPPER_H
#define SAPPER_SAPPER_H

typedef unsigned char byte;

class Sapper {
    int w, h;
    byte **field;
    byte **field2;
    int bombs;
    int *plants;
    byte gameOver = 0;
    int counter = 0;
    enum Constants {
        FIELD_FLAG = 254,
        FIELD_CLOSED = 255,
        FIELD_ZERO = 0,
        FIELD_BOMB = 9,
        ACT_OPEN = 0,
        ACT_FLAG = 1,
        REASON_WIN = 1,
        REASON_BOMB = 2
    };
    void exec();
    int natNumberTextToInt(const char *text);
public:
    Sapper();
    Sapper(const int bombs);
    Sapper(const int w, const int h, const int bombs);
    void move(const int i, const int j, const int action);
    void repaint();
    ~Sapper();
};

#endif //SAPPER_SAPPER_H
