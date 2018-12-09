#include <time.h>
#include <SFML/audio.hpp>
#include <fstream>
#include <cmath>
#include "player.h"
#include "barrier.h"
#include "circleO.h"
#include "button.h"

enum GameState
{
	MENU,
	GAME
};

//void changeState()

void initRound(player &thePlayer, circleO &top, circleO &right, circleO &left, circleO &bottom, barrier &theBarrier, bool &allowChange, bool &hardAllowChange, int &speedCount)
{
	theBarrier.circle.setFillColor(sf::Color(0, 0, 0, 0));
	top.circle.setPosition(400, -100);
	right.circle.setPosition(900, 400);
	left.circle.setPosition(-100, 400);
	bottom.circle.setPosition(400, 900);

	//int genRColor = rand() % 256;
	//int genGColor = rand() % 256;
	//int genBColor = rand() % 256;

	//thePlayer.setLastColor(genRColor, genGColor,genBColor);
	//thePlayer.setColor(genRColor, genGColor, genBColor);

	thePlayer.setColor(rand() % 256, rand() % 256, rand() % 256);
	//std::cout << "player: " << thePlayer.rColor << std::endl;
	thePlayer.setLastColor(thePlayer.rColor, thePlayer.gColor, thePlayer.bColor);
	//std::cout << "player lastR: " << thePlayer.lastRColor << std::endl;

	theBarrier.circle.setPosition(400, 400);
	theBarrier.interiorCircle.setPosition(400, 400);
	theBarrier.circle.setRadius(586); 
	theBarrier.circle.setOrigin(586, 586);
	theBarrier.circle.setPosition(400, 400);
	theBarrier.interiorCircle.setRadius(566);
	theBarrier.interiorCircle.setOrigin(586, 586);
	theBarrier.interiorCircle.setPosition(400, 400);

	theBarrier.setColor(rand() % 256, rand() % 256, rand() % 256);
	//std::cout << "Target: " << theBarrier.rColor << std::endl;

	int whichDirection = rand() % 4;
	//std::cout << whichDirection << std::endl;

	switch (whichDirection)
	{
		case 0:
			top.setColor(2 * theBarrier.rColor - thePlayer.rColor, 2 * theBarrier.gColor - thePlayer.gColor, 2 * theBarrier.bColor - thePlayer.bColor);
			break;
		case 1:
			right.setColor(2 * theBarrier.rColor - thePlayer.rColor, 2 * theBarrier.gColor - thePlayer.gColor, 2 * theBarrier.bColor - thePlayer.bColor);
			break;
		case 2:
			left.setColor(2 * theBarrier.rColor - thePlayer.rColor, 2 * theBarrier.gColor - thePlayer.gColor, 2 * theBarrier.bColor - thePlayer.bColor);
			break;
		case 3:
			bottom.setColor(2 * theBarrier.rColor - thePlayer.rColor, 2 * theBarrier.gColor - thePlayer.gColor, 2 * theBarrier.bColor - thePlayer.bColor);
			break;
	}

	if (whichDirection != 0)
	{
		top.setColor(rand() % 256, rand() % 256, rand() % 256);
	}
	if (whichDirection != 1)
	{
		right.setColor(rand() % 256, rand() % 256, rand() % 256);
	}
	if (whichDirection != 2)
	{
		left.setColor(rand() % 256, rand() % 256, rand() % 256);
	}
	if (whichDirection != 3)
	{
		bottom.setColor(rand() % 256, rand() % 256, rand() % 256);
	}

	allowChange = true;
	hardAllowChange = true;
	//theBarrier.isActive = true;
}

int main()
{
	//Window and seed choice for random num
	sf::RenderWindow window(sf::VideoMode(800, 800), "Colorsion");
	//window.setFramerateLimit(60);

	srand(time(NULL));

	//Music
	sf::Music background;
	if (!background.openFromFile("sound/background.wav"))
	{
		return -1; //error
	}
	background.play();
	background.setLoop(true);

	//HighScore
	int highScore = 0;

	//fstream
	std::ifstream fileStream;
	fileStream.open("highScore.txt", std::ios::in);
	if (fileStream.is_open())
	{
		fileStream >> highScore;
	}
	else
	{
		highScore = 0;
	} 
	fileStream.close();

	//Font
	sf::Font candal;
	candal.loadFromFile("font/Candal.ttf");

	//Game object init
	player thePlayer;

	circleO top;
	circleO right;
	circleO left;
	circleO bottom;

	barrier theBarrier;

	//Menu
	button start(400, 500, 400, 100, "START", 72);

	//Title
	sf::Text title("Colorsion", candal, 120);
	title.setOutlineThickness(3);
	title.setOutlineColor(sf::Color::White);
	title.setFillColor(sf::Color());
	sf::FloatRect titleRect = title.getLocalBounds();
	title.setOrigin(titleRect.left + titleRect.width / 2.0f, titleRect.top + titleRect.height / 2.0f);
	title.setPosition(400, 200);

	//Highscore
	sf::Text highScoreTex;
	highScoreTex.setFont(candal);
	highScoreTex.setCharacterSize(36);
	highScoreTex.setString("High Score: " + std::to_string(highScore));
	highScoreTex.setOutlineThickness(3);
	highScoreTex.setOutlineColor(sf::Color::White);
	highScoreTex.setFillColor(sf::Color());
	sf::FloatRect highScoreTexRect = highScoreTex.getLocalBounds();
	highScoreTex.setOrigin(highScoreTexRect.left + highScoreTexRect.width / 2.0f, highScoreTexRect.top + highScoreTexRect.height / 2.0f);
	highScoreTex.setPosition(400, 340);

	//Title color stuff
	int dr = 0;
	int dg = 0;
	int db = 0;
	sf::Uint8 r = 255, g = 0, b = 0;

	//Starting GameState
	GameState currentState = MENU;

	bool allowChange = true;
	bool hardAllowChange = true;
	bool allowDraw = false;
	bool newRound = false;

	int score = 0;
	
	thePlayer.isActive = false; 
	top.isActive = false;
	right.isActive = false;
	left.isActive = false;
	bottom.isActive = false;
	theBarrier.isActive = false;

	//Score
	sf::Text scoreText;
	scoreText.setFont(candal);
	scoreText.setString(std::to_string(score));
	scoreText.setCharacterSize(36);
	scoreText.setFillColor(sf::Color::White);
	scoreText.setOutlineColor(sf::Color::Black);
	scoreText.setOutlineThickness(3);
	scoreText.setPosition(750, 10);

	//Speed
	int speedCount = 4;
	float speed = 1;

	//Time
	sf::Clock clock;
	float timer = 0;
	float lastTime = 0;

	float colorTimer = 0;
	float lastColorTime = 0;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			//Close window event
			if (event.type == sf::Event::Closed)
			{
				std::ofstream writeScore;
				writeScore.open("highScore.txt", std::ios::out);
				if (writeScore.is_open())
				{
					writeScore << highScore;
				}
				else
				{
					//error
				}
				fileStream.close();
				window.close();
			}
			//KeyPressed input
			if (event.type == sf::Event::KeyPressed)
			{
				if (currentState == GAME)
				{
					if (allowChange)
					{
						switch (event.key.code)
						{
						//add/average player color w/ circleO
						case sf::Keyboard::Up:
							allowChange = false;
							//std::cout << "top before add " << top.rColor << std::endl;
							thePlayer.addColor(top.rColor, top.gColor, top.bColor);
							//std::cout << "top AFTER add " << top.rColor << std::endl;
							break;
						case sf::Keyboard::Right:
							allowChange = false;
							thePlayer.addColor(right.rColor, right.gColor, right.bColor);
							break;
						case sf::Keyboard::Left:
							allowChange = false;
							thePlayer.addColor(left.rColor, left.gColor, left.bColor);
							break;
						case sf::Keyboard::Down:
							allowChange = false;
							thePlayer.addColor(bottom.rColor, bottom.gColor, bottom.bColor);
							break;
						}
					}
					//Reset player color to start of round
					if (hardAllowChange && event.key.code == sf::Keyboard::Space)
					{
						//std::cout << "lastR Before: " << thePlayer.lastRColor << std::endl;
						thePlayer.setColor(thePlayer.lastRColor, thePlayer.lastGColor, thePlayer.lastBColor);
						//std::cout << "lastR AFTER: " << thePlayer.lastRColor << std::endl;
						//std::cout << "after space player: " << thePlayer.rColor << std::endl;
						allowChange = true;
					}
				}
			}
			if (event.type == sf::Event::MouseButtonPressed)
			{
				sf::Vector2i mouseCoord = sf::Mouse::getPosition(window);
				sf::Vector2f mouseWorld = window.mapPixelToCoords(mouseCoord);
				float mouseCoordX = mouseWorld.x;
				float mouseCoordY = mouseWorld.y;
				if (currentState == MENU)
				{
					if (event.key.code == sf::Mouse::Left)
					{
						if (start.rect.getGlobalBounds().contains(mouseCoordX, mouseCoordY))
						{
							currentState = GAME;
							allowChange = true;
							hardAllowChange = true;
							allowDraw = true;
							//bool newRound = true;

							score = 0;
							scoreText.setString(std::to_string(score));

							thePlayer.isActive = true;
							top.isActive = true;
							right.isActive = true;
							left.isActive = true;
							bottom.isActive = true;
							theBarrier.isActive = true;
							initRound(thePlayer, top, right, left, bottom, theBarrier, allowChange, hardAllowChange, speedCount);
							speedCount = 4;
						}
					}
				}
			}
		}

		//GAME once per frame
		if (currentState == GAME)
		{
			//New Round -- Player succeeded
			if (theBarrier.interiorCircle.getRadius() <= 20 && theBarrier.bColor == thePlayer.bColor && theBarrier.gColor == thePlayer.gColor && theBarrier.bColor == thePlayer.bColor)
			{
				theBarrier.isActive = false;
				std::cout << "newRound" << std::endl;
				newRound = true;
			}

			//New Round
			if (newRound)
			{
				if (scoreText.getString() == "0")
				{
					score = 1;
				}
				else
				{
					score++;
				}
				scoreText.setString(std::to_string(score));

				speedCount++;

				initRound(thePlayer, top, right, left, bottom, theBarrier, allowChange, hardAllowChange, speedCount);
				newRound = false;
			}

			//Move circles and ring
			timer = clock.getElapsedTime().asSeconds() - lastTime;
			if (timer >= 0.01f/(speedCount/4.0f))
			{
				lastTime = clock.getElapsedTime().asSeconds();
				if (top.circle.getPosition().y != 400)
				{
					top.circle.setPosition(top.circle.getPosition().x, top.circle.getPosition().y + 1);
					right.circle.setPosition(right.circle.getPosition().x - 1, right.circle.getPosition().y);
					left.circle.setPosition(left.circle.getPosition().x + 1, left.circle.getPosition().y);
					bottom.circle.setPosition(bottom.circle.getPosition().x, bottom.circle.getPosition().y - 1);
				}
				else
				{
					//hardAllowChange = false;
				}

				if (theBarrier.interiorCircle.getRadius() > 20)
				{
					theBarrier.circle.setRadius(theBarrier.circle.getRadius() - 1);
					theBarrier.circle.setPosition(400, 400);
					theBarrier.circle.setOrigin(theBarrier.circle.getRadius(), theBarrier.circle.getRadius());

					theBarrier.interiorCircle.setRadius(theBarrier.interiorCircle.getRadius() - 1);
					theBarrier.interiorCircle.setPosition(400, 400);
					theBarrier.interiorCircle.setOrigin(theBarrier.interiorCircle.getRadius(), theBarrier.interiorCircle.getRadius());
					theBarrier.isActive = true;
				}
				else
				{
					std::cout << "MENU" << std::endl;
					currentState = MENU;
					if (score > highScore)
					{
						highScore = score;
						highScoreTex.setString("High Score: " + std::to_string(highScore));
					}
					score = 0;
					allowChange = false;
					hardAllowChange = false;
					allowDraw = false;
					newRound = false;

					thePlayer.isActive = true;
					top.isActive = true;
					right.isActive = true;
					left.isActive = true;
					bottom.isActive = true;
					theBarrier.isActive = true;
				}
			}
		}
		//MENU once per frame
		else if (currentState == MENU)
		{
			//Title color change
			colorTimer = clock.getElapsedTime().asSeconds() - lastColorTime;
			if (colorTimer >= 0.015f)
			{
				lastColorTime = clock.getElapsedTime().asSeconds();
				r += dr;
				g += dg;
				b += db;

				if (r == 255 && g == 0 && b == 0)
				{
					dr = 0; dg = 1; db = 0;
				}

				if (r == 255 && g == 255 && b == 0)
				{
					dr = -1; dg = 0; db = 0;
				}

				if (r == 0 && g == 255 && b == 0)
				{
					dr = 0; dg = 0; db = 1;
				}

				if (r == 0 && g == 255 && b == 255)
				{
					dr = 0; dg = -1; db = 0;
				}

				if (r == 0 && g == 0 && b == 255)
				{
					dr = 1; dg = 0; db = 0;
				}

				if (r == 255 && g == 0 && b == 255)
				{
					dr = 0; dg = 0; db = -1;
				}

				title.setFillColor(sf::Color(r, g, b));
			}
		}

		//Window
		window.clear();
		//Draw GAME
		if (currentState == GAME)
		{
			if (theBarrier.isActive)
			{
				window.draw(theBarrier.circle);
				window.draw(theBarrier.interiorCircle);
			}
			if (top.isActive)
			{
				window.draw(top.circle);
			}
			if (right.isActive)
			{
				window.draw(right.circle);
			}
			if (left.isActive)
			{
				window.draw(left.circle);
			}
			if (bottom.isActive)
			{
				window.draw(bottom.circle);
			}
			if (thePlayer.isActive)
			{
				window.draw(thePlayer.circle);
			}
			window.draw(scoreText);
		}
		else if (currentState == MENU)
		{
			window.draw(title);
			window.draw(highScoreTex);
			window.draw(start.rect);
			window.draw(start.text);
		}
		window.display();
	}
}