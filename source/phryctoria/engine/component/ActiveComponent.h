#pragma once
#include "Component.h"

class ActiveComponent : public Component
{
public:
	void Start();
	void Update();
	void End();

	ActiveComponent(vec3 position);
	ActiveComponent();
};