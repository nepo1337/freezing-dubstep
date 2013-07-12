
#include "Mesh.h"

Mesh::Mesh()
{
    this->VAOh=0;
    this->VBO[0]=this->VBO[1]=this->VBO[2]=0;
    this->uploaded=false;
    this->position=vec3(0.0f);
    this->nrOfVertices=600;
}

Mesh::~Mesh()
{
}

void Mesh::uploadToGFX()
{
    float textureScale=0.1f;
    if(!this->uploaded)
    {
        //vector containing the local data
        std::vector<float> verts;
        std::vector<float> normals;
        std::vector<float> uvs;

        //creates the faces
        for(int i=0; i<HEIGHT; i++)
        {
            for(int j=0; j<WIDTH; j++)
            {
                this->topMesh[i][j].setCenterPosition(vec3(this->position.x*WIDTH+j,0.0f,this->position.z*HEIGHT+i));
                this->topMesh[i][j].createFaces();

                //uvs
                uvs.push_back(j*textureScale);
                uvs.push_back(i*textureScale);

                uvs.push_back(j*textureScale);
                uvs.push_back(i*textureScale+textureScale);

                uvs.push_back(j*textureScale+textureScale);
                uvs.push_back(i*textureScale);

                uvs.push_back(j*textureScale+textureScale);
                uvs.push_back(i*textureScale+textureScale);

                uvs.push_back(j*textureScale+textureScale);
                uvs.push_back(i*textureScale);

                uvs.push_back(j*textureScale);
                uvs.push_back(i*textureScale+textureScale);
            }
        }

        //fills the vertex vector and normal vector with the values from the faces
        this->getVboArrays(this->topMesh,verts,normals);

        glGenVertexArrays(1,&this->VAOh);
        glBindVertexArray(this->VAOh);

        //vertex buffer
        glGenBuffers(3,this->VBO);
        glBindBuffer(GL_ARRAY_BUFFER,this->VBO[0]);
        glBufferData(GL_ARRAY_BUFFER,sizeof(float)*verts.size(),&verts.front(),GL_STATIC_DRAW);

        //normal buffer
        glBindBuffer(GL_ARRAY_BUFFER,this->VBO[1]);
        glBufferData(GL_ARRAY_BUFFER,sizeof(float)*normals.size(),&normals.front(),GL_STATIC_DRAW);

        //uv buffer
        glBindBuffer(GL_ARRAY_BUFFER,this->VBO[2]);
        glBufferData(GL_ARRAY_BUFFER,sizeof(float)*uvs.size(),&uvs.front(),GL_STATIC_DRAW);


        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);

        glBindBuffer(GL_ARRAY_BUFFER, this->VBO[0]);
        glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,NULL);

        glBindBuffer(GL_ARRAY_BUFFER, this->VBO[1]);
        glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,0,NULL);

        glBindBuffer(GL_ARRAY_BUFFER, this->VBO[2]);
        glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,0,NULL);
        glBindVertexArray(0);
        this->uploaded=true;
    }
}

void Mesh::freeGFX()
{
    glDeleteBuffers(3,this->VBO);
    glDeleteVertexArrays(1,&this->VAOh);
}


GLuint Mesh::getVAOh()
{
    return this->VAOh;
}
void Mesh::setPosition(vec3 v)
{
    this->position=v;
}

void Mesh::getVboArrays(Quad mesh[][WIDTH],vector<float> &verts, vector<float> &normals)
{
    for(int i=0; i<HEIGHT; i++)
    {
        for(int j=0; j<WIDTH; j++)
        {

            //1st face
            verts.push_back(mesh[i][j].getFace1().v1.x);
            verts.push_back(mesh[i][j].getFace1().v1.y);
            verts.push_back(mesh[i][j].getFace1().v1.z);
            normals.push_back(mesh[i][j].getFace1().n1.x);
            normals.push_back(mesh[i][j].getFace1().n1.y);
            normals.push_back(mesh[i][j].getFace1().n1.z);

            verts.push_back(mesh[i][j].getFace1().v2.x);
            verts.push_back(mesh[i][j].getFace1().v2.y);
            verts.push_back(mesh[i][j].getFace1().v2.z);
            normals.push_back(mesh[i][j].getFace1().n2.x);
            normals.push_back(mesh[i][j].getFace1().n2.y);
            normals.push_back(mesh[i][j].getFace1().n2.z);

            verts.push_back(mesh[i][j].getFace1().v3.x);
            verts.push_back(mesh[i][j].getFace1().v3.y);
            verts.push_back(mesh[i][j].getFace1().v3.z);
            normals.push_back(mesh[i][j].getFace1().n3.x);
            normals.push_back(mesh[i][j].getFace1().n3.y);
            normals.push_back(mesh[i][j].getFace1().n3.z);


            //2nd face
            verts.push_back(mesh[i][j].getFace2().v1.x);
            verts.push_back(mesh[i][j].getFace2().v1.y);
            verts.push_back(mesh[i][j].getFace2().v1.z);
            normals.push_back(mesh[i][j].getFace2().n1.x);
            normals.push_back(mesh[i][j].getFace2().n1.y);
            normals.push_back(mesh[i][j].getFace2().n1.z);

            verts.push_back(mesh[i][j].getFace2().v2.x);
            verts.push_back(mesh[i][j].getFace2().v2.y);
            verts.push_back(mesh[i][j].getFace2().v2.z);
            normals.push_back(mesh[i][j].getFace2().n2.x);
            normals.push_back(mesh[i][j].getFace2().n2.y);
            normals.push_back(mesh[i][j].getFace2().n2.z);

            verts.push_back(mesh[i][j].getFace2().v3.x);
            verts.push_back(mesh[i][j].getFace2().v3.y);
            verts.push_back(mesh[i][j].getFace2().v3.z);
            normals.push_back(mesh[i][j].getFace2().n3.x);
            normals.push_back(mesh[i][j].getFace2().n3.y);
            normals.push_back(mesh[i][j].getFace2().n3.z);

        }
    }

}
bool Mesh::updateMesh(vector<Quad> polys)
{
    if(this->uploaded)
    {
        int c=0;
        for(int i=0; i<HEIGHT; i++)
        {
            for(int j=0; j<WIDTH; j++)
            {
                this->topMesh[i][j]=polys[c];
                c++;
            }
        }
        vector<float> verts;
        vector<float> normals;

        this->getVboArrays(this->topMesh,verts,normals);
        this->nrOfVertices=verts.size()/3;
        /*
        glBindBuffer(GL_ARRAY_BUFFER, this->VBOv);
        glBufferSubData(GL_ARRAY_BUFFER,0,sizeof(float)*verts.size(),&verts.front());
        glBindBuffer(GL_ARRAY_BUFFER, this->VBOn);
        glBufferSubData(GL_ARRAY_BUFFER,0,sizeof(float)*normals.size(),&normals.front());
        */
    }
    return this->uploaded;
}

int Mesh::getNrOfVertices()
{
    return this->nrOfVertices;
}
