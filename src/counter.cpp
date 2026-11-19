#include "counter.hpp"

Counter::Counter(float cool, std::function<void()> call, bool a){
	cooldown = cool;
	callback = call;
	automatic = a;
	counter = 0;
}
Counter::Counter() {
	cooldown = 0;
	callback = nullptr;
	automatic = false;
	counter = 0;
}
bool Counter::isTimeout(){
	return counter > cooldown;
}
void Counter::setCooldown(float c){
	cooldown = c;
}
void Counter::reset() {
	counter = 0;
}
void Counter::count(float time) {
	counter += time;
	if (isTimeout() && automatic) {
		callback(); 
		reset();
	}
}
