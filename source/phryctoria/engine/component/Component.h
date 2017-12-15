#pragma once

//first GLEW
#include <GL\glew.h>
//then GLFW
#include <GLFW\glfw3.h>
//and then GLM
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
using namespace glm;

class Component
{
public:
	vec3 Position;
	quat Rotation;

	Component(vec3 position);
	Component();

	void Translate(vec3 translation);
	void TranslateWorld(vec3 translation);

	void Rotate(float angle, vec3 axis);
	void Rotate(quat rotation);

	mat4 GetTransform();

	vec3 GetForward();
	vec3 GetRight();
	vec3 GetUp();
	
private:

};