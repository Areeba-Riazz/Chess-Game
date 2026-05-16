#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;

void check_int(int&);
void displayboard();
void r_displayboard();
void choose();
void checkmate();

void king();
void king_m(char[][8], int, int); //King_movement  
void kingpossibilities();       //shows the possibilities where king can move

void bishop();
void bishop_m(char[][8], int, int);  //Bishop_Movement
void bishoppossibilities();


void rook();
void rook_m(char[][8], int, int);  //Rock_movement
void rookpossibilities();

void queen();
void queen_m(char[][8], int, int); // Queen_movement
void queenpossibilities();

void knight();
void knight_m(char[][8], int, int);
void knightpossibilities();

//void pawns();
//void pawns_m();
void start();
void check(int& x, int& y);

int k_row,          // current row position
k_col,              // current col position
d_row,              // desired row position
d_col,              // desired col position
opt, player, turn = 0;
string player1, player2;
char temp;
char r_rook1 = 'R', l_rook1 = 'R', r_knight1 = 'N', l_knight1 = 'N', r_bishop1 = 'B', l_bishop1 = 'B', king1 = 'K', queen1 = 'Q';
char r_rook2= 'r', l_rook2 = 'r', r_knight2 = 'n', l_knight2 = 'n', r_bishop2 = 'b', l_bishop2 = 'b', king2 = 'k', queen2 = 'q';
char board[8][8] = { {' ',' ',' ',' ',' ',' ',' ',' '},
                     {' ',' ',' ',' ',' ',' ',' ',' '},
                     {' ',' ',' ',' ',' ',' ',' ',' '},
                     {' ',' ',' ',' ',' ',' ',' ',' '},
                     {' ',' ',' ',' ',' ',' ',' ',' '},
                     {' ',' ',' ',' ',' ',' ',' ',' '},
                     {' ',' ',' ',' ',' ',' ',' ',' '},
                     {' ',' ',' ',' ',' ',' ',' ',' '} };

//Function to choose Pieces
void choose() 
{
    cout << "\nChoose Your Piece (enter an integer) : \n 1. King  || 2. Queen || 3. Bishop || 4. Rock || 5. Knight: || 6. Exit :/ \n";
    check_int(player);
    if (player == 1)
        king();
    else if (player == 2)
        queen();
    else if (player == 3)
        bishop();
    else if (player == 4)
        rook();
    else if (player == 5)
        knight();
    else if (player == 6) 
    {
        cout << "Do you want to exit the game ?\n"
            << "   1. YES :( \n   2. NO :) " << endl;
        check_int(opt);
    check:
        if (opt == 1)
            exit(0);
        else if (opt == 2)
            choose();
        else
            cout << "Please select either 1 or 2 !!" << endl;
        check_int(opt);
        goto check;
    }
    else
    {
        cout << "Please, choose from given options." << endl;
        choose();
    }
}

int main() {
    start();
    return 0;
}

void start()
{
    //Placing initial positions for White player
    board[7][0] = l_rook1 ;
    board[7][1] = l_knight1;
    board[7][2] = l_bishop1;
    board[7][3] = queen1;
    board[7][4] = king1;
    board[7][5] = r_bishop1;
    board[7][6] = r_knight1;
    board[7][7] = r_rook1;
    //Placing initial positions for Black player
    board[0][0] = l_rook2;
    board[0][1] = l_knight2;
    board[0][2] = l_bishop2;
    board[0][3] = queen2;
    board[0][4] = king2;
    board[0][5] = r_bishop2;
    board[0][6] = r_knight2;
    board[0][7] = r_rook2;

  //Game starting
    cout << "---- YOU ARE PLAYING CHESS---- \n----- HAYE FUN----- \n";
    cout << "1st Player Name: ";
    cin >> player1;
    cout << "2nd Player Name: ";
    cin >> player2;

    cout << "{{{    GOOD LUCK " << player1 << " & " << player2<< "    }}}" << endl;

    while (true) 
    {
        cout << "\n----- " << player1 << "'s Turn -----" << endl;

        // player 1
        displayboard();
        choose(); // Calling the function chosen by player
        turn++;

        cout << "\n----- " << player2 << "'s Turn -----" << endl;
        // player 2
        choose(); // Calling the function chosen by player
        turn++;
    }
}

//shows all available blocks in chess
void displayboard()
{
    cout << "|-----------------------|" << endl << "|";
    cout << "     ";
    for (int a = 0; a < 8; a++)
        cout << a << " ";
    cout << "  |" <<endl;
    for (int i = 0; i < 8; i++)
    {
        cout << "|  " << i << "  ";
        for (int j = 0; j < 8; j++)
        {
            if (board[i][j] == ' ')
                board[i][j] = '.';
            cout << board[i][j] << " ";
        }
        cout << "  |" << endl;
    }
    cout << "|-----------------------|" << endl;
}
//for reset displayboard from x to empty
void r_displayboard()
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (board[i][j] == 'x')
                board[i][j] = '.';
            else if (board[i][j] == 'C')
                board[i][j] = temp;
        }
    }
}
//Function to check validity of rows and coloumns
void check(int& x, int& y)
{
    while ((x > 7 || y > 7) || (x < 0 || y < 0))
    {
        cout << "Invalid Position, Enter again" << endl;
        cout << "Select Position of King !! \n"
            << "Enter row: ";
        check_int(x);
        cout << "Enter Coloumn: ";
        check_int(y);
        check(x, y);
    }
}
//Function to check if intered num is int
void check_int(int &num)
{
    while (true) 
    {
        if (cin >> num) 
        {
            break;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter an integer.\n";
    }
}


//Functions when each piece is selected
void king()
{
    if (turn % 2 == 0)
    {
        int count = 0;
        //to check if there is king in chess board
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                if (board[i][j] != 'K')
                    count++;
            }
        }
        if (count == 64)
        {
            cout << player1 << " You don't have king !!" << endl;
            choose();
        }
        else
        {
            for (int a = 0; a < 8;a++) {
                for (int b = 0; b < 8;b++) {
                    if (board[a][b] == king1)
                    {
                        k_row = a;
                        k_col = b;
                    }
                }
            }
            king_m(board, k_row, k_col);
        }
    }
    else
    {
        int count = 0;
        //to check if there is queen is chess board
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                if (board[i][j] != 'Q')
                    count++;
            }
        }

        if (count == 64)
        {
            cout << player2 << " You don't have king !!" << endl;
            choose();
        }
        else
        {
            for (int a = 0; a < 8;a++) {
                for (int b = 0; b < 8;b++) {
                    if (board[a][b] == king2)
                    {
                        k_row = a;
                        k_col = b;
                    }
                }
            }
            king_m(board, k_row, k_col);
        }
    }
}
void queen()
{
    if (turn % 2 == 0)
    {
        int count = 0;
        //to check if there is queen is chess board
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                if (board[i][j] != 'Q')
                    count++;
            }
        }

        if (count == 64)
        {
            cout << player1 << " You don't have Queen !!" << endl;
            choose();
        }
        else
        {
            for (int a = 0; a < 8;a++) {
                for (int b = 0; b < 8;b++) {
                    if (board[a][b] == queen1)
                    {
                        k_row = a;
                        k_col = b;
                    }
                }
            }
            queen_m(board, k_row, k_col);
        }
    }
    else
    {
        int count = 0;
        //to check if there is queen is chess board
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                if (board[i][j] != 'q')
                    count++;
            }
        }
        if (count == 64)
        {
            cout << player2 << " You don't have Queen !!" << endl;
            choose();
        }
        else
        {
            for (int a = 0; a < 8;a++) {
                for (int b = 0; b < 8;b++) {
                    if (board[a][b] == queen2)
                    {
                        k_row = a;
                        k_col = b;
                    }
                }
            }
            queen_m(board, k_row, k_col);
        }
    }
}
void rook()
{
    if (turn % 2 == 0)
    {
    r_opt:
        cout << player1 << " Choose your rook: \n 1. Left Rook || 2. Right Rook \n";
        check_int(opt);
        if (opt == 1 || opt == 2)
        {
            bool left_rook_found = false;
            bool right_rook_found = false;

            // check for left and right rook for player 1
            for (int i = 0; i < 8; i++)
            {
                for (int j = 0; j < 8; j++)
                {
                    if (board[i][j] == 'R')
                    {
                        if (j < 4) // left rook
                        {
                            left_rook_found = true;
                        }
                        else // right rook
                        {
                            right_rook_found = true;
                        }
                    }
                }
            }

            if (!left_rook_found && !right_rook_found)
            {
                cout << player1 << " You don't have a rook!" << endl;
                choose();
            }
            else if (!right_rook_found && opt == 2)
            {
                cout << player1 << " You don't have a right rook!" << endl;
                choose();
            }
            else if (!left_rook_found && opt == 1)
            {
                cout << player1 << " You don't have a left rook!" << endl;
                choose();
            }
            else if (left_rook_found && opt == 1)
            {
                for (int a = 0; a < 8;a++) {
                    for (int b = 0; b < 8;b++) {
                        if ((board[a][b] == 'R') && (abs(a - b) < 4))
                        {
                            k_row = a;
                            k_col = b;
                            break;
                        }
                    }
                }
            }
            else if (right_rook_found && opt == 2)
            {
                for (int a = 0; a < 8;a++)
                {
                    for (int b = 0; b < 8;b++)
                    {
                        if ((board[a][b] == 'R') && (abs(a - b) >= 4))
                        {
                            k_row = a;
                            k_col = b;
                            break;
                        }
                    }
                }
            }
        }
        else
        {
            cout << player1 << " Please choose from given options !!" << endl;
            goto r_opt;
        }
        rook_m(board, k_row, k_col);
    }
    else
    {
        r2_opt:
        cout << player2 << " Choose your rook: \n 1. Left Rook || 2. Right Rook \n";
        check_int(opt);
        if (opt == 1 || opt == 2)
        {
            bool left_rook_found = false;
            bool right_rook_found = false;

            // check for left and right rook for player 1
            for (int i = 0; i < 8; i++)
            {
                for (int j = 0; j < 8; j++)
                {
                    if (board[i][j] == 'r')
                    {
                        if (j < 4) // left rook
                        {
                            left_rook_found = true;
                        }
                        else // right rook
                        {
                            right_rook_found = true;
                        }
                    }
                }
            }

            if (!left_rook_found && !right_rook_found)
            {
                cout << player2 << " You don't have a rook!" << endl;
                choose();
            }
            else if (!right_rook_found && opt == 2)
            {
                cout << player2 << " You don't have a right rook!" << endl;
                choose();
            }
            else if (!left_rook_found && opt == 1)
            {
                cout << player2 << " You don't have a left rook!" << endl;
                choose();
            }
            else if (left_rook_found && opt == 1)
            {
                for (int a = 0; a < 8;a++) {
                    for (int b = 0; b < 8;b++) {
                        if ((board[a][b] == 'r') && (abs(a - b) < 4))
                        {
                            k_row = a;
                            k_col = b;
                            break;
                        }
                    }
                }
            }
            else if (right_rook_found && opt == 2)
            {
                for (int a = 0; a < 8;a++)
                {
                    for (int b = 0; b < 8;b++)
                    {
                        if ((board[a][b] == 'r') && (abs(a - b) >= 4))
                        {
                            k_row = a;
                            k_col = b;
                            break;
                        }
                    }
                }
            }
        }
        else
        {
            cout << player2 << " Please choose from given options !!" << endl;
            goto r2_opt;
        }
        rook_m(board, k_row, k_col);
    }
}
void bishop()
{
    if (turn % 2 == 0)
    {
    b_opt:
        cout << player1 << " Choose your rook: \n 1. Left Bishop || 2. Right Bishop \n";
        check_int(opt);
        if (opt == 1 || opt == 2)
        {
            bool left_rook_found = false;
            bool right_rook_found = false;

            // check for left and right rook for player 1
            for (int i = 0; i < 8; i++)
            {
                for (int j = 0; j < 8; j++)
                {
                    if (board[i][j] == 'B')
                    {
                        if (j < 4) // left rook
                        {
                            left_rook_found = true;
                        }
                        else // right rook
                        {
                            right_rook_found = true;
                        }
                    }
                }
            }

            if (!left_rook_found && !right_rook_found)
            {
                cout << player1 << " You don't have a rook!" << endl;
                choose();
            }
            else if (!right_rook_found && opt == 2)
            {
                cout << player1 << " You don't have a right rook!" << endl;
                choose();
            }
            else if (!left_rook_found && opt == 1)
            {
                cout << player1 << " You don't have a left rook!" << endl;
                choose();
            }
            else if (left_rook_found && opt == 1)
            {
                for (int a = 0; a < 8;a++) {
                    for (int b = 0; b < 8;b++) {
                        if ((board[a][b] == 'B') && (abs(a - b) < 4))
                        {
                            k_row = a;
                            k_col = b;
                            break;
                        }
                    }
                }
            }
            else if (right_rook_found && opt == 2)
            {
                for (int a = 0; a < 8;a++)
                {
                    for (int b = 0; b < 8;b++)
                    {
                        if ((board[a][b] == 'B') && (abs(a - b) >= 4))
                        {
                            k_row = a;
                            k_col = b;
                            break;
                        }
                    }
                }
            }
        }
        else
        {
            cout << player1 << " Please choose from given options !!" << endl;
            goto b_opt;
        }
        bishop_m(board, k_row, k_col);

    }
    else
    {
    b2_opt:
        cout << player2 << " Choose your rook: \n 1. Left Rook || 2. Right Rook \n";
        check_int(opt);
        if (opt == 1 || opt == 2)
        {
            bool left_rook_found = false;
            bool right_rook_found = false;

            // check for left and right rook for player 1
            for (int i = 0; i < 8; i++)
            {
                for (int j = 0; j < 8; j++)
                {
                    if (board[i][j] == 'b')
                    {
                        if (j < 4) // left rook
                        {
                            left_rook_found = true;
                        }
                        else // right rook
                        {
                            right_rook_found = true;
                        }
                    }
                }
            }

            if (!left_rook_found && !right_rook_found)
            {
                cout << player2 << " You don't have a rook!" << endl;
                choose();
            }
            else if (!right_rook_found && opt == 2)
            {
                cout << player2 << " You don't have a right rook!" << endl;
                choose();
            }
            else if (!left_rook_found && opt == 1)
            {
                cout << player2 << " You don't have a left rook!" << endl;
                choose();
            }
            else if (left_rook_found && opt == 1)
            {
                for (int a = 0; a < 8;a++) {
                    for (int b = 0; b < 8;b++) {
                        if ((board[a][b] == 'b') && (abs(a - b) < 4))
                        {
                            k_row = a;
                            k_col = b;
                            break;
                        }
                    }
                }
            }
            else if (right_rook_found && opt == 2)
            {
                for (int a = 0; a < 8;a++)
                {
                    for (int b = 0; b < 8;b++)
                    {
                        if ((board[a][b] == 'b') && (abs(a - b) >= 4))
                        {
                            k_row = a;
                            k_col = b;
                            break;
                        }
                    }
                }
            }
        }
        else
        {
            cout << player1 << " Please choose from given options !!" << endl;
            goto b2_opt;
        }
        bishop_m(board, k_row, k_col);
    }
}
void knight()
{
    if (turn % 2 == 0)
    {
    n_opt:
        cout << player1 << " Choose your rook: \n 1. Left Knight || 2. Right Knight \n";
        check_int(opt);
        if (opt == 1 || opt == 2)
        {
            bool left_rook_found = false;
            bool right_rook_found = false;

            // check for left and right rook for player 1
            for (int i = 0; i < 8; i++)
            {
                for (int j = 0; j < 8; j++)
                {
                    if (board[i][j] == 'B')
                    {
                        if (j < 4) // left rook
                        {
                            left_rook_found = true;
                        }
                        else // right rook
                        {
                            right_rook_found = true;
                        }
                    }
                }
            }

            if (!left_rook_found && !right_rook_found)
            {
                cout << player1 << " You don't have a rook!" << endl;
                choose();
            }
            else if (!right_rook_found && opt == 2)
            {
                cout << player1 << " You don't have a right rook!" << endl;
                choose();
            }
            else if (!left_rook_found && opt == 1)
            {
                cout << player1 << " You don't have a left rook!" << endl;
                choose();
            }
            else if (left_rook_found && opt == 1)
            {
                for (int a = 0; a < 8;a++) {
                    for (int b = 0; b < 8;b++) {
                        if ((board[a][b] == 'B') && (abs(a - b) < 4))
                        {
                            k_row = a;
                            k_col = b;
                            break;
                        }
                    }
                }
            }
            else if (right_rook_found && opt == 2)
            {
                for (int a = 0; a < 8;a++)
                {
                    for (int b = 0; b < 8;b++)
                    {
                        if ((board[a][b] == 'B') && (abs(a - b) >= 4))
                        {
                            k_row = a;
                            k_col = b;
                            break;
                        }
                    }
                }
            }
        }
        else
        {
            cout << player1 << " Please choose from given options !!" << endl;
            goto n_opt;
        }
        knight_m(board, k_row, k_col);
    }
    else
    {
    n2_opt:
        cout << player2 << " Choose your rook: \n 1. Left Rook || 2. Right Rook \n";
        check_int(opt);
        if (opt == 1 || opt == 2)
        {
            bool left_rook_found = false;
            bool right_rook_found = false;

            // check for left and right rook for player 1
            for (int i = 0; i < 8; i++)
            {
                for (int j = 0; j < 8; j++)
                {
                    if (board[i][j] == 'n')
                    {
                        if (j < 4) // left rook
                        {
                            left_rook_found = true;
                        }
                        else // right rook
                        {
                            right_rook_found = true;
                        }
                    }
                }
            }

            if (!left_rook_found && !right_rook_found)
            {
                cout << player1 << " You don't have a rook!" << endl;
                choose();
            }
            else if (!right_rook_found && opt == 2)
            {
                cout << player1 << " You don't have a right rook!" << endl;
                choose();
            }
            else if (!left_rook_found && opt == 1)
            {
                cout << player1 << " You don't have a left rook!" << endl;
                choose();
            }
            else if (left_rook_found && opt == 1)
            {
                for (int a = 0; a < 8;a++) {
                    for (int b = 0; b < 8;b++) {
                        if ((board[a][b] == 'n') && (abs(a - b) < 4))
                        {
                            k_row = a;
                            k_col = b;
                            break;
                        }
                    }
                }
            }
            else if (right_rook_found && opt == 2)
            {
                for (int a = 0; a < 8;a++)
                {
                    for (int b = 0; b < 8;b++)
                    {
                        if ((board[a][b] == 'n') && (abs(a - b) >= 4))
                        {
                            k_row = a;
                            k_col = b;
                            break;
                        }
                    }
                }
            }
        }
        else
        {
            cout << player1 << " Please choose from given options !!" << endl;
            goto n2_opt;
        }
        knight_m(board, k_row, k_col);
    }
}

//Function for each piece's movement
void king_m(char board[][8], int k_row, int k_col)
{
    if (turn % 2 == 0)
    {   
        kingpossibilities();        //king possible outcomes = x
        displayboard();             //display x
        r_displayboard();           //reset x = .

        cout << endl<< player1 << " Enter Destination where you want to move king.\n"
            << "Enter row: ";
        check_int(d_row);
        cout << "Enter Coloumn: ";
        check_int(d_col);
        check(d_row, d_col);

        //king can move in square
        //check if the destination is empty and is one square away vertically, horizontally, or diagonally
        if (board[d_row][d_col] == '.' || board[d_row][d_col] == 'b' || board[d_row][d_col] == 'n'
            || board[d_row][d_col] == 'r' || board[d_row][d_col] == 'p' || board[d_row][d_col] == 'q' || board[d_row][d_col] == 'C')
        {
            if ((abs(k_col - d_col) <= 1) && (abs(k_row - d_row) <= 1))
            {
                board[d_row][d_col] = 'K';
                    board[k_row][k_col] = '.';
                    displayboard();
            }
            //if user selects invalid position
            else
            {
                cout << "Invalid move. " << player1 << " Please choose another destination." << endl;
                king_m(board, k_row, k_col);
            }
        }
    }
    else
    {
        kingpossibilities();        //king possible outcomes = x
        displayboard();             //display x
        r_displayboard();           //reset x = .

        cout << endl<< player2 << " Enter Destination where you want to move king.\n"
            << "Enter row: ";
        check_int(d_row);
        cout << "Enter Coloumn: ";
        check_int(d_col);
        check(d_row, d_col);

        //king can move in square
        //check if the destination is empty and is one square away vertically, horizontally, or diagonally
        if (board[d_row][d_col] == '.' || board[k_row][k_col] == 'B' || board[k_row][k_col] == 'N'
            || board[k_row][k_col] == 'R' || board[k_row][k_col] == 'P' || board[k_row][k_col] == 'Q')
        {
            if ((abs(k_col - d_col) <= 1) && (abs(k_row - d_row) <= 1))
            {
                board[d_row][d_col] = 'k';
                board[k_row][k_col] = '.';
                displayboard();
            }
            //if user selects invalid position
            else
            {
                cout << "Invalid move. " << player2 << " Please choose another destination." << endl;
                king_m(board, k_row, k_col);
            }
        }
    }
}
void queen_m(char board[][8], int k_row, int k_col)
{
    if (turn % 2 == 0)
    {
        
        queenpossibilities();   //queen possible outcomes = x
        displayboard();         //display x
        r_displayboard();       //reset x = .
        
        cout << endl << player1 << " Enter Destination where you want to move Queen.\n"
            << "Enter row: ";
        check_int(d_row);
        cout << "Enter Coloumn: ";
        check_int(d_col);
        check(d_row, d_col);

        //queen can move in straight left,right,up,down and diagonally
        //first condition to check if space is empty, 2nd for diagonal movement, third for left right up and down

        if ( board[d_row][d_col] == '.' || board[d_row][d_col] == 'r' || board[d_row][d_col] == 'n' 
            || board[d_row][d_col] == 'q' || board[d_row][d_col] == 'b')
        {
            if (((abs(k_col - d_col) < 8) && (abs(k_row - d_row) < 8)) || ((abs(k_col - d_col) < 8) || (abs(k_row - d_row) < 8))) 
            {
                board[d_row][d_col] = 'Q';
                board[k_row][k_col] = '.';
                displayboard();
            }
            else if ((((abs(k_col - d_col) < 8) && (abs(k_row - d_row) < 8)) || ((abs(k_col - d_col) < 8) || (abs(k_row - d_row) < 8))) &&
                (board[d_row][d_col] == 'k'))
                checkmate();
        }
        //if user selects invalid position
        else
        {
            cout << "Invalid move. " << player1 << " Please choose another destination." << endl;
            queen_m(board, k_row, k_col);
        }
    }
    else
    {
        queenpossibilities();   //queen possible outcomes = x
        displayboard();         //display x
        r_displayboard();       //reset x = .

        cout << endl<< player2 << "Enter Destination where you want to move Queen.\n"
            << "Enter row: ";
        check_int(d_row);
        cout << "Enter Coloumn: ";
        check_int(d_col);
        check(d_row, d_col);

        //queen can move in straight left,right,up,down and diagonally
        //first condition to check if space is empty, 2nd for diagonal movement, third for left right up and down
        if (board[d_row][d_col] == '.' || board[d_row][d_col] == 'R' || board[d_row][d_col] == 'N'
            || board[d_row][d_col] == 'Q' || board[d_row][d_col] == 'B' )
        {
            if (((abs(k_col - d_col) < 8) && (abs(k_row - d_row) < 8)) || ((abs(k_col - d_col) < 8) || (abs(k_row - d_row) < 8))) 
            {
                board[d_row][d_col] = 'q';
                board[k_row][k_col] = '.';
                displayboard();
            }
            else if ((((abs(k_col - d_col) < 8) && (abs(k_row - d_row) < 8)) || ((abs(k_col - d_col) < 8) || (abs(k_row - d_row) < 8))) &&
                (board[d_row][d_col] == 'K'))
                checkmate();
        }
        //if user selects invalid position
        else
        {
            cout << "Invalid move. " << player2 << " Please choose another destination." << endl;
            queen_m(board, k_row, k_col);
        }
    }
}
void rook_m(char board[][8], int k_row, int k_col)
{
    if (turn % 2 == 0)
    {
        rookpossibilities();        //rook possible outcomes = x
        displayboard();             //display x
        r_displayboard();           //reset x = .

        cout << endl<< player1 << " Enter Destination where you want to move Rook.\n"
            << "Enter row: ";
        check_int(d_row);
        cout << "Enter Coloumn: ";
        check_int(d_col);
        check(d_row, d_col);

        //Rook can move in straight left,right,up, and down
        //first condition to check if space is empty, 2nd for up, down and 3rd for left and right
        if (board[d_row][d_col] == '.' || board[d_row][d_col] == 'r' || board[d_row][d_col] == 'n' 
            || board[d_row][d_col] == 'q' || board[d_row][d_col] == 'b')
        {
            if (((abs(k_col - d_col) == 0) && (abs(k_row - d_row) < 8)) || ((abs(k_col - d_col) < 8) && (abs(k_row - d_row) == 0)))
            {
                board[d_row][d_col] = 'R';
                board[k_row][k_col] = '.';
                displayboard();
            }
            else if (((abs(k_col - d_col) == 0) && (abs(k_row - d_row) < 8)) || ((abs(k_col - d_col) < 8) && (abs(k_row - d_row) == 0)) &&
                board[d_row][d_col] == 'k')
                checkmate();
            //if user selects invalid position
            else
            {
                cout << "Invalid move. " << player1 << " Please choose another destination." << endl;
                rook_m(board, k_row, k_col);
            }
        }
    }
    else
    {
        rookpossibilities();        //rook possible outcomes =x
        displayboard();             //display x
        r_displayboard();           //reset x = .

        cout << endl << player2 << " Enter Destination where you want to move Rook.\n"
            << "Enter row: ";
        check_int(d_row);
        cout << "Enter Coloumn: ";
        check_int(d_col);
        check(d_row, d_col);

        //Rook can move in straight left,right,up, and down
        //first condition to check if space is empty, 2nd for up, down and 3rd for left and right
        if (board[d_row][d_col] == '.' || board[d_row][d_col] == 'B' || board[d_row][d_col] == 'N'
            || board[d_row][d_col] == 'R' || board[d_row][d_col] == 'P' || board[d_row][d_col] == 'Q')
        {
            if (((abs(k_col - d_col) == 0) && (abs(k_row - d_row) < 8)) || ((abs(k_col - d_col) < 8) && (abs(k_row - d_row) == 0)))
            {
                board[d_row][d_col] = 'r';
                board[k_row][k_col] = '.';
                displayboard();
            }
            else if ((((abs(k_col - d_col) == 0) && (abs(k_row - d_row) < 8)) || ((abs(k_col - d_col) < 8) && (abs(k_row - d_row) == 0))) &&
                (board[d_row][d_col] == 'K'))
                checkmate();
            //if user selects invalid position
            else
            {
                cout << "Invalid move. " << player2 << " Please choose another destination." << endl;
                rook_m(board, k_row, k_col);
            }
        }
    }
}
void bishop_m(char board[][8], int k_row, int k_col)
{
    if (turn % 2 == 0)
    {
        bishoppossibilities();       //bishop possible outcomes =x
        displayboard();             //display x
        r_displayboard();           //reset x = .

        cout << endl << player1 << " Enter Destination where you want to move Bishop.\n"
            << "Enter row: ";
        check_int(d_row);
        cout << "Enter Coloumn: ";
        check_int(d_col);
        check(d_row, d_col);

        //Bishop can move only diagonally
        //first condition to check if space is empty, 2nd for diagonal movement
        if (board[d_row][d_col] == '.' || board[d_row][d_col] == 'r' || board[d_row][d_col] == 'n'
            || board[d_row][d_col] == 'q' || board[d_row][d_col] == 'b')
        {
            if (((abs(k_col - d_col)) == (abs(k_row - d_row))) || ((abs(k_col - d_col)) == (abs(k_row - d_row))))
            {
                board[d_row][d_col] = 'B';
                board[k_row][k_col] = '.';
                displayboard();
            }
            else if ((((abs(k_col - d_col)) == (abs(k_row - d_row))) || ((abs(k_col - d_col)) == (abs(k_row - d_row)))) &&
                (board[d_row][d_col] == 'k'))
                checkmate();
            
            //if user selects invalid position
            else
            {
                cout << "Invalid move. " << player1 << " Please choose another destination." << endl;
                bishop_m(board, k_row, k_col);
            }
        }
    }
    else
    {
        bishoppossibilities();       //rook possible outcomes =x
        displayboard();             //display x
        r_displayboard();           //reset x = .

        cout << endl << player2 << " Enter Destination where you want to move Bishop.\n"
            << "Enter row: ";
        check_int(d_row);
        cout << "Enter Coloumn: ";
        check_int(d_col);
        check(d_row, d_col);

        //Bishop can move only diagonally
        //first condition to check if space is empty, 2nd for diagonal movement
        if (board[d_row][d_col] == '.' || board[d_row][d_col] == 'B' || board[d_row][d_col] == 'N'
            || board[d_row][d_col] == 'R' || board[d_row][d_col] == 'Q')
        {
            if (((abs(k_col - d_col)) == (abs(k_row - d_row))) || ((abs(k_col - d_col)) == (abs(k_row - d_row))))
            {
                board[d_row][d_col] = 'b';
                board[k_row][k_col] = '.';
                displayboard();
            }
            else if (((abs(k_col - d_col)) == (abs(k_row - d_row))) || ((abs(k_col - d_col)) == (abs(k_row - d_row))) && 
                board[d_row][d_col]=='K')
                checkmate();
            
            //if user selects invalid position
            else
            {
                cout << "Invalid move. " << player2 << " Please choose another destination." << endl;
                bishop_m(board, k_row, k_col);
            }
        }
    }
    
}
void knight_m(char[][8], int k_row, int k_col)
{
    if (turn % 2 == 0)
    {
        knightpossibilities();       //knight possible outcomes = x
        displayboard();             //display x
        r_displayboard();           //reset x = .

        cout << endl << player1 << " Enter Destination where you want to move knight.\n"
            << "Enter row: ";
        check_int(d_row);
        cout << "Enter Coloumn: ";
        check_int(d_col);
        check(d_row, d_col);

        //knight can move in L position
        //first condition to check if space is empty, 2nd for L movement
        if (board[d_row][d_col] == '.' || board[d_row][d_col] == 'r' || board[d_row][d_col] == 'n' 
            || board[d_row][d_col] == 'q' || board[d_row][d_col] == 'b')
        {
            if (((abs(d_col - k_col) == 2) && (abs(d_row - k_row) == 1)) || ((abs(d_col - k_col) == 1) && (abs(d_row - k_row) == 2)))
            {
                board[d_row][d_col] = 'N';
                board[k_row][k_col] = '.';
                displayboard();
            }
            else if ((((abs(d_col - k_col) == 2) && (abs(d_row - k_row) == 1)) || ((abs(d_col - k_col) == 1) && (abs(d_row - k_row) == 2))) &&
                (board[d_row][d_col] == 'k'))
                checkmate();
            //if user selects invalid position
            else
            {
                cout << "Invalid move. " << player1 << " Please choose another destination." << endl;
                knight_m(board, k_row, k_col);
            }
        }
    }
    else
    {
        knightpossibilities();       //knight possible outcomes = x
        displayboard();             //display x
        r_displayboard();           //reset x = .

        cout << player2 << " Enter Destination where you want to move knight.\n"
            << "Enter row: ";
        check_int(d_row);
        cout << "Enter Coloumn: ";
        check_int(d_col);
        check(d_row, d_col);

        //knight can move in L position
        //first condition to check if space is empty, 2nd for L movement
        if (board[d_row][d_col] == '.' || board[d_row][d_col] == 'B' || board[d_row][d_col] == 'N'
            || board[d_row][d_col] == 'R' ||  board[d_row][d_col] == 'Q')
        {
            if (((abs(d_col - k_col) == 2) && (abs(d_row - k_row) == 1)) || ((abs(d_col - k_col) == 1) && (abs(d_row - k_row) == 2)))
            {
                board[d_row][d_col] = 'n';
                board[k_row][k_col] = '.';
                displayboard();
            }
            else if ((((abs(d_col - k_col) == 2) && (abs(d_row - k_row) == 1)) || ((abs(d_col - k_col) == 1) && (abs(d_row - k_row) == 2))) &&
                (board[d_row][d_col] == 'K'))
                checkmate();
            //if user selects invalid position
            else
            {
                cout << "Invalid move. " << player2 << " Please choose another destination." << endl;
                knight_m(board, k_row, k_col);
            }
        }
    }
}

//Functions to mark possibilites of each piece
void kingpossibilities()
{
    if (turn % 2 == 0)
    {
        // all possible moves of a king on a chess board
        for (int row = -1; row <= 1; row++) {
            for (int col = -1; col <= 1; col++) {
                d_row = k_row + row;
                d_col = k_col + col;
                if ((row != 0 || col != 0) && d_row >= 0 && d_row < 8 && d_col >= 0 && d_col < 8)
                {
                    if (board[d_row][d_col] == '.')
                        board[d_row][d_col] = 'x';
                    else if (board[d_row][d_col] == 'b' || board[d_row][d_col] == 'n'
                        || board[d_row][d_col] == 'r' || board[d_row][d_col] == 'p' || board[d_row][d_col] == 'q')
                        break;
                }
            }
        }
    }
    else
    {
        for (int row = -1; row <= 1; row++) {
            for (int col = -1; col <= 1; col++) {
                d_row = k_row + row;
                d_col = k_col + col;
                if ((row != 0 || col != 0) && d_row >= 0 && d_row < 8 && d_col >= 0 && d_col < 8)
                {
                    if (board[d_row][d_col] == '.')
                        board[d_row][d_col] = 'x';
                    else if (board[d_row][d_col] == 'B' || board[d_row][d_col] == 'N'
                        || board[d_row][d_col] == 'R' || board[d_row][d_col] == 'P' || board[d_row][d_col] == 'Q')
                        break;
                }
            }
        }
    }
}
void queenpossibilities()
{
    if (turn % 2 == 0)
    {
        // all possible moves of a queen on a chess board
        // Check all diagonal directions
        for (int i = -1; i <= 1; i += 2) {
            for (int j = -1; j <= 1; j += 2) {
                int k = 1;
                while (true)
                {
                    int d_row = k_row + k * i;
                    int d_col = k_col + k * j;
                    if (d_row < 0 || d_row > 7 || d_col < 0 || d_col > 7)
                        break;
                    else if (board[d_row][d_col] == '.')
                        board[d_row][d_col] = 'x';
                    else if (board[d_row][d_col] == 'b' || board[d_row][d_col] == 'n'
                        || board[d_row][d_col] == 'r' || board[d_row][d_col] == 'p' || board[d_row][d_col] == 'q')
                        break;
                    k++;
                }
            }
        }
        // Check all horizontal and vertical directions
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                if (i == 0 && j == 0)
                    continue;
                int k = 1;
                while (true)
                {
                    int d_row = k_row + k * i;
                    int d_col = k_col + k * j;
                    if (d_row < 0 || d_row > 7 || d_col < 0 || d_col > 7)
                        break;
                    else if (board[d_row][d_col] == '.')
                        board[d_row][d_col] = 'x';
                    else if (board[d_row][d_col] == 'b' || board[d_row][d_col] == 'n'
                        || board[d_row][d_col] == 'r' || board[d_row][d_col] == 'p' || board[d_row][d_col] == 'q')
                        break;
                        k++;
                }
            }
        }
    }
    else
    {
        for (int i = -1; i <= 1; i += 2) {
            for (int j = -1; j <= 1; j += 2) {
                int k = 1;
                while (true)
                {
                    int d_row = k_row + k * i;
                    int d_col = k_col + k * j;
                    if (d_row < 0 || d_row > 7 || d_col < 0 || d_col > 7)
                        break;
                    else if (board[d_row][d_col] == '.')
                        board[d_row][d_col] = 'x';
                    else if (board[d_row][d_col] == 'B' || board[d_row][d_col] == 'N'
                        || board[d_row][d_col] == 'R' || board[d_row][d_col] == 'P' || board[d_row][d_col] == 'Q')
                        break;
                    k++;
                }
            }
        }
        // Check all horizontal and vertical directions
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                if (i == 0 && j == 0)
                    continue;
                int k = 1;
                while (true)
                {
                    int d_row = k_row + k * i;
                    int d_col = k_col + k * j;
                    if (d_row < 0 || d_row > 7 || d_col < 0 || d_col > 7)
                        break;
                    else if (board[d_row][d_col] == '.')
                        board[d_row][d_col] = 'x';
                    else if (board[d_row][d_col] == 'B' || board[d_row][d_col] == 'N'
                        || board[d_row][d_col] == 'R' || board[d_row][d_col] == 'P' || board[d_row][d_col] == 'Q')
                        break;
                    k++;
                }
            }
        }
    }
}
void rookpossibilities()
{
    if (turn % 2 == 0)
    {
        // all possible moves of a rook on a chess board
        // Checking squares in all four directions
        for (int i = 1; i <= 7; i++)
        {
            // Checking squares to the right
            if (k_col + i < 8)
            {
                if (board[k_row][k_col + i] == '.')
                {
                    board[k_row][k_col + i] = 'x';
                }
                else if (board[k_row][k_col + i] == 'b' || board[k_row][k_col + i] == 'n'
                    || board[k_row][k_col + i] == 'r' || board[k_row][k_col + i] == 'p' || board[k_row][k_col + i] == 'q')
                    break;
            }
            // Checking squares to the left
            if (k_col - i >= 0)
            {
                if (board[k_row][k_col - i] == '.')
                {
                    board[k_row][k_col - i] = 'x';
                }
                else if (board[k_row][k_col - i] == 'b' || board[k_row][k_col - i] == 'n'
                    || board[k_row][k_col - i] == 'r' || board[k_row][k_col - i] == 'p' || board[k_row][k_col - i] == 'q')
                    break;

            }
            // Checking squares above
            if (k_row + i < 8)
            {
                if (board[k_row + i][k_col] == '.')
                {
                    board[k_row + i][k_col] = 'x';
                }
                else if (board[k_row + i][k_col] == 'b' || board[k_row + i][k_col] == 'n'
                    || board[k_row + i][k_col] == 'r' || board[k_row + i][k_col] == 'p' || board[k_row + i][k_col] == 'q')
                    break;
            }
            // Checking squares below
            if (k_row - i >= 0)
            {
                if (board[k_row - i][k_col] == '.')
                {
                    board[k_row - i][k_col] = 'x';
                }
                else if (board[k_row - i][k_col] == 'b' || board[k_row - i][k_col] == 'n'
                    || board[k_row - i][k_col] == 'r' || board[k_row - i][k_col] == 'p' || board[k_row - i][k_col] == 'q')
                    break;
            }
      
        }
    }
    else
    {
        for (int i = 1; i <= 7; i++)
        {
            // Checking squares to the right
            if (k_col + i < 8)
            {
                if (board[k_row][k_col + i] == '.')
                {
                    board[k_row][k_col + i] = 'x';
                }
                else if (board[k_row][k_col + i] == 'B' || board[k_row][k_col + i] == 'N'
                    || board[k_row][k_col + i] == 'R' || board[k_row][k_col + i] == 'P' || board[k_row][k_col + i] == 'Q')
                    break;

            }
            // Checking squares to the left
            if (k_col - i >= 0)
            {
                if (board[k_row][k_col - i] == '.')
                {
                    board[k_row][k_col - i] = 'x';
                }
                else if (board[k_row][k_col - i] == 'B' || board[k_row][k_col - i] == 'N'
                    || board[k_row][k_col - i] == 'R' || board[k_row][k_col - i] == 'P' || board[k_row][k_col - i] == 'Q')
                    break;
            }
            // Checking squares above
            if (k_row + i < 8)
            {
                if (board[k_row + i][k_col] == '.')
                {
                    board[k_row + i][k_col] = 'x';
                }
                else if (board[k_row + i][k_col] == 'B' || board[k_row + i][k_col] == 'N'
                    || board[k_row + i][k_col] == 'R' || board[k_row + i][k_col] == 'P' || board[k_row + i][k_col] == 'Q')
                    break;
            }
            // Checking squares below
            if (k_row - i >= 0)
            {
                if (board[k_row - i][k_col] == '.')
                {
                    board[k_row - i][k_col] = 'x';
                }
                else if (board[k_row - i][k_col] == 'B' || board[k_row - i][k_col] == 'N'
                    || board[k_row - i][k_col] == 'R' || board[k_row - i][k_col] == 'P' || board[k_row - i][k_col] == 'Q')
                    break;
            }
        }
    }
}
void bishoppossibilities()
{
    if (turn % 2 == 0)
    {
        // all possible moves of a bishop on a chess board
        // Checking squares in all four diagonal directions
        for (int i = 1; i <= 7; i++)
        {
            // Checking squares to the top-right
            if (k_row + i < 8 && k_col + i < 8)
            {
                if (board[k_row + i][k_col + i] == '.')
                    board[k_row + i][k_col + i] = 'x';
                else if (board[k_row + i][k_col + i] == 'b' || board[k_row + i][k_col + i] == 'n' 
                    || board[k_row + i][k_col + i] == 'r' || board[k_row + i][k_col + i] == 'p' || board[k_row + i][k_col + i] == 'q')
                    break;       // stop checking in this direction if blocked by piece
            }
            // Checking squares to the top-left
            if (k_row + i < 8 && k_col - i >= 0)
            {
                if (board[k_row + i][k_col - i] == '.')
                    board[k_row + i][k_col - i] = 'x';
                else if (board[k_row + i][k_col - i] == 'b' || board[k_row + i][k_col - i] == 'n' 
                    || board[k_row + i][k_col - i] == 'r' || board[k_row + i][k_col - i] == 'p' || board[k_row + i][k_col - i] == 'q')
                    break;
            }
            // Checking squares to the bottom-right
            if (k_row - i >= 0 && k_col + i < 8)
            {
                if (board[k_row - i][k_col + i] == '.')
                    board[k_row - i][k_col + i] = 'x';
                else if (board[k_row - i][k_col + i] == 'b' || board[k_row - i][k_col + i] == 'n' || board[k_row - i][k_col + i] == 'k'
                    || board[k_row - i][k_col + i] == 'r' || board[k_row - i][k_col + i] == 'p' || board[k_row - i][k_col + i] == 'q')
                    break;
            }
            // Checking squares to the bottom-left
            if (k_row - i >= 0 && k_col - i >= 0)
            {
                if (board[k_row - i][k_col - i] == '.')
                    board[k_row - i][k_col - i] = 'x';
                else if (board[k_row - i][k_col - i] == 'b' || board[k_row - i][k_col - i] == 'n' || board[k_row - i][k_col - i] == 'k'
                    || board[k_row - i][k_col - i] == 'r' || board[k_row - i][k_col - i] == 'p' || board[k_row - i][k_col - i] == 'q')
                    break;
            }
        }
    }
    else
    {
        // all possible moves of a bishop on a chess board
        // Checking squares in all four diagonal directions
        for (int i = 1; i <= 7; i++)
        {
            // Checking squares to the top-right
            if (k_row + i < 8 && k_col + i < 8)
            {
                if (board[k_row + i][k_col + i] == '.')
                    board[k_row + i][k_col + i] = 'x';
                else if (board[k_row + i][k_col + i] == 'B' || board[k_row + i][k_col + i] == 'N' || board[k_row + i][k_col + i] == 'K'
                    || board[k_row + i][k_col + i] == 'R' || board[k_row + i][k_col + i] == 'P' || board[k_row + i][k_col + i] == 'Q')
                    break;       // stop checking in this direction if blocked by piece
            }
            // Checking squares to the top-left
            if (k_row + i < 8 && k_col - i >= 0)
            {
                if (board[k_row + i][k_col - i] == '.')
                    board[k_row + i][k_col - i] = 'x';
                else if (board[k_row + i][k_col - i] == 'B' || board[k_row + i][k_col - i] == 'N' || board[k_row + i][k_col - i] == 'K'
                    || board[k_row + i][k_col - i] == 'R' || board[k_row + i][k_col - i] == 'P' || board[k_row + i][k_col - i] == 'Q')
                    break;
            }
            // Checking squares to the bottom-right
            if (k_row - i >= 0 && k_col + i < 8)
            {
                if (board[k_row - i][k_col + i] == '.')
                    board[k_row - i][k_col + i] = 'x';
                else if (board[k_row - i][k_col + i] == 'B' || board[k_row - i][k_col + i] == 'N' || board[k_row - i][k_col + i] == 'K'
                    || board[k_row - i][k_col + i] == 'R' || board[k_row - i][k_col + i] == 'P' || board[k_row - i][k_col + i] == 'Q')   
                    break;
            }
            // Checking squares to the bottom-left
            if (k_row - i >= 0 && k_col - i >= 0)
            {
                if (board[k_row - i][k_col - i] == '.')
                    board[k_row - i][k_col - i] = 'x';
               
                else if (board[k_row - i][k_col - i] == 'B' || board[k_row - i][k_col - i] == 'N' || board[k_row - i][k_col - i] == 'K'
                    || board[k_row - i][k_col - i] == 'R' || board[k_row - i][k_col - i] == 'P' || board[k_row - i][k_col - i] == 'Q')
                    break;
            }
        }
    }
}
void knightpossibilities()
{
    if (turn % 2 == 0)
    {
        // all possible moves of a knight on a chess board
        // Generate all possible knight moves
        int moves[8][2] = { {2,1}, {2,-1}, {-2,1}, {-2,-1}, {1,2}, {1,-2}, {-1,2}, {-1,-2} };
        for (int i = 0; i < 8; i++)
        {
            int row = k_row + moves[i][0];
            int col = k_col + moves[i][1];
            if (row >= 0 && row < 8 && col >= 0 && col < 8 && board[row][col] == '.')
            {
                board[row][col] = 'x';
            }
        }
    }
    else
    {
        int moves[8][2] = { {2,1}, {2,-1}, {-2,1}, {-2,-1}, {1,2}, {1,-2}, {-1,2}, {-1,-2} };
        for (int i = 0; i < 8; i++)
        {
            int row = k_row + moves[i][0];
            int col = k_col + moves[i][1];
            if (row >= 0 && row < 8 && col >= 0 && col < 8 && board[row][col] == '.')
            {
                board[row][col] = 'x';
            }
        }
    }
}


void checkmate()
{
    cout << "OOPS! YOU SHOULD SAVE THE KING FROM BEING CHECKMATE" << endl;
}


