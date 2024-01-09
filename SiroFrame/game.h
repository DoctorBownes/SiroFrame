#ifndef GAME_H_
#define GAME_H_

class Game {
public:
	/**
	 * @brief Setup of the game. Runs only once at the beginning.
	 */
	virtual void setup();
	/**
	 * @brief Loop of the game. Runs 60 times per second.
	 */
	virtual void loop();
}; 

#endif
