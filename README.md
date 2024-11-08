# Flapocalypse

A 2D game (Flappy Bird clone) in C using SDL2.

## Quick Start (Play the Game)

1. Download the latest release from the [Releases](https://github.com/berzz26/SDL_C/releases) page
2. Extract the ZIP file
3. Run `flapocolypse.exe`
(another way can be directly just downloading the flapocolypse.exe and running it, but due to the great broker, windows, it would be detected malicious(as it is just another executable) so i recommend to just extract the zip and test.)

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

## Project Structure(how your root dir should look like)
```
project/
├── src/                # C source files
│   ├── main.c
│   ├── constants.h
│   └── 
├── include/            # Header files
│   └── SDL2/
│       └── SDL.h
├── lib/                # Library files
│   ├── libSDL2.a
│   ├── libSDL2main.a
│   
├── build/              # Ready to run game
│   ├── main.exe
│   ├── SDL2.dll
│   
└── .vscode/
    └── tasks.json
```

## Dependencies
All required dependencies are included in the project:
- SDL2 headers in `include/`
- SDL2 libraries in `lib/`
- Required DLLs in `build/`

## Controls
- Space to jump.


## Development Notes
- Written in C99
- Uses SDL2 for graphics and input
- Built with GCC

