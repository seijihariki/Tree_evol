#include <SFML/Graphics.hpp>

#include <iostream>
#include <iomanip>

// Designates possible app states
enum app_state
{
    STARTING    = 0,
    RUNNING     = 1,
    TERMINATING = 2
};

app_state state = STARTING;

void input_thread (sf::RenderWindow *window);                // Handles event polling of the window
void handle_event (sf::RenderWindow *window, sf::Event evn); // Handles individual events
void process_thread ();                                      // Handles simulation and processing
void render_thread (sf::RenderWindow *window);               // Handles rendering to the window

int main()
{
    state = STARTING;

    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");

    // Deactivate drawing context on main thread
    window.setActive(false);

    // Create and launch threads
    sf::Thread processing(&process_thread);
    sf::Thread rendering(&render_thread, &window);

    processing.launch();
    rendering.launch();

    state = RUNNING;

    // Pooling must be made in the same thread as the window was created
    input_thread(&window);

    // Wait for other threads to stop
    processing.wait();
    rendering.wait();

    return 0;
}

void input_thread (sf::RenderWindow *window)
{
    std::cout << "Input thread started\n";
    while (state != TERMINATING)
    {
        sf::Event event;
        while (window->pollEvent(event))
            handle_event(window, event);
    }
    std::cout << "Input thread terminated\n";
}

void handle_event (sf::RenderWindow *window, sf::Event evn)
{
    switch (evn.type)
    {
        case sf::Event::Closed:
        {
            window->close();
            state = TERMINATING;
            break;
        }
        case sf::Event::Resized:
        {
            sf::View view = window->getView();
            view.setSize({evn.size.width, evn.size.height});
            window->setView(view);
            break;
        }
        default:
            break;
    }
}

void process_thread ()
{
    // Time elapsed
    sf::Clock clock;

    std::cout << "Processing thread started\n";
    while (state != TERMINATING)
    {
        // Time delta from last frame
        sf::Time dt = clock.restart();

        // Processing is done here
    }
    std::cout << "Processing thread terminated\n";
}

void render_thread (sf::RenderWindow *window)
{
    // Setting up window for drawing...
    window->setActive();
    window->setFramerateLimit(100);

    // Time elapsed
    sf::Clock clock;

    std::cout << "Rendering thread started\n";
    while (state != TERMINATING)
    {
        // Time delta from last frame
        sf::Time dt = clock.restart();

        // Clear window for drawing
        window->clear();

        // Drawing is done here

        window->display();
    }
    std::cout << "Rendering thread terminated\n";
}