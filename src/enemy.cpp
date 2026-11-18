#include "enemy.hpp"
#include "enemy_projectile.hpp"
#include "player.hpp"
#include "random.hpp"

const int enemy_size = 40;
void Enemy::process(float delta) {
	shoot_counter += delta;
	damage_counter += delta;
	if (shoot_counter >= shoot_cooldown) {
		shoot(root->get_player_position());
		shoot_counter = 0;
		shoot_cooldown = Random::randf(1,3);
	}
	if (damage_counter > damage_cooldown) {
		damage_counter = 0;
		sprite->setFillColor(Color::Red);
		damaged = false;
		if (hp <= 0) {
			root->remove(this);
		}
	}
}
void Enemy::shoot(Vector2f target) {
	root->add(new EnemyProjectile(root, target - sprite->getPosition(), sprite->getPosition()));
}
Enemy::Enemy(Root* r) : Object(r, "Enemy") {
	sprite = std::make_unique<CircleShape>(enemy_size / 2.f);
	sprite->setOrigin({enemy_size / 2.f, enemy_size / 2.f});
	sprite->setPosition({Random::randf(100, 1900), Random::randf(100, 1000)});
	sprite->setFillColor(Color::Red);
	speed = 100;
	shoot_cooldown = 2;
	shoot_counter = 0;
	hp = 20;
	damage_counter = 0;
	damage_cooldown = 0.1;
	damaged = false;
};
void Enemy::damage(int value) {
	sprite->setFillColor(Color::White);
	damage_counter = 0;
	hp -= value;
	damaged = true;
}
