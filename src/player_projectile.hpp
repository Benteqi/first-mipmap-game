#pragma once
#include "projectile.hpp"
#include "root.hpp"
#include <SFML/System/Vector2.hpp>

class PlayerProjectile : public Projectile {
	public:
	PlayerProjectile(Root *r, Vector2f d, Vector2f p );
};

