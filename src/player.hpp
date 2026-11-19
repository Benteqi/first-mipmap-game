#pragma once
#include "object.hpp"
#include <SFML/System/Vector2.hpp>
#include "counter.hpp"

inline const int player_size = 40;
class Player : public Object {
	float speed;
	float dash_range;
	bool to_dash;
	Counter dash_counter;
	Counter damage_counter;
	Counter shoot_counter;
	int hp;
	public: 
	Vector2f direction;
	void damage(int value);
	void process(float delta);
	void move(Vector2f direction);
	void dash();
	void shoot(Vector2f target);
	Player(Root* r, Vector2f p);
};
