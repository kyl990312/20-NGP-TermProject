#include "shader.h"
#include "loadObj.h"


void loadOBJ::load(glm::mat4 projection, glm::mat4 view)
{
	GLuint VertexArrayID;

	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);
	
	//madeOBJ(objPath, vertices, uvs, normals);

	// 이것이 우리의 버텍스 버퍼를 가리킵니다.
	// 버퍼를 하나 생성합니다. vertexbuffer 에 결과 식별자를 넣습니다
	glGenBuffers(1, &vertexbuffer);
	// 아래의 명령어들은 우리의 "vertexbuffer" 버퍼에 대해서 다룰겁니다
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	// 우리의 버텍스들을 OpenGL로 넘겨줍니다
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

	// 버퍼의 첫번째 속성값(attribute) : 버텍스들
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(
		0,                  // 0번째 속성(attribute). 0 이 될 특별한 이유는 없지만, 쉐이더의 레이아웃(layout)와 반드시 맞추어야 합니다.
		3,                  // 크기(size)
		GL_FLOAT,           // 타입(type)
		GL_FALSE,           // 정규화(normalized)
		0,                  // 다음 요소 까지 간격(stride)
		(void*)0            // 배열 버퍼의 오프셋(offset; 옮기는 값)
	);

	glGenBuffers(1, &colorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec3), &uvs[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glVertexAttribPointer(
		1,                                // attribute
		3,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);

	glGenBuffers(1, &lightbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, lightbuffer);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, lightbuffer);
	glVertexAttribPointer(
		2,                                // attribute
		3,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);

	unsigned int projectionLocation = glGetUniformLocation(ourShaderID, "projectionTransform");
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);


	unsigned int viewLocation = glGetUniformLocation(ourShaderID, "viewTransform");
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);
}


void loadOBJ::setTransform(glm::mat4 Transforme)
{

	int lightPosLocation = glGetUniformLocation(ourShaderID, "lightPos"); //--- lightPos 값전달 
	glUniform3f (lightPosLocation, 0, 800, 2000);

	int lightColorLocation = glGetUniformLocation(ourShaderID, "lightColor"); //--- lightColor값전달 
	glUniform3f (lightColorLocation, 1.0, 1.0, 0.9);

	int lightViewLocation = glGetUniformLocation(ourShaderID, "viewPos");
	glUniform3f(lightViewLocation, 0.0, 45.0, 50);

	unsigned int transformLocation = glGetUniformLocation(ourShaderID, "transform");
	glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(Transforme));
}


void loadOBJ::draw()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawArrays(GL_TRIANGLES, 0, vertexIndices.size());

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	glDeleteBuffers(1, &lightbuffer);
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &colorbuffer);
}