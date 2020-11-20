#define _WINSOCK_DEPRECATED_NO_WARNINGS // �ֽ� VC++ ������ �� ��� ����
#pragma comment(lib, "ws2_32")
#include <winsock2.h>
#include <stdlib.h>
#include <stdio.h>
#include<fstream>
#include<iostream>
#include "DataStruct.h"


#define SERVERPORT 9000
#define BUFSIZE    512

// Scene
int currentScene = Scene::Title;

void sendFixedVar(SOCKET&, size_t, char[]);

DWORD WINAPI ProcessClient(LPVOID);

struct MultipleArg {
    SOCKET clientsock;
    int clientCount;
};

ObjectData mapdatas[10];

// ���� �Լ� ���� ��� �� ����
void err_quit(char* msg)
{
    LPVOID lpMsgBuf;
    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
        NULL, WSAGetLastError(),
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR)&lpMsgBuf, 0, NULL);
    MessageBox(NULL, (LPCTSTR)lpMsgBuf, (LPCTSTR)msg, MB_ICONERROR);
    LocalFree(lpMsgBuf);
    exit(1);
}

// ���� �Լ� ���� ���
void err_display(char* msg)
{
    LPVOID lpMsgBuf;
    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
        NULL, WSAGetLastError(),
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR)&lpMsgBuf, 0, NULL);
    printf("[%s] %s", msg, (char*)lpMsgBuf);
    LocalFree(lpMsgBuf);
}


int main(int argc, char* argv[])
{
    int retval;
    int clientCnt = 0;


    // ���� �ʱ�ȭ
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
        return 1;

    // socket()
    // ��� ����
    SOCKET listen_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_sock == INVALID_SOCKET) err_quit((char*)"socket()");

    // bind()
    SOCKADDR_IN serveraddr;
    ZeroMemory(&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serveraddr.sin_port = htons(SERVERPORT);
    retval = bind(listen_sock, (SOCKADDR*)&serveraddr, sizeof(serveraddr));
    if (retval == SOCKET_ERROR) err_quit((char*)"bind()");

    // listen()
    // bind�� ��� ����, �����ϴ� Ŭ���̾�Ʈ ��
    retval = listen(listen_sock, SOMAXCONN);
    if (retval == SOCKET_ERROR) err_quit((char*)"listen()");

    // ���� ����
    SOCKET client_sock;
    SOCKADDR_IN clientaddr;
    int addrlen;


    while (1) {
        switch (currentScene) {
        case Scene::Title:
        {
            // accept()
            addrlen = sizeof(clientaddr);
            client_sock = accept(listen_sock, (SOCKADDR*)&clientaddr, &addrlen);
            if (client_sock == INVALID_SOCKET) {
                err_display((char*)"accept()");
                break;
            }

            // ������ ����
            MultipleArg arg = { client_sock, clientCnt++ };
            HANDLE hThread = CreateThread(NULL, 0, ProcessClient, (LPVOID)&arg, 0, NULL);

            if (hThread == NULL)
                closesocket(client_sock);
            else
                CloseHandle(hThread);
        }
            break;
        case Scene::MainGame:
            break;
        case Scene::End:
            
            break;
        }


    }

    // closesocket()
    closesocket(listen_sock);

    // ���� ����
    WSACleanup();
    return 0;
}


DWORD WINAPI ProcessClient(LPVOID arg)
{
    SOCKET client_sock = ((MultipleArg*)arg)->clientsock;
    SOCKADDR_IN clientaddr;

    int addrlen = sizeof(clientaddr);
    getpeername(client_sock, (SOCKADDR*)&clientaddr, &addrlen);
    std::cout << "Ŭ���̾�Ʈ ����" << std::endl;

    for (int i = 0; i < 10; ++i) {
        mapdatas[i].tag = ModelIdx::Hero;

        mapdatas[i].positionX = 10 + i;
        mapdatas[i].positionY = 10 + i;
        mapdatas[i].positionZ = 10 + i;


        mapdatas[i].rotationX = 0;
        mapdatas[i].rotationY = 0; 
        mapdatas[i].rotationZ = 0;

        mapdatas[i].sizeX = 1;
        mapdatas[i].sizeY = 1; 
        mapdatas[i].sizeZ = 1;
    }

    // Ŭ���̾�Ʈ�� ������ ���
    for (const ObjectData& mapdata : mapdatas) {
        sendFixedVar(client_sock, sizeof(ObjectData), (char*)&mapdata);
    }

    // closesocket()
    closesocket(client_sock);

    return 0;
}

void sendFixedVar(SOCKET& sock, size_t readSize, char buf[])
{
    int retval;

    // ������ ������(���� ����)
    retval = send(sock, (char*)&readSize, sizeof(int), 0);
    if (retval == SOCKET_ERROR) {
        err_display((char*)"send()");
        return;
    }

    // ������ ������(���� ����)
    retval = send(sock, buf, readSize, 0);
    if (retval == SOCKET_ERROR) {
        err_display((char*)"send()");
        return;
    }
}