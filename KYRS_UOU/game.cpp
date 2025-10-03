#include "game.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <string>
#include <fstream>
#include <chrono>
using namespace std;
using namespace chrono;

bool Game::polushil(Board& enemy, int x, int y) {
    char cell = enemy.get(x, y);
    if (cell == 'S') { enemy.set(x, y, 'X'); return true; }
    if (cell == 'O') { enemy.set(x, y, '*'); return false; }
    return false;
}

void Game::stataSoxran(double seconds, int shots, int hits, bool chelovekWin) {
    ofstream fout("stats.txt", ios::app);
    fout << "Час гри: " << seconds << " сек\n";
    fout << "Пострілів гравця: " << shots
        << " (влучних: " << hits << ")\n";
    fout << "Результат: " << (chelovekWin ? "Перемога" : "Поразка") << "\n";
    fout << "--------------------------\n";
}

void Game::glavnoeMenu() {
    system("chcp 1251>null");

    while (true) {
        cout << "\n====== МОРСЬКИЙ БІЙ ======\n";
        cout << "1. Грати з комп'ютером\n";
        cout << "2. Комп'ютер проти комп'ютера\n";
        cout << "3. Вихід\n";
        cout << "Ваш вибір: ";
        int ch;
        if (!(cin >> ch)) {
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }
        if (ch == 1) ivsrobot();
        else if (ch == 2) aivsAI();
        else if (ch == 3) break;
    }
}

void Game::ivsrobot() {
    system("chcp 1251>null");

    srand((unsigned)time(nullptr));
    Board player, ai;
    player.randomnoKorably();
    ai.randomnoKorably();
    int yronIgrok = 0, aiHits = 0;
    int shots = 0;
    const int maxHits = ai.vsegoKorably();
    auto start = steady_clock::now();

    while (yronIgrok < maxHits && aiHits < maxHits) {
        cout << "\n--- Поле гравця ---\n";      player.print(true);
        cout << "\n--- Поле комп'ютера ---\n";  ai.print(false);

        // Хід гравця
        string input;
        cout << "\nВаш постріл (x y) або Q для виходу: ";
        cin >> input;

        if (input == "Q" || input == "q") {
            cout << "Гру перервано.\n";
            auto sec = duration<double>(steady_clock::now() - start).count();
            stataSoxran(sec, shots, yronIgrok, false);
            return;
        }
        bool chislo = true;
        for (unsigned char c : input) {
            if (!(c >= '0' && c <= '9')) {
                chislo = false;
                break;
            }
        }
        if (!chislo) {
            cout << " Нето пальто\n";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        int x = stoi(input);
        int y;
        if (!(cin >> y)) {
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }
        if (x < 0 || x >= player.getSize() || y < 0 || y >= player.getSize()) {
            cout << "как так не те кординаты\n";
            continue;
        }

        shots++;
        if (polushil(ai, x, y)) { cout << "Влучання!\n"; yronIgrok++; }
        else cout << "Промах.\n";
        if (yronIgrok == maxHits) break;

        // Хід комп'ютера
        do { x = rand() % player.getSize(); y = rand() % player.getSize(); } while (player.vistrel(x, y));
        if (polushil(player, x, y)) aiHits++;
    }

    auto sec = duration<double>(steady_clock::now() - start).count();
    bool win = (yronIgrok == maxHits);
    cout << (win ? "\n*** Ви перемогли! ***\n" : "\n*** Переміг комп'ютер. ***\n");
    cout << "Час гри: " << sec << " сек\n";
    cout << "Ваші постріли: " << shots
        << " (влучних: " << yronIgrok << ")\n";
    stataSoxran(sec, shots, yronIgrok, win);

    cout << "Натисніть Enter для повернення в меню.";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void Game::aivsAI() {
    srand((unsigned)time(nullptr));
    Board ai1, ai2;
    ai1.randomnoKorably();
    ai2.randomnoKorably();
    int hits1 = 0, hits2 = 0;
    const int maxHits = ai1.vsegoKorably();
    auto start = steady_clock::now();

    while (hits1 < maxHits && hits2 < maxHits) {
        int x, y;
        do { x = rand() % ai2.getSize(); y = rand() % ai2.getSize(); } while (ai2.vistrel(x, y));
        if (polushil(ai2, x, y)) hits1++;
        if (hits1 == maxHits) break;

        do { x = rand() % ai1.getSize(); y = rand() % ai1.getSize(); } while (ai1.vistrel(x, y));
        if (polushil(ai1, x, y)) hits2++;
    }

    auto sec = duration<double>(steady_clock::now() - start).count();
    cout << "\n--- Кінцеві поля ---\n";
    cout << "\nКомп'ютер 1:\n"; ai1.print(true);
    cout << "\nКомп'ютер 2:\n"; ai2.print(true);

    bool win1 = (hits1 == maxHits);
    cout << (win1 ? "\n*** Переміг Комп'ютер 1 ***\n"
        : "\n*** Переміг Комп'ютер 2 ***\n");
    stataSoxran(sec, 0, 0, win1);

    cout << "Натисніть Enter для повернення в меню.";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}
