#include "AssetMan.hpp"

Engine::AssetMan::AssetMan()
{}

Engine::AssetMan::~AssetMan() {}

void Engine::AssetMan::AddTexture(int id, const std::string& filePath, bool wantRepeated)
{
	auto texture = std::make_unique<sf::Texture>(); // auto?

	if (texture->loadFromFile(filePath))  //loadFromFile() method from SFML Texture class
	{
		texture->setRepeated(wantRepeated);
		m_textures[id] = std::move(texture);
	}
}

void Engine::AssetMan::AddFont(int id, const std::string& filePath)
{
	auto font = std::make_unique<sf::Font>();

	if (font->loadFromFile(filePath)) // sf::Font loads file
	{
		m_fonts[id] = std::move(font);
	}
}

void Engine::AssetMan::SetCurrentScore(int new_score)
{
	m_currentScore = new_score;
}

void Engine::AssetMan::AddScore()
{
	m_rankedList.push_back(m_currentScore);
}

const sf::Texture& Engine::AssetMan::GetTexture(int id) const 
{ 
	return *(m_textures.at(id).get()); //.at() .get()?
}

const sf::Font& Engine::AssetMan::GetFont(int id) const
{
	return *(m_fonts.at(id).get());
}

const std::vector<int>& Engine::AssetMan::GetScoreRankedList()
{
	std::sort(m_rankedList.begin(), m_rankedList.end(), std::greater<int>());
	return m_rankedList;
}
