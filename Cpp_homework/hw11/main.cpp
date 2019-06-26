#include <game.h>

using namespace std;

int main() {
    Game TicTacToe;
    TicTacToe.instructions(); // Вывод правил игры

    char choice = TicTacToe.humanPiece();
    TicTacToe.askNumber();    // Запрашивает ход игрока
    char side = TicTacToe.opponent(choice);
    cout << "You will go by " << choice << endl;
    cout << "Computer will go by " << side << endl;

    TicTacToe.displayBoard(); // Отрисовка пустого поля
    return 0;
}
