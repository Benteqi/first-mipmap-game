#include "popup.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

void PopUp::process(float delta) {
	counter.count(delta);
	if (counter.isTimeout()) {
		root->remove(this);
	}
}
PopUp::PopUp(Root* r, std::string t) : Object(r, "Pop up")
{
	counter = Counter(3);
	static Font f(ASSETS_PATH "fonts/font.ttf");
	text = new Text(f);
	text->setString(t);
	text->setFillColor(Color::White);
	text->setCharacterSize(100);
	text->setPosition((Vector2f)(root->get_center_position()));
	text->setOrigin(text->getLocalBounds().position + text->getLocalBounds().size / 2.f);
}
