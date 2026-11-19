#include <iostream>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include "random.hpp"
#include "root.hpp"

using namespace sf;

int main()
{
	std::cout << "Seed: " << Random::get_seed() << '\n';
	Root root({1920, 1080}, "My first mipmap game");
	root.mainloop();
	return 0;
}
