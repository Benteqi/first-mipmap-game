#include "enemy.hpp"
#include "counter.hpp"
#include "enemy_projectile.hpp"
#include "random.hpp"

const int enemy_size = 40;
void Enemy::process(float delta) {
	shoot_counter.count(delta);
	damage_counter.count(delta);
	if (shoot_counter.isTimeout()) {
		shoot_counter.reset();
		shoot(root->get_player_position());
		shoot_counter.setCooldown(Random::randf(1,3));
	}
	if (damage_counter.isTimeout()) {
		damage_counter.reset();
		sprite->setFillColor(Color::Red);
		if (hp <= 0) {
			root->remove(this);
		}
	}
}
void Enemy::shoot(Vector2f target) {
	root->add(new EnemyProjectile(root, target - sprite->getPosition(), sprite->getPosition()));
	root->play_sound(SoundType::SHOOT);
}
Enemy::Enemy(Root* r) : Object(r, "Enemy") {
	sprite = std::make_unique<CircleShape>(enemy_size / 2.f);
	sprite->setOrigin({enemy_size / 2.f, enemy_size / 2.f});
	sprite->setPosition({Random::randf(100, 1900), Random::randf(100, 1000)});
	sprite->setFillColor(Color::Red);
	speed = 100;
	shoot_counter = Counter(2);
	hp = 20;
	damage_counter = Counter(0.1);
	damaged = false;
};
void Enemy::damage(int value) {
	sprite->setFillColor(Color::White);
	root->play_sound(SoundType::ENEMY_HIT);
	damage_counter.reset();
	hp -= value;
}
