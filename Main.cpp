//Main.cpp by  Sam Brind (main program functions)
#include "Classes.h"

//function to safely get a user input integer
int getInt() {
	while (true) {
		std::string input;
		std::getline(std::cin, input);
		std::stringstream stream(input);
		int number;
		if (stream >> number) { return number; }
	}
}

//function to safely get a user input char that is either c1 or c2
char getChar(const char c1, const char c2) {
	while (true) {
		std::string input;
		std::getline(std::cin, input);
		if (input.length() == 1) {
			if (input[0] == c1 || input[0] == c2) { return input[0]; }
		}
	}
}

//main program
int main() {
	Board gameboard;
	bool play_again{ true };
	const int num_ships{ 3 };
	//ship names for sizes 2-5 (but note that submarine and cruiser are both size 3)
	const std::string ship_classes[5] {"Destroyer","Submarine","Cruiser","Battleship","Carrier"};
	//seed rand()
	srand(time(NULL));
	//game loop
	while (play_again) {
		int num_shots{ num_ships * 6 };
		gameboard.Clear();
		for (int i{ 0 }; i < num_ships; i++) {
			//generate a random ship
			Ship random_ship;
			//and loop while it can't be inserted onto the board
			do {
				//generate orientation (true/false)
				bool orientation{ (bool)(rand() % 2) };
				//generate a length (0 - 4)
				int length{ (rand() % 4) };
				std::string name {ship_classes[length]};
				//convert length to ship size
				length += 2;
				if (length > 3) { length--; }
				//generate a starting point (1-width,1-height)
				int x{ (rand() % gameboard.board_width) + 1 };
				int y{ (rand() % gameboard.board_height) + 1 };
				random_ship = Ship(orientation, length, Coordinate(x, y),name);
			} while (!gameboard.InsertShip(random_ship));
		}
		//display game situation
		std::cout << "You have " << num_shots << " missiles to destroy the enemy fleet:" << std::endl;
		gameboard.ListShips();
		//loop over player inputting coordinates
		while (num_shots > 0) {
			int x,y;
			std::cout << "What are your launch coordinates (x,y)?" << std::endl;
			//loop until user inputs a valid board coordinate
			do {
				std::cout << "x:";
				x = getInt();
				std::cout << "y:";
				y = getInt();
			} while (!gameboard.TryHit(Coordinate(x, y)));
			//check if game has been won
			if (gameboard.AllSunk()) {
				std::cout << "Enemy fleet is destroyed, you win!" << std::endl;
				num_shots = 1;
				break;
			}
			num_shots--;
			std::cout << "You have " << num_shots << " missiles left" << std::endl;
		}
		//lost the game
		if (num_shots == 0) {
			std::cout << "You failed to sink all the enemy ships, you lose!" << std::endl;
		}
		//check whether to play again
		std::cout << "Do you want to play again (y/n) ? ";
		char temp{ getChar('y', 'n') };
		if (temp == 'n') { play_again = false; }
	}
	return 0;
}