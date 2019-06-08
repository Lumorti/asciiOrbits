#include "ao_io.h"
#include "ao_save.h"
#include "ao_physics.h"
#include "ao_const.h"

#include <unistd.h>
#include <chrono>
#include <thread>
#include <curses.h>
#include <math.h>
#include <string>
#include <random>

using namespace std;

// Load planets
void genPlanets(planet * array){

	random_device rd;
    mt19937 eng(rd());
	uniform_int_distribution<> distr(planetMinCoord, planetMaxCoord);
    uniform_int_distribution<> distr2(planetMinSize, planetMaxSize);

	int x, y, psize;

    for(int n = 0; n < numPlanets; n++){

		x = distr(eng);
		y = distr(eng);
		psize = distr2(eng);
		array[n] = planet(psize, x, y);

		// If too close to the player, delete it
		if (sqrt(pow(x, 2)+pow(y,2)) - psize < minDistance){array[n] = planet();}

	}

}

// Load ships
void genShips(ship * array){

	array[0] = ship(0, 0);

}

int main(){

	// Main drawing handler
	charBuffer buf;

	// Menu vars
	int menu = 0;
	int selectedItem = 0;

	// User input var
	int ch;
	int ch2;

	// Handler for loading/saving data
	gameLoader saveData;
	int numSaves = saveData.getNumSaves();
	if (numSaves == 0){selectedItem = 1;}

	// For keeping track of the planets/ships
	planet planetArray[maxPlanets];
	ship shipArray[maxShips];

	// For handling the physics
	physicsHandler sim(maxShips, maxPlanets);
	traj mainTraj;
	physInfo info;

	// Hide cursor
	buf.hideCursor();

	// Main game loop
	while(true){

		// Main menu
		if (menu == 0){

			// Get the width and height of the terminal
			buf.updateSize();

			// Reset the buffer
			buf.reset();

			// Draw menu items
			buf.writeStringRel(-5, -2, "Load Game");
			buf.writeStringRel(-5, 0,  "New Game");
			buf.writeStringRel(-5, 2,  "Settings");
			buf.writeStringRel(-5, 4,  "Exit");

			// Get the user's input and process it
			if ((ch = getch()) != ERR) {

				// Move the menu item down
				if (ch == KEY_DOWN){

					selectedItem++;
					if (selectedItem > 3 && numSaves > 0){selectedItem = 0;}
					else if (selectedItem > 3){selectedItem = 1;}

				// Move the menu item up
				} else if (ch == KEY_UP){

					selectedItem--;
					if (numSaves > 0 && selectedItem < 0){selectedItem = 3;}
					else if (numSaves <= 0 && selectedItem < 1){selectedItem = 3;}

				// If pressing enter, do the menu item
				} else if (ch == 10 || ch == KEY_ENTER){

					// If trying to exit
					if (selectedItem == 3){

						buf.close();
						return 0;

					// If starting new game
					} else if (selectedItem == 1){

						// Generate planets and ships
						genPlanets(planetArray);
						genShips(shipArray);

						menu = 1;

					// If loading game
					} else if (selectedItem == 0 && numSaves > 0){

						menu = 2;

					// If opening settings menu
					} else if (selectedItem == 2){

						menu = 3;

					}

				}

			}

			// Show which menu item is selected
			buf.writeCharRel(-6, -2 + selectedItem*2, '>');

			// Render the buffer to the terminal
			buf.draw();

			// Wait for a bit
			std::this_thread::sleep_for(std::chrono::milliseconds(refreshDelay));

		// In game
		} else if (menu == 1){

			// Get the width and height of the terminal, reset screen
			buf.updateSize();
			buf.reset();

			// Update thhe player position in buffer memory
			buf.updateCenter(shipArray[0].getX(), shipArray[0].getY());

			// Draw ships and planets to buffer (if within a certain distance)
			for (int i=0; i < maxPlanets; i++){buf.addPlanet(planetArray[i]);}
			for (int i=0; i < maxShips; i++){buf.addShip(shipArray[i]);}

			// Run the simulation for a single step
			sim.runStep(planetArray, shipArray, &mainTraj, &info);

			// Write info to the screen
			buf.writeString(2, 2, "x = "); buf.writeFloatToPrec(7, 2, info.x, 1);
			buf.writeString(2, 3, "y = "); buf.writeFloatToPrec(7, 3, info.y, 1);

			buf.writeString(14, 2, "vx = "); buf.writeFloatToPrec(19, 2, info.vx, 1);
			buf.writeString(14, 3, "vy = "); buf.writeFloatToPrec(19, 3, info.vy, 1);

			buf.writeString(26, 2, "fx = "); buf.writeFloatToPrec(31, 2, info.fx, 1);
			buf.writeString(26, 3, "fy = "); buf.writeFloatToPrec(31, 3, info.fy, 1);

			// Render the buffer to the terminal
			buf.draw();

			// Get key pressed
			if ((ch = getch()) != ERR) {

				// Return to menu on escape
				if (ch == 27){

					menu = 0;

				} else if (ch == KEY_LEFT){

					shipArray[0].changeRot(45);

				} else if (ch == KEY_RIGHT){

					shipArray[0].changeRot(-45);

				} else if (ch == KEY_UP){

					shipArray[0].changeThrust(1);

				} else if (ch == KEY_DOWN){

					shipArray[0].changeThrust(-1);

				}

			}

			// Wait for a bit
			std::this_thread::sleep_for(std::chrono::milliseconds(refreshDelay));

		}

	}

}
