#include <SDL2/SDL.h>
#include <stdio.h>
#include "./constants.h"




//global 
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
int game_is_running = 0;

int window_initialize(void)
{

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        fprintf(stderr, "cant run SDL\n");
        return 0;
    }

    window = SDL_CreateWindow(
        NULL,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        640,
        400,
        SDL_WINDOW_BORDERLESS

    );

    if (!window)
    {
        fprintf(stderr, "Error genrating window\n");
        return 0;
    }

    renderer = SDL_CreateRenderer(
        window,
        -1,
        0);

    if (!renderer)
    {
        fprintf(stderr, "error rendering window\n");
        return 0;
    }

    printf("window created without errors\n");

    return 1;
}

void process_input()
{
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type)
    {
    case SDL_QUIT:
        game_is_running = 0;
        break;

    case SDL_KEYDOWN:
        if(event.key.keysym.sym == SDLK_ESCAPE){
            game_is_running = 0;
            break;
        }
    
    default:
        break;
    }

}

void setup(){
    //todo
}
void update()
{
    //todo
}
void render()
{
    //todo
}

void destroy_window()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main(int argc, char *args[])
{
    game_is_running = window_initialize();

    while (game_is_running)
    {
        process_input();
        update();
        render();
    }

    destroy_window();
    return 0;
}