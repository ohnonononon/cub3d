# cub3D

*This project has been created as part of the 42 curriculum by nimatura, olreshet.*

## Description

cub3D is a 3D graphical representation project inspired by the classic game Wolfenstein 3D. The goal is to create a realistic 3D graphical representation of a maze from a first-person perspective using raycasting techniques. This project introduces fundamental concepts of computer graphics, including texture mapping, sprite rendering, and real-time user interaction.

The project implements a simple raycasting engine that renders a 3D view of a 2D map, featuring:
- Textured walls with different textures based on orientation (North, South, East, West)
- Floor and ceiling colors
- Smooth player movement and rotation
- Window management and event handling

## Instructions

### Prerequisites

**Linux (Ubuntu/Debian):**
```bash
sudo apt-get update
sudo apt-get install build-essential libglfw3-dev cmake
```

**macOS:**
```bash
brew install glfw cmake
```

### Compilation

Clone the repository and compile:
```bash
git clone <repository-url>
cd cub3d
make
```

This will:
1. Build the MLX42 graphics library
2. Compile the cub3D executable

### Usage

Run the program with a valid `.cub` map file:
```bash
./cub3D maps/simple.cub
```

### Controls

- `W` / `↑` - Move forward
- `S` / `↓` - Move backward
- `A` - Strafe left
- `D` - Strafe right
- `←` - Rotate camera left
- `→` - Rotate camera right
- `ESC` - Exit the game

### Map Format

Maps must be `.cub` files with the following elements:

**Texture paths:**
```
NO ./textures/north.png
SO ./textures/south.png
WE ./textures/west.png
EA ./textures/east.png
```

**Colors (RGB format):**
```
F 220,100,0    (Floor color)
C 225,30,0     (Ceiling color)
```

**Map layout:**
- `1` - Wall
- `0` - Empty space
- `N/S/E/W` - Player starting position and orientation

Example:
```
111111
1N0001
100101
100001
111111
```

### Memory Debugging

The project includes AddressSanitizer for memory leak detection:
```bash
make re
./cub3D maps/simple.cub
```

For detailed leak checking on Linux:
```bash
valgrind --leak-check=full --show-leak-kinds=all ./cub3D maps/simple.cub
```

### Cleaning

```bash
make clean      # Remove object files
make fclean     # Remove object files and executable
make re         # Rebuild everything
```

## Resources

### Raycasting & Graphics
- [Lode's Computer Graphics Tutorial - Raycasting](https://lodev.org/cgtutor/raycasting.html) - Comprehensive raycasting tutorial
- [Wolfenstein 3D's Ray Casting Engine](https://en.wikipedia.org/wiki/Wolfenstein_3D) - Historical context
- [Ray-Casting Tutorial For Game Development](https://permadi.com/1996/05/ray-casting-tutorial-table-of-contents/)

### MLX42 Library
- [MLX42 Documentation](https://github.com/codam-coding-college/MLX42) - Official MLX42 graphics library
- [MLX42 Learn Guide](https://harm-smits.github.io/42docs/libs/minilibx) - MLX basics

### Mathematics
- [Trigonometry in Game Development](https://www.mathsisfun.com/algebra/trig-interactive-unit-circle.html)
- [Vector Mathematics for 3D Graphics](https://www.khanacademy.org/math/linear-algebra)

### Project Planning & Debugging
- [Valgrind Documentation](https://valgrind.org/docs/manual/quick-start.html) - Memory debugging
- [GDB Tutorial](https://www.cs.cmu.edu/~gilpin/tutorial/) - Debugging with GDB

### AI Usage

AI tools (GitHub Copilot, ChatGPT) were used for the following tasks:

**Code Assistance:**
- Debugging compilation errors and linking issues
- Code refactoring and optimization suggestions
- Understanding MLX42 API and usage patterns

**Documentation:**
- Generating this README structure
- Writing explanatory comments for complex algorithms

**Problem Solving:**
- Debugging raycasting calculations
- Fixing texture mapping issues
- Memory leak identification and resolution

**NOT used for:**
- Core raycasting algorithm implementation
- Game logic and player movement
- Map parsing and validation logic

All code involving the fundamental raycasting mechanics, game logic, and map parsing was written manually to ensure understanding of the underlying concepts.

## Technical Details

### Architecture

The project is structured into several modules:
- **Parser** - Validates and loads `.cub` configuration files
- **Renderer** - Implements raycasting and texture rendering
- **Player** - Handles player movement and collision detection
- **Textures** - Manages texture loading and pixel manipulation
- **Utilities** - String manipulation, memory management, error handling

### Raycasting Algorithm

The engine uses Digital Differential Analysis (DDA) algorithm to cast rays from the player's position and determine wall intersections. For each vertical stripe on the screen:
1. Calculate ray direction based on player angle and camera plane
2. Step through the map grid until hitting a wall
3. Calculate wall height based on distance (with fish-eye correction)
4. Sample texture pixels and draw vertical line

### Performance

- Uses optimized MLX42 library for hardware-accelerated rendering
- Efficient texture sampling with direct pixel manipulation
- Smooth movement with delta time calculations

## Authors

- **nimatura** - Raycasting engine, renderer implementation
- **olreshet** - Parser, validation, testing, macOS adaptation

---

*Project completed as part of 42 School curriculum - February 2026*
