#include "MeshHandler.h"

MeshHandler::MeshHandler()
{
	this->cam=0;
	this->mesh=0;
	this->width=this->height=0;
	this->modelMatrix=mat4(1.0f);
  

}
MeshHandler::~MeshHandler()
{

}
void MeshHandler::init()
{
	this->meshShader.compileShaderFromFile("terrWire.vsh",GLSLShader::VERTEX);
	cout<<this->meshShader.log()<<endl;
	this->meshShader.compileShaderFromFile("terrWire.fsh",GLSLShader::FRAGMENT);
	cout<<this->meshShader.log()<<endl;
	this->meshShader.compileShaderFromFile("terrWire.gsh",GLSLShader::GEOMETRY);
	cout<<this->meshShader.log()<<endl;
	this->meshShader.bindAttribLocation(0,"vertexPosition");
	this->meshShader.bindAttribLocation(1,"vertexNormal");
	this->meshShader.bindAttribLocation(2,"vertexUV");
	
	this->meshShader.link();
	cout<<this->meshShader.log()<<endl;
	
	btex.loadFromFile("textures/grass.png");
	glActiveTexture(GL_TEXTURE0);
	this->texH = this->uploadTextureGFX(this->btex);
	this->meshShader.use();
	this->meshShader.setUniform("tex",0);
	this->meshShader.setUniform("drawWireframe",true);;
}

void MeshHandler::setCamera(Camera* cam)
{
	this->cam=cam;
}
void MeshHandler::draw()
{
	if(this->cam)
	{
		//set upp matrices and uniforms
		mat4 mvp = cam->getCombinedVPMatrix();
		this->meshShader.use();
		this->meshShader.setUniform("viewMatrix",cam->getViewMatrix());
		this->meshShader.setUniform("modelMatrix",this->modelMatrix);
		this->meshShader.setUniform("normalMatrix",mat3(this->modelMatrix));
		this->meshShader.setUniform("MVP",cam->getCombinedVPMatrix());

		//draw
		for(int i=0;i<this->height;i++)
		{
			for(int j=0;j<=this->width;j++)
			{
				glBindVertexArray(this->mesh[i][i].getVAOh());
				glDrawArrays(GL_TRIANGLES,0,this->mesh[i][j].getNrOfVertices());
			}
		}
		glBindVertexArray(0);
		glUseProgram(0);
	}
}
void MeshHandler::setWidthHeight(int width, int height)
{
	if(width>0&&height>0)
	{
		//free up old mesh
		for(int i=0;i<this->height;i++)
		{
			for(int j=0;j<this->width;j++)
			{
				this->mesh[i][j].freeGFX();
			}
		}
		for(int i=0;i<this->height;i++)
		{
			delete[] this->mesh[i];
		}
		delete[] this->mesh;
		
		//new mesh
		this->width=width;
		this->height=height;
		this->mesh=new Mesh*[this->height];
		for(int i=0;i<this->height;i++)
		{
			this->mesh[i]=new Mesh[this->width];
		}
		for(int i=0;i<this->height;i++)
		{
			for(int j=0;j<this->width;j++)
			{
				this->mesh[i][j].setPosition(vec3(j,0.0f,i));
				this->mesh[i][j].uploadToGFX();
			}
		}
	}
}
void MeshHandler::windowResizedUpdate()
{
	if(this->cam)
	{
		this->meshShader.use();
		this->meshShader.setUniform("viewportMatrix",cam->getViewportMatrix());
		this->meshShader.setUniform("projectionMatrix",cam->getProjectionMatrix());
		glUseProgram(0);
	}
}
GLuint MeshHandler::uploadTextureGFX(sf::Image img)
{
	GLuint handle;
	glGenTextures(1,&handle);
	glBindTexture(GL_TEXTURE_2D,handle);
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,img.getSize().x,img.getSize().y,0,GL_RGBA,GL_UNSIGNED_BYTE,img.getPixelsPtr());
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR  );
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//glGenerateMipmap( GL_TEXTURE_2D);
	
	return handle;
}