//Classes.h by Sam Brind (class definitions)
#ifndef BATTLESHIPS_H
#define BATTLESHIPS_H

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

struct Coordinate {
	int x;
	int y;
	Coordinate() : x{ 0 }, y{ 0 } {}
	Coordinate(int x_in, int y_in) : x{ x_in }, y{ y_in } {}
};

class Ship {
public:
	Ship() : parts{}, name{ "Empty Ship" } {}
	Ship(bool orientation, int length, Coordinate start, std::string name_in);
	bool Hit(const Coordinate point);
	bool Sunk() const;
	bool Intersects(const Ship &s) const;
	int Length() const;
	Coordinate Start() const;
	std::string Name() const;
private:
	std::vector<Coordinate> parts;
	std::string name;
};

class Board {
public:
	static const int board_height{ 10 };
	static const int board_width{ 10 };
	Board() : ships{} {}
	bool InsertShip(const Ship &s);
	bool TryHit(const Coordinate point);
	bool AllSunk() const;
	void ListShips() const;
	void Clear();
private:
	std::vector<Ship> ships;
};

#endif