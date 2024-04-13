#ifndef RENDERER_H_
#define RENDERER_H_

#define RGB_OFF 0,0,0
#define RGB_BLK 0,0,0
#define RGB_DBLU 29, 43, 83
#define RGB_DPUR 126, 37, 83
#define RGB_DGRN 0, 135, 81
#define RGB_BRN 171, 82, 54
#define RGB_DGRY 95, 87, 79
#define RGB_LGRY 194, 195, 199
#define RGB_WHT 255, 241, 232
#define RGB_RED 255, 0, 77
#define RGB_ORN 255, 163, 0
#define RGB_YLW 255, 236, 39
#define RGB_GRN 0, 228, 54
#define RGB_BLU 41, 173, 255
#define RGB_LAV 131, 118, 156
#define RGB_PNK 255, 119, 168
#define RGB_PCH 255, 204, 170

#define WIN_WIDTH 256
#define WIN_HEIGHT 192
#define TILESIZE 8

typedef unsigned int GLuint;

class SiroRenderer {
public:
	SiroRenderer(const SiroRenderer&) = delete;

	static SiroRenderer* GetRenderer()
	{
		if (!_instance)	{
			_instance = new SiroRenderer();
		}
		return _instance;
	}

	void UpdatePalette(struct Palette* _palette);

	void UpdateGameScreen(void);

	void DrawGameScreen(void);

	unsigned char spritebuffer[WIN_WIDTH][WIN_WIDTH];
	unsigned char tilebuffer[WIN_WIDTH][WIN_WIDTH];

	friend class SiroCore;

private:
	SiroRenderer();

	static SiroRenderer* _instance;

	unsigned char rgba_palettebuffer[64];

	GLuint shaderProgram;
	GLuint vertexbuffer;
	GLuint BGTextureSampler;
	GLuint FGTextureSampler;
	GLuint PaletteSampler;
	GLuint EBO;

	void SetupRenderer();

};

#endif
