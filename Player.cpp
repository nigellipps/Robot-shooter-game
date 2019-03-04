// Nigel Lipps
//  Player.cpp


///////////////////////////////////////////////////////////////////////////
//  Player implementations
///////////////////////////////////////////////////////////////////////////

#include "Player.h"
#include "globals.h"
#include "Arena.h"
#include <stdlib.h>
#include <string>
#include <iostream>
using namespace std;

Player::Player(Arena* ap, int r, int c){
    if (ap == nullptr){
        cout << "***** The player must be in some Arena!" << endl;
        exit(1);
        
    }
    if (r < 1  ||  r > ap->rows()  ||  c < 1  ||  c > ap->cols()){
        cout << "**** Player created with invalid coordinates (" << r<< "," << c << ")!" << endl;
        exit(1);
    }
    m_arena = ap;
    m_row = r;
    m_col = c;
    m_age = 0;
    m_dead = false;
}
int Player::row() const{
    return m_row;
}
int Player::col() const{
    return m_col;
}
int Player::age() const{
    return m_age;
}
string Player::takeComputerChosenTurn(){
    //   If moving in some direction would put me in less immediate danger
    //     than standing, then move in that direction.
    //   else shoot in the direction of the nearest robot I can hit.
    // A more aggressive strategy is possible, where you hunt down robots.
    //Top left corner
    if (m_row == 1 && m_col == 1){
        if (m_arena->nRobotsAt(m_row+1,m_col) > 0 && m_arena->nRobotsAt(m_row,m_col+1) > 0){
            return my_shoot();
        }
        else if (m_arena->nRobotsAt(m_row+1,m_col) > 0){
            move(RIGHT);
            return "Moved.";
        }
        else if (m_arena->nRobotsAt(m_row,m_col+1) > 0){
            move(DOWN);
            return "Moved.";
        }
        else{
            return my_shoot();
        }
    }
    //Top right corner
    if (m_row == 1 && m_col == m_arena->cols()){
        if (m_arena->nRobotsAt(m_row,m_col-1) > 0 && m_arena->nRobotsAt(m_row+1,m_col) > 0){
            return my_shoot();
        }
        else if (m_arena->nRobotsAt(m_row,m_col-1) > 0){
            move(DOWN);
            return "Moved.";
        }
        else if (m_arena->nRobotsAt(m_row+1,m_col) > 0){
            move(LEFT);
            return "Moved.";
        }
        else{
            return my_shoot();
        }
    }
    //Bottom right corner
    if (m_row == m_arena->rows() && m_col == m_arena->cols()){
        if (m_arena->nRobotsAt(m_row-1,m_col) > 0 && m_arena->nRobotsAt(m_row,m_col-1) > 0 ){
            return my_shoot();
        }
        else if (m_arena->nRobotsAt(m_row-1,m_col) > 0){
            move(LEFT);
            return "Moved.";
        }
        else if (m_arena->nRobotsAt(m_row,m_col-1) > 0){
            move(UP);
            return "Moved.";
        }
        else{
            return my_shoot();
        }
    }
    //Bottom left corner
    if (m_row == m_arena->rows() && m_col == 1){
        if (m_arena->nRobotsAt(m_row,m_col+1) > 0 && m_arena->nRobotsAt(m_row-1,m_col) > 0){
            return my_shoot();
        }
        else if (m_arena->nRobotsAt(m_row,m_col+1) > 0){
            move(UP);
            return "Moved.";
        }
        else if (m_arena->nRobotsAt(m_row-1,m_col) > 0){
            move(RIGHT);
            return "Moved.";
        }
        else{
            return my_shoot();
        }
    }
    //check the top of the map
    if (m_row == 1){
        if (m_arena->nRobotsAt(m_row,m_col+1) > 0 && m_arena->nRobotsAt(m_row,m_col-1) > 0){
            move(DOWN);
            return "Moved.";
        }
        if (m_arena->nRobotsAt(m_row+1,m_col) > 0 ){
            move(LEFT);
            return "Moved.";
        }
    }
    //check the left of the map
    if (m_col == 1){
        if (m_arena->nRobotsAt(m_row+1,m_col) > 0 && m_arena->nRobotsAt(m_row-1,m_col) > 0){
            move(RIGHT);
            return "Moved.";
        }
        if (m_arena->nRobotsAt(m_row, m_col+1 > 0)){
            move(UP);
            return "Moved.";
        }
    }
    //check the bottom of the map
    if (m_row == MAXROWS){
        if (m_arena->nRobotsAt(m_row,m_col+1) > 0 && m_arena->nRobotsAt(m_row,m_col-1) > 0){
            move(UP);
            return "Moved.";
        }
        if (m_arena->nRobotsAt(m_row-1, m_col > 0)){
            move(RIGHT);
            return "Moved.";
        }
    }
    //check the right of the map
    if (m_row == MAXCOLS){
        if (m_arena->nRobotsAt(m_row+1,m_col) > 0 && m_arena->nRobotsAt(m_row-1,m_col) > 0){
            move(LEFT);
            return "Moved.";
        }
        if (m_arena->nRobotsAt(m_row, m_col-1 > 0)){
            move(UP);
            return "Moved.";
        }
    }
    //check if he is completly surrounded or completly free, then shoot
    if (m_arena->nRobotsAt(m_row-1,m_col)==0 && m_arena->nRobotsAt(m_row,m_col-1)==0
        && m_arena->nRobotsAt(m_row+1,m_col)==0 && m_arena->nRobotsAt(m_row,m_col+1)==0){
        return my_shoot();
    }
    //otherwise check what directions are free
    else if (m_arena->nRobotsAt(m_row-1,m_col)==0){
        move(UP);
        return "Moved.";
    }
    else if (m_arena->nRobotsAt(m_row,m_col-1)==0){
        move(LEFT);
        return "Moved.";
    }
    else if (m_arena->nRobotsAt(m_row+1,m_col)==0){
        move(DOWN);
        return "Moved.";
    }
    else if (m_arena->nRobotsAt(m_row,m_col+1)==0){
        move(RIGHT);
        return "Moved.";
    }
    else
        return my_shoot();
}
string Player::my_shoot(){
    for(int i=1; i<=MAXSHOTLEN; i++){
        //check all the directions and shoot in that direction
        if (m_arena->nRobotsAt(m_row-i,m_col)>0){
            if (shoot(UP))
                return "Shot and hit!";
            else
                return "Shot and missed!";
        }
        else if (m_arena->nRobotsAt(m_row,m_col-i)>0){
            if (shoot(LEFT))
                return "Shot and hit!";
            else
                return "Shot and missed!";
        }
        else if (m_arena->nRobotsAt(m_row+i,m_col)>0){
            if (shoot(DOWN))
                return "Shot and hit!";
            else
                return "Shot and missed!";
        }
        else if (m_arena->nRobotsAt(m_row,m_col+i)>0){
            if (shoot(RIGHT))
                return "Shot and hit!";
            else
                return "Shot and missed!";
        }
    }
    stand();
    return "Stood.";
}
void Player::stand(){
    m_age++;
}
void Player::move(int dir){
    m_age++;
    switch (dir){
        case UP:
            if(m_row>1)
                m_row--;
            break;
        case DOWN:
            if(m_row<m_arena->rows())
                m_row++;
            break;
        case LEFT:
            if(m_col>1)
                m_col--;
            break;
        case RIGHT:
            if(m_col<m_arena->cols())
                m_col++;
            break;
    }
}
bool Player::shoot(int dir){                    //////////////////////
    m_age++;
    if (rand() % 3 == 0)  // miss with 1/3 probability
        return false;
    switch (dir) {  //check for robots from closest to farthest
        case UP:
            for(int i=1; i<=MAXSHOTLEN; i++){
                if (m_arena->nRobotsAt(row()-i,col())>0){
                    m_arena->damageRobotAt(row()-i,col());
                    return true;
                }
            }
            return false;
        case DOWN:
            for(int i=1; i<=MAXSHOTLEN; i++){
                if (m_arena->nRobotsAt(row()+i,col())>0){
                    m_arena->damageRobotAt(row()+i,col());
                    return true;
                }
            }
            return false;
        case LEFT:
            for(int i=1; i<=MAXSHOTLEN; i++){
                if (m_arena->nRobotsAt(row(),col()-i)>0){
                    m_arena->damageRobotAt(row(),col()-i);
                    return true;
                }
            }
            return false;
        case RIGHT:
            for(int i=1; i<=MAXSHOTLEN; i++){
                if (m_arena->nRobotsAt(row(),col()+i)>0){
                    m_arena->damageRobotAt(row(),col()+i);
                    return true;
                }
            } 
            return false;
        default:
            return false;
    }
}
bool Player::isDead() const{
    return m_dead;
}
void Player::setDead(){
    m_dead = true;
}
