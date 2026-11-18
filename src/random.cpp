#include "random.hpp"
#include <ctime>

int Random::get_seed() {
	return seed;
}
int Random::randint(int min, int max) {
	return generator() % (max - min) + min;
};
int Random::randint(int max) {
	return randint(0, max);
}
float Random::randf() {
	return (float)generator() / (1 << 31);
}

std::mt19937 mt(time(0));
int Random::seed = mt() % 10000;
std::mt19937 Random::generator(seed);
