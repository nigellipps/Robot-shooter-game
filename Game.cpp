// Nigel Lipps
// Game.cpp


///////////////////////////////////////////////////////////////////////////
//  Game implementations
///////////////////////////////////////////////////////////////////////////
#include "globals.h"
#include "Game.h"
#include "Arena.h"
#include "Player.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

Game::Game(int rows, int cols, int nRobots)
{
    if (nRobots > MAXROBOTS)
    {
        cout << "***** Trying to create Game with " << nRobots<< " robots; only " << MAXROBOTS << " are allowed!" << endl;
        exit(1);
        
    }
    // Create arena
    m_arena = new Arena(rows, cols);
    // Add player
    int rPlayer = 1 + rand() % rows;
    int cPlayer = 1 + rand() % cols;
    m_arena->addPlayer(rPlayer, cPlayer);
    // Populate with robots
    while (nRobots > 0)
    {
        int r = 1 + rand() % rows;
        int c = 1 + rand() % cols;
        // Don't put a robot where the player is
        if (r != rPlayer  &&  c != cPlayer){
            m_arena->addRobot(r, c);
            nRobots--;
        }
    }
}

Game::~Game()
{
    delete m_arena;
}
void Game::play()
{
    Player* p = m_arena->player();
    if (p == nullptr)
    {
        m_arena->display("");
        return;
        
    }
    string msg = "";
    do
    {
        m_arena->display(msg);
        msg = "";
        cout << endl;
        cout << "Move (u/d/l/r/s/su/sd/sl/sr/c//q): ";
        string action;
        getline(cin,action);
        if (action.size() == 0)
            p->stand();
        else
        {
            switch (action[0])
            {
                default:   // if bad move, nobody moves
                    cout << '\a' << endl;  // beep
                    continue;
                case 'q':
                    return;
                case 'c':  // computer moves player
                    msg = p->takeComputerChosenTurn();
                    break;
                case 'u':
                    p->move(decodeDirection(action[0]));
                    break;
                case 'd':
                    p->move(decodeDirection(action[0]));
                    break;
                case 'l':
                    p->move(decodeDirection(action[0]));
                    break;
                case 'r':
                    p->move(decodeDirection(action[0]));
                    break;
                case 's':
                    if (action.size() < 2)  // if no direction, nobody moves
                    {
                        msg = "He is standing";
                        p->stand();
                        break;
                    }
                    switch (action[1])
                    {
                        case 'u':
                            if (p->shoot(decodeDirection(action[1])))
                                msg = "Hit!";
                            else
                                msg = "Missed!";
                            break;
                        case 'd':
                            if (p->shoot(decodeDirection(action[1])))
                                msg = "Hit!";
                            else
                                msg = "Missed!";
                            break;
                        case 'l':
                            if (p->shoot(decodeDirection(action[1])))
                                msg = "Hit!";
                            else
                                msg = "Missed!";
                            break;
                        case 'r':
                            if (p->shoot(decodeDirection(action[1])))
                                msg = "Hit!";
                            else
                                msg = "Missed!";
                            break;
                        default:   // if bad direction, nobody moves
                            cout << '\a' << endl;  // beep
                            break;
                    }
                    break;
            }
        }
        m_arena->moveRobots();
    } while ( ! m_arena->player()->isDead()  &&  m_arena->robotCount() > 0);
    m_arena->display(msg);
}
