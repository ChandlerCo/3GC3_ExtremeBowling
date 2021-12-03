TODO

    Chandler-
        bounding boxes
        floor class
            csv
            
    Thomas-
        level class         - thomas
            start location
            end location
            enemy spawn points
            power spawn points
            floor map           - chandler
            checkpoints
            pin locations
            pins collected
            - load from file - chandler
            score calculation
                pin
                
        fix camera
        add fps toggle
        make obj faster
            may need to test
        learn some blender
        
    Sarvin-
        Lighting
        and helping joseph with core mechanics
        
    Joseph-
        do everything modularly
        pause mechanic
            pop up mechanic
        jump mechanic
            add upward velocity, use main
            
        ball:
            respawn - if y < __ respawn - checkpoint

        menu interface - put in a separate file
            Instructions
            -previous high score
            -level selector

        level selector
            -load level class into main, clear other level

        power up class
            add interactions, use main

To Do

    Sarvin:
        Lighting
        Shaders
        Materials
    
    Thomas
        Make some obj & mtl

        implement level class
                lives
                last checkpoint - for later
                power up status
                enemy spawner
                    adjust animation with start and end path
                delete physics objs
                level complete fuction
                    menu - save high score to json

        ball 
            jump stuff
            lives
            score

    Chandler
        previous high score
        saved to json along with user
        enemy spawn locations - add start+end path
        add power ups to json
        delete pointer to delete physics objs

    
    Joseph
        make second menu
        json parser
        level selector calls level constructor with file name - pathing will be done by constructor
        menu dissapears after clicking start level
    
    
    Implement power ups
        power up callback



    make power up classes
        chandler will do physics stuff
        thomas will do level related stuff



    Stuff for later:
    
        Advanced graphics
        alpha blending - ball
    
    OTHER IDEAS
        mini map
        camera zoom
