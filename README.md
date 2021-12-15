# CS 3GC3 - Project

Team 2

## Contributors (Group 1)

- Sarvin Azadis   (azadis2)
- Chandler Co     (coc)
- Thomas Hankins  (hankinst)
- Joseph Lee      (leej240)
      
## Features Implemented

- Lighting 
- Textures
- Alpha blending
- Animated characters
- Non-geometric primitives (menu)
- Advanced camera control
- Shaders

* OBJ file parsing and drawing
    - Draws faces and sets normals
    - Textures not yet drawn

* Camera
    - Complex camera which moves around ball based on mouse movement

* Character Class - ball.h/ball.cpp
    - Contains physics values(position, bounding box, etc), loaded obj, controls, active power-up

* A pin/powerup class:
    - animation/ movement
    - physics values(position, bounding box, etc)
    - loaded obj
    - textures
    - alpha blending

* Enemy classes - boomba, sweepers
    - physics values(position, bounding box, etc)
    - animation/movement
    - loaded obj

* Physics
    - physics values, position, velocity, acceleration etc.
    - bonuding boxes and collision detection

* Basic World
    - floor
    - moveable character
    - enemies spawned and moving
    - maps / levels
    

# Controls
| Command  | Description  |
|---|---|
| up arrow  | ball moves forward |
| down arrow  | ball moves backward  |
| left arrow  | ball moves left |
| right arrow  | ball moves right  |
| left-click  | ball jumps  |   
| space  | game pauses  |
| mouse is outside window | game pauses  |
| moving mouse | camera moves around ball|