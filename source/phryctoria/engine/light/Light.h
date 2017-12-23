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

class Light : ActiveComponent
{
public:
	vec4 Color;
	float Intensity;
	bool Directional;
};