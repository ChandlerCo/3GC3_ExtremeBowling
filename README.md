# CS 3GC3 - Project

Team 2

## Contributors (Group 1)

- Sarvin Azadis   (azadis2)
- Chandler Co     (coc)
- Thomas Hankins  (hankinst)
- Joseph Lee      (leej240)
      
## Features Implemented

* Lighting 
<!-- Not sure what to include here -->

* Textures and materials
    - Added for all 3D objects, including character class, boombas, sweepers, pins, powerups, and floor

* Alpha blending
    - Implemented for objects during character class "ghost" mode 

* Animated characters
    - Sweepers and boombas have default movements in map
    - Power ups have a "floating" animation

* Non-geometric primitives 
    - Start menu, instructions menu, pause menu, end menu
    - HUD interface

* Advanced camera control
    - Complex camera which moves around ball based on mouse movement

* Shaders
<!-- do we have these? -->

* OBJ file parsing and drawing
    - Done for all 3D objects

* Character class - ball.h/ball.cpp
    - Contains physics values (position, bounding box, etc), loaded obj, controls, active power-up
    - Keeps track of last checkpoint

* Pin and power up classes:
    - Have physics values (position, bounding box, etc)
    - Disappear after collision with character class

<!-- * A pin/powerup class:
    - animation/ movement
    - physics values(position, bounding box, etc)
    - loaded obj
    - textures
    - alpha blending -->

* Enemy classes - boombas, sweepers
    - Have physics values (position, bounding box, etc)

* Physics
    - Values including position, velocity, acceleration etc.
    - Bounding boxes and collision detection

* Basic World
    - Floor
    - Moveable character class
    - Enemies spawned and have animation
    - 3 different maps/ levels

* Terrain generation
<!--  -->
    

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