/*
 * Name: Anjolaoluwa Aina
 * Student ID: 3586267
 * Last Modified: Wednesday, February 22nd, 2023
 * File: trash_pool.cpp
 *
 * Information:
 *
 * This file contains the Trash_Pool class, which is used to control the functionality of the 
 * trash sprites in the "pool" (as an array of Sprites).
 * 
 */
#include "trash_pool.h"

/*
Constructs a trash pool instance.
*/
Trash_Pool::Trash_Pool() {
	for (int i = 0; i < NUM_TRASH_SPRITES; i++) {
		trash_sprites[i] = new Sprite();
	}
} // constructor

/*
Deletes the trash_sprites array from memory.
*/
Trash_Pool::~Trash_Pool() {
	delete[] *trash_sprites;
} // destructor

/*
Checks if all diver sprite images have a BITMAP loaded into them.
@return - false if at least one did not load successfully, true otherwise
*/
bool Trash_Pool::did_sprite_images_load() {
	for (int i = 0; i < NUM_TRASH_SPRITES; i++) {
		if (trash_sprites[i]->get_image() == NULL) {
			return false;
		}
	} // for
	return true;
} // did_sprite_images_load

/*
Gets a sprite at the specific index.
@param index - the location of a specific sprite
@return - the sprite at the indicated index
*/
Sprite* Trash_Pool::get_sprite(int index) {
	return trash_sprites[index];
} // get_sprite

/*
Changes the image at the specified trash sprite's index.
@param index - the current trash sprite
@param image - the image to set the current trash sprite to
*/
void Trash_Pool::set_sprite(int index, BITMAP* image) {
	trash_sprites[index]->set_image(image);
} // set_sprite

/*
Spawns a random sprite out of the trash pool, as long as it is not already alive.
*/
void Trash_Pool::spawn_sprite() {
	int rand_index = rand() % NUM_TRASH_SPRITES;
	Sprite* trash_spr = trash_sprites[rand_index];
	if (!trash_spr->is_alive()) {
		trash_spr->set_x_pos(get_random_x_pos());
		trash_spr->set_y_pos(-150);
		trash_spr->set_alive(true);
	} // if
} // spawn_sprite

/*
Move the sprites currently alive in the trash pool.
*/
void Trash_Pool::move_alive_sprites() {
	for (int i = 0; i < NUM_TRASH_SPRITES; i++) {
		Sprite* curr_spr = trash_sprites[i];
		if (curr_spr->is_alive()) {
			int old_x_pos = curr_spr->get_x_pos();
			int old_y_pos = curr_spr->get_y_pos();
			int speed = curr_spr->get_speed();
			if (old_y_pos > 750) {
				curr_spr->set_y_pos(-150);
				curr_spr->set_x_pos(get_random_x_pos());
			} // inner if
			else {
				curr_spr->set_y_pos(old_y_pos + speed);
				curr_spr->set_x_pos(old_x_pos + speed / TRASH_SPEED);
			}  
		} // if
	} // for
} // move_alive_sprites

/*
Resets the trash pool back to its default value.
*/
void Trash_Pool::reset_trash_pool() {
	for (int i = 0; i < NUM_TRASH_SPRITES; i++) {
		trash_sprites[i]->set_y_pos(-100);
		trash_sprites[i]->set_alive(false);
	} // for
} // reset_trash_pool

/*
Resets the alive trash sprite to a different x location.
@param curr_spr - the current sprite in the trash pool (that is alive)
*/
void Trash_Pool::reset_position_alive_sprite(Sprite* curr_spr) {
	curr_spr->set_y_pos(-300);
	curr_spr->set_x_pos(get_random_x_pos());
} // reset_position_alive_sprite

/*
Gets a random position for the trash sprite to spawn, between 100 and 700 pixels.
@return - random x position of the sprite
*/
int Trash_Pool::get_random_x_pos() {
	return rand() % 500 + 100;
} // get_random_x_pos
