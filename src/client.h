#include <arpa/inet.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include "sea.h"

#ifndef CLIENT_H
#define CLIENT_H

#define SERVER_ADDR "127.0.0.1"
#define SERVER_PORT 9177
#define PACKET_SIZE 128

static struct sockaddr_in addr;
static int socketFd;
static socklen_t addr_size;

static char _roomId[8] = {0};
static char playerId[16] = {0};

void InitClient(void);
void GenerateRandomPlayerId(void);
ssize_t SendToServer(const char* buffer);
ssize_t ReceiveFromServer(char* buffer);
ssize_t CreateRoom(const char* roomId);
ssize_t JoinRoom(const char* roomId);
bool IsRoomFull(void);
ssize_t DeployFleet(const char* fleetPositions);
bool IsOpponentDeployed(void);
ssize_t TryHit(GridPosition position);
GridPosition GetHit(void);

#endif
