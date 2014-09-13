
class Menu
{
public:
	Menu();
	~Menu();

	void render();
	void update();
	void input(Input* input);
	void addButton(std::string fileName, STATE state, int width, int height, int x, int y);
	void addBackground(int width, int height, int red, int green, int blue);

private:
	Rectangle* background = nullptr;
	std::vector<Button*> buttons;
	int selectedButton;
};

Menu::Menu()
{
	selectedButton = 0;
}

Menu::~Menu()
{

}

void Menu::render()
{
	//Render background
	if (background != nullptr)
		background->render();

	//Render all buttons
	for (Button* button : buttons)
	{
		if (button != nullptr)
			button->render();
	}
}
void Menu::update()
{

}
void Menu::input(Input* input)
{
	//move up and down in the menu
	if (input->getKey(SDL_SCANCODE_DOWN))
	{	
		if (selectedButton + 1 < buttons.size())
		{
			selectedButton++;
			buttons.at(selectedButton - 1)->deselect();
			buttons.at(selectedButton)->select();
		}
	}
	else if (input->getKey(SDL_SCANCODE_UP))
	{
		if (selectedButton > 0)
		{
			selectedButton--;
			buttons.at(selectedButton + 1)->deselect();
			buttons.at(selectedButton)->select();
		}
	}
	
	//Input all buttons
	for (Button* button : buttons)
	{
		if (button != nullptr)
			button->input(input);
	}
}

void Menu::addButton(std::string fileName, STATE state, int width, int height, int x, int y)
{
	Button* newButton = new Button(fileName, state, width, height, x, y);
	buttons.push_back(newButton);
	
	//select first button in the vector
	if (buttons.size() == 1) buttons.at(0)->select();
}

void Menu::addBackground(int width, int height, int red, int green, int blue)
{
	background = new Rectangle(width, height, red, green, blue, 0, 0);
}