#ifndef SPRITE_H_
#define SPRITE_H_

#include <initializer_list>
#include <SiroFrame/vector.h>

struct Sprite {
	/**
	 * @brief An array of pixels forming an image.
	 *
	 * @param _width:
	 * The width of the image.
	 * @param _height:
	 * The height of the image.
	 * @param _pixels:
	 * The array itself. Can be of any shape or size inline with the width and height.
	 */
	Sprite(unsigned char _width, unsigned char _height, unsigned char _pixels,...);
	~Sprite();
	unsigned char width;
	unsigned char height;
	unsigned char* image;
};

struct AnimatedSprite {
	/**
	 * @brief An array sprites forming an animation.
	 *
	 * @param _sprites:
	 * The array of sprites.
	 * @param _speed:
	 * The speed at which the Animation is to be played.
	 */
	AnimatedSprite(std::initializer_list<Sprite*> _sprites, unsigned char _speed);
	SiroVector<Sprite*> sprites;
	unsigned char speed;
	unsigned char frame;
};

struct Tile {
	unsigned char canvas[8 * 8];
};

#endif
