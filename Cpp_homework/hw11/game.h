#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Константы, описывающее поле
const int NUM_SQUARES = 9;
const char EMPTY = ' ';

class Game
{
public:
    vector<char> board;
    char response;
    char piece;
    int number;
    int move;

    Game() : board(NUM_SQUARES, EMPTY) { }  // Конструктор без аргументов
    Game(char p) : piece(p) { }

// Прототипы функций
    void instructions();
    char askYesNo();
    int askNumber();
    void displayBoard();
    char humanPiece();
    char opponent(char piece);

};

#endif // GAME_H
