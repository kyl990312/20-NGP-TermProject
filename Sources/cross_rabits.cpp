#define _WINSOCK_DEPRECATED_NO_WARNINGS // �ֽ� VC++ ������ �� ��� ����
#pragma comment(lib, "ws2_32")
#include <winsock2.h>
#include <stdlib.h>
#include "MainGame_State.h"
#include "Title_State.h"
#include "End_State.h"
#include "ClientStruct.h"

#define SERVERIP   "127.0.0.1"
#define SERVERPORT 9000
#define BUFSIZE    128

Title_State title;
MainGame_State* main_game = nullptr;
End_State* end;

GLvoid drawScene();
GLvoid Reshape(int w, int h);
GLvoid TimerFunction(int value);
GLvoid keyboard(unsigned char key, int x, int y);

int state_mode = 0;

loadOBJ models[26];
Shader* shader1;

// �� ������ �޾ƺ���
MapData tmpMap;

void ModelLoad() {
	shader1 = new Shader("shaders/vertexshader.glvs", "shaders/fragmentshader.glfs");
	// Hero
	models[0] = loadOBJ("Resources/rabit.obj", shader1->ID);

	// box
	models[1] = loadOBJ("Resources/box.obj", shader1->ID);

	// ����
	models[2] = loadOBJ("Resources/number_0.obj", shader1->ID);
	models[3] = loadOBJ("Resources/number_1.obj", shader1->ID);
	models[4] = loadOBJ("Resources/number_2.obj", shader1->ID);
	models[5] = loadOBJ("Resources/number_3.obj", shader1->ID);
	models[6] = loadOBJ("Resources/number_4.obj", shader1->ID);
	models[7] = loadOBJ("Resources/number_5.obj", shader1->ID);
	models[8] = loadOBJ("Resources/number_6.obj", shader1->ID);
	models[9] = loadOBJ("Resources/number_7.obj", shader1->ID);
	models[10] = loadOBJ("Resources/number_8.obj", shader1->ID);
	models[11] = loadOBJ("Resources/number_9.obj", shader1->ID);

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

	// ��Ÿ
	models[21] = loadOBJ("Resources/snow.obj", shader1->ID);
	models[22] = loadOBJ("Resources/soul_cube.obj", shader1->ID);
	models[23] = loadOBJ("Resources/title_font.obj", shader1->ID);
	models[24] = loadOBJ("Resources/title_plane.obj", shader1->ID);
	models[25] = loadOBJ("Resources/ghost.obj", shader1->ID);

	shader1->setVec3("viewPos", glm::vec3(0.0f, 45.0f, 50));
	shader1->setVec3("lightColor", glm::vec3(0.5f, 0.5f, 0.5f));
	shader1->setVec3("lightPos", glm::vec3(0, 800, 2000));
}

int main(int argc, char** argv)
{
	int retval;

	// ���� �ʱ�ȭ
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

	// socket()
	// ��� ����
	SOCKET listen_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (listen_sock == INVALID_SOCKET) err_quit((char*)"socket()");

	// socket()
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) err_quit((char*)"socket()");

	// connect()
	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = inet_addr(SERVERIP);
	serveraddr.sin_port = htons(SERVERPORT);
	retval = connect(sock, (SOCKADDR*)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR) err_quit((char*)"connect()");


	// ��� ������ ����
	// ���� ����
	SOCKET client_sock;
	SOCKADDR_IN clientaddr;
	int addrlen;

	HANDLE hThread;

	hThread = CreateThread(NULL, 0, ProcessClient, (LPVOID)client_sock, 0, NULL);

	if (hThread == NULL)
		closesocket(client_sock);
	else
		CloseHandle(hThread);

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

	title.shader = new Shader("shaders/hero_vertexshader.glvs", "shaders/hero_fragmentshader.glfs");
	title.font_shader = new Shader("shaders/font_vertexshader.glvs", "shaders/font_fragmentshader.glfs");
	
	// �ݹ�
	glutDisplayFunc(drawScene);
	glutTimerFunc(10, TimerFunction, 1);
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(Reshape);
	glutMainLoop();

	delete title.shader;
	delete title.font_shader;

	// closesocket()
	closesocket(listen_sock);

	// ���� ����
	WSACleanup();
	return 0;
}

GLvoid drawScene()
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	switch (state_mode) {
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

	switch (state_mode) {
	case 0:
		title.Display();
		break;
	case 1:
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
	switch (state_mode) {
	case 0:
		title.update();
		break;
	case 1:
		main_game->update();
		state_mode = main_game->next_state;
		if (state_mode != 1) {
			delete main_game->shader;
			delete main_game->hero_shader;
			delete main_game;
			end = new End_State;
			end->shader1 = new Shader("shaders/number_vertexshader.glvs", "shaders/number_fragmentshader.glfs");
		}
		break;
	case 2:
		end->update();
		break;
	}
	glutTimerFunc(10, TimerFunction, 1);
	glutPostRedisplay();
}

GLvoid keyboard(unsigned char key, int x, int y) {
	switch (state_mode) {
	case 0:
		title.keyboard(key, x, y);
		state_mode = title.next_state;
		if (state_mode == 1) {
			main_game = new MainGame_State;
			main_game->shader = new Shader("shaders/vertexshader.glvs", "shaders/fragmentshader.glfs");
			main_game->hero_shader = new Shader("shaders/hero_vertexshader.glvs", "shaders/hero_fragmentshader.glfs");
		}
		break;
	case 1:
		main_game->keyboard(key, x, y);
		break;
	case 2:
		end->keyboard(key, x, y);
		state_mode = end->next_state;
		delete end->shader1;
		delete end;
		break;
	}
}

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

bool recvFixedVar(SOCKET& client_sock, int& len, char buf[])
{
	int retval;
	// ������ �ޱ�(���� ����)
	// ����, ������ ������ ����, ���� ���۷κ��� ������ ������ ũ��(BYTE), flag
	retval = recvn(client_sock, (char*)&len, sizeof(int), 0);
	if (retval == SOCKET_ERROR) {
		err_display((char*)"recv()");
		return false;
	}
	else if (retval == 0)
		return false;

	// ������ �ޱ�(���� ����)
	retval = recvn(client_sock, buf, len, 0);
	if (retval == SOCKET_ERROR) {
		err_display((char*)"recv()");
		return false;
	}
	else if (retval == 0)
		return false;

	return true;
}


// ����� ���� ������ ���� �Լ�
int recvn(SOCKET s, char* buf, int len, int flags)
{
	int received;
	// ���� �����͸� ������ ����
	char* ptr = buf;
	// ���� ���۷κ��� ������ ������ ũ��(BYTE)
	int left = len;

	while (left > 0) {
		// ����, ���� �����͸� ������ ����, ���� ���۷κ��� ������ ������ ũ��(BYTE), flag(0) 
		// ���� ����Ʈ �� or 0(���� ����) or SOKET_ERROR
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


DWORD WINAPI ProcessClient(LPVOID arg)
{
	SOCKET client_sock = (SOCKET)arg;
	SOCKADDR_IN clientaddr;

	int addrlen = sizeof(clientaddr);
	getpeername(client_sock, (SOCKADDR*)&clientaddr, &addrlen);

	// ������ ��ſ� ����� ����
	char buf[BUFSIZE + 1];
	int len = 0;

	//������ ������ ���

	while (recvFixedVar(client_sock, len, buf)) {
		// if(������ ������)
			// ������Ʈ �ض�
		ZeroMemory(&buf, sizeof(buf));
	}

	// closesocket()
	closesocket(client_sock);

	return 0;
}