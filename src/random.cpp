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
int Random::randint() {
	return randint(0, 1<<31);
}
float Random::randf(int min, int max) {
	return (float)generator() / (1 << 31) * (max - min) + min;
}
float Random::randf(int max) {
	return randf(0, max);
}
float Random::randf() {
	return randf(0, 1<<31);
}

std::mt19937 mt(time(0));
int Random::seed = mt() % 10000;
std::mt19937 Random::generator(seed);
