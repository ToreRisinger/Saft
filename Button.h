
class Button
{
public:
	Button(std::string textureFileName, std::string buttonText, unsigned int fontSize, SDL_Color textColor, int textX, int textY, STATE state, int width, int height, int x, int y);
	~Button();

	void render();
	void update();
	void input(Input* input);
	void select();
	void deselect();

private:
	Texture* deselectedTexture = nullptr;
	Texture* selectedTexture = nullptr;
	Texture* deselectedText = nullptr;
	Texture* selectedText = nullptr;
	STATE _state;
	bool _selected;
	int _x;
	int _y;
	int _textX;
	int _textY;
	int _width;
	int _height;

};

Button::Button(std::string textureFileName, std::string buttonText, unsigned int fontSize, SDL_Color textColor, int textX, int textY, STATE state, int width, int height, int x, int y)
{
	deselectedTexture = new Texture(textureFileName + "_deselected");
	selectedTexture = new Texture(textureFileName + "_selected");
	deselectedText = new Texture(buttonText, fontSize, textColor);
	selectedText = new Texture(buttonText, fontSize, textColor);
	_selected = false;
	_x = x;
	_y = y;
	_textX = textX;
	_textY = textY;
	_width = width;
	_height = height;
	_state = state;
}

Button::~Button()
{

}

void Button::render()
{
	if (_selected)
	{
		selectedTexture->render(_x, _y, _width, _height);
		selectedText->render(_textX+2, _textY+2, selectedText->getWidth(), selectedText->getHeight());
	}
	else if (!_selected)
	{
		deselectedTexture->render(_x, _y, _width, _height);
		deselectedText->render(_textX, _textY, selectedText->getWidth(), selectedText->getHeight());
	}
}

void Button::update()
{

}

void Button::input(Input* input)
{
	if (_selected && input->getKey(SDL_SCANCODE_SPACE))
	{
		state = _state;
	}
}

void Button::select()
{
	_selected = true;
}

void Button::deselect()
{
	_selected = false;
}
