// Nigel Lipps
// Arena.cpp


///////////////////////////////////////////////////////////////////////////
//  Arena implementations
///////////////////////////////////////////////////////////////////////////
#include "Arena.h"
#include "globals.h"
#include "Player.h"
#include "Robot.h"
#include <string>
#include <iostream>
using namespace std;

Arena::Arena(int nRows, int nCols){
    if (nRows <= 0  ||  nCols <= 0  ||  nRows > MAXROWS  ||  nCols > MAXCOLS){
        cout << "***** Arena created with invalid size " << nRows << " by "<< nCols << "!" << endl;
        exit(1);
    }
    m_rows = nRows;
    m_cols = nCols;
    m_player = nullptr;
    m_nRobots = 0;
}
Arena::~Arena(){
    delete m_player;
    for (int i = 0; i <m_nRobots; i++)
        delete m_robots[i];
}
int Arena::rows() const{
    return m_rows;
}
int Arena::cols() const{
    return m_cols; 
}
Player* Arena::player() const{
    return m_player;
}
int Arena::robotCount() const{
    return m_nRobots;
}
int Arena::nRobotsAt(int r, int c) const{
    //Return the number of robots at row r, column c.
    int C = 0;
    for(int i = 0; i < m_nRobots; i++){
        if (m_robots[i] -> row() == r && m_robots[i] -> col() == c)
            C++;
    }
    return C;
}
void Arena::display(string msg) const{
    // Position (row,col) in the arena coordinate system is represented in
    // the array element grid[row-1][col-1]
    char grid[rows()][cols()];
    int r, c;
    // Fill the grid with dots
    for (r = 0; r < rows(); r++)
        for (c = 0; c < cols(); c++)
            grid[r][c] = '.';
    // Indicate each robot's position
    // TODO:  If one robot is at some grid point, set the char to 'R'.
    //        If it's 2 though 8, set it to '2' through '8'.
    //        For 9 or more, set it to '9'.
    for (r = 0; r < rows(); r++)
        for (c = 0; c < cols(); c++)
            switch(nRobotsAt(r+1,c+1)){
                   case 1:
                       grid[r][c] = 'R';
                       break;
                   case 2:
                       grid[r][c] = '2';
                       break;
                   case 3:
                       grid[r][c] = '3';
                       break;
                   case 4:
                       grid[r][c] = '4';
                       break;
                   case 5:
                       grid[r][c] = '5';
                       break;
                   case 6:
                       grid[r][c] = '6';
                       break;
                   case 7:
                       grid[r][c] = '7';
                       break;
                   case 8:
                       grid[r][c] = '8';
                       break;
                   case 0:
                       break;
                   default:
                       grid[r][c] = '9';
                       break;
                   }
    
    // Indicate player's position
    if (m_player != nullptr){
        // Set the char to '@', unless there's also a robot there,
        // in which case set it to '*'.
        char& gridChar = grid[m_player->row()-1][m_player->col()-1];
        if (gridChar == '.')gridChar = '@';
        else
            gridChar = '*';
    }
    // Draw the grid
    cout << endl << endl << endl;
    clearScreen();
    for (r = 0; r < rows(); r++){
        for (c = 0; c < cols();c++)
            cout << grid[r][c];
        cout << endl;
    }
    cout << endl;
    // Write message, robot, and player info
    cout << endl;
    if (msg != "")
        cout << msg << endl;
    cout << "There are " << robotCount() << " robots remaining." << endl;
    if (m_player == nullptr)
        cout << "There is no player." << endl;
    else{
        if (m_player->age() > 0)
            cout << "The player has lasted " << m_player->age() << " steps." << endl;
        if (m_player->isDead())
            cout << "The player is dead." << endl;
    }
}
//done
bool Arena::addRobot(int r, int c){
    // If MAXROBOTS have already been added, return false.  Otherwise,
    // dynamically allocate a new robot at coordinates (r,c).  Save the
    // pointer to the newly allocated robot and return true.
    if(m_nRobots<MAXROBOTS){
        //Dynamically allocate a new Robot and add it to the arena
        m_robots[m_nRobots] = new Robot(this, r, c);
        m_nRobots++;
        return true;
    }
    return false;
}
//done
bool Arena::addPlayer(int r, int c){
    // Don't add a player if one already exists
    if (m_player != nullptr)
        return false;
    // Dynamically allocate a new Player and add it to the arena
    m_player = new Player(this, r, c);
    return true;
    
}
void Arena::damageRobotAt(int r, int c){
    // Damage one robot at row r, column c if at least one is there.
    // If the robot does not survive the damage, destroy it.
    Robot * temp;
    if(nRobotsAt(r,c)>0)
        for(int i = 0; i < m_nRobots; i++)
            if(m_robots[i]->row() == r && m_robots[i]->col() == c){
                if(! m_robots[i]->takeDamageAndLive()){
                    temp = m_robots[i];
                    while(i < m_nRobots){
                        m_robots[i] = m_robots[i+1];
                        i++;
                    }
                    m_robots[m_nRobots] = nullptr;
                    m_nRobots--;
                    delete temp;
                }
                return;
            }
}
bool Arena::moveRobots(){
    for (int k = 0; k < m_nRobots; k++){
        //first move the robot
         m_robots[k]->move();
        //then check if the robot and player are at the same poition
        if((m_robots[k]->row() == m_player->row()) && (m_robots[k]->col() == m_player->col()))
           m_player->setDead();
    }
    // return true if the player is still alive, false otherwise
    return ! m_player->isDead();
}
