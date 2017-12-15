#pragma once
#include "../component/ActiveComponent.h"

//first GLEW
#include <GL\glew.h>
//then GLFW
#include <GLFW\glfw3.h>
//and then GLM
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
using namespace glm;

enum projectionType
{
	PERSPECTIVE,
	ORTHO
};

class Camera : public ActiveComponent
{
public:
	float Zoom;

	Camera(projectionType projection, vec3 position);
	Camera();

	mat4 GetView();

	mat4 GetProjection(int screenWidth, int screenHeight);

private:
	projectionType projection;
};