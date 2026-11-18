#include "player.hpp"
#include "object.hpp"
#include "root.hpp"
#include "player_projectile.hpp"
#include <iostream>

void Player::process(float delta) {
	dash_counter += delta;
	damage_counter += delta;
	sprite->move(direction * delta * speed);
	if(to_dash) {
		sprite->move(direction * dash_range);
		to_dash = false;
		dash_counter = 0;
	}
	direction = {0, 0}; 
	if (damage_counter > damage_cooldown) {
		damage_counter = 0;
		sprite->setFillColor(Color::Green);
		damaged = false;
		if (hp <= 0) {
			std::cout << "Game over!";
		}
	}
}

Player::Player(Root* r, Vector2f p) : Object(r, "Player") {
	sprite = std::make_unique<CircleShape>(player_size / 2.f);
	sprite->setOrigin({player_size / 2.f, player_size / 2.f});
	sprite->setFillColor(Color::Green);
	sprite->setPosition(p);
	speed = 100;
	dash_range = 300;
	direction = {0, 0};
	dash_cooldown = 2;
	dash_counter = dash_cooldown;
	damage_counter = 0;
	damage_cooldown = 0.1;
	damaged = false;
	hp = 40;
};
void Player::move(Vector2f dir) {
	direction += dir;
}
void Player::dash() {
	if(dash_counter > dash_cooldown) {
		to_dash = true;
	}
}
void Player::shoot(Vector2f target) {
	root->add(new PlayerProjectile(root, target - sprite->getPosition(), sprite->getPosition()));
}

void Player::damage(int value) {
	sprite->setFillColor(Color::White);
	damage_counter = 0;
	hp -= value;
	damaged = true;
}
