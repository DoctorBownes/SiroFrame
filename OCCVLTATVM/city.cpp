#include "city.h"

void City::AddHotelAt(Hotel* hotel, int pos) {
	_hotels.insert(_hotels.begin() + pos, hotel);
}

void City::AddHotelAt(std::initializer_list<Hotel*> hotel, int pos) {
	_hotels.insert(_hotels.begin() + pos, hotel);
}
