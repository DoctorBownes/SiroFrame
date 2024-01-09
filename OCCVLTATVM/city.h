#ifndef CITY_H_
#define CITY_H_

#include <OCCVLTATVM/hotel.h>

class City {

public:
	void AddHotelAt(Hotel* hotel, int pos);
	void AddHotelAt(std::initializer_list<Hotel*> hotel, int pos);
	Hotel* GetHotelAt(int pos) { return _hotels[pos]; };

private:
	std::vector<Hotel*> _hotels;
};

#endif