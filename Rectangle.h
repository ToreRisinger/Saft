

class Rectangle
{
public:
	//create rectangle with a texture loaded from file
	Rectangle(std::string fileName, int width, int height, int x, int y);
	//create rectangle with a texture with a color
	Rectangle(int width, int height, int red, int green, int blue, int x, int y);
	~Rectangle();

	void render();
	void setX(int value);
	int getX();
	void setY(int value);
	int getY();
	void setWidth(int value);
	int getWidth();
	void setHeight(int value);
	int getHeight();
	
private:
	Texture* texture = nullptr;
	int _x;
	int _y;
	int _width;
	int _height;
};

Rectangle::Rectangle(std::string fileName, int width, int height ,int x, int y)
{
	texture = new Texture(fileName);
	_x = x;
	_y = y;
	_width = width;
	_height = height;
}

Rectangle::Rectangle(int width, int height, int red, int green, int blue, int x, int y)
{
	texture = new Texture(width, height, red, green, blue);
	_x = x;
	_y = y;
	_width = width;
	_height = height;
}

Rectangle::~Rectangle()
{
	delete texture;
	texture = nullptr;
}

void Rectangle::render()
{
	texture->render(_x, _y, _width, _height);
}

void Rectangle::setX(int value)
{
	_x = value;
}

int Rectangle::getX()
{
	return _x;
}

void Rectangle::setY(int value)
{
	_y = value;
}

int Rectangle::getY()
{
	return _y;
}
void Rectangle::setWidth(int value)
{
	_width = value;
}

int Rectangle::getWidth()
{
	return _width;
}

void Rectangle::setHeight(int value)
{
	_height = value;
}

int Rectangle::getHeight()
{
	return _height;
}
