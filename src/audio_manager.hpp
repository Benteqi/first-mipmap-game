#pragma once
#include <SFML/Audio.hpp>
#include <array>
#include "sounds.hpp"
using namespace sf;
class AudioManager {
	static constexpr int SOUND_BUFFER_SIZE = 64;
	int current_used_sound;
	std::vector<Sound> audio_buffer;
	public:
	void play_sound(SoundType t);
	AudioManager();
};
