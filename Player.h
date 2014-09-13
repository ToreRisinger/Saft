
class Player
{
public:
	Player();
	~Player();

	void render();
	void update();
	void input(Input* input);

private:
	Texture* texture = nullptr;
	int x;
	int y;
	int width;
	int height;
	double yVel;
	double xVel;
	bool jumping;
};

Player::Player()
{
	texture = new Texture("default_texture");
	x = 0;
	y = 6 * 32;
	width = 32;
	height = 32;
	yVel = 0;
	jumping = false;
}

Player::~Player()
{
	delete texture;
}

void Player::render()
{
	texture->render(x, y, width, height);
}

void Player::update()
{
	if (y > 6 * 32)
	{
		yVel = 0;
		y = 6 * 32;
		jumping = false;
	}
	if (jumping) {
		yVel = yVel - 0.15;
		y = y - yVel;
	}

}

void Player::input(Input* input)
{
	if (input->getKey(SDL_SCANCODE_D))
	{
		x+=4;
	}
	if (input->getKey(SDL_SCANCODE_A))
	{
		x-=4;
	}
	if (input->getKeyPressed(SDL_SCANCODE_W))
	{
		yVel = 4;
		xVel = 4;
		jumping = true;
	}
}

