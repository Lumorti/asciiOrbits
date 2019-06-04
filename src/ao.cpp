#include "ao_io.h"
#include <unistd.h>
#include <chrono>
#include <thread>

int main(){

	charBuffer buf;

	int menu = 0;

	// Main game loop
	while(true){

		if (menu == 0){

			buf.reset();
			
			buf.writeStringRel(-5, -2, "Load Game");
			buf.writeStringRel(-5, 0, "New Game");
			buf.writeStringRel(-5, 2, "Exit");
			
			buf.draw();

			std::this_thread::sleep_for(std::chrono::milliseconds(1000));

		} else if (menu == 1){
		
			// Reset the buffer
			buf.reset();

			// Draw planets to buffer

			// Draw ships to buffer

			// Render the buffer to the terminal
			buf.draw();	

			// Wait for a bit
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));

		}

	}

}
