#pragma once
#include "object.hpp"

class Enemy : public Object {
	int speed;
	int hp;
	bool damaged;
	float damage_counter;
	float damage_cooldown;
	float shoot_cooldown; 
	float shoot_counter;
	public:
	void process(float delta); 
	void shoot(Vector2f target);
	Enemy(Root* r);
	void damage(int value);
};

