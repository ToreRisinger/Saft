class Level
{
public:
	Level();
	~Level();

	void render(int x, int y);
	void render();
	void update();
	void input(Input* input);
	bool isBlock(int x, int y);
	bool playerCollision(int& x, int& y, double& xVel, double& yVel, int playerWidth, int playerHeight);
	void init();

private:
	std::vector<Block*> blocks;

};

Level::Level()
{
	init();
}

Level::~Level()
{
	unsigned size = blocks.size();
	for (unsigned int i = 0; i < size; i++)
		blocks.pop_back();
}

void Level::init()
{
	
	unsigned size = blocks.size();
	for (unsigned int i = 0; i < size; i++)
		blocks.pop_back();
	
	int randNumber;

	for (int x = 0; x < 30; ++x)
	{
		randNumber = rand() % (6);
		if (randNumber == 0) continue;
		else if (randNumber > 0)
		{
			//randNumber = rand() % (14) + 9;
			//Block* block = new Block("bricks_darkyellow_medium", 96, 32, x * 96, 8 * 32);
			Block* block = new Block(96, 32, 0, 0, 0, x * 96, 9 * 32);
			blocks.push_back(block);
		}
	}
}

void Level::render()
{
	for (Block* block : blocks)
		block->render();
}

void Level::render(int x, int y)
{
	for (Block* block : blocks)
		block->render(x, y);
}

void Level::update()
{

}

void Level::input(Input* input)
{

}

bool Level::isBlock(int x, int y)
{
	for (Block* block : blocks)
	{
		if (y >= block->getY() - 31 ) // y is under
			if (y <= block->getY()) // y is inside
				if (x >= block->getX()) // x is to the right
					if (x <= block->getX() + 31)
						return true;
	}

	return false;
}

//returns true if player is on the floor
bool Level::playerCollision(int& x, int& y, double& xVel, double& yVel, int playerWidth, int playerHeight)
{
	bool playerOnFloor = false;

	for (Block* block : blocks)
	{
		if (y - yVel >= block->getY() - block->getHeight()) // y is under
			if (y - yVel - (playerHeight - 1) <= block->getY()) // y is inside
				if (x + (playerWidth - 1) >= block->getX()) // x is to the right
					if (x <= block->getX() + block->getWidth() - 1) // x inside
					{
						if (yVel < 0)
						{
							y = block->getY() - block->getHeight();
							yVel = 0;
							playerOnFloor = true;
						}
						else if (yVel > 0)
						{
							y = block->getY() + playerHeight;
							yVel = 0;
						}
					}
	}

	for (Block* block : blocks)
	{
		if (y >= block->getY() - (block->getHeight()-1)) // y is under
			if (y - (playerHeight - 1) <= block->getY()) // y is inside
				if (x + (playerWidth - 1) + xVel >= block->getX()) // x is to the right
					if (x + xVel <= block->getX() + block->getWidth() - 1) // x inside
					{
						if (xVel < 0)
						{
							x = block->getX() + block->getWidth();
							xVel = 0;
						}
						else if (xVel > 0)
						{
							x = block->getX() - playerWidth;
							xVel = 0;
						}
					}
	}

	return playerOnFloor;
}