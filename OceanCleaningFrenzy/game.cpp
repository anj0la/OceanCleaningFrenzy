/*
 * Name: Anjolaoluwa Aina
 * Student ID: 3586267
 * Last Modified: Wednesday, February 22nd, 2023
 * File: game.cpp
 *
 * Information:
 *
 * This file contains the Game class, which is used to control the execution of the game.
 * The interrupt handler is in this file, and is a static method rather than a class method.
 * 
 * Documentation has been provided to all the following methods below to understand how 
 * each of them work.
 * 
 * Known Bugs:
 * 
 * 1. After pressing Ctrl + h or Ctrl + h to invoke the help module or toggle the background music, then you press the ESC key to quit 
 * the game, the game does not quit unless you click on another key, like the SHIFT or Up key.
 * 
 * I tried looking online on ways to fix the bug, but it seems to be an Allegro problem, since the ENTER key works perfectly fine
 * after pressing Ctrl + h / Ctrl + m. The source is here: https://www.allegro.cc/forums/thread/603468
 * 
 * Another trick to fix the bug is to close the application and open it up again, and pressing the ESC key then works as it should.
 * This is not something that really impacts the game, as the game works regardless of the bug. 
 * 
 * New Additions:
 * 
 * The pthreads library is used to create two different threads: one for updating the screen and the other to run the fish logic in the game.
 * Mutexes are not need because the threads are not sharing any data with each other (the methods have to be static as I am using a C++ class to 
 * control execution of the game).
 * 
 * Allegro datafiles were also used to store and load game objects - specifically, the bitmap images, the sounds, and fonts associated with the game.
 *
 * The game also makes use of the AI technique called tracking to add intelligence to the fish.
 */
#include "game.h"
#include <stdio.h> 
#include <stdlib.h>
#include <time.h>

volatile int Game::speed_counter = 0;

/*
Constructs a new instance of the game class, and initializes all variables.
*/
Game::Game() {
	timer = 61 * FPS;
	time_since_last_spawn = SPAWN_RATE;
	buffer = create_bitmap(WIDTH, HEIGHT);
	game_datafile = NULL;
	player = new Player();
	fish = new Fish();
	trash_pool = new Trash_Pool();
	start_background = NULL;
	game_background = NULL;
	end_background = NULL;
	game_banner = NULL;
	help_module = NULL;
	large_font = NULL;
	normal_font = NULL;
	small_font = NULL;
	score_font = NULL;
	background_music = NULL;
	caught_fish = NULL;
	caught_trash = NULL;
	background_music_muted = false;
	sprintf_s(total_score, MAX_SCORE_LEN, "%d", INIT_SCORE);
	sprintf_s(time_left, MAX_TIME_LEN, "%d", timer / FPS);
	paused = false;
	LOCK_VARIABLE(speed_counter);
	LOCK_FUNCTION(increment_speed_counter);
} // constructor

/*
Destroys the bitmaps, fonts, and samples associated with the game. 
*/
Game::~Game() {
	destroy_bitmap(buffer);
	unload_datafile(game_datafile);
	destroy_bitmap(game_background);
	destroy_bitmap(game_banner);
	destroy_bitmap(help_module);
	destroy_font(large_font);
	destroy_font(normal_font);
	destroy_font(small_font);
	destroy_font(score_font);
	destroy_sample(background_music);
	destroy_sample(caught_fish);
	destroy_sample(caught_trash);
} // destructor

/*
Loads the Allegro datafile containing all the game resources into the game.
@return - true if the datafile loaded successfully, false otherwise
*/
bool Game::load_game_datafile() {
	game_datafile = load_datafile("game_data.dat");
	if (game_datafile != NULL) {
		return true;
	}
	return false; // error loading the datafile
} // load_game_datafile

/*
Loads all BMP files into the backgrounds used in the game.
@return - true if all files was loaded successfully into their respective backgrounds, false otherwise
*/
bool Game::load_game_backgrounds() {
	game_background = (BITMAP*)game_datafile[GAME_BACKGROUND_BMP].dat;
	game_banner = (BITMAP*)game_datafile[GAME_BANNER_BMP].dat;
	start_background = (BITMAP*)game_datafile[START_BACKGROUND_BMP].dat;
	end_background = (BITMAP*)game_datafile[END_BACKGROUND_BMP].dat;
	help_module = (BITMAP*)game_datafile[HELP_MODULE_BMP].dat;
	if (game_background != NULL && game_banner != NULL && start_background != NULL && end_background != NULL && help_module != NULL) {
		return true;
	}
	return false; // background is NULL
} // load_game_background

/*
Loads all BMP files into the fonts used in the game.
@return - true if all files was loaded successfully into their respective fonts, false otherwise
*/
bool Game::load_fonts() {
	large_font = (FONT*)game_datafile[FONT_HEADER_PCX].dat;
	normal_font = (FONT*)game_datafile[FONT_SUBHEADER_PCX].dat;
	small_font = (FONT*)game_datafile[FONT_BODY_PCX].dat;
	score_font = (FONT*)game_datafile[SCORE_TIMER_FONT_PCX].dat;
	if (large_font != NULL && normal_font != NULL && small_font != NULL && score_font != NULL) {
		return true;
	}
	return false; // fonts are null
} // load_fonts

/*
Loads all BMP files into the sounds used in the game.
@return - true if all files was loaded successfully into their respective sounds, false otherwise
*/
bool Game::load_sounds() {
	background_music = (SAMPLE*)game_datafile[TROPICAL_SUMMER_MUSIC_WAV].dat;
	caught_fish = (SAMPLE*)game_datafile[NEGATIVE_BEEPS_WAV].dat;
	caught_trash = (SAMPLE*)game_datafile[TINY_SPLASH_WAV].dat;
	if (background_music != NULL && caught_fish != NULL && caught_trash != NULL) {
		return true;
	}
	return false; // sounds are null
} // load_sounds
/*
Sets up the sprites for the game.
@return - true if the sprite files were all successfully loaded, false otherwise
*/
bool Game::set_up_sprites() {
	player->set_specific_player_sprite_image(0, (BITMAP*)game_datafile[DIVER_SPRITE_LEFT_SWIM_1_BMP].dat);
	player->set_specific_player_sprite_image(1, (BITMAP*)game_datafile[DIVER_SPRITE_LEFT_SWIM_2_BMP].dat);
	player->set_specific_player_sprite_image(2, (BITMAP*)game_datafile[DIVER_SPRITE_RIGHT_SWIM_1_BMP].dat);
	player->set_specific_player_sprite_image(3, (BITMAP*)game_datafile[DIVER_SPRITE_RIGHT_SWIM_1_BMP].dat);
	fish->get_fish_sprite()->set_image((BITMAP*)game_datafile[TUNA_FISH_BMP].dat);
	trash_pool->set_sprite(0, (BITMAP*)game_datafile[BANANA_PEEL_BMP].dat);
	trash_pool->set_sprite(1, (BITMAP*)game_datafile[EATEN_APPLE_BMP].dat);
	trash_pool->set_sprite(2, (BITMAP*)game_datafile[PENCIL_BMP].dat);
	trash_pool->set_sprite(3, (BITMAP*)game_datafile[DIRTY_TRASH_CAN_BMP].dat);
	trash_pool->set_sprite(4, (BITMAP*)game_datafile[PLASTIC_BOTTLE_BMP].dat);
	bool loaded_player_sprite = player->did_sprite_images_load();
	bool loaded_fish_sprite = fish->get_fish_sprite()->get_image();
	bool loaded_trash_sprites = trash_pool->did_sprite_images_load();
	if (loaded_player_sprite && loaded_fish_sprite && loaded_trash_sprites) {
		return true;
	}
	return false;
} // set_up_sprites

/*
Initializes the game by loading all the game objects.
@return - true if every game object was loaded successfully, false otherwise
*/
bool Game::initialize_game() {
	bool loaded_bitmap_datafile = load_game_datafile();
	bool loaded_backgrounds = load_game_backgrounds();
	bool loaded_sprites = set_up_sprites();
	bool loaded_fonts = load_fonts();
	bool loaded_sounds = load_sounds();
	if (!loaded_bitmap_datafile || !loaded_backgrounds || !loaded_sprites || !loaded_fonts || !loaded_sounds) {
		return false;
	}
	return true;

} // initialize_game

/*
Starts the game by ensuring that all game objects have been loaded, and calls the new_game function to 
create a new game. If at least one game object has not loaded successfully, an error message is printed
in which afterwards, the game closes.
*/
void Game::start_game() {
	bool initialized_game = initialize_game();
	if (!initialized_game) {
		allegro_message("Error loading game objects.");
		return;
	}
	play_sample(background_music, VOLUME, PANNING, FREQUENCY, TRUE);
	new_game();
} // start_game

/*
Creates a new game by setting all game values to their default state and runs the game.
This function calls itself recursively every time the player wants to replay the game.
*/
void Game::new_game() {
	bool play_again = run_game();
	if (play_again) {
		reset_game();
		new_game();
	}
} // new_game

/*
Resets the game, by setting all game objects back to their initial states.
*/
void Game::reset_game() {
	speed_counter = 0;
	timer = 61 * FPS;
	time_since_last_spawn = 0;
	player->reset_player();
	fish->reset_fish();
	trash_pool->reset_trash_pool();
	sprintf_s(total_score, MAX_SCORE_LEN, "%d", INIT_SCORE);
	sprintf_s(time_left, MAX_TIME_LEN, "%d", timer / FPS);
	paused = false;
} // reset_game

/*
Runs the whole game, from the main menu to the end game menu.
@return - true if the player wants to play the game again, false otherwise
*/
bool Game::run_game() {
	toggle_background_music();
	bool advance = main_menu();
	if (!advance) {
		return false; // game is over
	}
	int installed_interrupt = install_int_ex(increment_speed_counter, BPS_TO_TIMER(FPS));
	if (installed_interrupt != 0) {
		allegro_message("Error setting up the interrupt handler.");
		return false; // an error has occured, so do not restart the game again
	}
	bool game_ended = play_game(); 
	if (game_ended) {
		return false; // game is over
	}
	bool pressed_esc = end_game_menu();
	if (pressed_esc) {
		return false; // game is over
	}
	return true; // the player wants to play the game again
} // run_game

/*
Displays the main menu of the game.
@param background - the static background
@return - true if the enter key was pressed was pressed, false if the escape key was pressed
*/
bool Game::main_menu() {
	clear_bitmap(buffer);
	blit(start_background, buffer, 0, 0, 0, 0, WIDTH, HEIGHT);
	pthread_t new_thread = create_pthread_for_updating_screen(buffer);
	join_pthread(new_thread, NULL);
	while (true) {
		if (key[KEY_ESC]) {
			return false;
		}
		if (key[KEY_ENTER]) {
			key[KEY_ENTER] = 0; // so that the user can press the key again
			return true; // the enter key was pressed
		}
		if (key[KEY_M]) {
			if (key_shifts & KB_CTRL_FLAG) {
				if (background_music_muted) {
					background_music_muted = false;
				}
				else {
					background_music_muted = true; // background_music_muted was false before
				}
				key[KEY_LCONTROL] = 0;
				key[KEY_M] = 0;
				key[KEY_RCONTROL] = 0;
				toggle_background_music();
			}
		} // outer if (toggling the background music)
		// clear_keybuf();
	} // while
} // main_menu

/*
Runs the following methods associated with the game logic, such as moving the player, fish, and trash sprites,
getting input from the user, and ensuring that all sprites are not out of bounds.
*/
void Game::run_game_logic() {
	player->handle_player_out_of_bounds();
	if (time_since_last_spawn == SPAWN_RATE - 2) { // the trash spawns every three seconds
		trash_pool->spawn_sprite();
	}
	void* time_left;
	pthread_t fish_thread = create_pthread_for_spawning_fish(fish, time_since_last_spawn, player);
	join_pthread(fish_thread, &time_left);
	time_since_last_spawn = (int) time_left;
	trash_pool->move_alive_sprites();
} // run_game_logic

/*
Handles the collision that occurs between a player and the fish sprite.
*/
void Game::handle_fish_sprite_collision() {
	if (player->collied_with_game_obj(fish->get_fish_sprite())) {
		play_sample(caught_fish, VOLUME, PANNING, FREQUENCY, FALSE);
		int old_score = player->get_score();
		player->set_score(old_score - 50);
		fish->get_fish_sprite()->set_y_pos(-100);
		fish->get_fish_sprite()->set_alive(false);
	}
} // handle_fish_sprite_collision

/*
Handles the collision that occurs between a player and a sprite in the trash pool that is alive.
*/
void Game::handle_trash_sprite_collision() {
	for (int i = 0; i < NUM_TRASH_SPRITES; i++) {
		Sprite* curr_trash_spr = trash_pool->get_sprite(i);
		if (curr_trash_spr->is_alive()) {
			if (player->collied_with_game_obj(curr_trash_spr)) {
				play_sample(caught_trash, VOLUME * 3, PANNING, FREQUENCY, FALSE);
				int old_score = player->get_score();
				player->set_score(old_score + 100);
				trash_pool->reset_position_alive_sprite(curr_trash_spr);
			} // inner if
		} // outer if
	} // for
} // handle_trash_sprite_collision

/*
Runs the actual game.
@return - true if the game was over by pressing the ESC key, false otherwise
*/
bool Game::play_game() {
	bool game_over = false;
	bool pressed_esc = false;
	while (!game_over) {
		while (speed_counter > 0) {
			speed_counter--;
			if (!paused) {
				run_game_logic();
				handle_fish_sprite_collision();
				handle_trash_sprite_collision();
				player->get_player_input();
				timer--;
				time_since_last_spawn--;	
			}
		} // inner while

		// If we are in the help module, we exit if the player presses Enter 
		exit_out_of_help_module();

		// If the timer has reached 0, the user has also finished the game
		if (timer <= 0) {
			game_over = true;
		}

		// If the user pressed Ctrl + H, then game is paused and the help module is displayed
		if (key[KEY_H]) {
			if (key_shifts & KB_CTRL_FLAG) {
				display_help_module();
				paused = true;
				key[KEY_LCONTROL] = 0;
				key[KEY_H] = 0;
				key[KEY_RCONTROL] = 0;
			}	
		}

		// Handling the toggling in the play game function
		if (key[KEY_M]) {
			if (key_shifts & KB_CTRL_FLAG) {
				if (background_music_muted) {
					background_music_muted = false;
				}
				else {
					background_music_muted = true; // background_music_muted was false before
				}
				key[KEY_LCONTROL] = 0;
				key[KEY_M] = 0;
				key[KEY_RCONTROL] = 0;
				toggle_background_music();
			}
		} // outer if (toggling the background music)

		// Game is over if the user has pressed the ESC key
		if (key[KEY_ESC]) {
			game_over = true;
			pressed_esc = true;
		}

		// Doesn't update if the game is paused
		if (!paused) {
			// Updating time_left string
			sprintf_s(time_left, MAX_TIME_LEN, "%d", timer / FPS);
			sprintf_s(total_score, MAX_SCORE_LEN, "Score: %d", player->get_score());
			draw_game_objects();
		} 

	} // game loop
	remove_int(increment_speed_counter); // removing the interrupt handler as we don't need it anymore
	return pressed_esc;
} // play_game

/*
Draws all the game objects to the buffer, and updates the screen at the end.
*/
void Game::draw_game_objects() {
	// Updating buffer 
	clear_bitmap(buffer);
	blit(game_background, buffer, 0, 0, 0, 0, WIDTH, HEIGHT);

	// Drawing player to buffer
	player->get_player_sprite()->draw(buffer);

	// Drawing fish to buffer
	if (fish->get_fish_sprite()->is_alive()) {
		fish->get_fish_sprite()->draw(buffer);
	}

	// Drawing trash objects to buffer
	for (int i = 0; i < NUM_TRASH_SPRITES; i++) {
		Sprite* curr_spr = trash_pool->get_sprite(i);
		if (curr_spr->is_alive()) {
			curr_spr->draw(buffer);
		}
	}

	// Drawing time left and score to buffer
	textout_centre_ex(buffer, small_font, "TIME", WIDTH / 2, HEIGHT - 50, CERULEAN_BLUE, -1);
	textout_centre_ex(buffer, large_font, time_left, WIDTH / 2, HEIGHT - 35, CERULEAN_BLUE, -1);
	textout_ex(buffer, normal_font, total_score, 10, HEIGHT - 30, ROYAL_BLUE, -1);

	// Drawing game banner to buffer
	blit(game_banner, buffer, 0, 0, 0, 0, WIDTH, BANNER_HEIGHT);

	// Updating screen
	pthread_t new_thread = create_pthread_for_updating_screen(buffer);
	join_pthread(new_thread, NULL);
} // draw_game_objects

/*
Displays the end game menu.
@param background - the static background
@return - true if the escape key was pressed, false if the enter key was pressed
*/
bool Game::end_game_menu() {
	clear_bitmap(buffer);
	blit(end_background, buffer, 0, 0, 0, 0, WIDTH, HEIGHT);
	textout_centre_ex(buffer, score_font, "Total", WIDTH / 2 - 95, 310, ROYAL_BLUE, -1);
	textout_centre_ex(buffer, score_font, total_score, WIDTH / 2 + 65, 310, ROYAL_BLUE, -1);
	pthread_t new_thread = create_pthread_for_updating_screen(buffer);
	join_pthread(new_thread, NULL);
	while (true) {
		if (key[KEY_ESC]) {
			return true;
		}
		if (key[KEY_ENTER]) {
			key[KEY_ENTER] = 0; // so that the user can press the key again
			break;
		}
		if (key[KEY_M]) {
			if (key_shifts & KB_CTRL_FLAG) {
				if (background_music_muted) {
					background_music_muted = false;
				}
				else {
					background_music_muted = true; // background_music_muted was false before
				}
				key[KEY_LCONTROL] = 0;
				key[KEY_M] = 0;
				key[KEY_RCONTROL] = 0;
				toggle_background_music();
			}
		} // outer if (toggling the background music)	
	}
	return false; // the enter key was pressed
} // end_game_menu

/*
Displays the help module.
*/
void Game::display_help_module() {
	clear_bitmap(buffer);
	blit(help_module, buffer, 0, 0, 0, 0, WIDTH, HEIGHT);
	pthread_t new_thread = create_pthread_for_updating_screen(buffer);
	join_pthread(new_thread, NULL);
} // display_help_module 

/*
Toggles the background music. If the background music was last muted, music will start to play. Otherwise, the music will stop playing.
*/
void Game::toggle_background_music() {
	if (!background_music_muted) {
			adjust_sample(background_music, VOLUME, PANNING, FREQUENCY, TRUE);
		} else {
			adjust_sample(background_music, 0, 0, FREQUENCY, TRUE);
	}
} // toggle_background_music

/*
Exits the help module.
*/
void Game::exit_out_of_help_module() {
	if (key[KEY_ENTER]) {
		paused = false;
		key[KEY_ENTER] = 0;
	}
	if (key[KEY_ESC]) {
		paused = false; // the ESC key has been pressed, so the in the play game method, KEY_ESC = 1 (true)
	}
} // exit_out_of_help_module

/*
Increases the speed counter, which is used to update / move the objects in the game.
*/
void Game::increment_speed_counter() {
	speed_counter++;
} // increment_speed_counter
END_OF_FUNCTION(increment_speed_counter);

/*
The new thread function that updates the screen. It works the same way the update_screen() function used to work, with the
only difference being is that another thread executes it.
@param game_buffer - the double buffer of the game (represented as a void pointer)
*/
void* Game::update(void* game_buffer) {
	BITMAP* buffer = (BITMAP*) game_buffer;
	acquire_screen();
	blit(buffer, screen, 0, 0, 0, 0, WIDTH, HEIGHT);
	release_screen();
	return NULL;
} // update

/*
The new thread function that runs the fish logic of the game. It replaces the fish functions located in the run_game_logic() function, and executes
every single time the run_game_logic() function is called.
@param args - the struct containing the fish and the time_since_last_spawn variable
@return - the new time_since_last_spawn value
*/
void* Game::run_fish_logic(void* args) {
	int ret_val;
	struct spawn_fish_params* thread_params = (struct spawn_fish_params*) args;
	if (thread_params->time_since_last_spawn == 0) { // the fish spawns every six seconds 
		thread_params->fish->respawn_fish();
		ret_val = SPAWN_RATE;
	}
	else {
		int player_x_pos = thread_params->player->get_player_sprite()->get_x_pos();
		int player_y_pos = thread_params->player->get_player_sprite()->get_y_pos();
		thread_params->fish->move_fish(player_x_pos, player_y_pos);
		thread_params->fish->handle_fish_out_of_bounds();
		ret_val = thread_params->time_since_last_spawn;
	}
	free(thread_params);
	return (void*) ret_val;
} // run_fish_logic

/*
Creates a pthread to be used for updating the screen.
@param buffer - the double buffer used in the game
@return - the thread id of the newly created thread.
*/
pthread_t Game::create_pthread_for_updating_screen(BITMAP* buffer) {
	pthread_t threadId;
	pthread_create(&threadId, NULL, update, (void*) buffer);
	return threadId;
} // create_pthread_for_updating_screen

/*
Creates a pthread to be used for updating the screen.
@param buffer - the double buffer used in the game
@return - the thread id of the newly created thread.
*/
pthread_t Game::create_pthread_for_spawning_fish(Fish* fish, int time_since_last_spawn, Player* player) {
	pthread_t threadId;
	struct spawn_fish_params* fish_params = (struct spawn_fish_params*) malloc(sizeof(struct spawn_fish_params));
	if (fish_params != NULL) {
		fish_params->fish = fish;
		fish_params->time_since_last_spawn = time_since_last_spawn;
		fish_params->player = player;
	}
	pthread_create(&threadId, NULL, run_fish_logic, (void*) fish_params);
	return threadId;
} // create_pthread_for_updating_screen

/*
Terminates a thread when finished running.
@param threadId - the id of the thread to be joined with the main thread
@param return_val - the value of the thread (if none exists, pass NULL)
*/
void Game::join_pthread(pthread_t threadId, void** return_val) {
	pthread_join(threadId, return_val);
} // join_pthread
