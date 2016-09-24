#ifndef SAPPER_SAPPER_H
#define SAPPER_SAPPER_H

#include <iostream>

using namespace std;
using std::cout;
using std::endl;

typedef unsigned char byte;

class sapper {
    int w, h;
    byte **field;
    byte **field2;
    int bombs;
    int *plants;
    byte gameOver = 0;
    int counter = 0;
    const byte FIELD_FLAG = 254;
    const byte FIELD_CLOSED = 255;
    enum Constants {
        //FIELD_FLAG = -2,
        //FIELD_CLOSED = -1,
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
    sapper();

    sapper(const int bombs);

    sapper(const int w, const int h);

    sapper(const int w, const int h, const int bombs);

    void move(const int i, const int j, const int action);

    void repaint();

    ~sapper();
};


#endif //SAPPER_SAPPER_H
