#ifndef MESHDATA_H
#define MESHDATA_H
#include <GL/glew.h>
#include "Mesh.h"

namespace MeshData
{
	void setWidthHeight(int w, int h);
	void free();
	int getWidth();
	int getHeight();
	GLuint getVAOh(int i, int j);
	GLuint getBlendTexHandle(int i,int j);
	Mesh* getMesh(int i,int j);
}
#endif
