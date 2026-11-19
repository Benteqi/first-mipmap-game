#pragma once
#include "object.hpp"
#include "counter.hpp"

class Enemy : public Object {
	int speed;
	int hp;
	bool damaged;
	Counter damage_counter;
	Counter shoot_counter;
	public:
	void process(float delta); 
	void shoot(Vector2f target);
	Enemy(Root* r);
	void damage(int value);
};

