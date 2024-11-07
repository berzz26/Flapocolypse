# Flapocalypse

A 2D game (Flappy Bird clone) in C using SDL2.

## Quick Start (Play the Game)

1. Download the latest release from the [Releases](https://github.com/berzz26/SDL_C/releases/V-1.0) page
2. Extract the ZIP file
3. Run `build/main.exe`

## Building from Source(run/view the code in your local system)

### Method 1: Using VS Code (Recommended)
1. Clone the repository
2. Open the project in VS Code
3. Press Ctrl+Shift+B to build
4. The executable will be created in the src folder

### Method 2: Manual Build with GCC
1. Clone the repository
2. From the project root, compile using:
   ```bash
   gcc src/main.c -o src/main.exe -I./include -L./lib -lSDL2 -lSDL2main -mwindows
   ```

## Project Structure
```
project/
├── src/                # C source files
│   ├── main.c
│   ├── constants.h
│   └── other_files.c
├── include/            # Header files
│   └── SDL2/
│       └── SDL.h
├── lib/                # Library files
│   ├── libSDL2.a
│   ├── libSDL2main.a
│   └── other_libs
├── build/              # Ready to run game
│   ├── main.exe
│   ├── SDL2.dll
│   └── other_dlls
└── .vscode/
    └── tasks.json
```

## Dependencies
All required dependencies are included in the project:
- SDL2 headers in `include/`
- SDL2 libraries in `lib/`
- Required DLLs in `build/`

## Controls
- ESC - Exit game
- (other controls)

## Development Notes
- Written in C99
- Uses SDL2 for graphics and input
- Built with GCC

