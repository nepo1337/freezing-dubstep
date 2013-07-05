#ifndef MESH_H
#define MESH_H
#include "Quad.h"
#include <GL/glew.h>
#include <vector>
#include <iostream>

#define WIDTH 10
#define HEIGHT 10

class Mesh
{
private:
	Quad topMesh[HEIGHT] [WIDTH];
	GLuint VAOh;
	GLuint VBOv,VBOn,VBOuv;
	bool uploaded;
	vec3 position;
	void getVboArrays(Quad mesh[][WIDTH],vector<float> &verts, vector<float> &normals);
	int nrOfVertices;
	
public:
	Mesh();
	~Mesh();
	void uploadToGFX();
	void freeGFX();
	GLuint getVAOh();
	void setPosition(vec3 v);
	bool updateMesh(vector<Quad> polys);
	int getNrOfVertices();
};

#endif // MESH_H
