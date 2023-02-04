#ifndef B7018854_9761_4EDA_818E_4B51EB331A5B
#define B7018854_9761_4EDA_818E_4B51EB331A5B
#include <stdbool.h>
#include <stdint.h>
typedef pos_t food;
typedef enum
{
    NONE = 0,
    LEFT = 1,
    RIGHT = -LEFT,
    UP = 2,
    DOWN = -UP
} DIRECTION;
typedef struct game_rule_t
{
    pos_t default_pos;
    uint32_t default_len;
    int32_t max_x, max_y;
    uintmax_t max_len;
    bool isBrick;
} game_rule_t;
typedef struct movement_buffer_t
{
    pos_t *array;
    uintmax_t len;
    uintmax_t pos;
} movement_buffer_t;

typedef struct snake
{
    movement_buffer_t buffer;
    uint32_t current_len;
    const game_rule_t rule;
    pos_t current_pos;
} snake;

snake snake_init(game_rule_t rules);

void snake_free(snake *snake);

void snake_move(snake *snake, pos_t dir);

void snake_collide(snake *snake, food *const food);

void snake_draw(const snake *snake, SDL_Renderer *ren);

#endif /* B7018854_9761_4EDA_818E_4B51EB331A5B */
