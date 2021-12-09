#ifndef LEVEL_H
#define LEVEL_H

#include <vector>

#include "../characters/boomba.h"
#include "../characters/pin.h"
#include "../characters/powerup.h"
#include "../characters/sweeper.h"
#include "../characters/ball.h"
#include "graphics.h"
#include "floor.h"


using namespace std;

class Level {
    //note if we have a map with a y dimension we can just adjust spawn at that location
    private:
        int startLocation[2]; // x,y coordinates
        int endLocation[3]; //x,y and radius
        int score;
        int currentTime; //current time in ms

        vector <PowerUp*> powerUps;
        vector <Pin*> pins;
        vector <Boomba*> boombas;
        vector <Sweeper*> sweepers;

        Ball ball;
        Floor map; //needs to be implemented still

        int powerUpStart;

        string levelFilename;
        int highScore;
        int floorLength;

        vector<PhysicsObject3D *> worldObjects;

        void saveHighScore(); // called by endLevel() 
    public:

        bool ended;

        Level(string filename); 
        /*
            create a new ball object
            load map - call constructor
                pass json data through


            init enemies and powerups and pins

        */
        void runLevel(int timePassed);
            //run physics
            //update time
            //check power ups
            //check collisions/delete where appropriate
            //clear overdue powerups
            

        void displayAssets();

        bool endLevel(); //return true if good ending, return false if bad ending

        /*
            called if ball.finished() = true;
            check/set high score
            delete all objects/vectors
            call main menu
            delete map
            maybe delete level itself instead

        */

        int getScore(); //calculates and returns score -- put in the corner of the level

        int getHighScore(); //get high score in json

        float getBallX();
        float getBallY();
        float getBallZ();
        void ballJump();
        void ballMove(Vec3D direction);
};

#endif

/*
    put in timer func, run end screen for 10 seconds, go back to start menu
    or press smth to go back to start 
    
    if level.ended = true
        currentscore = level.getScore
        highscore = level.getHighScore

        if(endLevel()){

            Your Score is currentScore
            if currentScore > highScore
                congrats new high score
        } else {
            game over ...
        }
        
        delete currentLevel


    global variable for menu function called currentLevel
    currentLevel = Level("map1.json")


*/