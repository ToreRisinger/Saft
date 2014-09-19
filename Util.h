SDL_Renderer* gRenderer = nullptr;
TTF_Font *gFont = nullptr;

enum STATE {
	MAINMENU,
	GAME,
	EXIT
};

STATE state;
