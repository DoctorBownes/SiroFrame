#ifndef DECORATOR_H_
#define DECORATOR_H_

#include <SiroFrame/sprite.h>
#include <SiroFrame/pencil.h>

class Decorator {
public:
	Decorator(const Decorator&) = delete;

	static Decorator* PayDecorator()
	{
		if (!_instance)
		{
			_instance = new Decorator();
		}
		return _instance;
	}

	Tile* TileArray[16];
	SiroPencil* pncl = pncl->SharpenPencil();

	unsigned char hotelnum = 0;
	unsigned char roomnum = 0;

	unsigned char GetTile(unsigned char tile) { return LoadedMap[tile]; };

	void DecorateRoom(unsigned char TileScreen[32 * 24]);

private:
	Decorator();

	unsigned char* LoadedMap;

	static Decorator* _instance;
};

#endif
