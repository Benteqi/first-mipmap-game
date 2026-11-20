#include <SFML/Window/Joystick.hpp>
#include <SFML/Window/WindowEnums.hpp>
#include <algorithm>
#include <iostream>
#include <ranges>
#include <string>
#include <SFML/Window/Mouse.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <unordered_map>
#include <vector>
#include "enemy_projectile.hpp"
#include "player_projectile.hpp"
#include "root.hpp"
#include "keymap.hpp"
#include "player.hpp"
#include "enemy.hpp"
#include "popup.hpp"

	Root::Root(Vector2i window_size, std::string title) {
		wave_number = 1;
		game_is_over = false;
		window = RenderWindow( VideoMode( { (unsigned int)window_size.x, (unsigned int)window_size.y } ), title, Style::Titlebar | Style::Close);
		player = new Player(this, (Vector2f)window.getSize() / 2.f);
		add(player);
	}
	Vector2f Root::get_player_position() {
		return player->sprite->getPosition();
	}
	int Root::mainloop() {
		Clock clock;
		while ( window.isOpen() && !game_is_over) {
			bool enemy_found = false;
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
				Vector2f pos = {0,0};
				if (object_array[i]->name != "Pop up") {
					pos = object_array[i]->sprite->getPosition() + Vector2f{12, 12};
				}
				if (object_array[i]->name == "Enemy") {
					enemy_found = true;
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
			if (!enemy_found) {
				add(new PopUp(this, "Wave" + std::to_string(wave_number)));
				int enemy_count = wave_number + wave_number / 2 + wave_number / 3 + 2;
				for( int i = 0; i < enemy_count; i++ ){
					add(new Enemy(this));
				}
				++wave_number;
			}
			for(auto i : std::views::reverse(to_remove)) {
				remove_at(i);
			}
			to_remove.clear();
			for(int i = 0; i < object_array.size(); i++) {
				if (object_array[i]->name == "Pop up")  {
					window.draw(*((PopUp*)object_array[i])->text);
				} else {
					window.draw(*object_array[i]->sprite);
				}
				object_array[i]->process(delta); //NOTE: Draw before process might break things in the future, but it fixes a few bugs right now
			}
			window.display();
		}
		for(auto o : object_array) {
			delete o;
		}
		PopUp p(this, "Game over!");
		while (window.isOpen()) {
			window.clear();
			while (std::optional event = window.pollEvent()) {
				if (event->is<Event::Closed>()) {
					window.close();
				}
				else if (const auto * pressed = event->getIf<Event::KeyPressed>()) 
					if (keymap[pressed->scancode] == Actions::Close) {
						window.close();
				}
			}
			window.draw(*p.text);
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
		to_remove.insert(std::distance(object_array.begin(), std::find(object_array.begin(), object_array.end(), obj)));
	}
	Vector2f Root::get_center_position() {
		return ((Vector2f)window.getSize() / 2.f);
	}
	void Root::game_over() {
		game_is_over = true;
	}
