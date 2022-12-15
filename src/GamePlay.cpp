#include "GamePlay.hpp"
#include "GameOver.hpp"
#include "GamePause.hpp"

#include <SFML/Window/Event.hpp>

// for generate random number
#include <stdlib.h>
#include <time.h>

GamePlay::GamePlay(std::shared_ptr<Context>& context)
	: m_context(context),
	  m_snakeDirection({ 16.f, 0.f }), newSnakeDirection({ 16.f, 0.f }),
	  m_elapsedTime(sf::Time::Zero), m_actionInterval(1.f / 15.f),
	  m_ifMovedOnKey(false), m_isPause(false), m_score(0),
	  num_onFood(0), isFromGameOver(false)
{}

GamePlay::~GamePlay(){}

void GamePlay::Init()
{
	srand(time(nullptr));//Seed the random number generator based on given current time

	m_context->m_assets->AddTexture(FOOD, "Assets/Textures/food.png");
	m_context->m_assets->AddTexture(SNAKE, "Assets/Textures/snake.png");

	for (auto& food : m_foods)
	{
		food.setTexture(m_context->m_assets->GetTexture(FOOD));

		unsigned x = std::clamp(rand() % m_context->m_window->getSize().x / 16 * 16, (unsigned)0, m_context->m_window->getSize().x - 16);
		unsigned y = std::clamp(rand() % m_context->m_window->getSize().y / 16 * 16, (unsigned)0, m_context->m_window->getSize().y - 16);
		food.setPosition(x, y);
	}

	m_snake.Init(m_context->m_assets->GetTexture(SNAKE), m_context->m_window->getSize().x, m_context->m_window->getSize().y); //Initialize Snake body

	m_scoreText.setFont(m_context->m_assets->GetFont(MAIN_FONT));
	m_scoreText.setString("Score : " + std::to_string(m_score));
	m_scoreText.setPosition(0, 0);
}

void GamePlay::ProcessInput()
{
	sf::Event event;
	while (m_context->m_window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_context->m_window->close();
		}
		else if (event.type == sf::Event::KeyPressed)
		{
			m_isPause = false;//Stop pausing, functioning Update()
			m_elapsedTime = sf::Time::Zero;//avoid uncontinuous movement due to continuous Keying Pause

			newSnakeDirection = m_snakeDirection;
			switch (event.key.code)
			{
			case sf::Keyboard::Up:
				newSnakeDirection = { 0.f, -16.f };
				break;
			case sf::Keyboard::Down:
				newSnakeDirection = { 0.f, 16.f };
				break;
			case sf::Keyboard::Left:
				newSnakeDirection = { -16.f, 0.f };
				break;
			case sf::Keyboard::Right:
				newSnakeDirection = { 16.f, 0.f };
				break;
			case sf::Keyboard::Space:
				//Pause State
				m_context->m_states->Add(std::make_unique<GamePause>(m_context));//replace flag is false, Pause() of current State is called
				m_context->m_states->ProcessStateChange(); /* I feel, in this way, it can lead to huge problems, really cannot
															  do those casually, need some professional guidance!!*/ 
														   //BUT WE CAN TRY THIS TOMORROW, SEE WHAT WOULD HAPPEN
														   //OR ACTUALLY, AT LEAST WE CAN TRY BACKWARD TWICE TO RESUME THE GAME !!
				break;
			default:
				break;
			}

			//Key moving (Update Process included)
			if (std::abs(newSnakeDirection.x) != std::abs(m_snakeDirection.x))
			{
				m_snakeDirection = newSnakeDirection;
				/*Before moving the Snake, always check if on food, or on self, 
				including Key moving, so we check those here*/
				if (m_snake.IsOnSelf()) 
				{
					isFromGameOver = true;
					m_context->m_assets->SetCurrentScore(m_score); // set current game score
					m_context->m_states->Add(std::make_unique<GameOver>(m_context));
				}

				for (auto& food : m_foods)
				{
					if (m_snake.IsOn(food))
					{
						num_onFood += 3;
						unsigned x = std::clamp(rand() % m_context->m_window->getSize().x / 16 * 16, (unsigned)0, m_context->m_window->getSize().x - 16);
						unsigned y = std::clamp(rand() % m_context->m_window->getSize().y / 16 * 16, (unsigned)0, m_context->m_window->getSize().y - 16);
						food.setPosition(x, y);

						m_score += 3;
						m_scoreText.setString("Score : " + std::to_string(m_score));
					}
				}

				if (num_onFood > 0)
				{
					m_snake.Grow(m_snakeDirection);
					num_onFood--;
				}
				else {m_snake.Move(m_snakeDirection);}

				m_ifMovedOnKey = true;
				m_elapsedTime = sf::seconds(m_actionInterval); //Enter next Update() instantly to omit m_ifMovedKey flag
			}
		}
	}
}

void GamePlay::Update(sf::Time deltaTime)
{
	if (!m_isPause)
	{
		m_elapsedTime += deltaTime;
		while (m_elapsedTime.asSeconds() > m_actionInterval)
		{
			//Hit On:
			
			//self
			if (m_snake.IsOnSelf())
			{
				isFromGameOver = true;
				m_context->m_assets->SetCurrentScore(m_score); // set current game score
				m_context->m_states->Add(std::make_unique<GameOver>(m_context));
			}

			//food
			for (auto& food : m_foods)
			{
				if (m_snake.IsOn(food))
				{
					num_onFood += 3;
					unsigned x = std::clamp(rand() % m_context->m_window->getSize().x / 16 * 16, (unsigned)0, m_context->m_window->getSize().x - 16);
					unsigned y = std::clamp(rand() % m_context->m_window->getSize().y / 16 * 16, (unsigned)0, m_context->m_window->getSize().y - 16);
					food.setPosition(x, y);

					m_score += 3;
					m_scoreText.setString("Score : " + std::to_string(m_score));
				}
			}

			//Not Hit

			if (!m_ifMovedOnKey)
			{
				if (num_onFood > 0) { m_snake.Grow(m_snakeDirection), num_onFood--; } //Grow replace Movement
				else { m_snake.Move(m_snakeDirection); }
			}
			else { m_ifMovedOnKey = false; }//set flag from true to false
			m_elapsedTime = sf::Time::Zero;
		}
	}
}

void GamePlay::Draw()
{
	m_context->m_window->clear();
	for (auto& food : m_foods)
	{
		m_context->m_window->draw(food);
	}
	m_context->m_window->draw(m_snake);
	m_context->m_window->draw(m_scoreText);
	m_context->m_window->display();

}

void GamePlay::Pause()
{

}

void GamePlay::Start()
{
	if (isFromGameOver)
	{
		m_snake.MoveBackward();
		m_snake.MoveBackward();
		num_onFood++;
		num_onFood++;
		isFromGameOver = false;
	}
	//Pause when Starting the Game
	m_isPause = true;
}


