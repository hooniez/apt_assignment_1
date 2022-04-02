
#ifndef COSC_ASS_ONE_TYPES
#define COSC_ASS_ONE_TYPES

// A 2D array to represent the maze or observations
// REMEMBER: in a grid, the location (x,y) is found by grid[y][x]!
typedef char** Env;

#define SYMBOL_WALL     '='
#define SYMBOL_EMPTY    '.'
#define SYMBOL_GOAL     'G'
#define SYMBOL_START    'S'

enum Direction {
    UP,
    RIGHT,
    DOWN,
    LEFT
};

#endif // COSC_ASS_ONE_TYPES
