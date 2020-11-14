#ifndef LOADOBJ_H
#define LOADOBJ_H

#include "shader.h"
#include <vector>
#include <cstdlib>
#include <ctime>


class loadOBJ {
private:
	std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
	std::vector< glm::vec3 > temp_vertices;
	std::vector< glm::vec3 > temp_uvs;
	std::vector< glm::vec3 > temp_normals;
	std::vector< glm::vec3 > vertices;
	std::vector< glm::vec3 > uvs;
	std::vector< glm::vec3 > normals; // 지금은 안쓸거에요. 
	GLuint lightbuffer;
	GLuint colorbuffer;
	GLuint vertexbuffer;

	const char * objPath; 
	unsigned int ourShaderID;

	void madeOBJ(const char * path, std::vector < glm::vec3 > & out_vertices, std::vector < glm::vec3 > & out_uvs, std::vector < glm::vec3 > & out_normals)
	{
		FILE * file;

		fopen_s(&file, path, "r");
		if (file == NULL) {
			printf("%s : Impossible to open the file !\n",path);
		}
		while (1) {
			char lineHeader[128];
			// read the first word of the line
			int res = fscanf_s(file, "%s", lineHeader, sizeof(lineHeader));
			if (res == EOF)
				break; // EOF = End Of File. Quit the loop.

			// else : parse lineHeader

			if (strcmp(lineHeader, "v") == 0) {
				glm::vec3 vertex;
				fscanf_s(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
				temp_vertices.push_back(vertex);
			}
			else if (strcmp(lineHeader, "vn") == 0) {
				glm::vec3 normal;
				fscanf_s(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
				temp_normals.push_back(normal);
			}
			else if (strcmp(lineHeader, "vt") == 0) {
				glm::vec3 uv;
				fscanf_s(file, "%f %f %f\n", &uv.x, &uv.y, &uv.z);
				temp_uvs.push_back(uv);
			}
			else if (strcmp(lineHeader, "f") == 0) {
				std::string vertex1, vertex2, vertex3;
				unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
				int matches = fscanf_s(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
				if (matches != 9) {
					printf("File can't be read by our simple parser : ( Try exporting with other options\n");
				}
				vertexIndices.push_back(vertexIndex[0]);
				vertexIndices.push_back(vertexIndex[1]);
				vertexIndices.push_back(vertexIndex[2]);
				uvIndices.push_back(uvIndex[0]);
				uvIndices.push_back(uvIndex[1]);
				uvIndices.push_back(uvIndex[2]);
				normalIndices.push_back(normalIndex[0]);
				normalIndices.push_back(normalIndex[1]);
				normalIndices.push_back(normalIndex[2]);
			}
		}
		// For each vertex of each triangle  (각 삼각형의 각 꼭지점을 순회합니다. ) 
		for (unsigned int i = 0; i < vertexIndices.size(); i++) {
			unsigned int vertexIndex = vertexIndices[i];
			unsigned int uvIndex = uvIndices[i];
			unsigned int normalIndex = normalIndices[i];

			glm::vec3 vertex = temp_vertices[vertexIndex - 1];
			glm::vec3 uv = temp_uvs[uvIndex - 1];
			glm::vec3 normal = temp_normals[normalIndex - 1];

			out_vertices.push_back(vertex);
			out_uvs.push_back(uv);
			out_normals.push_back(normal);
		}
		fclose(file);
	}
public:
	loadOBJ(){}

	loadOBJ(const char * obj, unsigned int ID)
	{
		objPath = obj;
		ourShaderID = ID;
		madeOBJ(objPath, vertices, uvs, normals);
	}

	void load(glm::mat4 projection, glm::mat4 view);

	void setTransform(glm::mat4 Transforme);

	void draw();
};


#endif