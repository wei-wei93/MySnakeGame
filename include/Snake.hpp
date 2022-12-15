#pragma once

#include <list>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

class Snake : public sf::Drawable
{  
	//Creating Snake class so easy to implement the movement of Snake controlled by Users
private:
	std::list<sf::Sprite> m_body; //using list to increase snake length //.(get iterator of sf::Sprite) then ->
	std::list<sf::Sprite>::iterator m_head;//->
	std::list<sf::Sprite>::iterator m_tail;//->

	unsigned windowSizex, windowSizey;

public:
	Snake();
	~Snake();

	void Init(const sf::Texture& texture, unsigned winSizex, unsigned winSizey);//Initialize the Snake
	void Move(const sf::Vector2f& direction);//Move the Snake into the direction
	void MoveBackward();//Move backward if resuming GamePlay from GameOver
	bool IsOn(const sf::Sprite& other) const;//Detect the object Snake has creashed
	void Grow(const sf::Vector2f& direction);//increase the length of Snake "at the head" into the direction
	bool IsOnSelf() const;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	//m_body a is private attribute, to draw it have to access from inside Snake class
 
	//override m_window->draw(m_snake); in GamePlay.cpp 
	//virtually from SFML/Drawable class
};



