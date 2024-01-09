#include <SiroFrame/sprite.h>
#include <stdarg.h>

Sprite::Sprite(unsigned char _width, unsigned char _height, unsigned char _pixels,...) {
	int result;
	va_list list;
	va_start(list, _pixels);
	image = new unsigned char[_width * _height];
	width = _width;
	height = _height;
	image[0] = _pixels;
	for (int i = 1; i < _width * _height; i++) {
		result = va_arg(list, unsigned char);
		image[i] = result;
	}
	va_end(list);
}

Sprite::~Sprite() {
	delete[] image;
}

AnimatedSprite::AnimatedSprite(std::initializer_list<Sprite*> _sprites, unsigned char _speed) {
	for (int i = 0; i < _sprites.size(); i++) {
		sprites.push_back(_sprites.begin()[i]);
	}
	speed = _speed;
	frame = 0;
}
