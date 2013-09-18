#ifndef QUAD_H
#define QUAD_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp>
#include "Face.h"
#include <iostream>

using namespace std;

namespace Orientation
{
	enum Orientations
	{
		NORTH,SOUTH,WEST,EAST
	};
};
class Quad
{
private:
	Face f1,f2;
	vec3 centerPosition;
	float height;
public:
	Quad();
	~Quad();
	vec3 getCenterPosition();
	void setCenterPosition(vec3 p);
	Face& getFace1();
	Face& getFace2();
	void createFaces();
	float getHeight();
	void setHeight(float h);
	void createRamp(Orientation::Orientations o,float h);
};

#endif // QUAD_H
