#include <SDL_render.h>
#include <error.h>
#include <food.h>
#include <macros.h>
#include <snake.h>
#include <stdlib.h>
DIRECTION direction;
#define pix_x WIDTH_PLAY_ZONE / snake->rule.max_x
#define pix_y HEIGHT_PLAY_ZONE / snake->rule.max_y
#define LOGIC(f, s) ((f > 0) ? f - 1 : s)
#define FORECH(i, buffer_pos, buffer_len, curent_len)                                                                  \
    for (uintmax_t i = LOGIC(buffer_pos, buffer_len), len = curent_len; len != 0; --len, i = LOGIC(i, buffer_len))
enum ERROR
{
    BAD_ALLOC,
    GAME_OVER,
    NO_RESOURSE
};
void snake_error_handler(snake *const snake, enum ERROR err)
{
    switch (err)
    {
    case BAD_ALLOC:
        error(-1, BAD_ALLOC, "%s", "ALOCATION WITH ERROR");
        break;
    case NO_RESOURSE:
        error(-1, NO_RESOURSE, "%s", "THERE IS NO WAY TO LOAD RESOURSE");
        break;
    case GAME_OVER:
        puts("Game Over");
        snake->current_pos = snake->rule.default_pos;
        snake->current_len = snake->rule.default_len;
        break;

    default:
        break;
    }
}
snake snake_init(const game_rule_t rules)
{

    snake res = {
        .current_pos = rules.default_pos,
        .rule = rules,
        .current_len = rules.default_len,
        .buffer = (movement_buffer_t){.array = calloc(sizeof(pos_t), rules.max_len), .len = rules.max_len, .pos = 0}};

    if (!res.buffer.array)
    {
        snake_error_handler(NULL, BAD_ALLOC);
    }
    return res;
}

void snake_free(snake *snake)
{
    free(snake->buffer.array);
}
void snake_move(snake *const snake, pos_t dir)
{
    if (snake->buffer.pos == snake->buffer.len)
    {
        snake->buffer.pos = 0;
    }
    snake->buffer.array[snake->buffer.pos++] = snake->current_pos;
    POS_VEC(snake->current_pos, dir, +);
    if (snake->rule.isBrick)
    {
        if (snake->current_pos.x >= snake->rule.max_x || snake->current_pos.y >= snake->rule.max_y ||
            snake->current_pos.x < 0 || snake->current_pos.y < 0)
        {
            snake_error_handler(snake, GAME_OVER);
            direction = NONE;
        }
    }
    else
    {
        if (snake->current_pos.x >= snake->rule.max_x)
        {
            snake->current_pos.x %= snake->rule.max_x;
        }
        else if (snake->current_pos.y >= snake->rule.max_y)
        {
            snake->current_pos.y %= snake->rule.max_y;
        }
        else if (snake->current_pos.x < 0)
        {
            snake->current_pos.x = snake->rule.max_x - 1;
        }
        else if (snake->current_pos.y < 0)
        {
            snake->current_pos.y = snake->rule.max_y - 1;
        }
    }
}
static inline void snake_eat(snake *const snake)
{
    ++snake->current_len;
}
void snake_collide(snake *const snake, food *const food)
{
    if (POS_EQ(snake->current_pos, (*food)))
    {
        food_random((*food), 0, snake->rule.max_x, snake->rule.max_y);
        snake_eat(snake);
    }
    FORECH(i, snake->buffer.pos, snake->buffer.len, snake->current_len)
    {
        if (snake->buffer.array[i].x == snake->current_pos.x && snake->buffer.array[i].y == snake->current_pos.y)
        {
            snake_error_handler(snake, GAME_OVER);
            direction = NONE;
        }
    }
}
void snake_draw(const snake *const snake, SDL_Renderer *const ren)
{

    uint8_t color[4];
    SDL_GetRenderDrawColor(ren, color, color + 1, color + 2, color + 3);
    SDL_SetRenderDrawColor(ren, HEAD_COLOR);
    // head
    SDL_RenderFillRect(ren, &(SDL_Rect){.x = WALL + snake->current_pos.x * pix_x,
                                        .y = WALL + snake->current_pos.y * pix_y,
                                        .w = pix_x,
                                        .h = pix_y});
    // tail
    SDL_SetRenderDrawColor(ren, TAIL_COLOR);
    FORECH(i, snake->buffer.pos, snake->buffer.len, snake->current_len)
    {
        SDL_RenderFillRect(ren, &(SDL_Rect){.x = WALL + snake->buffer.array[i].x * pix_x,
                                            .y = WALL + snake->buffer.array[i].y * pix_y,
                                            .w = pix_x,
                                            .h = pix_y});
    }

    SDL_SetRenderDrawColor(ren, color[0], color[1], color[2], color[3]);
}
