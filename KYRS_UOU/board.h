#pragma once
#include <vector>

using namespace std;

class Board {
public:
    Board(int n = 10);
    void randomnoKorably();
    void print(bool showShips) const;
    int  getSize() const { return size; }
    int  vsegoKorably() const { return ships; }

    char get(int x, int y) const { return grid[x][y]; }
    void set(int x, int y, char c) { grid[x][y] = c; }
    bool vistrel(int x, int y) const {
        return grid[x][y] == 'X' || grid[x][y] == '*';
    }

private:
    int size;
    int ships;
    vector<vector<char>> grid;
    void clear();
};