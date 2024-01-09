#include "decorator.h"

Decorator* Decorator::_instance = 0;

void Decorator::DecorateRoom(unsigned char* TileMap) {
	LoadedMap = TileMap;
	unsigned short sum = 0;
	for (int y = 0; y < 24; y++) {
		for (int x = 0; x < 32; x++) {
			if (TileArray[TileMap[sum]]) {
				pncl->DrawTile(TileArray[TileMap[sum]], x, y);
			}
			sum++;
		}
	}
}

Decorator::Decorator() {
	for (int j = 0; j < 16; j++) {
		TileArray[j] = nullptr;
	}
}