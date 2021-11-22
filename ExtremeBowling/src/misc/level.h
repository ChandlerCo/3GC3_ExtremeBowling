#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <vector>
#include "levelMap.h"
#include "../characters/boomba.h"
#include "../characters/pin.h"
#include "../characters/powerup.h"
#include "../characters/sweeper.h"


using namespace std;

class Level {
    //note if we have a map with a y dimension we can just adjust spawn at that location
    private:
        int startLocation[2]; // x,y coordinates
        int endLocation[3]; //x,y and radius
        vector <int[3]> checkpoints; 
        /*all map checkpoints including start - 
        checkpoints will get removed as they are reached and the first one 
        will be the current checkpoint
        */
        vector <PowerUp> powerUpSpawn; //might make different ones if there are different powerups
        vector <Pin> pinSpawn;
        vector <Boomba> boombaSpawn;
        vector <Sweeper> sweeperSpawn;
        LevelMap map; //needs to be implemented still

        int currentTime; //current time in ms
        int pins; //current pins collected
    
    public:
        Level(); //need to discuss implementation and loading

        bool checkLocation(int x, int y); 
        /*will return true if at end of level
         otherwise it will see if it's in the radius of any checkpoints
         will also run physics and adjust for collisions when appropriate
         then update latest checkpoint */
        
        //

        int getScore(); //calculates and returns score


};

#endif