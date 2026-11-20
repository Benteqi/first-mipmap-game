#pragma once
#include "counter.hpp"
#include "object.hpp"
#include "root.hpp"
#include <SFML/Graphics/Text.hpp>
#include <string>
class PopUp : public Object {
	Counter counter;
	public:
	Text* text;
	void process(float delta);
	PopUp(Root* r, std::string t);
};
