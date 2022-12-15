#include <SFML/Window/Event.hpp>

#include "GameOver.hpp"
#include "GamePlay.hpp"
#include "MainMenu.hpp"
#include "RankedList.hpp"

GameOver::GameOver(std::shared_ptr<Context>& context)
	: m_context(context), No_buttonSelected(0), No_buttonPressed(-1)
{}

GameOver::~GameOver(){}

void GameOver::Init()
{
	m_gameOverTitle.setFont(m_context->m_assets->GetFont(MAIN_FONT));
	m_gameOverTitle.setCharacterSize(50);
	m_gameOverTitle.setString("Game Over");
	m_gameOverTitle.setOrigin(m_gameOverTitle.getGlobalBounds().width / 2.f, m_gameOverTitle.getGlobalBounds().height / 2.f);
	m_gameOverTitle.setPosition(m_context->m_window->getSize().x / 2.f + 10.f, m_context->m_window->getSize().y / 2.f - 165.f);

	//0: Retry 1: Continue 2: Home 3: RankedList 4: Exit 
	m_buttons[0].setString("Retry");
	m_buttons[1].setString("Continue");
	m_buttons[2].setString("Home");
	m_buttons[3].setString("Ranked List");
	m_buttons[4].setString("Exit");

	int i = 0;
	for (auto& button : m_buttons)
	{
		button.setFont(m_context->m_assets->GetFont(MAIN_FONT));
		button.setOrigin(button.getGlobalBounds().width / 2.f, button.getGlobalBounds().height / 2.f);
		button.setPosition(m_context->m_window->getSize().x / 2.f, m_context->m_window->getSize().y / 2.f - 55.f + i*55.f);
		i++;
	}
}
void GameOver::ProcessInput()
{
	sf::Event event;
	while (m_context->m_window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_context->m_window->close(); //close window 
		}
		else if (event.type == sf::Event::KeyPressed)
		{
			switch (event.key.code)
			{
			case sf::Keyboard::Up:
				No_buttonSelected--;
				No_buttonSelected = (No_buttonSelected + 5) % 5;
				break;
			case sf::Keyboard::Down:
				No_buttonSelected++;
				No_buttonSelected = (No_buttonSelected + 5) % 5;
				break;
			case sf::Keyboard::Return:
				No_buttonPressed = No_buttonSelected;
				break;
			default:
				break;
			}
		}

	}
}
void GameOver::Update(sf::Time deltaTime)
{
	for (auto& button : m_buttons)
	{
		button.setFillColor(sf::Color::White);
		button.setScale(1, 1);
	}

	switch (No_buttonSelected)
	{
	case 0://retry
		m_buttons[0].setFillColor(sf::Color::Yellow);
		m_buttons[0].setScale(1.4, 1.4);
		break;
	case 1://continue
		m_buttons[1].setFillColor(sf::Color::Yellow);
		m_buttons[1].setScale(1.4, 1.4);
		break;
	case 2://home
		m_buttons[2].setFillColor(sf::Color::Yellow);
		m_buttons[2].setScale(1.4, 1.4);
		break;
	case 3://ranked list
		m_buttons[3].setFillColor(sf::Color::Yellow);
		m_buttons[3].setScale(1.4, 1.4);
		break;
	case 4://exit
		m_buttons[4].setFillColor(sf::Color::Yellow);
		m_buttons[4].setScale(1.4, 1.4);
		break;
	default:
		break;
	}

	switch (No_buttonPressed)
	{
	case 0://Retry
		//those just set flags
		m_context->m_assets->AddScore(); //Add new score
		m_context->m_states->PopCurrent();//Pop once
		m_context->m_states->Replace(std::make_unique<GamePlay>(m_context));//from Last GamePlay to new GamePlay
		break;
	case 1://Continue
		m_context->m_states->PopCurrent();//Continue last GamePlay
		break;
	case 2://Return to Home
		m_context->m_assets->AddScore(); //Add new score
		m_context->m_states->PopCurrent();
		m_context->m_states->Replace(std::make_unique<MainMenu>(m_context));//from Last GamePlay to Main Menu
		break;
	case 3://Ranked List
		//To Ranked List State
		m_context->m_states->Add(std::make_unique<RankedList>(m_context));
		break;
	case 4://Exit
		m_context->m_window->close();
		break;
	default:
		break;
	}
}
void GameOver::Draw()
{
	m_context->m_window->clear();
	m_context->m_window->draw(m_gameOverTitle);
	for (auto& button : m_buttons)
	{
		m_context->m_window->draw(button);
	}
	m_context->m_window->display();
}

void GameOver::Pause()
{

}

void GameOver::Start()
{
	No_buttonSelected = 0;
	No_buttonPressed = -1;
}