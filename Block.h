class Block
{
public:
	//create rectangle with a texture loaded from file
	Block(std::string fileName, int width, int height, int x, int y);
	//create rectangle with a texture with a color
	Block(int width, int height, int red, int green, int blue, int x, int y);
	~Block();

	void render();
	void render(int x, int y);

	void setX(int value);
	int getX();
	
	void setY(int value);
	int getY();
	
	void setWidth(int value);
	int getWidth();
	
	void setHeight(int value);
	int getHeight();

	void Block::moveX(int value);
	
private:
	Texture* texture = nullptr;
	int _x;
	int _y;
	int _width;
	int _height;
};

Block::Block(std::string fileName, int width, int height, int x, int y)
{
	texture = new Texture(fileName);
	_x = x;
	_y = y;
	_width = width;
	_height = height;
}

Block::Block(int width, int height, int red, int green, int blue, int x, int y)
{
	texture = new Texture(width, height, red, green, blue);
	_x = x;
	_y = y;
	_width = width;
	_height = height;
}

Block::~Block()
{
	delete texture;
	texture = nullptr;
}

void Block::render()
{
	if (_x > -29 && _x < 640 && _y > 1 && _y < 480)
		texture->render(_x, _y - _height, _width, _height);
}

void Block::render(int offsetX, int offsetY)
{
	texture->render(_x - (offsetX - 304), _y - _height, _width, _height);
}

void Block::setX(int value)
{
	_x = value;
}

int Block::getX()
{
	return _x;
}

void Block::setY(int value)
{
	_y = value;
}

int Block::getY()
{
	return _y;
}
void Block::setWidth(int value)
{
	_width = value;
}

int Block::getWidth()
{
	return _width;
}

void Block::setHeight(int value)
{
	_height = value;
}

int Block::getHeight()
{
	return _height;
}

void Block::moveX(int value)
{
	_x += value;
}
