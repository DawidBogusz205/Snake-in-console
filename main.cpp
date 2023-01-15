/**
 * @author Dawid 'Bugi' Bogusz
 * @date 2022-06-01
 */

#include <iostream>
#include <Windows.h>
#include <ctime>
#include <string>
#include <conio.h>
#include <math.h>

using namespace std;

const uint8_t BORDER_CHAR = 219; //█

unsigned int GameWidth, GameHeight, cmdWidth, cmdHeight, points, moveDirection;
float GameSpeed;
string cmdMode;
bool gameRunning, programRunning, gamePaused;
char ClickedKey;
char** gameBoard;

int moveTime = 0;

unsigned int PlayerPosX, PlayerPosY, PlayerLength=1;

//function prototypes
void StartMenu();
void KeyboardInputHandler();
void MemClean();
void GameLogic();

int main(int argc, char** argv)
{
    programRunning=true;

    while(programRunning)
    {
        if(!gameRunning)
        {
            system("mode con:cols=70 lines=35");    //min cols=15 lines=1

            StartMenu();
            
            GameWidth+=2;
            GameHeight+=2;

            gameBoard = new char *[GameWidth];
            for(int i=0; i<GameWidth; i++)
            {
                gameBoard[i] = new char [GameHeight];
            }

            for(int i=0; i<GameHeight; i++)
            {
                for(int x=0; x<GameWidth; x++)
                {
                    gameBoard[x][i] = ' ';
                }
            }

            for (int i=0; i<GameWidth; i++)
            {
                gameBoard[i][0] = BORDER_CHAR;
                gameBoard[i][GameHeight-1] = BORDER_CHAR;
            }

            for (int i = 0; i < GameHeight; i++)
            {
                gameBoard[0][i] = BORDER_CHAR;
                gameBoard[GameWidth-1][i] = BORDER_CHAR;
            }

            if(GameWidth > 39) cmdWidth=GameWidth;
            else cmdWidth=39;
            cmdHeight=GameHeight;

            points=0;
            PlayerPosX = floor(GameWidth/2);
            PlayerPosY = floor(GameHeight/2);
            moveDirection=0;

            gameRunning=true;
            gamePaused=false;
            
            cmdMode = "mode con:cols=" + to_string(cmdWidth) + " lines=" + to_string(cmdHeight+3);
            system(cmdMode.c_str());    //c_str converts string to const char*
        }
        else
        {
            cout<<"=== Snake in console ==="<<endl;
            cout<<"Points: "<<points<<" | Click ESC to go to menu\n"<<endl;

            for(int i=0; i<GameHeight; i++)
            {
                for(int x=0; x<GameWidth; x++)
                {
                    cout<<gameBoard[x][i];
                }
                if(i!=GameHeight-1) cout<<endl;
            }

            KeyboardInputHandler();
            
            //pause
            if(gamePaused)
            {
                cout<<"\nGame Paused";

                while(gamePaused) KeyboardInputHandler();
            }

            GameLogic();

            system("cls");
        }
    }

    system("pause");
    return 0;
}


//==================================


void StartMenu()
{
    MemClean();

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
            gameRunning=false;
            return;
        }

        gameBoard[PlayerPosX][PlayerPosY] = '#';

        if(moveDirection==1) PlayerPosY--;
        else if(moveDirection==2) PlayerPosY++;
        else if(moveDirection==3) PlayerPosX--;
        else if(moveDirection==4) PlayerPosX++;

        moveTime=clock()+200;
    }
    if(PlayerLength==GameWidth*GameHeight)
    {
        gameRunning=false;
        return;
    } 
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
    case ' ':
        gamePaused = !gamePaused;
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
    ClickedKey=0;
}

void MemClean()
{
    for(int i=0; i<GameWidth; i++)
    {
        delete [] gameBoard[i];
    }

    delete [] gameBoard;
}