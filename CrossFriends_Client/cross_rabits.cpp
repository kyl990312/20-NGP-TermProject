#include "GameManager.h"

GameManager gameManager;

int g_prevTimeInMillisecond = 0.f;

GLvoid drawScene();
GLvoid Reshape(int w, int h);
GLvoid TimerFunction(int value);
GLvoid keyboard(unsigned char key, int x, int y);

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

	// GamManager Init
	gameManager.Init();

	glutDisplayFunc(drawScene);
	glutTimerFunc(10, TimerFunction, 1);
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(Reshape);
	glutMainLoop();

}

GLvoid drawScene()
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	gameManager.Render();
	glutSwapBuffers();
}


GLvoid Reshape(int w, int h) {
	glViewport(0, 0, w, h);
}

GLvoid TimerFunction(int value)
{
	// calc elaspedTime
	int currentTime = glutGet(GLUT_ELAPSED_TIME);
	int elapsedTime = currentTime - g_prevTimeInMillisecond;
	g_prevTimeInMillisecond = currentTime;

	// game update
	gameManager.Update(float(elapsedTime/32));

	glutTimerFunc(33, TimerFunction, 1);
	glutPostRedisplay();
}

GLvoid keyboard(unsigned char key, int x, int y) {
	gameManager.Keyboard(key);
}