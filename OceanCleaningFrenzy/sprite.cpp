/*
 * Name: Anjolaoluwa Aina
 * Student ID: 3586267
 * Last Modified: Wednesday, February 22nd, 2023
 * File: sprite.cpp
 *
 * Information:
 *
 * This file contains the Sprite class, which is used to create a sprite in the game.
 * It is used in the Player, Fish and Trash_Pool classes.
 *
 */
#include "sprite.h"

/*
Constructs a new instance of the sprite class.
*/
Sprite::Sprite() {
	image = NULL;
	width = 0;
	height = 0;
	x_pos = 0;
	y_pos = 0;
	speed = 4;
	alive = false; // not alive
} // constructor

/*
Removes the sprite bitmap from memory.
*/
Sprite::~Sprite() {
	if (image != NULL) {
		destroy_bitmap(image);
	}
} // destructor

/*
Loads the sprite.
@returns - true if the bitmap was successfully loaded, false otherwise
*/
bool Sprite::load(const char* filename) {
	image = load_bitmap(filename, NULL);
	if (image != NULL) {
		width = image->w;
		height = image->h;
		return true;
	}
	return false; // image is NULL
} // load

/*
Gets the image of the sprite.
@return - image of sprite
*/
BITMAP* Sprite::get_image() {
	return image;
} // get_image

/*
Draws the sprite to the destination bitmap (usually screen or a buffer).
@param dest - the bitmap to that the sprite is being drawn to.
*/
void Sprite::draw(BITMAP* dest) {
	draw_sprite(dest, image, x_pos, y_pos);
} // draw

/*
Gets the width of the sprite.
@return - width of sprite
*/
int Sprite::get_width() {
	return width;
} // get_width

/*
Gets the height of the sprite.
@return - height of sprite
*/
int Sprite::get_height() {
	return height;
} // get_height

/*
Gets the current position of the sprite on the x-axis.
@return - x position of sprite
*/
int Sprite::get_x_pos() {
	return x_pos;
} // get_x_pos

/*
Gets the current position of the sprite on the y-axis.
@return - y position of sprite
*/
int Sprite::get_y_pos() {
	return y_pos;
} // get_y_pos

/*
Gets the current speed of the sprite.
@return - speed of sprite
*/
int Sprite::get_speed() {
	return speed;
} // get_speed

/*
Gets the current state of the sprite.
@return - whether the sprite is alive (true) or not (false)
*/
bool Sprite::get_alive() {
	return alive;
} // get_alive

/*
Changes the image of the sprite to be the new image specified.
@param new_image - the new image of the sprite
*/
void Sprite::set_image(BITMAP* new_image) {
	image = new_image;
	width = image->w;
	height = image->h;
} // set_image

/*
Changes the x position of the sprite.
@param new_pos the new position of the sprite on the x-axis
*/
void Sprite::set_x_pos(int new_pos) {
	x_pos = new_pos;
} // set_x_pos

/*
Changes the y position of the sprite.
@param new_pos the new position of the sprite on the y-axis
*/
void Sprite::set_y_pos(int new_pos) {
	y_pos = new_pos;
} // set_y_pos

/*
Changes the speed of the sprite.
@param new_speed - the new speed of the sprite.
*/
void Sprite::set_speed(int new_speed) {
	speed = new_speed;
} // set_speed

/*
Sets the alive state of the sprite.
@param state_of_sprite - the new alive state of the sprite
*/
void Sprite::set_alive(bool state_of_sprite) {
	alive = state_of_sprite;
} // set_alive

/*
Checks if a sprite is alive or not.
@return - true if the sprite is alive (i.e., no collision has occured), and false otherwise
*/
bool Sprite::is_alive() {
	if (alive == true) {
		return true;
	}
	else {
		return false;
	}
} // is_alive

/*
Checks if a sprite has collided with another sprite.
@return - true if a sprite has collided with another sprite (that is, their boundary rectangle collides with the boundary rectange of another sprite), and false otherwise.
*/
bool Sprite::collided(Sprite* other) {
	int other_width_offset = other->get_x_pos() + other->get_width();
	int other_height_offset = other->get_y_pos() + other->get_height();
	if ((x_pos + width) >= other->get_x_pos() && x_pos < other_width_offset && (y_pos + height) >= other->get_y_pos() && y_pos <= other_height_offset) {
		return true;
	}
	// no collisions occurred
	return false;
} // collided