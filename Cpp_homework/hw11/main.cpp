#include <game.h>

using namespace std;

int main() {
    Game TicTacToe;
    TicTacToe.instructions(); // Вывод правил игры

// ---- Проверка запроса хода игрока ----

//    char human = TicTacToe.humanPiece(); // Спрашивает, будет ли игрок ходить первым
//    TicTacToe.askNumber();    // Запрашивает ход игрока
//    char computer = TicTacToe.opponent(human); // Вычисление, кем будет играть компьютер в зависимости от выбора игрока
//    cout << "You will go by " << human << endl;
//    cout << "Computer will go by " << computer << endl;

// --------------------------------------


// ---- Проверка победителя ----
    TicTacToe.board[0] = 'O';
    TicTacToe.board[1] = 'X';
    TicTacToe.board[2] = 'X';

    TicTacToe.displayBoard(); // Отрисовка поля

    char win = TicTacToe.winner();
    cout << win << endl;
// -----------------------------


// ---- Проверка корректности хода ----

    int mv = TicTacToe.humanMove();
    cout << mv << endl;


// ------------------------------------


// ---- Проверка хода компьютера ----

    int cmv = TicTacToe.computerMove();
    cout << cmv << endl;


// -----------------------------------

//    int Game::*pointer;
//    pointer = &Game::board;

    return 0;
}
