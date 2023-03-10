/*
 * Name: Anjolaoluwa Aina
 * Student ID: 3586267
 * Last Modified: Wednesday, February 22nd, 2023
 * File: fish.cpp
 *
 * Information:
 *
 * This file contains the Fish class, which is used to control the functionality of the
 * fish.
 * 
 */
#include "fish.h"

/*
Constructs a new instance of the fish class.
*/
Fish::Fish() {
	fish_spr = new Sprite();
	fish_spr->set_speed(FISH_SPEED);
	fish_spr->set_x_pos(get_random_fish_x_pos());
	fish_spr->set_y_pos(-100);
} // constructor

/*
Automatically removes the fish object from memory.
*/
Fish::~Fish() {
	// Empty destructor, sprite classes handles the deleting of the bitmap associated with the fish
} // destructor

/*
Gets the fish sprite.
@return - the pointer pointing to the fish sprite
*/
Sprite* Fish::get_fish_sprite() {
	return fish_spr;
} // get_fish_sprite

/*
Moves the fish by the speed specified in the initial construction of the fish class.
The fish has more intelligence as it moves towards the player, depending on the player's
x and y positions.
@param player_x_pos - the x position of the player
@param player_y_pos - the y position of the player
*/
void Fish::move_fish(int player_x_pos, int player_y_pos) {
	if (fish_spr->is_alive()) {
		int old_x_pos = fish_spr->get_x_pos();
		int old_y_pos = fish_spr->get_y_pos();
		int speed = fish_spr->get_speed();
		
		// State 1 - player is moving left, so fish needs to move left
		if (fish_spr->get_x_pos() < player_x_pos) {
			fish_spr->set_x_pos(old_x_pos + speed);
		} 

		// State 2 - player is moving right, so fish needs to move right
		if (fish_spr->get_x_pos() >= player_x_pos) {
			fish_spr->set_x_pos(old_x_pos - speed);
		}

		fish_spr->set_y_pos(old_y_pos + speed);
	}
} // move_fish

/*
Respawns the fish if it is not alive.
*/
void Fish::respawn_fish() {
	if (!fish_spr->is_alive()) {
		fish_spr->set_y_pos(-100);
		fish_spr->set_x_pos(get_random_fish_x_pos());
		fish_spr->set_alive(true);
	}
} // respawn_fish

/*
Checks if a fish is out of bounds, that is, its y position is greater than height of the game.
*/
void Fish::handle_fish_out_of_bounds() {
	if (!fish_spr->is_alive()) {
		return; // not alive, exit the method
	}
	if (fish_spr->get_y_pos() >= 600) { // down
		fish_spr->set_y_pos(-100);
		fish_spr->set_x_pos(get_random_fish_x_pos());
		fish_spr->set_alive(false);
	}
} // handle_fish_out_of_bounds

/*
Gets a random position for the fish to spawn, between 100 and 700 pixels.
@return - random x position of the fish
*/
int Fish::get_random_fish_x_pos() {
	return rand() % 550 + 150;
} // get_random_fish_x_pos

/*
Resets the fish back to its default values.
*/
void Fish::reset_fish() {
	fish_spr->set_x_pos(get_random_fish_x_pos());
	fish_spr->set_y_pos(-100);
	fish_spr->set_alive(true);
} // reset_fish


