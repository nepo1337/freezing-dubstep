#include "MeshHandler.h"

MeshHandler::MeshHandler()
{
	this->cam=0;
	this->modelMatrix=mat4(1.0f);
	this->drawWireframe=false;  

}
MeshHandler::~MeshHandler()
{
	t.freeTextures();
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
	this->meshShader.setUniform("tex",1);
	this->meshShader.setUniform("drawWireframe",this->drawWireframe);
	glUseProgram(0);
	
	
	t.create("textures/green","greenSet");
	sf::Image img;
	string fn=t.getPath()+"/grass02.png";
	img.loadFromFile(fn);
	glActiveTexture(GL_TEXTURE0);
	t.addTexture(TextureHandler::uploadTextureGFX(img),"grass02");
	fn=t.getPath()+"/grass07.png";
	img.loadFromFile(fn);
	glActiveTexture(GL_TEXTURE1);
	t.addTexture(TextureHandler::uploadTextureGFX(img),"grass07");
	fn=t.getPath()+"/dirt01.png";
	img.loadFromFile(fn);
	glActiveTexture(GL_TEXTURE2);
	t.addTexture(TextureHandler::uploadTextureGFX(img),"dirt01");
	fn=t.getPath()+"/dirt05.png";
	img.loadFromFile(fn);
	glActiveTexture(GL_TEXTURE3);
	t.addTexture(TextureHandler::uploadTextureGFX(img),"dirt05");
	fn=t.getPath()+"/gravel01.png";
	img.loadFromFile(fn);
	glActiveTexture(GL_TEXTURE3);
	t.addTexture(TextureHandler::uploadTextureGFX(img),"gravel01");
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


