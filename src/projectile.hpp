#pragma once
#include "object.hpp"
#include <SFML/System/Vector2.hpp>

class Projectile : public Object {
	protected: 
	Vector2f direction;
	float speed;
	public:
	Projectile(Root* r, Vector2f d, Vector2f p);
	void process(float delta);
};
