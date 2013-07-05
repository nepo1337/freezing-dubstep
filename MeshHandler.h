#ifndef MESHHANDLER_H
#define MESHHANDLER_H
#include <GL/glew.h>
#include "Camera.h"
#include "Mesh.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp>
#include "GLSLProgram.h"
#include <iostream>
#include <SFML/Graphics.hpp>

class MeshHandler
{
private:
	Camera *cam;
	GLSLProgram meshShader;
	Mesh **mesh;
	mat4 modelMatrix;
	int width, height;
	GLuint uploadTextureGFX(sf::Image img);
	sf::Image btex;
	GLuint texH;
public:
	MeshHandler();
	~MeshHandler();
	void init();
	void setWidthHeight(int width, int height);
	void draw();
	void setCamera(Camera *cam);
	void windowResizedUpdate();
};

#endif