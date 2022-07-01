/**
 * @author Dawid 'Bugi' Bogusz
 * @date 2022-06-01
 */

#include <iostream>
#include <Windows.h>
#include <ctime>
#include <string>
#include <conio.h>

using namespace std;

unsigned int GameWidth, GameHeight,cmdWidth, cmdHeight, points;
float GameSpeed;
string cmdMode;
bool gameRunning, programRunning;
char ClickedKey;
char** gameBoard;

//function prototypes
void StartMenu();
void KeyboardInputHandler();
void MemClean();

int main(int argc, char** argv)
{
    programRunning=true;

    system("mode con:cols=70 lines=35");    //min cols=15 lines=1

    while(programRunning)
    {
        if(!gameRunning)
        {
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
                gameBoard[i][0] = '#';
                gameBoard[i][GameHeight-1] = '#';
            }

            for (int i = 0; i < GameHeight; i++)
            {
                gameBoard[0][i] = '#';
                gameBoard[GameWidth-1][i] = '#';
            }

            if(GameWidth > 35) cmdWidth=GameWidth;
            else cmdWidth=35;
            cmdHeight=GameHeight;
            
            cmdMode = "mode con:cols=" + to_string(cmdWidth) + " lines=" + to_string(cmdHeight+2);
            system(cmdMode.c_str());    //c_str converts string to const char*
        }
        else
        {
            cout<<"=== Snake in console ==="<<endl;
            cout<<"Points: "<<points<<" | Click ESC to go to menu"<<endl;

            for(int i=0;i<GameHeight;i++)
            {
                for(int x=0;x<GameWidth;x++)
                {
                    cout<<gameBoard[x][i];
                }
                if(i!=GameHeight-1) cout<<endl;
            }

            KeyboardInputHandler();

            system("cls");
        }
    }

    system("pause");
    return 0;
}


//==================================


void StartMenu()
{
    cout<<"========================== Snake in console ==========================\n"<<endl;

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

    gameRunning=true;
}

void KeyboardInputHandler()
{
    if(_kbhit()){
        ClickedKey = _getch();
    }

    switch (ClickedKey)
    {
    //ESC
    case 27:
        gameRunning = false;
        MemClean();
        break;
    default:
        break;
    }
    ClickedKey='P';
}

void MemClean()
{
    for(int i=0; i<GameWidth; i++)
    {
        delete [] gameBoard[i];
    }

    delete [] gameBoard;
}
