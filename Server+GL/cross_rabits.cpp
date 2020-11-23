#define _WINSOCK_DEPRECATED_NO_WARNINGS // 최신 VC++ 컴파일 시 경고 방지
#pragma comment(lib, "ws2_32")
#include <winsock2.h>
#include <stdlib.h>
#include <stdio.h>
#include<fstream>
#include<iostream>
#include "DataStruct.h"
#include "MainGame_State.h"
#include "Title_State.h"
#include "End_State.h"

#define SERVERPORT 9000
#define BUFSIZE    512

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
int currentScene = Scene::MainGame;

// GL
Title_State title;
MainGame_State* main_game = nullptr;
End_State* end;

GLvoid drawScene();
GLvoid Reshape(int w, int h);
GLvoid TimerFunction(int value);
GLvoid keyboard(unsigned char key, int x, int y);

loadOBJ models[26];
Shader* shader1;
Shader* fontShader;

// frame
float elpasedTime;
int m_time = 0;

void ModelLoad() {
	shader1 = new Shader("shaders/vertexshader.glvs", "shaders/fragmentshader.glfs");
	fontShader = new Shader("shaders/vertexshader.glvs", "shaders/font_fragmentshader.glfs");

	// Hero
	models[0] = loadOBJ("Resources/rabit.obj", shader1->ID);

	// box
	models[1] = loadOBJ("Resources/box.obj", shader1->ID);

	// ¼ýÀÚ
	models[2] = loadOBJ("Resources/number_0.obj", fontShader->ID);
	models[3] = loadOBJ("Resources/number_1.obj", fontShader->ID);
	models[4] = loadOBJ("Resources/number_2.obj", fontShader->ID);
	models[5] = loadOBJ("Resources/number_3.obj", fontShader->ID);
	models[6] = loadOBJ("Resources/number_4.obj", fontShader->ID);
	models[7] = loadOBJ("Resources/number_5.obj", fontShader->ID);
	models[8] = loadOBJ("Resources/number_6.obj", fontShader->ID);
	models[9] = loadOBJ("Resources/number_7.obj", fontShader->ID);
	models[10] = loadOBJ("Resources/number_8.obj", fontShader->ID);
	models[11] = loadOBJ("Resources/number_9.obj", fontShader->ID);

	// State
	models[12] = loadOBJ("Resources/common.obj", shader1->ID);
	models[13] = loadOBJ("Resources/road.obj", shader1->ID);
	models[14] = loadOBJ("Resources/river.obj", shader1->ID);
	models[15] = loadOBJ("Resources/trail.obj", shader1->ID);

	// obj in state
	models[16] = loadOBJ("Resources/car.obj", shader1->ID);
	models[17] = loadOBJ("Resources/truck.obj", shader1->ID);
	models[18] = loadOBJ("Resources/train.obj", shader1->ID);
	models[19] = loadOBJ("Resources/tree.obj", shader1->ID);
	models[20] = loadOBJ("Resources/log.obj", shader1->ID);

	// ±âÅ¸
	models[21] = loadOBJ("Resources/snow.obj", shader1->ID);
	models[22] = loadOBJ("Resources/soul_cube.obj", shader1->ID);
	models[23] = loadOBJ("Resources/title_font.obj", fontShader->ID);
	models[24] = loadOBJ("Resources/title_plane.obj", shader1->ID);
	models[25] = loadOBJ("Resources/ghost.obj", shader1->ID);

	shader1->setVec3("viewPos", glm::vec3(0.0f, 45.0f, 50));
	shader1->setVec3("lightColor", glm::vec3(0.5f, 0.5f, 0.5f));
	shader1->setVec3("lightPos", glm::vec3(0, 800, 2000));

	fontShader->setVec3("viewPos", glm::vec3(0.0f, 45.0f, 50));
	fontShader->setVec3("lightColor", glm::vec3(0.5f, 0.5f, 0.5f));
	fontShader->setVec3("lightPos", glm::vec3(0, 800, 2000));
	fontShader->setVec3("obj_color", glm::vec3(1.0, 0.6, 0.0));

}

int main(int argc, char** argv)
{
	srand((unsigned int)time(NULL));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(900, 700);
	glutCreateWindow("Floating Window");
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "GLEW Initialized" << std::endl;
	ModelLoad();

	// tag init
	for (ObjectData data : mapdatas) {
		data.tag = -1;
	}

	main_game = new MainGame_State;
	// 통신
	// 윈속 - 데이터 처리 스레드 분리 
	HANDLE hThread = CreateThread(NULL, 0, ProcessServer, NULL, 0, NULL);

	title.shader = shader1;
	title.font_shader = fontShader;


	glutDisplayFunc(drawScene);
	glutTimerFunc(33, TimerFunction, 1);
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(Reshape);
	glutMainLoop();

	CloseHandle(hThread);
}

GLvoid drawScene()
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	switch (currentScene) {
	case 0:
	case 2:
		glClearColor(1.0f, 0.7f, 0.9f, 1.0f);
		break;
	case 1:
		glClearColor(0.5f, 0.9f, 0.4f, 1.0f);
		break;
	}
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	switch (currentScene) {
	case 0:
		title.Display();
		break;
	case 1:
		if(main_game!=NULL)
			main_game->Display();
		break;
	case 2:
		end->Display();
	}
	glutSwapBuffers();
}


GLvoid Reshape(int w, int h) {
	glViewport(0, 0, w, h);
}

GLvoid TimerFunction(int value)
{
	// calc elapsedTime
	//int currnetTime = 

	switch (currentScene) {
	case 0:
		title.update();
		break;
	case 1:
		main_game->update();
		//main_game;
		/*if (currentScene != 1) {
			currentScene = main_game->next_state;
			delete main_game;
			end = new End_State;

		}*/

		break;
	case 2:
		end->update();
		break;
	}
	glutTimerFunc(10, TimerFunction, 1);
	glutPostRedisplay();
}

GLvoid keyboard(unsigned char key, int x, int y) {
	switch (currentScene) {
	case 0:
		title.keyboard(key, x, y);
		currentScene = title.next_state;
		if (currentScene == 1) {
			//main_game = new MainGame_State;
		}
		break;
	case 1:
		//main_game->keyboard(key, x, y);
		break;
	case 2:
		end->keyboard(key, x, y);
		currentScene = end->next_state;
		delete end;
		break;
	}
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
	int retval;
	int clientCnt = 0;

	std::cout << "ProcessServer" << std::endl;
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


	while (1) {
		switch (currentScene) {
		case Scene::MainGame:
		{
			// accept()
			addrlen = sizeof(clientaddr);
			client_sock = accept(listen_sock, (SOCKADDR*)&clientaddr, &addrlen);
			if (client_sock == INVALID_SOCKET) {
				err_display((char*)"accept()");
				break;
			}

			// 스레드 생성
			std::cout << "Create Thread" << std::endl;
			MultipleArg arg = { client_sock, clientCnt++ };
			HANDLE hThread = CreateThread(NULL, 0, ConversationWithClient, (LPVOID)&arg, 0, NULL);

			if (hThread == NULL)
				closesocket(client_sock);
			else
				CloseHandle(hThread);
		}
		break;
		case Scene::Title:
			
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

DWORD WINAPI ConversationWithClient(LPVOID arg)
{
	std::cout << "ConversationWithClient" << std::endl;
	SOCKET client_sock = ((MultipleArg*)arg)->clientsock;
	SOCKADDR_IN clientaddr;

	int addrlen = sizeof(clientaddr);
	getpeername(client_sock, (SOCKADDR*)&clientaddr, &addrlen);
	std::cout << "클라이언트 접속" << std::endl;

	while (1) {
		//test
		/*int cnt = 0;
		for (const ObjectData& mapdata : mapdatas) {
			if (mapdata.tag != -1) {
				std::cout << cnt<<"."<<"Map tag = " << mapdata.tag << std::endl;

				std::cout <<cnt<<"."<< "Map Position = " << mapdata.positionX <<","<<mapdata.positionY<<","<<mapdata.positionZ << std::endl;
				std::cout << cnt << "." << "Map Size = " << mapdata.sizeX <<","<<mapdata.sizeY<<","<<mapdata.sizeZ << std::endl;
				std::cout << cnt << "." << "Map Roatation = " << mapdata.rotationX <<","<<mapdata.rotationY<<","<<mapdata.rotationZ << std::endl;
				cnt++;
			}
		}*/
		

		switch (currentScene) {
		case Scene::Title:
			break;
		case Scene::MainGame:


			// map data 전송
			main_game->GetMapDatas(mapdatas);
			for (const ObjectData& mapdata : mapdatas) {
					sendFixedVar(client_sock, sizeof(ObjectData), (char*)&mapdata);
			}
			break;
		case Scene::End:
			break;
		}



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