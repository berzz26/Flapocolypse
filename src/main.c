#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include"./constants.h"
// Window and game constants


// Bird structure
typedef struct {
    float x, y;        // Position of the bird
    float velocity;    // Current velocity (used for gravity and jump)
} Bird;

// Pipe structure
typedef struct {
    int x;             // Horizontal position of the pipe
    int height;        // Height of the top pipe
} Pipe;

// Function to initialize SDL components
bool initSDL(SDL_Window **window, SDL_Renderer **renderer) {
    // Initialize SDL with video capabilities
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    // Create the game window
    *window = SDL_CreateWindow("Flappy Bird", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (*window == NULL) {
        printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    // Create a renderer for the window (this is where graphics are drawn)
    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
    if (*renderer == NULL) {
        printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
        return false;
    }
    return true;
}

// Function to handle user input for jumping and quitting
void handleInput(bool *isRunning, Bird *bird) {
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0) { // Process all events in the event queue
        if (event.type == SDL_QUIT) {     // If the user closes the window
            *isRunning = false;
        }
        if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE) {
            // If the space key is pressed, make the bird jump by adjusting velocity
            (*bird).velocity = JUMP_STRENGTH;
        }
    }
}

// Function to update bird position and apply gravity
void updateBird(Bird *bird) {
    (*bird).velocity += GRAVITY; // Increase downward velocity due to gravity
    (*bird).y += (*bird).velocity; // Update bird's y-position with new velocity

    // Prevent bird from moving off the top of the screen
    if ((*bird).y < 0) {
        (*bird).y = 0;
        (*bird).velocity = 0;
    }

    // Prevent bird from falling below the bottom of the screen
    if ((*bird).y + BIRD_SIZE > WINDOW_HEIGHT) {
        (*bird).y = WINDOW_HEIGHT - BIRD_SIZE;
        (*bird).velocity = 0;
    }
}

// Function to update pipe position and reset if it goes off-screen
void updatePipe(Pipe *pipe) {
    (*pipe).x -= PIPE_SPEED; // Move pipe to the left

    // Reset pipe to the right side of the screen if it goes off-screen
    if ((*pipe).x < -PIPE_WIDTH) {
        (*pipe).x = WINDOW_WIDTH; // Move it back to the right edge
        (*pipe).height = rand() % (WINDOW_HEIGHT - PIPE_GAP); // Randomize pipe height
    }
}

// Function to render the bird, pipes, and background
void render(SDL_Renderer *renderer, Bird bird, Pipe pipe) {
    // Set background color to sky blue and clear the screen
    SDL_SetRenderDrawColor(renderer, 135, 206, 235, 255);
    SDL_RenderClear(renderer);

    // Draw the bird as a yellow square
    SDL_Rect birdRect = { (int)bird.x, (int)bird.y, BIRD_SIZE, BIRD_SIZE };
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255); // Yellow color
    SDL_RenderFillRect(renderer, &birdRect);

    // Draw the top and bottom pipes as green rectangles
    SDL_Rect pipeRectTop = { pipe.x, 0, PIPE_WIDTH, pipe.height };
    SDL_Rect pipeRectBottom = { pipe.x, pipe.height + PIPE_GAP, PIPE_WIDTH, WINDOW_HEIGHT - pipe.height - PIPE_GAP };
    SDL_SetRenderDrawColor(renderer, 34, 139, 34, 255); // Green color
    SDL_RenderFillRect(renderer, &pipeRectTop);
    SDL_RenderFillRect(renderer, &pipeRectBottom);

    // Display the rendered content on the screen
    SDL_RenderPresent(renderer);
}

// Function to check for collision with pipes or ground
bool checkCollision(Bird bird, Pipe pipe) {
    // Check if bird hits top or bottom of the screen
    if (bird.y < 0 || bird.y + BIRD_SIZE > WINDOW_HEIGHT) {
        return true;
    }

    // Check if bird hits a pipe
    if (bird.x + BIRD_SIZE > pipe.x && bird.x < pipe.x + PIPE_WIDTH) {
        if (bird.y < pipe.height || bird.y + BIRD_SIZE > pipe.height + PIPE_GAP) {
            return true;
        }
    }
    return false;
}

// Main game loop
int main(int argc, char *args[]) {
    srand(time(NULL)); // Seed random number generator for pipe height

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    if (!initSDL(&window, &renderer)) { // Initialize SDL components
        return 1;
    }

    // Initialize bird and pipe objects
    Bird bird = { .x = WINDOW_WIDTH / 4, .y = WINDOW_HEIGHT / 2, .velocity = 0 };
    Pipe pipe = { .x = WINDOW_WIDTH, .height = rand() % (WINDOW_HEIGHT - PIPE_GAP) };

    bool isRunning = true; // Game running flag
    while (isRunning) {
        handleInput(&isRunning, &bird); // Handle user input
        updateBird(&bird); // Update bird position and apply gravity
        updatePipe(&pipe); // Move pipe to the left and reset if off-screen
        
        // Check for collision and reset if bird collides
        if (checkCollision(bird, pipe)) {
            printf("Game Over!\n");
            SDL_Delay(1000); // Pause for a second before resetting
            bird.y = WINDOW_HEIGHT / 2; // Reset bird position
            bird.velocity = 0; // Reset bird velocity
            pipe.x = WINDOW_WIDTH; // Reset pipe position
            pipe.height = rand() % (WINDOW_HEIGHT - PIPE_GAP); // New random height for pipe
        }
        
        render(renderer, bird, pipe); // Draw the game elements
        SDL_Delay(16); // Delay to cap frame rate at ~60 FPS
    }

    // Clean up and quit SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
