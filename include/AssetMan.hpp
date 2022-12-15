#pragma once

#include <map>
#include <memory>
#include <string>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>

namespace Engine
{
	class AssetMan //Asset Manager
	{
	private:
		std::map<int, std::unique_ptr<sf::Texture>> m_textures; //1 id(int) -> 1 type of Texture/Font
		std::map<int, std::unique_ptr<sf::Font>> m_fonts;
		std::vector<int> m_rankedList;
		int m_currentScore;

	public:
		AssetMan();
		~AssetMan();

		void AddTexture(int id, const std::string& filePath, bool wantRepeated = false); 
		void AddFont(int id, const std::string& filePath); 
		//const means unchangeable, 
		//& means reference, passing filePath itself
		void SetCurrentScore(int new_score);
		void AddScore();

		const sf::Texture& GetTexture(int id) const; 
		const sf::Font& GetFont(int id) const;
		//const in the beginning means returned Font/Texture references are unchangeable
		//const in the end means they are read-only functions
		const std::vector<int>& GetScoreRankedList();
	};
}


