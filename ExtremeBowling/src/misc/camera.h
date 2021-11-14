#ifndef CAMERA_H
#define CAMERA_H

class Camera {
    private:
        float sensitivity;
        float distance;
        float centre[3];
        float position[3];
        float theta;
        float phi;
        void updatePosition();

    public:
        Camera(float startDistance);
        void orbitVertical(int amount); 
        void orbitHorizontal(int amount);
        void changeDistance(bool direction);
        void translate(float x, float y, float z); //input translation distance
        void changePosition(float x, float y, float z);

        float getX();
        float getY();
        float getZ();
};

#endif