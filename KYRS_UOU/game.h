#pragma once
#include "board.h"
#include <string>

class Game {
public:
    void glavnoeMenu();
private:
    void ivsrobot();
    void aivsAI();
    bool polushil(Board& enemy, int x, int y);
    void stataSoxran(double seconds, int shots, int hits, bool chelovekWin);
};