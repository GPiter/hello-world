#include <game.h>

using namespace std;

int main() {
    Game TicTacToe;
    TicTacToe.instructions(); // Вывод правил игры

// ---- Запрос хода игрока ----

    char human = TicTacToe.humanPiece();         // Спрашивает, будет ли игрок ходить первым
    char computer = TicTacToe.opponent(human);   // Определение позиции компьютера
    char turn = X;

// --------------------------------------


    TicTacToe.displayBoard();   // Отрисовка поля

    while (TicTacToe.winner() == NO_ONE)
    {
        if (turn == human)
        {
            TicTacToe.move = TicTacToe.humanMove();
            TicTacToe.board[TicTacToe.move] = human;
        }
        else
        {
            TicTacToe.move = TicTacToe.computerMove(computer);
            TicTacToe.board[TicTacToe.move] = computer;
        }
        TicTacToe.displayBoard();
        turn = TicTacToe.opponent(turn);
    }

    TicTacToe.announceWinner(TicTacToe.winner(), computer, human);

    return 0;

}
