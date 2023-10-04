#include <iostream>
#include <windows.h>
using namespace std;

void show_grid(char (&grid)[3][3]) //Function to show the board of game (Using double for-loop)
{
    cout<<endl;
    for (int i = 0; i < 3; i++)
    {
         cout<<"\t\t\t";
        for (int j = 0; j < 3; j++)
        {
            cout << " " << grid[i][j] << " |";
        }
        cout << "\b \b" << endl;
        if (i != 2)
            cout << "\t\t\t-----------" << endl;
    }
    cout << endl;
}

void add_mark(char (&grid)[3][3], char mark) //Function to add mark on the desired place of board
{
    int loc;
    cin >> loc;
    loc--;
    if (grid[loc / 3][loc % 3] == ' ')
        grid[loc / 3][loc % 3] = mark;
    else
    {
        cout << "Invalid Move! Try again: ";
        add_mark(grid, mark);
    }
}

bool check_draw(char (&grid)[3][3]) //Function to check if the game results in a draw
{
    bool checker = true;
    for (int i = 0; i < 3; i++)
    {
        if (grid[i][0] == ' ' || grid[i][1] == ' ' || grid[i][2] == ' ')
        {
            checker = false;
            break;
        }
    }
    return checker;
}
bool check_win(char grid[3][3]) //Function to check if the game results in a win
{
    bool checker = false;
    //Checking win at diagonal
    if ((grid[0][0] != ' ' && grid[0][0] == grid[1][1] && grid[1][1] == grid[2][2]) || 
        (grid[0][2] != ' ' && grid[0][2] == grid[1][1] && grid[1][1] == grid[2][0]))
    {
        cout << "\t\t3 Match found at Diagonal" << endl;
        checker = true;
    }
    else
    {
        for (int i = 0; i < 3; i++)
        {
            if (grid[i][0] != ' ' && grid[i][0] == grid[i][1] && grid[i][1] == grid[i][2]) //Checking win at row
            {
                cout << "\t\t3 Match found at Row " << i + 1 << endl;
                checker = true;
                break;
            }
            else if (grid[0][i] != ' ' && grid[0][i] == grid[1][i] && grid[1][i] == grid[2][i]) //Checking win at column

            {
                cout << "\t\t3 Match found at Column " << i + 1 << endl;
                checker = true;
                break;
            }
        }
    }
    return checker;
}

void play_game(int &score1, int &score2) //Function to start playing the game
{
    system("CLS");
    //Initializing game board and other variables used during the game
    char grid[3][3] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};
    char mark;
    bool player = false; //player = false -> player 1, player = true -> player 2
    string game_status = "Ongoing";
    while (true)
    {
        cout<<"\t\t\t\"NEW GAME\""<<endl<< "\t\tPlayer 1 (X)\tPlayer 2 (O)"<<endl;
        if (player)
        {   
            system("COLOR 0B");
            mark = 'O';
        }
        else
        {
            system("COLOR 0A");
            mark = 'X';
        }
        show_grid(grid);
        cout << "Game Status: " << game_status << endl;
        cout << "Player " << player + 1 << "'s Turn (" << mark << ") : ";
        add_mark(grid, mark);
        system("CLS");
        if (check_win(grid)) //Checking for a win
        {
            game_status = "Win";
            show_grid(grid);
            if (player == 0)
                score1++;
            else
                score2++;
            cout << "Game Status: "<< game_status<< endl<< "Player " << player + 1 << " has won the game!"<< endl;
        }
        else if (check_draw(grid)) //Checking for a draw
        {
            game_status = "Draw";
            show_grid(grid);
        cout << "Game Status: " << game_status<< endl;
        }
        if (game_status == "Win" || game_status == "Draw")
        {
            cout << "Score: " << score1 << " - " << score2 << endl;
            char choice;
            cout << endl << "Do you want to play another game? (y/n)" << endl;
            cin >> choice;
            if (choice == 'y') //For playing another game
                play_game(score1, score2);
            break;
         }
    player = !player; //Changing player's turn
    }
}

int main()
{   
    system("CLS");
    //Initializing scores and guide board
    int score1 = 0;
    int score2 = 0;
    char guide[3][3] = {
        {'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}};
    //Designing the game menu and calling function to start playing
    cout << "\t\t*************************" << endl
         << "\t\t* Tic - Tac - Toe (X|O) *" << endl
         << "\t\t*************************" << endl << endl
         <<"GUIDE: Game Board indicating numbers for different positions" << endl;
    show_grid(guide);
    cout<<"Starting a new game. "<<endl;
    system("PAUSE");
    play_game(score1, score2);
    system("COLOR 0F");
    cout << endl<< "\"Final Score\"" << endl << "Player 1 (X): " << score1 << " win(s)" << endl
         << "Player 2 (O): " << score2 << " win(s)" << endl
         << "Thanks for playing the game :)" << endl;
    return 0;
}