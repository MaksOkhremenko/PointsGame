#pragma once
#define SCREEN_WIDTH 700
#define SCREEN_HEIGHT 700
#define GATE_SIZE 25
#include <SFML/Graphics.hpp>
#include "DrawEngine.h"
#include "Player.h"
#include "Point.h" 

class Game
{
private:
    Player blue, red;
    Point allPoints[SCREEN_HEIGHT / GATE_SIZE][SCREEN_WIDTH / GATE_SIZE];
    Point pointer;
    bool checkPoint(Point prev, Point current);
    bool capture(Player& player, Point::owners owner, sf::VertexArray& lines);
    void restart();
public:
    Game();
    ~Game();
	void run();
};
