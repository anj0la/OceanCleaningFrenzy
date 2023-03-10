/*
 * Name: Anjolaoluwa Aina
 * Student ID: 3586267
 * Last Modified: Wednesday, February 22nd, 2022
 * File: player.cpp
 *
 * Information:
 * 
 * This file implements the class defined in the player.h header, initializes the class variables,
 * creates the constructor/destructor and finally, the methods associated with the class.
 * It is used to keep track of the score that the player has currently, along with the current frame
 * of the diver sprite.
 *
 */

#include "player.h"

/*
Constructs a new instance of the player class.
*/
Player::Player() {
	for (int i = 0; i < NUM_DIVER_SPRITES; i++) {
		diver_sprite_imgs[i] = new Sprite();
		diver_sprite_imgs[i]->set_speed(PLAYER_SPEED);
	}
	score = 0;
	diver_sprite_counter = 0;
	player_spr_direction = LEFT;
	diver_sprite_imgs[diver_sprite_counter]->set_x_pos(375);
	diver_sprite_imgs[diver_sprite_counter]->set_y_pos(400);
	diver_sprite_imgs[diver_sprite_counter]->set_alive(true);
} // constructor 

/*
Deletes the diver_sprite_imgs array from memory.
*/
Player::~Player() {
	delete[] *diver_sprite_imgs;
} // destructor

/*
Checks if all diver sprite images have a BITMAP loaded into them. 
@return - false if at least one did not load successfully, true otherwise
*/
bool Player::did_sprite_images_load() {
	for (int i = 0; i < NUM_DIVER_SPRITES; i++) {
		if (diver_sprite_imgs[i]->get_image() == NULL) {
			return false;
		}
	} // for
	return true;
} // did_sprite_images_load

/*
Gets the player sprite.
@return - the player's sprite
*/
Sprite* Player::get_player_sprite() {
	return diver_sprite_imgs[diver_sprite_counter];
} // get_player_sprite

/*
Changes the image at the specified diver sprite's index.
@param frame - the index of the current diver sprite
@param frame_img - the image to set the current diver sprite image to
*/
void Player::set_specific_player_sprite_image(int frame, BITMAP* frame_img) {
	diver_sprite_imgs[frame]->set_image(frame_img);
} // set_specific_player_sprite_image

/*
Gets the player's score.
@return - the current score of the player
*/
int Player::get_score() {
	return score;
} // get_score

/*
Sets the score of the player to the new score specified by the parameter.
@param - the new score of the player
*/
void Player::set_score(int new_score) {
	score = new_score;
} // set_score

/*
Gets keyboard input from the player, and executes an action based on the key that the user has pressed.
*/
void Player::get_player_input() {
	if (key[KEY_LEFT]) {
		move_left();
	} 
	if (key[KEY_RIGHT]) {
		move_right();
	} 
} // get_player_input

/*
Moves the player's sprite left by subtracting the speed of the player's sprite from its current x position, and updating the frame of the diver
sprite so it is facing left.
*/
void Player::move_left() {
	player_spr_direction = LEFT;
	change_diver_sprite_frame();
	diver_sprite_imgs[diver_sprite_counter]->set_x_pos(diver_sprite_imgs[diver_sprite_counter]->get_x_pos() - diver_sprite_imgs[diver_sprite_counter]->get_speed());
} // move_left

/*
Moves the player's sprite right by subtracting the speed of the player's sprite from its current y position, and updating the frame of the diver
sprite so it is facing right.
*/
void Player::move_right() {
	player_spr_direction = RIGHT;
	change_diver_sprite_frame();
	diver_sprite_imgs[diver_sprite_counter]->set_x_pos(diver_sprite_imgs[diver_sprite_counter]->get_x_pos() + diver_sprite_imgs[diver_sprite_counter]->get_speed());
} // move_right

/*
Checks if the player has collided with a game object.
@param other_spr - a game object's sprite
@return true if the player sprite collided with the game object's sprite, false otherwise
*/
bool Player::collied_with_game_obj(Sprite* other_spr) {
	if (diver_sprite_imgs[diver_sprite_counter]->collided(other_spr)) {
		return true;
	}
	return false;
} // collied_with_game_obj

/*
Handles out of bounds movement if, after the player enters a key, makes the ship greater than the width or height of the game.
*/
void Player::handle_player_out_of_bounds() {
	// checking if position is out of bounds
	if (diver_sprite_imgs[diver_sprite_counter]->get_x_pos() <= 0) { // left
		diver_sprite_imgs[diver_sprite_counter]->set_x_pos(0);
	} 
	if (diver_sprite_imgs[diver_sprite_counter]->get_x_pos() >= 700) { // right
		diver_sprite_imgs[diver_sprite_counter]->set_x_pos(700);
	}
} // handle_player_out_of_bounds

/*
* Resets the plauer back to its default values.
*/
void Player::reset_player() {
	score = 0;
	diver_sprite_imgs[diver_sprite_counter]->set_x_pos(375);
	diver_sprite_imgs[diver_sprite_counter]->set_y_pos(400);
	diver_sprite_imgs[diver_sprite_counter]->set_alive(true);
} // reset_player

/*
Changes the current frame of the diver sprite depending on what direction the player's diver sprite.
*/
void Player::change_diver_sprite_frame() {
	int old_x_position = diver_sprite_imgs[diver_sprite_counter]->get_x_pos();
	int old_y_position = diver_sprite_imgs[diver_sprite_counter]->get_y_pos();
	diver_sprite_imgs[diver_sprite_counter]->set_x_pos(-900);
	diver_sprite_imgs[diver_sprite_counter]->set_y_pos(-900);
	diver_sprite_imgs[diver_sprite_counter]->set_alive(false);

	if (player_spr_direction == LEFT) {
		if (diver_sprite_counter >= 1) {
			diver_sprite_counter = 0;
		}  
		else { // diver_sprite_counter <= 0
			diver_sprite_counter = 1;
		} 
	} // LEFT
	else { // player_spr_direction == RIGHT
		if (diver_sprite_counter == 2) {
			diver_sprite_counter = 3;
		}
		else if (diver_sprite_counter == 3) {
			diver_sprite_counter = 2;
			update_diver_sprite_frame(old_x_position, old_y_position);
		}
		else { // diver_sprite_counter < 2
			diver_sprite_counter = 2;
			update_diver_sprite_frame(old_x_position, old_y_position);
		}
	} // RIGHT
	update_diver_sprite_frame(old_x_position, old_y_position);
} // change_diver_sprite_frame

/*
Updates the diver sprite frame.
@param old_x_pos - the x position of the old diver sprite frame
@param old_y_pos - the y position of the old diver sprite frame
*/
void Player::update_diver_sprite_frame(int old_x_pos, int old_y_pos) {
	diver_sprite_imgs[diver_sprite_counter]->set_x_pos(old_x_pos);
	diver_sprite_imgs[diver_sprite_counter]->set_y_pos(old_y_pos);
	diver_sprite_imgs[diver_sprite_counter]->set_alive(true);
} // update_diver_sprite_frame