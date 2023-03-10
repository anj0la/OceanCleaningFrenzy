/*
 * Name: Anjolaoluwa Aina
 * Student ID: 3586267
 * Last Modified: Saturday, December 31st, 2022
 * File: sprite.h
 *
 * Information:
 *
 * This file defines the Sprite class, which is implemented in its respective .cpp file.
 *
 */
#ifndef sprite_h
#define sprite_h
#include <allegro.h>

class Sprite {
private:
	BITMAP* image;
	int width;
	int height;
	int x_pos;
	int y_pos;
	int speed;
	bool alive;
public:
	Sprite();
	~Sprite();
	bool load(const char* filename);
	void draw(BITMAP* dest);
	BITMAP* get_image();
	int get_width();
	int get_height();
	int get_x_pos();
	int get_y_pos();
	int get_speed();
	bool get_alive();
	void set_image(BITMAP* new_image);
	void set_x_pos(int new_pos);
	void set_y_pos(int new_pos);
	void set_speed(int new_speed);
	void set_alive(bool state_of_sprite);
	bool is_alive();
	bool collided(Sprite* other);
};
#endif 
