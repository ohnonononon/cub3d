# cub3D
Creating a rayCaster with MLX

## Notes

### CODAM
CODAM MLX is allowed, must be downloaded and compiled with to work. It's documented, it's not that much of stuff.

### DEV LAWSSSSssssssssssssssss
- NO LEAKS
- Set error paths correctly

### development roadmap
breakdown by phases for testing and making sure everything works up to that point

Summary,
1.  Window environment
2.  Render hardcoded 2D map

#### 1
Window creation and implement behavior interaction, such as close, minimizing,
changing windows, segfaults, etc

Subject says:
``` Creating the window system, set interactions with hook such as close, etc. Subject says:
Pressing ESC must close the window and quit the program cleanly.
    Clicking on the red cross on the window’s frame must close the window and quit the program cleanly. ```

#### 2
- Rendering a hardcoded 2d representation of the map and its interaction and integration
with the window.
- Occupied spaces visibly different than spaces
- Scales properly to window size
>> Test with different arrays

#### 3
- Create a sensor that indicates the player position within the map.
- Create a representation for the player pov:
    -> Set starting position system as preparation for 4
- Set behavior when interacting through hooks: movement and camera rotation
- Set colision:
    -> If not, dealing with "what does the map look like when outside of valid map
>> Test the feeling: gotta feel it dude

#### 4 PARSER PHASE
- Only load .cub file extension
- Validate characters
- Detect invalid shapes (map configuration)
- Set starting position
- Reject open map
    -> Set a minimum viable map as requisite as well: 3x3 including the walls.
- Handle bad files without crashing
- Parse map texture configuration
- Parse map configuration:
    -> 1 for walls
    -> 0 for spaces
    -> N, S, E or W for starting point
    -> ' ' are accepted and allows to draw "nothing"

#### 5
- Load textures
- Map textures in map slices
- Handle different wall directions


