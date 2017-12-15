#include "Camera.h"

Camera::Camera(projectionType projection, vec3 position)
{
	this->projection = projection;
	Position = position;
	Zoom = 1.0f;
}

Camera::Camera()
{
	projection = PERSPECTIVE;
	Position = vec3(0.0f, 0.0f, 0.0f);
	Zoom = 1.0f;
}

mat4 Camera::GetView()
{
	return lookAt(Position, Position + GetForward(), GetUp());
}

mat4 Camera::GetProjection(int screenWidth, int screenHeight)
{
	switch (projection)
	{
	case PERSPECTIVE: return perspective(radians(Zoom), (float)screenWidth / (float)screenHeight, 0.1f, 100.0f);
		break;
	case ORTHO: return perspective(radians(Zoom), (float)screenWidth / (float)screenHeight, 0.1f, 100.0f);
		break;

	default: return mat4(1.0f);
	}
}