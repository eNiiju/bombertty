/**
 * Server header file.
 * @file server.h
 * @date 2022-11-16
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <signal.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>

#include "../include/definitions.h"
#include "message.h"

/* ------------------------------------------------------------------------- */
/*                            Function prototypes                            */
/* ------------------------------------------------------------------------- */

/**
 * Set up and initialize the server.
 * @return true if successful, false otherwise
*/
bool setup(void);

/**
 * Function handling players' actions.
 * It is created as a thread once a player joins the game.
 * It is responsible for the communication between the server and the client,
 * including receiving player's inputs and take them into account for the game.
 * @param arg (long) The player's number.
*/
void* thread_player(void* arg);

/**
 * Function handling the game.
 * It is created as a thread once the game starts.
 * It is responsible for the game's logic, including moving players, placing
 * modifying the map, etc.
 * @param arg Unused.
*/
void* thread_game(void* arg);

/**
 * Creates a player if it's not already added, initializes it's values and
 * adds it to the game.
 * @param pid_client The client's PID.
 * @return true if successful, false otherwise.
*/
bool create_player(pid_t pid_client);

/**
 * Returns if the client is in the game or not.
 * @param pid_client The client's PID.
 * @return true if the client is in the game, false otherwise.
*/
bool client_in_game(pid_t pid_client);

/**
 * Function for the thread handling the "connection" messages.
 * It is created as a thread once the server starts.
 * @param arg Unused.
*/
void* thread_main_message_queue(void* arg);

/**
 * Function for the thread handling the "move" messages received
 * from a client.
 * @param arg (long) The player's number.
*/
void* thread_player_message_move(void* arg);

/**
 * Function for the thread handling the "place bomb" messages received
 * from a client.
 * @param arg (long) The player's number.
*/
void* thread_player_message_place_bomb(void* arg);

/**
 * Returns if a player can move in a given direction, in the current
 * game state in the global variable "game".
 * @param player_number The player's number.
 * @param direction The direction the player wants to move in.
*/
bool player_can_move(long player_number, int direction);

/**
 * Returns if a player can place a bomb in the current game state in the
 * global variable "game".
 * @param player_number The player's number.
*/
bool player_can_place_bomb(long player_number);

/**
 * Thread waiting for the player's move cooldown to end,
 * then ends.
 * @param arg (long) The player's number.
*/
void* thread_wait_player_move_cooldown(void* arg);

/**
 * Moves the player in the given direction, when the player has 
 * no active cooldown.
 * @param player_number The player's number.
 * @param direction The direction the player will be moved
*/
void move_player(long player_number, int direction);

/**
 * Places a bomb in the player's position, then starts a thread
 * that will make the bomb explode after the defined time.
 * @param player_number The player's number.
*/
void place_bomb(long player_number);
