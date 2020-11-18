#define _WINSOCK_DEPRECATED_NO_WARNINGS // 최신 VC++ 컴파일 시 경고 방지
#pragma comment(lib, "ws2_32")
#include <winsock2.h>
#include <stdlib.h>
#include <stdio.h>
#include<fstream>
#include<iostream>
#include "DataStruct.h"

#include "MainGame_State.h"

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

MapData mapdatas[10];

// 소켓 함수 오류 출력 후 종료
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

// 소켓 함수 오류 출력
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


    // 윈속 초기화
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
        return 1;

    // socket()
    // 대기 소켓
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
    // bind한 대기 소켓, 수용하는 클라이언트 수
    retval = listen(listen_sock, SOMAXCONN);
    if (retval == SOCKET_ERROR) err_quit((char*)"listen()");

    // 전용 소켓
    SOCKET client_sock;
    SOCKADDR_IN clientaddr;
    int addrlen;

    HANDLE hThread;

    while (1) {
        switch (currentScene) {
        case Scene::Title:
            // accept()
            addrlen = sizeof(clientaddr);
            client_sock = accept(listen_sock, (SOCKADDR*)&clientaddr, &addrlen);
            if (client_sock == INVALID_SOCKET) {
                err_display((char*)"accept()");
                break;
            }

            // 스레드 생성
            MultipleArg arg{ client_sock, clientCnt++ };
            hThread = CreateThread(NULL, 0, ProcessClient, (LPVOID)&arg, 0, NULL);


            break;
        case Scene::MainGame:
            break;
        case Scene::End:
            break;
        }

        if (hThread == NULL)
            closesocket(client_sock);
        else
            CloseHandle(hThread);
    }

    // closesocket()
    closesocket(listen_sock);

    // 윈속 종료
    WSACleanup();
    return 0;
}


DWORD WINAPI ProcessClient(LPVOID arg)
{
    SOCKET client_sock = ((MultipleArg*)arg)->clientsock;
    SOCKADDR_IN clientaddr;

    int addrlen = sizeof(clientaddr);
    getpeername(client_sock, (SOCKADDR*)&clientaddr, &addrlen);

    for (int i = 0; i < 10; ++i) {
        mapdatas[i].tag = 'a' + i;
        mapdatas[i].x = i;
        mapdatas[i].y = i;
        mapdatas[i].z = i;
    }

    // 클라이언트와 데이터 통신
    for (const MapData& mapdata : mapdatas) {
        sendFixedVar(client_sock, sizeof(MapData), (char*)&mapdata);
    }

    // closesocket()
    closesocket(client_sock);

    return 0;
}

void sendFixedVar(SOCKET& sock, size_t readSize, char buf[])
{
    int retval;

    // 데이터 보내기(고정 길이)
    retval = send(sock, (char*)&readSize, sizeof(int), 0);
    if (retval == SOCKET_ERROR) {
        err_display((char*)"send()");
        return;
    }

    // 데이터 보내기(가변 길이)
    retval = send(sock, buf, readSize, 0);
    if (retval == SOCKET_ERROR) {
        err_display((char*)"send()");
        return;
    }
}