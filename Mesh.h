#ifndef MESH_H
#define MESH_H
#include "Quad.h"
#include <GL/glew.h>
#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Brush.h"


#define WIDTH 10
#define HEIGHT 10

class Mesh
{
private:
	Quad topMesh[HEIGHT] [WIDTH];
	GLuint VAOh,blendMapHandle;
	GLuint VBO[3];
	bool uploaded;
	vec3 position;
	void getVboArrays(Quad mesh[][WIDTH],vector<float> &verts, vector<float> &normals);
	int nrOfVertices;
	sf::Image blendMap;
	int blendmapIndecis[4];
	void updateBlendmapIndecis(int v);
	int nextEmptyBlendIndex;
	void increasePixelPaint(int i, int j, Brush b, int index,float distance);
	bool inCircle(float cx,float cy, float x, float y,float r);
public:
	Mesh();
	~Mesh();
	void uploadToGFX();
	void freeGFX();
	GLuint getVAOh();
	void setPosition(vec3 v);
	bool updateMesh(vector<Quad> polys);
	int getNrOfVertices();
	GLuint getBlendmapHandle();
	void updateGFXBlendmap();
	void paintBlendmap(float i, float j, Brush b);
	int *getBlendmapIndecis();
	void setBlendmapIndex(int i, int v);
	vec3 rayIntersectMeshTriangle(vec3 origin, vec3 direction);
};

#endif // MESH_H
