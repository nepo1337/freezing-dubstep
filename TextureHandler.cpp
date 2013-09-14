#include "TextureHandler.h"

namespace TextureHandler
{
	vector<TextureSet> textureSets;
	bool addTextureSet(TextureSet set)
	{
		bool valid=true;
		for(int i=0;i<textureSets.size();i++)
		{
			if(set.getTextureSetName()==textureSets[i].getTextureSetName())
				valid=false;
		}
		if(valid)
			textureSets.push_back(set);
		
		return valid;
	}

	TextureSet getTextureSet(int index)
	{
		TextureSet set = textureSets[0];
		if(index>=0&&index<=index)
			set=textureSets[index];
		return set;
	}
	TextureSet getTextureSet(string name)
	{
		TextureSet set = textureSets[0];
		for(int i=0;i<textureSets.size();i++)
		{
			if(textureSets[i].getTextureSetName()==name)
				set=textureSets[i];
		}
		return set;
	}


	GLuint uploadTextureGFX(sf::Image img)
	{
		GLuint handle;
		glGenTextures(1,&handle);
		glBindTexture(GL_TEXTURE_2D,handle);
		glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,img.getSize().x,img.getSize().y,0,GL_RGBA,GL_UNSIGNED_BYTE,img.getPixelsPtr());
		glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
		glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glGenerateMipmap( GL_TEXTURE_2D);
		
		return handle;
	}
	GLuint uploadSimpleTexNearest(sf::Image img)
	{
		glActiveTexture(GL_TEXTURE0);
		GLuint handle;
		glGenTextures(1,&handle);
		glBindTexture(GL_TEXTURE_2D,handle);
		glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,img.getSize().x,img.getSize().y,0,GL_RGBA,GL_UNSIGNED_BYTE,img.getPixelsPtr());
		glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
		
		return handle;
	}
	GLuint uploadSimpleTexLinear(sf::Image img)
	{
		glActiveTexture(GL_TEXTURE0);
		GLuint handle;
		glGenTextures(1,&handle);
		glBindTexture(GL_TEXTURE_2D,handle);
		glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,img.getSize().x,img.getSize().y,0,GL_RGBA,GL_UNSIGNED_BYTE,img.getPixelsPtr());
		glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		
		return handle;
	}

}

