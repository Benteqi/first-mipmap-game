#include "projectile.hpp"
#include "root.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <memory>


Projectile::Projectile(Root *r, Vector2f d, Vector2f p) : Object(r, "Projectile") {
	speed = 1000;
	direction = d.normalized();
	sprite = std::unique_ptr<RectangleShape>( new RectangleShape({20, 5}));
	sprite->setOrigin(sprite->getLocalBounds().size/2.f);
	sprite->setPosition(p);
	sprite->rotate(direction.angle());
}
void Projectile::process(float delta) {
	sprite->move(direction * delta * speed);
}
