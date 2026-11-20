#pragma once 
#include <unordered_map>
#include <vector>
#include <string>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include "audio_manager.hpp"
#include "sounds.hpp"
#include "player.hpp"
#include "signal.hpp"
#include "object.hpp"
#include <set>


using namespace sf;
class Root {
	std::unordered_map<Signal, void(*)(int*, int)> signal_map = {
	};
	int wave_number;
	bool game_is_over;
	std::vector<Object*> object_array = {};
	Player* player;
	RenderWindow window;
	AudioManager audio_manager;
	std::set<int> to_remove;
	public:
	Root(Vector2i window_size, std::string title);
	int mainloop(); 
	Vector2f get_player_position();
	void add(Object* obj);
	void remove_at(int index);
	void remove(Object* obj);
	void connect(Signal s, void (*function)(int*, int)); 
	void emit(Signal s, int* arr, int count); 
	void play_sound(SoundType t);
	void game_over();
	Vector2f get_center_position();
};
