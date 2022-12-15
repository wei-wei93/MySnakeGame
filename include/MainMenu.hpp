#pragma once

#include <memory>
#include <array>

#include <SFML/Graphics/Text.hpp>

#include "State.hpp"
#include "Game.hpp" // import Context Struct

class MainMenu : public Engine::State //MainMenu inherits State class
{
private:
	std::shared_ptr<Context> m_context;
	sf::Text m_gameTitle;
	std::array<sf::Text, 3> m_buttons;//0: play 1: ranked list 2: exit

	int No_buttonSelected;//0: play 1: ranked list 2: exit
	int No_buttonPressed;

public:
	MainMenu(std::shared_ptr<Context>& context);
	~MainMenu();

	//override keyword confirm you override virtual functions of base class
	void Init() override;
	void ProcessInput() override;
	void Update(sf::Time deltaTime) override;
	void Draw() override;

	void Pause() override;
	void Start() override;

};