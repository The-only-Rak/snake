#ifndef AFA2250E_5E17_4ACA_83C3_EFD5D26A7A17
#define AFA2250E_5E17_4ACA_83C3_EFD5D26A7A17
#include <pos.h>
#include <snake.h>
#include <stdlib.h>
typedef pos_t food;
typedef struct SDL_Renderer SDL_Renderer;
#define food_random(food, seed, _x, _y)                                                                                \
    do                                                                                                                 \
    {                                                                                                                  \
        if (seed)                                                                                                      \
        {                                                                                                              \
            srand(seed);                                                                                               \
        }                                                                                                              \
        food.x = rand() % _x;                                                                                          \
        food.y = rand() % _y;                                                                                          \
    } while (0)
void food_draw(const food *food, const game_rule_t rule, SDL_Renderer *ren);

#endif /* AFA2250E_5E17_4ACA_83C3_EFD5D26A7A17 */
