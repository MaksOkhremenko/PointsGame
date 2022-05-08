#include "Game.h"

bool Game::checkPoint(Point prev, Point current)
{
	int x = (int)(current.getPosition().x + 4) / GATE_SIZE;
	int y = (int)(current.getPosition().y + 4) / GATE_SIZE;
	if (allPoints[x][y].getIsChecked())
		return false;
	int prevX = (int)(prev.getPosition().x + 4) / GATE_SIZE;
	int prevY = (int)(prev.getPosition().y + 4) / GATE_SIZE;
	bool checks[8];
	checks[0] = allPoints[x - 1][y - 1].getPosition() == allPoints[prevX][prevY].getPosition();
	checks[1] = allPoints[x][y - 1].getPosition() == allPoints[prevX][prevY].getPosition();
	checks[2] = allPoints[x + 1][y - 1].getPosition() == allPoints[prevX][prevY].getPosition();
	checks[3] = allPoints[x - 1][y].getPosition() == allPoints[prevX][prevY].getPosition();
	checks[4] = allPoints[x + 1][y].getPosition() == allPoints[prevX][prevY].getPosition();
	checks[5] = allPoints[x - 1][y + 1].getPosition() == allPoints[prevX][prevY].getPosition();
	checks[6] = allPoints[x][y + 1].getPosition() == allPoints[prevX][prevY].getPosition();
	checks[7] = allPoints[x + 1][y + 1].getPosition() == allPoints[prevX][prevY].getPosition();
	bool result = checks[0] || checks[1] || checks[2]
		|| checks[3] || checks[4] || checks[5] || checks[6] || checks[7];
	return result;
}

bool Game::capture(Player& player, Point::owners owner, sf::VertexArray& lines)
{
	int xPos, yPos;
	bool canCapture = false, hadEnemyPoint = false, hadEnd = false, addLine = false;
	for (int i = 0; i < lines.getVertexCount() - 1; i++)
	{
		xPos = (int)(lines[i].position.x + 4) / GATE_SIZE;
		yPos = (int)(lines[i].position.y + 4) / GATE_SIZE;
		if (allPoints[xPos + 1][yPos].getOwner() == owner && (allPoints[xPos + 1][yPos].getIsChecked()))
			continue;
		else
		{
			for (int j = 0; xPos + j < (int)(SCREEN_WIDTH / GATE_SIZE); j++)
			{
				if ((allPoints[xPos + j][yPos].getOwner() != owner && allPoints[xPos + j][yPos].getOwner() != Point::owners::NONE))
				{
					hadEnemyPoint = true;
				}
				if (allPoints[xPos + j][yPos].getIsChecked() && hadEnemyPoint)
				{
					hadEnd = true;
				}
				if (hadEnd && hadEnemyPoint)
					canCapture = true;
			}
			hadEnemyPoint = false;
			hadEnd = false;
		}
		if (canCapture)
			break;
	}
	if (canCapture)
	{
		for (int i = 0; i < lines.getVertexCount() - 1; i++)
		{
			xPos = (int)(lines[i].position.x + 4) / GATE_SIZE;
			yPos = (int)(lines[i].position.y + 4) / GATE_SIZE;
			if (allPoints[xPos + 1][yPos].getOwner() == owner && (allPoints[xPos + 1][yPos].getIsChecked()))
				continue;
			for (int j = 0; xPos + j < (int)(SCREEN_WIDTH / GATE_SIZE) || !addLine; j++)
			{
				if ((allPoints[xPos + j][yPos].getIsChecked()))
				{
					addLine = true;
					for (int k = xPos + 1; k < xPos + j; k++)
					{
						allPoints[k][yPos].setOwner(owner);
						if(!allPoints[k][yPos].getIsCaptured())
							allPoints[k][yPos].setIsCaptured(true);
						else
						{
							if (owner == Point::owners::RED)
								blue.subtractChipCount();
							else
								red.subtractChipCount();
						}
						allPoints[k][yPos].setRadius(5.f);
						if (owner == Point::owners::RED)
							allPoints[k][yPos].setFillColor(sf::Color::Red);
						else
							allPoints[k][yPos].setFillColor(sf::Color::Blue);
						player.addPoint(allPoints[k][yPos]);
						player.addChipCount();
						
					}
				}
			}
		}
	}
	return canCapture;
}

void Game::restart()
{
	red.getChips().clear();
	red.getPoints().clear();
	red.subtractChipCount(100);
	blue.getChips().clear();
	blue.getPoints().clear();
	blue.subtractChipCount(100);
	for (int i = 0; i < SCREEN_HEIGHT / GATE_SIZE; i++)
	{
		for (int j = 0; j < SCREEN_HEIGHT / GATE_SIZE; j++)
		{
			allPoints[i][j].setOwner(Point::owners::NONE);
			allPoints[i][j].setIsCaptured(false);
			allPoints[i][j].setFillColor(sf::Color::White);
			allPoints[i][j].setRadius(0);
		}
	}
}

Game::Game()
{
	red.setColor(sf::Color::Red);
	blue.setColor(sf::Color::Blue);
	pointer.setFillColor(sf::Color::Blue);
	pointer.setRadius(5.f);
	blue.setIsMove(true), red.setIsMove(false);
}

Game::~Game()
{
}

void Game::run()
{
	DrawEngine engine;
	engine.createWindow("Points");
	bool isMenu = true;
	bool conviction = false;
	bool isResults = false;
	bool isRules = false;
	bool isSelecting = false;
	Point begin, prev;
	begin.setPosition(sf::Vector2f(100 * GATE_SIZE - 4, 100 * GATE_SIZE - 4));
	prev.setPosition(sf::Vector2f(100 * GATE_SIZE - 4, 100 * GATE_SIZE - 4));
	sf::VertexArray lines(sf::LineStrip);
	for (int i = 0; i < SCREEN_HEIGHT / GATE_SIZE; i++)
	{
		for (int j = 0; j < SCREEN_HEIGHT / GATE_SIZE; j++)
		{
			allPoints[i][j].setPosition(i * GATE_SIZE - 4, j * GATE_SIZE - 4);
			allPoints[i][j].setFillColor(sf::Color::Black);
			allPoints[i][j].setRadius(0.f);
		}
	}
	while (engine.getWindow().isOpen())
	{
		sf::Vector2i pos = sf::Mouse::getPosition(engine.getWindow());
		int xPointerPos = pos.x / GATE_SIZE;
		int yPointerPos = pos.y / GATE_SIZE;
		pointer.setPosition(xPointerPos * GATE_SIZE - 4, yPointerPos * GATE_SIZE - 4);
		sf::Event event;

		while (isMenu)
		{
			while (engine.getWindow().pollEvent(event))
			{
				if (event.type == sf::Event::Closed ||
					(sf::IntRect(SCREEN_WIDTH / GATE_SIZE * 9.5f, SCREEN_HEIGHT / GATE_SIZE * 14, 150, 50).contains(sf::Mouse::getPosition(engine.getWindow()))
						&& event.type == sf::Event::MouseButtonPressed))
				{
					engine.getWindow().close();
				}
				if (sf::IntRect(SCREEN_WIDTH / GATE_SIZE * 7.5f, SCREEN_HEIGHT / GATE_SIZE * 8, 250, 50).contains(sf::Mouse::getPosition(engine.getWindow())))
					if (event.type == sf::Event::MouseButtonPressed)
						isMenu = false;
				if (sf::IntRect(SCREEN_WIDTH / GATE_SIZE * 7, SCREEN_HEIGHT / GATE_SIZE * 11, 300, 50).contains(sf::Mouse::getPosition(engine.getWindow())))
					if (event.type == sf::Event::MouseButtonPressed)
					{
						isMenu = false;
						isRules = true;
					}
			}
			engine.drawMenu();
		}

		while (isRules)
		{
			while (engine.getWindow().pollEvent(event))
			{
				if (event.type == sf::Event::KeyPressed)
				{
					isRules = false;
					isMenu = true;
				}
				engine.drawRules();
			}
		}

		while (conviction)
		{
			while (engine.getWindow().pollEvent(event))
			{
				if (event.key.code == sf::Keyboard::Enter)
				{
					conviction = false;
					isResults = true;
				}
				else if (event.key.code == sf::Keyboard::Space)
					conviction = false;
			}
			engine.drawConviction();
		}

		while (isResults)
		{
			while (engine.getWindow().pollEvent(event))
			{
				if (event.type == sf::Event::KeyPressed)
				{
					restart();
					isMenu = true;
					isResults = false;
				}
			}
			if (red.getChipsCount() != blue.getChipsCount())
			{
				if (red.getChipsCount() > blue.getChipsCount())
					engine.drawResults(sf::Color::Red, red.getChipsCount(), blue.getChipsCount());
				else
					engine.drawResults(sf::Color::Blue, red.getChipsCount(), blue.getChipsCount());
			}
			else
				engine.drawResults(sf::Color::Green, red.getChipsCount(), blue.getChipsCount());
		}

		while (engine.getWindow().pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				engine.getWindow().close();
			}
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
			{
				conviction = true;
			}
			if(event.type == sf::Event::MouseButtonPressed)
			{
				if (event.key.code == sf::Mouse::Left)
				{
					if (!isSelecting)
					{
						allPoints[xPointerPos][yPointerPos].setRadius(5.f);
						if (allPoints[xPointerPos][yPointerPos].getOwner() == Point::owners::NONE)
						{
							if (red.getIsMove())
							{
								allPoints[xPointerPos][yPointerPos].setFillColor(sf::Color::Red);
								allPoints[xPointerPos][yPointerPos].setOwner(Point::owners::RED);
								pointer.setFillColor(sf::Color::Blue);
								red.addPoint(allPoints[xPointerPos][yPointerPos]);
								red.setIsMove(false);
								blue.setIsMove(true);
							}
							else
							{
								allPoints[xPointerPos][yPointerPos].setFillColor(sf::Color::Blue);
								allPoints[xPointerPos][yPointerPos].setOwner(Point::owners::BLUE);
								pointer.setFillColor(sf::Color::Red);
								blue.addPoint(allPoints[xPointerPos][yPointerPos]);
								blue.setIsMove(false);
								red.setIsMove(true);
							}
						}

					}
					else
					{
						if (red.getIsMove())
						{
							if (allPoints[xPointerPos][yPointerPos].getOwner() != Point::owners::RED)
								break;
							int beginX = (int)(begin.getPosition().x + 4) / GATE_SIZE;
							int beginY = (int)(begin.getPosition().y + 4) / GATE_SIZE;
							int prevX = (int)(prev.getPosition().x + 4) / GATE_SIZE;
							int prevY = (int)(prev.getPosition().y + 4) / GATE_SIZE;
							bool check[3], result = false;
							check[0] = allPoints[xPointerPos][yPointerPos].getOwner() == Point::owners::RED 
								&& !allPoints[xPointerPos][yPointerPos].getIsCaptured();
							check[1] = prev.getPosition() == sf::Vector2f(100 * GATE_SIZE - 4, 100 * GATE_SIZE - 4);
							check[2] = false;
							if (!check[1])
								check[2] = checkPoint(allPoints[prevX][prevY], allPoints[xPointerPos][yPointerPos]);
							result = check[0] && (check[1] || check[2]) ||
								allPoints[xPointerPos][yPointerPos].getPosition() == begin.getPosition();
							if (result)
							{
								if (begin.getPosition() == sf::Vector2f(100 * GATE_SIZE - 4, 100 * GATE_SIZE - 4))
									begin.setPosition(allPoints[xPointerPos][yPointerPos].getPosition());
								prev.setPosition(allPoints[xPointerPos][yPointerPos].getPosition());
								allPoints[xPointerPos][yPointerPos].setIsChecked(true);
								lines.append(sf::Vertex(sf::Vector2f(xPointerPos * GATE_SIZE, yPointerPos * GATE_SIZE)));
							}
							if ((lines.getVertexCount() > 4 && lines[0].position == lines[lines.getVertexCount() - 1].position) && 
								capture(red, Point::owners::RED, lines))
							{
								red.addChip(lines);
								prev.setPosition(sf::Vector2f(100 * GATE_SIZE - 4, 100 * GATE_SIZE - 4));
								lines.clear();
								lines.resize(0);
							}
						}
						else
						{
							if (allPoints[xPointerPos][yPointerPos].getOwner() != Point::owners::BLUE)
								break;
							int beginX = (int)(begin.getPosition().x + 4) / GATE_SIZE;
							int beginY = (int)(begin.getPosition().y + 4) / GATE_SIZE;
							int prevX = (int)(prev.getPosition().x + 4) / GATE_SIZE;
							int prevY = (int)(prev.getPosition().y + 4) / GATE_SIZE;
							bool check[3], result = false;
							check[0] = allPoints[xPointerPos][yPointerPos].getOwner() == Point::owners::BLUE;
							check[1] = prev.getPosition() == sf::Vector2f(100 * GATE_SIZE - 4, 100 * GATE_SIZE - 4);
							check[2] = false;
							if (check[0] && !check[1])
								check[2] = checkPoint(allPoints[prevX][prevY], allPoints[xPointerPos][yPointerPos]);
							result = check[0] && (check[1] || check[2]) ||
								allPoints[xPointerPos][yPointerPos].getPosition() == begin.getPosition();
							if (result)
							{
								if (begin.getPosition() == sf::Vector2f(100 * GATE_SIZE - 4, 100 * GATE_SIZE - 4))
									begin.setPosition(allPoints[xPointerPos][yPointerPos].getPosition());
								prev.setPosition(allPoints[xPointerPos][yPointerPos].getPosition());
								allPoints[xPointerPos][yPointerPos].setIsChecked(true);
								lines.append(sf::Vertex(sf::Vector2f(xPointerPos * GATE_SIZE, yPointerPos * GATE_SIZE)));
							}
							if ((lines.getVertexCount() > 4 && lines[0].position == lines[lines.getVertexCount() - 1].position) &&
								capture(blue, Point::owners::BLUE, lines))
							{
								blue.addChip(lines);
								prev.setPosition(sf::Vector2f(100 * GATE_SIZE - 4, 100 * GATE_SIZE - 4));
								lines.clear();
								lines.resize(0);
							}
						}
					}
				}
				else if (event.key.code == sf::Mouse::Right)
				{
					for (int i = 0; i < SCREEN_HEIGHT / GATE_SIZE; i++)
					{
						for (int j = 0; j < SCREEN_HEIGHT / GATE_SIZE; j++)
						{
							allPoints[i][j].setIsChecked(false);
						}
					}
					begin.setPosition(sf::Vector2f(100 * GATE_SIZE - 4, 100 * GATE_SIZE - 4));
					prev.setPosition(sf::Vector2f(100 * GATE_SIZE - 4, 100 * GATE_SIZE - 4));
					lines.clear();
					lines.resize(0);
					if (red.getIsMove())
					{
						for (int i = 0; i < SCREEN_HEIGHT / GATE_SIZE; i++)
							for (int j = 0; j < SCREEN_WIDTH / GATE_SIZE; j++)
								if (allPoints[i][j].getOwner() == Point::owners::RED && !allPoints[i][j].getIsCaptured())
								{
									allPoints[i][j].setFillColor(sf::Color::Green);
								}
					}
					else
					{
						for (int i = 0; i < SCREEN_HEIGHT / GATE_SIZE; i++)
							for (int j = 0; j < SCREEN_WIDTH / GATE_SIZE; j++)
								if (allPoints[i][j].getOwner() == Point::owners::BLUE && !allPoints[i][j].getIsCaptured())
								{
									allPoints[i][j].setFillColor(sf::Color::Green);
								}
					}
					isSelecting = !isSelecting;
					if (!isSelecting)
					{
						if (red.getIsMove())
						{
							for (int i = 0; i < SCREEN_HEIGHT / GATE_SIZE; i++)
								for (int j = 0; j < SCREEN_WIDTH / GATE_SIZE; j++)
									if (allPoints[i][j].getOwner() == Point::owners::RED)
									{
										allPoints[i][j].setFillColor(sf::Color::Red);
									}
						}
						else
						{
							for (int i = 0; i < SCREEN_HEIGHT / GATE_SIZE; i++)
								for (int j = 0; j < SCREEN_WIDTH / GATE_SIZE; j++)
									if (allPoints[i][j].getOwner() == Point::owners::BLUE)
									{
										allPoints[i][j].setFillColor(sf::Color::Blue);
									}
						}
					}
				}
			}
		}
		engine.drawFrame(red, blue, allPoints, pointer);
			
	}
}