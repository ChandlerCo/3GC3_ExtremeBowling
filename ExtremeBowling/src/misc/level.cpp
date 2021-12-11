#include "level.h"
#include <algorithm>


#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif

#include <iostream>

using namespace std;

Level::Level(string filename){

    levelFilename = filename;
    ifstream f(levelFilename);

    if (f.is_open())
    {
        json level_data;
        f >> level_data;
        this->map = Floor::fromJson(level_data.find("Floor").value());
        map.getPointers(this->worldObjects);
        this->floorLength = worldObjects.size();

    
        json enemies_data = level_data.find("Enemies").value();

        vector<json> boombas_data = enemies_data.find("Boombas").value();
        this->boombas = Boomba::fromJson(boombas_data, this->map.getTileSize());
        for (Boomba *i : boombas)
        {
            this->worldObjects.push_back(i->getPhysicsPointer());
        }

        vector<json> sweepers_data = enemies_data.find("Sweepers").value();
        this->sweepers = Sweeper::fromJson(sweepers_data, this->map.getTileSize());
        for(Sweeper *i: sweepers){
            this->worldObjects.push_back(i->getPhysicsPointer());
        }

        vector<json> pins_data = level_data.find("Pins").value();
        this->pins = Pin::fromJson(pins_data, this->map.getTileSize());
        for(Pin *i: pins){
            this->worldObjects.push_back(i->getPhysicsPointer());
        }

        vector<json> powerups_data = level_data.find("PowerUps").value();
        this->powerUps = PowerUp::fromJson(powerups_data, this->map.getTileSize());
        for (PowerUp *i : powerUps)
        {
            this->worldObjects.push_back(i->getPhysicsPointer());
        }

        this->ball = Ball(this->map.spawnX(),this->map.spawnY(), this->map.spawnZ(), 5);
        this->ball.init();

        highScore = level_data.find("HighScore").value();
    }
    

    this->currentTime = 0;

    this->ended = false;
    this->score = 0;
    this->powerUpStart = 0;
}

void Level::runLevel(int timePassed){
    this->ball.runPhysics(timePassed, worldObjects); //time passed will be the same argument as is previously called, need chandler to advise

    this->currentTime += timePassed;

    
    for(Sweeper *i : sweepers){
        i->animate(timePassed);
    }

    for(Boomba *i : boombas){
        i->animate(timePassed);
    }

    vector<vector<PowerUp*>::iterator> deletePowerUps;
    for (vector<PowerUp*>::iterator it = powerUps.begin(); it != powerUps.end(); it++)
    {
        if((*it)->checkCollision() == true){
            this->powerUpStart = currentTime;
            this->ball.activatePowerUp(*(*it));

            //WARNING --- DON'T TRY TO UNDERSTAND THIS
            int localID = (*it)->getPhysicsPointer()->getLocalId();
            int objectID = (*it)->getPhysicsPointer()->getId();
            
            this->worldObjects.erase(std::remove_if(
            this->worldObjects.begin() + this->floorLength, this->worldObjects.end(), //start at number of tiles
            [localID, objectID](PhysicsObject3D * &j){
                return (j->getLocalId() == localID && j->getId() == objectID);
            }), this->worldObjects.end());

            // delete object
            delete *it;

            // remove from powerUps
            deletePowerUps.push_back(it);
        }
    }
    for (vector<PowerUp*>::iterator it : deletePowerUps)
    {
        powerUps.erase(it);
    }

    vector<vector<Pin*>::iterator> deletePins;
    for (vector<Pin*>::iterator it = pins.begin(); it != pins.end(); it++)
    {
        if((*it)->checkCollision() == true){
            this->score += 1;

            //WARNING --- DON'T TRY TO UNDERSTAND THIS
            int localID = (*it)->getPhysicsPointer()->getLocalId();
            int objectID = (*it)->getPhysicsPointer()->getId();
            
            this->worldObjects.erase(std::remove_if(
            this->worldObjects.begin() + this->floorLength, this->worldObjects.end(), //start at number of tiles
            [localID, objectID](PhysicsObject3D * &j){
                return (j->getLocalId() == localID && j->getId() == objectID);
            }), this->worldObjects.end());

            // delete object
            delete *it;

            // remove from powerUps
            deletePins.push_back(it);
        }
    }
    for (vector<Pin*>::iterator it : deletePins)
    {
        pins.erase(it);
    }
    /*
    for(PowerUp *i : powerUps){
        if(i->checkCollision() == true){
            this->powerUpStart = currentTime;
            this->ball.activatePowerUp(i);

            // erase from worldObjects
            //WARNING --- DON'T TRY TO UNDERSTAND THIS
            int localID = i->getPhysicsPointer()->getLocalId();
            int objectID = i->getPhysicsPointer()->getId();
            
            this->worldObjects.erase(std::remove_if(
            this->worldObjects.begin() + this->floorLength, this->worldObjects.end(), //start at number of tiles
            [localID, objectID](PhysicsObject3D * &j){
                return (j->getLocalId() == localID && j->getId() == objectID);
            }), this->worldObjects.end());

            
        }
    }
    //cout << "Done checking power ups\n";
    for(Pin *i : pins){
        if(i->checkCollision() == true){
            this->score += 1;

            //WARNING --- DON'T TRY TO UNDERSTAND THIS
            int localID = i->getPhysicsPointer()->getLocalId();
            int objectID = i->getPhysicsPointer()->getId();

            this->worldObjects.erase(std::remove_if(
            this->worldObjects.begin() + this->floorLength, this->worldObjects.end(), //start at number of tiles
            [localID, objectID](PhysicsObject3D * &j){
                return (j->getLocalId() == localID && j->getId() == objectID);
            }), this->worldObjects.end());
        }
    }
    //cout << "Done checking pins\n";
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
    */
    //cout << "Done erasing stuff\n";
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
    //cout << "Exit runLevel\n";
}

void Level::displayAssets(){

    float lightPos[] ={ 50, 700, 5, 1 };
    //float lightPos2[] = {0,0,0,1};
    float lightAmb[] = { 1, 1, 1, 1 };
    float lightDif[] = { 0.8, 0.8, 0.8, 1 };
    //float lightDif2[] = { 1, 1, 1, 1 };
    float lightSpc[] = { 0.35, 0.35, 0.35, 1 };
    
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmb);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDif);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpc);
    //Graphics::initTextures();

    for(Boomba* i : boombas){
        i->displayAsset();//add materials
    }

    for(Sweeper* i : sweepers){
        i->displayAsset();
    }
    for(Pin* i : pins){
        //glBindTexture(GL_TEXTURE_2D, Graphics::textures[1]);
        i->displayAsset();
    }
    for(PowerUp* i : powerUps){
        i->displayAsset();
    }
    //glBindTexture(GL_TEXTURE_2D, Graphics::textures[0]);
    if (ball.blend) 
    {
        glEnable(GL_BLEND);					// Turn Blending On
		glDisable(GL_DEPTH_TEST);			// Turn Depth Testing Off
        this->ball.displayAsset();
    } else 
    {
        glDisable(GL_BLEND);					// Turn Blending Off
		glEnable(GL_DEPTH_TEST);				// Turn Depth Testing On
        this->ball.displayAsset();
    }
    
    
    //glBindTexture(GL_TEXTURE_2D, Graphics::textures[2]);
    this->map.displayFloor();

}



int Level::getScore(){
    return score*100 - currentTime/1000 + 1000;
}

bool Level::endLevel(){
    int lives = ball.getLives();

    for(Boomba* i : boombas)
        delete i;
    for(Sweeper* i : sweepers)
        delete i;
    for(PowerUp* i : powerUps)
        delete i;
    for(Pin* i : pins)
        delete i;

    this->boombas.clear();
    this->sweepers.clear();
    this->powerUps.clear();
    this->pins.clear();
    this->map.clearTiles();   

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

//gameplay methods
float Level::getBallX(){
    return this->ball.getX();
}

float Level::getBallY(){
    return this->ball.getY();
}

float Level::getBallZ(){
    return this->ball.getZ();
}

void Level::ballJump(){
    this->ball.jump();
}

void Level::ballMove(Vec3D direction){
    int mult = 10;

    //Vec3D vel = direction.multiply(10);
    Vec3D acc = direction.multiply(mult);
    
    //ball.addVelocity(vel.x, vel.y, vel.z);
    ball.accelerate(acc.x, acc.y, acc.z);
}

