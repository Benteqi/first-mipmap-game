#include "player_projectile.hpp"
#include <SFML/Graphics/Color.hpp>

PlayerProjectile::PlayerProjectile(Root *r, Vector2f d, Vector2f p ) : Projectile(r, d, p){
	name = "Player Projectile";
	damage = 5;
	speed = 1000;
	sprite->setFillColor(Color::Yellow);
}

int PlayerProjectile::get_damage() {
	return damage;
}

