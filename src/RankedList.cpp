#include "RankedList.hpp"

#include <SFML/Window/Event.hpp>

#include <iostream>
#include <algorithm>

RankedList::RankedList(std::shared_ptr<Context> context)
	: m_context(context), m_isReturnSelected(true), m_isReturnPressed(false), m_listLength(0)
{}

RankedList::~RankedList() {}

void RankedList::Init()
{
	float half_window_x = m_context->m_window->getSize().x / 2.f;
	float half_window_y = m_context->m_window->getSize().y / 2.f;

	m_rankedListTitle.setFont(m_context->m_assets->GetFont(MAIN_FONT));
	m_rankedListTitle.setCharacterSize(30);
	m_rankedListTitle.setString("Ranked  List");
	m_rankedListTitle.setOrigin(m_rankedListTitle.getGlobalBounds().width / 2.f, m_rankedListTitle.getGlobalBounds().height / 2.f);
	m_rankedListTitle.setPosition(half_window_x + 10.f, half_window_y - 185.f);

	for (auto& category : m_categories)
	{
		category.setFont(m_context->m_assets->GetFont(MAIN_FONT));
		category.setCharacterSize(30);
	}
	m_categories[0].setString("No.");
	m_categories[0].setOrigin(m_categories[0].getGlobalBounds().width / 2.f, m_categories[0].getGlobalBounds().height / 2.f);
	m_categories[0].setPosition(half_window_x - 230.f, half_window_y - 155.f);

	m_categories[1].setString("Score");
	m_categories[1].setOrigin(m_categories[1].getGlobalBounds().width / 2.f, m_categories[1].getGlobalBounds().height / 2.f);
	m_categories[1].setPosition(half_window_x + 230.f, half_window_y - 155.f);

	std::vector<int> m_list = m_context->m_assets->GetScoreRankedList();
	m_listLength = std::min(unsigned(m_list.size()), unsigned(8));
	for (int i = 0; i < m_listLength; i++)
	{
		m_listNo[i].setFont(m_context->m_assets->GetFont(MAIN_FONT));
		m_listNo[i].setCharacterSize(30);
		m_listNo[i].setString(std::to_string(i + 1));
		m_listNo[i].setOrigin(m_listNo[i].getGlobalBounds().width / 2.f, m_listNo[i].getGlobalBounds().height / 2.f);
		m_listNo[i].setPosition(half_window_x - 230.f, half_window_y - 155.f + ((i + 1) * 35.f));

		m_listScores[i].setFont(m_context->m_assets->GetFont(MAIN_FONT));
		m_listScores[i].setCharacterSize(30);
		m_listScores[i].setString(std::to_string(m_list[i]));
		m_listScores[i].setOrigin(m_listScores[i].getGlobalBounds().width / 2.f, m_listScores[i].getGlobalBounds().height / 2.f);
		m_listScores[i].setPosition(half_window_x + 230.f, half_window_y - 155.f + ((i + 1) * 35.f));
	}

	m_returnButton.setFont(m_context->m_assets->GetFont(MAIN_FONT));
	m_returnButton.setCharacterSize(15);
	m_returnButton.setString("Return");
	m_returnButton.setOrigin(m_returnButton.getGlobalBounds().width / 2.f, m_returnButton.getGlobalBounds().height / 2.f);
	m_returnButton.setPosition(half_window_x + 10.f, half_window_y + 185.f);

}

void RankedList::ProcessInput()
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
			case sf::Keyboard::Return:
				m_isReturnPressed = true;
				break;
			default:
				break;
			}
		}

	}
}

void RankedList::Update(sf::Time deltaTime)
{
	if (m_isReturnSelected)
	{
		m_returnButton.setFillColor(sf::Color::Yellow);
		m_returnButton.setScale(1.4, 1.4);
	}
	else
	{
		m_returnButton.setFillColor(sf::Color::White);
		m_returnButton.setScale(1, 1);
	}

	if (m_isReturnPressed)
	{
		//Back to Previous State
		m_context->m_states->PopCurrent();
	}
}

void RankedList::Draw()
{
	m_context->m_window->clear();
	m_context->m_window->draw(m_rankedListTitle);
	for (auto& category : m_categories)
	{
		m_context->m_window->draw(category);
	}
	for (int i = 0; i < m_listLength; i++)
	{
		m_context->m_window->draw(m_listNo[i]);
		m_context->m_window->draw(m_listScores[i]);
	}
	m_context->m_window->draw(m_returnButton);
	m_context->m_window->display();
}


