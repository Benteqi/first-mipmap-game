#include "enemy_projectile.hpp"
#include <SFML/Graphics/Color.hpp>

EnemyProjectile::EnemyProjectile(Root *r, Vector2f d, Vector2f p ) : Projectile(r, d, p){
	speed = 600;

	sprite->setFillColor(Color::Red);
}

