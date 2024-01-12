#ifndef PENCIL_H_
#define PENCIL_H_

#include <SiroFrame/sprite.h>

class SiroRenderer;

class SiroPencil {
public:
	SiroPencil(const SiroPencil&) = delete;

	/**
	 * @brief Initializes SiroPencil.
	 */
	static SiroPencil* SharpenPencil()
	{
		if (!_instance)
		{
			_instance = new SiroPencil();
		}
		return _instance;
	}

	/**
	 * @brief This draws a single Sprite Image onto the screen.
	 *
	 * @param sprite:
	 * The sprite you wish to put on the screen.
	 * @param x_pos:
	 * The x position of the sprite.
	 * @param y_pos:
	 * The y position of the sprite.
	 * @param colour:
	 * The colour and or mirroring of the sprite.
	 */
	void DrawSprite(Sprite* sprite, unsigned char x_pos, unsigned char y_pos, unsigned char dir = 0);

	/**
	 * @brief This draws an Animated Sprite Image onto the screen.
	 *
	 * @param animation:
	 * The Sprite Animation you wish to put on the screen.
	 * @param x_pos:
	 * The x position of the displayed sprite.
	 * @param y_pos:
	 * The y position of the displayed sprite.
	 * @param colour:
	 * The colour and or mirroring of the displayed sprite.
	 */
	bool DrawAnimatedSprite(AnimatedSprite* animation, unsigned char x_pos, unsigned char y_pos, unsigned char colour);

	/**
	 * @brief This draws a single pixel onto the screen.
	 *
	 * @param x_pos:
	 * The x position of the pixel.
	 * @param y_pos:
	 * The y position of the pixel.
	 * @param colour:
	 * The colour of the pixel.
	 */
	void DrawPixel(unsigned char x_pos, unsigned char y_pos, unsigned char colour);

	/**
	 * @brief This draws an 8x8 colour to the background.
	 *
	 * @param x_pos:
	 * The x position of the colour.
	 * @param y_pos:
	 * The y position of the colour.
	 * @param colour:
	 * The colour itself.
	 */
	void DrawTile(Tile* tile, unsigned char x_pos, unsigned char y_pos);

	/**
	 * @brief This draws a single Tile onto the screen.
	 *
	 * @param SizeTenArray:
	 * An array of at least 10 tiles.
	 * @param x_pos:
	 * The x position of the number.
	 * @param y_pos:
	 * The y position of the number.
	 * @param number:
	 * The value of the number.
	 * @param blankdigit:
	 * The Tile you wish to leave when a digit disappears.
	 */
	void DrawTileNumber(Tile* SizeTenArray[10], unsigned char x_pos, unsigned char y_pos, int number, Tile* blankdigit);
	/**
	 * @brief This draws a single Tile onto the screen.
	 *
	 * @param SizeTenArray:
	 * An array of at least 10 tiles.
	 * @param x_pos:
	 * The x position of the number.
	 * @param y_pos:
	 * The y position of the number.
	 * @param number:
	 * The value of the number.
	 * @param colour:
	 * The Background Colour you wish to leave when a digit disappears. Default is black.
	 */
	void DrawTileNumber(Tile* SizeTenArray[10], unsigned char x_pos, unsigned char y_pos, int number, unsigned char colour = 0);

	/**
	 * @brief Clears the entire screen of all pixels.
	 *
	 * @param colour:
	 * The Background Colour of your choosing. Default is black.
	 */
	void ClearScreen(unsigned char colour = 0);

	/**
	 * @brief Removes a single Tile from the screen.
	 *
	 * @param x_pos:
	 * The x position of the Tile you wish to remove.
	 * @param y_pos:
	 * The y position of the Tile you wish to remove.
	 * @param colour:
	 * The Background Colour you wish to leave behind. Default is black.
	 */
	void RemoveTile(unsigned char x_pos, unsigned char y_pos);

	/**
	 * @brief Removes a single Sprite from the screen.
	 *
	 * @param sprite:
	 * The Sprite you wish to remove.
	 * @param x_pos:
	 * The x position of the Sprite.
	 * @param y_pos:
	 * The y position of the Sprite.
	 */
	void RemoveSprite(Sprite* sprite, unsigned char x_pos, unsigned char y_pos);

	Palette* GetPalette() { return _palette; };
	void SetPalette(Palette* palette);
	void SetColor(unsigned char pos, Color color);

private:

	SiroPencil();

	static SiroPencil* _instance;

	Palette* _palette;

	SiroRenderer* _renderer;
};

#endif
