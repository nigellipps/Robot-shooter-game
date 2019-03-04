// Nigel Lipps
//  Robots.cpp


///////////////////////////////////////////////////////////////////////////
//  Robot implementation
///////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <stdlib.h>
#include "Robot.h"
#include "Arena.h"
#include "globals.h"

using namespace std;

Robot::Robot(Arena* ap, int r, int c){
    if (ap == nullptr){
        cout << "***** A robot must be in some Arena!" << endl;
        exit(1);
        
    }
    if (r < 1  ||  r > ap->rows()  ||  c < 1  ||  c > ap->cols()){
        cout << "***** Robot created with invalid coordinates (" << r << ","<< c << ")!" << endl;
        exit(1);
    }
    m_arena = ap;
    m_row = r;
    m_col = c;
    hit = false;
}
int Robot::row() const{
    return m_row;
    
}
int Robot::col() const{
    return m_col;
}
void Robot::move(){
    // Attempt to move in a random direction; if we can't move, don't move
    //check if the robot is alive
        switch (rand() % 4){
            case UP:
                if(row()>1)
                    m_row--;
                break;
            case DOWN:
                if(row()<m_arena->rows())
                    m_row++;
                break;
            case LEFT:
                if(col()>1)
                    m_col--;
            break;
            case RIGHT:
                if(col()<m_arena->cols())
                    m_col++;
            break;
    }
}
bool Robot::takeDamageAndLive(){
    //call arena player and if equal row and col then hit
    if(hit == false) {
        hit = true;
        return true;
    }
    return false;
}
            
            
            
            
            
