#pragma once

#include "State.hpp"
#include "Game.hpp"

#include <SFML/Graphics/Text.hpp>

#include <array>

class RankedList : public Engine::State
{
private:
	std::shared_ptr<Context> m_context;
	sf::Text m_rankedListTitle;

	std::array<sf::Text, 2> m_categories;
	std::array<sf::Text, 8> m_listNo;
	std::array<sf::Text, 8> m_listScores;

	sf::Text m_returnButton;

	int m_listLength; //m_list is a vector<int>

	bool m_isReturnSelected;
	bool m_isReturnPressed;

public:
	RankedList(std::shared_ptr<Context> context);
	~RankedList();

	void Init() override;
	void ProcessInput() override;
	void Update(sf::Time deltaTime) override;
	void Draw() override;

};





