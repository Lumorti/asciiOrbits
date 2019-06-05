#include "ao_io.h"
#include <unistd.h>
#include <chrono>
#include <thread>
#include <curses.h>

const int refreshDelay = 200;
const int maxPlanets = 100;
const int planetSpacing = 20;

int main(){

	charBuffer buf;
	int menu = 0;
	int selectedItem = 0;
	int ch;

	planet planetArray[maxPlanets];

	// Main game loop
	while(true){

		if (menu == 0){

			// Get the width and height of the terminal
			buf.updateSize();

			// Reset the buffer
			buf.reset();

			// Draw menu items
			buf.writeStringRel(-5, -2, "Load Game");
			buf.writeStringRel(-5, 0, "New Game");
			buf.writeStringRel(-5, 2, "Settings");
			buf.writeStringRel(-5, 4, "Exit");

			// Get the user's input and process it			
			if ((ch = getch()) != ERR) {
			
				if (ch == KEY_DOWN){

					selectedItem++;
					if (selectedItem > 3){selectedItem = 0;}

				} else if (ch == KEY_UP){

					selectedItem--;
					if (selectedItem < 0){selectedItem = 3;}

				} else if (ch == 10 || ch == KEY_ENTER){

					// If trying to exit
					if (selectedItem == 3){

						buf.close();
						return 0;

					// If starting new game
					} else if (selectedItem == 1){

						menu = 1;
						
						// Load planets
						//for (int i=0; i < maxPlanets; i++){

						//	planetArray[i] = planet(5, i*15, 0);

						//}

						planetArray[0] = planet(5, 10, 0);

						// Load ships

						// Hide cursor
						buf.hideCursor();

					// If loading game 
					} else if (selectedItem == 0){

						menu = 2;

					// If opening settings menu
					} else if (selectedItem == 2){

						menu = 3;

					}

				}

			}

			if (selectedItem == 0){buf.mvCursorRel(-5, -2);}
			else if (selectedItem == 1){buf.mvCursorRel(-5, 0);}
			else if (selectedItem == 2){buf.mvCursorRel(-5, 2);}
			else if (selectedItem == 3){buf.mvCursorRel(-5, 4);}

			// Render the buffer to the terminal
			buf.draw();

			// Wait for a bit
			std::this_thread::sleep_for(std::chrono::milliseconds(refreshDelay));

		} else if (menu == 1){
		
			// Get the width and height of the terminal
			buf.updateSize();

			// Reset the buffer
			buf.reset();

			// Draw planets to buffer
			for (int i=0; i < maxPlanets; i++){

				buf.addPlanet(planetArray[i]);

			}

			// Draw ships to buffer

			// Render the buffer to the terminal
			buf.draw();	

			if ((ch = getch()) != ERR) {

				if (ch == 27){

					menu = 0;
					buf.showCursor();

				}

			}

			// Wait for a bit
			std::this_thread::sleep_for(std::chrono::milliseconds(refreshDelay));

		}

	}

}
