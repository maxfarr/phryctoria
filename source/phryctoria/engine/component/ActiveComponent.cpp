#include "ActiveComponent.h"

ActiveComponent::ActiveComponent(vec3 position)
{
	Position = position;
}

ActiveComponent::ActiveComponent()
{
	Position = vec3(0.0f, 0.0f, 0.0f);
}