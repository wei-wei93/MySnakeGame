#pragma once

#include <SFML/Graphics/Text.hpp>

#include "State.hpp"
#include "Game.hpp"

class GamePause : public Engine::State
{
private:
	std::shared_ptr<Context> m_context;
	sf::Text m_gamePauseTitle;

public:
	GamePause(std::shared_ptr<Context>& context);
	~GamePause();

	//override keyword confirm you override virtual functions of base class
	void Init() override;
	void ProcessInput() override;
	void Update(sf::Time deltaTime) override;
	void Draw() override;

};