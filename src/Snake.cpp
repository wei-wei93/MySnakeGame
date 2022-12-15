#include "Snake.hpp"

Snake::Snake()
	: m_body(std::list<sf::Sprite>(10)),
	  windowSizex(0), windowSizey(0)
{}

Snake::~Snake(){}

void Snake::Init(const sf::Texture& texture, unsigned winSizex, unsigned winSizey)
{
	windowSizex = winSizex, windowSizey = winSizey;
	m_head = --m_body.end();
	m_tail = m_body.begin();
	float x = 16.f;
	for (auto& piece : m_body)
	{
		piece.setTexture(texture);
		piece.setPosition({ x, 16.f });
		x += 16.f;
	}
}

/*We can implement Snake separating its head and body
  more advancely, we can also separate its tail from body*/

void Snake::Move(const sf::Vector2f& direction)
{
	//Obtain real position(x,y) of head after movement
	int curr_x = m_head->getPosition().x + direction.x, curr_y = m_head->getPosition().y + direction.y;
	unsigned modify_x = 0, modify_y = 0;
	modify_x = (curr_x + windowSizex) % windowSizex, modify_y = (curr_y + windowSizey) % windowSizey;

	m_tail->setPosition(modify_x, modify_y);

	m_head = m_tail;

	++m_tail;

	if (m_tail == m_body.end())
	{
		m_tail = m_body.begin();
	}
	//the movement of the snake is a loop in the list
}

void Snake::MoveBackward()
{
	m_body.erase(m_head);//delete the head piece
	//get new head iterator
	if (m_tail == m_body.begin()) { m_head = --m_body.end(); }
	else 
	{ 
		m_head = --m_tail;
		++m_tail;//resume the tail
	}
}

bool Snake::IsOn(const sf::Sprite& other) const
{
	return other.getGlobalBounds().intersects(m_head->getGlobalBounds());
}

void Snake::Grow(const sf::Vector2f& direction)
{
	//Grow on head, count as one movement as well
	sf::Sprite newPiece;
	newPiece.setTexture(*(m_body.begin()->getTexture()));
	//Obtain real position(x,y) of head after growth
	int curr_x = m_head->getPosition().x + direction.x, curr_y = m_head->getPosition().y + direction.y;
	unsigned modify_x = 0, modify_y = 0;
	modify_x = (curr_x + windowSizex) % windowSizex, modify_y = (curr_y + windowSizey) % windowSizey;

	newPiece.setPosition(modify_x, modify_y);
	
	m_head = m_body.insert(++m_head, newPiece);//insert() method in list
}

bool Snake::IsOnSelf() const
{
	bool flag = false;
	for (auto piece = m_body.begin(); piece != m_body.end(); ++piece)
	{
		if (m_head != piece)
		{
			flag = IsOn(*piece);
			if (flag)
			{
				break;
			}
		}
	}
	return flag;
}

void Snake::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto& piece : m_body)
	{
		target.draw(piece);
	}
}



