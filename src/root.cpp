#include <SFML/Window/WindowEnums.hpp>
#include <algorithm>
#include <ranges>
#include <string>
#include <SFML/Window/Mouse.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <unordered_map>
#include <vector>
#include <set>
#include "enemy_projectile.hpp"
#include "player_projectile.hpp"
#include "root.hpp"
#include "keymap.hpp"
#include "player.hpp"
#include "enemy.hpp"

	Root::Root(Vector2i window_size, std::string title) {
		window = RenderWindow( VideoMode( { (unsigned int)window_size.x, (unsigned int)window_size.y } ), title, Style::Titlebar | Style::Close);
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
			std::set<int> to_remove = {};
			for(int i = 0; i < object_array.size(); i++) {
				auto pos = object_array[i]->sprite->getPosition() + Vector2f{12, 12};
				if (object_array[i]->name == "Enemy") {
					for(int j = 0; j < object_array.size(); j++) {
						if (object_array[j]->name == "Player Projectile") {
							if ((object_array[i]->sprite->getPosition() - object_array[j]->sprite->getPosition()).length() < 20 ) {
								((Enemy*)object_array[i])->damage(((PlayerProjectile*)object_array[j])->get_damage());
								to_remove.insert(j);
							}
						}
					}
				} else if (( object_array[i]->name == "Enemy Projectile" || object_array[i]->name == "Player Projectile" )
						&& (pos.x > window.getSize().x || pos.y > window.getSize().y || pos.x < 0 || pos.y < 0 )) {
					to_remove.insert(i);
				} else if (object_array[i]->name == "Enemy Projectile" && (object_array[i]->sprite->getPosition() - get_player_position()).length() < 20) {
					player->damage(((EnemyProjectile*)object_array[i])->get_damage());
					to_remove.insert(i);
				}
			}
			for(auto i : std::views::reverse(to_remove)) {
				remove_at(i);
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
		object_array[index] = object_array[object_array.size() - 1];
		object_array.pop_back();
	}
	void Root::remove(Object* obj) {
		remove_at(std::distance(object_array.begin(), std::find(object_array.begin(), object_array.end(), obj)));
	}
