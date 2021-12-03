//#include <iostream>
#include "button.h"
#include "menu.h"

Menu::Menu(int windowX, int windowY) 
{
    this->windowWidth = windowX;
    this->windowHeight = windowY;
}

void Menu::display() {}

// call this at beginning of display for each menu
void Menu::initMenu()
{
    // we will be switching to 2d projection here
    glMatrixMode(GL_PROJECTION);
    glPushMatrix(); // save projection matrix state
        glLoadIdentity(); // reset projection matrix
        gluOrtho2D(0, windowWidth, windowHeight, 0); // set 2d projection matrix
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix(); // save modelview matrix state
            glDisable(GL_CULL_FACE);
            //glClear(GL_DEPTH_BUFFER_BIT);
            glDisable(GL_DEPTH_TEST);
            glLoadIdentity(); // reset modelview matrix state
            glDisable(GL_LIGHTING);
            // draw menu background
            glPushMatrix();
                glColor3f(0.95, 0.95, 0.95);
                glBegin(GL_QUADS);
                    glVertex2f(windowWidth*0.15, windowHeight*0.15);
                    glVertex2f(windowWidth*0.85, windowHeight*0.15);
                    glVertex2f(windowWidth*0.85, windowHeight*0.85);
                    glVertex2f(windowWidth*0.15, windowHeight*0.85);
                glEnd();
            glPopMatrix();
}

// call this at end of display for each menu
void Menu::endMenu()
{
    // switch back to 3d projection
            glMatrixMode(GL_PROJECTION);
        glPopMatrix(); // retrieve projection matrix state
        glMatrixMode(GL_MODELVIEW);
    glPopMatrix(); // retrieve modelview matrix state
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glEnable(GL_LIGHTING);
}

// void Menu::display(int windowX, int windowY, MenuType type)
// {
//     // we will be switching to 2d projection here
//     glMatrixMode(GL_PROJECTION);
//     glPushMatrix(); // save projection matrix state
//         glLoadIdentity(); // reset projection matrix
//         gluOrtho2D(0, windowWidth, windowHeight, 0); // set 2d projection matrix
//         glMatrixMode(GL_MODELVIEW);
//         glPushMatrix(); // save modelview matrix state
//         glDisable(GL_CULL_FACE);
//         //glClear(GL_DEPTH_BUFFER_BIT);
//         glDisable(GL_DEPTH_TEST);
//             glLoadIdentity(); // reset modelview matrix state
//             glDisable(GL_LIGHTING);
//             // draw menu background
//             glPushMatrix();
//                 glColor3f(0.95, 0.95, 0.95);
//                 glBegin(GL_QUADS);
//                     glVertex2f(windowWidth*0.15, windowHeight*0.15);
//                     glVertex2f(windowWidth*0.85, windowHeight*0.15);
//                     glVertex2f(windowWidth*0.85, windowHeight*0.85);
//                     glVertex2f(windowWidth*0.15, windowHeight*0.85);
//                 glEnd();
//             glPopMatrix();
//             switch (type) {
//                 case MenuType::start:
//                     this->start();
//                     break;
//                 case MenuType::instructions:
//                     this->instructions();
//                     break;
//                 case MenuType::pause:
//                     this->pause();
//                     break;
//                 default:
//                     break;
//             }
//             // switch back to 3d projection
//             glMatrixMode(GL_PROJECTION);
//         glPopMatrix(); // retrieve projection matrix state
//         glMatrixMode(GL_MODELVIEW);
//     glPopMatrix(); // retrieve modelview matrix state
//     glEnable(GL_DEPTH_TEST);
//     glEnable(GL_CULL_FACE);
//     glCullFace(GL_BACK);
//     glEnable(GL_LIGHTING);
// }

// void Menu::start()
// {
//     glPushMatrix();

//         glColor3f(1.0, 0.0, 0.0);
//         void* font = GLUT_BITMAP_9_BY_15;

//         // Game title
//         string title = "WELCOME TO EXTREME BOWLING";
//         centerText(title, font, windowHeight*0.20);

//         // Underline the title
//         string underlineTitle = "__________________________";
//         centerText(underlineTitle, font, windowHeight*0.205);

//         // Buttons

//         // temp level starter
//         Button level1 (windowWidth*0.40, windowWidth*0.60, windowHeight*0.34, windowHeight*0.30, "Level 1");
//         level1.display();

//         Button instructions (windowWidth*0.40, windowWidth*0.60, windowHeight*0.77, windowHeight*0.73, "Instructions");
//         instructions.display();

//         Button quit (windowWidth*0.45, windowWidth*0.55, windowHeight*0.83, windowHeight*0.79, "Quit");
//         quit.display();

//     glPopMatrix();
// }

// void Menu::instructions()
// {
//     glPushMatrix();

//         glColor3f(1.0, 0.0, 0.0);
//         void* font = GLUT_BITMAP_9_BY_15;

//         // Instructions 
//         string title = "Instructions";
//         centerText(title, font, windowHeight*0.20);

//         // Underline the title
//         string underlineTitle = "____________";
//         centerText(underlineTitle, font, windowHeight*0.205);

//         Button back (windowWidth*0.45, windowWidth*0.55, windowHeight*0.83, windowHeight*0.79, "Back");
//         back.display();

//     glPopMatrix();
// }

// void Menu::pause()
// {
//     // draw text onto background
//     glPushMatrix();

//         glColor3f(1.0, 0.0, 0.0);
//         void* font = GLUT_BITMAP_9_BY_15;

//         // Game title
//         string title = "EXTREME BOWLING";
//         centerText(title, font, windowHeight*0.20);

//         // Underline the title
//         string underlineTitle = "_______________";
//         centerText(underlineTitle, font, windowHeight*0.205);

//         // Unpause game text 
//         string unpause = "Press space to unpause game.";
//         centerText(unpause, font, windowHeight*0.80);
        
//     glPopMatrix();
// }

// Will render and center text
void Menu::centerText(string text, void* font, float y)
{
    float textWidth = 0;
    for (int i = 0; i < text.size(); i++) {
        textWidth += glutBitmapWidth(font, text[i]);
    }
    glRasterPos2f(windowWidth / 2.0 - textWidth / 2.0, y);
    for (char& c : text) {
        glutBitmapCharacter(font, c);
    }
}