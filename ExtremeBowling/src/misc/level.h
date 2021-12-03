#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <vector>
#include "levelMap.h"
#include "../characters/boomba.h"
#include "../characters/pin.h"
#include "../characters/powerup.h"
#include "../characters/sweeper.h"
#include "../characters/ball.h"


using namespace std;

class Level {
    //note if we have a map with a y dimension we can just adjust spawn at that location
    private:
        int startLocation[2]; // x,y coordinates
        int endLocation[3]; //x,y and radius

        int score;
        int currentTime; //current time in ms

        vector <PowerUp> powerUpSpawn; //might make different ones if there are different powerups
        vector <Pin> pinSpawn;
        vector <Boomba> boombaSpawn;
        vector <Sweeper> sweeperSpawn;

        Ball ball;
        LevelMap map; //needs to be implemented still

        int powerUpStart;

        
        void powerUpDelete();
            //if currentTime - powerUpStart > 10
            //this->ball.deletePowerUp();
        void pinDelete();
            //same as above for pins
        
        void checkBall();
            //if ball y < -10
            //ball.respawn();
        void deleteCollisions();
            //for the power vectors, pin vector if collided = true, delete
            //if power up check collisions = true
            //powerup start = currentTime
        

    public:
        Level(); 
        /*
            create a new ball object
            load map - call constructor
                pass json data through


            init enemies and powerups and pins

        */
        void runLevel();
            //run physics
            //update time
            //check collisions
            //powerupdelete called
            

        void endLevel();

        /*
            called if ball.finished() = true;
            check/set high score
            delete all objects/vectors
            call main menu
            delete map
            maybe delete level itself instead

        */

        int getScore(); //calculates and returns score -- put in the corner of the level


};

#endif