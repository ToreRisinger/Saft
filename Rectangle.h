#include "Texture.h"
#include <string>

class Rectangle
{
public:
	Rectangle();
	~Rectangle();

	void render();
	void setTexture(std::string fileName);
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
	int x;
	int y;
	int width;
	int height;
};

Rectangle::Rectangle()
{
	texture = new Texture("default_texture.png");
	x = 0;
	y = 0;
	width = 0;
	height = 0;
}

Rectangle::~Rectangle()
{
	delete texture;
	texture = nullptr;
}

void Rectangle::render()
{
	texture->render(x, y, width, height);
}

void Rectangle::setTexture(std::string fileName)
{
	texture->loadTexture(fileName);
}

void Rectangle::setX(int value)
{
	x = value;
}

int Rectangle::getX()
{
	return x;
}

void Rectangle::setY(int value)
{
	y = value;
}

int Rectangle::getY()
{
	return y;
}
void Rectangle::setWidth(int value)
{
	width = value;
}

int Rectangle::getWidth()
{
	return width;
}

void Rectangle::setHeight(int value)
{
	height = value;
}

int Rectangle::getHeight()
{
	return height;
}
