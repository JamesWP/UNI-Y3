
//
// Disclamer:
// ----------
//
// This code will work only if you selected window, graphics and audio.
//
// In order to load the resources like cute_image.png, you have to set up
// your target scheme:
//
// - Select "Edit Scheme…" in the "Product" menu;
// - Check the box "use custom working directory";
// - Fill the text field with the folder path containing your resources;
//        (e.g. your project folder)
// - Click OK.
//

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Consts.h"
#include "Engine.hpp"
#include "FPS.h"

EngineConfig conf;

int main(int argc, char const** argv)
{

  // Create the main window
  sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "SFML window");

  // Create a graphical text to display
  sf::Font font;
  if (!font.loadFromFile("ufonts.com_courier-new.ttf")) {
    return EXIT_FAILURE;
  }
  sf::Text text("Hello SFML", font, 50);
  sf::Text stateMsg("Hello SFML", font, 50);
  stateMsg.move(sf::Vector2f(0,40));
  text.setColor(sf::Color::White);


  Engine e;
  sf::Clock clock;
  int64_t time = clock.getElapsedTime().asMicroseconds();
  FPS fpsCounter;

  window.setVerticalSyncEnabled(true);

  // Start the game loop
  while (window.isOpen())
  {
    // Process events
    sf::Event event;
    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::MouseMoved) {
        conf.setMousePosition(sf::Vector2i(event.mouseMove.x,event.mouseMove.y));
      }

      // Close window: exit
      if (event.type == sf::Event::Closed) {
        window.close();
      }

      // Escape pressed: exit
      if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
        window.close();
      }

      // Space pressed: next mode
      if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
        conf.nextState();
      }
    }

    // Clear screen
    window.clear();

    int64_t newTime = clock.getElapsedTime().asMicroseconds();
    int64_t elapsedTime = newTime - time;
    time = newTime;

    e.update(elapsedTime);
    e.draw(&window);

    fpsCounter.update();

    text.setString(std::to_string(fpsCounter.getFPS()*100000000000+ e.objCount()));
    stateMsg.setString(conf.getStateMsg());

    // Draw the string
    window.draw(text);
    window.draw(stateMsg);

    // Update the window
    window.display();
  }

  return EXIT_SUCCESS;
}
