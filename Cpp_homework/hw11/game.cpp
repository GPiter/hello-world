#include "game.h"

void Game::instructions()
{
    cout << "Welcome to the ultimate man-machine showdown: Tic-Tac-Toe.\n";

    cout << "Make your move known by entering a number, 0 - 8.  The number\n";
    cout << "corresponds to the desired board position, as illustrated:\n\n";

    cout << "       0 | 1 | 2\n";
    cout << "       ---------\n";
    cout << "       3 | 4 | 5\n";
    cout << "       ---------\n";
    cout << "       6 | 7 | 8\n\n";

    cout << "Prepare yourself, human.  The battle is about to begin.\n\n";
}

char Game::askYesNo()
{
    do
    {
        cout << "Do you require the first move (y/n): ";
        cin >> response;
    } while (response != 'y' && response != 'n');

    return response;
}

void Game::displayBoard()
{
    cout << "\n\t" << board[0] << " | " << board[1] << " | " << board[2];
    cout << "\n\t" << "---------";
    cout << "\n\t" << board[3] << " | " << board[4] << " | " << board[5];
    cout << "\n\t" << "---------";
    cout << "\n\t" << board[6] << " | " << board[7] << " | " << board[8];
    cout << "\n\n";
}

int Game::askNumber()
{
    do
    {
        cout << "Where will you move?" << endl;
        cin >> number;
    } while (number > 9 || number < 0);

    return number;
}

char Game::humanPiece()
{
    char go_first = askYesNo();

    if(go_first == 'y')
    {
        cout << "\nThen take the first move.  You will need it.\n";
        return 'X';
    }

    if(go_first == 'n')
    {
        cout << "\nYour bravery will be your undoing... I will go first.\n";
        return 'O';
    }
}

char Game::opponent(char piece)
{
    if(piece == 'X')
        return 'O';
    else
        return 'X';
}
