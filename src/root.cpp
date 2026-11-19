#include <algorithm>
#include <string>
#include <SFML/Window/Mouse.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include "root.hpp"
#include "enemy_projectile.hpp"
#include "keymap.hpp"
#include "player.hpp"
#include "enemy.hpp"
#include "player_projectile.hpp"

	Root::Root(Vector2i window_size, std::string title) {
		window = RenderWindow( VideoMode( { (unsigned int)window_size.x, (unsigned int)window_size.y } ), title);
		player = new Player(this, (Vector2f)window.getSize() / 2.f);
		add(new Enemy(this));
		add(player);
	}
	Vector2f Root::get_player_position() {
		return player->sprite->getPosition();
	}
	int Root::mainloop() {
		Clock clock;
		while ( window.isOpen() ) {
			float delta = clock.restart().asSeconds();
			window.clear();
			while (std::optional event = window.pollEvent()) {
				if (event->is<Event::Closed>()) {
					window.close();
				}
				else if (const auto * mouse_pressed = event->getIf<Event::MouseButtonPressed>()) 
					if (mouse_pressed->button == Mouse::Button::Left ) {
						player->shoot((Vector2f)mouse_pressed->position);
				}
			};
			for(auto m = keymap.begin(); m != keymap.end(); m++) {
				if(Keyboard::isKeyPressed(m->first)) {
					switch(m->second) {
						case Actions::MoveLeft:
							player->move({1, 0});
							break;
						case Actions::MoveRight:
							player->move({-1, 0});
							break;
						case Actions::MoveDown:
							player->move({0, 1});
							break;
						case Actions::MoveUp:
							player->move({0, -1});
							break;
						case Actions::Dash:
							player->dash();
							break;
						case Actions::Close:
							window.close();
							break;
					}
				}
			}
			for(int i = 0; i < object_array.size(); i++) {
				if (object_array[i]->name == "Enemy") {
					for(int j = 0; j < object_array.size(); j++) {
						if (object_array[j]->name == "Player Projectile" && (object_array[i]->sprite->getPosition() - object_array[j]->sprite->getPosition()).length() < 20 ) {
							Enemy* e = (Enemy*)object_array[i];
							PlayerProjectile* p = (PlayerProjectile*)object_array[j];
							e->damage(p->get_damage());
							remove_at(j);
						}
					}
				}
				else if (object_array[i]->name == "Enemy Projectile" && (object_array[i]->sprite->getPosition() - get_player_position()).length() < 20) {
					EnemyProjectile* e = (EnemyProjectile*)object_array[i];
					player->damage(e->get_damage());
					remove_at(i);
				}
			}
			for(int i = 0; i < object_array.size(); i++) {
				object_array[i]->process(delta);
				window.draw(*object_array[i]->sprite);
			}
			window.display();
		}
		return 0;
	}
	void Root::play_sound(SoundType t) {
		audio_manager.play_sound(t);
	}
	void Root::connect(Signal s, void (*function)(int*, int)) {
		signal_map[s] = function;
	}
	void Root::emit(Signal s, int* arr, int count) {
		signal_map[s](arr, count);
	}
	void Root::add(Object* obj) {
		object_array.push_back(obj);
	}
	void Root::remove_at(int index) {
		delete object_array[index];
		object_array.erase(object_array.begin() + index);
	}
	void Root::remove(Object* obj) {
		object_array.erase(std::find(object_array.begin(), object_array.end(), obj));
	}
