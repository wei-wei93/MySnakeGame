#include "GamePause.hpp"

#include <SFML/Window/Event.hpp>

GamePause::GamePause(std::shared_ptr<Context>& context) : m_context(context)
{}
GamePause::~GamePause() {}

void GamePause::Init()
{
	m_gamePauseTitle.setFont(m_context->m_assets->GetFont(MAIN_FONT));
	m_gamePauseTitle.setCharacterSize(50);
	m_gamePauseTitle.setString("Pause");
	m_gamePauseTitle.setOrigin(m_gamePauseTitle.getGlobalBounds().width / 2.f,
						  m_gamePauseTitle.getGlobalBounds().height / 2.f);
	m_gamePauseTitle.setPosition(m_context->m_window->getSize().x / 2.f,
							m_context->m_window->getSize().y / 2.f);

}
void GamePause::ProcessInput()
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
			switch (event.key.code)
			{
			case sf::Keyboard::Space:
			{
				m_context->m_states->PopCurrent();//return to GamePlay State
				break;
			}
			default:
				break;
			}
		}

	}
}
void GamePause::Update(sf::Time deltaTime)
{
		
}
void GamePause::Draw()
{
	m_context->m_window->draw(m_gamePauseTitle);
	m_context->m_window->display();
}

