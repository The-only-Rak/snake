#include <SDL.h>
#include <food.h>
#include <macros.h>
#include <snake.h>
#define pix_x WIDTH_PLAY_ZONE / rule.max_x
#define pix_y HEIGHT_PLAY_ZONE / rule.max_y
void food_draw(const food *const food, const game_rule_t rule, SDL_Renderer *const ren)
{
    uint8_t color[4];
    SDL_GetRenderDrawColor(ren, color, color + 1, color + 2, color + 3);
    SDL_SetRenderDrawColor(ren, FOOD_COLOR);
    // head
    SDL_RenderFillRect(ren,
                       &(SDL_Rect){.x = WALL + food->x * pix_x, .y = WALL + food->y * pix_y, .w = pix_x, .h = pix_y});
    SDL_SetRenderDrawColor(ren, color[0], color[1], color[2], color[3]);
}