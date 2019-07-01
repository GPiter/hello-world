#include "game.h"

// ------------------- Функция вывода правил игры ---------------------------

void Game::instructions()
{
//    cout << "Добро пожаловать в игру крестики-нолики! \n";
    cout << "Welcome, human!\n";
    cout << "Make your move known by entering a number, 0 - 8.  The number\n";
    cout << "corresponds to the desired board position, as illustrated:\n\n";

    cout << "       0 | 1 | 2\n";
    cout << "       ---------\n";
    cout << "       3 | 4 | 5\n";
    cout << "       ---------\n";
    cout << "       6 | 7 | 8\n\n";

    cout << "Prepare yourself, human.  The battle is about to begin.\n\n";
}

// ---------------------------------------------------------------------------

int Game::chooseMode()
{
    cout << "Choose mode, that you wanna play:\n";
    cout << "1. With PC\n";
    cout << "2. With 2 Player\n";

    do
    {
        cout << "> ";
        cin >> mode;
    }

    while(mode > 2 || mode < 1);

    return mode;
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

char Game::winner()
{
    // all possible winning rows
    const int WINNING_ROWS[8][3] = { {0, 1, 2},
                                     {3, 4, 5},
                                     {6, 7, 8},
                                     {0, 3, 6},
                                     {1, 4, 7},
                                     {2, 5, 8},
                                     {0, 4, 8},
                                     {2, 4, 6} };
    const int TOTAL_ROWS = 8;

    // if any winning row has three values that are the same (and not EMPTY),
    // then we have a winner
    for(int row = 0; row < TOTAL_ROWS; ++row)
    {
        if ( (board[WINNING_ROWS[row][0]] != EMPTY) &&
             (board[WINNING_ROWS[row][0]] == board[WINNING_ROWS[row][1]]) &&
             (board[WINNING_ROWS[row][1]] == board[WINNING_ROWS[row][2]]) )
        {
            return board[WINNING_ROWS[row][0]];
        }
    }

    // since nobody has won, check for a tie (no empty squares left)
    if (count(board.begin(), board.end(), EMPTY) == 0)
        return TIE;

    // since nobody has won and it isn't a tie, the game ain't over
    return NO_ONE;
}

char Game::player2winner()
{
    // since nobody has won, check for a tie (no empty squares left)
    if (count(board.begin(), board.end(), EMPTY) == 0)
        return TIE;

    // since nobody has won and it isn't a tie, the game ain't over
    return NO_ONE;
}

inline bool Game::isLegal(int move)
{
    return (board[move] == EMPTY);
}

int Game::humanMove()
{
    int move = askNumber();
    while (!isLegal(move))
    {
        cout << "\nThat square is already occupied, foolish human.\n";
        move = askNumber();
    }
    cout << "Fine...\n";
    return move;
}

int Game::player2Move()
{
    cout << "Player 2 moved.\n";
    int move = askNumber();
    while (!isLegal(move))
    {
        cout << "\nThat square is already occupied, foolish human.\n";
        move = askNumber();
    }
    cout << "Fine...\n";
    return move;
}

int Game::computerMove(char computer)
{
    unsigned int move = 0;
    bool found = false;

    //if computer can win on next move, that’s the move to make
    while (!found && move < board.size())
    {
        if (isLegal(move))
        {
            //try move
            board[move] = computer;
            //test for winner
            found = winner() == computer;
            //undo move
            board[move] = EMPTY;
        }

        if (!found)
        {
            ++move;
        }
    }

    //otherwise, if opponent can win on next move, that's the move to make
    if (!found)
    {
        move = 0;
        char human = opponent(computer);

        while (!found && move < board.size())
        {
            if (isLegal(move))
            {
                //try move
                board[move] = human;
                //test for winner
                found = winner() == human;
                //undo move
                board[move] = EMPTY;
            }

            if (!found)
            {
                ++move;
            }
        }
    }

    //otherwise, moving to the best open square is the move to make
    if (!found)
    {
        move = 0;
        unsigned int i = 0;

        const int BEST_MOVES[] = {4, 0, 2, 6, 8, 1, 3, 5, 7};
        //pick best open square
        while (!found && i <  board.size())
        {
            move = BEST_MOVES[i];
            if (isLegal(move))
            {
                found = true;
            }

            ++i;
        }
    }

    cout << "I shall take square number " << move << endl;
    return move;
}

void Game::announceWinner(char winner, char computer, char human)
{
    if (winner == computer)
    {
        cout << winner << "'s won!\n";
        cout << "As I predicted, human, I am triumphant once more -- proof\n";
        cout << "that computers are superior to humans in all regards.\n";
    }

    else if (winner == human)
    {
        cout << winner << "'s won!\n";
        cout << "No, no!  It cannot be!  Somehow you tricked me, human.\n";
        cout << "But never again!  I, the computer, so swear it!\n";
    }

    else
    {
        cout << "It's a tie.\n";
        cout << "You were most lucky, human, and somehow managed to tie me.\n";
        cout << "Celebrate... for this is the best you will ever achieve.\n";
    }
}

void Game::showPlayersWinner(char winner, char player2, char human)
{
    if (winner == player2)
    {
        cout << winner << "'s won!\n";
        cout << "As I predicted, human, I am triumphant once more -- proof\n";
        cout << "that computers are superior to humans in all regards.\n";
    }

    else if (winner == human)
    {
        cout << winner << "'s won!\n";
        cout << "No, no!  It cannot be!  Somehow you tricked me, human.\n";
        cout << "But never again!  I, the computer, so swear it!\n";
    }

    else
    {
        cout << "It's a tie.\n";
        cout << "You were most lucky, human, and somehow managed to tie me.\n";
        cout << "Celebrate... for this is the best you will ever achieve.\n";
    }
}
