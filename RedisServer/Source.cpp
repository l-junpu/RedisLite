// Server

#include "src/Server.h"
#include "src/Cache.h"

#include <iostream>
#include <WinSock2.h>

void HandleClientRequest(SOCKET ClientSocket, soba::Cache* Cache)
{
    int iResult;
    int iSendResult;
    char recvbuf[1024];
    int recvbuflen = 1024;

    do {
        iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
        if (iResult > 0) {
            printf("Bytes received: %d\n", iResult);

            // Echo the buffer back to the sender
            iSendResult = send(ClientSocket, recvbuf, iResult, 0);
            if (iSendResult == SOCKET_ERROR) {
                printf("send failed with error: %d\n", WSAGetLastError());
                closesocket(ClientSocket);
                WSACleanup();
                return;
            }
            printf("Bytes sent: %d\n", iSendResult);
        }
        else if (iResult == 0)
            printf("Connection closing...\n");
        else {
            printf("recv failed with error: %d\n", WSAGetLastError());
            closesocket(ClientSocket);
            WSACleanup();
            return;
        }

    } while (iResult > 0);
}

int main()
{

}