
#include "Mesh.h"
#include "TextureHandler.h"

Mesh::Mesh()
{
    this->VAOh=0;
    this->VBO[0]=this->VBO[1]=this->VBO[2]=0;
    this->uploaded=false;
    this->position=vec3(0.0f);
    this->nrOfVertices=600;
    this->blendMapHandle=0;
    this->blendmapIndecis[0]=0;
    this->blendmapIndecis[1]=0;
    this->blendmapIndecis[2]=0;
    this->blendmapIndecis[3]=0;
    this->nextEmptyBlendIndex=1;
}

Mesh::~Mesh()
{
}
int* Mesh::getBlendmapIndecis()
{
	return this->blendmapIndecis;
}
void Mesh::setBlendmapIndex(int i, int v)
{
	this->blendmapIndecis[i]=v;
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
	this->blendMap.create(32,32,sf::Color(255,0,0,0));
	
	this->updateGFXBlendmap();
    }
}

//sets which texture to use.
//a given 10x10 quad can only ahve 4 textures, if a 5th texture is to be drawn,
//the first is replaced with the current (v)
void Mesh::updateBlendmapIndecis(int v)
{
	bool found=false;
	for(int i=0;i<4;i++)
	{
		if(this->blendmapIndecis[i]==v)
		{
			found=true;
		}
	}
	if(!found)
	{
		this->blendmapIndecis[this->nextEmptyBlendIndex]=v;
		this->nextEmptyBlendIndex++;
		if(this->nextEmptyBlendIndex>3)
			this->nextEmptyBlendIndex=0;
	}
}

void Mesh::paintBlendmap(float i, float j, Brush b)
{
	this->updateBlendmapIndecis(b.getBrushTexture());
	
	//looks what index the texture should have in the blendmap
	int index=-1;
	for(int f=0;f<4&&index<0;f++)
	{
		if(this->blendmapIndecis[f]==b.getBrushTexture())
		{
			index=f;
		}
	}
	//updates the blendmap based on what texture is used
	
	int lk=i*3.2-b.getRadius();
	if(lk<0)
		lk=0;
	int tk =i*3.2+b.getRadius();
	if(tk>32)
		tk=32;
	int ll=j*3.2-b.getRadius();
	if(ll<0)
		ll=0;
	int tl=j*3.2+b.getRadius();
	if(tl>32)
		tl=32;
	for(int k=lk;k<tk;k++)
	{
		for(int l=ll;l<tl;l++)
		{

			float dist = sqrt(((i*3.2)-k)*((i*3.2)-k)+((j*3.2)-l)*((j*3.2)-l));
			this->increasePixelPaint(k,l,b, index,dist);

		}
	}


	this->updateGFXBlendmap();
}
void Mesh::increasePixelPaint(int i, int j, Brush b, int index, float distance)
{
	float sum=0;
	sf::Color pix = this->blendMap.getPixel(i,j);
	int pixBlends[]=
	{
		pix.r,pix.g,pix.b,pix.a,
	};
	float t=0;
	float r=0;
	if(b.getBrushType()==BrushType::CIRCLE)
	{
		t = std::min(distance,b.getRadius());
		r = 1-(t/b.getRadius());
	}
	if(b.getBrushType()==BrushType::SQUARE)
	{
		r=0.5;
	}
	
	pixBlends[index]+=r*20;

	sum=pixBlends[0]+pixBlends[1]+pixBlends[2]+pixBlends[3];
	pix.r=(pixBlends[0]/sum)*255;
	pix.g=(pixBlends[1]/sum)*255;
	pix.b=(pixBlends[2]/sum)*255;
	pix.a=(pixBlends[3]/sum)*255;
	this->blendMap.setPixel(i,j,pix);
}
bool Mesh::inCircle(float cx, float cy, float x, float y,float r)
{
	float dist;
	dist = (cx-x)*(cx-x)+(cy-y)*(cy-y);
	return dist<r*r;
}

void Mesh::updateGFXBlendmap()
{
	glActiveTexture(GL_TEXTURE0);
	glDeleteTextures(1,&this->blendMapHandle);
	this->blendMapHandle = TextureHandler::uploadSimpleTexNearest(this->blendMap);
}

GLuint Mesh::getBlendmapHandle()
{
	return this->blendMapHandle;
}
void Mesh::freeGFX()
{
    glDeleteBuffers(3,this->VBO);
    glDeleteVertexArrays(1,&this->VAOh);
    glDeleteTextures(1,&this->blendMapHandle);
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

vec3 Mesh::rayIntersectMeshTriangle(vec3 origin, vec3 direction)
{
	bool pass=true;
	bool found=false;
	vec3 hit;
	for(int i=0;i<HEIGHT&&!found;i++)
	{
		for(int j=0;j<WIDTH&&!found;j++)
		{
			//for saving the closest target
			float lowestY=999999.0f;

			pass=true;
			vec3 p0=this->topMesh[i][j].getFace1().v1;
			vec3 p1=this->topMesh[i][j].getFace1().v2;
			vec3 p2=this->topMesh[i][j].getFace1().v3;
			
			vec3 e1 = p1-p0;
			vec3 e2 = p2-p0;
			vec3 q = cross(direction,e2);
			float a = dot(e1,q);
			
			if(a>-0.00000001&&a<0.00000001)
			{
				pass=false;
			}
			if(pass)
			{
				float f = 1/a;
				vec3 s = origin-p0;
				float u = f*dot(s,q);
				if(u<0.0)
				{
					pass=false;
				}
				if(pass)
				{
					vec3 r = cross(s,e1);
					float v = f*dot(direction,r);
					if(v<0.0 || u+v>1.0)
					{
						pass=false;
					}
					if(pass)
					{
						float t=f*dot(e2,r);
						if(t<lowestY)
						{
							hit=vec3(v+j,t,u+i);
						}
						found=true;
					}
				}
			}
			
			if(!found)
			{
				pass=true;
			vec3 p0=this->topMesh[i][j].getFace2().v1;
			vec3 p1=this->topMesh[i][j].getFace2().v2;
			vec3 p2=this->topMesh[i][j].getFace2().v3;
			
			vec3 e1 = p1-p0;
			vec3 e2 = p2-p0;
			vec3 q = cross(direction,e2);
			float a = dot(e1,q);
			
			if(a>-0.00000001&&a<0.00000001)
			{
				pass=false;
			}
			if(pass)
			{
				float f = 1/a;
				vec3 s = origin-p0;
				float u = f*dot(s,q);
				if(u<0.0)
				{
					pass=false;
				}
				if(pass)
				{
					vec3 r = cross(s,e1);
					float v = f*dot(direction,r);
					if(v<0.0 || u+v>1.0)
					{
						pass=false;
					}
					if(pass)
					{
						float t=f*dot(e2,r);
						if(t<lowestY)
						{
							hit=vec3(1-v+j,t,1-u+i);
						}
						found=true;
					}
				}
			}
			}
		}
	}
	if(!found)
		hit=vec3(-1,-1,-1);
	return hit;
}