#pragma once

#include <array>

#include <SFML/Graphics/Text.hpp>

#include "State.hpp"
#include "Game.hpp"

class GameOver : public Engine::State
{
private:
	std::shared_ptr<Context> m_context; 
	sf::Text m_gameOverTitle;
	std::array<sf::Text, 5> m_buttons;//0: Retry 1: Continue 2: Home 3: RankedList 4: Exit 
	
	int No_buttonSelected;//0: Retry 1: Continue 2: Home 3: RankedList 4: Exit 
	int No_buttonPressed;

public:
	GameOver(std::shared_ptr<Context>& context);
	~GameOver();

	void Init() override;
	void ProcessInput() override;
	void Update(sf::Time deltaTime) override;
	void Draw() override;

	void Pause() override;
	void Start() override;

};



