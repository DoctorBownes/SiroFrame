#ifndef RENDERER_H_
#define RENDERER_H_

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

	unsigned char pixelbuffer[WIN_WIDTH][WIN_WIDTH];

	friend class SiroCore;

private:
	SiroRenderer();

	void DrawGameScreen(void);

	void UpdateGameScreen(void);

	static SiroRenderer* _instance;

	GLuint shaderProgram;
	GLuint vertexbuffer;
	GLuint TextureSampler;
	GLuint PaletteSampler;
	GLuint EBO;

	void SetupRenderer();

};

#endif
