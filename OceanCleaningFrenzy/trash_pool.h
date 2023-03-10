/*
 * Name: Anjolaoluwa Aina
 * Student ID: 3586267
 * Last Modified: Wednesday, February 22nd, 2022
 * File: trash_pool.h
 *
 * Information:
 *
 * This file defines the Trash_Pool class, which is implemented in its respective .cpp file.
 *
 */
#ifndef trash_pool_h
#define trash_pool_h
#include "sprite.h"

// Constants
#define TRASH_SPEED 4
#define NUM_TRASH_SPRITES 5

class Trash_Pool {
private:
	Sprite* trash_sprites[NUM_TRASH_SPRITES];
public:
	Trash_Pool();
	~Trash_Pool();
	bool did_sprite_images_load();
	Sprite* get_sprite(int index);
	void set_sprite(int index, BITMAP* image);
	void spawn_sprite();
	void move_alive_sprites();
	void reset_trash_pool();
	void reset_position_alive_sprite(Sprite* curr_spr);
private:
	int get_random_x_pos();
};

#endif 
