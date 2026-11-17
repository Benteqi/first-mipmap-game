#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <string>

class Root;

using namespace sf;

class Object {
	public: 
	Object(Root* r, std::string n) : root(r), name(n) {};
	Root* root;
	std::string name;
	std::unique_ptr<Shape> sprite;
	virtual void process(float delta) {
	}
};

