#ifndef CAMERA_H
#define CAMERA_H
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform2.hpp"
#include <iostream>
#include <math.h>
#include <fstream>

using namespace std;
using namespace glm;

class Camera
{
private:
    mat4 viewMatrix,projectionMatrix,viewportMatrix;
    vec3 lookat, eye,up;
    void calcViewMatrix();
    float rotx,roty,rotz;
    float distance;
public:
    Camera();
    ~Camera();
    mat4 getViewMatrix();
    vec3 getPos();
    void moveForeward(float a);
    void moveBackward(float a);
    void strafeLeft(float a);
    void strafeRight(float a);
    void zoomOut(float a);
    void zoomIn(float a);
    void rotateLeft(float deg);
    void rotateUp(float deg);
    void saveState();
    void loadState();
    void updateProjectionMatrix(int width, int height);
    mat4 getProjectionMatrix();
    mat4 getCombinedVPMatrix();
    mat4 getViewportMatrix();

};

#endif // CAMERA_H
