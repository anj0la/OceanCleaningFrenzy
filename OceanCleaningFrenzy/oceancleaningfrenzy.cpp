/*
 * Name: Anjolaoluwa Aina
 * Student ID: 3586267
 * Last Modified: Saturday, December 31, 2022
 * File: oceancleaningfrenzy.cpp
 *
 * Information:
 * 
 * This file is the entry point of the application. It initializes Allegro, sets the window title, the
 * GFX mode, the sound, creates a new game object, and calls start_game() to start the execution of the game.
 * 
 * Once the palyer has stopped playing the game, the destructor in the Game class handles the deleting of all
 * the bitmaps, fonts, and samples associated with the game. 
 *
 */

#include "oceancleaningfrenzy.h"
/*
The entry point of the game.
*/
int main(void) {
	srand(time(NULL));
	if (allegro_init() != 0) {
		return 1;
	}
	set_window_title("Ocean Cleaning Frenzy");
	set_color_depth(24);
	install_keyboard();
	set_keyboard_rate(10000, 0);
	int ret = set_gfx_mode(GFX_SAFE, 800, 600, 0, 0);
	if (ret != 0) {
		allegro_message("Error setting GFX mode.");
		return 1;
	}
	if (install_sound(DIGI_AUTODETECT, MIDI_NONE, "") != 0) {
		allegro_message("Error initializing sound system.");
		return 1;
	}

	Game* game = new Game();
	//pthread_t tid;
	//spawn_fish_params* fish_params;
	game->start_game();
	//fish_params->fish = game->get_fish();

	//game->new_game();
	allegro_exit();
	return 0;
}
END_OF_MAIN()

//void* draw_fish(spawn_fish_params* params) {
//	if (time_since_last_spawn == 0) { // the fish spawns every six seconds 
//		fish->respawn_fish();
//		time_since_last_spawn = SPAWN_RATE;
//	}
//}
