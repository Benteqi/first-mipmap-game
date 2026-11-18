#pragma once
#include "projectile.hpp"
#include "root.hpp"
#include <SFML/System/Vector2.hpp>

class EnemyProjectile : public Projectile {
	int damage;
	public:
	EnemyProjectile(Root *r, Vector2f d, Vector2f p );
	int get_damage();
};

