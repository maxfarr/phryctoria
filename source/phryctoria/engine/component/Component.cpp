#include "Component.h"

Component::Component(vec3 position)
{
	Position = position;
}

Component::Component()
{
	Position = vec3(0.0f, 0.0f, 0.0f);
}

void Component::Translate(vec3 translation)
{
	vec4 localTranslation = vec4(translation, 1.0f) * mat4_cast(Rotation);
	Position += vec3(localTranslation.x, localTranslation.y, localTranslation.z);
}

void Component::TranslateWorld(vec3 translation)
{
	Position += translation;
}

void Component::Rotate(float angle, vec3 axis)
{
	Rotation = rotate(Rotation, angle, axis);
}

void Component::Rotate(quat rotation)
{
	Rotation *= rotation;
}

mat4 Component::GetTransform()
{
	mat4 transform = mat4(1.0f);
	transform = translate(transform, Position);
	transform *= mat4_cast(Rotation);

	return transform;
}

vec3 Component::GetForward()
{
	vec4 tempForward = vec4(0.0f, 0.0f, 1.0f, 1.0f) * mat4_cast(Rotation);
	return vec3(tempForward.x, tempForward.y, tempForward.z);
}

vec3 Component::GetRight()
{
	return normalize(cross(GetForward(), vec3(0.0f, 1.0f, 0.0f)));
}

vec3 Component::GetUp()
{
	return normalize(cross(GetRight(), GetForward()));
}