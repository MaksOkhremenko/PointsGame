#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Point.h"
#include "Player.h"
#include "Game.h"

class DrawEngine
{
private:
    sf::RenderWindow window;
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Font font;
    sf::Text textRed, textBlue, redScore, blueScore, winnerText, conviction[3];
    sf::Text menuName, menuStart, menuRules, menuExit, menuAbout, rules;
public:
    DrawEngine();
    ~DrawEngine();
    void createWindow(const char* name);
    void drawFrame(Player red, Player blue, Point allPoints[SCREEN_HEIGHT / GATE_SIZE][SCREEN_WIDTH / GATE_SIZE], Point pointer);
    void drawMenu();
    void drawConviction();
    void drawResults(sf::Color winner, size_t redScore, size_t blueScore);
    void drawRules();
    sf::RenderWindow& getWindow();

};