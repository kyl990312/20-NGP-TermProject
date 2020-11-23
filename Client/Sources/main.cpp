#define _WINSOCK_DEPRECATED_NO_WARNINGS // 최신 VC++ 컴파일 시 경고 방지
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

// gameProceess
GLvoid drawScene();
GLvoid Reshape(int w, int h);
GLvoid TimerFunction(int value);
GLvoid keyboard(unsigned char key, int x, int y);
GLvoid mouse(int button, int state, int x, int y);

void ModelLoad();
void DrawObject(int modelIdx, glm::vec3 position, glm::vec3 rotation, glm::vec3 size);
void TitleRender();
void MainGameRender();
void EndRender();

//std::vector<ObjectData> objectDatas;
ObjectData objectDatas[100];
HeroData heroData[3];

int currentScene = Scene::MainGame;
char key;

loadOBJ models[27];
Shader* shader1;
Shader* fontShader;
Shader* startbuttonShader;

glm::mat4 projection = glm::ortho(-300 * (float)SCR_WIDTH / (float)SCR_HEIGHT, 300 * (float)SCR_WIDTH / (float)SCR_HEIGHT, (float)-400, (float)400, (float)-600, (float)600);
glm::vec3 cameraPos = glm::vec3(8.0f, 45.0f, 40);
glm::vec3 cameraDirection = cameraDirection = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
glm::mat4 view = glm::lookAt(cameraPos, cameraDirection, cameraUp);

int main(int argc, char** argv)
{
	//objectDatas.reserve(200);

	HANDLE hThread;

	hThread = CreateThread(NULL, 0, ProcessClient, NULL, 0, NULL);

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
	
	// 콜백
	glutDisplayFunc(drawScene);
	glutTimerFunc(33, TimerFunction, 1);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutReshapeFunc(Reshape);
	glutMainLoop();

	return 0;
}

GLvoid drawScene()
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	switch (currentScene) {
	case Scene::Title:
		glClearColor(1.0f, 0.7f, 0.9f, 1.0f);
		MainGameRender();
		break;
	case Scene::MainGame:
		glClearColor(0.5f, 0.9f, 0.4f, 1.0f);
		MainGameRender();
		break;
	case Scene::End:
		glClearColor(1.0f, 0.7f, 0.9f, 1.0f);
		break;
	}
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
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
	glutTimerFunc(33, TimerFunction, 1);
	glutPostRedisplay();
}

GLvoid keyboard(unsigned char key, int x, int y) {
	switch (currentScene) {
	case Scene::Title:
		
		break;
	case Scene::MainGame:
		switch (key) {
		case 'w' | 'W':
			break;
		case 'a'|'A':
			break;
		case 'd' |'D':
			break;
		}
		

		break;
	case Scene::End:
		
		break;
	}
}

// title 버튼 처리
GLvoid mouse(int button, int state, int x, int y) {
	//if (state_mode == 0) {
	//	title.mouse(button, state, x, y);
	//}
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

bool recvFixedVar(SOCKET& client_sock, int& len, char buf[])
{
	int retval;
	// 데이터 받기(고정 길이)
	// 소켓, 데이터 저장할 버퍼, 수신 버퍼로부터 복사할 데이터 크기(BYTE), flag
	retval = recvn(client_sock, (char*)&len, sizeof(int), 0);
	if (retval == SOCKET_ERROR) {
		err_display((char*)"recv()");
		return false;
	}
	else if (retval == 0)
		return false;

	// 데이터 받기(가변 길이)
	retval = recvn(client_sock, buf, len, 0);
	if (retval == SOCKET_ERROR) {
		err_display((char*)"recv()");
		return false;
	}
	else if (retval == 0)
		return false;

	return true;
}


// 사용자 정의 데이터 수신 함수
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


DWORD WINAPI ProcessClient(LPVOID arg)
{
	std::cout << "ProcessClient" << std::endl;
	int retval;

	// 윈속 초기화
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

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
	std::cout << "connect" << std::endl;

	// 데이터 통신에 사용할 변수
	char buf[BUFSIZE + 1];
	int len = 0;

	//서버와 데이터 통신
	while (1) {
		std::cout << "Conversation" << std::endl;
		switch (currentScene)
		{
		case Scene::Title:
			
			//if(다음씬으로 넘어갈때)
				//ResetObjects(필요한오브젝트개수);
			break;
		case  Scene::MainGame:
		{			
			// mapData 수신
			//objectDatas.clear();
			int idx = 0;
			for(ObjectData& obj : objectDatas ) {
				ObjectData tmpMap;
				recvFixedVar(sock, len, buf);
				memcpy(&tmpMap, buf, sizeof(ObjectData));
				//objectDatas.emplace_back(tmpMap);
				obj = tmpMap;
				ZeroMemory(&buf, sizeof(buf));
			}
			//std::cout << objectDatas.size() << std::endl;

		/*	int cnt = 0;
			for (const ObjectData& mapdata : objectDatas) {
				if (mapdata.tag != -1) {
					std::cout << cnt << "." << "Map tag = " << mapdata.tag << std::endl;

					std::cout << cnt << "." << "Map Position = " << mapdata.positionX << "," << mapdata.positionY << "," << mapdata.positionZ << std::endl;
					std::cout << cnt << "." << "Map Size = " << mapdata.sizeX << "," << mapdata.sizeY << "," << mapdata.sizeZ << std::endl;
					std::cout << cnt << "." << "Map Roatation = " << mapdata.rotationX << "," << mapdata.rotationY << "," << mapdata.rotationZ << std::endl;
					cnt++;
				}
			}*/
		}

			
			break;
		case Scene::End:
			break;
		}
	}

	// closesocket()
	closesocket(sock);

	// 윈속 종료
	WSACleanup();

	return 0;
}

void ModelLoad() {
	shader1 = new Shader("shaders/vertexshader.glvs", "shaders/fragmentshader.glfs");
	fontShader = new Shader("shaders/vertexshader.glvs", "shaders/font_fragmentshader.glfs");
	// fragmentshader->startbutton_fragmentshader
	startbuttonShader = new Shader("shaders/vertexshader.glvs", "shaders/fragmentshader.glfs");

	// Hero
	models[0] = loadOBJ("Resources/rabit.obj", shader1->ID);

	// box
	models[1] = loadOBJ("Resources/box.obj", shader1->ID);

	// 숫자
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

	// 기타
	models[21] = loadOBJ("Resources/snow.obj", shader1->ID);
	models[22] = loadOBJ("Resources/soul_cube.obj", shader1->ID);
	models[23] = loadOBJ("Resources/title_font.obj", shader1->ID);
	models[24] = loadOBJ("Resources/title_plane.obj", shader1->ID);
	models[25] = loadOBJ("Resources/ghost.obj", shader1->ID);
	//models[26] = loadOBJ("Resources/start_button.obj", startbuttonShader->ID);

	shader1->setVec3("viewPos", glm::vec3(0.0f, 45.0f, 50));
	shader1->setVec3("lightColor", glm::vec3(0.5f, 0.5f, 0.5f));
	shader1->setVec3("lightPos", glm::vec3(0, 800, 2000));
}


void DrawObject(int modelIdx, glm::vec3 position, glm::vec3 rotation, glm::vec3 size) {
	models[modelIdx].load(projection, view);

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(position.x, position.y, position.z));
	model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::scale(model, size);

	// transform
	models[modelIdx].setTransform(model);

	models[modelIdx].draw();
}

// 필요 확인
void TitleRender() {
	// set shader 
	shader1->use();
	// draw object
	
	//set shader

	// draw font

	// set shader
	startbuttonShader->use();
	// draw startButton
}

void MainGameRender() {
	// set shader
	shader1->use();

	// draw all objects
	for (const ObjectData& obj : objectDatas) {
		//DrawObject(int modelIdx, glm::vec3 position, glm::vec3 rotation, glm::vec3 size);
		if (obj.tag == -1)
			break;
		DrawObject(obj.tag, glm::vec3(obj.positionX, obj.positionY, obj.positionZ)
			, glm::vec3(obj.rotationX, obj.rotationY, obj.rotationZ)
			, glm::vec3(obj.sizeX, obj.sizeY, obj.sizeZ));
	}

	//// draw all heros
	//if (heroData.alive) {
	//	models[ModelIdx::Hero].load(projection, view);

	//	glm::mat4 model = glm::mat4(1.0f);
	//	model = glm::translate(model, glm::vec3(heroData.x, heroData.y, heroData.z));
	//	model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	//	model = glm::rotate(model, glm::radians(-heroData.rotaionAngle), glm::vec3(0.0f, 1.0f, 0.0f));

	//	// transform
	//	models[ModelIdx::Hero].setTransform(model);

	//	models[ModelIdx::Hero].draw();
	//}
}

// 필요 확인
void EndRender() {
	//set shader
	// draw numbers
}