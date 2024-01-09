#include <SiroFrame/core.h>
#include <SiroFrame/input.h>
#include <SiroFrame/game.h>
#include <OCCVLTATVM/bronx/pregoapartments.h>
#include <OCCVLTATVM/city.h>

SiroInput* input = input->PlugInKeyboard();

//extern unsigned char* TileMap;

int main(void) {
	SiroCore sc;

	sc.StartupConsole();

	Hotel* hotel = new Hotel();
	City* bronx = new City();

	//hotel->AddRoomAt({room1, room2}, 0);

	bronx->AddHotelAt(new PregoApartments(), 0);

	while (!sc.ShutdownConsole() && !input->KeyDown(KeyCode::Escape)) {

		sc.RunGame(bronx->GetHotelAt(0)->GetRoomAt(0));

	}

	return 0;
}
