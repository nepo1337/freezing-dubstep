#include "Face.h"

Face::Face()
{
	this->v1=vec3(0.0f);
	this->v2=vec3(0.0f);
	this->v3=vec3(0.0f);
	this->n1=vec3(0.0f,1.0f,0.0f);
	this->n2=vec3(0.0f,1.0f,0.0f);
	this->n3=vec3(0.0f,1.0f,0.0f);
	this->surfaceNormal=vec3(0.0f,1.0f,0.0f);
}

Face::~Face()
{
}

void Face::calculateSurfaceNormal()
{
	this->surfaceNormal=(glm::cross(this->v2-this->v1,this->v3-this->v1));
}