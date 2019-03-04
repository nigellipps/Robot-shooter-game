// Nigel Lipps
//  utilities.cpp


///////////////////////////////////////////////////////////////////////////
//  Auxiliary function implementations
///////////////////////////////////////////////////////////////////////////
#include "globals.h"
#include <iostream>

using namespace std;
int decodeDirection(char dir)
{
    switch (dir)
    {
        case 'u':
            return UP;
        case 'd':
            return DOWN;
        case 'l':
            return LEFT;
        case 'r':
            return RIGHT;
            
    }
    return -1;  // bad argument passed in!    
}

///////////////////////////////////////////////////////////////////////////
//  clearScreen implementations
///////////////////////////////////////////////////////////////////////////
#ifdef _MSC_VER    //  Microsoft Visual C++
#include <windows.h>
void clearScreen()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    DWORD dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
    COORD upperLeft = { 0, 0 };
    DWORD dwCharsWritten;
    FillConsoleOutputCharacter(hConsole, TCHAR(' '), dwConSize, upperLeft,&dwCharsWritten);SetConsoleCursorPosition(hConsole, upperLeft);
    
}
#else  // not Microsoft Visual C++, so assume UNIX interface
#include <cstring>
void clearScreen()  // will just write a newline in an Xcode output window
{
    static const char* term = getenv("TERM");
    if (term == nullptr  ||  strcmp(term, "dumb") == 0)
        cout << endl;
    else
    {
        static const char* ESC_SEQ = "\x1B[";  // ANSI Terminal esc seq:  ESC [
        cout << ESC_SEQ << "2J" << ESC_SEQ << "H" << flush;
    }
}
#endif
