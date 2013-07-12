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
#include "TextureSet.h"
#include "TextureHandler.h"
#include "MeshData.h"

class MeshHandler
{
private:
	Camera *cam;
	GLSLProgram meshShader;
	mat4 modelMatrix;
	bool drawWireframe;
public:
	MeshHandler();
	~MeshHandler();
	void init();
	void draw();
	void setCamera(Camera *cam);
	void windowResizedUpdate();
	void toggleWireframe();
	void setWidthHeight(int w, int h);
};

#endif
