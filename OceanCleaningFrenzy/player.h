/*
 * Name: Anjolaoluwa Aina
 * Student ID: 3586267
 * Last Modified: Wednesday, February 22nd, 2022
 * File: player.h
 *
 * Information:
 * 
 * This file defines the Player class, which is implemented in its respective .cpp file.
 *
 */
#ifndef player_h
#define player_h
#include "sprite.h"

// Constants
#define NUM_DIVER_SPRITES 4
#define PLAYER_SPEED 5
enum Direction { LEFT, RIGHT };

class Player {
private:
	Sprite* diver_sprite_imgs[NUM_DIVER_SPRITES];
	Direction player_spr_direction;
	int diver_sprite_counter;
	int score;
public:
	Player();
	~Player();
	Sprite* get_player_sprite();
	bool did_sprite_images_load();
	void set_specific_player_sprite_image(int frame, BITMAP* frame_img);
	int get_score();
	void set_score(int new_score);
	void get_player_input();
	void move_left();
	void move_right();
	bool collied_with_game_obj(Sprite* other_spr);
	void handle_player_out_of_bounds();
	void reset_player();
	void change_diver_sprite_frame();
	void update_diver_sprite_frame(int old_x_pos, int old_y_pos);
};

#endif 
