#include "ao_io.h"
#include "ao_save.h"
#include "ao_physics.h"

#include <unistd.h>
#include <chrono>
#include <thread>
#include <curses.h>
#include <math.h>

const int refreshDelay = 100;
const int maxPlanets = 100;
const int maxShips = 100;
const int planetSpacing = 20;

// Load planets
void genPlanets(planet * array){

	array[0] = planet(5, 10, 0);

}

// Load ships
void genShips(ship * array){

	array[0] = ship(0, 0);

}

int main(){

	charBuffer buf;
	int menu = 0;
	int selectedItem = 0;
	int ch;

	gameLoader saveData;
	int numSaves = saveData.getNumSaves();
	if (numSaves == 0){selectedItem = 1;}

	planet planetArray[maxPlanets];
	ship shipArray[maxShips];

	physicsHandler sim(maxShips, maxPlanets);
	traj mainTraj;

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

			// Render the buffer to the terminal
			buf.draw();

			sim.runStep(planetArray, shipArray, &mainTraj);

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
