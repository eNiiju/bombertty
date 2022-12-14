/**
 * Constants & definitions for the client and the server.
 * @file definitions.h
 * @date 2022-11-29
 */

#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <stdbool.h>
#include <limits.h>

/* ------------------------------------------------------------------------- */
/*                                 Constants                                 */
/* ------------------------------------------------------------------------- */

// Miscelaneous
#define TOKEN_PATH_NAME   "/etc/passwd"
#define MAX_LENGTH_PATH_TO_MAP PATH_MAX
#define MAX_LENGTH_MAP_NAME    NAME_MAX

// Message types
#define MESSAGE_CLIENT_CONNECTION_TYPE    1
#define MESSAGE_CLIENT_DISCONNECTION_TYPE 2
#define MESSAGE_CLIENT_MOVE_TYPE          3
#define MESSAGE_CLIENT_PLACE_BOMB_TYPE    4
#define MESSAGE_SERVER_RESPONSE_TYPE      5
#define MESSAGE_SERVER_GAME_STATE_TYPE    6
#define MESSAGE_SERVER_GAME_END_TYPE      7

// Direction values
#define DIRECTION_UP    1
#define DIRECTION_DOWN  2
#define DIRECTION_LEFT  3
#define DIRECTION_RIGHT 4

// Game default values & constants
#define MAX_PLAYERS                           4
#define DEFAULT_BOMB_RANGE                    1
#define MAX_BOMB_RANGE                        5
#define MAX_POWERUPS            3 * MAX_PLAYERS
#define CHANCE_POWERUP_SPAWN_PERCENT         10
#define MAX_MAP_WIDTH                        50
#define MAX_MAP_HEIGHT                       50
#define BOMB_EXPLOSION_TIMER_MS            3000
#define PLAYER_MOVE_COOLDOWN_MS             100
#define BOMB_FIRE_TIME_MS                  2000
#define REFRESH_DELAY_MS                    100

// Map tiles
#define MAP_TILE_SIZE_X                4
#define MAP_TILE_SIZE_Y                2
#define MAP_TILE_EMPTY               ' '
#define MAP_TILE_WALL                '#'
#define MAP_TILE_BREAKABLE_WALL      '/'
#define MAP_TILE_BOMB                'o'
#define MAP_TILE_EXPLOSION           'x'
#define MAP_TILE_POWERUP             '$'
#define MAP_TILE_PLAYER_1            '1'
#define MAP_TILE_PLAYER_2            '2'
#define MAP_TILE_PLAYER_3            '3'
#define MAP_TILE_PLAYER_4            '4'

// Colors
#define MAP_TILE_COLOR_EMPTY          0
#define MAP_TILE_COLOR_WALL           1
#define MAP_TILE_COLOR_BREAKABLE_WALL 2
#define MAP_TILE_COLOR_BOMB           3
#define MAP_TILE_COLOR_EXPLOSION      4
#define MAP_TILE_COLOR_POWERUP        5
#define MAP_TILE_COLOR_PLAYER_1       6
#define MAP_TILE_COLOR_PLAYER_2       7
#define MAP_TILE_COLOR_PLAYER_3       8
#define MAP_TILE_COLOR_PLAYER_4       9
#define TEXT_COLOR_TITLE             10
#define TEXT_COLOR_MAP_NAME          11
#define TEXT_COLOR_CONTROL_KEY       12

// Player control keys
#define CONTROL_KEY_UP         'z'
#define CONTROL_KEY_DOWN       's'
#define CONTROL_KEY_LEFT       'q'
#define CONTROL_KEY_RIGHT      'd'
#define CONTROL_KEY_PLACE_BOMB ' '
#define CONTROL_KEY_REFRESH    'r' // Used to refresh the display

/* ------------------------------------------------------------------------- */
/*                                Structures                                 */
/* ------------------------------------------------------------------------- */

struct coordinates {
    int x;
    int y;
};

struct bomb {
    bool active;
    struct coordinates coords;
    int range;
    bool exploded;
};

struct powerup {
    bool active;
    struct coordinates coords;
};

/**
 * Structure representing every informations about a player
 * during a game.
*/
struct player {
    pid_t pid_client;
    bool alive;
    struct coordinates coords;
    int bomb_range;
    struct bomb bomb;
    bool can_move;
};

/**
 * Structure responsible for holding all informations about
 * the game's current state.
*/
struct game {
    int game_code;
    int msqid; // Main message queue ID
    bool ended;
    int winner; // Winner's player number, -1 if no winner
    int player_count; // Players that are still alive
    int number_of_players;
    int map_height;
    int map_width;
    struct powerup powerups[MAX_POWERUPS];
    int powerup_count;
    char map_name[MAX_LENGTH_MAP_NAME];
    char path_to_map_file[MAX_LENGTH_PATH_TO_MAP];
    char map[MAX_MAP_WIDTH][MAX_MAP_HEIGHT];
    struct player players[MAX_PLAYERS];
};

/**
 * Structure representing a move a player wants to make.
*/
struct player_move {
    int player_number;
    int direction; // DIRECTION_UP, DIRECTION_DOWN, DIRECTION_LEFT or DIRECTION_RIGHT
};

#endif
