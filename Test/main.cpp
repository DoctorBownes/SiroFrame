#include <SiroFrame/core.h>
#include <SiroFrame/game.h>
#include <SiroFrame/pencil.h>
#include <SiroFrame/input.h>
#include <vector>
#include <stdio.h>

SiroInput* input = input->PlugInKeyboard();
SiroPencil* pencil = pencil->SharpenPencil();

#define RESETPLAYER {pepe->x = 128; \
					pepe->y = 176;\
}

struct Entity {
	Sprite* sprite;
	unsigned char x;
	unsigned char y;
};

struct Lane {
	Lane(Sprite* carsprite, unsigned char colour, int size, unsigned char y_pos);
	virtual void UpdateLane(int speed);
	std::vector<Entity*>cars;
	unsigned char _colour;
	signed int _speed;
};

void Lane::UpdateLane(signed int speed) {
	_speed = speed;
	for (int i = 0; i < cars.size(); i++) {
		pencil->DrawSprite(cars[i]->sprite, cars[i]->x, cars[i]->y, _colour);
		cars[i]->x += _speed;
	}
}

Lane::Lane(Sprite* carsprite, unsigned char colour, int size, unsigned char y_pos) {
	cars.resize(size);
	for (int i = 0; i < cars.size(); i++) {
		cars[i] = new Entity();
		cars[i]->sprite = carsprite;
		cars[i]->x = i * (256 / cars.size());
		cars[i]->y = y_pos;
	}
	_colour = colour;
}

class Frogger : public Game {
public:
	void setup() override;
	void loop() override;

	Entity* pepe = new Entity();

	bool Collision(Entity* entity1, Entity* entity2);

};

unsigned char posx = 0;
unsigned char posy = 0;

Sprite* frogsprite = new Sprite(8, 8,
		0,1,0,1,1,0,1,0,
		1,1,1,1,1,1,1,1,
		0,1,1,1,0,1,1,0,
		0,0,1,1,1,1,0,0,
		0,0,1,0,1,1,0,0,
		0,1,1,1,1,1,1,0,
		1,1,0,1,1,0,1,1,
		0,1,0,0,0,0,1,0
	);

Sprite* car = new Sprite(16, 8,
		0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,
		0,0,0,0,0,0,1,0,1,0,0,0,0,1,0,0,
		0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,0,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
		1,1,0,0,0,1,1,1,1,1,1,0,0,0,1,1,
		1,0,0,1,0,0,1,1,1,1,0,0,1,0,0,1,
		1,0,1,0,1,0,1,1,1,1,0,1,0,1,0,1,
		0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0
	);

Sprite* logg = new Sprite(24, 8,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,
	0,1,1,1,0,1,1,1,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,0,
	0,1,1,0,0,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,0,
	0,0,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
	0,1,1,1,0,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,1,1,1,0,
	0,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
	);

Lane* slowlane = new Lane(car, DGRN, 3, 168);

Lane* midllane = new Lane(car, CYN | MIRROR, 4, 8 * 18);

Lane* fastlane = new Lane(car, RED, 2, 8 * 15);

Lane* waterlane = new Lane(logg, DYLW, 4, 8 * 11);
Lane* waterlane2 = new Lane(logg, DYLW, 6, 8 * 10);
Lane* waterlane3 = new Lane(logg, DYLW, 3, 8 * 9);
Lane* waterlane4 = new Lane(logg, DYLW, 3, 8 * 8);

bool Frogger::Collision(Entity* entity1, Entity* entity2) {
	if (entity1->x + entity1->sprite->width > entity2->x &&
		entity1->x < entity2->x + entity2->sprite->width &&
		entity1->y + entity1->sprite->height > entity2->y &&
		entity1->y < entity2->y + entity2->sprite->height
		) {
		return true;
	}
	return false;
}



void Frogger::setup() {
	pepe->sprite = frogsprite;
	RESETPLAYER;

}

void Frogger::loop() {
	pencil->ClearScreen();

	slowlane->UpdateLane(-1);
	for (int i = 0; i < slowlane->cars.size(); i++) {
		if (Collision(pepe, slowlane->cars[i])) {
			RESETPLAYER;
		}
	}

	midllane->UpdateLane(2);
	for (int i = 0; i < midllane->cars.size(); i++) {
		if (Collision(pepe, midllane->cars[i])) {
			RESETPLAYER;
		}
	}
	fastlane->UpdateLane(-4);
	for (int i = 0; i < fastlane->cars.size(); i++) {
		if (Collision(pepe, fastlane->cars[i])) {
			RESETPLAYER;
		}
	}


	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 32; x++) {
			pencil->DrawBGColour(x, y + 8, DBLU);
		}
	}

	waterlane->UpdateLane(1);
	waterlane2->UpdateLane(-1);
	waterlane3->UpdateLane(1);
	waterlane4->UpdateLane(-3);


	if (pepe->y >= 64 && pepe->y < 96) {
		bool touch = false;
		for (int i = 0; i < waterlane->cars.size(); i++) {
			if (Collision(pepe, waterlane->cars[i])) {
				pepe->x += waterlane->_speed;
				touch = true;
			}
		}
		for (int i = 0; i < waterlane2->cars.size(); i++) {
			if (Collision(pepe, waterlane2->cars[i])) {
				pepe->x += waterlane2->_speed;
				touch = true;
			}
		}
		for (int i = 0; i < waterlane3->cars.size(); i++) {
			if (Collision(pepe, waterlane3->cars[i])) {
				pepe->x += waterlane3->_speed;
				touch = true;
			}
		}
		for (int i = 0; i < waterlane4->cars.size(); i++) {
			if (Collision(pepe, waterlane4->cars[i])) {
				pepe->x += waterlane4->_speed;
				touch = true;
			}
		}
		if (!touch) {
			RESETPLAYER;
		}
	}

	pencil->DrawBGColour( 4, 5, MGT);
	pencil->DrawBGColour(12, 5, MGT);
	pencil->DrawBGColour(20, 5, MGT);
	pencil->DrawBGColour(28, 5, MGT);

	if (input->KeyPressed(KeyCode::Up)) {
		pepe->y -= 8;
	}
	else if (input->KeyPressed(KeyCode::Down)) {
		pepe->y += 8;
	}
	else if (input->KeyPressed(KeyCode::Left)) {
		pepe->x -= 8;
	}
	else if (input->KeyPressed(KeyCode::Right)) {
		pepe->x += 8;
	}

	pencil->DrawSprite(pepe->sprite, pepe->x, pepe->y, GRN);
}

int main(void) {
	SiroCore sc;

	Frogger* frogger = new Frogger();

	sc.StartupConsole("Frogger");
	
	while (!sc.ShutdownConsole()) {
		sc.RunGame(frogger);
	}

	return 0;
}
