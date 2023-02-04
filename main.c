
#include <SDL.h>
#include <food.h>
#include <macros.h>
#include <snake.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#define BACKGROUND_COLOR 255, 255, 255, 255
#define SNAKE_MOVE_TIME TO_CLOCK(0.5)
extern DIRECTION direction;
int main()
{
    // Init
    SDL_Init(SDL_INIT_EVERYTHING);
    direction = NONE;
    SDL_Window *win;
    SDL_Renderer *ren;
    SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &win, &ren);
    const uint8_t *const keyboard = SDL_GetKeyboardState(0);
    snake snake = snake_init(BASIC_GAME_RULE);
    clock_t delta = TO_CLOCK(1. / MAX_FRAMERATE);
    clock_t snake_time = SNAKE_MOVE_TIME;
    // Game cycle
    SDL_SetRenderDrawColor(ren, BACKGROUND_COLOR);
    food f;
    food_random(f, time(0), snake.rule.max_x, snake.rule.max_y);
    while (1)
    {
        clock_t time = clock();
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                goto free_event;
            }
        }
        // control
        if (keyboard[SDL_SCANCODE_UP] && UP + direction != 0)
        {
            direction = UP;
        }
        if (keyboard[SDL_SCANCODE_DOWN] && DOWN + direction != 0)
        {
            direction = DOWN;
        }
        if (keyboard[SDL_SCANCODE_LEFT] && LEFT + direction != 0)
        {
            direction = LEFT;
        }
        if (keyboard[SDL_SCANCODE_RIGHT] && RIGHT + direction != 0)
        {
            direction = RIGHT;
        }
        if ((snake_time -= delta) < 0)
        {
            snake_collide(&snake, &f);
            if (direction == LEFT)
            {
                snake_move(&snake, (pos_t){-1, 0});
            }
            else if (direction == RIGHT)
            {
                snake_move(&snake, (pos_t){1, 0});
            }
            else if (direction == UP)
            {
                snake_move(&snake, (pos_t){0, -1});
            }
            else if (direction == DOWN)
            {
                snake_move(&snake, (pos_t){0, 1});
            }
            snake_time = SNAKE_MOVE_TIME;
        }
        // render
        SDL_RenderClear(ren);
        food_draw(&f, snake.rule, ren);
        snake_draw(&snake, ren);
        SDL_RenderPresent(ren);
        // debug
        printf("%lf\r", TO_SECONDS(delta));
        // delta
        delta = clock() - time;
    }
free_event : {
    SDL_DestroyWindow(win);
    SDL_DestroyRenderer(ren);
    SDL_Quit();
    snake_free(&snake);
}
    return 0;
}
