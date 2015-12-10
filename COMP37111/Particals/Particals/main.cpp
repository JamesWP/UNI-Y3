
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
#include <chrono>
#include <thread>
#include "Consts.h"
#include "Engine.hpp"
#include "FPS.h"
#include "Timer.hpp"

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
  sf::Text text("Hello SFML", font, 10);
  sf::Text stateMsg("Hello SFML", font, 20);
  sf::Text stateDesc("Hello SFML", font, 14);
  sf::Text instructions("Space: change mode (hold shift to reverse)\nEnter: create emmitter\nBackspace: clear screen", font, 14);
  text.move(5,5);
  stateMsg.move(sf::Vector2f(5,20));
  stateDesc.move(sf::Vector2f(5,40));
  instructions.move(5,HEIGHT-50);
  text.setColor(sf::Color::White);



  Engine e;
  sf::Clock clock;
  conf.setClock(&clock);
  int64_t time = clock.getElapsedTime().asMicroseconds();
  FPS fpsCounter;

  window.setVerticalSyncEnabled(true);

/*
  Timer update;
  update.start(std::chrono::microseconds(10), [&]{



    fpsCounter.update();
  });
 */

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
        if(!event.key.shift)
          conf.nextState();
        else
          conf.prevState();
      }
      if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return) {
        conf.enterPressed();
      }
      if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::BackSpace) {
        conf.backspacePressed();
      }
    }

    // Clear screen
    window.clear();

    int64_t newTime = clock.getElapsedTime().asMicroseconds();
    int64_t elapsedTime = newTime - time;
    time = newTime;
    fpsCounter.update();
    e.update(elapsedTime);
    e.draw(&window);


    text.setString("fps: " + std::to_string(fpsCounter.getFPS()) + "   particle count: " + std::to_string(e.objCount()) + "   emitter count: " + std::to_string(e.emmCount()));
    stateMsg.setString(conf.getStateMsg());
    stateDesc.setString(conf.getStateDesc());

    // Draw the string
    window.draw(text);
    window.draw(stateMsg);
    window.draw(stateDesc);
    window.draw(instructions);

    // Update the window
    window.display();
  }

//  update.stop();

  return EXIT_SUCCESS;
}
