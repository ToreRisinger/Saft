SDL_Renderer* gRenderer = nullptr;
TTF_Font *gFont = nullptr;

enum STATE {
	MAINMENU,
	GAME
};

STATE state = MAINMENU;
