#ifndef QUAD_H
#define QUAD_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp>
#include "Face.h"
#include <iostream>

using namespace std;

class Quad
{
private:
	Face f1,f2;
	vec3 centerPosition;
public:
	Quad();
	~Quad();
	vec3 getCenterPosition();
	void setCenterPosition(vec3 p);
	Face& getFace1();
	Face& getFace2();
	void createFaces();
};

#endif // QUAD_H
