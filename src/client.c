#include "client.h"
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <time.h>

void InitClient(void) {
    socketFd = socket(AF_INET, SOCK_DGRAM, 0);
    if (socketFd < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&addr, '\0', sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(SERVER_PORT);
    addr.sin_addr.s_addr = inet_addr(SERVER_ADDR);

    GenerateRandomPlayerId();

    char buffer[PACKET_SIZE];
    memset(buffer, 0, PACKET_SIZE);
    strcpy(buffer, "ping");
    ssize_t a = SendToServer(buffer);
    printf("Sent %ld bytes\n", a);
    memset(buffer, 0, PACKET_SIZE);
    ReceiveFromServer(buffer);
    printf("Server response: %s\n", buffer);
}

void GenerateRandomPlayerId(void) {
    srand(time(NULL));
    sprintf(playerId, "client-%d", rand() % 1000);
}

ssize_t SendToServer(const char* buffer) {
    return sendto(socketFd, buffer, strlen(buffer), 0, (struct sockaddr*)&addr, sizeof(addr));
}

ssize_t ReceiveFromServer(char* buffer) {
    return recvfrom(socketFd, buffer, PACKET_SIZE, 0, (struct sockaddr*)&addr, &addr_size);
}

ssize_t CreateRoom(const char* roomId) {
    strcpy(_roomId, roomId);
    char buffer[PACKET_SIZE];
    sprintf(buffer, "cr:%s:%s", _roomId, playerId);
    SendToServer(buffer);

    char response[PACKET_SIZE];
    ReceiveFromServer(response);

    return strcmp(response, "ok") ? -1 : 0;
}

ssize_t JoinRoom(const char* roomId) {
    strcpy(_roomId, roomId);
    char buffer[PACKET_SIZE];
    sprintf(buffer, "jr:%s:%s", _roomId, playerId);
    SendToServer(buffer);

    char response[PACKET_SIZE];
    ReceiveFromServer(response);

    return strcmp(response, "ok") ? -1 : 0;
}

bool IsRoomFull(void) {
    char buffer[PACKET_SIZE];
    sprintf(buffer, "if:%s", _roomId);
    SendToServer(buffer);

    char response[PACKET_SIZE];
    ReceiveFromServer(response);

    return !strcmp(response, "yes");
}

ssize_t DeployFleet(const char* fleetPositions) {
    char buffer[PACKET_SIZE];
    sprintf(buffer, "df:%s:%s:%s", _roomId, playerId, fleetPositions);
    SendToServer(buffer);

    char response[PACKET_SIZE];
    ReceiveFromServer(response);

    return strcmp(response, "ok") ? -1 : 0;
}

bool IsOpponentDeployed(void) {
    char buffer[PACKET_SIZE];
    sprintf(buffer, "id:%s:%s", _roomId, playerId);
    SendToServer(buffer);

    char response[PACKET_SIZE];
    ReceiveFromServer(response);

    return !strcmp(response, "yes");
}

ssize_t TryHit(GridPosition position) {
    char buffer[PACKET_SIZE];
    sprintf(buffer, "th:%s:%s:%d,%d", _roomId, playerId, position.x, position.y);
    SendToServer(buffer);

    char response[PACKET_SIZE];
    ReceiveFromServer(response);

    return !strcmp(response, "hit") ? 1 : !strcmp(response, "miss") ? 0 : -1;
}

GridPosition GetHit(void) {
    char buffer[PACKET_SIZE];
    sprintf(buffer, "gh:%s:%s", _roomId, playerId);
    SendToServer(buffer);

    char response[PACKET_SIZE];
    ReceiveFromServer(response);

    GridPosition position = {0, 0};
    sscanf(response, "%d,%d", &position.x, &position.y);

    return position;
}
