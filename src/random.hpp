#pragma once
#include <random>

class Random {
	static int seed;
	static std::mt19937 generator;
	public: 
	static int get_seed();
	static int randint(int min, int max) ;
	static int randint(int max);
	static int randint();
	static float randf(int min, int max);
	static float randf(int max);
	static float randf();
};
