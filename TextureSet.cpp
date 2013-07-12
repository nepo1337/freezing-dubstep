#include "TextureSet.h"

TextureSet::TextureSet()
{
    this->tex1=this->tex2=this->tex3=this->tex4=0;
    this->name1=this->name2=this->name3=this->name4="NONE";
}
TextureSet::~TextureSet()
{

}
void TextureSet::create(string path, string tsn, string n1, string n2, string n3, string n4)
{
    this->path=path;
    this->textureSetname=tsn;
    this->name1=n1;
    this->name2=n2;
    this->name3=n3;
    this->name4=n4;
}
string TextureSet::getPath()
{
    return this->path;
}
GLuint TextureSet::getTex1H()
{
    return this->tex1;
}
GLuint TextureSet::getTex2H()
{
    return this->tex2;
}
GLuint TextureSet::getTex3H()
{
    return this->tex3;
}
GLuint TextureSet::getTex4H()
{
    return this->tex4;
}
string TextureSet::getTextureSetName()
{
    return this->textureSetname;
}
vector< GLuint > TextureSet::getTexHandles()
{
    return this->texHandels;
}
string TextureSet::getTex1Name()
{
    return this->name1;
}
string TextureSet::getTex2Name()
{
    return this->name2;
}
string TextureSet::getTex3Name()
{
    return this->name3;
}
string TextureSet::getTex4Name()
{
    return this->name4;
}
void TextureSet::setTextureIDs(GLuint t1, GLuint t2, GLuint t3, GLuint t4)
{
    this->tex1=t1;
    this->tex2=t2;
    this->tex3=t3;
    this->tex4=t4;

    this->texHandels.push_back(this->tex1);
    this->texHandels.push_back(this->tex2);
    this->texHandels.push_back(this->tex3);
    this->texHandels.push_back(this->tex4);
}





