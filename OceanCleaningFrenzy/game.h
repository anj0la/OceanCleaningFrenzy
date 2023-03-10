/*
 * Name: Anjolaoluwa Aina
 * Student ID: 3586267
 * Last Modified: Monday, February 20th, 2023
 * File: game.h
 *
 * Information:
 *
 * This file defines the Game class, which is used to control the execution of the game.
 * The interrupt handler is in this file, and is a static method rather than a class method.
 * 
 * New Additions:
 * 
 * The pthreads library is used to create two different threads: one for updating the screen and the other to run the fish logic in the game.
 * Mutexes are not need because the threads are not sharing any data with each other (the methods have to be static as I am using a C++ class to 
 * control execution of the game).
 *
 */
#ifndef game_h
#define game_h

#define HAVE_STRUCT_TIMESPEC
#include "sprite.h"
#include "player.h"
#include "fish.h"
#include "trash_pool.h"
#include <pthread.h>
#include "datafile.h"

// Screen Constants
#define WIDTH 800
#define HEIGHT 600
#define BANNER_HEIGHT 50

// Colours
#define BLACK makecol(0, 0, 0)
#define WHITE makecol(255, 255, 255)
#define BROWN makecol(122, 49, 69)
#define ROYAL_BLUE makecol(65, 105, 225)
#define CERULEAN_BLUE makecol(42, 82, 190)
#define DARKER_BLUE makecol(9, 115, 186)

// Game Constants
#define FPS 60
#define SPAWN_RATE 6 * FPS
#define INIT_SCORE 0
#define MAX_SCORE_LEN 12 // max int digits = 10 + 1 to account for the '\0' (null) character and + 1 for the '-' character
#define MAX_TIME_LEN 3
#define VOLUME 32
#define PANNING 32
#define FREQUENCY 1000

// Struct for Parameter Passing
struct spawn_fish_params {
	Fish* fish;
	int time_since_last_spawn;
	Player* player;
};

class Game {
private:
	static volatile int speed_counter;
	DATAFILE* game_datafile;
	volatile int timer; 
	volatile int time_since_last_spawn;
	const char* diver_image_filenames[NUM_DIVER_SPRITES] = {"graphics\\diver_sprite_left_swim_1.bmp",
		"graphics\\diver_sprite_left_swim_2.bmp", "graphics\\diver_sprite_right_swim_1.bmp", "graphics\\diver_sprite_right_swim_2.bmp"};
	const char* trash_image_filenames[NUM_TRASH_SPRITES] = {"graphics\\dirty_trash_can.bmp", 
		"graphics\\banana_peel.bmp", "graphics\\eaten_apple.bmp", "graphics\\plastic_bottle.bmp", "graphics\\pencil.bmp"};
	BITMAP* buffer;
	Player* player;
	Fish* fish;
	Trash_Pool* trash_pool;
	BITMAP* start_background;
	BITMAP* game_background;
	BITMAP* end_background;
	BITMAP* game_banner;
	BITMAP* help_module;
	FONT* large_font;
	FONT* normal_font;
	FONT* small_font;
	FONT* score_font;
	SAMPLE* background_music;
	SAMPLE* caught_fish;
	SAMPLE* caught_trash;
	char total_score[MAX_SCORE_LEN];
	char time_left[MAX_TIME_LEN];
	bool paused;
	bool background_music_muted;
public:
	Game();
	~Game();
	static pthread_t create_pthread_for_updating_screen(BITMAP* buffer);
	static pthread_t create_pthread_for_spawning_fish(Fish* fish, int time_since_last_spawn, Player* player);
	static void join_pthread(pthread_t threadId, void** return_val);
	bool load_game_datafile();
	bool load_game_backgrounds();
	bool load_fonts();
	bool load_sounds();
	bool set_up_sprites();
	bool initialize_game();
	void start_game();
	void new_game();
	void reset_game();
	bool run_game();
	bool main_menu();
	void run_game_logic();
	void handle_trash_sprite_collision();
	void handle_fish_sprite_collision();
	bool play_game();
	void draw_game_objects();
	bool end_game_menu();
	void display_help_module();
	void toggle_background_music();
	void exit_out_of_help_module();
	static void increment_speed_counter();
	static void* update(void* buffer);
	static void* run_fish_logic(void* thread_param);
};

#endif