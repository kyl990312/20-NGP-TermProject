#include "firework_particle.h"

firework::firework()
{
	color_random1 = (rand() % 500 + 500) * 0.001;
	color_random2 = (rand() % 500 + 500) * 0.001;
	color_random3 = (rand() % 500 + 500) * 0.001;
	float X_pos = rand() % 800 - 400;
	float Y_pos = rand() % 800 - 400;
	float timer_rand = rand() % 10 + 5;
	for (int i = 0; i < 50; i++) {
		snow[i].X = X_pos;
		snow[i].Y = Y_pos;
		snow[i].Z = 100;
		snow[i].timer = timer_rand;
		snow[i].dir = rand() % 360;
	}
}

void firework::draw() {
	Shader snowShader("shaders/snowvertex.glvs", "shaders/snowfragment.glfs");

	loadOBJ snow_obj[50];
	// you can name your shader files however you like
	snowShader.use();

	for (int i = 0; i < 50; i++) {

		snow_obj[i] = loadOBJ("Resources/snow.obj", snowShader.ID);

		if (snow[i].timer < 0) {
			color_random1 = (rand() % 500+ 500) * 0.001;
			color_random2 = (rand() % 500 + 500) * 0.001;
			color_random3 = (rand() % 500 + 500) * 0.001;
			float X_pos = rand() % 800 - 400;
			float Y_pos = rand() % 800 - 400;
			float timer_rand = rand() % 10 + 5;
			for (int i = 0; i < 50; i++) {
				snow[i].X = X_pos;
				snow[i].Y = Y_pos;
				snow[i].Z = 100;
				snow[i].timer = timer_rand;
				snow[i].dir = rand() % 360;
			}
		}

		if (snow[i].dir > 0 and snow[i].dir <= 90) {
			snow[i].X += snow[i].speed * (sin(snow[i].dir* M_PI / 180));
			snow[i].Z += snow[i].speed * (cos(snow[i].dir* M_PI / 180));
			snow[i].Y += snow[i].speed * (-cos(snow[i].dir* M_PI / 180));

		}
		else if (snow[i].dir > 90 and snow[i].dir <= 180) {
			snow[i].X += snow[i].speed * (sin(snow[i].dir* M_PI / 180));
			snow[i].Z += snow[i].speed * (cos(snow[i].dir* M_PI / 180));
			snow[i].Y += snow[i].speed * (-sin(snow[i].dir* M_PI / 180));
		}
		else if (snow[i].dir > 180 and snow[i].dir <= 270) {
			snow[i].X += snow[i].speed * (sin(snow[i].dir* M_PI / 180));
			snow[i].Z += snow[i].speed * (cos(snow[i].dir* M_PI / 180));
			snow[i].Y += snow[i].speed * (sin(snow[i].dir* M_PI / 180));
		}
		else if (snow[i].dir > 270 and snow[i].dir <= 360) {
			snow[i].X += snow[i].speed * (sin(snow[i].dir* M_PI / 180));
			snow[i].Z += snow[i].speed * (-sin(snow[i].dir* M_PI / 180));
			snow[i].Y += snow[i].speed * (-cos(snow[i].dir* M_PI / 180));
		}

		snow_obj[i].load(projection, view);

		//За·Д
		glm::mat4 transMatrix = glm::mat4(1.0f);
		glm::mat4 scaleMatix = glm::mat4(1.0f);
		glm::mat4 myTransformeVector = glm::mat4(1.0f);


		transMatrix = glm::translate(transMatrix, glm::vec3(snow[i].X, snow[i].Y, snow[i].Z));
		scaleMatix = glm::scale(scaleMatix, glm::vec3(5.0f, 5.0f, 5.0f));

		myTransformeVector = transMatrix * scaleMatix;

		snowShader.setVec3("viewPos", 0.0, 45.0, 50);
		snowShader.setVec3("lightPos", glm::vec3(snow[i].X, snow[i].Y, snow[i].Z));
		snow_obj[i].setTransform(myTransformeVector);

		glm::vec3 lightColor = glm::vec3(color_random1, color_random2, color_random3);

		snowShader.setVec3("lightColor", lightColor);
		snow_obj[i].draw();

		snow[i].timer--;
	}
};