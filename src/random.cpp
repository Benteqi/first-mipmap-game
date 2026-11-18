#include "random.hpp"
#include <cstdint>
#include <ctime>
#include <random>

int Random::get_seed() {
	return seed;
}
int Random::randint(int min, int max) {
	std::uniform_int_distribution<> dist(min, max);
	return dist(generator);
};
int Random::randint(int max) {
	return randint(0, max);
}
int Random::randint() {
	return randint(0, INT32_MAX);
}
float Random::randf(int min, int max) {
	return ((float)randint() / INT32_MAX * (max - min)) + min;
}
float Random::randf(int max) {
	return randf(0, max);
}
float Random::randf() {
	return randf(0, INT32_MAX);
}

std::mt19937 mt(time(0));
int Random::seed = mt() % 10000;
std::mt19937 Random::generator(seed);
