#include "MainMenu.hpp"
#include "GamePlay.hpp"
#include "RankedList.hpp"

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Font.hpp>

/*except valuing parameters, don't do other initializations 
in constructor, do it in another method and run it after 
instance creation, like Init() method here*/
MainMenu::MainMenu(std::shared_ptr<Context> &context)
	: m_context(context), No_buttonSelected(0), No_buttonPressed(-1)
{}

MainMenu::~MainMenu() {}

void MainMenu::Init()
{
	m_context->m_assets->AddFont(MAIN_FONT, "Assets/Fonts/Pacifico-Regular.ttf");
	m_gameTitle.setFont(m_context->m_assets->GetFont(MAIN_FONT));
	//m_context->m_assets->GetFont(MAIN_FONT) = font1;
	m_gameTitle.setCharacterSize(50); //default 30
	m_gameTitle.setString("Snake Game!");
	m_gameTitle.setOrigin(m_gameTitle.getGlobalBounds().width / 2.f,
						  m_gameTitle.getGlobalBounds().height / 2.f);
	m_gameTitle.setPosition(m_context->m_window->getSize().x / 2.f + 10.f,
							m_context->m_window->getSize().y / 2.f - 145.f);

	m_buttons[0].setString("Play");
	m_buttons[1].setString("Ranked List");
	m_buttons[2].setString("Exit");

	int i = 0;
	for (auto& button : m_buttons)
	{
		button.setFont(m_context->m_assets->GetFont(MAIN_FONT));
		button.setOrigin(button.getGlobalBounds().width / 2.f, button.getGlobalBounds().height / 2.f);
		button.setPosition(m_context->m_window->getSize().x / 2.f, m_context->m_window->getSize().y / 2.f + i*60.f);
		i++;
	}
}


void MainMenu::ProcessInput()
{
	sf::Event event;
	while (m_context->m_window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_context->m_window->close(); //click close button on the window
		}
		else if (event.type == sf::Event::KeyPressed)
		{
			switch (event.key.code)
			{
			case sf::Keyboard::Up:
				No_buttonSelected--;
				No_buttonSelected = (No_buttonSelected + 3) % 3;
				break;
			case sf::Keyboard::Down:
				No_buttonSelected++;
				No_buttonSelected = (No_buttonSelected + 3) % 3;
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


void MainMenu::Update(sf::Time deltaTime)
{
	for (auto& button : m_buttons)
	{
		button.setFillColor(sf::Color::White);
		button.setScale(1, 1);
	}

	switch (No_buttonSelected)
	{
	case 0:
		m_buttons[0].setFillColor(sf::Color::Yellow);
		m_buttons[0].setScale(1.4, 1.4);
		break;
	case 1:
		m_buttons[1].setFillColor(sf::Color::Yellow);
		m_buttons[1].setScale(1.4, 1.4);
		break;
	case 2:
		m_buttons[2].setFillColor(sf::Color::Yellow);
		m_buttons[2].setScale(1.4, 1.4);
		break;
	default:
		break;	
	}

	switch (No_buttonPressed)
	{
	case 0://play
		m_context->m_states->Replace(std::make_unique<GamePlay>(m_context));
		break;
	case 1://ranked list
		//To Ranked List State
		m_context->m_states->Add(std::make_unique<RankedList>(m_context));
		break;
	case 2://exit
		m_context->m_window->close();
		break;
	default:
		break;
	}
}


void MainMenu::Draw()
{
	m_context->m_window->clear();
	m_context->m_window->draw(m_gameTitle);
	for (auto& button : m_buttons)
	{
		m_context->m_window->draw(button);
	}
	m_context->m_window->display();
}

void MainMenu::Pause()
{

}

void MainMenu::Start()
{
	No_buttonSelected = 0;
	No_buttonPressed = -1;
}
