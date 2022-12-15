#include <SFML/Graphics.hpp>

#include "Game.hpp"

int main()
{
    Game game;  // doesn't need to " = new Game()", it's not Java, I think Java needs this because it has Templates, 
                    // definition perffix at the left might not be class, might be a template, so it needs to specify class once more at the right
                    // but in C++, Class is just Class, say it and name its Obj then it's done!
    // if no args needed to be passed to Obj during definition, don't add "()", or it triggers ERROR
                                                        // just type the name, so instead of Game game();, do Game game;
    game.Run();
    
    return 0;
}