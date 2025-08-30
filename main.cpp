/**
 * @author Dawid 'Bugi' Bogusz
 * @date 2022-06-01
 */

#include <iostream>
#include <Windows.h>
#include <string>
#include <conio.h>
#include <math.h>

//for time control
#include <ctime>
#include <chrono>
#include <thread>
using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono; // nanoseconds, system_clock, seconds

//#include <vector>
//#include <stack>

using namespace std;


const uint8_t BORDER_CHAR = 219; //█

unsigned int GameWidth, GameHeight, cmdWidth, cmdHeight, points, moveDirection;
int GameSpeed;
string cmdMode;
bool gameRunning, programRunning, gamePaused;
char ClickedKey;
char** gameBoard;
char** tempGameBoard;

int moveTime = 0;

unsigned int PlayerPosX, PlayerPosY, PlayerLength=1;

//function prototypes
void StartMenu();
void GameBoardInit();
void GameBoardPrint();
void GameBoardCopy(char** src, char** dest);
bool GameBoardChanged(char** a, char** b);
void KeyboardInputHandler();
void MemClean();
void GameLogic();

int main(int argc, char** argv)
{
    programRunning = true;

    while(programRunning)
    {
        if(!gameRunning) // if game is not running show menu
        {
            MemClean();
            system("mode con:cols=70 lines=35");    //min cols=15 lines=1
            
            StartMenu();
            
            //add borders to game size
            GameWidth+=2;
            GameHeight+=2;

            GameBoardInit(); //initialize game board

            if(GameWidth > 39) cmdWidth=GameWidth;
            else cmdWidth = 39;
            cmdHeight = GameHeight;

            points = 0;

            PlayerPosX = floor(GameWidth/2);
            PlayerPosY = floor(GameHeight/2);

            moveDirection = 0;

            gameRunning = true;
            gamePaused = false;
            
            cmdMode = "mode con:cols=" + to_string(cmdWidth) + " lines=" + to_string(cmdHeight+3);
            system(cmdMode.c_str());    //c_str converts string to const char*
        }
        else if(gameRunning && !gamePaused) //if game is running and not paused
        {
            GameBoardCopy(gameBoard, tempGameBoard); //copy game board to temp array for further detection of changes

            KeyboardInputHandler(); //check for keyboard input

            GameLogic();

            //checks if there were any changes in game board and if so, clears console and prints new game board
            if(GameBoardChanged(gameBoard, tempGameBoard))
            {
                system("cls"); //clear console command

                cout<<"=== Snake in console ==="<<endl;
                cout<<"Points: "<<points<<" | Click ESC to go to menu\n"<<endl;

                GameBoardPrint(); //print game board
            }
        }
        else if(gameRunning && gamePaused) //if game is paused
        {
            KeyboardInputHandler(); //check for keyboard input
        }
    }

    system("pause"); //wait for user input before closing console
    return 0;
}


//==================================


void StartMenu()
{
    cout<<"========================== Snake in console =========================="<<endl;
    cout<<"Made by Dawid \"Bugi\" Bogusz | Github: https://github.com/BugiBugi205\n"<<endl;

    cout<<"Enter game width (min 3): ";
    do{
        cin>>GameWidth;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(512,'\n');
            cout << "Not a number, enter correct value: ";
        }
        else if(GameWidth<3) cout<<"Apply to size requrements: ";
    } while (GameWidth<3);

    cout<<"\nEnter game height (min 3): ";
    do{
        cin>>GameHeight;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(512,'\n');
            cout << "Not a number, enter correct value: ";
        }
        else if(GameHeight<3) cout<<"Apply to size requrements: ";
    } while (GameHeight<3);

    cout<<"\nEnter game speed (tiles/s): ";
    do{
        cin>>GameSpeed;
        GameSpeed = 1000/GameSpeed;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(512,'\n');
            cout << "Not a number, enter correct value: ";
        }
        else if(GameSpeed<=0) cout<<"Enter correct value: ";
    } while (GameSpeed<=0);
} 

void GameLogic()
{
    if(clock()>moveTime)
    {
        //border collision detection
        if(PlayerPosX <= 0 || PlayerPosX >= GameWidth-1 || PlayerPosY <= 0 || PlayerPosY >= GameHeight-1)
        {
            gameRunning = false;
            return;
        }

        gameBoard[PlayerPosX][PlayerPosY] = '#';

        if      (moveDirection == 1) PlayerPosY--;
        else if (moveDirection == 2) PlayerPosY++;
        else if (moveDirection == 3) PlayerPosX--;
        else if (moveDirection == 4) PlayerPosX++;

        //sleep_for(seconds(1));
        moveTime = clock() + GameSpeed;
    }
    
    //if snake fills whole board
    if(PlayerLength == GameWidth * GameHeight)
    {
        //win condition
        gameRunning = false;
        return;
    } 
}

void GameBoardInit()
{
    //creates 2d array od gameboard
    gameBoard = new char *[GameWidth];
    for(int i=0; i<GameWidth; i++)
    {
        gameBoard[i] = new char [GameHeight];
    }

    //creates 2d array od temp gameboard
    tempGameBoard = new char *[GameWidth];
    for(int i=0; i<GameWidth; i++)
    {
        tempGameBoard[i] = new char [GameHeight];
    }

    //fills gameboard array with empty spaces
    for(int i=0; i<GameHeight; i++)
    {
        for(int x=0; x<GameWidth; x++)
        {
            gameBoard[x][i] = ' ';
        }
    }

    //fills gameboard array borders with special character
    for (int i=0; i<GameWidth; i++)
    {
        gameBoard[i][0] = BORDER_CHAR; //top
        gameBoard[i][GameHeight-1] = BORDER_CHAR; //bottom
    }
    for (int i = 0; i < GameHeight; i++)
    {
        gameBoard[0][i] = BORDER_CHAR; //left
        gameBoard[GameWidth-1][i] = BORDER_CHAR; //right
    }
}

void GameBoardPrint()
{
    for(int i=0; i<GameHeight; i++)
    {
        for(int x=0; x<GameWidth; x++)
        {
            cout<<gameBoard[x][i];
        }
        if(i != GameHeight-1) cout<<endl;
    }
}

//copies game board array to temp array
void GameBoardCopy(char** src, char** dest) {
    for(int i=0; i<GameWidth; i++)
    {
        for(int j=0; j<GameHeight; j++)
        {
            dest[i][j] = src[i][j];
        }
    }
}

//checks if game board changed
bool GameBoardChanged(char** a, char** b) {
    for(int i=0; i<GameWidth; i++)
        for(int j=0; j<GameHeight; j++)
            if(a[i][j] != b[i][j])
                return true;
    return false;
}

void KeyboardInputHandler()
{
    if(_kbhit()){
        ClickedKey = _getch();
    }    

    switch (ClickedKey)
    {
    case 27: //ESC
        gameRunning = false;
        break;
    case ' ': //space
        gamePaused = !gamePaused;
        if(gamePaused) cout<<"\nGame Paused"; //notify user that game is paused
        break;
    case 'w': case 'W':
        if(moveDirection != 2) moveDirection=1;
        break;
    case 's': case 'S':
        if(moveDirection != 1) moveDirection=2;
        break;
    case 'a': case 'A':
        if(moveDirection != 4) moveDirection=3;
        break;
    case 'd': case 'D':
        if(moveDirection != 3) moveDirection=4;
        break;
    default:
        break;
    }
    ClickedKey = 0;
}

void MemClean()
{
    for(int i=0; i<GameWidth; i++)
    {
        delete [] gameBoard[i];
        delete [] tempGameBoard[i];
    }

    delete [] gameBoard;
    delete [] tempGameBoard;
}