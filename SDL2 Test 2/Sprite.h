#include <SDL\SDL_image.h>

class Sprite
{
public:
	Sprite(SDL_Renderer *renderer, const char *filename, int width, int height);
	~Sprite();
	void draw();
	void setX(int x);
	void setY(int y);
	int getX();
	int getY();

private:
	SDL_Texture *imageTexture;
	SDL_Renderer *renderer;
	int width;
	int height;
	int x;
	int y;
};