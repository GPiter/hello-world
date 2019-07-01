#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

// Константы, описывающее поле
const int NUM_SQUARES = 9;
const char EMPTY = ' ';
const char X = 'X';
const char O = 'O';
const char TIE = 'T';
const char NO_ONE = 'N';

using namespace std;

class Game
{
public:
    vector<char> board;
    int mode;
    char response;
    char piece;
    int number;
    int move;

    Game() : board(NUM_SQUARES, EMPTY) { }      // Конструктор без аргументов
    Game(char p, int m) : piece(p), move(m) { }     // Конструктор с аргументами

// Прототипы функций
    void instructions();
    int chooseMode();
    char askYesNo();
    int askNumber();
    void displayBoard();
    char humanPiece();
    char opponent(char piece);
    char winner();
    char player2winner();
    bool isLegal(int move);
    int humanMove();
    int computerMove(char computer);
    int player2Move();
    void announceWinner(char winner, char computer, char human);
    void showPlayersWinner(char winner, char player2, char human);
};

#endif // GAME_H
