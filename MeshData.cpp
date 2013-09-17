#include "MeshData.h"

namespace MeshData
{
int width=0;
int height=0;
Mesh **mesh =0;
void free()
{
    //free up old mesh
    for(int i=0; i<height; i++)
    {
        for(int j=0; j<width; j++)
        {
            mesh[i][j].freeGFX();
        }
    }
    for(int i=0; i<height; i++)
    {
        delete[] mesh[i];
    }
    delete[] mesh;
}
void setWidthHeight(int w, int h)
{
    if(w>0&&h>0)
    {
        //free up old mesh
        for(int i=0; i<height; i++)
        {
            for(int j=0; j<width; j++)
            {
                mesh[i][j].freeGFX();
            }
        }
        for(int i=0; i<height; i++)
        {
            delete[] mesh[i];
        }
        delete[] mesh;

        //new mesh
        width=w;
        height=h;
        mesh=new Mesh*[height];
        for(int i=0; i<height; i++)
        {
            mesh[i]=new Mesh[width];
        }
        for(int i=0; i<height; i++)
        {
            for(int j=0; j<width; j++)
            {
                mesh[i][j].setPosition(vec3(j,0.0f,i));
                mesh[i][j].uploadToGFX();
            }
        }
    }
}

int getHeight()
{
    return height;
}
int getWidth()
{
    return width;
}
GLuint getVAOh(int i, int j)
{
    return mesh[i][j].getVAOh();
}
GLuint getBlendTexHandle(int i, int j)
{
	return mesh[i][j].getBlendmapHandle();
}
Mesh* getMesh(int i, int j)
{
	return &mesh[i][j];
}

}
