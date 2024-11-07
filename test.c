#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int WINDOW_WIDTH = 480;
const int WINDOW_HEIGHT = 480;
const int PIPE_WIDTH = 80;
const int PIPE_GAP = 150;
const int BIRD_SIZE = 20;
const int GRAVITY = 1;
const int JUMP_STRENGTH = -10;
const int PIPE_SPEED = 3;

typedef struct {
    float x, y;
    float velocity;
} Bird;

typedef struct {
    int x;
    int height;
} Pipe;

// Initialize SDL components
bool initSDL(SDL_Window **window, SDL_Renderer **renderer) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        return false;
    }
    *window = SDL_CreateWindow("Flappy Bird", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (*window == NULL) {
        printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
        return false;
    }
    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
    if (*renderer == NULL) {
        printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
        return false;
    }
    return true;
}

// Handle bird jump on spacebar press
void handleInput(bool *isRunning, Bird *bird) {
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0) {
        if (event.type == SDL_QUIT) {
            *isRunning = false;
        }
        if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE) {
            bird->velocity = JUMP_STRENGTH;
        }
    }
}

// Update bird position and apply gravity
void updateBird(Bird *bird) {
    bird->velocity += GRAVITY;
    bird->y += bird->velocity;
    if (bird->y < 0) {
        bird->y = 0;
        bird->velocity = 0;
    }
    if (bird->y + BIRD_SIZE > WINDOW_HEIGHT) {
        bird->y = WINDOW_HEIGHT - BIRD_SIZE;
        bird->velocity = 0;
    }
}

// Update pipe position and reset if it goes off-screen
void updatePipe(Pipe *pipe) {
    pipe->x -= PIPE_SPEED;
    if (pipe->x < -PIPE_WIDTH) {
        pipe->x = WINDOW_WIDTH;
        pipe->height = rand() % (WINDOW_HEIGHT - PIPE_GAP);
    }
}

// Render the bird, pipes, and background
void render(SDL_Renderer *renderer, Bird bird, Pipe pipe) {
    SDL_SetRenderDrawColor(renderer, 135, 206, 235, 255); // Sky blue
    SDL_RenderClear(renderer);

    // Render bird
    SDL_Rect birdRect = { (int)bird.x, (int)bird.y, BIRD_SIZE, BIRD_SIZE };
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255); // Yellow
    SDL_RenderFillRect(renderer, &birdRect);

    // Render pipes
    SDL_Rect pipeRectTop = { pipe.x, 0, PIPE_WIDTH, pipe.height };
    SDL_Rect pipeRectBottom = { pipe.x, pipe.height + PIPE_GAP, PIPE_WIDTH, WINDOW_HEIGHT - pipe.height - PIPE_GAP };
    SDL_SetRenderDrawColor(renderer, 34, 139, 34, 255); // Green
    SDL_RenderFillRect(renderer, &pipeRectTop);
    SDL_RenderFillRect(renderer, &pipeRectBottom);

    SDL_RenderPresent(renderer);
}

// Check for collision with pipes or ground
bool checkCollision(Bird bird, Pipe pipe) {
    if (bird.y < 0 || bird.y + BIRD_SIZE > WINDOW_HEIGHT) {
        return true;
    }
    if (bird.x + BIRD_SIZE > pipe.x && bird.x < pipe.x + PIPE_WIDTH) {
        if (bird.y < pipe.height || bird.y + BIRD_SIZE > pipe.height + PIPE_GAP) {
            return true;
        }
    }
    return false;
}

// Main game loop
int main(int argc, char *args[]) {
    srand(time(NULL));

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    if (!initSDL(&window, &renderer)) {
        return 1;
    }

    Bird bird = { .x = WINDOW_WIDTH / 4, .y = WINDOW_HEIGHT / 2, .velocity = 0 };
    Pipe pipe = { .x = WINDOW_WIDTH, .height = rand() % (WINDOW_HEIGHT - PIPE_GAP) };

    bool isRunning = true;
    while (isRunning) {
        handleInput(&isRunning, &bird);
        updateBird(&bird);
        updatePipe(&pipe);
        
        if (checkCollision(bird, pipe)) {
            printf("Game Over!\n");
            SDL_Delay(1000);
            bird.y = WINDOW_HEIGHT / 2;
            bird.velocity = 0;
            pipe.x = WINDOW_WIDTH;
            pipe.height = rand() % (WINDOW_HEIGHT - PIPE_GAP);
        }
        
        render(renderer, bird, pipe);
        SDL_Delay(16); // Delay to cap frame rate at ~60 FPS
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
