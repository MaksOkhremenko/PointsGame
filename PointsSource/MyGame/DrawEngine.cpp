#include "DrawEngine.h"

DrawEngine::DrawEngine()
{
	texture.loadFromFile("gate.png");
	sprite.setTexture(texture);
	font.loadFromFile("ofont.ru_Marutya.ttf");
	textRed.setFont(font);
	textRed.setPosition(0, SCREEN_HEIGHT - GATE_SIZE * 2);
	textRed.setCharacterSize(GATE_SIZE * 2);
	textRed.setFillColor(sf::Color::Red);
	textBlue.setFont(font);
	textBlue.setPosition(0, SCREEN_HEIGHT - GATE_SIZE * 4);
	textBlue.setCharacterSize(GATE_SIZE * 2);
	textBlue.setFillColor(sf::Color::Blue);
	redScore.setFont(font);
	redScore.setPosition(GATE_SIZE * 8, SCREEN_HEIGHT - GATE_SIZE * 2);
	redScore.setCharacterSize(GATE_SIZE * 2);
	redScore.setFillColor(sf::Color::Red);
	blueScore.setFont(font);
	blueScore.setPosition(GATE_SIZE * 5, SCREEN_HEIGHT - GATE_SIZE * 4);
	blueScore.setCharacterSize(GATE_SIZE * 2);
	blueScore.setFillColor(sf::Color::Blue);
	winnerText.setFont(font);
	winnerText.setCharacterSize(GATE_SIZE * 2);
	for (int i = 0; i < 3; i++)
	{
		conviction[i].setFont(font);
		conviction[i].setFillColor(sf::Color::Black);
		conviction[i].setCharacterSize(GATE_SIZE * 2);
	}
	conviction[0].setPosition(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4);
	conviction[0].setString(L"Завертиши гру?");
	conviction[1].setPosition(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4 + GATE_SIZE * 3);
	conviction[1].setString(L"E  nter - так");
	conviction[2].setPosition(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4 + GATE_SIZE * 6);
	conviction[2].setString(L"Space - продовжити");
	menuName.setFont(font);
	menuName.setCharacterSize(GATE_SIZE * 4);
	menuName.setFillColor(sf::Color::Blue);
	menuName.setPosition(SCREEN_WIDTH / GATE_SIZE * 6.75f, SCREEN_HEIGHT / GATE_SIZE * 2);
	menuName.setString(L"Точки");
	menuStart.setFont(font);
	menuStart.setCharacterSize(GATE_SIZE * 2);
	menuStart.setFillColor(sf::Color::Black);
	menuStart.setPosition(SCREEN_WIDTH / GATE_SIZE * 7.5f, SCREEN_HEIGHT / GATE_SIZE * 8);
	menuStart.setString(L"Почати гру");
	menuRules.setFont(font);
	menuRules.setCharacterSize(GATE_SIZE * 2);
	menuRules.setFillColor(sf::Color::Black);
	menuRules.setPosition(SCREEN_WIDTH / GATE_SIZE * 7, SCREEN_HEIGHT / GATE_SIZE * 11);
	menuRules.setString(L"Правила гри");
	menuExit.setFont(font);
	menuExit.setCharacterSize(GATE_SIZE * 2);
	menuExit.setFillColor(sf::Color::Black);
	menuExit.setPosition(SCREEN_WIDTH / GATE_SIZE * 9.5f, SCREEN_HEIGHT / GATE_SIZE * 14);
	menuExit.setString(L"Вийти");
	menuAbout.setFont(font);
	menuAbout.setCharacterSize(GATE_SIZE);
	menuAbout.setFillColor(sf::Color::Black);
	menuAbout.setPosition(SCREEN_WIDTH / GATE_SIZE, SCREEN_HEIGHT - GATE_SIZE * 5);
	menuAbout.setString(L"Гра була створена за тематикою для виконання \nкурсовоi роботи\nАвтор: Охременко Максим, група 1ПР2\n2022");
	rules.setFont(font);
	rules.setCharacterSize(GATE_SIZE * 1.5f);
	rules.setFillColor(sf::Color::Black);
	rules.setPosition(GATE_SIZE, GATE_SIZE);
	rules.setString(L"У гру потрiбно грати удвох. Гра \nвiдбувається на полi з клiтинками, на \nперетинi кожноi з 4 клiтинок гравець\nможе поставити свою точку.Цiль\nгравця - оточити точку ворога з усiх\nсторiн та захопити ii, обвiвши лiнiєю\nГравцi ходять по черзi.\nПiд час свого ходу гравець може або\nпоставити точку, або обвести лiнiєю\nзахоплену територiю(лише якщо\nвсерединi територii присутня ворожа\nточка).Точка ставиться на ЛКМ,\nна ПКМ гравець перемикається на\nрежим обведення точок.Перемога за \nтим, хто захопив бiльше точок.");
}

DrawEngine::~DrawEngine()
{
}

void DrawEngine::createWindow(const char* name)
{
	window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), name);
}

void DrawEngine::drawFrame(Player red, Player blue, Point allPoints[SCREEN_HEIGHT / GATE_SIZE][SCREEN_WIDTH / GATE_SIZE], Point pointer)
{
	textRed.setPosition(0, SCREEN_HEIGHT - GATE_SIZE * 2);
	textBlue.setPosition(0, SCREEN_HEIGHT - GATE_SIZE * 4);
	redScore.setPosition(GATE_SIZE * 8, SCREEN_HEIGHT - GATE_SIZE * 2);
	blueScore.setPosition(GATE_SIZE * 5, SCREEN_HEIGHT - GATE_SIZE * 4);
	blueScore.setString(std::to_string(blue.getChipsCount()));
	redScore.setString(std::to_string(red.getChipsCount()));
	window.clear(sf::Color::White);
	for (int i = 0; i < SCREEN_WIDTH / GATE_SIZE; i++)
		for (int j = 0; j < SCREEN_HEIGHT / GATE_SIZE; j++)
		{
			sprite.setPosition(i * GATE_SIZE, j * GATE_SIZE);
			window.draw(sprite);
		}
	for (int i = 0; i < SCREEN_HEIGHT / GATE_SIZE; i++)
	{
		for (int j = 0; j < SCREEN_HEIGHT / GATE_SIZE; j++)
		{
			window.draw(allPoints[i][j]);
		}
	}
	for (std::list<sf::VertexArray>::iterator i = blue.getChips().begin(); i != blue.getChips().end(); i++)
	{
		window.draw(*i);
	}
	for (std::list<sf::VertexArray>::iterator i = red.getChips().begin(); i != red.getChips().end(); i++)
	{
		window.draw(*i);
	}
	textBlue.setString(L"Синi:");
	textRed.setString(L"Червонi:");
	window.draw(pointer);
	window.draw(textBlue);
	window.draw(blueScore);
	window.draw(textRed);
	window.draw(redScore);
	window.display();
}

void DrawEngine::drawMenu()
{
	window.clear(sf::Color::White);
	window.clear(sf::Color::White);
	for (int i = 0; i < SCREEN_WIDTH / GATE_SIZE; i++)
		for (int j = 0; j < SCREEN_HEIGHT / GATE_SIZE; j++)
		{
			sprite.setPosition(i * GATE_SIZE, j * GATE_SIZE);
			window.draw(sprite);
		}
	window.draw(menuName);
	window.draw(menuStart);
	window.draw(menuRules);
	window.draw(menuExit);
	window.draw(menuAbout);
	window.display();
}

void DrawEngine::drawConviction()
{
	for(int i = 0; i < 3; i++)
		window.draw(conviction[i]);
	window.display();
}

void DrawEngine::drawResults(sf::Color winner, size_t redScore, size_t blueScore)
{
	this->blueScore.setString(std::to_string(blueScore));
	this->redScore.setString(std::to_string(redScore));
	window.clear(sf::Color::White);
	for (int i = 0; i < SCREEN_WIDTH / GATE_SIZE; i++)
		for (int j = 0; j < SCREEN_HEIGHT / GATE_SIZE; j++)
		{
			sprite.setPosition(i * GATE_SIZE, j * GATE_SIZE);
			window.draw(sprite);
		}
	winnerText.setFillColor(winner);
	if (winner == sf::Color::Red)
	{
		winnerText.setPosition(SCREEN_WIDTH / 5, SCREEN_HEIGHT / 3);
		winnerText.setString(L"Червоний перемiг!!!");
	}
	else if (winner == sf::Color::Blue)
	{
		winnerText.setPosition(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 3);
		winnerText.setString(L"Синiй перемiг!!!");
	}
	else
	{
		winnerText.setPosition(SCREEN_WIDTH / 3, SCREEN_HEIGHT / 3);
		winnerText.setString(L"Нiчия!!!");
	}
	textBlue.setString(L"Синi:");
	textBlue.setPosition(SCREEN_WIDTH / GATE_SIZE * 14, SCREEN_HEIGHT / GATE_SIZE * 12);
	this->blueScore.setPosition(SCREEN_WIDTH / GATE_SIZE * 18, SCREEN_HEIGHT / GATE_SIZE * 12);
	textRed.setString(L"Червонi:");
	textRed.setPosition(SCREEN_WIDTH / GATE_SIZE * 4, SCREEN_HEIGHT / GATE_SIZE * 12);
	this->redScore.setPosition(SCREEN_WIDTH / GATE_SIZE * 11, SCREEN_HEIGHT / GATE_SIZE * 12);
	window.draw(textBlue);
	window.draw(this->blueScore);
	window.draw(textRed);
	window.draw(this->redScore);
	window.draw(winnerText);
	window.display();
}

void DrawEngine::drawRules()
{
	window.clear(sf::Color::White);
	for (int i = 0; i < SCREEN_WIDTH / GATE_SIZE; i++)
		for (int j = 0; j < SCREEN_HEIGHT / GATE_SIZE; j++)
		{
			sprite.setPosition(i * GATE_SIZE, j * GATE_SIZE);
			window.draw(sprite);
		}
	window.draw(rules);
	window.display();
}


sf::RenderWindow& DrawEngine::getWindow()
{
	return window;
}
