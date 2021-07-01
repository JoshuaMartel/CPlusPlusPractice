// Sudoku.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <algorithm>
//#include <random>

using namespace std;

class Board 
{
public:
    Board(char board[][9]);
    Board();
    void DisplayBoard();
    void ChangeTile(int row, int col, char num);
    void NewBoard();
    void PlayerBoard(int dif);
    void DisplayRefBoard();
    void ResetBoard();

    void CreateReferenceBoard();

    bool MoveIsLegal(char const board[][9], int row, int col, char tile);
    bool IsSolved();

private:
    char rowColBoard[9][9];
    char referenceBoard[9][9];
    
};

Board::Board()
{
    
    for (int i = 0; i < 9; ++i)
    {
        for (int j = 0; j < 9; ++j)
        {
            rowColBoard[i][j] = '0';
        }
    }
}

Board::Board(char board[][9])
{

    for (int i = 0; i < 9; ++i)
    {
        for (int j = 0; j < 9; ++j)
        {
            rowColBoard[i][j] = board[i][j];
        }
    }
}

void Board::CreateReferenceBoard()
{
    for (int i = 0; i < 9; ++i)
    {
        for (int j = 0; j < 9; ++j)
        {
            if (rowColBoard[i][j] != ' ')
            {
                referenceBoard[i][j] = '*';
            }
            else {
                referenceBoard[i][j] = ' ';
            }
        }
    }
}

void Board::DisplayBoard()
{
    for (int i = 0; i < 9; ++i)
    {
        for (int j = 0; j < 9; j += 3)
        {
            cout << " || " << rowColBoard[i][j] << " | " << rowColBoard[i][j + 1] << " | " << rowColBoard[i][j + 2];
        }
        cout << " || ";
        cout << "\n";

        if ((i + 1) % 3 == 0)
        {
            for (int k = 0; k < 17 * 3; ++k)
            {
                cout << "-";
            }
            cout << "\n";
        }

    }

}

void Board::DisplayRefBoard()
{
    for (int i = 0; i < 9; ++i)
    {
        for (int j = 0; j < 9; j += 3)
        {
            cout << " || " << referenceBoard[i][j] << " | " << referenceBoard[i][j + 1] << " | " << referenceBoard[i][j + 2];
        }
        cout << " || ";
        cout << "\n";

        if ((i + 1) % 3 == 0)
        {
            for (int k = 0; k < 17 * 3; ++k)
            {
                cout << "-";
            }
            cout << "\n";
        }

    }
}

void Board::ChangeTile(int row, int col, char num = '1')
{
    // for debugging
    //cout <<endl << row << " " << col << " " << num << endl; 
    try {
        if (referenceBoard[row-1][col-1] == '*')
        {
            cout << "You cannot change that tile." << endl;
        }
        else
        {
            rowColBoard[row-1][col-1] = num;
        }
    }
    catch (...)
    {
        cout << "Error in ChangeTile" << endl;
    }

    
}

bool Board::MoveIsLegal(char const board[][9], int row, int col, char tile)
{
    //3 creteria must be satisfied:
    //row has no repeats, column has no repeats, and box has no repeats

    for (int i = 0; i < 9; ++i) //check row and col
    {
        if (board[row][i] == tile) {
            //cout << tile;
            return false;
        }
        else if (board[i][col] == tile) {
            return false;
        }
    }
 

    for (int i = 0; i < 9; ++i)
    {
        for (int j = 0; j < 9; ++j)
        {
            if ((row + 3) / 3 == (i + 3) / 3 && (col + 3) / 3 == (j + 3) / 3)
            {
                if (board[i][j] == tile) {
                    return false;
                }
            }
        }
    }
    return true;
}

bool Board::IsSolved()
{
    for (int row = 0; row < 9; ++row)
    {
        //row, col, or box
        for (int col = 0; col < 9; ++col)
        {
            for (int k = 0; k < 9; ++k) //tiles left to check in a particular set:
            {
                if (rowColBoard[row][col] == ' ') { //Unfilled tile
                    return false;
                }
                else if (rowColBoard[row][col] == rowColBoard[row][k] && k != col) { //One of the columns has a duplicate
                    return false;
                }
                else if (rowColBoard[row][col] == rowColBoard[k][col] && k != row) { //One of the rows has a duplicate
                    return false;
                }
            }

           for (int i = 0; i < 9; ++i)
            {
                for (int j = 0; j < 9; ++j)
                {
                    if ((row + 3) / 3 == (i + 3) / 3 && (col + 3) / 3 == (j + 3) / 3)
                    {
                        //Test if 3x3 has duplicates
                        if (rowColBoard[row][col] == rowColBoard[i][j] && i != row && j != col) {
                            return false;
                        }
                    }
                }
            }
        }
    }
    // if all tests fail, then the board is solved
    return true;
}

void Board::ResetBoard() 
{
    for (int i = 0; i < 9; ++i)
    {
        for (int j = 0; j < 9; ++j)
        {
            rowColBoard[i][j] = '0';
        }
    }
}

void Board::NewBoard()
{
    
    
    char tile = '0';
    int numIterations = 0;  //Prevents an infinite loop
    //Main solving loop
    for (int i = 0; i < 9; ++i)
    {

        vector<char> tilesArr{ '1','2','3','4','5','6','7','8','9' }; //Numbers left in row
        random_shuffle(tilesArr.begin(), tilesArr.end());             //Shuffle array
        vector<char>::iterator iterTile = tilesArr.begin();               //Declare after array is shuffled
        
        int lastEl = tilesArr.size() - 1;

        //Solve line-by-line tsarting from top row, left to right        
        int j = 0;
        while(!tilesArr.empty())
        {
            numIterations++;
            //Error handling
            if (iterTile == tilesArr.end()) {
                iterTile -= 1;
                //cout << "\nIterator out of range\n";
                //cout << "element it stopped on was: " << *iterTile << "\n";
               // cout << "size of vector is: " << tilesArr.size() << "\n\n";
                break;
            }


            tile = *iterTile;
            if (MoveIsLegal(rowColBoard, i, j, tile))
            {
                // for 9x9x board
                rowColBoard[i][j] = *iterTile;

                tilesArr.erase(iterTile);       //iterTile is now invalid
                iterTile = tilesArr.begin();    //revalidates the iterator
                lastEl = tilesArr.size() - 1;
                j++;                            //We only increment to the next board tile when if the current is filled
            }
            else
            {
                ++iterTile;
            }    
        }
        //if a solution cannot be found during the current iteration
        if (tilesArr.size() > 0) { // clear entire row and start again
            for (int k = 0; k < 9; ++k) {
                rowColBoard[i][k] = '0';
            }
            i--;
        }
        // Essentially forces a complete restart of the board building -
        // if the building takes too long
        if (numIterations >= 10000) 
        {
            //cout << "\n**Restarting Building Process**\n\n"; //For debugging
            i = 0; j = 0; numIterations = 0;
            ResetBoard();
            
        }
    }
    
}

void Board::PlayerBoard(int dif) 
{
    // the number of clues given depends on difficulty
    int clues = 0;
    switch (dif) {
    case 1:
        clues = 40;
        break;
    case 2:
        clues = 28;
        break;
    case 3:
        clues = 17;
        break;
    default:
        clues = 40;
        break;
    }

    srand(static_cast<unsigned int>(time(0))); //seed random number generator
    int i = 81 - clues;                     //iterations
    int row, col;
    while (i > 0) {
        row = rand() % 9;
        col = rand() % 9;

        if (rowColBoard[row][col] == ' ') {
            continue;
        }
        else {
            rowColBoard[row][col] = ' ';
            i--;
        }
    }
}


void Menu();
void GreetPlayer();
void Instructions();
int GetPlayerInput();
int * GetMove();
bool DoMove(Board board, int row, int col, char tile);
int GetDifficulty();
bool MoveIsLegal(const Board board,int row, int col, char tile);




int main()
{
    ///*
    GreetPlayer();
    Menu();

    int input,row,col,index,dif;
    string sInput;
    dif = 0; index = 0;
    char digits[] = { '0','1','2','3', '4','5','6','7','8','9' };
    char tile;
    int * pMove;
    Board board;
    bool testGameRunning = false;
    const enum {INSTR,MOVE,NEWGAME,ISSOLVED,EXIT,MENU};

    input = GetPlayerInput();

    while (input != EXIT)  //Main loop
    {
        switch (input)
        {
        case INSTR:
            Instructions();
            break;

        case MOVE:
            if (!testGameRunning) {
                cout << "You have not started a game!" << "\n";
            }
            else {
                pMove = GetMove(); // returns an array containing the positon as a row and column integer and the tile value
                col = *pMove;
                pMove++;
                row = *pMove;
                pMove++;
                index = (*pMove);
                tile =  digits[index];

                board.ChangeTile(row, col, tile); //if the player tries to change a starting tile, no tile will change
            }
            break;

        case NEWGAME:
            if (testGameRunning) board.ResetBoard();
            board.NewBoard();
            dif = GetDifficulty();
            board.PlayerBoard(dif);
            board.CreateReferenceBoard();
            testGameRunning = true;
            break;

        case ISSOLVED:
            if (testGameRunning) // Test if the player has started a game
            {             
                if (board.IsSolved())
                {
                    cout << "Congradulations! You have solved the puzzle." << endl;
                    cout << "Want to play again? If so, type 2 for New Game, or 4 for to Exit." << "\n\n";
                }
                else
                {
                    cout << "Sorry, your solution is wrong." << "\n\n";
                }
            }
            else 
            {
                cout << "You have not started a game!" << "\n";
            }
            break;

        case EXIT:
            break;

        case MENU:
            Menu();
            break;

        default:
            Menu();
            break;
        }

        if (testGameRunning) //If a game is running, show board
        {
            board.DisplayBoard();
        }
        input = GetPlayerInput(); //Obtain player input before starting a new iteration
    }
    //*/
    
     /*
    int dif = 3;
    Board board;
    board.NewBoard();
    board.DisplayBoard();
    if (board.IsSolved()) {
        cout << "\nSuccess! Solver works\n";
    }
    board.PlayerBoard(dif);
    board.DisplayBoard();
    
    if (!board.IsSolved()) {
        cout << "\nSuccess! Solver works\n";
    }
    board.CreateReferenceBoard();
    board.DisplayRefBoard();

    Board board2;
    board2.ChangeTile(1, 1, '1');
    board2.DisplayBoard();

    /*int input, row, col, index;
    string sInput;
    dif = 0; index = 0;
    char digits[] = { '0','1','2','3', '4','5','6','7','8','9' };
    char tile;
    int* pMove;
    cin >> input;
    cout << "Entering Loop." << endl;
    while (input != 0)
    {
        cin >> input;
        pMove = GetMove(); // returns an array containing the positon as a row and column integer and the tile value
        row = *pMove;
        pMove++;
        col = *pMove;
        pMove++;
        index = (*pMove);
        tile = digits[index];

        board.ChangeTile(row, col, tile);
        board.DisplayBoard();

    }*/
    //*/

    return 0;
}

void GreetPlayer()
{
    cout << "Hello, and welcome to Sudoku." << "\n";
}

void Menu()
{
    cout << "Welcome to the Sudoku menu." << endl;
    cout << "Type each number for the following" << "\n\n";
    cout << "0 - Game instructions" << endl;
    cout << "1 - Make a move" << endl;
    cout << "2 - Start a new game" << endl;
    cout << "3 - Check if puzzle is solved" << endl;
    cout << "4 - Exit" << endl;
    cout << "5 - Menu" << endl;
}

void Instructions()
{
    cout << "The board is a 9x9 set of squares, with rows labeled 1-9 from left to right" << endl;
    cout << "and columns labeled 1-9 from top to bottom." << endl;
    cout << "To make a move, enter a 2-digit number for the position, 1st digit = row," << endl;
    cout << "2nd digit = column, ";
    cout << "and then enter the number you wish to place there." << endl;
    cout << endl;
    cout << "Each row, column, and 3x3 square can only have one of each number " << endl;
    cout << "from 1-9. Once all squares are filled, type 'check' to see if  you have solved it" << endl;
}

int GetPlayerInput()
{
    int input;
    string sInput;
    const enum { INSTR, MOVE, NEWGAME, ISSOLVED, EXIT, MENU };
    cin >> sInput;
    try
    {
        input = stoi(sInput);
        switch (input)
        {
        case INSTR:
            return INSTR;
        case MOVE:
            return MOVE;
        case NEWGAME:
            return NEWGAME;
        case ISSOLVED:
            return ISSOLVED;
        case EXIT:
            return EXIT;
        case MENU:
            return MENU;
        default:
            cout << "That is not an option." << "\n\n";
            return MENU;
        }
    }
    catch (...)
    {
        cout << "That is not an option." << "\n\n";
        return MENU;
    }
}

int GetDifficulty()
{
    cout << "Enter:" << endl;
    cout << "1 - Easy" << endl;
    cout << "2 - Medium" << endl;
    cout << "3 - Hard" << endl;
    int dif = 0;
    string sDif;
    cin >> sDif;

    try
    {
        dif = stoi(sDif);
        
        switch (dif)
        {
        case 1:
            cout << "You chose Easy." << "\n\n";
            break;
        case 2:
            cout << "You chose Medium." << "\n\n";
            break;
        case 3:
            cout << "You chose Hard. Good Luck." << "\n\n";
            break;
        default: //If player chooses an invalid input, start an easy game
            cout << "That is not an option. Starting an \"Easy\" level game." << "\n\n";
            dif = 1;
            break;
        }
    }
    catch (...)
    {
        cout << "That is not an option. Starting an \"Easy\" level game." << "\n\n";
        return 1;
    }
    
    return dif;
}

int * GetMove()
{
    string sPosition, sNum;
    int position, num;
    int static arr[3] = { 0,0,0 };
    
    cout << "Enter position:\n";

    cin >> sPosition;

    cout << "Enter number:\n";
    cin >> sNum;

    try
    {
        position = stoi(sPosition);
        num      = stoi(sNum);
        if (num >= 10 || position >= 100) {
            throw 20;
        }
    }
    catch (...)
    {
        cout << "Invalid input." << endl;
        return arr;
    }

    arr[0] = position % 10;
    arr[1] = (position - position % 10)/10;
    arr[2] = num;

    return arr;
}
/*
bool DoMove(Board board, int row, int col, char tile)
{
    if board.
    board.ChangeTile(row, col, tile);
}
*/








// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
