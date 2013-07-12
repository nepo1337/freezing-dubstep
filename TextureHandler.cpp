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
		{
			sf::Image img,img2,img3,img4;
			valid = img.loadFromFile(set.getPath()+"/"+set.getTex1Name())&&img2.loadFromFile(set.getPath()+"/"+set.getTex2Name())&&img3.loadFromFile(set.getPath()+"/"+set.getTex3Name())&&img4.loadFromFile(set.getPath()+"/"+set.getTex4Name());
			if(valid)
			{
				GLuint t1,t2,t3,t4;
				glActiveTexture(GL_TEXTURE1);
				t1=uploadTextureGFX(img);
				glActiveTexture(GL_TEXTURE2);
				t2=uploadTextureGFX(img2);
				glActiveTexture(GL_TEXTURE3);
				t3=uploadTextureGFX(img3);
				glActiveTexture(GL_TEXTURE4);
				t4=uploadTextureGFX(img4);
				valid =t1&&t2&&t3&&t4;
				if(valid)
					set.setTextureIDs(t1,t2,t3,t4);
				textureSets.push_back(set);
			}
		}
		return valid;
	}
	void freeOnceInEndOfMain()
	{
		for(int i=0;i<textureSets.size();i++)
		{
			glDeleteTextures(4,&textureSets[i].getTexHandles().front());
		}
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
}

