class Game
{
public:
	Game();
	~Game();
	void render();
	void update();
	void input(Input* input);
private:
	std::vector<Rectangle*> rectangles;
	Player* player = nullptr;
	Menu* mainmenu = nullptr;
};

Game::Game()
{
	state = MAINMENU;

	player = new Player();

	mainmenu = new Menu();

	mainmenu->addBackground(640, 480, 100, 80, 80);

	SDL_Color textColor = { 0, 0, 0 };
	mainmenu->addButton("button1", "Game", 20, textColor, 296, 102, GAME, 64, 32, 288, 96);
	mainmenu->addButton("button1", "Help", 20, textColor, 296, 166, MAINMENU, 64, 32, 288, 160);
	mainmenu->addButton("button1", "Score", 20, textColor, 292, 230, MAINMENU, 64, 32, 288, 224);
	mainmenu->addButton("button1", "Exit", 20, textColor, 296, 294, EXIT, 64, 32, 288, 288);

	for (int x = 0; x < 20; ++x)
	{
		for (int y = 7; y < 15; ++y)
		{
			Rectangle* rect = new Rectangle("bricks_darkyellow_medium", 32, 32, x*32, y*32);
			rectangles.push_back(rect);
		}
	}
}

Game::~Game() {}

void Game::render()
{
	if (state == MAINMENU)
	{
		mainmenu->render();
	}
	else if (state == GAME)
	{
		for (Rectangle* rect : rectangles)
			rect->render();
		
		player->render();
	}
}

void Game::update()
{
	if (state == MAINMENU)
	{
		mainmenu->update();
	}
	else if (state == GAME)
	{
		player->update();
	}
	else if (state == EXIT)
	{
		SDL_Event* e = new SDL_Event;
		e->type = SDL_QUIT;
		SDL_PushEvent(e);
	}
}

void Game::input(Input* input)
{
	if (state == MAINMENU)
	{
		mainmenu->input(input);
	}
	else if (state == GAME)
	{
		player->input(input);
	}
}
