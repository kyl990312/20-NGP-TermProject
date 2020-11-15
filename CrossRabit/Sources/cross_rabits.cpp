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

loadOBJ models[26];
Shader *shader1;
Shader* fontShader;

void ModelLoad() {
	shader1 = new Shader("shaders/vertexshader.glvs", "shaders/fragmentshader.glfs");
	fontShader = new Shader("shaders/vertexshader.glvs", "shaders/font_fragmentshader.glfs");

	// Hero
	models[0] = loadOBJ("Resources/rabit.obj", shader1->ID);

	// box
	models[1] = loadOBJ("Resources/box.obj", shader1->ID);

	// 숫자
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

	// 기타
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

	title.shader = new Shader("shaders/vertexshader.glvs", "shaders/fragmentshader.glfs");
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

			delete main_game;
			end = new End_State;

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
		}
		break;
	case 1:
		main_game->keyboard(key, x, y);
		break;
	case 2:
		end->keyboard(key, x, y);
		state_mode = end->next_state;
		delete end;
		break;
	}
}