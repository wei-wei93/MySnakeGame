#pragma once

#include <SFML/System/Time.hpp>

namespace Engine
{
	class State
	{
	public:
		State() {};  // constructor
		virtual ~State() {};  // destructor  // what virtual means ? 

		virtual void Init() = 0;
		virtual void ProcessInput() = 0;
		virtual void Update(sf::Time deltaTime) = 0;  // Here Time deltaTime means System Time? means how long a while loop execute once? 
		virtual void Draw() = 0;					  // while(true) {stateObj->Update();}

		virtual void Pause() {};
		virtual void Start() {};
	};
}  // namespace Engine



