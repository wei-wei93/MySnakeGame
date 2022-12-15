#include "Game.hpp"
#include <SFML/Graphics/CircleShape.hpp>

#include "MainMenu.hpp"

Game::Game() : m_context(std::make_shared<Context>()) //all pointers need to be initialized before using
{
    m_context->m_window->create(sf::VideoMode(768, 432), "SFML works!", sf::Style::Close); //"m_window" is a "unique_ptr<sf::RenderWindow>" 
    // VideoMode for WindowSize, "SFML works!" for title, how about sf::Style::Close?
    // Render Window, export currently displaced graphics scene to an image file or a geometric description file
    // that can be processed by an external Render to produce a final image to show in a window
    m_context->m_states->Add(std::make_unique<MainMenu>(m_context)); //virtual base class
}

Game::~Game() {}

void Game::Run()
{
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    sf::Clock clock; // start ticking when it's created
    sf::Time timeSinceLastFrame = sf::Time::Zero;

    while (m_context->m_window->isOpen())
    {
        //HOW THIS TIME LOOP WORKS?
        timeSinceLastFrame += clock.restart(); ////
        while (timeSinceLastFrame > TIME_PER_FRAME)
        {
            timeSinceLastFrame -= TIME_PER_FRAME; //// System FPS: 60
            //Todo: only process states seems
            
            /*ALL BECAUSE OF THE IMPLEMENT SEPARATE LABELS SETTINGS AND 
            REAL REALISATION, LEADING THE SNAKE MOVEMENT AND KEY ACCEPTANCE
            UNSTABLE*/

            m_context->m_states->ProcessStateChange(); //Process State Changes
            //Init() is executed in ProcessStateChange() method
            //State Changes includes: popcurrent (remove), add (add, replace)
            m_context->m_states->GetCurrent()->ProcessInput(); //Get Inputs, set related labels
            //GetCurrent() returns an unique_pointer of a State
            m_context->m_states->GetCurrent()->Update(TIME_PER_FRAME); //Update and Reflect Inputs
            m_context->m_states->GetCurrent()->Draw(); //constantly draw one picture //animation
           
        }
    }
}