#include "Quad.h"

Quad::Quad()
{
    f1=Face();
    f2=Face();
    centerPosition=vec3(0.0f);
    this->height=0;
}

Quad::~Quad()
{
}

void Quad::setCenterPosition(vec3 p)
{
    this->centerPosition=p;
}
vec3 Quad::getCenterPosition()
{
    return this->centerPosition;
}

void Quad::createFaces()
{
    //face 1, calculated from a center position that the poly has (always left faced)

    this->f1.v1.x = this->centerPosition.x -0.5;
    this->f1.v1.y = 0.0f;
    this->f1.v1.z = this->centerPosition.z -0.5;

    this->f1.v2.x = this->centerPosition.x -0.5;
    this->f1.v2.y = 0.0f;
    this->f1.v2.z = this->centerPosition.z +0.5;

    this->f1.v3.x = this->centerPosition.x +0.5;
    this->f1.v3.y = 0.0f;
    this->f1.v3.z = this->centerPosition.z -0.5;

    //face 2
    this->f2.v1.x = this->centerPosition.x +0.5;
    this->f2.v1.y = 0.0f;
    this->f2.v1.z = this->centerPosition.z +0.5;

    this->f2.v2.x = this->centerPosition.x +0.5;
    this->f2.v2.y = 0.0f;
    this->f2.v2.z = this->centerPosition.z -0.5;

    this->f2.v3.x = this->centerPosition.x -0.5;
    this->f2.v3.y = 0.0f;
    this->f2.v3.z = this->centerPosition.z +0.5;
}

Face& Quad::getFace1()
{
    return this->f1;
}
Face& Quad::getFace2()
{
    return this->f2;
}
float Quad::getHeight()
{
	return this->height;
}
void Quad::setHeight(float h)
{
	this->height=h;
	this->f1.v1.y = this->height;
	this->f1.v2.y = this->height;
	this->f1.v3.y = this->height;
	this->f2.v1.y = this->height;
	this->f2.v2.y = this->height;
	this->f2.v3.y = this->height;
}
void Quad::createRamp(Orientation::Orientations o,float h)
{
	this->f1.v1.y = this->height;
	this->f1.v2.y = this->height;
	this->f1.v3.y = this->height;
	this->f2.v1.y = this->height;
	this->f2.v2.y = this->height;
	this->f2.v3.y = this->height;
	switch(o)
	{
		case Orientation::NORTH:
			this->f1.v2.y = this->height+h;
			this->f2.v1.y = this->height+h;
			this->f2.v3.y = this->height+h;
			break;
		case Orientation::SOUTH:
			this->f1.v1.y = this->height+h;
			this->f1.v3.y = this->height+h;
			this->f2.v2.y = this->height+h;
			break;
		case Orientation::WEST:
			this->f1.v1.y = this->height+h;
			this->f1.v2.y = this->height+h;
			this->f2.v3.y = this->height+h;
			break;
		case Orientation::EAST:
			this->f1.v3.y = this->height+h;
			this->f2.v1.y = this->height+h;
			this->f2.v2.y = this->height+h;
			break;
	}
}

