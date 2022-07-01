#include <iostream>
#include <Windows.h>
#include <ctime>
#include <string>
#include <conio.h>

using namespace std;

unsigned int GameWidth, GameHeight,cmdWidth, cmdHeight;
float GameSpeed;
string cmdMode;
bool gameRunning;
char ClickedKey;

//function prototypes
void StartMenu();
void KeyboardInputHandler();
void MemClean();

int main(int argc, char** argv)
{
    //min cols=15 lines=1
    system("mode con:cols=70 lines=35");

    StartMenu();

    cmdHeight=40;
    cmdWidth=80;
    
    cmdMode = "mode con:cols=" + to_string(cmdWidth) + " lines=" + to_string(cmdHeight);

    system(cmdMode.c_str());    //c_str converts string to const char*

    while(gameRunning)
    {
        cout<<"SNAKE";

        KeyboardInputHandler();

        system("cls");
    }

    system("pause");
    return 0;
}

void StartMenu()
{
    cout<<"========================== Snake in console ==========================\n"<<endl;

    cout<<"Enter game width (min 3): ";
    do{
        cin>>GameWidth;
        if(GameWidth<3) cout<<"Apply to size requrements: ";
    } while (GameWidth<3);

    cout<<"\nEnter game height (min 3): ";
    do{
        cin>>GameHeight;
        if(GameHeight<3) cout<<"Apply to size requrements: ";
    } while (GameHeight<3);
    
    cout<<"\nEnter game speed (tiles/s): ";
    do{
        cin>>GameSpeed;
        if(GameSpeed<=0) cout<<"Enter correct value: ";
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
        break;
    default:
        break;
    }
}