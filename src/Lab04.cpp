#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <array_list.h>  // Include the header for ArrayList
#include <string>
#include <random>
#include "WordReader.h"

class TextCircle
{
private:
    sf::Text my_text;
    sf::CircleShape my_circle;
    float speed;

public:
    TextCircle(sf::Font& the_font) : my_text(the_font)
    {
    }

    void setSpeed(float cir_speed)
    {
        speed = cir_speed;
    }

    void update(float delta_time)
    {
        float new_y = my_circle.getPosition().y + speed * delta_time; // Update position based on time
        my_circle.setPosition(sf::Vector2f(my_circle.getPosition().x, new_y));  // Update Y position (moving down)
        my_text.setPosition(sf::Vector2f(my_text.getPosition().x, new_y));  // Update text position to match circle
        my_text.rotate(sf::degrees(1));  // Rotate text for some effect
        
    }

    float get_ypos() {
        return my_circle.getPosition().y;
    }

    void set_position(float x, float y)
    {
        my_text.setPosition(sf::Vector2f(x, y));
        my_circle.setPosition(sf::Vector2f(x, y));
    }

    void setColor(sf::Color color)
    {
        my_circle.setFillColor(color);
    }

    void draw(sf::RenderWindow& rw)
    {
        rw.draw(my_circle);
        rw.draw(my_text);
    }

    void set_text(std::string s)
    {
        my_text.setString(s);
    }

    sf::FloatRect getBounds() const
    {
        return my_text.getLocalBounds();
    }
};

int main(int argc, char** argv)
{
    // Create a window
    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "Text Circles");

    // Load a font
    sf::Font my_font;
    if (!my_font.openFromFile("..\\..\\media\\Oswald\\static\\Oswald-Regular.ttf")) {
        std::cerr << "Error: Could not load font!" << std::endl;
        return -1;  // Exit if font loading fails
    }

    // Arrays to hold all the TextCircle objects (instead of std::vector)
    ssuds::ArrayList<float> x_list;
    ssuds::ArrayList<float> y_list;
    ssuds::ArrayList<std::string> word_list;
    ssuds::ArrayList<float> speed_list;
    ssuds::ArrayList<int> radius_list;
    ssuds::ArrayList<int> color_rlist;
    ssuds::ArrayList<int> color_glist;
    ssuds::ArrayList<int>color_blist;

    // Timer to spawn new circles every second
    sf::Clock spawnClock;

    // Random number generator for speed and positions
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> speedDist(0, 20);
    std::uniform_int_distribution<> posDist(50, 750);

    // WordReader to get a random word
    WordReader wordReader("..\\..\\media\\scowl.txt");

    // Populate the lists with random data (for simplicity, just populating with a few words and positions)
    

    // Create TextCircle objects to hold the circles and words
    std::vector<TextCircle> circles;

    while (window.isOpen())
    {
        // Event handling loop
        while (const std::optional event = window.pollEvent())
        {
            // We use event to see if it's something we care about
            if (event->is<sf::Event::Closed>())
            {
                // The quit button was pressed.
                window.close();
            }
        }

        // Spawn a new circle every second
        if (spawnClock.getElapsedTime().asSeconds() >= 1.0f)
        {
            spawnClock.restart(); // Reset the spawn clock

            std::string rand_word = wordReader.getRandomWord();

            x_list.append(rand()%800);  // Random X position
            y_list.append(0);  // Random Y position
            color_rlist.append(rand()%255);
            color_glist.append(rand() % 255);
            color_blist.append(rand() % 255);
            word_list.append(rand_word);  // Random word from file
            speed_list.append(rand()%30);  // Random speed
            radius_list.append(sizeof(rand_word));
            // Create and draw all circles from the lists
            for (int i = 0; i < x_list.size(); i++)
            {

                float x = x_list[i];
                float y = y_list[i];
                std::string s = word_list[i];
                float speed = speed_list[i];
                int color_r = color_rlist[i];
                int color_g = color_glist[i];
                int color_b = color_blist[i];
                TextCircle temp(my_font);
                temp.set_position(x, y);
                temp.set_text(s);
                temp.setSpeed(speed_list[i]);
                temp.set_text(word_list[i]);
                temp.setColor(sf::Color(color_r,color_g, color_b));


                circles.push_back(temp);  // Add to the list of circles
            }
        }

        // Clear the window
        window.clear();

        float delta_time = spawnClock.getElapsedTime().asSeconds();

        // Update and draw all circles
        // Iterate and remove off-screen circles
        for (auto it = circles.begin(); it != circles.end();)
        {
            it->update(delta_time);  // Update each circle with delta time for smoother movement
            it->draw(window);  // Draw the circle and text

            // Remove circles that go off-screen (y position > 600)
            if (it->get_ypos() > 600)
            {
                it = circles.erase(it);  // Erase and move to the next element
            }
            else
            {
                ++it;  // Only move to next element if no deletion
            }
        }

        // Display the updated window
        window.display();
    }

    return 0;
}
