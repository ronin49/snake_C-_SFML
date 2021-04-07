#include <SFML/Graphics.hpp>
class Map {
public:
	int width = 20;
	int height = 10;
} map;
int main() {
    sf::RenderWindow window(sf::VideoMode(600, 400), "snake");
	window.setFramerateLimit(60);
	std::vector<sf::Vector2i> snake;
	for(int i = 0; i < 3; i++)
		snake.push_back({4,i});
	sf::Vector2i direction(0,1);
	sf::Clock clock;
	sf::Time time;
    while (window.isOpen()) {
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) &&
		snake[snake.size()-1]+sf::Vector2i(-1,0)!=snake[snake.size()-2])
			direction = {-1,0};
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) &&
		snake[snake.size()-1]+sf::Vector2i(1,0)!=snake[snake.size()-2])
			direction = {1,0};
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) &&
		snake[snake.size()-1]+sf::Vector2i(0,1)!=snake[snake.size()-2])
			direction = {0,1};
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) &&
		snake[snake.size()-1]+sf::Vector2i(0,-1)!=snake[snake.size()-2])
			direction = {0,-1};
		time += clock.restart();
		if(time.asMilliseconds()>=200) {
			time -= sf::milliseconds(200);
			for(int i = 0; i < snake.size()-1;i++) {
				snake[i] = snake[i+1];
			}
			snake[snake.size()-1] += direction;
		}
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear(sf::Color(255,255,255));
		sf::RectangleShape rs;
		rs.setFillColor(sf::Color(249, 228, 9));
		rs.setOutlineColor(sf::Color(35, 118, 255));
		rs.setOutlineThickness(-4);
		rs.setSize({(float)window.getSize().x/map.width,(float)window.getSize().y/map.height});
		for(auto s : snake) {
			rs.setPosition(s.x*rs.getSize().x,s.y*rs.getSize().y);
			window.draw(rs);
		}
        window.display();
    }
    return 0;
}