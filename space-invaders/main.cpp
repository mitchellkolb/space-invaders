#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include "point_interface.h"
#include "points.h"


/*
If you're using mac use these commands to run the game

g++ -c main.cpp points.cpp
g++ main.o points.o -o sfml-app -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system
./sfml-app
*/

int w = 500;
int h = (w / 2) * 3;
const int num_enemies = 6;

struct delta
{
	float dx;
	float dy;
};

int main()
{
	srand(time(NULL));

	Points player_pts;
	player_pts.set_pts(0);

	float speed = 5;
	delta e[num_enemies], p, b;
	for (int i = 0; i < num_enemies; ++i)
	{
		e[i].dx = speed;
		e[i].dy = 0.25;
	}
	b.dx = 0;
	b.dy = 0;
	p.dx = 0;
	p.dy = 0;

	sf::RenderWindow window(sf::VideoMode(w, h), "Space Invaders!");
	window.setFramerateLimit(30);

	//Adding a background texture
    sf::Texture texture;
    if (!texture.loadFromFile("images/background1.jpeg"))
    {}
    sf::Sprite background(texture);

	sf::CircleShape player(25.f);

	sf::CircleShape enemies[num_enemies];
	for (int i = 0; i < num_enemies; ++i)
		enemies[i].setRadius(30);
	
	sf::CircleShape shape(20.f); // player bullet

	player.setPosition(w / 2, h - 55);
	for (int i = 1, j = 10, k = num_enemies; i <= num_enemies; ++i)
	{
		if (i % 3 == 0)
			j -= 5;
		enemies[i - 1].setPosition(i * w / k, j);
	}
	shape.setPosition(w / 2, h - 10);

	//Adds the sounds into the game for effects and background sound
	sf::SoundBuffer explosionbuffer;
	sf::SoundBuffer shootBuffer;
	sf::SoundBuffer musicBuffer;
	shootBuffer.loadFromFile("Sound/shoot.wav");
	sf::Sound shoot(shootBuffer);
	explosionbuffer.loadFromFile("Sound/explosion.wav");
	sf::Sound explosion(explosionbuffer);
	musicBuffer.loadFromFile("Sound/Interstellar-Odyssey.ogg");
	sf::Sound music(musicBuffer);

	
	
	//After player object has been created and position has been set 
	//This will create/attach the texture
	sf::Texture playerTexture;
    playerTexture.loadFromFile("images/ship1.gif");
    player.setTexture(&playerTexture);

    //After bullet object has been created and position has been set 
	//This will create/attach the texture
	sf::Texture bulletTexture;
    bulletTexture.loadFromFile("images/missile.png");
    shape.setTexture(&bulletTexture);

    //After enemies object has been created and position has been set 
	//This will create/attach the texture
	sf::Texture enemiesTexture;
    enemiesTexture.loadFromFile("images/alien_ship.png");
    for(int i = 0; i < num_enemies; i++)
	{
    	enemies[i].setTexture(&enemiesTexture);
    }

    //Background music
	music.setVolume(20);
	music.play();
	music.setLoop(true);

	//Ending text
	sf::Font font;
    if(!font.loadFromFile("Tuffy.ttf"))
    {
    	//error
    }
    sf::Text text1;
    text1.setFont(font);
    text1.setString("The Game has Ended.");
    text1.setCharacterSize(40);
    text1.setFillColor(sf::Color::Red);
    text1.setStyle(sf::Text::Bold | sf::Text::Underlined);
    text1.setPosition(w/7,h/3);

    sf::Text text2;
    text2.setFont(font);
    text2.setString("Press 'S' Key to Close Window");
    text2.setCharacterSize(30);
    text2.setFillColor(sf::Color::Red);
    text2.setStyle(sf::Text::Bold);
    text2.setPosition(w/9,h/2);

	//Creates Pause Bool
	bool pause = true;

	//Game functions
	while (window.isOpen() && pause == true)
	{
		
		sf::Vector2f pPos = player.getPosition();
		sf::Vector2f ePos[num_enemies];
		for (int i = 0; i < num_enemies; ++i)
			ePos[i] = enemies[i].getPosition();
		sf::Vector2f bPos = shape.getPosition();

		if (bPos.y < 0) // bullet out of bounds
		{
			b.dy = 0;
			shape.setPosition(pPos.x + 8, pPos.y + 2);
		}
		else if (b.dy == 0)
			shape.setPosition(pPos.x + 8, pPos.y + 2);
		for (int i = 0; i < num_enemies; ++i)
		{
			if (ePos[i].x < 0) // enemy/wall collision
				e[i].dx = speed;
			else if (ePos[i].x > w - 30)
				e[i].dx = -speed;
			enemies[i].move(e[i].dx, e[i].dy);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) // player shoots
		{
			shoot.setVolume(10);
			shoot.play();
			
			shape.setPosition(pPos.x + 8, pPos.y + 2);
			b.dy = -speed;
		}
		for (int i = 0; i < num_enemies; ++i)
		{
			if (bPos.y <= ePos[i].y + 30 && bPos.y >= ePos[i].y) // enemy/bullet collision
			{
				if (bPos.x <= ePos[i].x + 30 && bPos.x >= ePos[i].x) // same as &&
				{
					//Sounds
					explosion.setVolume(10);
					explosion.play();

					enemies[i].setPosition(rand() % w + 1, 10); // new enemy
					speed += 1; // increase speed
					e[i].dx = speed;
					e[i].dy += .1;
					player_pts.add_pt();
					i = num_enemies; // only 1 collision possible so we dont need to check rest of enemies
				}
			}
		}
		shape.move(b.dx, b.dy);

		if (pPos.x >= w) // player loops around screen
			player.setPosition(0, h - 55);
		else if (pPos.x <= 0)
			player.setPosition(w, h - 55);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) // player moves
			p.dx = -(speed + 1);
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			p.dx = speed + 1;
		else // player doesnt move
			p.dx = 0;
		player.move(p.dx, p.dy);

		for (int i = 0; i < num_enemies; ++i)
		{
			if (ePos[i].y > h)
			{
				pause = false;
				i = num_enemies;
			}
		}

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(background);
		window.draw(player);
		for (int i = 0; i < num_enemies; ++i)
			window.draw(enemies[i]);
		window.draw(shape);
		window.display();
	}

	//After game has ended with pause
	while(window.isOpen() && pause == false)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			window.close();
		}

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.draw(background);
		window.draw(player);
		for (int i = 0; i < num_enemies; ++i)
			window.draw(enemies[i]);
		window.draw(shape);
		window.draw(text1);
		window.draw(text2);
		window.display();
	}

	//Prints out the score to the console
	std::cout << "\nScore: ";
	player_pts.pt_out();
	std::cout << "\n";

	return 0;
}