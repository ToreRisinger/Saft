
class Button
{
public:
	Button(std::string fileName, STATE state, int width, int height, int x, int y);
	~Button();

	void render();
	void update();
	void input(Input* input);
	void select();
	void deselect();

private:
	Rectangle* selectedRect;
	Rectangle* deselectedRect;
	STATE _state;
	bool _selected;
	int _x;
	int _y;
	int _width;
	int _height;

};

Button::Button(std::string fileName, STATE state, int width, int height, int x, int y)
{
	deselectedRect = new Rectangle(fileName + "_deselected", width, height, x, y);
	selectedRect = new Rectangle(fileName + "_selected", width, height, x, y);
	_selected = false;
	_x = x;
	_y = y;
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
		selectedRect->render();
	else if (!_selected)
		deselectedRect->render();
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
