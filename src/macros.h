#ifndef DC53661D_5BB8_4C3D_A45F_10BEC06A01F0
#define DC53661D_5BB8_4C3D_A45F_10BEC06A01F0
#define POS_VEC(f, s, ex)                                                                                              \
    do                                                                                                                 \
    {                                                                                                                  \
        f.x ex## = s.x;                                                                                                \
        f.y ex## = s.y;                                                                                                \
    } while (0)
#define POS_EQ(f, s) f.x == s.x &&f.y == s.y
#define MAX_FRAMERATE (240)
#define TO_SECONDS(cl) (((double)cl) / CLOCKS_PER_SEC)
#define TO_CLOCK(sec) ((sec)*CLOCKS_PER_SEC)
#define INTERFACE 50
#define WALL 0
#define WIDTH_PLAY_ZONE 600
#define HEIGHT_PLAY_ZONE 600
#define WIDTH (WIDTH_PLAY_ZONE + WALL * 2)
#define HEIGHT (HEIGHT_PLAY_ZONE + WALL * 2 + INTERFACE)
#define HEAD_COLOR 255, 0, 0, 255
#define TAIL_COLOR 0, 0, 0, 255
#define FOOD_COLOR 0, 0, 255, 255
#define BASIC_GAME_RULE                                                                                                \
    (game_rule_t)                                                                                                      \
    {                                                                                                                  \
        .isBrick = false, .max_len = 100, .max_x = 10, .max_y = 10, .default_len = 0, .default_pos = (pos_t)           \
        {                                                                                                              \
            0, 0                                                                                                       \
        }                                                                                                              \
    }
#endif /* DC53661D_5BB8_4C3D_A45F_10BEC06A01F0 */
