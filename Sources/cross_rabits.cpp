#define _WINSOCK_DEPRECATED_NO_WARNINGS // �ֽ� VC++ ������ �� ��� ����
#pragma comment(lib, "ws2_32")
#include <winsock2.h>
#include <stdlib.h>
#include <vector>
#include "DataStruct.h"
#include "shader.h"
#include "loadObj.h"

#define SERVERIP   "127.0.0.1"
#define SERVERPORT 9000
#define BUFSIZE    128

#define SCR_WIDTH 800
#define SCR_HEIGHT 600


// Server-Client Process
void err_quit(char* );
void err_display(char* );
bool recvFixedVar(SOCKET& , int& , char []);
int recvn(SOCKET , char* , int , int );
DWORD WINAPI ProcessClient(LPVOID);
void ResetObjectDatas(int vectorSize);
void StoreMapData();

// gameProceess
GLvoid drawScene();
GLvoid Reshape(int w, int h);
GLvoid TimerFunction(int value);
GLvoid keyboard(unsigned char key, int x, int y);

void ModelLoad();
void DrawObject(int modelIdx, glm::vec3 position, glm::vec3 rotation, glm::vec3 size);
void TitleRender();
void MainGameRender();

void EndRender();

std::vector<ObjectData> objectDatas;
HeroData heroData;

int currentScene = 0;

loadOBJ models[27];
Shader* shader1;
Shader* fontShader;
Shader* startbuttonShader;

glm::mat4 projection = glm::ortho(-300 * (float)SCR_WIDTH / (float)SCR_HEIGHT, 300 * (float)SCR_WIDTH / (float)SCR_HEIGHT, (float)-400, (float)400, (float)-600, (float)600);
glm::vec3 cameraPos = glm::vec3(8.0f, 45.0f, 40);
glm::vec3 cameraDirection = cameraDirection = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
glm::mat4 view = glm::lookAt(cameraPos, cameraDirection, cameraUp);

// �� ������ �޾ƺ���
ObjectData tmpMap;

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

	HANDLE hThread;

	hThread = CreateThread(NULL, 0, ProcessClient, (LPVOID)sock, 0, NULL);

	if (hThread == NULL)
		closesocket(sock);
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

	
	// �ݹ�
	glutDisplayFunc(drawScene);
	glutTimerFunc(10, TimerFunction, 1);
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(Reshape);
	glutMainLoop();


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
	switch (currentScene) {
	case Scene::Title:
		glClearColor(0.5f, 0.9f, 0.4f, 1.0f);
		break;
	case Scene::MainGame:
		glClearColor(1.0f, 0.7f, 0.9f, 1.0f);
		break;
	case Scene::End:
		glClearColor(0.5f, 0.9f, 0.4f, 1.0f);
		break;
	}
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	switch (currentScene) {
	case Scene::Title:
		
		break;
	case Scene::MainGame:
		
		break;
	case Scene::End:
		break;
	}
	glutSwapBuffers();
}


GLvoid Reshape(int w, int h) {
	glViewport(0, 0, w, h);
}

GLvoid TimerFunction(int value)
{
	switch (currentScene) {
	case Scene::Title:
		
		break;
	case Scene::MainGame:
		
		break;
	case Scene::End:
		
		break;
	}
	glutTimerFunc(10, TimerFunction, 1);
	glutPostRedisplay();
}

GLvoid keyboard(unsigned char key, int x, int y) {
	switch (currentScene) {
	case Scene::Title:
		
		break;
	case Scene::MainGame:
		
		break;
	case Scene::End:
		
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

	// ������ ��ſ� ����� ����
	char buf[BUFSIZE + 1];
	int len = 0;
	ResetObjectDatas(3);
	//������ ������ ���
	while (recvFixedVar(client_sock, len, buf)) {
		switch (currentScene)
		{
		case Scene::Title:
			
			//if(���������� �Ѿ��)
				//ResetObjects(�ʿ��ѿ�����Ʈ����);
			break;
		case  Scene::MainGame:

			//if(���������� �Ѿ��)
				//ResetObjects(�ʿ��ѿ�����Ʈ����);
			break;
		case Scene::End:
			break;
		}
		// if(������ ������)
			// ������Ʈ �ض�
		memcpy(&tmpMap, buf, sizeof(ObjectData));
		std::cout << "tag: " << tmpMap.tag 
			<< "(x, y, z): " << tmpMap.positionX << ", " << tmpMap.positionY << ", " << tmpMap.positionZ << std::endl;
		ZeroMemory(&buf, sizeof(buf));
	}

	// closesocket()
	closesocket(client_sock);

	return 0;
}

void ModelLoad() {
	shader1 = new Shader("shaders/vertexshader.glvs", "shaders/fragmentshader.glfs");
	fontShader = new Shader("shaders/vertexshader.glvs", "shaders/font_fragmentshader.glfs");
	startbuttonShader = new Shader("shaders/startbutton_vertexshader.glvs", "shaders/startbutton_fragmentshader.glfs");

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

void ResetObjectDatas(int vectorSize) {
	objectDatas.clear();
	objectDatas.resize(vectorSize);

	for (int i = 0; i < vectorSize; ++i) {
		objectDatas.emplace_back(ObjectData());
	}
}

void StoreMapData(int len,char* buf) {
	for (int i = 0; i < len / sizeof(ObjectData); ++i) 
		memcpy(&buf, buf + i, sizeof(objectDatas));
}

void DrawObject(int modelIdx, glm::vec3 position, glm::vec3 rotation, glm::vec3 size) {
	models[modelIdx].load(projection, view);

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(position.x, position.y, position.z));
	model = glm::rotate(model, glm::radians(position.x), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(position.y), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(position.z), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::scale(model, size);

	// transform
	models[modelIdx].setTransform(model);

	models[modelIdx].draw();
}

void TitleRender() {
	// set shader 

	// draw object
	
	//set shader

	// draw font

	// set shader
	startbuttonShader->use();
	// draw startButton
}

void MainGameRender() {
	// set shader

	// draw all objects
	
	// draw all heros
}

void EndRender() {
	//set shader
	// draw numbers
}