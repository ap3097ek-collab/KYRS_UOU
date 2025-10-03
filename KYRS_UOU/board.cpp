#include "board.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

Board::Board(int n) : size(n), ships(10), grid(n, vector<char>(n, 'O')) {}

void Board::clear() {
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            grid[i][j] = 'O';
}

void Board::randomnoKorably() {
    clear();
    int placed = ships;
    while (placed > 0) {
        int x = rand() % size;
        int y = rand() % size;
        if (grid[x][y] == 'O') {
            grid[x][y] = 'S';
            placed--;
        }
    }
}

void Board::print(bool pokathKorabl) const {
    cout << "   ";
    for (int j = 0; j < size; j++) cout << j << ' ';
    cout << '\n';
    for (int i = 0; i < size; i++) {
        cout << i << "  ";
        for (int j = 0; j < size; j++) {
            char c = grid[i][j];
            if (!pokathKorabl && c == 'S') c = 'O';
            cout << c << ' ';
        }
        cout << '\n';
    }
}