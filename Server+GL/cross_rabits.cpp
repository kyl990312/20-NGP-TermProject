#define _WINSOCK_DEPRECATED_NO_WARNINGS // 최신 VC++ 컴파일 시 경고 방지
#pragma comment(lib, "ws2_32")
#include <winsock2.h>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include "DataStruct.h"
#include "MainGame_State.h"
#include "Title_State.h"
#include "End_State.h"

#define SERVERPORT 9009
#define BUFSIZE    512

#define MAX_CLIENT 3

// 통신
void sendFixedVar(SOCKET&, size_t, char[]);

DWORD WINAPI ProcessServer(LPVOID);
DWORD WINAPI ConversationWithClient(LPVOID);

struct MultipleArg {
	SOCKET clientsock;
	int clientCount;
};
ObjectData mapdatas[100];
HeroData heroDatas[3];

int currentScene = Scene::Title;
HANDLE hThread[3];
HANDLE hAllUpdated[3];
HANDLE hAllSend[3];
HANDLE hAllScoreRecv[3];

// GL
Title_State* title_game = nullptr;
MainGame_State* main_game = nullptr;
End_State* end_game = nullptr;

GLvoid drawScene();
GLvoid Reshape(int w, int h);
GLvoid TimerFunction(int value);

int clientCnt = 0;
bool ready_check[3] = { false, false, false };

int score[3] = {};
bool isRecvscore[3] = { false, false, false };

// frame
int prevTime = 0;
float elapsedTimeSec = 0;


int main(int argc, char** argv)
{
	srand((unsigned int)time(NULL));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(900, 700);
	glutCreateWindow("Server");
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "GLEW Initialized" << std::endl;

	// tag init
	for (ObjectData data : mapdatas) {
		data.tag = -1;
	}

	main_game = new MainGame_State;
	title_game = new Title_State;
	end_game = new End_State;

	// 통신
	// 윈속 - 데이터 처리 스레드 분리 
	HANDLE hThread0 = CreateThread(NULL, 0, ProcessServer, NULL, 0, NULL);

	glutDisplayFunc(drawScene);
	glutTimerFunc(16, TimerFunction, 1);
	glutReshapeFunc(Reshape);
	glutMainLoop();

	CloseHandle(hThread0);

	if (title_game != NULL)
		delete title_game;
	if (main_game != NULL)
		delete main_game;
	if (end_game != NULL)
		delete end_game;
}

GLvoid drawScene()
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glutSwapBuffers();
}


GLvoid Reshape(int w, int h) {
	glViewport(0, 0, w, h);
}


int recvn(SOCKET s, char* buf, int len, int flags);
void recvFixedVar(SOCKET& client_sock, size_t len, char buf[]);


GLvoid TimerFunction(int value)
{
	// calc elapsedTime
	int currentTime = glutGet(GLUT_ELAPSED_TIME);
	int elapsedTime = currentTime - prevTime;
	prevTime = currentTime;
	elapsedTimeSec = (float)elapsedTime / 1000.f;

	switch (currentScene) {
	case Scene::Title:
		if (WaitForMultipleObjects(clientCnt, hAllSend, TRUE, INFINITE) == WAIT_OBJECT_0) {
			title_game->update();
			for (int i = 0; i < clientCnt; ++i) {
				SetEvent(hAllUpdated[i]);
				ResetEvent(hAllSend[i]);
			}
		}
		break;
	case Scene::MainGame:
		if (WaitForMultipleObjects(3, hAllSend, TRUE, INFINITE) == WAIT_OBJECT_0) {
			main_game->update();
			for (int i = 0; i < 3; ++i) {
				SetEvent(hAllUpdated[i]);
				ResetEvent(hAllSend[i]);
			}
		}
		break;
	case Scene::End:
		if (WaitForMultipleObjects(3, hAllScoreRecv, TRUE, INFINITE) == WAIT_OBJECT_0) {
			std::cout << "스코어 업데이트" << std::endl;
			if (main_game != NULL) {
				delete main_game;
				main_game = new MainGame_State;
			}
			end_game->update();
			end_game->rankingData(mapdatas);

			std::cout << "스코어 업데이트 끝" << std::endl;
			for (int i = 0; i < 3; ++i) {
				ResetEvent(hAllScoreRecv[i]);
				SetEvent(hAllUpdated[i]);
			}
		}
		break;
	}
	glutTimerFunc(16, TimerFunction, 1);
	glutPostRedisplay();
}

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

DWORD WINAPI ProcessServer(LPVOID arg)
{
	for (int i = 0; i < 3; ++i) {
		hAllUpdated[i] = CreateEvent(  // event object 생성
			NULL,          // 상속 불가
			TRUE,          // manual-reset mode로 생상
			TRUE,         // non-signaled 상태로 생성
			NULL           // 이름 없는 event
		);
		if (hAllUpdated[i] == NULL) {
			printf("Event object creation error \n");
			return -1;
		}

		hAllSend[i] = CreateEvent(  // event object 생성
			NULL,          // 상속 불가
			TRUE,          // manual-reset mode로 생상
			FALSE,         // signaled 상태로 생성
			NULL           // 이름 없는 event
		);
		if (hAllSend[i] == NULL) {
			printf("Event object creation error \n");
			return -1;
		}

		hAllScoreRecv[i] = CreateEvent(  // event object 생성
			NULL,          // 상속 불가
			TRUE,          // manual-reset mode로 생상
			TRUE,         // non - signaled 상태로 생성
			NULL           // 이름 없는 event
		);
		if (hAllScoreRecv[i] == NULL) {
			printf("Event object creation error \n");
			return -1;
		}
	}

	int retval;

	// 윈속 초기화
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

	// socket()
	// 대기 소켓
	int option = 1;
	SOCKET listen_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (listen_sock == INVALID_SOCKET) err_quit((char*)"socket()");
	setsockopt(listen_sock, IPPROTO_TCP, TCP_NODELAY, (char*)&option, sizeof(option));

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

	while (1) {
		switch (currentScene) {
		case Scene::Title:
		{
			// accept() 
			SOCKADDR_IN clientaddr;
			int addrlen = sizeof(clientaddr);
			SOCKET client_sock = accept(listen_sock, (SOCKADDR*)&clientaddr, &addrlen);
			if (client_sock == INVALID_SOCKET) {
				err_display((char*)"accept()");
				break;
			}

			int clientCount = clientCnt;

			// 스레드 생성
			MultipleArg arg = { client_sock, clientCount };
			hThread[clientCount] = CreateThread(NULL, 0, ConversationWithClient, (LPVOID)&arg, 0, NULL);

			if (hThread[clientCount] == NULL)
				closesocket(client_sock);
			else
				CloseHandle(hThread[clientCount]);

			clientCnt++;
		}
		break;
		case Scene::MainGame:
			break;
		case Scene::End:

			break;
		}
	}
	// close Event
	for (int i = 0; i < 3; ++i) {
		CloseHandle(hAllUpdated[i]);
		CloseHandle(hAllSend[i]);
	}

	// closesocket()
	closesocket(listen_sock);

	// 윈속 종료
	WSACleanup();
	return 0;
}

DWORD WINAPI ConversationWithClient(LPVOID arg)
{
	std::cout << "ConversationWithClient" << std::endl;
	SOCKET client_sock = ((MultipleArg*)arg)->clientsock;
	SOCKADDR_IN clientaddr;

	int addrlen = sizeof(clientaddr);
	getpeername(client_sock, (SOCKADDR*)&clientaddr, &addrlen);
	std::cout << "클라이언트 접속" << std::endl;

	int cnt = ((MultipleArg*)arg)->clientCount;
	char key;

	std::ofstream out("rank.txt", std::ios::app);

	while (1) {
		switch (currentScene) {
		case Scene::Title:
			if (WaitForSingleObject(hAllUpdated[cnt], INFINITE) == WAIT_OBJECT_0) {
				// ready 받기
				recvFixedVar(client_sock, sizeof(bool), (char*)&ready_check[cnt]);

				if (ready_check[0] == true && ready_check[1] == true && ready_check[2] == true)
					currentScene = Scene::MainGame;

				// 맵 데이터 넘겨주기
				title_game->TitleDatas(mapdatas);
				for (const ObjectData& mapdata : mapdatas) {
					sendFixedVar(client_sock, sizeof(ObjectData), (char*)&mapdata);
				}

				sendFixedVar(client_sock, sizeof(int), (char*)&currentScene);

				ResetEvent(hAllUpdated[cnt]);
				SetEvent(hAllSend[cnt]);
			}
			break;
		case Scene::MainGame:
			if (WaitForSingleObject(hAllUpdated[cnt], INFINITE) == WAIT_OBJECT_0) {
				// key 입력 받기
				recv(client_sock, &key, sizeof(char), 0);
				if (key != '\0' || key != NULL) {
					main_game->keyboard(key, cnt, 0);
				}
				// hero data 전송
				main_game->GetHeroDatas(heroDatas);
				for (const HeroData data : heroDatas) {
					sendFixedVar(client_sock, sizeof(HeroData), (char*)&data);
				}
				// map data 전송
				main_game->GetMapDatas(mapdatas);
				for (const ObjectData& mapdata : mapdatas) {
					sendFixedVar(client_sock, sizeof(ObjectData), (char*)&mapdata);
				}

				//cnt 전송- 죽었는지 안죽었는지 send
				sendFixedVar(client_sock, sizeof(bool), (char*)&heroDatas[cnt].alive);

				// 3명 다 죽으면 scene::end로 
				if (heroDatas[0].alive == false && heroDatas[1].alive == false && heroDatas[2].alive == false) {
					currentScene = Scene::End;
				}
				sendFixedVar(client_sock, sizeof(int), (char*)&currentScene);

				ResetEvent(hAllUpdated[cnt]);
				SetEvent(hAllSend[cnt]);
			}
			break;
		case Scene::End:
		{
			if (isRecvscore[cnt] == false) {
				isRecvscore[cnt] = true;
				// 스코어 받기
				recvFixedVar(client_sock, sizeof(int), (char*)&score[cnt]);
				out << score[cnt] << std::endl;
				SetEvent(hAllScoreRecv[cnt]);
				std::cout << "스코어 받음" << std::endl;
			}


			// rankingData처리한 데이터 정보 넘겨주기
			if (WaitForSingleObject(hAllUpdated[cnt], INFINITE) == WAIT_OBJECT_0) {
				std::cout << "스코어 보내는 중" << std::endl;
				for (const ObjectData& mapdata : mapdatas) {
					sendFixedVar(client_sock, sizeof(ObjectData), (char*)&mapdata);
				}
			}
			std::cout << "스코어 다 보냄" << std::endl;

			ready_check[cnt] = false;
			isRecvscore[cnt] = false;
			heroDatas[cnt].alive = true;
			currentScene = Scene::Title;

			sendFixedVar(client_sock, sizeof(int), (char*)&currentScene);
			ResetEvent(hAllUpdated[cnt]);
			SetEvent(hAllSend[cnt]);
			break;
		}
		}
	}
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

void recvFixedVar(SOCKET& client_sock, size_t len, char buf[])
{
	int retval;

	// 데이터 받기(고정 길이)
	// 소켓, 데이터 저장할 버퍼, 수신 버퍼로부터 복사할 데이터 크기(BYTE), flag
	retval = recvn(client_sock, (char*)&len, sizeof(int), 0);
	if (retval == SOCKET_ERROR) {
		err_display((char*)"recv()");
		return;
	}
	else if (retval == 0)
		return;

	// 데이터 받기(가변 길이)
	retval = recvn(client_sock, buf, len, 0);
	if (retval == SOCKET_ERROR) {
		err_display((char*)"recv()");
		return;
	}
	else if (retval == 0)
		return;
}