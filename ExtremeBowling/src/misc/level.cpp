#include "level.h"
#include <algorithm>

Level::Level(string filename){
    levelFilename = filename;
    ifstream f(levelFilename);

    if (f)
    {
        json level_data;
        f >> level_data;
        this->map = Floor::fromJson(level_data.find("Floor").value());
        map.getPointers(this->worldObjects);
        this->floorLength = worldObjects.size();
    
        json enemies_data = level_data.find("Enemies").value();

        vector<json> boombas_data = enemies_data.find("Boombas").value();
        this->boombas = Boomba::fromJson(boombas_data, this->map.getTileSize());
        for (Boomba &i : boombas)
        {
            this->worldObjects.push_back(i.getPhysicsPointer());
        }

        vector<json> sweepers_data = enemies_data.find("Sweepers").value();
        this->sweepers = Sweeper::fromJson(sweepers_data, this->map.getTileSize());
        for(Sweeper &i: sweepers){
            this->worldObjects.push_back(i.getPhysicsPointer());
        }

        vector<json> pins_data = level_data.find("Pins").value();
        this->pins = Pin::fromJson(pins_data, this->map.getTileSize());
        for(Pin &i: pins){
            this->worldObjects.push_back(i.getPhysicsPointer());
        }
        for (Pin &i : pins)
        {
            this->worldObjects.push_back(i.getPhysicsPointer());
        for(PowerUp &i: powerUps){
            this->worldObjects.push_back(i.getPhysicsPointer());
        }        }

        vector<json> powerups_data = level_data.find("PowerUps").value();
        this->powerUps = PowerUp::fromJson(powerups_data, this->map.getTileSize());
        for (PowerUp &i : powerUps)
        {
            this->worldObjects.push_back(i.getPhysicsPointer());
        }


        this->ball = Ball(this->map.spawnX(),this->map.spawnY(), this->map.spawnZ(), 5);


        highScore = level_data.find("HighScore").value();
    }
    

    this->currentTime = 0;
}

void Level::runLevel(int timePassed){
    this->ball.runPhysics(timePassed, worldObjects); //time passed will be the same argument as is previously called, need chandler to advise
    this->currentTime += timePassed;


    
    for(PowerUp &i : powerUps){
        if(i.checkCollision() == true){
            this->powerUpStart = currentTime;
            this->ball.activatePowerUp(i);

            //WARNING --- DON'T TRY TO UNDERSTAND THIS
            int localID = i.getPhysicsPointer()->getLocalId();
            int objectID = i.getPhysicsPointer()->getId();
            
            this->worldObjects.erase(std::remove_if(
            this->worldObjects.begin() + this->floorLength, this->worldObjects.end(), //start at number of tiles
            [localID, objectID](PhysicsObject3D * &j){
                return (j->getLocalId() == localID && j->getId() == objectID);
            }), this->worldObjects.end());

        }
    }

    for(Pin &i : pins){
        if(i.checkCollision() == true){
            this->score += 1;


            //WARNING --- DON'T TRY TO UNDERSTAND THIS
            int localID = i.getPhysicsPointer()->getLocalId();
            int objectID = i.getPhysicsPointer()->getId();

            this->worldObjects.erase(std::remove_if(
            this->worldObjects.begin() + this->floorLength, this->worldObjects.end(), //start at number of tiles
            [localID, objectID](PhysicsObject3D * &j){
                return (j->getLocalId() == localID && j->getId() == objectID);
            }), this->worldObjects.end());
        }
    }

    //checking and clearing collisions
    powerUps.erase(std::remove_if(
        powerUps.begin(), powerUps.end(), 
        [](PowerUp &i){
            return i.checkCollision();
        }), powerUps.end());

    pins.erase(std::remove_if(
        pins.begin(), pins.end(), 
        [](Pin &i){
            return i.checkCollision();
        }), pins.end());

    //clearing powerups
    if(currentTime - powerUpStart > 10000){
        ball.clearPowerUp();
    }

    //check ball position then respawns
    if(this->ball.getY() < -20){ // can adjust based on preferences
        if(!ball.respawn()){
            this->ended = true;
        }

    }
}

int Level::getScore(){
    return score*100 - currentTime/1000 + 1000;
}

bool Level::endLevel(){
    int lives = ball.getLives();
    this->boombas.clear();
    this->pins.clear();
    this->map.clearTiles();   
    this->powerUps.clear();

    if(this->getScore() > this->highScore){
        this->saveHighScore();
    }

    if(lives == 0){
        return false;
    } else {
        return true;
    }
    
    
}

void Level::saveHighScore()
{
    // read JSON file
    std::ifstream i(levelFilename);
    json j;
    i >> j;

    j["HighScore"] = getScore();
    // write prettified JSON to another file
    std::ofstream o(levelFilename);
    o << std::setw(4) << j << std::endl;
}