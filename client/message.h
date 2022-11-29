/**
 * message.c header file.
 * @file message.h
 * @date 2022-11-23
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

/* ------------------------------------------------------------------------- */
/*                          Constants & definitions                          */
/* ------------------------------------------------------------------------- */

#define GAME_CODE 42
#define TOKEN_PATH_NAME "/etc/passwd"

#define MESSAGE_TYPE_CONNECTION 1
#define MESSAGE_TYPE_DISCONNECTION 2
#define MESSAGE_TYPE_MOVE 3
#define MESSAGE_TYPE_PLACE_BOMB 4

#define DIRECTION_UP 1
#define DIRECTION_DOWN 2
#define DIRECTION_LEFT 3
#define DIRECTION_RIGHT 4

/* Messages sent by the client */

struct message_connection {
    long mtype; // MESSAGE_TYPE_CONNECTION
    struct {
        pid_t pid; // PID of the client
    } mcontent;
};

struct message_disconnection {
    long mtype; // MESSAGE_TYPE_DISCONNECTION
    struct {
        pid_t pid; // PID of the client
    } mcontent;
};

struct message_move {
    long mtype; // MESSAGE_TYPE_MOVE
    struct {
        pid_t pid; // PID of the client
        int direction;
    } mcontent;
};

struct message_place_bomb {
    long mtype; // MESSAGE_TYPE_PLACE_BOMB
    struct {
        pid_t pid; // PID of the client
    } mcontent;
};

/* Messages sent by the server */

struct message_response {
    long mtype; // PID of the client
    struct {
        pid_t pid; // PID of the server
        bool success;
    } mcontent;
};



/* ------------------------------------------------------------------------- */
/*                            Function prototypes                            */
/* ------------------------------------------------------------------------- */

bool send_message_connection(int msqid, pid_t pid);

bool send_message_disconnection(int msqid, pid_t pid);

bool send_message_move(int msqid, pid_t pid, int direction);

bool send_message_place_bomb(int msqid, pid_t pid);

bool receive_message_response(int msqid, pid_t pid);
