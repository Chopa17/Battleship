//Classes.cpp by Sam Brind (class implementations)
#include "Classes.h"

//ship member functions
//constructor (orientation [true/false]->[vertical/horizontal])
Ship::Ship(bool orientation, int length, Coordinate start, std::string name_in) {
	//set up the ship's parts vector with each ship coordinate
	parts.reserve(length);
	for (int i{ 0 }; i < length; i++) {
		if (orientation) {
			parts.emplace_back(Coordinate(start.x, start.y + i));
		} else {
			parts.emplace_back(Coordinate(start.x + i, start.y));
		}
	}
	name = name_in;
}
//is the point a hit on this ship?
bool Ship::Hit(const Coordinate point) {
	for (auto p{ parts.begin() }; p != parts.end(); p++) {
		if (point.x == p->x && point.y == p->y) {
			//delete ship point from hits parts vector
			parts.erase(p);
			return true;
		}
	}
	return false;
}
//is this ship sunk?
bool Ship::Sunk()const {
	return (parts.size() == 0);
}
//does this ship intersect with another ship (s)?
bool Ship::Intersects(const Ship &s)const {
	for (auto p1 : parts) {
		for (auto p2 : s.parts) {
			if (p1.x == p2.x && p1.y == p2.y) { return true; }
		}
	}
	return false;
}
//return ship's length
int Ship::Length()const {
	return (int)parts.size();
}
//return the ship's starting point
Coordinate Ship::Start()const {
	return parts[0];
}
//return the ship's name
std::string Ship::Name()const {
	return name;
}

//board member functions
//insert a ship (s) onto the board (returns true if successful or false if not)
bool Board::InsertShip(const Ship &s) {
	//check ship fits onto the board
	if (s.Start().x < 1 || s.Start().y < 1) { return false; }
	if (s.Start().x + s.Length() > board_width || s.Start().y + s.Length() > board_height) { return false; }
	//check ship doesn't intersect any already placed ships
	for (auto placed_ship : ships) {
		if (s.Intersects(placed_ship)) { return false; }
	}
	ships.emplace_back(s);
	return true;
}
//try to launch a shot at a board point (returns true if successful or false if not)
bool Board::TryHit(const Coordinate point) {
	//check if point is within the board
	if (point.x < 1 || point.x > board_width || point.y < 1 || point.y > board_height) {
		std::cout << "Point is off the board! Try again..." << std::endl;
		return false;
	}
	//try hitting each ship on the board
	for (auto s{ ships.begin() }; s != ships.end(); s++) {
		if (s->Hit(point)) {
			std::cout << "HIT!" << std::endl;
			if (s->Sunk()) {
				std::cout << s->Name() << " was sunk!" << std::endl;
				//remove sunk ship from ships vector
				ships.erase(s);
			}
			return true;
		}
	}
	std::cout << "MISS!" << std::endl;
	return true;
}
//are all the ships on the board sunk?
bool Board::AllSunk()const {
	return (ships.size() == 0);
}
//list the names of ships on the board
void Board::ListShips()const {
	for (auto s : ships) {
		std::cout << "   " << s.Name() << std::endl;
	}
}
//clear the board of ships
void Board::Clear() {
	ships.clear();
}