#pragma once

#include <memory>
#include <array>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include "State.hpp"
#include "Game.hpp"
#include "Snake.hpp"

class GamePlay : public Engine::State
{
private:
	const static int num_food = 1;

	std::shared_ptr<Context> m_context;
	sf::Sprite m_grass;
	std::array<sf::Sprite, num_food> m_foods;
	unsigned num_onFood;
	std::array<sf::Sprite, 4> m_walls;
	Snake m_snake;
	
	sf::Vector2f m_snakeDirection;
	sf::Vector2f newSnakeDirection;

	sf::Time m_elapsedTime;
	float m_actionInterval;
	
	bool m_ifMovedOnKey;
	bool m_isPause;

	sf::Text m_scoreText;
	unsigned m_score;

	bool isFromGameOver;

public:
	GamePlay(std::shared_ptr<Context>& context);//&, no need to copy
	~GamePlay();

	void Init() override;
	void ProcessInput() override;
	void Update(sf::Time deltaTime) override;
	void Draw() override;

	void Pause() override;
	void Start() override;

};