#include "player.hpp"
#include "object.hpp"
#include "root.hpp"
#include "player_projectile.hpp"
#include <iostream>


void Player::process(float delta) {
	dash_counter.count(delta);
	damage_counter.count(delta);
	shoot_counter.count(delta); 

	sprite->move(direction * delta * speed);
	if(to_dash) {
		sprite->move(direction * dash_range);
		to_dash = false;
		dash_counter.reset(); 
	}
	direction = {0, 0}; 
	if (damage_counter.isTimeout()) {
		damage_counter.reset();
		sprite->setFillColor(Color::Green);
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
	speed = 150;
	dash_range = 300;
	direction = {0, 0};
	hp = 100;
	dash_counter = Counter(2);
	damage_counter = Counter(0.1);
	shoot_counter = Counter(0.5);
};
void Player::move(Vector2f dir) {
	direction += dir;
}
void Player::dash() {
	if(dash_counter.isTimeout()) {
		to_dash = true;
	}
}
void Player::shoot(Vector2f target) {
	if (shoot_counter.isTimeout()) {
		shoot_counter.reset();
		root->add(new PlayerProjectile(root, target - sprite->getPosition(), sprite->getPosition()));
		root->play_sound(SoundType::SHOOT);
	}
}

void Player::damage(int value) {
	root->play_sound(SoundType::PLAYER_HIT);
	sprite->setFillColor(Color::White);
	damage_counter.reset();
	hp -= value;
}
