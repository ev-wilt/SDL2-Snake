#include <vector>
#include "Sprite.h"

enum Direction { up, down, left, right };

class Snake
{
public:
	Snake();
	void draw();
	void update();
	void checkInput();
	bool ateFood();

private:
	std::vector<Sprite> snakeSegments;
	Direction currentDirection;
};

