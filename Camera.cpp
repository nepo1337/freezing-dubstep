#include "Camera.h"

#define PI 3.14159265

Camera::Camera()
{
    this->eye=vec3(0.0f,0.0f,0.0f);
    this->lookat=vec3(1.0f,0.0f,1.0f);
    this->up=vec3(0.0f,1.0f,0.0f);
    this->viewMatrix=mat4(1.0f);
    this->rotx=0;
    this->roty=0;
    this->rotz=80;
    this->distance=5;

    this->eye.x=sin(rotz*PI/180)*sin(roty*PI/180)*this->distance+this->lookat.x;
    this->eye.y=cos(rotz*PI/180)*this->distance+this->lookat.y;
    this->eye.z=sin(rotz*PI/180)*cos(roty*PI/180)*this->distance+this->lookat.z;
    this->calcViewMatrix();
    this->updateProjectionMatrix(2,2);
    
    this->wHeight=0;
    this->wWidth=0;
}

Camera::~Camera()
{
}
void Camera::calcViewMatrix()
{
    this->viewMatrix=glm::lookAt(eye,lookat,up);
}
mat4 Camera::getViewMatrix()
{
    return this->viewMatrix;
}

vec3 Camera::getPos()
{
    return this->eye;
}

//*0.1 represents the speed, as the direction gets normalized, then scaled
void Camera::moveForeward(float a)
{
    vec3 dir= ((this->eye-this->lookat));
    vec3 dirMoved=normalize(vec3(dir.x,0,dir.z))*-a;
    this->eye+=dirMoved;
    this->lookat+=dirMoved;
    this->calcViewMatrix();
}
void Camera::moveBackward(float a)
{
    vec3 dir= ((this->eye-this->lookat));
    vec3 dirMoved=normalize(vec3(dir.x,0,dir.z))*a;
    this->eye+=dirMoved;
    this->lookat+=dirMoved;
    this->calcViewMatrix();
}
void Camera::strafeLeft(float a)
{
    vec3 dir= ((this->eye-this->lookat));
    vec3 dirMoved=normalize(vec3(dir.x,0,dir.z))*a;
    vec3 crossed = cross(dirMoved,vec3(0.0,1.0,0.0));
    this->eye+=crossed;
    this->lookat+=crossed;
    this->calcViewMatrix();
}
void Camera::strafeRight(float a)
{
    vec3 dir= ((this->eye-this->lookat));
    vec3 dirMoved=normalize(vec3(dir.x,0,dir.z))*-a;
    vec3 crossed = cross(dirMoved,vec3(0.0,1.0,0.0));
    this->eye+=crossed;
    this->lookat+=crossed;
    this->calcViewMatrix();
}
void Camera::zoomIn(float a)
{
    if(length(this->eye-this->lookat)-a>0.5)
    {
        this->distance-=a;
        //vec3 dir= normalize((this->eye-this->lookat));
        //if(this->eye.y-dir.y*a>0.4f)
        //this->eye+=this->distance;

        this->eye.x=sin(rotz*PI/180)*sin(roty*PI/180)*this->distance+this->lookat.x;
        this->eye.y=cos(rotz*PI/180)*this->distance+this->lookat.y;
        this->eye.z=sin(rotz*PI/180)*cos(roty*PI/180)*this->distance+this->lookat.z;

        this->calcViewMatrix();
    }
}
void Camera::zoomOut(float a)
{
    if(length(this->eye-this->lookat)+a>0.5)
    {
        this->distance+=a;
        //vec3 dir= normalize((this->eye-this->lookat));
        //this->eye+=this->distance;

        this->eye.x=sin(rotz*PI/180)*sin(roty*PI/180)*this->distance+this->lookat.x;
        this->eye.y=cos(rotz*PI/180)*this->distance+this->lookat.y;
        this->eye.z=sin(rotz*PI/180)*cos(roty*PI/180)*this->distance+this->lookat.z;

        this->calcViewMatrix();
    }
}
void Camera::rotateLeft(float deg)
{
    this->roty+=deg;
    this->eye.x=sin(rotz*PI/180)*sin(roty*PI/180)*this->distance+this->lookat.x;
    this->eye.y=cos(rotz*PI/180)*this->distance+this->lookat.y;
    this->eye.z=sin(rotz*PI/180)*cos(roty*PI/180)*this->distance+this->lookat.z;
    this->calcViewMatrix();
    /*
    //calculates a vector for rotating around the lookat point
    vec3 dir= ((this->eye-this->lookat));
    mat4 rot(1.0f);
    rot*=scale(dir);
    rot*=rotate(deg*-0.2f,vec3(0,1,0));

    vec4 t(1.0);
    t=t*rot;
    vec3 f=vec3(t.x,t.y,t.z);

    this->eye.x=(this->lookat.x+f.x);
    this->eye.y=(this->lookat.y+f.y);
    this->eye.z=(this->lookat.z+f.z);

    this->calcViewMatrix();
     */
}

void Camera::rotateUp(float deg)
{
    this->rotz+=deg;
    //a few if to avoid angle 0
    if(rotz==0)
        rotz=1;
    if(rotz==180)
        rotz=181;
    if(rotz>=360)
        rotz=1;
    if(rotz<=-180)
        rotz=181;
    this->eye.x=sin(rotz*PI/180)*sin(roty*PI/180)*this->distance+this->lookat.x;
    this->eye.y=cos(rotz*PI/180)*this->distance+this->lookat.y;
    this->eye.z=sin(rotz*PI/180)*cos(roty*PI/180)*this->distance+this->lookat.z;
    this->calcViewMatrix();
    /*
    this->eye.y+=deg*-0.04;

    this->calcViewMatrix();
     */
}
void Camera::saveState()
{
    ofstream file;
    file.open("camstate");
    file << this->eye.x<< " " << this->eye.y<< " " << this->eye.z <<" "<< this->lookat.x<< " "<< this->lookat.y<< " "<< this->lookat.z;
    file.close();
}
void Camera::loadState()
{
    ifstream file;
    file.open("camstate");
    file >> this->eye.x >> this->eye.y >> this->eye.z >> this->lookat.x>> this->lookat.y>> this->lookat.z;
    file.close();
    this->calcViewMatrix();
}

void Camera::updateProjectionMatrix(int width, int height)
{
    //updates the projectionMatrix
    float nearClip = 0.5f;
    float farClip  = 1000.0f;
    float fov_deg = 45.0f;
    float aspect = (float)width/(float)height;
    this->projectionMatrix=perspective(fov_deg, aspect,nearClip,farClip);

    //updates the viewportMatrix
    float w2 = width / 2.0f;
    float h2 = height / 2.0f;
    viewportMatrix = mat4( vec4(w2,0.0f,0.0f,0.0f),
                           vec4(0.0f,h2,0.0f,0.0f),
                           vec4(0.0f,0.0f,1.0f,0.0f),
                           vec4(w2+0, h2+0, 0.0f, 1.0f));
    
    this->wWidth=width;
    this->wHeight=height;
}
mat4 Camera::getCombinedVPMatrix()
{
    return this->projectionMatrix*this->viewMatrix;
}
mat4 Camera::getProjectionMatrix()
{
    return this->projectionMatrix;
}
mat4 Camera::getViewportMatrix()
{
    return this->viewportMatrix;
}
vec3 Camera::getClickRay(int x, int y)
{
	float normalisedx = 2 * (float)x / this->wWidth - 1;
	float normalisedy = 1 - 2 * (float)y / this->wHeight;
	mat4 unview = inverse(this->projectionMatrix*this->viewMatrix);
	vec4 near_point = unview * vec4(normalisedx, normalisedy, 0, 1);
	//the last vec3 is the pos of the camera
	vec3 t = vec3(near_point.x/near_point.w,near_point.y/near_point.w,near_point.z/near_point.w)-this->eye;
	vec3 rayd = normalize(t);
	
	return rayd;
}

