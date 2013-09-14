#include "TextureSet.h"

TextureSet::TextureSet()
{
	this->path="";
	this->textureSetname="";
}
TextureSet::~TextureSet()
{
}
void TextureSet::create(string path, string tsn)
{
    this->path=path;
    this->textureSetname=tsn;
}
string TextureSet::getPath()
{
    return this->path;
}

string TextureSet::getTextureSetName()
{
    return this->textureSetname;
}
vector< GLuint > TextureSet::getTexHandles()
{
    return this->texHandels;
}

void TextureSet::addTexture(GLuint t,string name)
{
	this->textureNames.push_back(name);
	this->texHandels.push_back(t);
}
GLuint TextureSet::getTexHandle(int i)
{
	GLuint t=-1;
	if(i>=0&&i<this->texHandels.size())
	{
		t=this->texHandels[i];
	}
	return t;
}
GLuint TextureSet::getTexHandle(string s)
{
	GLuint t=-1;
	for(int i=0;i<this->textureNames.size()||t>-1;i++)
	{
		if(this->textureNames[i]==s)
			t=i;
	}
	return t;
}
void TextureSet::freeTextures()
{
	for(int i=0;i<texHandels.size();i++)
	{
		glDeleteTextures(this->texHandels.size(),&texHandels[0]);
	}
}

