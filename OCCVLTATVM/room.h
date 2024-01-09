#ifndef ROOM_H_
#define ROOM_H_

#include <SiroFrame/game.h>
#include <SiroFrame/pencil.h>
#include <SiroFrame/input.h>
#include <OCCVLTATVM/decorator.h>
#include <OCCVLTATVM/entity.h>

class Room : public Game {

public:

protected:
	SiroInput* Input = Input->PlugInKeyboard();
	SiroPencil* Pencil = Pencil->SharpenPencil();
	Decorator* Decor = Decor->PayDecorator();

private:

};

#endif
