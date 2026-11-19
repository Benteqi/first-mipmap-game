#pragma once 
#include <functional>
class Counter {
	float cooldown;
	float counter;
	bool automatic;
	std::function<void()> callback; 
	public:
	Counter(float cool, std::function<void()> call = nullptr, bool a = false);
	Counter();
	bool isTimeout();
	void setCooldown(float c);
	void reset();
	void count(float time);
};

