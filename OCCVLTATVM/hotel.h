#ifndef HOTEL_H_
#define HOTEL_H_

#include <OCCVLTATVM/room.h>
#include <initializer_list>
#include <vector>

class Hotel {

public:
	void AddRoomAt(Room* room, int pos);
	void AddRoomAt(std::initializer_list<Room*> room, int pos);
	Room* GetRoomAt(int pos) { return _rooms[pos]; };
	Room* GetDynamicRoom() { return _rooms[RoomNumber]; };

	int RoomNumber = 0;

private:
	std::vector<Room*> _rooms;
};

#endif