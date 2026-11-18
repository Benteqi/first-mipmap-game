#pragma once
#include "object.hpp"
#include <SFML/System/Vector2.hpp>
inline const int player_size = 40;
class Player : public Object {
	float speed;
	float dash_range;
	bool to_dash;
	float dash_counter;
	float dash_cooldown;
	bool damaged;
	float damage_counter;
	float damage_cooldown;
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
