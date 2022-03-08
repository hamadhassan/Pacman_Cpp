#include <iostream>
#include <fstream>
#include <sstream>
#include <windows.h>
#include <time.h>
using namespace std;
//----------------------- PROTOTYPE -----------------------
void loadMaze();
void displayMaze();
void movePacmanLeft();
void movePacmanRight();
void movePacmanUp();
void movePacmanDown();
void calculateScore();
void printScore();
void gotoxy(int y, int x);
int ghostDirection();
bool ghostMovement1(); // random movement
bool ghostMovement2(); // horizontal movement
bool ghostMovement3(); // vertical movement
bool ghostMovement4(); // toward packman
bool over();
//----------------------- DATA STRUCTURE -----------------------
char maze[24][71];
int pacmanX = 10; // X Coordinate of Pacman
int pacmanY = 32; // Y Coordinate of Pacman
int score = 0;
int ghostX = 19;    // X Coordinate of Ghost no 1
int ghostY = 25;    // Y Coordinate of Ghost no 1
int ghostX2 = 15;   // X Coordinate of Ghost no 2
int ghostY2 = 25;   // Y Coordinate of Ghost no 2
int ghostX3 = 2;    // X Coordinate of Ghost no 3
int ghostY3 = 2;    // Y Coordinate of Ghost no 3
int ghostX4 = 4;    // X Coordinate of Ghost no 4
int ghostY4 = 4;    // XY Coordinate of Ghost no 4
bool flagG2 = true; // horizontal movement
bool flagG3 = true; // vertical movement
bool gameRunning = true;
char previousItem = ' ';
bool gameclose = true;
int main()
{
    system("cls");
    loadMaze();
    displayMaze();
    gotoxy(pacmanY, pacmanX);
    cout << "P";
    while (gameRunning == false || gameclose == true)
    {
        printScore();
        Sleep(200);
        gameRunning = ghostMovement1();
        gameRunning = ghostMovement2();
        gameRunning = ghostMovement3();
        if (GetAsyncKeyState(VK_LEFT))
        {
            movePacmanLeft(); // Function call to move Pacman towards left
        }
        if (GetAsyncKeyState(VK_RIGHT))
        {
            movePacmanRight(); // Function call to move Pacman towards right
        }
        if (GetAsyncKeyState(VK_UP))
        {
            movePacmanUp(); // Function call to move Pacman towards up
        }
        if (GetAsyncKeyState(VK_DOWN))
        {
            movePacmanDown(); // Function call to move Pacman towards down
        }
        if (GetAsyncKeyState(VK_ESCAPE))
        {
            gameRunning = false; // Stop the game
        }
    }
    system("cls");
    cout << "You lost game";
}
void loadMaze()
{
    string record;
    fstream read;
    read.open("maze.txt", ios::in);
    for (int i = 0; i < 24; i++)
    {
        getline(read, record);
        for (int j = 0; j < 71; j++)
        {
            maze[i][j] = record[j];
        }
    }
    read.close();
}
void displayMaze()
{
    for (int x = 0; x < 24; x++)
    {
        for (int y = 0; y < 71; y++)
        {
            cout << maze[x][y];
        }
        cout << endl;
    }
}
void movePacmanLeft()
{
    if (maze[pacmanX][pacmanY - 1] == ' ' || maze[pacmanX][pacmanY - 1] == '.')
    {
        if (maze[pacmanX][pacmanY] == '.')
        {
            calculateScore();
        }
        maze[pacmanX][pacmanY] = ' ';
        gotoxy(pacmanY, pacmanX);
        cout << " ";
        pacmanY = pacmanY - 1;
        gotoxy(pacmanY, pacmanX);
        cout << "P";
    }
}
void movePacmanRight()
{
    if (maze[pacmanX][pacmanY + 1] == ' ' || maze[pacmanX][pacmanY + 1] == '.')
    {
        if (maze[pacmanX][pacmanY] == '.')
        {
            calculateScore();
        }
        maze[pacmanX][pacmanY] = ' ';
        gotoxy(pacmanY, pacmanX);
        cout << " ";
        pacmanY = pacmanY + 1;
        gotoxy(pacmanY, pacmanX);
        cout << "P";
    }
}
void movePacmanUp()
{
    if (maze[pacmanX - 1][pacmanY] == ' ' || maze[pacmanX - 1][pacmanY] == '.')
    {
        if (maze[pacmanX][pacmanY] == '.')
        {
            calculateScore();
        }
        maze[pacmanX][pacmanY] = ' ';
        gotoxy(pacmanY, pacmanX);
        cout << " ";
        pacmanX = pacmanX - 1;
        gotoxy(pacmanY, pacmanX);
        cout << "P";
    }
}
void movePacmanDown()
{
    if (maze[pacmanX + 1][pacmanY] == ' ' || maze[pacmanX + 1][pacmanY] == '.')
    {
        if (maze[pacmanX][pacmanY] == '.')
        {
            calculateScore();
        }
        maze[pacmanX][pacmanY] = ' ';
        gotoxy(pacmanY, pacmanX);
        cout << " ";
        pacmanX = pacmanX + 1;
        gotoxy(pacmanY, pacmanX);
        cout << "P";
    }
}
void calculateScore()
{
    score = score + 1;
}
void printScore()
{
    gotoxy(0, 23);
    cout
        << endl
        << "Score: " << score << endl;
}
void gotoxy(int x, int y)
{
    COORD coordinates;
    coordinates.X = x;
    coordinates.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}
int ghostDirection()
{
    srand(time(0));
    int result = 1 + (rand() % 4);
    return result;
}
bool ghostMovement1()
{
    int value = ghostDirection();
    if (value == 1)
    {
        if (maze[ghostX][ghostY - 1] == ' ' || maze[ghostX][ghostY - 1] == '.' || maze[ghostX][ghostY - 1] == 'P')
        {
            if (previousItem == 'P')
            {
                return false;
            }
            previousItem = maze[ghostX][ghostY];
            ghostY = ghostY - 1;
            gotoxy(ghostY, ghostX);
            cout << 'G';
            gotoxy(ghostY + 1, ghostX);
            cout << previousItem;
        }
    }
    if (value == 2)
    {
        if (maze[ghostX][ghostY + 1] == ' ' || maze[ghostX][ghostY + 1] == '.' || maze[ghostX][ghostY + 1] == 'P')
        {
            if (previousItem == 'P')
            {
                return false;
            }
            previousItem = maze[ghostX][ghostY];
            ghostY = ghostY + 1;
            gotoxy(ghostY, ghostX);
            cout << 'G';
            gotoxy(ghostY - 1, ghostX);
            cout << previousItem;
        }
    }
    if (value == 3)
    {
        if (maze[ghostX - 1][ghostY] == ' ' || maze[ghostX - 1][ghostY] == '.' || maze[ghostX - 1][ghostY] == 'P')
        {
            if (previousItem == 'P')
            {
                return 0;
            }
            previousItem = maze[ghostX][ghostY];
            ghostX = ghostX - 1;
            gotoxy(ghostY, ghostX);
            cout << 'G';
            gotoxy(ghostY, ghostX + 1);
            cout << previousItem;
        }
    }
    if (value == 4)
    {
        if (maze[ghostX + 1][ghostY] == ' ' || maze[ghostX + 1][ghostY] == '.' || maze[ghostX + 1][ghostY] == '.')
        {
            if (previousItem == 'P')
            {
                return 0;
            }
            previousItem = maze[ghostX][ghostY];
            ghostX = ghostX + 1;
            gotoxy(ghostY, ghostX);
            cout << 'G';
            gotoxy(ghostY, ghostX - 1);
            cout << previousItem;
        }
    }
    return true;
}
bool ghostMovement2()
{
    if (maze[ghostX2][ghostY2 + 1] == '|' || maze[ghostX2][ghostY2 + 1] == '%' || maze[ghostX2][ghostY2 + 1] == '#')
    {
        flagG2 = false;
    }
    else if (maze[ghostX2][ghostY2 - 1] == '|' || maze[ghostX2][ghostY2 - 1] == '%' || maze[ghostX2][ghostY2 - 1] == '#')
    {
        flagG2 = true;
    }
    if (flagG2 == true)
    {
        if (maze[ghostX2][ghostY2 + 1] == ' ' || maze[ghostX2][ghostY2 + 1] == '.' || maze[ghostX2][ghostY2 + 1] == 'P')
        {
            if (previousItem == 'P')
            {
                return false;
            }
            previousItem = maze[ghostX2][ghostY2];
            ghostY2 = ghostY2 + 1;
            gotoxy(ghostY2, ghostX2);
            cout << 'G';
            gotoxy(ghostY2 - 1, ghostX2);
            cout << previousItem;
        }
    }
    else if (flagG2 == false)
    {
        if (maze[ghostX2][ghostY2 - 1] == ' ' || maze[ghostX2][ghostY2 - 1] == '.' || maze[ghostX2][ghostY2 - 1] == 'P')
        {
            if (previousItem == 'P')
            {
                return false;
            }
            previousItem = maze[ghostX2][ghostY2];
            ghostY2 = ghostY2 - 1;
            gotoxy(ghostY2, ghostX2);
            cout << 'G';
            gotoxy(ghostY2 + 1, ghostX2);
            cout << previousItem;
        }
    }
    return true;
}
bool ghostMovement3()
{
    if (maze[ghostX3 + 1][ghostY3] == '|' || maze[ghostX3 + 1][ghostY3] == '%' || maze[ghostX3 + 1][ghostY3] == '#')
    {
        flagG3 = false;
    }
    else if (maze[ghostX3 - 1][ghostY3] == '|' || maze[ghostX3 - 1][ghostY3] == '%' || maze[ghostX3 - 1][ghostY3] == '#')
    {
        flagG3 = true;
    }
    if (flagG3 == true)
    {
        if (maze[ghostX3 + 1][ghostY3] == ' ' || maze[ghostX3 + 1][ghostY3] == '.' || maze[ghostX3 + 1][ghostY3] == 'P')
        {
            if (previousItem == 'P')
            {
                return false;
            }
            previousItem = maze[ghostX3][ghostY3];
            ghostX3 = ghostX3 + 1;
            gotoxy(ghostY3, ghostX3);
            cout << 'G';
            gotoxy(ghostY3, ghostX3 - 1);
            cout << previousItem;
        }
    }
    else if (flagG3 == false)
    {
        if (maze[ghostX3 - 1][ghostY3] == ' ' || maze[ghostX3 - 1][ghostY3] == '.' || maze[ghostX3 - 1][ghostY3] == 'P')
        {
            if (previousItem == 'P')
            {
                return false;
            }
            previousItem = maze[ghostX3][ghostY3];
            ghostX3 = ghostX3 - 1;
            gotoxy(ghostY3, ghostX3);
            cout << 'G';
            gotoxy(ghostY3, ghostX3 + 1);
            cout << previousItem;
        }
    }
    return true;
}
bool ghostMovement4()
{
    gotoxy(ghostY4--, ghostX4);
    cout << 'G';
}
bool over()
{
    if ((pacmanX == ghostX && pacmanY == ghostY) || (pacmanX == ghostX2 && pacmanY == ghostY2) || (pacmanX == ghostX3 && pacmanY == ghostX3))
    {
        return false;
    }
    return true;
}