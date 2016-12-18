#include "Sapper.h"
#include <iostream>

#pragma ide diagnostic ignored "CannotResolve"
#pragma ide diagnostic ignored "missing_default_case"

using namespace std;

Sapper::Sapper() {
    Sapper(10, 10, 10);
}

Sapper::Sapper(const int bombs) {
    Sapper(10, 10, bombs);
}

Sapper::~Sapper() {
    for (int i = 0; i < h; ++i) {
        delete[] field[i];
        delete[] field2[i];
    }
    delete[] field;
    delete[] field2;
    delete[] plants;
}

Sapper::Sapper(const int w, const int h, const int bombs) {
    this->bombs = bombs;
    this->w = w;
    this->h = h;
    plants = new int[bombs];
    field = new byte *[h];
    field2 = new byte *[h];
    for (int i = 0; i < h; ++i) {
        field[i] = new byte[w];
        field2[i] = new byte[w];
        for (int j = 0; j < w; ++j) {
            field[i][j] = 0;
            field2[i][j] = FIELD_CLOSED;
        }
    }
    srand(time(0));
    int tmp = w * h - 1;
    for (int i = 0; i < bombs; ++i) {
        plants[i] = rand() % tmp;
        for (int j = 0; j < i; ++j) {
            if (plants[j] == plants[i]) --i;
        }
    }
    for (int i = 0; i < bombs; ++i) {
        int m = plants[i] / w;
        int n = plants[i] % w;
        field[m][n] = FIELD_BOMB;
        for (int k = m - 1; k < m + 2; ++k) {
            if (k < 0 || k > h - 1) continue;
            for (int l = n - 1; l < n + 2; ++l) {
                if (l < 0 || l > w - 1) continue;
                if (field[k][l] == FIELD_BOMB) continue;
                ++field[k][l];
            }
        }
    }
    exec();
}

void Sapper::move(const int i, const int j, const int action) {
    switch (action) {
        case ACT_OPEN:
            if (field2[i][j] == FIELD_FLAG) return;
            if (field[i][j] == FIELD_BOMB) {
                gameOver = REASON_BOMB;
                for (int m = 0; m < bombs; ++m) {
                    field2[plants[m] / w][plants[m] % w] = FIELD_BOMB;
                }
                return;
            }
            if (field2[i][j] == field[i][j]) return;
            field2[i][j] = field[i][j];
            if (field2[i][j] == FIELD_ZERO) {
                for (int m = i - 1; m < i + 2; ++m) {
                    if (m < 0 || m > h - 1) continue;
                    for (int n = j - 1; n < j + 2; ++n) {
                        if (n < 0 || n > w - 1) continue;
                        move(m, n, ACT_OPEN);
                    }
                }
            }
            if (++counter == w * h - bombs) {
                gameOver = REASON_WIN;
                for (int m = 0; m < bombs; ++m) {
                    field2[plants[m] / w][plants[m] % w] = FIELD_FLAG;
                }
            }
            return;
        case ACT_FLAG:
            if (field2[i][j] == field[i][j]) return;
            field2[i][j] = field2[i][j] == FIELD_FLAG ? FIELD_CLOSED : FIELD_FLAG;
            return;
    }
}

void Sapper::repaint() {
    system("clear");
    byte tmp;
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            tmp = field2[i][j];
            cout << (char) (
                    tmp == FIELD_CLOSED ? '-' :
                    tmp == FIELD_FLAG ? 'F' :
                    tmp == FIELD_BOMB ? '*' :
                    tmp == FIELD_ZERO ? ' ' :
                    tmp + 48
            ) << " ";
        }
        cout << "| " << (i + 1) % 10 << endl;
    }
    for (int j = 1; j <= w; ++j) cout << '-' << '-';
    cout << endl;
    for (int j = 1; j <= w; ++j) cout << j % 10 << ' ';
    cout << endl;
}

void Sapper::exec() {
    string buff;
    while (!gameOver) {
        repaint();
        cout << "Coordinates: x - to right (1.." << w << "); y - to down (1.." << h << ");" << endl;
        cout << "Actions: 0 - open; 1 - flag;" << endl;
        cout << "Enter (x y action): ";
        getline(cin, buff);
        int tmp[3];
        for (int i = 0; i < 3; ++i) {
            string temp;
            for (int n = 0; *(buff.data() + n) != ' '; ++n) {
                temp += *(buff.data() + n);
            }
            buff.erase(0, buff.find(' ') + 1);
            tmp[i] = natNumberTextToInt(temp.data());
        }
        if (tmp[0] < 1 || tmp[0] > w) continue;
        if (tmp[1] < 1 || tmp[1] > h) continue;
        if (tmp[2] < 0 || tmp[2] > 1) continue;
        move(tmp[1] - 1, tmp[0] - 1, tmp[2]);
    }
    repaint();
    cout << (gameOver == REASON_WIN ? "You are WIN!!!" :
             gameOver == REASON_BOMB ? "You are loose :'("
                                     : "It is impossible! How did you do this?")
         << endl;
}

int Sapper::natNumberTextToInt(const char *text) {
    if (*text == 0) return -1;
    int out = 0;
    for (int i = 0; *(text + i) != 0; ++i) {
        if (*(text + i) < 48 || *(text + i) > 57) return -1;
        out *= 10;
        out += *(text + i) - 48;
    }
    return out;
}