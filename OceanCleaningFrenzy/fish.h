/*
 * Name: Anjolaoluwa Aina
 * Student ID: 3586267
 * Last Modified: Wednesday, February 22nd, 2023
 * File: fish.h
 *
 * Information:
 *
 * This file defines the Fish class, which is implemented in its respective .cpp file.
 *
 */
#ifndef fish_h
#define fish_h
#include "sprite.h"

#define FISH_SPEED 2

class Fish {
private:
	Sprite* fish_spr;
public:
	Fish();
	~Fish();
	Sprite* get_fish_sprite();
	void move_fish(int player_x_pos, int player_y_pos);
	void respawn_fish();
	void handle_fish_out_of_bounds();
	void reset_fish();
private:
	int get_random_fish_x_pos();
};

#endif 
