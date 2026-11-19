#include "audio_manager.hpp"
#include "sounds.hpp"
#include <SFML/Audio/SoundBuffer.hpp>
#include <vector>

void AudioManager::play_sound(SoundType t) {
	static const std::string sound_extension = ".wav";
	static const std::string sound_path = ASSETS_PATH "sounds/";
	static std::unordered_map<SoundType , SoundBuffer> sound_map {
		{ SoundType::PLAYER_HIT, SoundBuffer(sound_path + "player_hurt" + sound_extension)},
			{ SoundType::ENEMY_HIT, SoundBuffer(sound_path + "enemy_hurt" + sound_extension)},
			{ SoundType::SHOOT, SoundBuffer(sound_path + "shoot" + sound_extension)},
	};
	audio_buffer[current_used_sound] = Sound(sound_map[t]);
	audio_buffer[current_used_sound++].play();
	current_used_sound %= SOUND_BUFFER_SIZE;
}
AudioManager::AudioManager() {
	SoundBuffer b;
	audio_buffer = std::vector<Sound>(SOUND_BUFFER_SIZE, Sound(b));
	current_used_sound = 0;
}
