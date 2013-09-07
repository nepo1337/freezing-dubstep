#include "MeshHandler.h"

MeshHandler::MeshHandler()
{
	this->cam=0;
	this->modelMatrix=mat4(1.0f);
	this->drawWireframe=false;  

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
	
	this->meshShader.use();
	this->meshShader.setUniform("tex",2);
	this->meshShader.setUniform("drawWireframe",this->drawWireframe);
	glUseProgram(0);
	
	TextureSet t;
	t.create("textures/green","greenSet","grass_02.png","grass_07.png","dirt01.png","dirt_05.png");
	TextureHandler::addTextureSet(t);
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
		for(int i=0;i<MeshData::getHeight();i++)
		{
			for(int j=0;j<=MeshData::getWidth();j++)
			{
				glBindVertexArray(MeshData::getVAOh(i,j));
				glDrawArrays(GL_TRIANGLES,0,600);
			}
		}
		
		glUseProgram(0);
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
void MeshHandler::toggleWireframe()
{
	this->drawWireframe=!this->drawWireframe;
	this->meshShader.use();
	this->meshShader.setUniform("drawWireframe",this->drawWireframe);
	glUseProgram(0);
}
void MeshHandler::setWidthHeight(int w, int h)
{
	MeshData::setWidthHeight(w,h);
}


