#include "hotel.h"
#include <OCCVLTATVM/room.h>

void Hotel::AddRoomAt(Room* room, int pos) {
	_rooms.insert(_rooms.begin() + pos, room);
}

void Hotel::AddRoomAt(std::initializer_list<Room*> room, int pos) {
	_rooms.insert(_rooms.begin() + pos, room);
}
