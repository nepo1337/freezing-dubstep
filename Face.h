#ifndef FACE_H
#define FACE_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp>

using namespace glm;

class Face
{
public:
	void calculateSurfaceNormal();
	vec3 surfaceNormal;
	vec3 v1,v2,v3;
	vec3 n1,n2,n3;
	Face();
	~Face();

};

#endif // FACE_H
