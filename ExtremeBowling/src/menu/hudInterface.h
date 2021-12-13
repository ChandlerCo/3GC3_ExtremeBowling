#ifndef HUDINTERFACE
#define HUDINTERFACE

#include "menu.h"
#include "../misc/graphics.h"

struct Image {
    int mWidth;
    int mHeight;
    GLubyte * mImage;

    void load(char * filename) {
        mImage = LoadPPM(filename, &mWidth, &mHeight);
        }

    void draw(unsigned int x, unsigned int y) {
        glRasterPos2i(x + mWidth, y);
        /**
         * If you are on a retina display then you should replace the values
         * from -1, 1 to -2, 2 to ensure they appear at full size!
         *
         * The PPM parser packs the image mirrored horizontally. Thus we use
         * glPixelZoom to "flip" the image back the correct way by scaling the
         * x axis by -1. This is the same concept as mirroring an object with
         * glScalef(-1, 1, 1).
         *
         * Aside: Using the parsing code from last year. I don't think the code
         * is very good. There is definitely a way to parse PPM bitmaps without
         * needing to flip the image like this.
         */
        glPixelZoom(-1, 1);

        glDrawPixels(mWidth, mHeight, GL_RGB, GL_UNSIGNED_BYTE, mImage);
        /**
         * YOUR CODE HERE
         *  Note: this should just be drawing the pixels with the info on this struct!
         */
    }

    void texture() {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, mWidth, mHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, mImage);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); 
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
        
        /**
         * YOUR CODE HERE FOR BONUS
         * 
         * Add the glTexImage2D and glTexParameterf calls.
         * I strongly recommend reading the documentation to get a loose sense
         * of what these values mean.
         */
    }
};

class HudInterface : public Menu {
    public:
        HudInterface(int windowX, int windowY);
        void display(int lives, int currentTime);
    private:
        Graphics graphics;
        // Image heart;
};


#endif