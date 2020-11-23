#define _WINSOCK_DEPRECATED_NO_WARNINGS // 최신 VC++ 컴파일 시 경고 방지
#pragma comment(lib, "ws2_32")
#include <winsock2.h>
#include <stdlib.h>
#include <stdio.h>
#include<fstream>
#include<iostream>
#include <vector>
#include "DataStruct.h"


#define SERVERPORT 9000
#define BUFSIZE    512

// Scene
int currentScene = Scene::Title;
float font_sin_angle = 0.0f;

std::vector<ObjectData> mapdatas;

void TitleDatas();
void sendFixedVar(SOCKET&, size_t, char*);
DWORD WINAPI ProcessClient(LPVOID);

struct MultipleArg {
    SOCKET clientsock;
    int clientCount;
};

struct MyPos {
    float x;
    float y;
    float z;
};
MyPos obj_pos = { 0.0f,0.0f,0.0f };


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
    mapdatas.reserve(200);

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
        {
            // accept()
            addrlen = sizeof(clientaddr);
            client_sock = accept(listen_sock, (SOCKADDR*)&clientaddr, &addrlen);
            if (client_sock == INVALID_SOCKET) {
                err_display((char*)"accept()");
                break;
            }

            // 스레드 생성
            MultipleArg arg = { client_sock, clientCnt++ };
            hThread = CreateThread(NULL, 0, ProcessClient, (LPVOID)&arg, 0, NULL);

            if (hThread == NULL)
                closesocket(client_sock);
            else
                CloseHandle(hThread);

            if (clientCnt == 3)
                currentScene = Scene::MainGame;
        }
            break;
        case Scene::MainGame:
            //std::cout << "Main Game!" << std::endl;
            break;
        case Scene::End:
            break;
        }
    }

    // closesocket()
    closesocket(listen_sock);

    // 윈속 종료
    WSACleanup();
    return 0;
}

int recvn(SOCKET s, char* buf, int len, int flags)
{
    int received;
    // 받은 데이터를 저장할 버퍼
    char* ptr = buf;
    // 수신 버퍼로부터 복사할 데이터 크기(BYTE)
    int left = len;

    while (left > 0) {
        // 소켓, 받은 데이터를 저장할 버퍼, 수신 버퍼로부터 복사할 데이터 크기(BYTE), flag(0) 
        // 받은 바이트 수 or 0(연결 종료) or SOKET_ERROR
        received = recv(s, ptr, left, flags);
        if (received == SOCKET_ERROR)
            return SOCKET_ERROR;
        else if (received == 0)
            break;
        left -= received;
        ptr += received;
    }

    return (len - left);
}


void TitleDatas() {
    ObjectData tmpMap;

    font_sin_angle = (float)(((int)font_sin_angle + 5) % 180);
    obj_pos.z = 50 * sin(font_sin_angle);

    tmpMap.tag = ModelIdx::Hero;
    tmpMap.positionX = 300;
    tmpMap.positionY = obj_pos.y;
    tmpMap.positionZ = obj_pos.z;
    tmpMap.rotationX = 0;
    tmpMap.rotationY = 0;
    tmpMap.rotationZ = 0;
    tmpMap.sizeX = 3;
    tmpMap.sizeY = 3;
    tmpMap.sizeZ = 3;
    mapdatas.emplace_back(tmpMap);

    tmpMap.tag = ModelIdx::TitleFont;
    tmpMap.positionX = obj_pos.x;
    tmpMap.positionY = obj_pos.y;
    tmpMap.positionZ = obj_pos.z;
    tmpMap.rotationX = 0;
    tmpMap.rotationY = 0;
    tmpMap.rotationZ = 0;
    tmpMap.sizeX = 1;
    tmpMap.sizeY = 1;
    tmpMap.sizeZ = 1;
    mapdatas.emplace_back(tmpMap);

    tmpMap.tag = ModelIdx::StartButton;
    tmpMap.positionX = 10;
    tmpMap.positionY = -300;
    tmpMap.positionZ = 10;
    tmpMap.rotationX = 60;
    tmpMap.rotationY = 6;
    tmpMap.rotationZ = -27;
    tmpMap.sizeX = 3.5;
    tmpMap.sizeY = 4.0;
    tmpMap.sizeZ = 4.0;
    mapdatas.emplace_back(tmpMap);
}

DWORD WINAPI ProcessClient(LPVOID arg)
{
    int retval = 0;

    SOCKET client_sock = ((MultipleArg*)arg)->clientsock;
    SOCKADDR_IN clientaddr;

    int addrlen = sizeof(clientaddr);
    getpeername(client_sock, (SOCKADDR*)&clientaddr, &addrlen);
    std::cout << "클라이언트 접속" << std::endl;

    //while (1) {
    switch (currentScene) {
    case Scene::Title:
        TitleDatas();
        // 클라이언트와 데이터 통신
        for (const ObjectData& mapdata : mapdatas) {
            sendFixedVar(client_sock, sizeof(ObjectData), (char*)&mapdata);
        }
        //mapdatas.clear();
        break;
    case Scene::MainGame:
        break;
    case Scene::End:
        break;
    }
    //ZeroMemory(&mapdatas, sizeof(mapdatas));
    //}
    // closesocket()
    closesocket(client_sock);

    return 0;
}

void sendFixedVar(SOCKET& sock, size_t readSize, char* buf)
{
    int retval;

    // 데이터 보내기(고정 길이)
    retval = send(sock, (char*)&readSize, sizeof(int), 0);
    //std::cout <<"고정 길이 retval :" << retval << std::endl;
    if (retval == SOCKET_ERROR) {
        err_display((char*)"send()");
        return;
    }

    // 데이터 보내기(가변 길이)
    retval = send(sock, buf, readSize, 0);
    //std::cout << "가변 길이 retval :" << retval << std::endl;
    if (retval == SOCKET_ERROR) {
        err_display((char*)"가변_send()");
        return;
    }
}