#include "MainGame_State.h"
#include "Title_State.h"
#include "End_State.h"

Title_State title;
MainGame_State* main_game = nullptr;
End_State* end;

GLvoid drawScene();
GLvoid Reshape(int w, int h);
GLvoid TimerFunction(int value);
GLvoid keyboard(unsigned char key, int x, int y);

int state_mode = 0;

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
	title.shader = new Shader("shaders/hero_vertexshader.glvs", "shaders/hero_fragmentshader.glfs");
	title.font_shader = new Shader("shaders/font_vertexshader.glvs", "shaders/font_fragmentshader.glfs");
	glutDisplayFunc(drawScene);
	glutTimerFunc(10, TimerFunction, 1);
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(Reshape);
	glutMainLoop();

	delete title.shader;
	delete title.font_shader;
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